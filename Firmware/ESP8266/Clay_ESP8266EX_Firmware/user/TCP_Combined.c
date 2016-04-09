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

#include "TCP_Combined.h"
#include "Message_Queue.h"
#include "Message.h"
#include "AddressSerialization.h"
#include "Priority_Manager.h"

////Macros ////////////////////////////////////////////////////////
#define DATA_CONNECT_ATTEMPT_MAX 		10
#define RECEIVE_DATA_SIZE				1024
#define TRANSMIT_DATA_SIZE				256
#define LOCAL_TCP_PORT					1002
#define ADDR_STRING_SIZE 				50
#define CONNECT_TIMEOUT_ms				100
#define LISTEN_TIMEOUT_ms				100
#define CONNECT_ATTEMPT_MAX				10

#define MESSAGE_TRIGGER_LEVEL			10

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////
static int32 listen_sock;
static int32 data_sock;

static int32 received_count;

static int32 current_outgoing_fail_count;

static bool connected;
static bool promoted;

static char *receive_data;
static char *transmit_data;
static char *message_ptr;

static char * local_address_string;
static char * remote_address_string;

struct sockaddr_in local_address;
struct sockaddr_in remote_address;

static Message temp_message;
static Message * temp_message_ptr;
static Message_Type * ignored_message_type;

static int receive_head;
static int receive_tail;
static int receive_size;

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
static int32 Receive(int32 source_socket, char * message,
		uint32 message_length_max);

static bool Check_Needs_Promotion();
static uint8_t * memchr2(uint8_t * ptr, uint8_t ch, size_t size);

////Global implementations ////////////////////////////////////////
bool ICACHE_RODATA_ATTR TCP_Combined_Init()
{
	bool rval = true;
	promoted = false;

	taskENTER_CRITICAL();
	local_address_string = zalloc(ADDR_STRING_SIZE);
	remote_address_string = zalloc(ADDR_STRING_SIZE);
	receive_data = zalloc(RECEIVE_DATA_SIZE);
	transmit_data = zalloc(TRANSMIT_DATA_SIZE);
	taskEXIT_CRITICAL();

	taskYIELD();

	xTaskHandle TCP_combined_handle;

	//TODO: print high water mark and revise stack size if necessary.
	xTaskCreate(TCP_Combined_Task, "TCPall_1", 600, NULL,
			Get_Task_Priority(TASK_TYPE_TCP_RX), TCP_combined_handle);

	Register_Task(TASK_TYPE_TCP_RX, TCP_combined_handle, Check_Needs_Promotion);

	return rval;
}

void ICACHE_RODATA_ATTR TCP_Combined_Deinit()
{
	connected = false;

	lwip_close(data_sock);
	lwip_close(listen_sock);

	listen_sock = -1;
	data_sock = -1;

	free(local_address_string);
	free(remote_address_string);
	free(receive_data);
	free(transmit_data);

	Stop_Task(TASK_TYPE_TCP_RX);
}

void ICACHE_RODATA_ATTR TCP_Combined_Task()
{
	for (;;)
	{
		connected = false;
		current_outgoing_fail_count = 0;

		//open listener
		while ((listen_sock = Open_Listen_Connection(local_address_string,
				&local_address)) < 0)
		{
			Priority_Check(TASK_TYPE_TCP_RX);

			//TODO: we may need to be able to initiate a connection and send from here
			taskYIELD();
		}

		//listen for incoming connection, start a connection if we have an outgoing message.
		while (!connected)
		{
			data_sock = Listen(listen_sock, remote_address_string,
					&remote_address);
			connected = data_sock > -1;

			Priority_Check(TASK_TYPE_TCP_RX);

			if (!connected)
			{
				connected = Initiate_Connection_For_Outgoing_Message();
			}

			taskYIELD();
		}

		receive_head = 0;
		receive_tail = 0;
		receive_size = 0;

		while (connected)
		{
			//Dequeue_And_Transmit will not disconnect, but Receive_And_Enqueue
			//	may, so we capture that return to exit the loop.

			Priority_Check(TASK_TYPE_TCP_RX);

			Dequeue_And_Transmit(data_sock);
			connected = Receive_And_Enqueue(data_sock);

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

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_socket > -1)
	{
		/* Bind to the local port */
		bind_result = lwip_bind(listen_socket, (struct sockaddr *) local_addr,
				sizeof(*local_addr));

		if (bind_result != 0)
		{
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

	if (listen_socket > -1)
	{
		listen_result = lwip_listen(listen_socket, TCP_MAX_CONNECTIONS);

		if (listen_result != 0)
		{
			lwip_close(listen_socket);
			listen_socket = -1;
		}
	}

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

		taskENTER_CRITICAL();
		Serialize_Address(remote_addr->sin_addr.s_addr,
				ntohs(remote_addr->sin_port), remote_addr_string, 50);
		taskEXIT_CRITICAL();
	}

	return accepted_sock;
}

static bool Initiate_Connection_For_Outgoing_Message()
{
	bool rval = false;

	taskENTER_CRITICAL();
//do not dequeue. leave the message in the queue to be processed below.
	temp_message_ptr = Peek_Message(&outgoing_TCP_message_queue);

	if (temp_message_ptr != NULL)
	{
		Initialize_Message(&temp_message, temp_message_ptr->type,
				temp_message_ptr->source, temp_message_ptr->destination,
				temp_message_ptr->content);
	}
	taskEXIT_CRITICAL();

	if (temp_message_ptr != NULL)
	{
		temp_message_ptr = NULL;

		taskENTER_CRITICAL();
		Deserialize_Address(temp_message.destination, &remote_address,
				ignored_message_type);
		taskEXIT_CRITICAL();

		sprintf(remote_address_string, temp_message.destination);

		data_sock = Open_Data_Connection(&remote_address);

		rval = data_sock > -1;

		if (rval)
		{
			socklen_t sockaddr_size = sizeof(local_address);
			getsockname(data_sock, (struct sockaddr* )&local_address,
					&sockaddr_size);

			Serialize_Address(local_address.sin_addr.s_addr,
					local_address.sin_port, local_address_string,
					ADDR_STRING_SIZE);
		}
		else
		{
			//couldn't connect. drop this message
			if (++current_outgoing_fail_count > CONNECT_ATTEMPT_MAX)
			{
				Dequeue_Message(&outgoing_TCP_message_queue);
				current_outgoing_fail_count = 0;
			}
		}

	}

	return rval;
}

//used to initiate connection.
static ICACHE_RODATA_ATTR int32 Open_Data_Connection(
		struct sockaddr_in * remote_addr)
{
	int opened_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (opened_socket != -1)
	{
		int millis = CONNECT_TIMEOUT_ms;
		setsockopt(opened_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
				sizeof(millis));

		if (connect(opened_socket, (struct sockaddr * )(remote_addr),
				sizeof(struct sockaddr_in)) == 0)
		{
			millis = TCP_RECEIVE_CONNECTION_TIMEOUT_ms;
			setsockopt(opened_socket, SOL_SOCKET, SO_RCVTIMEO, &millis,
					sizeof(millis));

			//send timeout not supported in ESP8266
//			setsockopt(opened_socket, SOL_SOCKET, SO_SNDTIMEO, &millis,
//					sizeof(millis));
		}
		else
		{
			int32 error = 0;
			uint32 optionLength = sizeof(error);
			int getReturn = lwip_getsockopt(opened_socket, SOL_SOCKET, SO_ERROR,
					&error, &optionLength);

			lwip_close(opened_socket);
			opened_socket = -1;
		}
	}

	return opened_socket;
}

//send a message to the
static ICACHE_RODATA_ATTR bool Send_Message(int32 destination_socket,
		Message * m)
{
	bool rval = false;
	struct sockaddr_in message_dest;

	taskENTER_CRITICAL();
	Deserialize_Address(m->destination, &message_dest, ignored_message_type);
	taskEXIT_CRITICAL();

	if (message_dest.sin_addr.s_addr == remote_address.sin_addr.s_addr
			&& message_dest.sin_port == remote_address.sin_port)
	{

		taskENTER_CRITICAL();
		size_t length = (size_t) (strlen(m->content) + 1);
		taskEXIT_CRITICAL();

		//this blocks forever. why?
		rval = lwip_write(destination_socket, m->content, length) == length;
	}

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

static bool Dequeue_And_Transmit(int32 data_sock)
{
	bool rval = false;

	if (Peek_Message(&outgoing_TCP_message_queue) != NULL)
	{
		taskENTER_CRITICAL();
		temp_message_ptr = Dequeue_Message(&outgoing_TCP_message_queue);
		taskEXIT_CRITICAL();

		rval = Send_Message(data_sock, temp_message_ptr);

		free(temp_message_ptr);   //dequeue alloc's a message.
		temp_message_ptr = NULL;
	}

	return rval;
}

static bool Receive_And_Enqueue(int32 data_sock)
{
	bool rval = true;

	//offset into receive_data based on
	received_count = Receive(data_sock, receive_data + receive_tail,
			(RECEIVE_DATA_SIZE - receive_size));

//	taskENTER_CRITICAL();
//	printf("rx c%d,h%d,t%d,s%d\r\n", received_count, receive_head, receive_tail,
//			receive_size);
//	taskEXIT_CRITICAL();

	if (received_count > 0 || (receive_size > 0 && received_count > -1))
	{
		receive_tail = (receive_tail + received_count) % RECEIVE_DATA_SIZE;
		receive_size += received_count;

//		taskENTER_CRITICAL();
//		printf("hd c%d,h%d,t%d,s%d\r\n", received_count, receive_head,
//				receive_tail, receive_size);
//		taskEXIT_CRITICAL();

		taskENTER_CRITICAL();
		message_ptr = memchr2(receive_data + receive_head, message_delimiter[0],
				(RECEIVE_DATA_SIZE - receive_size));
		taskEXIT_CRITICAL();

		//if we didn't find the end and the tail is before the head of the queue, look up until the tail.
		if (message_ptr == NULL
				&& (receive_tail < receive_head
						|| (receive_tail == receive_head
								&& receive_size == RECEIVE_DATA_SIZE)))
		{
			taskENTER_CRITICAL();
			message_ptr = memchr2(receive_data, message_delimiter[0],
					receive_tail);
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("wa c%d,h%d,t%d,s%d\r\n", received_count, receive_head,
//					receive_tail, receive_size);
//			taskEXIT_CRITICAL();

			if (message_ptr != NULL)
			{
//				taskENTER_CRITICAL();
//				printf("fm c%d,h%d,t%d,s%d\r\n", received_count, receive_head,
//						receive_tail, receive_size);
//				taskEXIT_CRITICAL();

				*message_ptr = '\0';
				char * swap = zalloc(strlen(message_ptr) + 1);
				strcpy(swap, receive_data);
				strncpy(receive_data, receive_data + receive_head,
				RECEIVE_DATA_SIZE - receive_head + 1);
				strcat(receive_data, swap);
				free(swap);

				receive_head = 0;
				receive_tail = (strlen(receive_data) + 1);
				receive_size = receive_tail;

				message_ptr = receive_data;
			}
			else if (receive_size == RECEIVE_DATA_SIZE)
			{
				//buffer's full and no terminator was found.
				receive_head = 0;
				receive_tail = 0;
				receive_size = 0;
			}
		}
		else if (message_ptr != NULL)
		{
			*message_ptr = '\0';
			message_ptr = receive_data + receive_head;
		}

		if (message_ptr != NULL)
		{
			taskENTER_CRITICAL();
			receive_size -= strlen(message_ptr);
			receive_head = (receive_head + strlen(message_ptr))
					% RECEIVE_DATA_SIZE;
			taskEXIT_CRITICAL();

//			taskENTER_CRITICAL();
//			printf("po c%d,h%d,t%d,s%d\r\n", received_count, receive_head,
//					receive_tail, receive_size);
//			taskEXIT_CRITICAL();

			taskENTER_CRITICAL();
			Initialize_Message(&temp_message,
					message_type_strings[MESSAGE_TYPE_TCP],
					remote_address_string, local_address_string, message_ptr);
			taskEXIT_CRITICAL();

			taskYIELD();

			taskENTER_CRITICAL();
			Queue_Message(&incoming_message_queue, &temp_message);
			taskEXIT_CRITICAL();
		}
	}
	else if (received_count < 0)
	{
		//Assume tcp queue has messages for the open socket. We clear
		//	it so we don't waste a bunch of cpu trying to reopen the
		//	connection.

		taskENTER_CRITICAL();
		Initialize_Message_Queue(&outgoing_TCP_message_queue);
		taskEXIT_CRITICAL();

		lwip_close(data_sock);
		lwip_close(listen_sock);

		listen_sock = -1;
		data_sock = -1;

		rval = false;
	}

	return rval;

}

static int loops = 0;

static bool Check_Needs_Promotion()
{
	bool rval = false;

//remain promoted until we empty the queue.
	taskENTER_CRITICAL();
	rval = outgoing_TCP_message_queue.count
			> (promoted ? 0 : MESSAGE_TRIGGER_LEVEL);
	taskEXIT_CRITICAL();

//	if (++loops > LOOPS_BEFORE_PRINT || outgoing_TCP_message_queue.count)
//	{
//		loops = 0;
//		taskENTER_CRITICAL();
//		printf("tcp count:%d\r\n", outgoing_TCP_message_queue.count);
//		taskEXIT_CRITICAL();
//
//		portENTER_CRITICAL();
//		UART_WaitTxFifoEmpty();
//		portEXIT_CRITICAL();
//	}

	promoted = rval;

	return rval;
}

uint8_t *memchr2(uint8_t *ptr, uint8_t ch, size_t size)
{
	int i;
	for (i = 0; i < size; i++)
		if (*ptr++ == ch)
			return ptr;
	return NULL;
}
