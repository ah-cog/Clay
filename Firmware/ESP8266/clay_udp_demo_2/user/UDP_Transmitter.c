/*
 * UDP_Transmitter.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: thebh
 *
 *      This class consumes (Clay_Message)s from a queue and transmits them over UDP
 */

/*
 * States:
 *      Disabled -- no transmissions occur
 *      Configure -- Create a UDP socket and prepare it for listening.
 *          -upon completion, we go to Idle
 *      Idle -- no messages available in buffer
 *          -messages become available, we go to Buffer_Message
 *          -Disable message sends us back to Disabled
 *      Buffer_Message -- message was available in queue
 *          -Message consumed out of queue into transmit buffer. Go to Send_Message. Leave message in queue for now.
 *          -Disable message sends us back to Disabled.
 *      Send_Message (combine with Buffer_Message?)
 *          -Send the message waiting in the buffer. Return to idle upon successful completion
 *      Retry?
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
   Buffer_Message,
   Send_Message,
   UDP_STATE_MAX
} UDP_Transmitter_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static UDP_Transmitter_States CurrentState;

static int ret;

static uint8_t *UDP_Tx_Buffer;
static uint16_t UDP_Tx_Count;

static size_t fromlen;

static struct sockaddr_in from;
static struct sockaddr_in lastFrom;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static bool Transmit();

////Global implementations ////////////////////////////////////////
bool UDP_Transmitter_Init()
{
   bool rval = false;

   CurrentState = Configure;
   return rval;
}

void UDP_Transmitter_State_Step()
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

         case Buffer_Message:
         {
            break;
         }

         case Send_Message:
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
   server_addr.sin_port = htons(UDP_TX_PORT);
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

static bool Transmit()
{
   bool rval = false;
   //         sendto(sock_fd, (uint8* ) txBuf, pendingTxBytes, 0, (struct sockaddr * ) &lastFrom, fromlen);
   //         pendingTxBytes = 0;

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

