/*
 * ref_code.c
 *
 *  Created on: Feb 23, 2016
 *      Author: thebh
 */

#if 0


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
#endif
