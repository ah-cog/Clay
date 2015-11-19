// ArduinoCompat/HardwareSPI.cpp
//
// Interface between Arduino-like SPI interface and STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include "wirish.h"
#include "HardwareSPI.h"
#include "SM1.h"
#include "system_tick.h"
#include "MESH_CS.h"
#include "LED1.h"
#include "LED2.h"

HardwareSPI::HardwareSPI(uint32_t spiPortNumber)
{
    //sm1 is auto-init'd by PE code.
}

void HardwareSPI::begin(SPIFrequency frequency, uint32_t bitOrder, uint32_t mode)
{
    //TODO: PE init code
}

void HardwareSPI::end(void)
{
    //TODO: PE de-init code
}

static uint8_t rval = 0;
static uint8_t * rvalPtr = &rval;        //attempting to pass &rval into ReceiveBlock was yielding 0x00 returns every time.

uint8_t HardwareSPI::transfer(uint8_t data)
{
    //Enable receive, then initiate send. the RX will happen at the same time.
    SM1_ReceiveBlock(SM1_DeviceData, rvalPtr, 1);
    SM1_SendBlock(SM1_DeviceData, (void*) &data, 1);

    //wait for transmission.
    while (!SM1_GetBlockReceivedStatus(SM1_DeviceData ))
        ;

    return rval;
}
