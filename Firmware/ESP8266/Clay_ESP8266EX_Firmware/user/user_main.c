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

#include "../include/AddressSerialization.h"
#include "../include/CommandParser.h"
#include "GPIO.h"
#include "UART.h"

#include "Serial_Receiver.h"
#include "Serial_Transmitter.h"
#include "UDP_Receiver.h"
#include "UDP_Transmitter.h"
#include "TCP_Combined.h"
#include "TCP_Receiver.h"
#include "TCP_Transmitter.h"
#include "Message_Queue.h"

//#include "user_interface.h"
//#include "eagle_soc.h"
#include "stdint.h"
#include "c_types.h"
//#include "ets_sys.h"
#include "stdarg.h"

void ICACHE_FLASH_ATTR registerInterrupt(int pin, GPIO_INT_TYPE mode,
		_xt_isr handler);
void ICACHE_RODATA_ATTR GPIO_Init();
void ICACHE_RODATA_ATTR wifi_handle_event_cb(System_Event_t *evt);
void Master_Interrupt_Handler(void * arg);
void Run_Queue_Test();

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_RODATA_ATTR user_init(void)
{
	// TODO: how do we stop the debug messages in the RTOS SDK?
//	system_set_os_print(0);

	GPIO_Init();

	printf("SDK version:%s\n", system_get_sdk_version());
	/* need to set opmode before you set config */
	wifi_set_opmode(STATIONAP_MODE);

	uart_init_new();

#if 0
	Message_Conversion_Test();
#endif

	{
		taskENTER_CRITICAL();
		struct station_config *config = (struct station_config *) zalloc(
				sizeof(struct station_config));
		taskEXIT_CRITICAL();

		sprintf(config->ssid, "hefnet");
		sprintf(config->password, "h3fn3r_is_better_than_me");

		/* need to sure that you are in station mode first,
		 * otherwise it will be failed. */
		wifi_station_set_config(config);
		free(config);
	}
//added to allow 3+ TCP connections per ESP RTOS SDK API Reference 1.3.0 Chapter 1, page 2
	TCP_WND = 2 * TCP_MSS;

#if 0
	xTaskCreate(Run_Queue_Test, "power_on_signal", 256, NULL, 2, NULL);
#endif

#if 1
	//set up our callback handler. this will start the networking tasks on connect.
	wifi_set_event_handler_cb(wifi_handle_event_cb);

	Start_System_Monitor();

	//these state machines should be started immediately so that we
	//		can process instructions from the micro.
#if ENABLE_SERIAL_RX
	Serial_Receiver_Init();
#endif

#if ENABLE_SERIAL_TX
	Serial_Transmitter_Init();
#endif

#if ENABLE_COMMAND_PARSER
	Command_Parser_Init();
#endif
#endif

	//TODO: wait for uC to respond to this. Probably means another task. "start device wifi" Don't even connect until we get the message.
	Send_Startup_Message();
}

void ICACHE_FLASH_ATTR registerInterrupt(int pin, GPIO_INT_TYPE mode,
		_xt_isr handler)
{
	portENTER_CRITICAL();

	GPIO_AS_INPUT(BIT(pin));

	//clear interrupt status
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(pin));

	// set the mode
	gpio_pin_intr_state_set(GPIO_ID_PIN(pin), mode);

	_xt_isr_attach(ETS_GPIO_INUM, handler, NULL);
	_xt_isr_unmask(1 << ETS_GPIO_INUM);

	portEXIT_CRITICAL();
}

void Master_Interrupt_Handler(void * args)
{
	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS,
			gpio_status & BIT(CLAY_INTERRUPT_IN_PIN));
	master_interrupt_received = true;
}

void ICACHE_RODATA_ATTR GPIO_Init()
{
	///setup GPIO and set output to 1.
#if CLAY_INTERRUPT_OUT_PIN == 16
	gpio16_output_conf();
	gpio16_output_set(1);
#else
	GPIO_AS_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN));
	GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

	registerInterrupt(CLAY_INTERRUPT_IN_PIN, GPIO_PIN_INTR_NEGEDGE,
			Master_Interrupt_Handler);
}

void wifi_handle_event_cb(System_Event_t *evt)
{
//	os_printf("event %x\n", evt->event_id);
	switch (evt->event_id)
	{
	case EVENT_STAMODE_CONNECTED:
	{
//		os_printf("connect to ssid %s, channel %d\n",
//				evt->event_info.connected.ssid,
//				evt->event_info.connected.channel);
		break;
	}
	case EVENT_STAMODE_DISCONNECTED:
	{
//		os_printf("disconnect from ssid %s, reason %d\n",
//				evt->event_info.disconnected.ssid,
//				evt->event_info.disconnected.reason);

		Get_Wifi_Status_Command(NULL);
		break;
	}
	case EVENT_STAMODE_AUTHMODE_CHANGE:
	{
//		os_printf("mode: %d -> %d\n", evt->event_info.auth_change.old_mode,
//				evt->event_info.auth_change.new_mode);
		break;
	}
	case EVENT_STAMODE_GOT_IP:
	{
#if ENABLE_UDP_SENDER
		UDP_Transmitter_Init();
#endif

#if ENABLE_UDP_RECEIVER
		UDP_Receiver_Init();
#endif

#if ENABLE_TCP_SENDER
		TCP_Transmitter_Init();
#endif

#if ENABLE_TCP_RECEIVER
		TCP_Receiver_Init();
#endif

#if ENABLE_TCP_COMBINED_TX || ENABLE_TCP_COMBINED_RX
		TCP_Combined_Init();
#endif

		Get_Wifi_Status_Command(NULL);
		Get_IP_Command(NULL);

		break;
	}
	case EVENT_SOFTAPMODE_STACONNECTED:
	{
//		os_printf("station: " MACSTR "join, AID = %d\n",
//				MAC2STR(evt->event_info.sta_connected.mac),
//				evt->event_info.sta_connected.aid);
		break;
	}
	case EVENT_SOFTAPMODE_STADISCONNECTED:
	{
//		os_printf("station: " MACSTR "leave, AID = %d\n",
//				MAC2STR(evt->event_info.sta_disconnected.mac),
//				evt->event_info.sta_disconnected.aid);
		break;
	}
	default:
	{
		break;
	}
	}
}

#if 0
static Message temp_message;
static Message dequeued_message;

static int i;
static int current_max;
static int message_counter;

static bool dequeue_ok;

static char type_str[] = "tcp";
static char dest_addr[] = "192.168.1.3:1002";
static char source_addr[] = "192.168.1.21:1002";
static char message_content_template[] =
"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm%d";
static char message_content[256];

void Run_Queue_Test()
{
	message_counter = 0;
	current_max = 1;

	taskENTER_CRITICAL();
	Initialize_Message_Queue(&incoming_message_queue);
	taskEXIT_CRITICAL();

	for (;;)
	{
		for (i = 0;
				(i
						< ((current_max == MAXIMUM_MESSAGE_COUNT) ?
								current_max * 20 : current_max)); ++i)
		{
			taskENTER_CRITICAL();
			sprintf(message_content, message_content_template,
					++message_counter);
			taskEXIT_CRITICAL();

			taskYIELD();

			taskENTER_CRITICAL();
			Initialize_Message(&temp_message, type_str, source_addr, dest_addr,
					message_content);
			taskEXIT_CRITICAL();

			taskYIELD();

			taskENTER_CRITICAL();
			printf("nq:%s,%s,%s,%s\r\n", temp_message.type, temp_message.source,
					temp_message.destination, temp_message.content);
			Queue_Message(&incoming_message_queue, &temp_message);
//			UART_WaitTxFifoEmpty(UART0);
			taskEXIT_CRITICAL();
			taskYIELD();
		}

		taskENTER_CRITICAL();
		printf("nq'd %d. queue size: %d\r\n", current_max,
				incoming_message_queue.count);
		taskEXIT_CRITICAL();
		taskYIELD();

		for (i = 0;
				(i
						< ((current_max == MAXIMUM_MESSAGE_COUNT) ?
								current_max * 20 : current_max)); ++i)
		{
			taskENTER_CRITICAL();
			dequeue_ok = Dequeue_Message(&incoming_message_queue,
					&dequeued_message);
			taskEXIT_CRITICAL();
			if (dequeue_ok)
			{
				taskENTER_CRITICAL();
				printf("dq:%s,%s,%s,%s\r\n", dequeued_message.type,
						dequeued_message.source, dequeued_message.destination,
						dequeued_message.content);
//				UART_WaitTxFifoEmpty(UART0);
				taskEXIT_CRITICAL();

				taskYIELD();
			}
			else
			{
				DEBUG_Print("no data");
			}

			taskYIELD();
		}

		taskENTER_CRITICAL();
		printf("dq'd %d\r\n", current_max);
		taskEXIT_CRITICAL();
		taskYIELD();

		current_max = ((current_max + 1) % (MAXIMUM_MESSAGE_COUNT + 1));
	}
}
#endif
