/*
 * app_nrf24l01.c
 *
 *  Created on: Oct 1, 2015
 *      Author: Ben
 */

// includes //////////////////
#include "app_nrf24l01.h"

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

// defines ///////////////////
#define RF_TIMEOUT_MS               30
#define MAX_TX_RETRIES_PER_MESSAGE  5

// structs ///////////////////
typedef enum
{
    JOIN_NETWORK,
    ACTIVE_RECEIVING,
    IDLE_RECEIVING,
    RX_DATA_READY,
    TX_MESSAGE_PENDING,
    TRANSMITTING
} mesh_state;

// global vars ///////////////
clay_mesh_module clayModules[MESH_MODULE_MAX_COUNT];

// local vars ////////////////
static mesh_message pendingTxMessages[TX_MESSAGE_BUFFER_LENGTH];
static mesh_message * currentMessage;
static uint32_t pendingTxHead;
static uint32_t pendingTxTail;
static uint32_t pendingTxCount;
static uint32_t packetCounter;

static uint8_t meshTxDataBuf[40];
static uint8_t mesh_rx_buf[128];

static volatile uint8_t isr_flag;
static volatile uint8_t txInProgress;

static volatile uint8_t status_reg;
static volatile uint32_t tx_time_ms;

static volatile uint8_t rxInProgress;
static volatile uint32_t rx_start_time_ms;
static volatile uint8_t rx_data_ready;
static volatile uint32_t rxDataCount;

static volatile mesh_state state;

// prototypes ////////////////
static void setTxDestinationAddress(uint32_t destination);
static void meshListen();
static void resetTxBuffer();
static void sendMessage(mesh_message * txMsg);
static void stateMachineTick();

// implementations ///////////

void meshInit()
{
    RF1_Init();

    RF1_WriteRegister(RF1_CONFIG, 0);        //power down
    delay_n_ms(4);

    RF1_WriteRegister(RF1_RX_PW_P0, MESH_PACKET_SIZE);        //set payload size

    RF1_WriteRegister(RF1_RF_CH, MESH_CHANNEL_NUMBER);                           // set channel

    RF1_WriteRegister(RF1_SETUP_AW, MESH_RADIO_ADDRESS_WIDTH);          //set address width

    meshTxDataBuf[0] = (MESH_RADIO_ADDRESS_GLOBAL & 0xFF);
    meshTxDataBuf[1] = ((MESH_RADIO_ADDRESS_GLOBAL >> 8) & 0xFF);
    meshTxDataBuf[2] = ((MESH_RADIO_ADDRESS_GLOBAL >> 16) & 0xFF);
    meshTxDataBuf[3] = ((MESH_RADIO_ADDRESS_GLOBAL >> 24) & 0xFF);
    meshTxDataBuf[4] = 0x00;
    RF1_WriteRegisterData(RF1_RX_ADDR_P0, meshTxDataBuf, 5);              //set global address as pipe 0
    RF1_WriteRegisterData(RF1_TX_ADDR, meshTxDataBuf, 5);                 //set global address as tx destination

    RF1_WriteRegister(RF1_EN_RXADDR, RF1_EN_RXADDR_ERX_P0);            //enable pipe 0

    //enter rx mode, this is the typical idle state for the device
    RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_RECEIVE_CONFIG);
    RF1_WriteRegister(RF1_EN_AA, RF1_EN_AA_ENAA_P0);
    //set up .75ms retry delay, 15 retries
    RF1_WriteRegister(RF1_SETUP_RETR, RF1_SETUP_RETR_ARD_750 | RF1_SETUP_RETR_ARC_15);

    //enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR
    RF1_WriteRegister(RF1_EN_AA, RF1_EN_AA_ENAA_P0);

    RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_TRANSMIT_CONFIG);

    RF1_WriteFeature(RF1_FEATURE_EN_DPL);
    RF1_WriteRegister(RF1_DYNPD, 0x3F);        //set dynamic packet length on all pipes

    state = ACTIVE_RECEIVING;
    resetTxBuffer();
}

//
//state machine. Consumes ISR flag and then runs state machine.
void meshStateUpdate()
{
    uint8_t readbytes = RF1_ReadRegister(RF1_RX_PW_P0);
    status_reg = RF1_GetStatus();

    if (isr_flag)
    { /* check if we have received an interrupt */
        isr_flag = FALSE; /* reset interrupt flag */
        if (status_reg & RF1_STATUS_RX_DR)
        { /* data received interrupt */
            RF1_ResetStatusIRQ(RF1_STATUS_RX_DR | RF1_STATUS_TX_DS | RF1_STATUS_MAX_RT);
            if (readbytes > 0)
            {
                RF1_RxPayload(mesh_rx_buf, readbytes);
                rxDataCount = readbytes;
                rx_data_ready = TRUE;
                state = RX_DATA_READY;
            }
        }
        if (status_reg & RF1_STATUS_TX_DS)
        { /* data sent interrupt */
            RF1_ResetStatusIRQ(RF1_STATUS_TX_DS); /* clear bit */

            if (pendingTxCount > 0 || (currentMessage != NULL && !(currentMessage->transmissionComplete)))
            {
                state = TX_MESSAGE_PENDING;

                if (currentMessage->onMessageComplete != NULL)
                {
                    currentMessage->onMessageComplete(OK);
                }
            }
            else
            {
                if (currentMessage != NULL && currentMessage->onMessageComplete != NULL)
                {
                    currentMessage->onMessageComplete(EXCEEDED_MAX_RETRY);
                }
//                state = IDLE_RECEIVING;
                state = ACTIVE_RECEIVING;
            }

            txInProgress = FALSE;
            tx_time_ms = 0; /* reset timeout counter */
        }
        if (status_reg & RF1_STATUS_MAX_RT)
        { /* retry timeout interrupt */
            RF1_ResetStatusIRQ(RF1_STATUS_MAX_RT); /* clear bit */

            //send back to RX mode. Could retry here.
            if (pendingTxCount > 0 && (currentMessage->retryCount < MAX_TX_RETRIES_PER_MESSAGE))
            {
                state = TX_MESSAGE_PENDING;
                if (currentMessage != NULL)
                {
                    currentMessage->transmissionComplete = FALSE;
                    if (currentMessage->lastPacket > 0)
                    {
                        --(currentMessage->lastPacket);
                    }

                    if (++(currentMessage->retryCount) > MAX_TX_RETRIES_PER_MESSAGE && currentMessage->onMessageComplete != NULL)
                    {
                        currentMessage->onMessageComplete(EXCEEDED_MAX_RETRY);
                    }
                }
            }
            else
            {
//                state = IDLE_RECEIVING;
                state = ACTIVE_RECEIVING;
            }

            txInProgress = FALSE;
            tx_time_ms = 0;
        }
    }

    stateMachineTick();

}

//
//sends the data in tx_buf. length should be less than 32 bytes for now.
bool meshSend(uint8_t * tx_buf, uint32_t length, uint32_t destinationAddress, messageCompleteCallback messageComplete)
{
    if ((pendingTxCount < TX_MESSAGE_BUFFER_LENGTH && !txInProgress) || (pendingTxCount < (TX_MESSAGE_BUFFER_LENGTH - 1)))
    {
        pendingTxMessages[pendingTxTail].data = tx_buf;
        pendingTxMessages[pendingTxTail].destination = destinationAddress;
        pendingTxMessages[pendingTxTail].length = length;
        pendingTxMessages[pendingTxTail].lastPacket = 0;
        pendingTxMessages[pendingTxTail].transmissionComplete = FALSE;
        pendingTxMessages[pendingTxTail].messageId = packetCounter++;
        pendingTxMessages[pendingTxTail].onMessageComplete = messageComplete;

        pendingTxTail = (pendingTxTail + 1) % TX_MESSAGE_BUFFER_LENGTH;
        ++pendingTxCount;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//
//Transmits using global address.
bool meshBroadcast(uint8_t * txBuf, uint32_t length, messageCompleteCallback messageComplete)
{
    return meshSend(txBuf, length, MESH_RADIO_ADDRESS_GLOBAL, messageComplete);
}

//
//returns number of bytes actually retrieved into rx_buf.
int meshReceiveString(uint8_t * rxBuf, uint32_t length)
{
    int rval = -1;

    if (rx_data_ready)
    {
        rval = (rxDataCount > length ? length : rxDataCount);
        rx_data_ready = FALSE;

        if (state == RX_DATA_READY)
        {
            state = IDLE_RECEIVING;
        }

        for (int i = 0; i < rval; ++i)
        {
            rxBuf[i] = mesh_rx_buf[i];
        }
    }

    return rval;
}

//
//Clears the CE flag so that the radio stops transmitting or receiving, sets the ISR flag, which is consumed in the State Update function.
extern void meshInterruptHandler()
{
    CE1_ClrVal();
    isr_flag = TRUE;
    txInProgress = FALSE;
    rxInProgress = FALSE;
}

//
//Sets the transmit destination in both the TX register and the pipe 0 RX
static void setTxDestinationAddress(uint32_t destination)
{
    meshTxDataBuf[0] = (destination & 0xFF);
    meshTxDataBuf[1] = ((destination >> 8) & 0xFF);
    meshTxDataBuf[2] = ((destination >> 16) & 0xFF);
    meshTxDataBuf[3] = ((destination >> 24) & 0xFF);
    RF1_WriteRegisterData(RF1_TX_ADDR, meshTxDataBuf, 4);              //set global address as pipe 0
    RF1_WriteRegisterData(RF1_RX_ADDR_P0, meshTxDataBuf, 5);              //set global address as pipe 
}

//
//Enable the RX function of the mesh radio and set the CE line high so that it starts listening
static void meshListen()
{
    RF1_ResetStatusIRQ(RF1_STATUS_RX_DR | RF1_STATUS_TX_DS | RF1_STATUS_MAX_RT);
    RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_RECEIVE_CONFIG);
    RF1_StartRxTx();
}

static void resetTxBuffer()
{
    pendingTxHead = 0;
    pendingTxTail = 0;
    pendingTxCount = 0;
}

//
//takes a mesh_message struct and sends it out in MESH_PACKET_SIZE chunks.
static void sendMessage(mesh_message * txMsg)
{
    if (txMsg == NULL) return;

    setTxDestinationAddress(txMsg->destination);
    if ((txMsg->length) > MESH_PACKET_SIZE)
    {
        if ((txMsg->length) - (MESH_PACKET_SIZE * (txMsg->lastPacket)) > 0)
        {
            RF1_TxPayload((txMsg->data) + (MESH_PACKET_SIZE * (txMsg->lastPacket)++), MESH_PACKET_SIZE);
        }
        else
        {
            RF1_TxPayload(txMsg->data + (MESH_PACKET_SIZE * (txMsg->lastPacket)),
                    (txMsg->length) - (MESH_PACKET_SIZE * (txMsg->lastPacket)++));
            txMsg->transmissionComplete = TRUE;
        }
    }
    else
    {
        RF1_TxPayload(txMsg->data, txMsg->length);
        txMsg->transmissionComplete = TRUE;
    }
}

//
//call periodically to run the internal communication state machine.
static void stateMachineTick()
{
    //state descriptions:
    //  JOIN_NETWORK
    //   tbd 
    //  ACTIVE_RECEIVING
    //   Set RX mode if not enabled.
    //   State is not allowed to change for some time
    //  IDLE_RECEIVING
    //   Allow to rest in IDLE_RECEIVING, RX mode enabled
    //   return to ACTIVE_RECEIVING after timeout to reset the RX.
    //  RX_DATA_READY
    //   do nothing. state can be changed.
    //  TX_MESSAGE_PENDING
    //   Initiates transmission of waiting data.
    //   State updated to TRANSMITTING
    //  TRANSMITTING
    //   State not allowed to change until TX is complete
    //   implements timeout. CE will be set low after timeout.
    switch (state)
    {
        case JOIN_NETWORK:
            {

            //request address claim on global
            //wait for address claims
            //add nodes as they come in

            break;
        }
        case ACTIVE_RECEIVING:
            {
            if (!rxInProgress)
            {
                meshListen();
                rxInProgress = TRUE;
                rx_start_time_ms = power_on_time_msec;
            }

            if ((power_on_time_msec - rx_start_time_ms) > (RF_TIMEOUT_MS * 5))
            {
                state = (pendingTxCount > 0 ? TX_MESSAGE_PENDING : IDLE_RECEIVING);
            }
            break;
        }
        case IDLE_RECEIVING:
            {

            if (RF1_ReadRegister(RF1_RPD) == 0)
            {
                state = (pendingTxCount > 0 ? TX_MESSAGE_PENDING : IDLE_RECEIVING);
            }
//            if ((power_on_time_msec - rx_start_time_ms) > (RF_TIMEOUT_MS * 10))
//            {
//                rxInProgress = FALSE;
//                state = ACTIVE_RECEIVING;
//            }
            break;
        }
        case RX_DATA_READY:
            {
            break;
        }
        case TX_MESSAGE_PENDING:
            {
            rxInProgress = FALSE;

            //TODO: come up with way to do spectrum sharing. round robin seems like maybe an OK way to do it
            //      Try:
            //          --watch CD to see if the channel is busy
            //          --if the channel is busy, wait x ms before retrying
            //          --decrease wait time gradually?

            //TODO: this is where we basically ignore the 'jamming' detection. may need review later.
            //      see nrf spec version 2.0, appendix E
            if (RF1_ReadRegister(8) >= 0x70)
            {
                //dummy write to channel, in case we have had many lost packets.
                RF1_WriteRegister(RF1_RF_CH, MESH_CHANNEL_NUMBER);                           // set channel
            }

//            if (RF1_ReadRegister(RF1_RPD) == 0)
//            {
            RF1_ResetStatusIRQ(RF1_STATUS_RX_DR | RF1_STATUS_TX_DS | RF1_STATUS_MAX_RT);

            RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_TRANSMIT_CONFIG);

            delay_n_ms(3);

            if (currentMessage == NULL || currentMessage->transmissionComplete)
            {
                currentMessage = pendingTxMessages + pendingTxHead++;
                pendingTxHead = (pendingTxHead + 1) % TX_MESSAGE_BUFFER_LENGTH;
                --pendingTxCount;
                txInProgress = TRUE;
                sendMessage(currentMessage);
            }
            else
            {
                txInProgress = TRUE;
                sendMessage(currentMessage);
            }

            state = TRANSMITTING;
//            }
//            else
//            {
//                state = ACTIVE_RECEIVING;
//            }
            break;
        }
        case TRANSMITTING:
            {
            rxInProgress = FALSE;

            if (power_on_time_msec - tx_time_ms > RF_TIMEOUT_MS)
            {
                state = ACTIVE_RECEIVING;
                ++(currentMessage->retryCount);
            }

            break;
        }
        default:
            {
            break;
        }
    }
}
