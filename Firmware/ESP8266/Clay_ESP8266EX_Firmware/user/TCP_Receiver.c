/*
 * TCP_Receiver.c
 *
 *  Created on: Mar 2, 2016
 *      Author: thebh_000
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

#include "TCP_Receiver.h"
#include "Clay_Config.h"

#include "Clay_Message.h"
#include "Message_Queue.h"

////Typedefs  /////////////////////////////////////////////////////
typedef enum
{
	Disable,
	Configure,
	Idle,
	Enqueue_Message,
	Rx_Blocked,
	Data_Received,
	UDP_STATE_MAX
} TCP_Receiver_States;
////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static TCP_Receiver_States State;

static int ret;

static uint8_t *TCP_Rx_Buffer;
static uint16_t TCP_Rx_Count;

static size_t fromlen;

static struct sockaddr_in from;

static struct sockaddr_in lastSourceAddress;
static struct sockaddr_in server_addr;

static int nNetTimeout;

static int32 sock_fd;
static bool Connected;
static int32 testCounter;

//static char sinZeroStr[50];
//static int sinZeroSize;
//static int i;

Message tempMessage;
char * tempAddr;

////Local Prototypes///////////////////////////////////////////////
static bool Connect();
static void Disconnect();
static bool Receive();

////Local implementations /////////////////////////////////////////
bool TCP_Receiver_Init()
{
	bool rval = false;
	TCP_Rx_Buffer = zalloc(UDP_RX_BUFFER_SIZE_BYTES);
	nNetTimeout = UDP_RX_TIMEOUT_MSEC;

	State = Disable;

	tempAddr = zalloc(SOCKADDR_IN_SIZE_BYTES * 2); //*2 for safety.
	Initialize_Message_Queue(&incomingMessageQueue);

//   printf("udp rx port: %u\n", htons(UDP_RX_PORT));
//   printf("start udp rx\n");
	xTaskCreate(TCP_Receiver_State_Step, "tcprx1", 1024, NULL, 2, NULL);
//   printf("started udp rx\n");

	testCounter = 0;

	return rval;
}

void TCP_Receiver_State_Step()
{
	while(!Connect());
	for (;;)
	{

		if (Receive())
		{
			taskENTER_CRITICAL();
			TCP_Rx_Buffer[TCP_Rx_Count] = '\0';
			printf("%d:[%s]\n", system_get_time(), TCP_Rx_Buffer);
			taskEXIT_CRITICAL();
		}
		taskYIELD();
	}
}

////Local implementations /////////////////////////////////////////

///TCP Scratch area/////////
#define SERVER_IP "192.168.1.12"
#define SERVER_PORT 1001

int sta_socket;
struct sockaddr_in remote_ip;
uint8 * pbuf;
int recbytes;

bool Connect()
{
	bool rval = true;

	//create socket
	sta_socket = socket(PF_INET, SOCK_STREAM, 0);

	//this should be a loop like the UDP.
	if (-1 == sta_socket)
	{
		close(sta_socket);
		vTaskDelay(1000 / portTICK_RATE_MS);
		printf("ESP8266 TCP client task > socket fail!\n");
		rval = false;
	}
	if (rval) {
		printf("ESP8266 TCP client task > socket ok!\n");
	}

	//create tcp connection
	bzero(&remote_ip, sizeof(struct sockaddr_in));
	remote_ip.sin_family = AF_INET;
	remote_ip.sin_addr.s_addr = inet_addr(SERVER_IP);
	remote_ip.sin_port = htons(SERVER_PORT);

	//this should be a loop like the UDP.
	if ((sta_socket != -1)
			&& connect(sta_socket, (struct sockaddr * ) (&remote_ip),
					sizeof(struct sockaddr)))
	{
		close(sta_socket);
		vTaskDelay(1000 / portTICK_RATE_MS);
		printf("ESP8266 TCP client task > connect fail!\n");
		rval = false;
	}

	if (rval) {
		printf("ESP8266 TCP client task > connect ok!\n");
	}

	return rval;
}
///TCP scratch area/////////

static void Disconnect()
{
	if (TCP_Rx_Buffer)
	{
		free(TCP_Rx_Buffer);
		TCP_Rx_Buffer = NULL;
	}
	free(TCP_Rx_Buffer);
	close(sock_fd);
}

static bool Receive()
{
	bool rval = false;

	char *recv_buf = (char *) zalloc(128);
	while ((recbytes = read(sta_socket, recv_buf, 128)) > 0)
	{
		recv_buf[recbytes] = 0;
		printf(
				"ESP8266 TCP client task > recv data %d bytes!\nESP8266 TCP client task > %s\n",
				recbytes, recv_buf);
	}
	free(recv_buf);
	if (recbytes <= 0)
	{
		rval = false;
		close(sta_socket);
		printf("ESP8266 TCP client task > read data fail!\n");
	}
	else
	{
		rval = true;
	}

	return rval;
}
