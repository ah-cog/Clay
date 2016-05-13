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
#include "esp_common.h"

#include "stdio.h"
#include "string.h"

#include "UART.h"
#include "TCP_Combined.h"

#include "Wifi_Message_Serialization.h"
#include "System_Monitor.h"
#include "Message_Queue.h"
#include "Message.h"
#include "Queues.h"
#include "AddressSerialization.h"
#include "Multibyte_Ring_Buffer.h"

////Macros ////////////////////////////////////////////////////////
#define DATA_CONNECT_ATTEMPT_MAX 		10
#define RECEIVE_DATA_SIZE				1024
#define TRANSMIT_DATA_SIZE				1024
#define LOCAL_TCP_PORT					3000
#define ADDR_STRING_SIZE 				50
#define CONNECT_TIMEOUT_ms				100
#define LISTEN_TIMEOUT_ms				100
#define CONNECT_ATTEMPT_MAX				5

#define MESSAGE_TRIGGER_LEVEL			10
#define RECEIVE_BYTES_TRIGGER_LEVEL		512

#define CONNECT_RETRY_TIME				100000
////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
	int socket;
	struct sockaddr_in * address;
	volatile bool connected;
} Connect_Task_Args;

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static int32 listen_sock;
static int32 data_sock;

static int32 received_count;

static xTaskHandle idle_handle;

static bool connected;
static bool promoted;

//static char *receive_data;
static char *transmit_data;

static char * local_address_string;
static char * remote_address_string;

struct sockaddr_in local_address;
struct sockaddr_in remote_address;

static Message * temp_msg_ptr;
static Message_Type * ignored_message_type;

static uint32 last_tcp_activity_time;
static uint32 tcp_connection_timeout_us = 2500000;

static bool listening;
static bool task_running = false;
static bool opening_connection = false;

static Message_Type connection_type;

static const char http_get_format[] = "GET %s HTTP/1.1\r\n\r\n";

static Multibyte_Ring_Buffer tcp_rx_multibyte;

////Local Prototypes///////////////////////////////////////////////
static int32 Open_Listen_Connection(char * local_addr_string,
		struct sockaddr_in * local_addr);
static int32 Listen(int32 listen_socket, char * remote_addr_string,
		struct sockaddr_in * remote_addr);
static int32 Open_Data_Connection(struct sockaddr_in * remote_addr);

static bool Initiate_Connection_For_Outgoing_Message();
static bool Dequeue_And_Transmit(int32 data_sock);
static bool Receive_And_Enqueue(int32 data_sock);

static bool Send_Message(int32 destination_socket, Message * m);
static int32 Receive(int32 source_socket, char * destination,
		uint32 receive_length_max);

static bool Check_Needs_Promotion();
static uint8_t * memchr2(uint8_t * ptr, uint8_t ch, size_t size);
static void Connect_Task(void * PvParams);
static void Data_Disconnect();
static void Listen_Disconnect();
static bool TCP_Timeout_Check();
static bool Prepare_Http_Message(Message * m);

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Combined_Init()
{
	bool rval = true;

	if (!task_running)
	{

		idle_handle = xTaskGetIdleTaskHandle();

		promoted = false;

		taskENTER_CRITICAL();
		Free_Message_Queue(&outgoing_tcp_message_queue);
		Multibyte_Ring_Buffer_Init(&tcp_rx_multibyte, RECEIVE_DATA_SIZE);
		local_address_string = zalloc(ADDR_STRING_SIZE);
		remote_address_string = zalloc(ADDR_STRING_SIZE);
		transmit_data = zalloc(TRANSMIT_DATA_SIZE);
		taskEXIT_CRITICAL();

		taskYIELD();

		xTaskHandle TCP_combined_handle;

		xTaskCreate(TCP_Combined_Task, "TCP combined", 256, NULL,
				DEFAULT_PRIORITY, &TCP_combined_handle);

		System_Register_Task(TASK_TYPE_TCP_RX, TCP_combined_handle,
				Check_Needs_Promotion);

		if (TCP_combined_handle != NULL)
		{
//			DEBUG_Print("tcp task started");
			task_running = true;
		}
	}
	else
	{
		rval = false;
	}

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Combined_Deinit()
{
//	DEBUG_Print("tcp deinit");

	if (task_running)
	{

		connected = false;

		Data_Disconnect();
		Listen_Disconnect();

		taskENTER_CRITICAL();
		Free_Message_Queue(&outgoing_tcp_message_queue);
		outgoing_tcp_message_count = 0;
		taskEXIT_CRITICAL();

		free(local_address_string);
		free(remote_address_string);
		Multibyte_Ring_Buffer_Free(&tcp_rx_multibyte);
		free(transmit_data);

		task_running = false;

		System_Stop_Task(TASK_TYPE_TCP_RX);
	}
}

void ICACHE_RODATA_ATTR TCP_Combined_Task()
{
	for (;;)
	{
		connected = false;
		opening_connection = true;

#if ENABLE_TCP_COMBINED_RX
		//open listener
		while (!listening
				&& (listen_sock = Open_Listen_Connection(local_address_string,
						&local_address)) < 0)
		{
			taskYIELD();
		}
#endif

		//listen for incoming connection, start a connection if we have an outgoing message.
		while (!connected)
		{
#if ENABLE_TCP_COMBINED_RX
			data_sock = Listen(listen_sock, remote_address_string,
					&remote_address);
			connected = data_sock > -1;
#endif

#if ENABLE_TCP_COMBINED_TX
			if (!connected)
			{
				connected = Initiate_Connection_For_Outgoing_Message();
			}
#endif

			taskYIELD();
		}

		opening_connection = false;

		while (connected)
		{
#if ENABLE_TCP_COMBINED_TX
			connected = Dequeue_And_Transmit(data_sock);
#endif

#if ENABLE_TCP_COMBINED_RX
			connected &= Receive_And_Enqueue(data_sock);
#endif

			connected &= TCP_Timeout_Check();

			taskYIELD();
		}

	}

}

////Local implementations ////////////////////////////////////////
//initialize listener socket. Set up timeout too.
static int32 ICACHE_RODATA_ATTR Open_Listen_Connection(char * local_addr_string,
		struct sockaddr_in * local_addr)
{
	uint16 server_port = LOCAL_TCP_PORT;

	int32 listen_socket = -1;
	int32 bind_result;
	int32 listen_result;

	taskENTER_CRITICAL();
	memset(local_addr, 0, sizeof(struct sockaddr_in));
	taskEXIT_CRITICAL();

	local_addr->sin_family = AF_INET;
	local_addr->sin_addr.s_addr = INADDR_ANY;
	local_addr->sin_len = sizeof(*local_addr);
	local_addr->sin_port = htons(server_port);

	taskENTER_CRITICAL();
	Serialize_Address(Get_IP_Address(), ntohs(local_addr->sin_port),
			local_addr_string, 50);
	taskEXIT_CRITICAL();

	taskYIELD();

	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listen_socket > -1)
	{
		/* Bind to the local port */
		bind_result = lwip_bind(listen_socket, (struct sockaddr *) local_addr,
				sizeof(*local_addr));

		taskYIELD();

		if (bind_result != 0)
		{
			int32 error = 0;
			uint32 optionLength = sizeof(error);
			int getReturn = lwip_getsockopt(listen_socket, SOL_SOCKET,
			SO_ERROR, &error, &optionLength);

			lwip_close(listen_socket);
			listen_socket = -1;
		}
		else
		{
			int millis = LISTEN_TIMEOUT_ms;
			lwip_setsockopt(listen_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
					sizeof(millis));
		}
	}

	taskYIELD();

	if (listen_socket > -1)
	{
		listen_result = lwip_listen(listen_socket, TCP_MAX_CONNECTIONS);

		if (listen_result != 0)
		{
			int32 error = 0;
			uint32 optionLength = sizeof(error);
			int getReturn = lwip_getsockopt(listen_socket, SOL_SOCKET,
			SO_ERROR, &error, &optionLength);

			lwip_close(listen_socket);
			listen_socket = -1;
		}
		else
		{
			listening = true;
		}
	}

	taskYIELD();

	return listen_socket;
}

//accepts connections
static int32 ICACHE_RODATA_ATTR Listen(int32 listen_socket,
		char * remote_addr_string, struct sockaddr_in * remote_addr)
{
	int32 accepted_sock;
	int32 len = sizeof(struct sockaddr_in);

	if ((accepted_sock = lwip_accept(listen_socket,
			(struct sockaddr *) remote_addr, (socklen_t *) &len)) < 0)
	{
		int32 error = 0;
		uint32 option_length = sizeof(error);
		int getReturn = lwip_getsockopt(listen_socket, SOL_SOCKET, SO_ERROR,
				&error, &option_length);

		accepted_sock = -1;
	}
	else
	{
		//Set receive timeout.
		int millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
		lwip_setsockopt(accepted_sock, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		last_tcp_activity_time = system_get_time();

		taskENTER_CRITICAL();
		Serialize_Address(remote_addr->sin_addr.s_addr,
				ntohs(remote_addr->sin_port), remote_addr_string, 50);
		taskEXIT_CRITICAL();

		connection_type = MESSAGE_TYPE_TCP;
	}

	return accepted_sock;
}

static bool ICACHE_RODATA_ATTR Initiate_Connection_For_Outgoing_Message()
{
	bool rval = false;
	Message * connection_message = NULL;

	taskYIELD();

	taskENTER_CRITICAL();
	//do not dequeue. leave the message in the queue to be processed by the send function..
	temp_msg_ptr = Peek_Message(&outgoing_tcp_message_queue);

	if (temp_msg_ptr != NULL)
	{
		connection_message = Create_Message();
		Set_Message_Type(connection_message, temp_msg_ptr->message_type);
		Set_Message_Source(connection_message, temp_msg_ptr->source);
		Set_Message_Destination(connection_message, temp_msg_ptr->destination);
		Set_Message_Content_Type(connection_message,
				temp_msg_ptr->content_type);
		Set_Message_Content(connection_message, temp_msg_ptr->content,
				temp_msg_ptr->content_length);

		connection_type = Get_Message_Type_From_Str(
				connection_message->message_type);
	}
	taskEXIT_CRITICAL();

	taskYIELD();

	if (temp_msg_ptr != NULL)
	{

		temp_msg_ptr = NULL;

		taskYIELD();

		if (connection_type == MESSAGE_TYPE_HTTP)
		{

			taskENTER_CRITICAL();
			char * start_of_uri = strchr(connection_message->destination,
					*http_uri_delimiter_fs);
			taskEXIT_CRITICAL();

			if (start_of_uri == NULL)
			{
				taskENTER_CRITICAL();
				start_of_uri = strchr(connection_message->destination,
						*http_uri_delimiter_bs);
				taskEXIT_CRITICAL();
			}

			if (start_of_uri != NULL)
			{
				*start_of_uri = '\0';
				taskENTER_CRITICAL();
				Deserialize_Address(connection_message->destination,
						&remote_address, ignored_message_type);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				memset(remote_address_string, 0, ADDR_STRING_SIZE);
				strncpy(remote_address_string, connection_message->destination,
						start_of_uri - connection_message->destination);
				taskEXIT_CRITICAL();
				rval = true;
			}
			else
			{
				taskENTER_CRITICAL();
				Deserialize_Address(connection_message->destination,
						&remote_address, ignored_message_type);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				sprintf(remote_address_string, connection_message->destination);
				taskEXIT_CRITICAL();
				rval = true;
			}
		}
		else
		{
			taskENTER_CRITICAL();
			Deserialize_Address(connection_message->destination,
					&remote_address, ignored_message_type);
			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			sprintf(remote_address_string, connection_message->destination);
			taskEXIT_CRITICAL();
			rval = true;
		}

		if (rval)
		{
			data_sock = Open_Data_Connection(&remote_address);

			taskYIELD();

			rval = data_sock > -1;
		}

		if (rval)
		{

			socklen_t sockaddr_size = sizeof(local_address);
			getsockname(data_sock, (struct sockaddr* )&local_address,
					&sockaddr_size);

			last_tcp_activity_time = system_get_time();

			taskYIELD();

			taskENTER_CRITICAL();
			Serialize_Address(local_address.sin_addr.s_addr,
					local_address.sin_port, local_address_string,
					ADDR_STRING_SIZE);
			taskEXIT_CRITICAL();
		}
		else
		{

			Message * m = Dequeue_Message(&outgoing_tcp_message_queue);
			if (m != NULL)
			{
				--outgoing_tcp_message_count;
				//couldn't connect. drop this message
				Delete_Message(m);
			}
		}

		if (connection_message != NULL)
		{
			Delete_Message(connection_message);
		}

		taskYIELD();
	}

	return rval;
}

//used to initiate connection.
static ICACHE_RODATA_ATTR int32 Open_Data_Connection(
		struct sockaddr_in * remote_addr)
{
	int opened_socket;

	opened_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (opened_socket != -1)
	{
		int retries = 0;
		int millis = CONNECT_TIMEOUT_ms;
		setsockopt(opened_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		taskYIELD();

		Connect_Task_Args connect_args =
		{ opened_socket, remote_addr, false };
		xTaskHandle connect_task_handle = NULL;
		while (connect_task_handle == NULL)
		{
			//start new task to connect

			//high water mark recorded as 28 bytes. Leaving this stack at 128 for safety.
			xTaskCreate(Connect_Task, "tcp connect task",
					configMINIMAL_STACK_SIZE, &connect_args,
					System_Get_Task_Priority(TASK_TYPE_TCP_TX),
					&connect_task_handle);

			if (connect_task_handle == NULL)
			{
				//raise priority so we make sure connect task gets cleaned up.
				xTaskHandle idle_handle = xTaskGetIdleTaskHandle();

				vTaskPrioritySet(idle_handle,
						System_Get_Task_Priority(TASK_TYPE_TCP_TX));
				vTaskDelay(250 / portTICK_RATE_MS);
				vTaskPrioritySet(idle_handle, 0);
			}
		}

		if (connect_task_handle != NULL)
		{
			uint32 connect_start_time_us = system_get_time();

			while (!connect_args.connected
					&& (system_get_time() - connect_start_time_us)
							< CONNECT_RETRY_TIME)
			{
				vTaskDelay(10 / portTICK_RATE_MS);
			}
		}

		if (connect_args.connected)
		{
			//task doesn't need to be deleted in this case. if we connected
			//		by now, then the task has deleted itself.

			millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
			setsockopt(opened_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
					sizeof(millis));
		}
		else
		{
			vTaskDelete(connect_task_handle);

			taskYIELD();

			vTaskPrioritySet(idle_handle,
					System_Get_Task_Priority(TASK_TYPE_TCP_TX));
			vTaskDelay(250 / portTICK_RATE_MS);
			vTaskPrioritySet(idle_handle, 0);

			lwip_close(opened_socket);
			opened_socket = -1;
		}
	}

	return opened_socket;
}

static ICACHE_RODATA_ATTR void Connect_Task(void * PvParams)
{
	((Connect_Task_Args*) PvParams)->connected =
			connect(((Connect_Task_Args* )PvParams)->socket,
					(struct sockaddr * )(((Connect_Task_Args* )PvParams)->address),
					sizeof(struct sockaddr_in)) == 0;

	vTaskDelete(NULL);
}

//send a message to the
static ICACHE_RODATA_ATTR bool Send_Message(int32 destination_socket,
		Message * m)
{
	if (m == NULL)
	{
		return true;
	}

	size_t length = 0;

	taskENTER_CRITICAL();
	bool rval = strstr(m->destination, remote_address_string) != NULL;
	taskEXIT_CRITICAL();

	if (rval)
	{
//		DEBUG_Print("match");

		if (connection_type == MESSAGE_TYPE_HTTP
				&& (m->content_length) <= MAXIMUM_MESSAGE_LENGTH - 19) //get adds on this much
		{
//			DEBUG_Print("http");

			taskENTER_CRITICAL();
			rval = Prepare_Http_Message(m);
			taskEXIT_CRITICAL();
		}
		else
		{
//			DEBUG_Print("tcp");

			taskENTER_CRITICAL();
			length = (size_t) Serialize_Message_Content(m, transmit_data,
			TRANSMIT_DATA_SIZE);
			taskEXIT_CRITICAL();

			rval = true;
		}

		if (rval)
		{
			taskYIELD();

			if (connection_type == MESSAGE_TYPE_HTTP)
			{
//				taskENTER_CRITICAL();
//				printf("send http to [%s] [%d] bytes: \r\n[%s]\r\n",
//						remote_address_string, m->content_length, m->content);
//				taskEXIT_CRITICAL();

				rval = lwip_write(destination_socket, m->content,
						m->content_length) == m->content_length;

//				taskENTER_CRITICAL();
//				printf("send of %d %s\r\n", m->content_length,
//						rval ? "ok" : "failed");
//				taskEXIT_CRITICAL();
			}
			else
			{
//				DEBUG_Print("send tcp");

				rval = lwip_write(destination_socket, transmit_data, length)
						== length;

//				taskENTER_CRITICAL();
//				printf("send of %d %s\r\n", m->content_length,
//						rval ? "ok" : "failed");
//				taskEXIT_CRITICAL();

			}

			taskYIELD();

			if (!rval)
			{
				int32 error = 0;
				uint32 optionLength = sizeof(error);
				int getReturn = lwip_getsockopt(destination_socket, SOL_SOCKET,
				SO_ERROR, &error, &optionLength);

//				taskENTER_CRITICAL();
//				printf("error: %d", error);
//				taskEXIT_CRITICAL();

				switch (error)
				{
				case ECONNRESET:
				{
					//we disconnected. return false.
					Data_Disconnect();
					break;
				}
				case EAGAIN:
				{
					rval = true;

					break;
				}
				default:
				{
					rval = true;
					break;
				}
				}
			}
			else
			{
				last_tcp_activity_time = system_get_time();
			}
		}

	}
	else
	{
		rval = true;
	}

	Delete_Message(m);

	return rval;
}

static bool ICACHE_RODATA_ATTR Dequeue_And_Transmit(int32 data_sock)
{
	bool rval = false;
	Message * message = NULL;

	taskENTER_CRITICAL();
	message = Dequeue_Message(&outgoing_tcp_message_queue);
	taskEXIT_CRITICAL();

	if (message != NULL)
	{
		--outgoing_tcp_message_count;
		taskYIELD();

		rval = Send_Message(data_sock, message);
	}
	else
	{
		//we have no reason to think we've been disconnected.
		rval = true;
	}

	return rval;
}

static bool ICACHE_RODATA_ATTR Receive_And_Enqueue(int32 data_sock)
{
	bool rval = true;
	uint32_t received_message_length = 0;
	Message * dequeued_message = NULL;

	taskENTER_CRITICAL();
	uint32_t rx_temp_buffer_size = tcp_rx_multibyte.max_count + 2; //add extra so we have room for null terminator.

	char * rx_temp_buffer = zalloc(rx_temp_buffer_size);
	uint32_t buffer_free = Multibyte_Ring_Buffer_Get_Free_Size(
			&tcp_rx_multibyte);
	taskEXIT_CRITICAL();

	taskYIELD();

	received_count = Receive(data_sock, rx_temp_buffer, buffer_free);

	taskENTER_CRITICAL();
	Multibyte_Ring_Buffer_Enqueue(&tcp_rx_multibyte, rx_temp_buffer,
			received_count);
	taskEXIT_CRITICAL();

	taskYIELD();

	if (tcp_rx_multibyte.count > 0)
	{
//		DEBUG_Print("rx data");

		if (connection_type == MESSAGE_TYPE_TCP)
		{
			//free, because the dequeue method below allocates into the pointer sent.
			free(rx_temp_buffer);
			rx_temp_buffer = NULL;

			taskENTER_CRITICAL();
			Multibyte_Ring_Buffer_Dequeue_Serialized_Message_Content(
					&tcp_rx_multibyte, &rx_temp_buffer);
			taskEXIT_CRITICAL();

			if (rx_temp_buffer != NULL)
			{
				taskENTER_CRITICAL();
				dequeued_message = Deserialize_Message_Content(rx_temp_buffer);
				taskEXIT_CRITICAL();
				free(rx_temp_buffer);
			}
		}
		else
		{
			//parse http message out of queue

			//		example message:
			//		HTTP/1.1 200 OK
			//		X-Powered-By: Express
			//		Content-Type: application/text; charset=utf-8
			//		Content-Length: 6
			//		ETag: W/"6-+nKcZrG+cjY967w8u/TfRA"
			//		Date: Sat, 30 Apr 2016 23:50:41 GMT
			//		Connection: keep-alive
			//
			//		130128

			//TODO: get the content_type out of here as well.
//			DEBUG_Print("http rx attempt");

			//dq until Content-Length:
			taskENTER_CRITICAL();
			uint32_t dequeued_count =
					Multibyte_Ring_Buffer_Dequeue_Until_String(
							&tcp_rx_multibyte, rx_temp_buffer,
							rx_temp_buffer_size, "Content-Length:");
			taskEXIT_CRITICAL();

			if (dequeued_count != 0)
			{
//				DEBUG_Print("cl");
				//dq until newline
				taskENTER_CRITICAL();
				memset(rx_temp_buffer, 0, rx_temp_buffer_size);
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				dequeued_count = Multibyte_Ring_Buffer_Dequeue_Until_String(
						&tcp_rx_multibyte, rx_temp_buffer, rx_temp_buffer_size,
						"\r\n");
				taskEXIT_CRITICAL();

				if (dequeued_count != 0)
				{
					//parse content-length value out of last parsed string
					taskENTER_CRITICAL();
					received_message_length = atoi(rx_temp_buffer);
//					printf("cl:%d", received_message_length);
					taskEXIT_CRITICAL();

					taskENTER_CRITICAL();
					dequeued_count = Multibyte_Ring_Buffer_Dequeue_Until_String(
							&tcp_rx_multibyte, rx_temp_buffer,
							rx_temp_buffer_size, "Connection:");
					taskEXIT_CRITICAL();

					//dq until Connection:
					if (dequeued_count != 0)
					{
//						DEBUG_Print("got connection");

						taskENTER_CRITICAL();
						//dq until \n\n
						dequeued_count =
								Multibyte_Ring_Buffer_Dequeue_Until_String(
										&tcp_rx_multibyte, rx_temp_buffer,
										rx_temp_buffer_size, "\r\n\r\n");
						taskEXIT_CRITICAL();

						if (dequeued_count != 0)
						{
//							DEBUG_Print("got doublenewlien");

							taskENTER_CRITICAL();
							dequeued_count = Multibyte_Ring_Buffer_Dequeue(
									&tcp_rx_multibyte, rx_temp_buffer,
									received_message_length);
							taskEXIT_CRITICAL();

							//dq content-length bytes.
							if (dequeued_count == received_message_length)
							{
//								DEBUG_Print("got message");

								taskENTER_CRITICAL();
								dequeued_message = Create_Message();
								Set_Message_Content_Type(dequeued_message,
										content_type_strings[CONTENT_TYPE_BINARY]);
								Set_Message_Content(dequeued_message,
										rx_temp_buffer,
										received_message_length);
								taskEXIT_CRITICAL();

								taskYIELD();
							}
						}
					}
				}
			}

			free(rx_temp_buffer);
		}
	}
	else
	{
//		DEBUG_Print("no rx data");
		free(rx_temp_buffer);
	}

	if (dequeued_message != NULL)
	{
		taskENTER_CRITICAL();
		Set_Message_Type(dequeued_message,
				message_type_strings[connection_type]);
		Set_Message_Source(dequeued_message, remote_address_string);
		Set_Message_Destination(dequeued_message, local_address_string);

		incoming_message_count = Queue_Message(&incoming_message_queue,
				dequeued_message);
//		DEBUG_Print("nq");

		taskEXIT_CRITICAL();

	}

	taskYIELD();

	if (received_count < 0)
	{
		Data_Disconnect();

		rval = false;
	}

	return rval;
}

static ICACHE_RODATA_ATTR int Receive(int32 source_socket, char * destination,
		uint32 receive_length_max)
{
	if (destination == NULL)
	{
		return 0;
	}

	int rval = lwip_recv(source_socket, destination, receive_length_max, 0);

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

	if (rval > 0)
	{
		last_tcp_activity_time = system_get_time();
	}

	return rval;
}

static void ICACHE_RODATA_ATTR Data_Disconnect()
{

	if (!opening_connection && (data_sock > -1))
	{
//		DEBUG_Print("data_disconnect");

		taskENTER_CRITICAL();
		Multibyte_Ring_Buffer_Reset(&tcp_rx_multibyte);
		taskEXIT_CRITICAL();

		shutdown(data_sock, 2);
		lwip_close(data_sock);
		data_sock = -1;
		connected = false;
	}
}

static void ICACHE_RODATA_ATTR Listen_Disconnect()
{
//	DEBUG_Print("listen_disconnect");

	if (listening || listen_sock > -1)
	{
		shutdown(listen_sock, 2);
		lwip_close(listen_sock);
		listen_sock = -1;
		listening = false;
	}
}

static bool ICACHE_RODATA_ATTR Check_Needs_Promotion()
{
	bool rval = false;

//	if (!opening_connection
//			&& (system_get_time() - last_tcp_activity_time)
//					> tcp_connection_timeout_us)
//	{
//		Data_Disconnect();
////		TCP_Combined_Deinit();
////
////		TCP_Combined_Init();
//	}

	//remain promoted until we empty the queue.
	taskENTER_CRITICAL();
	rval = (outgoing_tcp_message_count > 5
			|| Multibyte_Ring_Buffer_Get_Count(&tcp_rx_multibyte)
					> RECEIVE_BYTES_TRIGGER_LEVEL);
//	rval = (Multibyte_Ring_Buffer_Get_Count(&tcp_rx_multibyte)
//			> RECEIVE_BYTES_TRIGGER_LEVEL);
	taskEXIT_CRITICAL();

	promoted = rval;

	return rval;
}

uint8_t ICACHE_RODATA_ATTR *memchr2(uint8_t *ptr, uint8_t ch, size_t size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (*ptr == ch)
		{
			return ptr;
		}
		else
		{
			++ptr;
		}
	}

	return NULL;
}

static bool ICACHE_RODATA_ATTR TCP_Timeout_Check()
{
	bool rval = true;

	if ((system_get_time() - last_tcp_activity_time)
			> tcp_connection_timeout_us)
	{
		Data_Disconnect();
		rval = false;
	}

	return rval;
}

static bool ICACHE_RODATA_ATTR Prepare_Http_Message(Message * m)
{
	bool rval = false;
	char * start_of_uri;

	start_of_uri = strchr(m->destination, *http_uri_delimiter_fs);

	if (start_of_uri == NULL)
	{
		start_of_uri = strchr(m->destination, *http_uri_delimiter_bs);
	}

	if (start_of_uri != NULL)
	{
		m->content_length = sprintf(m->content, http_get_format, start_of_uri);

		rval = true;
	}

	return rval;
}
