/*
 * TCP_Combined.c
 *
 *  Created on: Mar 31, 2016
 *      Author: thebh_000
 */

//TCP Combined Task.
// watches for messages in outgoing queue
//	sends messages after they are removed from the buffer.
// watches for messages from TCP.
//	puts messages into incoming buffer.
//
//Later, we can look at separating these into two tasks, as has been
//	done with TCP_Transmitter and TCP_Receiver, (but hopefully with
//	a working implementation...)
//
////Includes //////////////////////////////////////////////////////
#include "TCP_Combined.h"
#include "Message_Queue.h"
#include "Message.h"
#include "AddressSerialization.h"

////Macros ////////////////////////////////////////////////////////
#define DATA_CONNECT_ATTEMPT_MAX 		10
#define RECEIVE_DATA_SIZE				256
#define TRANSMIT_DATA_SIZE				RECEIVE_DATA_SIZE
#define LOCAL_TCP_PORT					1002

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static int32 listen_sock;
static int32 listen_return_sock;
static int32 data_sock;

static int32 failure_count;

static int32 receive_count;
static int32 transmit_count;

static char *receive_data;
static char *transmit_data;
static char *message_ptr;

static char * local_address_string;
static char * remote_address_string;

static Message temp_message;

static xTaskHandle TCP_combined_handle;

////Local Prototypes///////////////////////////////////////////////
static int32 Open_Listen_Connection(char * local_addr_string);
static int32 Listen(int32 listen_socket, char * remote_addr_string);
static int32 Open_Data_Connection();
static bool Send_Message(int32 destination_socket, Message * m);
static int32 Receive(int32 source_socket, char * message,
		uint32 message_length_max);

////Global implementations ////////////////////////////////////////
void ICACHE_RODATA_ATTR TCP_Combined_Init()
{
	taskENTER_CRITICAL();
	local_address_string = zalloc(50);
	remote_address_string = zalloc(50);
	receive_data = zalloc(RECEIVE_DATA_SIZE);
	transmit_data = zalloc(TRANSMIT_DATA_SIZE);
	taskEXIT_CRITICAL();

	taskYIELD();

	xTaskCreate(TCP_Combined_Task, "TCPall_1", 512, NULL, 2,
			TCP_combined_handle);
}

void ICACHE_RODATA_ATTR TCP_Combined_Task()
{
	for (;;)
	{
		//TODO: need to be able to initiate the connection as well

		DEBUG_Print("tcp combined start");

		//open listener
		while ((listen_sock = Open_Listen_Connection(local_address_string)) < 0)
		{
			DEBUG_Print("open fail");
			vTaskDelay(1 / portTICK_RATE_MS);
		}

		//listen for incoming connection.
		while ((listen_return_sock = Listen(listen_sock, remote_address_string))
				< 0)
		{
			taskYIELD();
		}

		data_sock = listen_return_sock;

		failure_count = 0;

		while (data_sock > 0)
		{
			receive_count = Receive(data_sock, receive_data, RECEIVE_DATA_SIZE);

			if (receive_count > 0)
			{
				taskENTER_CRITICAL();
				message_ptr = strtok(receive_data, message_delimiter);
				taskEXIT_CRITICAL();

				taskYIELD();

				if (message_ptr != NULL)
				{
					//TODO: strtokn't.
					//		receive into static buffer
					//		put chars into ring buffer, watch for message delimiter
					//		when a delimiter is found, read the message out of the ring buff, update indexes
					//		init message and enqueue.

					taskENTER_CRITICAL();
					Initialize_Message(&temp_message,
							message_type_strings[MESSAGE_TYPE_TCP],
							local_address_string, remote_address_string,
							receive_data);
					taskEXIT_CRITICAL();

					taskYIELD();

					taskENTER_CRITICAL();
					Queue_Message(&incoming_message_queue, &temp_message);
					taskEXIT_CRITICAL();
				}
			}
			else if (receive_count < 0)
			{
				DEBUG_Print("close socket");

				lwip_close(data_sock);
				lwip_close(listen_sock);

				listen_sock = -1;
				data_sock = -1;
			}

			taskYIELD();
		}

	}

}

////Local implementations ////////////////////////////////////////
//initialize listener socket. Set up timeout too.
static int32 ICACHE_RODATA_ATTR Open_Listen_Connection(char * local_addr_string)
{
	struct sockaddr_in server_addr;
	uint16 server_port = LOCAL_TCP_PORT;

	int32 listen_socket = -1;
	int32 bind_result;
	int32 listen_result;

	taskENTER_CRITICAL();
	memset(&server_addr, 0, sizeof(server_addr));
	taskEXIT_CRITICAL();

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = htons(server_port);

	taskENTER_CRITICAL();
	Serialize_Address(Get_IP_Address(), ntohs(server_addr.sin_port),
			local_addr_string, 50);
	taskEXIT_CRITICAL();

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_socket > -1)
	{
		/* Bind to the local port */
		bind_result = lwip_bind(listen_socket, (struct sockaddr *) &server_addr,
				sizeof(server_addr));

		if (bind_result != 0)
		{
			vTaskDelay(1000 / portTICK_RATE_MS);
			lwip_close(listen_socket);
			listen_socket = -1;
		}
		else
		{
			int millis = 100;
			lwip_setsockopt(listen_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
					sizeof(millis));
		}
	}

	if (listen_socket > -1)
	{
		listen_result = lwip_listen(listen_socket, TCP_MAX_CONNECTIONS);

		if (listen_result != 0)
		{
			vTaskDelay(1000 / portTICK_RATE_MS);
			lwip_close(listen_socket);
			listen_socket = -1;
		}
	}

	return listen_socket;
}

//accepts connections
static int32 ICACHE_RODATA_ATTR Listen(int32 listen_socket,
		char * remote_addr_string)
{
	struct sockaddr_in dest_addr;
	int32 accepted_sock;
	int32 len = sizeof(dest_addr);

	if ((accepted_sock = lwip_accept(listen_socket,
			(struct sockaddr *) &dest_addr, (socklen_t *) &len)) < 0)
	{
		int32 error = 0;
		uint32 option_length = sizeof(error);
		int getReturn = lwip_getsockopt(listen_socket, SOL_SOCKET, SO_ERROR,
				&error, &option_length);

//		taskENTER_CRITICAL();
//		printf("listen fail: %d, listen:%d, accepted:%d\r\n", error,
//				listen_sock, accepted_sock);
//		taskEXIT_CRITICAL();

		accepted_sock = -1;
	}
	else
	{
		//Set receive timeout.
		int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
		lwip_setsockopt(accepted_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		taskENTER_CRITICAL();
		Serialize_Address(dest_addr.sin_addr.s_addr, ntohs(dest_addr.sin_port),
				remote_addr_string, 50);
		taskEXIT_CRITICAL();

		DEBUG_Print(remote_addr_string);
	}

	return accepted_sock;
}

//used to initiate connection.
static ICACHE_RODATA_ATTR int32 Open_Data_Connection(int32 remote_socket)
{
	int32 rval = -1;
	return rval;
}

//send a message to the
static ICACHE_RODATA_ATTR bool Send_Message(int32 destination_socket,
		Message * m)
{
	bool rval = false;
	return rval;
}

//returns size of data put into message, or -1 if the connection was reset.
static ICACHE_RODATA_ATTR int Receive(int32 source_socket, char * message,
		uint32 message_length_max)
{
	int32 rval = lwip_recv(source_socket, (void*) message,
			(size_t) message_length_max,
			MSG_PEEK);

	if (rval < 0)
	{
		int32 error = 0;
		uint32 optionLength = sizeof(error);
		int getReturn = lwip_getsockopt(source_socket, SOL_SOCKET, SO_ERROR,
				&error, &optionLength);

		switch (error)
		{
		case ECONNRESET:
		{
			rval = -1;
			break;
		}
		case EAGAIN:
		{
			rval = 0;

			break;
		}
		default:
		{
			break;
		}
		}
	}
	else if (rval > 0 && rval < message_length_max)
	{
		rval = lwip_recv(source_socket, message, message_length_max, 0);
	}

	return rval;
}
