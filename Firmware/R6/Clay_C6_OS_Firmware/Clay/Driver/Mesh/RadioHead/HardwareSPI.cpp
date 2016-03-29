// ArduinoCompat/HardwareSPI.cpp
//
// Interface between Arduino-like SPI interface and STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include "wirish.h"
#include "HardwareSPI.h"
//#include "MESH_SPI.h" //TODO: update driver
//#include "MESH_CS.h"  //TODO: Update driver
//#include "LED1.h"
//#include "LED2.h"
#include "Mesh.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "Clock.h"

#ifdef __cplusplus
}
#endif

#define MAX_XFER_RETRIES  10

HardwareSPI::HardwareSPI(uint32_t spiPortNumber) {
   //MESH_SPI is init'd in Mesh.c
}

void HardwareSPI::begin(SPIFrequency frequency, uint32_t bitOrder, uint32_t mode) {
}

void HardwareSPI::end(void) {
}

static uint8_t rval = 0;
static uint8_t * rvalPtr = &rval;        //attempting to pass &rval into ReceiveBlock was yielding 0x00 returns every time.
static uint8_t retryCount;

uint8_t HardwareSPI::transfer(uint8_t data) {
   retryCount = 0;

   //TODO: Update SPI driver.

   //Enable receive, then initiate send. the RX will happen at the same time.
//   MESH_SPI_ReceiveBlock(SPI_DeviceData, rvalPtr, 1);
//   MESH_SPI_SendBlock(SPI_DeviceData, (void*) &data, 1);
//
//   //wait for transmission.
//   while (!MESH_SPI_GetBlockReceivedStatus(SPI_DeviceData) && (retryCount++ < MAX_XFER_RETRIES))
//      ;

   return rval;
}
