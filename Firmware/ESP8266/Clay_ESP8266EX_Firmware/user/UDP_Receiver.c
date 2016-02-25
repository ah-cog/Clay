/*
 * UDP_Receive.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class receives messages over UDP and puts them into a buffer.
 */

/*
 * States:
 *      Disable -- No receiving occurs.
 *          -Go to configure when enable received
 *      Configure -- set up serial port, interrupts, etc
 *          -Go to Idle upon completion
 *      Idle
 *          -Watch for received data.
 *          -Go to Disable if disabled.
 *      Rx_Blocked
 *          -Something else has exclusive access to the rx buffer. Wait for it to finish.
 *          -Exit to Idle when exclusive access has been relinquished
 *          -Exit to Disable if disabled
 *      Data_Received
 *          -Put data into rx buffer and return to Idle.
 * */

////Includes //////////////////////////////////////////////////////
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "Clay_Config.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
   Disable,
   Configure,
   Idle,
   Rx_Blocked,
   Data_Received,
   UDP_STATE_MAX
} UDP_Receiver_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static UDP_Receiver_States CurrentState;

static int ret;

static uint8_t *UDP_Rx_Buffer;
static uint16_t UDP_Rx_Count;

static size_t fromlen;

static struct sockaddr_in from;
static struct sockaddr_in lastFrom;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Receive();

////Global implementations ////////////////////////////////////////
bool UDP_Receiver_Init()
{
   bool rval = false;
   UDP_Rx_Buffer = zalloc(UDP_RX_BUFFER_SIZE_BYTES);
   nNetTimeout = UDP_RX_TIMEOUT_MSEC;

   CurrentState = Configure;
   return rval;
}

void UDP_Receiver_State_Step()
{
   for (;;)
   {
      switch (CurrentState)
      {
         case Disable:
         {
            break;
         }

         case Configure:
         {
            if (Connect())
            {
               CurrentState = Idle;
            }
            break;
         }

         case Idle:
         {
            break;
         }

         case Rx_Blocked:
         {
            break;
         }

         case Data_Received:
         {
            break;
         }

         case UDP_STATE_MAX:
         default:
         {
            break;
         }
      }

      vTaskDelay(5 / portTICK_RATE_MS);
   }
}

////Local implementations /////////////////////////////////////////
static bool Connect()
{
   bool rval = false;

   memset(&server_addr, 0, sizeof(server_addr));

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(UDP_RX_PORT);
   server_addr.sin_len = sizeof(server_addr);

   ///create the socket
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

   //bind the socket
   do
   {
      ret = bind(sock_fd, (struct sockaddr * ) &server_addr, sizeof(server_addr));
      if (ret != 0)
      {
         //         printf("ESP8266 UDP task > captdns_task failed to bind sock!\n");
         vTaskDelay(1000 / portTICK_RATE_MS);
      }
   } while (ret != 0);
   //   printf("ESP8266 UDP task > bind OK!\n");

   return rval;
}

static bool Receive()
{
   bool rval = false;

   memset(UDP_Rx_Buffer, 0, UDP_RX_BUFFER_SIZE_BYTES);
   memset(&from, 0, sizeof(from));
   setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char * ) &nNetTimeout, sizeof(int));
   fromlen = sizeof(struct sockaddr_in);

   // attempt to receive
   ret = recvfrom(sock_fd,
                  (uint8 * ) UDP_Rx_Buffer,
                  UDP_RX_BUFFER_SIZE_BYTES,
                  0,
                  (struct sockaddr * ) &from,
                  (socklen_t * ) &fromlen);

   if (ret > 0)
   {
      //RxInvalid = TRUE;
      rval = true;

      //store the source address
      lastFrom.sin_addr = from.sin_addr;
      lastFrom.sin_family = from.sin_family;
      lastFrom.sin_len = from.sin_len;
      lastFrom.sin_port = from.sin_port;
      int i = 0;
      for (; i < SIN_ZERO_LEN; ++i)
      {
         lastFrom.sin_zero[i] = from.sin_zero[i];
      }

//      pendingRxBytes = ret > UDP_RX_BUFFER_SIZE_BYTES ? UDP_RX_BUFFER_SIZE_BYTES : ret;
//      memcpy(rxBuf, UDP_Rx_Buffer, ret); // output buffer stuff.
//      rxBuf[pendingRxBytes - 1] = '\0';
//      ret = 0;

//we have a message
      GPIO_OUTPUT(BIT(0), 0);
   }

   return rval;
}

////cut snippets //////////////////////////////////////////////////////////////

//   //cleanup stuff. gone, or maybe we create another state?
//   if (UDP_Rx_Buffer)
//   {
//      free(UDP_Rx_Buffer);
//      UDP_Rx_Buffer = NULL;
//   }
//   free(UDP_Rx_Buffer);
//   close(sock_fd);

//      ///this goes to the transmitter side.
//      if (pendingTxBytes)
//      {
//         //         printf("pending: %d - \"%s\"\r\n", pendingTxBytes, txBuf);
//         sendto(sock_fd, (uint8* ) txBuf, pendingTxBytes, 0, (struct sockaddr * ) &lastFrom, fromlen);
//         pendingTxBytes = 0;
//      }
//      ///end of transmitter side.
