/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/12/1, v1.0 create this file.
 *******************************************************************************/
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "../include/GPIO.h"
#include "../include/UART.h"
#include "Clay_Message.h"
#include "Serial_Receiver.h"
#include "Serial_Transmitter.h"
#include "UDP_Receiver.h"
#include "UDP_Transmitter.h"
#include "String_Message_Parser.h"

#define server_ip "192.168.101.142"
#define server_port 9669

#define UDP_LOCAL_PORT 1200
#define UDP_DATA_LEN   100
#define MAX_PINS       3

#define RX_BUF_SIZE    UDP_DATA_LEN
#define TX_BUF_SIZE    100

uint32 pendingRxBytes;
uint32 pendingTxBytes;

char rxBuf[RX_BUF_SIZE];
char txBuf[TX_BUF_SIZE];

bool RxInvalid;

void uC_Interrupt_Handler()
{
   printf("got the interrupt\r\n");
}

void main_int_handler()
{
//   printf("main_int_callback!\n");
   int i;
   uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
   for (i = 0; i < MAX_PINS; i++)
   {
      if ((gpio_status & BIT(i)))
      {
//         printf("triggered on int: %d\n", i);
         //disable interrupt
         gpio_pin_intr_state_set(GPIO_ID_PIN(i), GPIO_PIN_INTR_DISABLE);

         // call func here
         if (i == 2)
         {
            //TODO: more generic caller
            uC_Interrupt_Handler();
         }

         //clear interrupt status
         GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(i));

         // restore
         gpio_pin_intr_state_set(GPIO_ID_PIN(i), GPIO_PIN_INTR_DISABLE);
      }
   }
}

void ICACHE_FLASH_ATTR registerInterrupt(int pin, GPIO_INT_TYPE mode)
{
   portENTER_CRITICAL();

   //clear interrupt status
   GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(pin));

   // set the mode
   gpio_pin_intr_state_set(GPIO_ID_PIN(pin), mode);

   portEXIT_CRITICAL();
}

void GPIO_Init()
{
   ///setup GPIO and set output to 1.
   GPIO_AS_OUTPUT(BIT(0));
   GPIO_OUTPUT(BIT(0), 1);
   GPIO_AS_INPUT(BIT(2));

   _xt_isr_attach(ETS_GPIO_INUM, (_xt_isr) main_int_handler, NULL);
   _xt_isr_unmask(1 << ETS_GPIO_INUM);

   registerInterrupt(2, GPIO_PIN_INTR_NEGEDGE);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void user_init(void)
{
   GPIO_Init();

#if 0
   printf("SDK version:%s\n", system_get_sdk_version());
#endif

   /* need to set opmode before you set config */
   wifi_set_opmode(STATIONAP_MODE);
   uart_init_new();

   {
      struct station_config *config = (struct station_config *) zalloc(sizeof(struct station_config));
      sprintf(config->ssid, "hefnetm");
      sprintf(config->password, "dips00BOYNEdo$!&");

      /* need to sure that you are in station mode first,
       * otherwise it will be failed. */
      wifi_station_set_config(config);
      free(config);
   }

   xTaskCreate(UDP_Receiver_State_Step, "", 256, NULL, 2, NULL);
   xTaskCreate(UDP_Transmitter_State_Step, "", 256, NULL, 2, NULL);
   xTaskCreate(Serial_Receiver_State_Step, "", 256, NULL, 2, NULL);
   xTaskCreate(Serial_Transmitter_State_Step, "", 256, NULL, 2, NULL);
   xTaskCreate(String_Message_Parser_State_Step, "", 256, NULL, 2, NULL);
}

