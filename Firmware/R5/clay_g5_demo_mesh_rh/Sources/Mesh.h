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
//#define MESH_STARTUP_ADDRESS 253
#define MESH_STARTUP_ADDRESS 3
//
#define MESH_CMD_CHANGE_MESH_MODE       0x00
#define MESH_CMD_UPDATE_IMU_DATA        0x01
#define MESH_CMD_ADDRESS_CLAIM_MSG      0x02
#define MESH_CMD_TERMINATION            0xEE
//
#define ADDRESS_1                       0
#define ADDRESS_2                       2
#define ADDRESS_3                       0
//
typedef void (*cmd_func)(uint8_t * data, uint8_t len);

typedef struct
{
    uint8_t cmd;
    cmd_func function;
} mesh_command;

extern mesh_command commands[];
extern uint32_t command_count;

extern void mesh_init(cmd_func changeMeshModeCallback, cmd_func updateImuLedsCallback);
extern void mesh_process_commands(void);
extern void mesh_do_routing(void);
extern uint8_t mesh_rx(void * data, uint8_t * dataLength, uint8_t * source);
extern uint8_t mesh_tx_command(void * data, uint32_t dataLength, uint8_t destination);
extern uint8_t mesh_tx(void * data, uint32_t dataLength, uint8_t destination);
extern uint8_t mesh_broadcast_command(void * data, uint32_t dataLength);
extern uint8_t mesh_broadcast(void * data, uint32_t dataLength);
extern void mesh_discover_nodes_and_get_address();
extern uint8_t get_first_node();
extern uint8_t get_last_node();
extern uint8_t get_next_node(uint8_t startAddr);

#endif /* MESH_H_ */
