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
#include "gpio.h"
#include "uart.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#define server_ip "192.168.101.142"
#define server_port 9669

//TODO: check UDP ports
//TODO: my port and a broadcast report, tx and rx
//TODO: discovery port

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
   //set flag to say send the message to the uC if a message is waiting.
   //if message not waiting, set flag to stop rx interrupts and read message from the uC.
   //signal uC that we're ready to receive by setting GPIO line low again
//   printf("got the interrupt\r\n");
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

   //TODO: interrupts
//   _xt_isr_attach(ETS_GPIO_INUM, (_xt_isr) main_int_handler, NULL);
//   _xt_isr_unmask(1 << ETS_GPIO_INUM);
//
//   registerInterrupt(2, GPIO_PIN_INTR_NEGEDGE);
}

void task2(void *pvParameters)
{
   int ret;

   uint8_t *udp_msg = zalloc(UDP_DATA_LEN);

   size_t fromlen;

   struct sockaddr_in from;
   struct sockaddr_in lastFrom;
   struct sockaddr_in server_addr;

   int nNetTimeout = 100;

   RxInvalid = FALSE;

   LOCAL int32 sock_fd;

   GPIO_OUTPUT(BIT(0), 1);
   memset(&server_addr, 0, sizeof(server_addr));

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(UDP_LOCAL_PORT);
   server_addr.sin_len = sizeof(server_addr);

   do
   {
      sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
      if (sock_fd == -1)
      {
//         printf("ESP8266 UDP task > failed to create sock!\n");
         vTaskDelay(1000 / portTICK_RATE_MS);
      }
   } while (sock_fd == -1);
//   printf("ESP8266 UDP task > socket OK!\n");

   do
   {
      ret = bind(sock_fd, (struct sockaddr * )&server_addr, sizeof(server_addr));
      if (ret != 0)
      {
//         printf("ESP8266 UDP task > captdns_task failed to bind sock!\n");
         vTaskDelay(1000 / portTICK_RATE_MS);
      }
   } while (ret != 0);
//   printf("ESP8266 UDP task > bind OK!\n");

   while (1)
   {
      memset(udp_msg, 0, UDP_DATA_LEN);
      memset(&from, 0, sizeof(from));
      setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char * )&nNetTimeout, sizeof(int));
      fromlen = sizeof(struct sockaddr_in);
      ret = recvfrom(sock_fd, (uint8 * )udp_msg, UDP_DATA_LEN, 0, (struct sockaddr * )&from, (socklen_t * )&fromlen);
      if (ret > 0 && !pendingRxBytes)
      {
//         sendto(sock_fd, (uint8* )udp_msg, ret, 0, (struct sockaddr * )&from, fromlen);
         RxInvalid = TRUE;

         lastFrom.sin_addr = from.sin_addr;
         lastFrom.sin_family = from.sin_family;
         lastFrom.sin_len = from.sin_len;
         lastFrom.sin_port = from.sin_port;
         int i = 0;
         for (; i < SIN_ZERO_LEN; ++i)
         {
            lastFrom.sin_zero[i] = from.sin_zero[i];
         }

         pendingRxBytes = ret > RX_BUF_SIZE ? RX_BUF_SIZE : ret;
         memcpy(rxBuf, udp_msg, ret);
         rxBuf[pendingRxBytes - 1] = '\0';
         ret = 0;
         RxInvalid = FALSE;
         GPIO_OUTPUT(BIT(0), 0);
//         vTaskDelay(20 / portTICK_RATE_MS);
//         GPIO_OUTPUT(BIT(0), 1);
      }

      if (pendingTxBytes)
      {
//         printf("pending: %d - \"%s\"\r\n", pendingTxBytes, txBuf);
         sendto(sock_fd, (uint8* )txBuf, pendingTxBytes, 0, (struct sockaddr * )&lastFrom, fromlen);
         pendingTxBytes = 0;
      }
   }
   if (udp_msg)
   {
      free(udp_msg);
      udp_msg = NULL;
   }
   free(udp_msg);
   close(sock_fd);

   for (;;)
      ;
}

void task3(void *pvParameters)
{
   uint8 changer = 0;
   uint8 startTime = 0;

   for (;;)
   {
      if (!GPIO_INPUT_GET(2) && !RxInvalid)
      {

//         printf("%d 2 low\r\n", ++changer);
         if (pendingRxBytes)
         {
//            printf("%d requested data \r\n", ++changer);
            //TODO: we should be in this state if we have data -- check that
            //micro ack'd our rx interrupt. Send the message back.

            //TODO: watch out for there to be no null. For now we're just putting one in in case.
            RxInvalid = TRUE;
            rxBuf[RX_BUF_SIZE - 1] = 0x00;
            printf("%s\r\n", rxBuf);
            pendingRxBytes = 0;
            vTaskDelay(20 / portTICK_RATE_MS);
            RxInvalid = FALSE;
            GPIO_OUTPUT(BIT(0), 1);
         }
         else
         {
//            printf("%d tx requested\r\n", ++changer);
            GPIO_OUTPUT(BIT(0), 0);
            vTaskDelay(20 / portTICK_RATE_MS);
            GPIO_OUTPUT(BIT(0), 1);
            //this is code written for the ESP uart driver, with the fifo_x vars made global
            if (fifo_len || !(++startTime))
            {
               pendingTxBytes = fifo_len > TX_BUF_SIZE ? TX_BUF_SIZE : fifo_len;
               memcpy(txBuf, fifo_tmp, pendingTxBytes);

               startTime = 0;
            }
         }

      }
      else
      {
//         printf("%d 2 high\r\n", ++changer);
      }
      vTaskDelay(100 / portTICK_RATE_MS);
   }
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void user_init(void)
{
///This demo shows the ESP generating an interrupt on GPIO0 when a UDP message is received.
///  The message is then queued up and held until an interrupt arrives on GPIO2 from the uC
///  When that interrupt is received, the message is transmitted over UART to the uC
///The uC can also interrupt and send a message.

   GPIO_Init();
//   UART_SetBaudrate(UART0, 115200);

//   printf("SDK version:%s\n", system_get_sdk_version());

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

   xTaskCreate(task2, "tsk2", 256, NULL, 2, NULL);
   xTaskCreate(task3, "tsk3", 256, NULL, 2, NULL);
}

