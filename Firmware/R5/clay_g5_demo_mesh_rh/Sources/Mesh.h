/*
 * Mesh.h
 *
 *  Created on: Nov 19, 2015
 *      Author: Ben
 */

#ifndef MESH_H_
#define MESH_H_

#include <stdint.h>

#define MESH_MAX_NODES 10
//
#define MESH_RESERVED_ADDRESS 254
//

extern void mesh_init(void);
extern uint8_t mesh_rx(void * data, uint32_t * dataLength, uint8_t * source);
extern uint8_t mesh_tx(void * data, uint32_t dataLength, uint8_t destination);
extern void mesh_discover_nodes();
extern uint8_t get_first_node();

#endif /* MESH_H_ */
