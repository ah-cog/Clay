/**
 * \file
 * \brief This is the implementation of the Nordic Semiconductor nRF24L01+ low level driver.
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module deals with the low level functions of the transceiver.
 */

#include "RNetConf.h"
#include "Radio.h"
#include "RadioNRF24.h"
#include "RF1.h"
#include "RMSG.h"
#include "RStdIO.h"
#include "RPHY.h"
#include "UTIL1.h"
#include "Events.h" /* for event handler interface */

#define NRF24_DYNAMIC_PAYLOAD  1 /* if set to one, use dynamic payload size */
#define RADIO_CHANNEL_DEFAULT  RNET_CONFIG_TRANSCEIVER_CHANNEL  /* default communication channel */

/* macros to configure device either for RX or TX operation */
#define RF1_CONFIG_SETTINGS  (RF1_EN_CRC|RF1_CRCO)
#define TX_POWERUP()         RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS|RF1_PWR_UP|RF1_PRIM_TX) /* enable 2 byte CRC, power up and set as PTX */
#define RX_POWERUP()         RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS|RF1_PWR_UP|RF1_PRIM_RX) /* enable 1 byte CRC, power up and set as PRX */
#define POWERDOWN()          RF1_WriteRegister(RF1_CONFIG, RF1_CONFIG_SETTINGS) /* power down */

static bool RADIO_isSniffing = FALSE;
static const uint8_t RADIO_TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address, as specified in the properties */

#if RNET_CONFIG_SEND_RETRY_CNT>0
static uint8_t RADIO_RetryCnt;
static uint8_t TxDataBuffer[RPHY_BUFFER_SIZE]; /*!< global buffer if using retries */
#endif

/* Radio state definitions */
typedef enum RADIO_AppStatusKind {
  RADIO_INITIAL_STATE, /* initial state of the state machine */
  RADIO_RECEIVER_ALWAYS_ON, /* receiver is in RX mode */
  RADIO_TRANSMIT_DATA, /* send data */
  RADIO_WAITING_DATA_SENT, /* wait until data is sent */
  RADIO_TIMEOUT,
  RADIO_READY_FOR_TX_RX_DATA,
  RADIO_CHECK_TX,   /* send data if any */
  RADIO_POWER_DOWN, /* transceiver powered down */
} RADIO_AppStatusKind;

static RADIO_AppStatusKind RADIO_AppStatus = RADIO_INITIAL_STATE;
static RPHY_PacketDesc radioRx;
static uint8_t radioRxBuf[RPHY_BUFFER_SIZE];
static uint8_t RADIO_CurrChannel = RADIO_CHANNEL_DEFAULT;

/* need to have this in case RF device is still added to project */
static volatile bool RADIO_isrFlag; /* flag set by ISR */

static void Err(unsigned char *msg) {
  (void)msg; /* not used, as no Shell used */
}

/* callback called from radio driver */
void RADIO_OnInterrupt(void) {
  RADIO_isrFlag = TRUE;
}

uint8_t RADIO_FlushQueues(void) {
  uint8_t res = ERR_OK;
  
  if (RPHY_FlushRxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  if (RPHY_FlushTxQueue()!=ERR_OK) {
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t RADIO_Flush(void) {
  RF1_Write(RF1_FLUSH_RX); /* flush old data */
  RF1_Write(RF1_FLUSH_TX); /* flush old data */
  return ERR_OK;
}

bool RADIO_CanDoPowerDown(void) {
  if (RADIO_isrFlag) {
    return FALSE; /* interrupt pending */
  }
  switch(RADIO_AppStatus) {
    case RADIO_TRANSMIT_DATA:
    case RADIO_WAITING_DATA_SENT:
    case RADIO_TIMEOUT:
      return FALSE; /* sending/receiving data, cannot power down */

    case RADIO_INITIAL_STATE:
    case RADIO_RECEIVER_ALWAYS_ON:
    case RADIO_READY_FOR_TX_RX_DATA:
    case RADIO_CHECK_TX:
    case RADIO_POWER_DOWN:
      break; /* check other conditions */
    default:
      break;
  } /* switch */
  if (RMSG_RxQueueNofItems()!=0) {
    return FALSE; /* items received, cannot power down */
  }
  if (RMSG_TxQueueNofItems()!=0) {
    return FALSE; /* items to be sent, cannot power down */
  }
  return TRUE; /* ok to power down */
}

uint8_t RADIO_PowerDown(void) {
  uint8_t res;
  
  res = RADIO_Flush();
  POWERDOWN();
  return res;
}

static uint8_t CheckTx(void) {
  RPHY_PacketDesc packet;
  uint8_t res = ERR_OK;
#if RNET_CONFIG_SEND_RETRY_CNT==0
  uint8_t TxDataBuffer[RPHY_BUFFER_SIZE]; /* local tx buffer if not using retries */
#endif
  RPHY_FlagsType flags;
  
  if (RMSG_GetTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
    flags = RPHY_BUF_FLAGS(TxDataBuffer);
    if (flags&RPHY_PACKET_FLAGS_POWER_DOWN) {
      /* special request */
      (void)RADIO_PowerDown();
      return ERR_DISABLED; /* no more data, pipes flushed */
    }
    RF1_StopRxTx();  /* CE low */
    TX_POWERUP();
    /* set up packet structure */
    packet.phyData = &TxDataBuffer[0];
    packet.flags = flags;
    packet.phySize = sizeof(TxDataBuffer);
#if NRF24_DYNAMIC_PAYLOAD
    packet.rxtx = RPHY_BUF_PAYLOAD_START(packet.phyData);
#else
    packet.rxtx = &RPHY_BUF_SIZE(packet.phyData); /* we transmit the data size too */
#endif
    if (RADIO_isSniffing) {
      RPHY_SniffPacket(&packet, TRUE); /* sniff outgoing packet */
    }
#if NRF24_DYNAMIC_PAYLOAD
    RF1_TxPayload(packet.rxtx, RPHY_BUF_SIZE(packet.phyData)); /* send data, using dynamic payload size */
#else
    RF1_TxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* send data, using fixed payload size */
#endif
    return ERR_OK;
  } else {
    return ERR_NOTAVAIL; /* no data to send? */
  }
  return res;
}

/* called to check if we have something in the RX queue. If so, we queue it */
static uint8_t CheckRx(void) {
  uint8_t res = ERR_OK;
  uint8_t RxDataBuffer[RPHY_BUFFER_SIZE];
  uint8_t status;
  RPHY_PacketDesc packet;
  bool hasRxData, hasRx;
  
  hasRxData = FALSE;
  packet.flags = RPHY_PACKET_FLAGS_NONE;
  packet.phyData = &RxDataBuffer[0];
  packet.phySize = sizeof(RxDataBuffer);
#if NRF24_DYNAMIC_PAYLOAD
  packet.rxtx = RPHY_BUF_PAYLOAD_START(packet.phyData);
#else
  packet.rxtx = &RPHY_BUF_SIZE(packet.phyData); /* we transmit the data size too */
#endif
  status = RF1_GetStatusClrIRQ();
  hasRx = (status&RF1_STATUS_RX_DR)!=0;
#if !RF1_IRQ_PIN_ENABLED
#if 1 /* experimental */
  if (!hasRx) { /* interrupt flag not set, check if we have otherwise data */
    (void)RF1_GetFifoStatus(&status);
    if (!(status&RF1_FIFO_STATUS_RX_EMPTY) || (status&RF1_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
      hasRx = TRUE;
    }
  }
#endif
#endif
  if (hasRx) { /* data received interrupt */
    hasRxData = TRUE;
#if NRF24_DYNAMIC_PAYLOAD
    uint8_t payloadSize;
    
    (void)RF1_ReadNofRxPayload(&payloadSize);
    if (payloadSize>32) { /* packet with error? */
      RF1_Write(RF1_FLUSH_RX); /* flush old data */
      return ERR_FAILED;
    } else {
      RF1_RxPayload(packet.rxtx, payloadSize); /* get payload: note that we transmit <size> as payload! */
      RPHY_BUF_SIZE(packet.phyData) = payloadSize;
    }
#else
    RF1_RxPayload(packet.rxtx, RPHY_PAYLOAD_SIZE); /* get payload: note that we transmit <size> as payload! */
#endif
  }
  if (hasRxData) {
    /* put message into Rx queue */
#if RNET1_CREATE_EVENTS
    RNET1_OnRadioEvent(RNET1_RADIO_MSG_RECEIVED);
#endif
    res = RMSG_QueueRxMsg(packet.phyData, packet.phySize, RPHY_BUF_SIZE(packet.phyData), packet.flags);
    if (res!=ERR_OK) {
      if (res==ERR_OVERFLOW) {
        Err((unsigned char*)"ERR: Rx queue overflow!\r\n");
      } else {
        Err((unsigned char*)"ERR: Rx Queue full?\r\n");
      }
    }
  } else {
    res = ERR_RXEMPTY; /* no data */
  }
  return res;
}

static void RADIO_HandleStateMachine(void) {
  uint8_t status, res;
  
  for(;;) { /* will break/return */
    switch (RADIO_AppStatus) {
      case RADIO_INITIAL_STATE:
        RF1_StopRxTx();  /* will send/receive data later */
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      case RADIO_RECEIVER_ALWAYS_ON: /* turn receive on */
        RX_POWERUP();
        RF1_StartRxTx(); /* Listening for packets */
        RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        break; /* process switch again */
  
      case RADIO_READY_FOR_TX_RX_DATA: /* we are ready to receive/send data data */
#if !RF1_IRQ_PIN_ENABLED
        RF1_PollInterrupt();
#if 1 /* experimental */
        if (!RADIO_isrFlag) { /* interrupt flag not set, check if we have otherwise data */
          (void)RF1_GetFifoStatus(&status);
          if (!(status&RF1_FIFO_STATUS_RX_EMPTY) || (status&RF1_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
            RADIO_isrFlag = TRUE;
          }
        }
#endif
#endif
        if (RADIO_isrFlag) { /* Rx interrupt? */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          res = CheckRx(); /* get message */
#if 1 /* experimental */
          (void)RF1_GetFifoStatus(&status);
          if (res==ERR_RXEMPTY && !(status&RF1_FIFO_STATUS_RX_EMPTY)) { /* no data, but still flag set? */
            RF1_Write(RF1_FLUSH_RX); /* flush old data */
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
          } else if (!(status&RF1_FIFO_STATUS_RX_EMPTY) || (status&RF1_FIFO_STATUS_RX_FULL)) { /* Rx not empty? */
            RADIO_isrFlag = TRUE; /* stay in current state */
          } else {
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
          }
#else
          RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* continue listening */
#endif
          break; /* process switch again */
        }
#if RNET_CONFIG_SEND_RETRY_CNT>0
        RADIO_RetryCnt=0;
#endif
        RADIO_AppStatus = RADIO_CHECK_TX; /* check if we can send something */
        break;
        
      case RADIO_CHECK_TX:
        res = CheckTx();
        if (res==ERR_OK) { /* there was data and it has been sent */
          RADIO_AppStatus = RADIO_WAITING_DATA_SENT;
          break; /* process switch again */
        } else if (res==ERR_DISABLED) { /* powered down transceiver */
          RADIO_AppStatus = RADIO_POWER_DOWN;
        } else {
          RADIO_AppStatus = RADIO_READY_FOR_TX_RX_DATA;
        }
        return;
        
      case RADIO_POWER_DOWN:
        return;
  
      case RADIO_WAITING_DATA_SENT:
#if !RF1_IRQ_PIN_ENABLED
        RF1_PollInterrupt();
#endif
#if 1 /* experimental */
        if (!RADIO_isrFlag) { /* check if we missed an interrupt? */
          RF1_PollInterrupt();
        }
#endif
        if (RADIO_isrFlag) { /* check if we have received an interrupt: this is either timeout or low level ack */
          RADIO_isrFlag = FALSE; /* reset interrupt flag */
          status = RF1_GetStatusClrIRQ();
          if (status&RF1_STATUS_MAX_RT) { /* retry timeout interrupt */
            RF1_Write(RF1_FLUSH_TX); /* flush old data */
            RADIO_AppStatus = RADIO_TIMEOUT; /* timeout */
          } else {
    #if RNET1_CREATE_EVENTS
            RNET1_OnRadioEvent(RNET1_RADIO_MSG_SENT);
    #endif
            RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
          }
          break; /* process switch again */
        }
        return;
        
      case RADIO_TIMEOUT:
#if RNET_CONFIG_SEND_RETRY_CNT>0
        if (RADIO_RetryCnt<RNET_CONFIG_SEND_RETRY_CNT) {
          Err((unsigned char*)"ERR: Retry\r\n");
  #if RNET1_CREATE_EVENTS
          RNET1_OnRadioEvent(RNET1_RADIO_RETRY);
  #endif
          RADIO_RetryCnt++;
          if (RMSG_PutRetryTxMsg(TxDataBuffer, sizeof(TxDataBuffer))==ERR_OK) {
            RADIO_AppStatus = RADIO_CHECK_TX; /* resend packet */
            return; /* iterate state machine next time */
          } else {
            Err((unsigned char*)"ERR: PutRetryTxMsg failed!\r\n");
  #if RNET1_CREATE_EVENTS
            RNET1_OnRadioEvent(RNET1_RADIO_RETRY_MSG_FAILED);
  #endif
          }
        }
#endif
        Err((unsigned char*)"ERR: Timeout\r\n");
#if RNET1_CREATE_EVENTS
        RNET1_OnRadioEvent(RNET1_RADIO_TIMEOUT);
#endif
        RADIO_AppStatus = RADIO_RECEIVER_ALWAYS_ON; /* turn receive on */
        break; /* process switch again */
  
      default: /* should not happen! */
        return;
    } /* switch */
  } /* for */
}

uint8_t RADIO_SetChannel(uint8_t channel) {
  RADIO_CurrChannel = channel;
  return RF1_SetChannel(channel);
}

/*! 
 * \brief Radio power-on initialization.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t RADIO_PowerUp(void) {
  RF1_Init(); /* set CE and CSN to initialization value */
  
  RF1_WriteRegister(RF1_RF_SETUP, RF1_RF_SETUP_RF_PWR_0|RNET_CONFIG_NRF24_DATA_RATE);
//  RF1_WriteRegister(RF1_RF_SETUP, RF1_RF_SETUP_RF_PWR_18|RF1_RF_SETUP_RF_DR_1000);
#if NRF24_DYNAMIC_PAYLOAD
  /* enable dynamic payload */
  RF1_WriteFeature(RF1_FEATURE_EN_DPL|RF1_FEATURE_EN_ACK_PAY|RF1_FEATURE_EN_DYN_PAY); /* set EN_DPL for dynamic payload */
  RF1_EnableDynamicPayloadLength(RF1_DYNPD_DPL_P0); /* set DYNPD register for dynamic payload for pipe0 */
#else
  RF1_SetStaticPipePayload(0, RPHY_PAYLOAD_SIZE); /* static number of payload bytes we want to send and receive */
#endif
  (void)RADIO_SetChannel(RADIO_CurrChannel);

  /* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
  RF1_WriteRegisterData(RF1_RX_ADDR_P0, (uint8_t*)RADIO_TADDR, sizeof(RADIO_TADDR));
  RF1_WriteRegisterData(RF1_TX_ADDR, (uint8_t*)RADIO_TADDR, sizeof(RADIO_TADDR));

  /* Enable RX_ADDR_P0 address matching */
  RF1_WriteRegister(RF1_EN_RXADDR, RF1_EN_RXADDR_ERX_P0); /* enable data pipe 0 */
  
  /* clear interrupt flags */
  RF1_ResetStatusIRQ(RF1_STATUS_RX_DR|RF1_STATUS_TX_DS|RF1_STATUS_MAX_RT);
  
  /* rx/tx mode */
  RF1_EnableAutoAck(RF1_EN_AA_ENAA_P0); /* enable auto acknowledge on pipe 0. RX_ADDR_P0 needs to be equal to TX_ADDR! */
  RF1_WriteRegister(RF1_SETUP_RETR, RF1_SETUP_RETR_ARD_750|RF1_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
  
  RX_POWERUP();  /* Power up in receiving mode */
  RADIO_Flush(); /* flush possible old data */
  RF1_StartRxTx(); /* Listening for packets */

  RADIO_AppStatus = RADIO_INITIAL_STATE;
  /* init Rx descriptor */
  radioRx.phyData = &radioRxBuf[0];
  radioRx.phySize = sizeof(radioRxBuf);
  radioRx.rxtx = &RPHY_BUF_SIZE(radioRx.phyData); /* we transmit the size too */
  return ERR_OK;
}

uint8_t RADIO_Process(void) {
  uint8_t res;
  
  RADIO_HandleStateMachine(); /* process state machine */
  /* process received packets */
  res = RPHY_GetPayload(&radioRx); /* get message */
  if (res==ERR_OK) { /* packet received */
    if (RADIO_isSniffing) {
      RPHY_SniffPacket(&radioRx, FALSE); /* sniff incoming packet */
    }
    if (RPHY_OnPacketRx(&radioRx)==ERR_OK) { /* process incoming packets */
#if RNET1_CREATE_EVENTS
      if (radioRx.flags&RPHY_PACKET_FLAGS_IS_ACK) { /* it was an ack! */
        RNET1_OnRadioEvent(RNET1_RADIO_ACK_RECEIVED);
      }
#endif
    }
  }
  return ERR_OK;
}


void RADIO_Deinit(void) {
  /* nothing to do */
}

void RADIO_Init(void) {
  RADIO_isSniffing = FALSE;
  RADIO_CurrChannel = RADIO_CHANNEL_DEFAULT;
}
  
