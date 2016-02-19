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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#define server_ip "192.168.101.142"
#define server_port 9669
#define UDP_LOCAL_PORT 1200
#define UDP_DATA_LEN   64


void task2(void *pvParameters)
{
   int ret;
   uint8_t *udp_msg = zalloc(UDP_DATA_LEN);
   size_t fromlen;
   struct sockaddr_in from;
   int nNetTimeout = 100;

   LOCAL int32 sock_fd;
   struct sockaddr_in server_addr;
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
         printf("ESP8266 UDP task > failed to create sock!\n");
         vTaskDelay(1000 / portTICK_RATE_MS);
      }
   } while (sock_fd == -1);
   printf("ESP8266 UDP task > socket OK!\n");

   do
   {
      ret = bind(sock_fd, (struct sockaddr * )&server_addr, sizeof(server_addr));
      if (ret != 0)
      {
         printf("ESP8266 UDP task > captdns_task failed to bind sock!\n");
         vTaskDelay(1000 / portTICK_RATE_MS);
      }
   } while (ret != 0);
   printf("ESP8266 UDP task > bind OK!\n");

   while (1)
   {
      memset(udp_msg, 0, UDP_DATA_LEN);
      memset(&from, 0, sizeof(from));
      setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char * )&nNetTimeout, sizeof(int));
      fromlen = sizeof(struct sockaddr_in);
      ret = recvfrom(sock_fd, (uint8 * )udp_msg, UDP_DATA_LEN, 0, (struct sockaddr * )&from, (socklen_t * )&fromlen);
      if (ret > 0)
      {
         //ret contains bytes
         //udp_msg contains message
         printf("ESP8266 UDP task > recv %d Bytes from Port %d %s\n ", ret, ntohs(from.sin_port), inet_ntoa(from.sin_addr));
         printf("message:%s", udp_msg);
//         gpio_output_conf(0,1,0,0);
         GPIO_OUTPUT(BIT(0), 0);
         sendto(sock_fd, (uint8* )udp_msg, ret, 0, (struct sockaddr * )&from, fromlen);
         vTaskDelay(100 / portTICK_RATE_MS);
         GPIO_OUTPUT(BIT(0), 1);
//         gpio_output_conf(1,0,0,0);
      }
   }
   if (udp_msg)
   {
      free(udp_msg);
      udp_msg = NULL;
   }
   free(udp_msg);
   close(sock_fd);
}

void task3(void *pvParameters)
{
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
   ///  the UDP packet length and content are printed on the UART, and the message is echoed to
   ///  the sender
   ///


   printf("SDK version:%s\n", system_get_sdk_version());

   ///setup GPIO and set output to 1.
   GPIO_AS_OUTPUT(BIT(0));
   GPIO_OUTPUT(BIT(0), 1);

   GPIO_AS_INPUT(BIT(2));

   /* need to set opmode before you set config */
   wifi_set_opmode(STATIONAP_MODE);

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
//   xTaskCreate(task3, "tsk3", 256, NULL, 2, NULL);
}

