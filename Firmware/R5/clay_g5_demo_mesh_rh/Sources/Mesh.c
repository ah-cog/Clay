/*
 * Mesh.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Ben
 */

#include "Mesh.h"

#ifndef RHMesh_h
#include "../RadioHead/RHMesh.h"
#endif

#ifndef RH_NRF24_h
#include "../RadioHead/RH_NRF24.h"
#endif

#ifndef RHGenericDriver_h
#include "../RadioHead/RHGenericDriver.h"
#endif

#ifndef _wirish_h
#include "../RadioHead/wirish.h"
#endif

#ifndef _HardwareSPI_h
#include "../RadioHead/HardwareSPI.h"
#endif

#ifndef RHGenericSPI_h
#include "../RadioHead/RHGenericSPI.h"
#endif

#ifndef RHHardwareSPI_h
#include "../RadioHead/RHHardwareSPI.h"
#endif

#ifndef RHRouter_h
#include "../RadioHead/RHRouter.h"
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef LED_DRIVER_PCA9552_H_
#include "led_driver_pca9552.h"
#endif

static color_rgb colors[] = { { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF },        //off
        { LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF },        //red
        { LED_MODE_OFF, LED_MODE_MED, LED_MODE_OFF },        //green
        { LED_MODE_OFF, LED_MODE_OFF, LED_MODE_MED }         //blue
};

#define RED_OUTPUT  (colors + 1)
#define GREEN_OUTPUT  (colors + 2)
#define BLUE_OUTPUT  (colors + 3)

#define MESH_ALIVE_PERIOD_MS            1000
#define MESH_NODE_DISCONNECT_TIMEOUT_MS (3 * MESH_ALIVE_PERIOD_MS)
//
#define DO_ROUTING_TIMEOUT_MSEC         2
//
#define MESH_RX_BUF_LEN                 0xFF
#define RH_MESH_PACKET_SIZE             22
#define MAX_MESH_NODE_COUNT             10

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

///global vars 
mesh_command commands[] =
        {
                { MESH_CMD_CHANGE_MESH_MODE, 0 },        //change mesh mode: transmit/receive, transmit only, receive only
                { MESH_CMD_UPDATE_IMU_DATA, 0 }         //update IMU LED data.
        };
uint32_t command_count = sizeof(commands) / sizeof(mesh_command);

static found_mesh_node mesh_nodes[MAX_MESH_NODE_COUNT];

///local vars
uint8_t rx_buf[MESH_RX_BUF_LEN];
static RHMesh * meshManager;
static RH_NRF24 * meshRadio;
static uint32_t rx_buf_size;
static uint8_t rx_buf_source;

static uint8_t do_routing_data;
static uint8_t do_routing_length;
static uint32_t time_last_alive_sent_ms;

///prototypes
static bool findUnusedAddressInRoutingTable();
static void clear_mesh_nodes();
static void send_alive_msg();

///functions
void mesh_init(cmd_func changeMeshModeCallback, cmd_func updateImuLedsCallback)
{
    commands[0].function = changeMeshModeCallback;
    commands[1].function = updateImuLedsCallback;

    meshRadio = new
    RH_NRF24(MESH_CE_PIN_INDEX, MESH_SELECT_PIN_INDEX);
    meshManager = new
    RHMesh(*meshRadio);

    meshManager->init();
    meshManager->setRetries(3);
    meshManager->setTimeout(10);
    mesh_discover_nodes_and_get_address();

    clear_mesh_nodes();
}

void mesh_process_commands(void)
{
    uint8_t size;
    uint8_t source;
    uint8_t available_spot = MESH_MAX_NODES;

    meshManager->printRoutingTable();

    if (power_on_time_msec - time_last_alive_sent_ms >= MESH_ALIVE_PERIOD_MS)
    {
        send_alive_msg();
    }

    if (mesh_rx(rx_buf, &size, &source))
    {
        switch (source)
        {
            case 1:
                {
                set_led_output(RGB_1, GREEN_OUTPUT);
                break;
            }
            case 2:
                {
                set_led_output(RGB_1, BLUE_OUTPUT);
                break;
            }
            case 3:
                {
                set_led_output(RGB_1, RED_OUTPUT);
                break;
            }
        }
        set_led_output(RGB_8, GREEN_OUTPUT);

        if (size == 3 && rx_buf[0] == MESH_CMD_ADDRESS_CLAIM_MSG)
        {
            set_led_output(RGB_9, BLUE_OUTPUT);
            for (int i = 0; i < MESH_MAX_NODES; ++i)
            {
                if (mesh_nodes[i].address == rx_buf[1])
                {
                    mesh_nodes[i].last_alive_received = power_on_time_msec;
                    mesh_nodes[i].status = NODE_CONNECTED;
                }
                else if (mesh_nodes[i].status == NODE_CONNECTED && mesh_nodes[i].last_alive_received > MESH_NODE_DISCONNECT_TIMEOUT_MS)
                {
                    mesh_nodes[i].status = NODE_NOT_CONNECTED;
                    available_spot = i;
                }
                else if (mesh_nodes[i].status == NODE_NOT_CONNECTED && available_spot == MESH_MAX_NODES)
                {
                    available_spot = i;
                }
                else if (i == MESH_MAX_NODES - 1 && available_spot < MESH_MAX_NODES)
                {
                    mesh_nodes[available_spot].address = rx_buf[1];
                    mesh_nodes[available_spot].status = NODE_CONNECTED;
                    mesh_nodes[available_spot].last_alive_received = power_on_time_msec;
                }
            }
        }
        else if (size > 0)
        {
            set_led_output(RGB_9, GREEN_OUTPUT);

            if (rx_buf[0] < command_count && commands[rx_buf[0]].function != NULL)
            {
                commands[rx_buf[0]].function(rx_buf, size);
            }

        }
    }
    else
    {
        set_led_output(RGB_8, BLUE_OUTPUT);
    }
}

void mesh_do_routing(void)
{
    do_routing_length = 0;
    meshManager->recvfromAckTimeout(&do_routing_data, &do_routing_length, DO_ROUTING_TIMEOUT_MSEC);
}

uint8_t mesh_tx_command(void * data, uint32_t len, uint8_t destination)
{
    uint8_t rval = 1;
    uint8_t max_rt = 4;

    if (len > RH_MESH_PACKET_SIZE)
    {
        uint8_t length_remaining = len;
        uint8_t offset = 0;
        while (length_remaining > 0 && --max_rt)
        {
            if (rval && length_remaining >= RH_MESH_PACKET_SIZE
                    && mesh_tx(((uint8_t*) data) + offset * RH_MESH_PACKET_SIZE, RH_MESH_PACKET_SIZE, destination))
            {
                length_remaining -= RH_MESH_PACKET_SIZE;
                ++offset;
                rval = 1;
            }
            else if (rval &= mesh_tx(((uint8_t*) data) + offset * RH_MESH_PACKET_SIZE, length_remaining, destination))
            {
                length_remaining = 0;
                rval = 1;
            }
            else
            {
                rval = 0;
            }
        }
    }
    else
    {
        rval = mesh_tx(data, len, destination);
    }

    return rval;
}

uint8_t mesh_broadcast_command(void * data, uint32_t len)
{
    uint8_t rval = 1;

    if (len > RH_MESH_PACKET_SIZE)
    {
        uint8_t length_remaining = len;
        uint8_t offset = 0;
        while (length_remaining > 0)
        {
            if (rval && length_remaining >= RH_MESH_PACKET_SIZE
                    && mesh_broadcast(((uint8_t*) data) + offset * RH_MESH_PACKET_SIZE, RH_MESH_PACKET_SIZE))
            {
                length_remaining -= RH_MESH_PACKET_SIZE;
                ++offset;
                rval = 1;
            }
            else if (mesh_broadcast(((uint8_t*) data) + offset * RH_MESH_PACKET_SIZE, length_remaining))
            {
                length_remaining = 0;
                rval = 1;
            }
            else
            {
                rval = 0;
            }
        }
    }
    else
    {
        rval = mesh_broadcast(data, len);
    }

    return rval;
}

uint8_t mesh_tx(void * data, uint32_t dataLength, uint8_t destination)
{
    return meshManager->sendtoWait((uint8_t*) data, dataLength, destination, 0);
}

uint8_t mesh_broadcast(void * data, uint32_t dataLength)
{
    uint8_t current_addr = get_first_node();
    uint8_t rval = 1;

    while (current_addr <= get_first_node())
    {
        rval &= meshManager->sendtoWait((uint8_t*) data, dataLength, current_addr, 0);
        current_addr = get_next_node(current_addr);
    }

    return rval;
}

uint8_t mesh_rx(void * data, uint8_t * dataLength, uint8_t * source)
{
    return meshManager->recvfromAck((uint8_t*) data, (uint8_t*) dataLength, (uint8_t*) source);
}

void mesh_discover_nodes_and_get_address()
{
#if ADDRESS_1
    meshManager->setThisAddress(1);
#elif ADDRESS_2
    meshManager->setThisAddress(2);
#elif ADDRESS_3
    meshManager->setThisAddress(3);
#endif

#if ADDRESS_1 || ADDRESS_2 || ADDRESS_3
    update_random_seed(meshManager->thisAddress());
    return;
#endif

    update_random_seed(millis());
    uint8_t randomAddress = random(0, MESH_STARTUP_ADDRESS);
    RHRouter
    ::RoutingTableEntry * foundRoute;

    meshManager->setThisAddress(randomAddress);
    meshManager->sendtoWait(&randomAddress, 1, meshManager->thisAddress(), 0);

    foundRoute = meshManager->getRouteTo(meshManager->thisAddress());

    if (foundRoute)
    {
        findUnusedAddressInRoutingTable();
    }
}

static bool findUnusedAddressInRoutingTable()
{
    bool rval = false;
    RHRouter
    ::RoutingTableEntry * foundRoute;

    for (uint32_t i = 0; i < MESH_STARTUP_ADDRESS; ++i)
    {
        foundRoute = meshManager->getRouteTo(meshManager->thisAddress());
        if (!foundRoute)
        {
            meshManager->setThisAddress(i);
            update_random_seed(i);
            rval = true;
        }
    }

    return rval;
}

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
    uint8_t buf[] = { MESH_CMD_ADDRESS_CLAIM_MSG, meshManager->thisAddress(), MESH_CMD_TERMINATION };
    mesh_tx(buf, 3, 0xFF);
    time_last_alive_sent_ms = power_on_time_msec;
}

///returns the first node to which a route is found.
uint8_t get_first_node()
{
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

    return rval;
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
