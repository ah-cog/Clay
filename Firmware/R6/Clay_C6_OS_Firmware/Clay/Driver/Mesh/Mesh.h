/*
 * Mesh.h
 *
 *  Created on: Nov 19, 2015
 *      Author: Ben
 */

#ifndef MESH_H_
#define MESH_H_

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

#define MESH_MAX_NODES 10
//
#define MESH_RESERVED_ADDRESS 254
//#define MESH_STARTUP_ADDRESS 253
#define MESH_STARTUP_ADDRESS 3
//
#define MESH_ALIVE_PERIOD_MS            5000
#define MESH_NODE_DISCONNECT_TIMEOUT_MS (3 * MESH_ALIVE_PERIOD_MS)
//
//enum for now
typedef enum
{
   MESH_CMD_CHANGE_MESH_MODE = 0x00,
   MESH_CMD_UPDATE_IMU_DATA = 0x01,
   MESH_CMD_ADDRESS_CLAIM_MSG = 0x02,
   MESH_CMD_BUTTON_PRESSED = 0x03,
   MESH_CMD_ACKNOWLEDGE = 0x04,
   MESH_CMD_MAX     //max mesh command value.
} Mesh_Command_Index;

#define MESH_CMD_TERMINATION            0xEE

//
#define ADDRESS_1                       1
#define ADDRESS_2                       0
#define ADDRESS_3                       0
#if !(ADDRESS_1 || ADDRESS_2 || ADDRESS_3)
#error must define address
#endif
//

typedef void (*Mesh_Command_Callback)(uint8_t * data, uint8_t len);

typedef enum
{
   _250uS = 0,
   _500uS = 1,
   _750uS = 2,
   _1000uS = 3,
   _1250uS = 4,
   _1500uS = 5,
   _1750uS = 6,
   _2000uS = 7,
   _2250uS = 8,
   _2500uS = 9,
   _2750uS = 10,
   _3000uS = 11,
   _3250uS = 12,
   _3500uS = 13,
   _3750uS = 14,
   _4000uS = 15
} mesh_HW_retry_interval;

typedef enum
{
   _1Mbps = 0,
   _2Mbps = 1
} mesh_radio_datarate;

typedef enum
{
   _18dBm = 0,
   _12dBm = 1,
   _6dBm = 2,
   _0dBm = 3
} mesh_radio_tx_attenuation;

typedef struct
{
      uint8_t cmd;
      Mesh_Command_Callback function;
      bool Registered;
} Mesh_Command;

extern bool MeshRxEnabled;
extern bool MeshTxEnabled;
extern bool MeshMessagesAvailable;
//extern LDD_TDeviceData *SPI_DeviceData; //TODO: update drivers

//TODO: Temp vars, used for remote button press demo.
extern uint8_t ThisAddress;
extern uint8_t RemoteAddress;

extern Mesh_Command MeshCommands[];
extern uint32_t MeshCommandCount;

#ifdef __cplusplus
extern "C"
{
#endif

extern bool Enable_Mesh();
extern bool Start_Mesh();
extern void Stop_Mesh();
extern void Pause_Mesh();
extern void Resume_Mesh();
extern void Reset_Mesh();

extern void Mesh_Init();
extern void Mesh_Register_Callback(Mesh_Command_Index command, Mesh_Command_Callback function);
extern void Mesh_Process_Commands(void);
extern uint8_t Mesh_Rx(void * data, uint8_t * dataLength, uint8_t * source);
extern uint8_t Mesh_Tx(void * data, uint32_t dataLength, uint8_t destination);
extern uint8_t Mesh_Tx_With_Retry(void * Data, uint8_t DataLength, uint8_t Destination);
extern uint8_t Mesh_Broadcast(void * data, uint32_t dataLength);
extern void Mesh_Discover_Nodes_And_Get_Address();
extern uint8_t Mesh_Get_First_Node();
extern uint8_t Mesh_Get_Last_Node();
extern uint8_t Mesh_Get_Next_Node(uint8_t startAddr);
extern void Mesh_Irq_Handler(void);
extern bool Mesh_Set_RH_Retry_Count(uint8_t retries);
extern bool Mesh_Set_RH_Timeout(uint16_t timeout_ms);
extern bool Mesh_Set_HW_Retry_Count(uint8_t retransmitCount);
extern bool Mesh_Set_HW_Retry_Delay(mesh_HW_retry_interval retransmitDelay);
extern void Reinit_Mesh_Retries();

#ifdef __cplusplus
}
#endif

#endif /* MESH_H_ */
