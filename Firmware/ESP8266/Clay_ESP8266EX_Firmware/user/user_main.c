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
#include "GPIO.h"
#include "UART.h"

#include "Serial_Receiver.h"
#include "Serial_Transmitter.h"
#include "UDP_Receiver.h"
#include "UDP_Transmitter.h"
#include "TCP_Receiver.h"
#include "TCP_Transmitter.h"

#include "Message_Queue.h"

#define server_ip "192.168.101.142"
#define server_port 9669

#define UDP_LOCAL_PORT 1200
#define UDP_DATA_LEN   100
#define MAX_PINS       3

#define RX_BUF_SIZE    UDP_DATA_LEN
#define TX_BUF_SIZE    100

void uC_Interrupt_Handler()
{
	printf("got the interrupt\r\n");
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

//TODO: still need to be able to set the SSID and PW.
//void Signal_Power_On_Complete()
//{
//	UART_SetPrintPort(UART1);
//	//wait for wifi to connect, then
//	while (wifi_station_get_connect_status() != STATION_GOT_IP)
//	{
//		vTaskDelay(500 / portTICK_RATE_MS);
//	}
//
//	gpio16_output_set(0);
//	vTaskDelay(500 / portTICK_RATE_MS);
//	gpio16_output_set(1);
//
//	UART_SetPrintPort(UART0);
//
//	vTaskDelete(NULL);
//}

void GPIO_Init()
{
	///setup GPIO and set output to 1.
#if CLAY_INTERRUPT_OUT_PIN == 16
	gpio16_output_conf();
	gpio16_output_set(1);
#else
	GPIO_AS_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN));
	GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

	GPIO_AS_INPUT(BIT(CLAY_INTERRUPT_IN_PIN));

//	registerInterrupt(CLAY_INTERRUPT_IN_PIN, GPIO_PIN_INTR_NEGEDGE);
//	_xt_isr_attach(ETS_GPIO_INUM, (_xt_isr) main_int_handler, NULL);
//	_xt_isr_unmask(1 << ETS_GPIO_INUM);
}

void wifi_handle_event_cb(System_Event_t *evt)
{
//	os_printf("event %x\n", evt->event_id);
	switch (evt->event_id)
	{
	case EVENT_STAMODE_CONNECTED:
//		os_printf("connect to ssid %s, channel %d\n",
//				evt->event_info.connected.ssid,
//				evt->event_info.connected.channel);
		break;
	case EVENT_STAMODE_DISCONNECTED:
//		os_printf("disconnect from ssid %s, reason %d\n",
//				evt->event_info.disconnected.ssid,
//				evt->event_info.disconnected.reason);
		break;
	case EVENT_STAMODE_AUTHMODE_CHANGE:
//		os_printf("mode: %d -> %d\n", evt->event_info.auth_change.old_mode,
//				evt->event_info.auth_change.new_mode);
		break;
	case EVENT_STAMODE_GOT_IP:
//		os_printf("ip:" IPSTR ",mask:" IPSTR ",gw:" IPSTR,
//				IP2STR(&evt->event_info.got_ip.ip),
//				IP2STR(&evt->event_info.got_ip.mask),
//				IP2STR(&evt->event_info.got_ip.gw));
//		os_printf("\n");
		UDP_Transmitter_Init();
		UDP_Receiver_Init();
		Serial_Receiver_Init();
		Serial_Transmitter_Init();

		//TCP todo's
		//TODO: on send, have flag for close after send
		TCP_Transmitter_Init();
		TCP_Receiver_Init();
		break;
	case EVENT_SOFTAPMODE_STACONNECTED:
//		os_printf("station: " MACSTR "join, AID = %d\n",
//				MAC2STR(evt->event_info.sta_connected.mac),
//				evt->event_info.sta_connected.aid);
		break;
	case EVENT_SOFTAPMODE_STADISCONNECTED:
//		os_printf("station: " MACSTR "leave, AID = %d\n",
//				MAC2STR(evt->event_info.sta_disconnected.mac),
//				evt->event_info.sta_disconnected.aid);
		break;
	default:
		break;
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
	GPIO_Init();

#if 0
	printf("SDK version:%s\n", system_get_sdk_version());
#endif
	/* need to set opmode before you set config */
	wifi_set_opmode(STATIONAP_MODE);
	uart_init_new();

#if 0
	Message_Conversion_Test();
#endif

	{
		struct station_config *config = (struct station_config *) zalloc(
				sizeof(struct station_config));
//      sprintf(config->ssid, "hefnetm");
//      sprintf(config->password, "dips00BOYNEdo$!&");

		sprintf(config->ssid, "hefnet");
		sprintf(config->password, "h3fn3r_is_better_than_me");

		/* need to sure that you are in station mode first,
		 * otherwise it will be failed. */
		wifi_station_set_config(config);
		free(config);
	}

//uncomment to generate an interrupt when we connect to the AP.
//	xTaskCreate(Signal_Power_On_Complete, "power_on_signal", 256, NULL, 2, NULL);
	//Set up our event handler from above. this starts the tasks that talk over WiFi.
	wifi_set_event_handler_cb(wifi_handle_event_cb);
}

