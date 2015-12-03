// ArduinoCompat/HardwareSPI.cpp
//
// Interface between Arduino-like SPI interface and STM32F4 Discovery and similar
// using STM32F4xx_DSP_StdPeriph_Lib_V1.3.0

#include "wirish.h"
#include "HardwareSPI.h""
#include "SM1.h"

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

uint8_t HardwareSPI::transfer(uint8_t data)
{
    //TODO: PE xfer code
    SM1_SendBlock(SM1_DeviceData, (void*)data, 1);
    
    SM1_ReceiveBlock(SM1_DeviceData, &data, 1);
    return data;
}
