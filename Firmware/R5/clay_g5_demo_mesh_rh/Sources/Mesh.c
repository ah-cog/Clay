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

///local vars
static RHMesh * meshManager;
static RH_NRF24 * meshRadio;

///prototypes
static bool findUnusedAddressInRoutingTable();

///functions
void mesh_init()
{
    meshRadio = new
    RH_NRF24(MESH_CE_PIN_INDEX, MESH_SELECT_PIN_INDEX);
    meshManager = new
    RHMesh(*meshRadio);
    meshManager->init();
    meshManager->setThisAddress((uint8_t) random(0, MESH_RESERVED_ADDRESS - 1));
    mesh_discover_nodes();
}

uint8_t mesh_tx(void * data, uint32_t dataLength, uint8_t destination)
{
    return meshManager->sendtoWait((uint8_t*) data, dataLength, destination, 0);
}

uint8_t mesh_rx(void * data, uint32_t * dataLength, uint8_t * source)
{
    return meshManager->recvfromAck((uint8_t*) data, (uint8_t*) dataLength, (uint8_t*) source);
}

void mesh_discover_nodes()
{
    uint8_t derp = 0x00;
    RHRouter
    ::RoutingTableEntry * foundRoute;

    meshManager->sendtoWait(&derp, 1, MESH_RESERVED_ADDRESS, 0);

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

    for (uint32_t i = 0; i < MESH_RESERVED_ADDRESS; ++i)
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

///returns the first node to which a route is found.
uint8_t get_first_node()
{
    RHRouter
    ::RoutingTableEntry * foundRoute;
    uint8_t rval = 0xFF;        //invalid address.

    for (uint32_t i = 0; i < MESH_RESERVED_ADDRESS; ++i)
    {
        foundRoute = meshManager->getRouteTo(meshManager->thisAddress());
        if (foundRoute)
        {
            rval = i;
            break;
        }
    }

    return rval;
}
