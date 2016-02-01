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

extern "C"
{
#include "MESH_SPI.h"
#include "Clock.h"
}

#if ENABLE_DIAGNOSTIC_LED
static color_rgb colors[] =
{
	{	LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF},        //off
	{	LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF},        //red
	{	LED_MODE_OFF, LED_MODE_MED, LED_MODE_OFF},        //green
	{	LED_MODE_OFF, LED_MODE_OFF, LED_MODE_MED}         //blue
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

typedef enum
{
	NODE_NOT_CONNECTED, NODE_CONNECTED, NODE_TIMED_OUT
} found_node_status;

typedef struct
{
	uint8_t address;
	uint32_t last_alive_received;
	found_node_status status;
} found_mesh_node;

///global vars 
mesh_command commands[MESH_CMD_MAX];

bool mesh_rx_enabled;
bool mesh_messages_available;

///local vars
uint8_t rx_buf[MESH_RX_BUF_LEN];
static RHMesh * meshManager;
static RH_NRF24 * meshRadio;
static uint8_t rx_buf_size;
static uint8_t rx_buf_source;

static uint32_t time_last_alive_sent_ms;

static found_mesh_node mesh_nodes[MAX_MESH_NODE_COUNT];
static bool MeshStarted = FALSE;
static bool MeshPaused = FALSE;
static LDD_TEventMask SPI_EventMask;
LDD_TDeviceData* SPI_DeviceData;
LDD_TDeviceData* MESH_CE_DeviceData;
LDD_TDeviceData* MESH_CS_DeviceData;
LDD_TDeviceData* MESH_IRQ_DeviceData;

///prototypes
static bool findUnusedAddressInRoutingTable();
static void clear_mesh_nodes();
static void send_alive_msg();
static void start_mesh_rx();
static void stop_mesh_rx();

extern "C"
{
///functions
bool Enable_Mesh()
{
	return TRUE;
}

bool Start_Mesh()
{
	mesh_init();
	MeshStarted = TRUE;
	MeshPaused = FALSE;
	return TRUE;
}

void Stop_Mesh()
{
	if (MeshStarted)
	{
		Pause_Mesh();
		MeshStarted = FALSE;
	}
}

void Pause_Mesh()
{
	if (!MeshPaused)
	{
		stop_mesh_rx();
//        SPI_EventMask = MESH_SPI_GetEventMask(SPI_DeviceData);
//        MESH_SPI_SetEventMask(SPI_DeviceData, 0);
		MeshPaused = TRUE;
	}
}

void Resume_Mesh()
{
	if (MeshPaused)
	{
//        MESH_SPI_SetEventMask(SPI_DeviceData, SPI_EventMask);
		MeshPaused = FALSE;
	}
}

void Reset_Mesh()
{
	Stop_Mesh();
	Start_Mesh();
}

//initialize the mesh objects.
void mesh_init()
{
//    MESH_CE_DeviceData = MESH_CE_Init(MESH_CE_DeviceData);
//    MESH_IRQ_DeviceData = MESH_IRQ_Init(MESH_IRQ_DeviceData);
//    MESH_CS_DeviceData = MESH_CS_Init(MESH_CS_DeviceData);
	SPI_DeviceData = MESH_SPI_Init(SPI_DeviceData);

	meshRadio = new RH_NRF24(MESH_CE_PIN_INDEX, MESH_SELECT_PIN_INDEX);

//enable auto-ack on all pipes.
	meshRadio->spiWriteRegister(RH_NRF24_REG_01_EN_AA, 0x3F);

	meshManager = new RHMesh(*meshRadio);

	meshManager->init();

//set address and seed RNG.
	mesh_discover_nodes_and_get_address();

//enable hw ack.
	set_hw_retry_delay(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.retry_interval : _500uS);        //default: no retries
	set_hw_retry_count(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.max_rh_retry_count : 15);

	set_RH_retry_count(experiment_data.settings.max_rh_retry_count ? random(experiment_data.settings.min_rh_retry_count, experiment_data.settings.max_rh_retry_count) : experiment_data.settings.max_rh_retry_count);        //default: 3 retries @ 10msec

	set_RH_timeout(experiment_data.settings.max_rh_retry_timeout_ms ? random(experiment_data.settings.min_rh_retry_timeout_ms, experiment_data.settings.max_rh_retry_timeout_ms) : experiment_data.settings.max_rh_retry_timeout_ms);

	clear_mesh_nodes();
	digitalWrite(MESH_CE_PIN_INDEX, 0);

	mesh_rx_enabled = FALSE;
	mesh_messages_available = FALSE;

}

extern void mesh_register_callback(MeshCommandIndex command, cmd_func function)
{
	if (command < MESH_CMD_MAX)
	{
		commands[command].function = function;
	}
}

//call periodically to parse received messages and to enable the radio to receive.
void mesh_process_commands(void)
{
	uint8_t available_spot = MESH_MAX_NODES;

//    meshManager->printRoutingTable();

	if (Millis() - time_last_alive_sent_ms >= MESH_ALIVE_PERIOD_MS)
	{
		send_alive_msg();
	}

	if (mesh_messages_available)
	{
		mesh_messages_available = FALSE;
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

		if (rx_buf_size == 3 && rx_buf[0] == MESH_CMD_ADDRESS_CLAIM_MSG)
		{
#if ENABLE_DIAGNOSTIC_LED
			set_led_output(RGB_9, BLUE_OUTPUT);
#endif
			for (int i = 0; i < MESH_MAX_NODES; ++i)
			{
				if (mesh_nodes[i].address == rx_buf[1])
				{
					//already found this node
					mesh_nodes[i].last_alive_received = Millis();
					mesh_nodes[i].status = NODE_CONNECTED;
				}
				else if (mesh_nodes[i].status == NODE_CONNECTED && mesh_nodes[i].last_alive_received > MESH_NODE_DISCONNECT_TIMEOUT_MS)
				{
					//haven't heard from this node for a while
					mesh_nodes[i].status = NODE_NOT_CONNECTED;
					available_spot = i;
				}
				else if (mesh_nodes[i].status == NODE_NOT_CONNECTED && available_spot == MESH_MAX_NODES)
				{
					available_spot = i;
				}
				else if (i == MESH_MAX_NODES - 1 && available_spot < MESH_MAX_NODES)
				{
					//add this node
					mesh_nodes[available_spot].address = rx_buf[1];
					mesh_nodes[available_spot].status = NODE_CONNECTED;
					mesh_nodes[available_spot].last_alive_received = Millis();
					++experiment_data.detected_node_count;
				}
			}
		}
		else if (rx_buf_size > 0)
		{
#if ENABLE_DIAGNOSTIC_LED
			set_led_output(RGB_9, GREEN_OUTPUT);
#endif

			++experiment_data.messages_received[rx_buf_source > MAX_NODE_COUNT ? MAX_NODE_COUNT + 1 : rx_buf_source - 1];
			if (rx_buf[0] < MESH_CMD_MAX && commands[rx_buf[0]].function != NULL)
			{
				commands[rx_buf[0]].function(rx_buf, rx_buf_size);
			}

		}
	}
#if ENABLE_DIAGNOSTIC_LED
	else
	{
		set_led_output(RGB_8, BLUE_OUTPUT);
	}
#endif

	bool MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);
	uint8_t mesh_status = meshRadio->statusRead();

	if (!mesh_rx_enabled)
	{
		start_mesh_rx();
	}
}

//send message to one node. Stops the radio if it's in receive mode and starts it again once the TX is complete.
uint8_t mesh_tx(void * data, uint32_t dataLength, uint8_t destination)
{
//store state of rx enable.
	bool rx_enable_push = mesh_rx_enabled;
	stop_mesh_rx();

	uint8_t rval = meshManager->sendtoWait((uint8_t*) data, dataLength, destination, 0);

//resume rx, if it was in progress
	if (rx_enable_push)
	{
		start_mesh_rx();
	}

	return rval;
}

//send message to all nodes. Stops the radio if it's in receive mode and starts it again once the TX is complete.
uint8_t mesh_broadcast(void * data, uint32_t dataLength)
{
	return mesh_tx(data, dataLength, 0xFF);
}

//calls into RH library and retrieves a message if one is available.
//note: this is used in the interrupt handler. direct call behavior is untested
uint8_t mesh_rx(void * data, uint8_t * dataLength, uint8_t * source)
{
	return meshManager->recvfromAck((uint8_t*) data, (uint8_t*) dataLength, (uint8_t*) source);
}

//sets the radio address to an address that is available on the network.
void mesh_discover_nodes_and_get_address()
{
#if ADDRESS_1
	meshManager->setThisAddress(1);
#elif ADDRESS_2
	meshManager->setThisAddress(2);
#elif ADDRESS_3
	meshManager->setThisAddress(3);
#endif

#if (ADDRESS_1 || ADDRESS_2 || ADDRESS_3)
	update_random_seed(meshManager->thisAddress());
	return;
#endif

//    update_random_seed(millis());
//    uint8_t randomAddress = random(0, MESH_STARTUP_ADDRESS);
//    RHRouter
//    ::RoutingTableEntry * foundRoute;
//
//    meshManager->setThisAddress(randomAddress);
//    meshManager->sendtoWait(&randomAddress, 1, meshManager->thisAddress(), 0);
//
//    foundRoute = meshManager->getRouteTo(meshManager->thisAddress());
//
//    if (foundRoute)
//    {
//        findUnusedAddressInRoutingTable();
//    }
}

///returns the first node to which a route is found.
uint8_t get_first_node()
{
	return 0;        //not implemented
	int rval = 0;
	for (int i = 0; i < MESH_MAX_NODES; ++i)
	{
		if (mesh_nodes[i].status == NODE_CONNECTED)
		{
			rval = mesh_nodes[i].address;
			break;
		}
	}

	return rval;

//    RHRouter
//    ::RoutingTableEntry * foundRoute;
//    uint8_t rval = MESH_RESERVED_ADDRESS;        //invalid address.
//
//    for (uint32_t i = 0; i < MESH_RESERVED_ADDRESS; ++i)
//    {
//        if (i == meshManager->thisAddress())
//        {
//            continue;
//        }
//        foundRoute = meshManager->getRouteTo(i);
//        if (foundRoute)
//        {
//            rval = i;
//            break;
//        }
//    }
//
//    return rval;
}

//counts down to the highest-valued node with an address.
uint8_t get_last_node()
{
	return 0;        //not implemented
	int rval = 0;
	for (int i = MESH_MAX_NODES; i >= 0; --i)
	{
		if (mesh_nodes[i].status == NODE_CONNECTED)
		{
			rval = mesh_nodes[i].address;
			break;
		}
	}

	return rval;

//    RHRouter
//    ::RoutingTableEntry * foundRoute;
//    uint8_t rval = MESH_RESERVED_ADDRESS;        //invalid address.
//
//    for (int32_t i = MESH_RESERVED_ADDRESS; i >= 0; --i)
//    {
//        if (i == meshManager->thisAddress())
//        {
//            continue;
//        }
//        foundRoute = meshManager->getRouteTo(i);
//        if (foundRoute)
//        {
//            rval = i;
//            break;
//        }
//    }

//    return rval;
}

uint8_t get_next_node(uint8_t startAddr)
{
	return startAddr;        //not implemented
//    RHRouter
//    ::RoutingTableEntry * foundRoute;
//    uint8_t rval = MESH_STARTUP_ADDRESS;        //invalid address.
////    uint8_t rval = 0xFF;        //invalid address.
//
//    if (startAddr >= MESH_STARTUP_ADDRESS)
//    {
//        startAddr = meshManager->thisAddress();
//    }
//
//    for (uint32_t i = startAddr + 1; i < MESH_STARTUP_ADDRESS; ++i)
//    //    for (uint32_t i = startAddr + 1; i < 0xFE; ++i)
//    {
//        foundRoute = meshManager->getRouteTo(i);
//        if (foundRoute)
//        {
//            rval = i;
//            break;
//        }
//    }
//
////    if (rval == 0xFF)
//    if (rval == MESH_STARTUP_ADDRESS)
//    {
//        for (uint32_t i = 0; i < startAddr; ++i)
//        {
//            foundRoute = meshManager->getRouteTo(i);
//            if (foundRoute)
//            {
//                rval = i;
//                break;
//            }
//        }
//    }
//
//    meshManager->printRoutingTable();
//
//    return rval;
}

uint32_t irq_handler_time;

///handles routing and message reception. messages are stored into a local buffer.
void mesh_irq_handler(void)
{
	bool MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);

	++experiment_data.rx_interrupt_count;
	irq_handler_time = Millis();

	uint8_t MeshStatus = meshRadio->statusRead();

	mesh_rx_enabled = FALSE;
	rx_buf_size = 0xFF;        //mesh_rx will put the size it receives in here, or 0xFF if no value

	if (mesh_rx(rx_buf, &rx_buf_size, &rx_buf_source))
	{
		stop_mesh_rx();
	}

	MeshStatus = meshRadio->statusRead();
	MeshIrqStatus = digitalRead(MESH_IRQ_PIN_INDEX);

	if (rx_buf_size > 0 && rx_buf_size != 0xFF)        //actual return of rx_buf_size shouldn't ever exceed 0d30. 0xFF is a default value.
	{
		mesh_messages_available = TRUE;
	}
	else
	{
		mesh_messages_available = FALSE;
		start_mesh_rx();
	}

	experiment_data.rx_interrupt_time_total_ms += Millis() - irq_handler_time;
}

//sets the retry count in radiohead. 
//returns TRUE if set successful (which should _always_ be the case)
bool set_RH_retry_count(uint8_t retries)
{
	meshManager->setRetries(retries);
	return meshManager->retries() == retries;
}

//sets the timeout in radiohead.
//returns TRUE if set successful (which should _always_ be the case)
bool set_RH_timeout(uint16_t timeout_ms)
{
	meshManager->setTimeout(timeout_ms);
	return meshManager->timeout() == timeout_ms;
}

//sets the retry count on the NRF radio. set to 0 to disable.
//returns TRUE if the set was successful.
bool set_hw_retry_count(uint8_t retransmitCount)
{
	if (retransmitCount > 0xF)
		return FALSE;

	meshRadio->spiWriteRegister(RH_NRF24_REG_04_SETUP_RETR, retransmitCount & RH_NRF24_ARC);
	return (meshRadio->spiReadRegister(RH_NRF24_REG_04_SETUP_RETR) & RH_NRF24_ARC);
}

//sets the retry count on the NRF radio. set to 0 to disable.
//returns TRUE if the set was successful.
bool set_hw_retry_delay(mesh_HW_retry_interval retransmitDelay)
{
	meshRadio->spiWriteRegister(RH_NRF24_REG_04_SETUP_RETR, ((uint8_t) retransmitDelay << 4) & RH_NRF24_ARD);
	return (((meshRadio->spiReadRegister(RH_NRF24_REG_04_SETUP_RETR) & RH_NRF24_ARD) >> 4) == (uint8_t) retransmitDelay);
}

void re_init_mesh_retries()
{
//enable hw ack.
	set_hw_retry_delay(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.retry_interval : _500uS);        //default: no retries
	set_hw_retry_count(experiment_data.settings.randomize_hw_retry_count ? experiment_data.settings.max_rh_retry_count : 15);

	set_RH_retry_count(experiment_data.settings.max_rh_retry_count ? random(experiment_data.settings.min_rh_retry_count, experiment_data.settings.max_rh_retry_count) : experiment_data.settings.max_rh_retry_count);        //default: 3 retries @ 10msec

	set_RH_timeout(experiment_data.settings.max_rh_retry_timeout_ms ? random(experiment_data.settings.min_rh_retry_timeout_ms, experiment_data.settings.max_rh_retry_timeout_ms) : experiment_data.settings.max_rh_retry_timeout_ms);

	clear_mesh_nodes();
}

}

//looks for an address that hasn't been added to the routing table.
static bool findUnusedAddressInRoutingTable()
{
	return FALSE;
	bool rval = FALSE;
	RHRouter::RoutingTableEntry * foundRoute;

	for (uint32_t i = 0; i < MESH_STARTUP_ADDRESS; ++i)
	{
		foundRoute = meshManager->getRouteTo(meshManager->thisAddress());
		if (!foundRoute)
		{
			meshManager->setThisAddress(i);
			update_random_seed(i);
			rval = TRUE;
		}
	}

	return rval;
}

//clears the mesh_nodes array, which contains a list of modules which have sent address broadcasts.
static void clear_mesh_nodes()
{
	for (int i = 0; i < MESH_MAX_NODES; ++i)
	{
		mesh_nodes[i].status = NODE_NOT_CONNECTED;
	}
}

//broadcast address to all nodes.
static void send_alive_msg()
{
	uint8_t buf[] =
	{ MESH_CMD_ADDRESS_CLAIM_MSG, meshManager->thisAddress(), MESH_CMD_TERMINATION };
	mesh_tx(buf, 3, 0xFF);
	time_last_alive_sent_ms = Millis();
}

//tells the radio to start receiving data. It will listen until data is available.
static void start_mesh_rx()
{
	meshRadio->setModeRx();
	mesh_rx_enabled = TRUE;
#if ENABLE_DIAGNOSTIC_LED
	set_led_output(RGB_6, GREEN_OUTPUT);
#endif
}

//puts the radio back into idle mode. 
static void stop_mesh_rx()
{
	if (mesh_rx_enabled)
	{
		mesh_rx_enabled = FALSE;
		meshRadio->setModeIdle();
#if ENABLE_DIAGNOSTIC_LED
		set_led_output(RGB_6, BLUE_OUTPUT);
#endif
	}
}
