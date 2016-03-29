/*
 * Mesh.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Ben
 */

#include "Mesh.h"
#include "RHMesh.h"
#include "RH_NRF24.h"
#include "RHGenericDriver.h"
#include "wirish.h"
#include "HardwareSPI.h"
#include "RHGenericSPI.h"
#include "RHHardwareSPI.h"
#include "RHRouter.h"
#include "mesh_stastistics.h"

extern "C" {
#include "UUID.h"
//#include "MESH_SPI.h" //TODO: update drivers
#include "Clock.h"
//#include "MESH_CE.h" //TODO: update drivers
//#include "MESH_CS.h"
}

#if ENABLE_DIAGNOSTIC_LED
static color_rgb colors[] =
{
   {  LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF},        //off
   {  LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF},        //red
   {  LED_MODE_OFF, LED_MODE_MED, LED_MODE_OFF},        //green
   {  LED_MODE_OFF, LED_MODE_OFF, LED_MODE_MED}         //blue
};

#define RED_OUTPUT  (colors + 1)
#define GREEN_OUTPUT  (colors + 2)
#define BLUE_OUTPUT  (colors + 3)
#endif

//
#define DO_ROUTING_TIMEOUT_MSEC         2
//
#define MESH_RX_BUF_LEN                 0xFF
#define RH_MESH_PACKET_SIZE             22
#define MAX_MESH_NODE_COUNT             10

#define MESSAGES_AWAITING_RESPONSE_MAX  10
#define TX_RETRY_MAX                    5
#define TX_RETRY_INTERVAL_MIN_MS        20

typedef enum
{
   NODE_NOT_CONNECTED,
   NODE_CONNECTED,
   NODE_TIMED_OUT
} found_node_status;

typedef struct
{
      uint8_t address;
      uint32_t last_alive_received;
      found_node_status status;
} found_mesh_node;

typedef struct
{
      uint8_t UUID[UUID_SIZE_BYTES];
      uint8_t Message[UUID_SIZE_BYTES + 10];
      uint8_t MessageLength;bool ResponseReceived;
      uint32_t TimeSent;
      uint32_t TimeLastRetrySent;
      uint8_t RetryCount;
      uint8_t DestinationNode;bool RetriesExhausted;
} SentMessage;

///global vars 
Mesh_Command MeshCommands[MESH_CMD_MAX];

bool MeshRxEnabled;
bool MeshTxEnabled;
bool MeshMessagesAvailable;

//TODO: Temp vars, used for remote button press demo.
uint8_t ThisAddress;
uint8_t RemoteAddress;

///local vars
uint8_t rx_buf[MESH_RX_BUF_LEN];
static RHMesh * meshManager;
static RH_NRF24 * meshRadio;
static uint8_t rx_buf_size;
static uint8_t rx_buf_source;

static SentMessage MessagesAwaitingResponse[MESSAGES_AWAITING_RESPONSE_MAX];

static uint32_t time_last_alive_sent_ms;

static found_mesh_node mesh_nodes[MAX_MESH_NODE_COUNT];
static bool MeshStarted = false;
static bool MeshPaused = false;

//TODO: update drivers for SPI and mesh GPIOs
//static LDD_TEventMask SPI_EventMask;
//LDD_TDeviceData* SPI_DeviceData;
//LDD_TDeviceData* MESH_CE_DeviceData;
//LDD_TDeviceData* MESH_CS_DeviceData;

///prototypes
//static bool Find_Unused_Address_In_Routing_Table(); //TODO: unused
static void Clear_Mesh_Nodes();
static void Send_Alive_Msg();
static void Start_Mesh_Rx();
static void Stop_Mesh_Rx();
static SentMessage * Add_Message_Awaiting_Response(SentMessage * Message);
static SentMessage * Find_Message_Awaiting_Response(uint8_t * UUID);
static void Remove_Message_Awaiting_Response(uint8_t * UUID);
static void Send_Awaiting_Message(SentMessage * Message);
static SentMessage * Find_Message_To_Resend();

extern "C" {
///functions
bool Enable_Mesh() {
   return true;
}

bool Start_Mesh() {
   Mesh_Init();
   MeshStarted = true;
   MeshPaused = false;
   return true;
}

void Stop_Mesh() {
   if (MeshStarted) {
      Pause_Mesh();
      MeshStarted = false;
   }
}

void Pause_Mesh() {
   if (!MeshPaused) {
      Stop_Mesh_Rx();
//        SPI_EventMask = MESH_SPI_GetEventMask(SPI_DeviceData);
//        MESH_SPI_SetEventMask(SPI_DeviceData, 0);
      MeshPaused = true;
   }
}

void Resume_Mesh() {
   if (MeshPaused) {
//        MESH_SPI_SetEventMask(SPI_DeviceData, SPI_EventMask);
      MeshPaused = false;
   }
}

void Reset_Mesh() {
   Stop_Mesh();
   Start_Mesh();
}

//initialize the mesh objects.
void Mesh_Init() {
   //TODO: update spi and mesh gpios.
//   MESH_CE_DeviceData = MESH_CE_Init(MESH_CE_DeviceData);
//   MESH_CS_DeviceData = MESH_CS_Init(MESH_CS_DeviceData);
//   SPI_DeviceData = MESH_SPI_Init(SPI_DeviceData);

   for (int i = 0; i < MESSAGES_AWAITING_RESPONSE_MAX; ++i) {
      MessagesAwaitingResponse[i].ResponseReceived = true;
   }

   meshRadio = new RH_NRF24(MESH_CE_PIN_INDEX, MESH_SELECT_PIN_INDEX);

//enable auto-ack on all pipes.
   meshRadio->spiWriteRegister(RH_NRF24_REG_01_EN_AA, 0x3F);

   meshManager = new RHMesh(*meshRadio);

   meshManager->init();

//set address and seed RNG.
   Mesh_Discover_Nodes_And_Get_Address();

//enable hw ack.
   Mesh_Set_HW_Retry_Delay(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.retry_interval : _500uS);     //default: no retries
   Mesh_Set_HW_Retry_Count(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.max_rh_retry_count : 15);

   Mesh_Set_RH_Retry_Count(
         experiment_data.settings.max_rh_retry_count ? random(experiment_data.settings.min_rh_retry_count,
                                                              experiment_data.settings.max_rh_retry_count) :
                                                       experiment_data.settings.max_rh_retry_count);     //default: 3 retries @ 10msec

   Mesh_Set_RH_Timeout(
         experiment_data.settings.max_rh_retry_timeout_ms ? random(experiment_data.settings.min_rh_retry_timeout_ms,
                                                                   experiment_data.settings.max_rh_retry_timeout_ms) :
                                                            experiment_data.settings.max_rh_retry_timeout_ms);

   Clear_Mesh_Nodes();
   digitalWrite(MESH_CE_PIN_INDEX, 0);

   MeshRxEnabled = false;
   MeshMessagesAvailable = false;

}

extern void Mesh_Register_Callback(Mesh_Command_Index command, Mesh_Command_Callback function) {
   if (command < MESH_CMD_MAX) {
      MeshCommands[command].function = function;
   }
}

//call periodically to parse received messages and to enable the radio to receive.
void Mesh_Process_Commands(void) {
   uint8_t available_spot = MESH_MAX_NODES;

//    meshManager->printRoutingTable();

   if (Millis() - time_last_alive_sent_ms >= MESH_ALIVE_PERIOD_MS) {
      Send_Alive_Msg();
   }

   //try:expand time between resends
   //try:focus on one message until it's sent or retries exhausted.
   SentMessage *RetryMessage;
   RetryMessage = Find_Message_To_Resend();
   if (RetryMessage != NULL) {
      Send_Awaiting_Message(RetryMessage);
   }

   if (MeshMessagesAvailable) {
      MeshMessagesAvailable = false;
      ++experiment_data.alives_received[rx_buf_source > MAX_NODE_COUNT ? MAX_NODE_COUNT + 1 : rx_buf_source - 1];

#if ENABLE_DIAGNOSTIC_LED
      set_led_output(RGB_8, GREEN_OUTPUT);

      switch (rx_buf_source)
      {
         case 1:
         {
            set_led_output(RGB_1, RED_OUTPUT);
            break;
         }
         case 2:
         {
            set_led_output(RGB_1, GREEN_OUTPUT);
            break;
         }
         case 3:
         {
            set_led_output(RGB_1, BLUE_OUTPUT);
            break;
         }
      }
#endif

      if (rx_buf_size == 3 && rx_buf[0] == MESH_CMD_ADDRESS_CLAIM_MSG) {
#if ENABLE_DIAGNOSTIC_LED
         set_led_output(RGB_9, BLUE_OUTPUT);
#endif
         for (int i = 0; i < MESH_MAX_NODES; ++i) {
            if (mesh_nodes[i].address == rx_buf[1]) {
               //already found this node
               mesh_nodes[i].last_alive_received = Millis();
               mesh_nodes[i].status = NODE_CONNECTED;
            } else if (mesh_nodes[i].status
                       == NODE_CONNECTED&& mesh_nodes[i].last_alive_received > MESH_NODE_DISCONNECT_TIMEOUT_MS) {
               //haven't heard from this node for a while
               mesh_nodes[i].status = NODE_NOT_CONNECTED;
               available_spot = i;
            } else if (mesh_nodes[i].status == NODE_NOT_CONNECTED && available_spot == MESH_MAX_NODES) {
               available_spot = i;
            } else if (i == MESH_MAX_NODES - 1 && available_spot < MESH_MAX_NODES) {
               //add this node
               mesh_nodes[available_spot].address = rx_buf[1];
               mesh_nodes[available_spot].status = NODE_CONNECTED;
               mesh_nodes[available_spot].last_alive_received = Millis();
               ++experiment_data.detected_node_count;
            }
         }
      } else if (rx_buf_size == 1 + UUID_SIZE_BYTES && rx_buf[0] == MESH_CMD_ACKNOWLEDGE) {
         Remove_Message_Awaiting_Response(rx_buf + 1);
      } else if (rx_buf_size > 0) {
#if ENABLE_DIAGNOSTIC_LED
         set_led_output(RGB_9, GREEN_OUTPUT);
#endif

         ++experiment_data.messages_received[rx_buf_source > MAX_NODE_COUNT ? MAX_NODE_COUNT + 1 : rx_buf_source - 1];
         uint8_t ResponseBuf[1 + UUID_SIZE_BYTES];
         ResponseBuf[0] = MESH_CMD_ACKNOWLEDGE;

         for (int i = 0; i < UUID_SIZE_BYTES; ++i) {
            ResponseBuf[i + 1] = rx_buf[rx_buf_size - UUID_SIZE_BYTES + i];
         }

         Mesh_Tx(ResponseBuf, 1 + UUID_SIZE_BYTES, rx_buf[rx_buf_size - UUID_SIZE_BYTES - 1]);

         if (rx_buf[0] < MESH_CMD_MAX && MeshCommands[rx_buf[0]].function != NULL) {
            MeshCommands[rx_buf[0]].function(rx_buf, rx_buf_size);
         }
      }
   }
#if ENABLE_DIAGNOSTIC_LED
   else
   {
      set_led_output(RGB_8, BLUE_OUTPUT);
   }
#endif

//   bool MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);
//   uint8_t mesh_status = meshRadio->statusRead();

   if (!MeshRxEnabled) {
      Start_Mesh_Rx();
   }
}

//send message to one node. Stops the radio if it's in receive mode and starts it again once the TX is complete.
uint8_t Mesh_Tx(void * data, uint32_t dataLength, uint8_t destination) {
//store state of rx enable.
   bool rx_enable_push = MeshRxEnabled;
   MeshTxEnabled = true;
   Stop_Mesh_Rx();

   uint8_t rval = meshManager->sendtoWait((uint8_t*) data, dataLength, destination, 0);

   MeshTxEnabled = false;

//resume rx, if it was in progress
   if (rx_enable_push) {
      Start_Mesh_Rx();
   }

   return rval;
}

uint8_t Mesh_Tx_With_Retry(void * Data, uint8_t DataLength, uint8_t Destination) {
   SentMessage NewMessage;
   NewMessage.DestinationNode = Destination;
   NewMessage.MessageLength = DataLength;

   for (int i = 0; i < DataLength; ++i) {
      NewMessage.Message[i] = ((uint8_t*) Data)[i];
   }

   Send_Awaiting_Message(Add_Message_Awaiting_Response(&NewMessage));

   //TODO: return value
   return 0;
}

//send message to all nodes. Stops the radio if it's in receive mode and starts it again once the TX is complete.
uint8_t Mesh_Broadcast(void * data, uint32_t dataLength) {
   return Mesh_Tx(data, dataLength, 0xFF);
}

//calls into RH library and retrieves a message if one is available.
//note: this is used in the interrupt handler. direct call behavior is untested
uint8_t Mesh_Rx(void * data, uint8_t * dataLength, uint8_t * source) {
   return meshManager->recvfromAck((uint8_t*) data, (uint8_t*) dataLength, (uint8_t*) source);
}

//sets the radio address to an address that is available on the network.
void Mesh_Discover_Nodes_And_Get_Address() {
#if ADDRESS_1
   meshManager->setThisAddress(1);
   ThisAddress = 1;
   RemoteAddress = 2;
#elif ADDRESS_2
   meshManager->setThisAddress(2);
   ThisAddress = 2;
   RemoteAddress = 1;
#elif ADDRESS_3
   meshManager->setThisAddress(3);
#endif

#if (ADDRESS_1 || ADDRESS_2 || ADDRESS_3)
   update_random_seed(meshManager->thisAddress());
   return;
#endif
}

///returns the first node to which a route is found.
uint8_t Mesh_Get_First_Node() {
   return 0;        //not implemented
   int rval = 0;
   for (int i = 0; i < MESH_MAX_NODES; ++i) {
      if (mesh_nodes[i].status == NODE_CONNECTED) {
         rval = mesh_nodes[i].address;
         break;
      }
   }

   return rval;
}

//counts down to the highest-valued node with an address.
uint8_t Mesh_Get_Last_Node() {
   return 0;        //not implemented
   int rval = 0;
   for (int i = MESH_MAX_NODES; i >= 0; --i) {
      if (mesh_nodes[i].status == NODE_CONNECTED) {
         rval = mesh_nodes[i].address;
         break;
      }
   }

   return rval;
}

uint8_t Mesh_Get_Next_Node(uint8_t startAddr) {
   return startAddr;        //not implemented
}

uint32_t irq_handler_time;

///handles routing and message reception. messages are stored into a local buffer.
void Mesh_Irq_Handler(void) {
//   bool MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);

   ++experiment_data.rx_interrupt_count;
   irq_handler_time = Millis();

//   uint8_t MeshStatus = meshRadio->statusRead();

   MeshRxEnabled = false;
   rx_buf_size = 0xFF;        //mesh_rx will put the size it receives in here, or 0xFF if no value

   if (Mesh_Rx(rx_buf, &rx_buf_size, &rx_buf_source)) {
      Stop_Mesh_Rx();
   }

//   MeshStatus = meshRadio->statusRead();
//   MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);

   if (rx_buf_size > 0 && rx_buf_size != 0xFF)     //actual return of rx_buf_size shouldn't ever exceed 0d30. 0xFF is a default value.
                          {
      MeshMessagesAvailable = true;
   } else {
      MeshMessagesAvailable = false;
      Start_Mesh_Rx();
   }

   experiment_data.rx_interrupt_time_total_ms += Millis() - irq_handler_time;
}

//sets the retry count in radiohead. 
//returns true if set successful (which should _always_ be the case)
bool Mesh_Set_RH_Retry_Count(uint8_t retries) {
   meshManager->setRetries(retries);
   return meshManager->retries() == retries;
}

//sets the timeout in radiohead.
//returns true if set successful (which should _always_ be the case)
bool Mesh_Set_RH_Timeout(uint16_t timeout_ms) {
   meshManager->setTimeout(timeout_ms);
   return meshManager->timeout() == timeout_ms;
}

//sets the retry count on the NRF radio. set to 0 to disable.
//returns true if the set was successful.
bool Mesh_Set_HW_Retry_Count(uint8_t retransmitCount) {
   if (retransmitCount > 0xF) return false;

   meshRadio->spiWriteRegister(RH_NRF24_REG_04_SETUP_RETR, retransmitCount & RH_NRF24_ARC);
   return (meshRadio->spiReadRegister(RH_NRF24_REG_04_SETUP_RETR) & RH_NRF24_ARC);
}

//sets the retry count on the NRF radio. set to 0 to disable.
//returns true if the set was successful.
bool Mesh_Set_HW_Retry_Delay(mesh_HW_retry_interval retransmitDelay) {
   meshRadio->spiWriteRegister(RH_NRF24_REG_04_SETUP_RETR, ((uint8_t) retransmitDelay << 4) & RH_NRF24_ARD);
   return (((meshRadio->spiReadRegister(RH_NRF24_REG_04_SETUP_RETR) & RH_NRF24_ARD) >> 4) == (uint8_t) retransmitDelay);
}

void Reinit_Mesh_Retries() {
//enable hw ack.
   Mesh_Set_HW_Retry_Delay(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.retry_interval : _500uS);     //default: no retries
   Mesh_Set_HW_Retry_Count(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.max_rh_retry_count : 15);

   Mesh_Set_RH_Retry_Count(
         experiment_data.settings.max_rh_retry_count ? random(experiment_data.settings.min_rh_retry_count,
                                                              experiment_data.settings.max_rh_retry_count) :
                                                       experiment_data.settings.max_rh_retry_count);     //default: 3 retries @ 10msec

   Mesh_Set_RH_Timeout(
         experiment_data.settings.max_rh_retry_timeout_ms ? random(experiment_data.settings.min_rh_retry_timeout_ms,
                                                                   experiment_data.settings.max_rh_retry_timeout_ms) :
                                                            experiment_data.settings.max_rh_retry_timeout_ms);

   Clear_Mesh_Nodes();
}

}

//TODO: unused.
//looks for an address that hasn't been added to the routing table.
//static bool Find_Unused_Address_In_Routing_Table()
//{
//   return false;
//   bool rval = false;
//   RHRouter::RoutingTableEntry * foundRoute;
//
//   for (uint32_t i = 0; i < MESH_STARTUP_ADDRESS; ++i)
//   {
//      foundRoute = meshManager->getRouteTo(meshManager->thisAddress());
//      if (!foundRoute)
//      {
//         meshManager->setThisAddress(i);
//         update_random_seed(i);
//         rval = true;
//      }
//   }
//
//   return rval;
//}

//clears the mesh_nodes array, which contains a list of modules which have sent address broadcasts.
static void Clear_Mesh_Nodes() {
   for (int i = 0; i < MESH_MAX_NODES; ++i) {
      mesh_nodes[i].status = NODE_NOT_CONNECTED;
   }
}

//broadcast address to all nodes.
static void Send_Alive_Msg() {
   uint8_t buf[] = { MESH_CMD_ADDRESS_CLAIM_MSG, meshManager->thisAddress(), MESH_CMD_TERMINATION };
   Mesh_Tx(buf, 3, 0xFF);
   time_last_alive_sent_ms = Millis();
}

//tells the radio to start receiving data. It will listen until data is available.
static void Start_Mesh_Rx() {
   meshRadio->setModeRx();
   MeshRxEnabled = true;
#if ENABLE_DIAGNOSTIC_LED
   set_led_output(RGB_6, GREEN_OUTPUT);
#endif
}

//puts the radio back into idle mode. 
static void Stop_Mesh_Rx() {
   if (MeshRxEnabled) {
      MeshRxEnabled = false;
      meshRadio->setModeIdle();
#if ENABLE_DIAGNOSTIC_LED
      set_led_output(RGB_6, BLUE_OUTPUT);
#endif
   }
}

static SentMessage * Find_Message_To_Resend() {
   SentMessage *rval = NULL;
   for (int i = 0; i < MESSAGES_AWAITING_RESPONSE_MAX; ++i) {
      if (!MessagesAwaitingResponse[i].ResponseReceived && !MessagesAwaitingResponse[i].RetriesExhausted) {
         if (MessagesAwaitingResponse[i].TimeSent == 0||
         (Millis() - MessagesAwaitingResponse[i].TimeLastRetrySent) > TX_RETRY_INTERVAL_MIN_MS) {
            rval = MessagesAwaitingResponse + i;
         }
      }
   }

   return rval;
}

static void Send_Awaiting_Message(SentMessage * Message) {
   bool DoSend = false;
   Mesh_Tx(Message->Message, Message->MessageLength, Message->DestinationNode);
   if (Message->TimeSent == 0) {
      Message->TimeSent = Millis();
      DoSend = true;
   } else if ((Millis() - Message->TimeLastRetrySent) > TX_RETRY_INTERVAL_MIN_MS) {
      Message->TimeLastRetrySent = Millis();
      if (++(Message->RetryCount) > TX_RETRY_MAX) {
         Message->RetriesExhausted = true;
      } else {
         DoSend = true;
      }
   }

   if (DoSend) {
      Mesh_Tx(Message->Message, Message->MessageLength, Message->DestinationNode);
   }
}

static SentMessage * Add_Message_Awaiting_Response(SentMessage * NewMessage) {
   if (NewMessage == NULL) return NULL;

   char * UUID = Get_Random_UUID();
   SentMessage * EmptyMessage;
   for (int i = 0; i < MESSAGES_AWAITING_RESPONSE_MAX; ++i) {
      if (MessagesAwaitingResponse[i].ResponseReceived || MessagesAwaitingResponse[i].RetriesExhausted) {
         EmptyMessage = MessagesAwaitingResponse + i;
      }
   }

   for (int i = 0; i < UUID_SIZE_BYTES; ++i) {
      EmptyMessage->UUID[i] = UUID[i];
   }

   for (int i = 0; i < NewMessage->MessageLength; ++i) {
      EmptyMessage->Message[i] = NewMessage->Message[i];
   }

   EmptyMessage->Message[NewMessage->MessageLength] = ThisAddress;

   for (int i = 1 + NewMessage->MessageLength; i < NewMessage->MessageLength + 1 + UUID_SIZE_BYTES; ++i) {
      EmptyMessage->Message[i] = NewMessage->UUID[i];
   }

   EmptyMessage->MessageLength = NewMessage->MessageLength;
   EmptyMessage->RetryCount = 0;
   EmptyMessage->TimeLastRetrySent = 0;
   EmptyMessage->TimeSent = 0;
   EmptyMessage->DestinationNode = NewMessage->DestinationNode;
   EmptyMessage->RetriesExhausted = false;
   EmptyMessage->ResponseReceived = false;

   return EmptyMessage;
}

static SentMessage * Find_Message_Awaiting_Response(uint8_t * UUID) {
   bool FoundUuid;
   SentMessage * rval = NULL;
   for (int i = 0; i < MESSAGES_AWAITING_RESPONSE_MAX; ++i) {
      FoundUuid = true;
      for (int j = 0; j < UUID_SIZE_BYTES; ++j) {
         FoundUuid &= MessagesAwaitingResponse[i].UUID[j] == UUID[j];
      }
      if (FoundUuid) {
         rval = MessagesAwaitingResponse + i;
         break;
      }

   }

   return rval;
}

static void Remove_Message_Awaiting_Response(uint8_t *UUID) {
   SentMessage * m = Find_Message_Awaiting_Response(UUID);
   if (m != NULL) {
      m->ResponseReceived = true;
   }
}
