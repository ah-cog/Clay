////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#include "Mesh_Simple.h"

#include "MESH_SPI.h"
#include "MESH_CE.h"
#include "MESH_IRQ.h"
#include "MESH_CS.h"

////Macros ////////////////////////////////////////////////////////
#define REGISTER_CONFIG  			 0
#define REGISTER_EN_AA               1
#define REGISTER_EN_RXADDR           2
#define REGISTER_SETUP_AW            3
#define REGISTER_SETUP_RETR          4
#define REGISTER_RF_CH               5
#define REGISTER_RF_SETUP            6
#define REGISTER_STATUS              7
#define REGISTER_OBSERVE_TX          8
#define REGISTER_RPD                 9
#define REGISTER_RX_ADDR_P0          A
#define REGISTER_RX_ADDR_P1          B
#define REGISTER_RX_ADDR_P2          C
#define REGISTER_RX_ADDR_P3          D
#define REGISTER_RX_ADDR_P4          E
#define REGISTER_RX_ADDR_P5          F
#define REGISTER_TX_ADDR             10
#define REGISTER_RX_PW_P0            11
#define REGISTER_RX_PW_P1            12
#define REGISTER_RX_PW_P2            13
#define REGISTER_RX_PW_P3            14
#define REGISTER_RX_PW_P4            15
#define REGISTER_RX_PW_P5            16
#define REGISTER_FIFO_STATUS         17
#define REGISTER_DYNPD               1C
#define REGISTER_FEATURE             1D

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
LDD_TDeviceDataPtr mesh_spi_data;
LDD_TDeviceDataPtr mesh_ce_data;
LDD_TDeviceDataPtr mesh_irq_data;
LDD_TDeviceDataPtr mesh_cs_data;

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////
bool Mesh_Enable() {
   bool rval = false;

   mesh_spi_data = MESH_SPI_Init(NULL);
   mesh_ce_data = MESH_CE_Init(NULL);
   mesh_irq_data = MESH_IRQ_Init(NULL);
   mesh_cs_data = MESH_CS_Init(NULL);

   return rval;
}

void Mesh_Periodic() {
}

bool Mesh_Send(uint8_t * tx_buf, uint32_t length, uint32_t destination_address, Message_Complete_Callback message_complete) {
   bool rval = false;
   return rval;
}

bool Mesh_Broadcast(uint8_t * tx_buf, uint32_t length, Message_Complete_Callback message_complete) {
   bool rval = false;
   return rval;
}

int Mesh_Receive(uint8_t * rx_buf, uint32_t length) {
   int rval = -1;
   return rval;
}

void Mesh_Interrupt_Handler() {
}

////Local implementations /////////////////////////////////////////
