/*
 * ref_code.c
 *
 *  Created on: Feb 23, 2016
 *      Author: thebh
 */

//this code was a UDP demo that would receive a message, send the message to the micro, and then take the micro's
//  output and send it back. It only works with up to 9 chars though.
#if 0
void uC_Interrupt_Handler()
{
   //set flag to say send the message to the uC if a message is waiting.
   //if message not waiting, set flag to stop rx interrupts and read message from the uC.
   //signal uC that we're ready to receive by setting GPIO line low again
//   printf("got the interrupt\r\n");
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

void GPIO_Init()
{
   ///setup GPIO and set output to 1.
   GPIO_AS_OUTPUT(BIT(0));
   GPIO_OUTPUT(BIT(0), 1);
   GPIO_AS_INPUT(BIT(2));

   //TODO: interrupts
//   _xt_isr_attach(ETS_GPIO_INUM, (_xt_isr) main_int_handler, NULL);
//   _xt_isr_unmask(1 << ETS_GPIO_INUM);
//
//   registerInterrupt(2, GPIO_PIN_INTR_NEGEDGE);
}

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

   LOCAL int32
   sock_fd;

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
      ret = bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
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
      setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &nNetTimeout, sizeof(int));
      fromlen = sizeof(struct sockaddr_in);
      ret = recvfrom(sock_fd, (uint8 *) udp_msg, UDP_DATA_LEN, 0, (struct sockaddr *) &from, (socklen_t *) &fromlen);
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
         sendto(sock_fd, (uint8*) txBuf, pendingTxBytes, 0, (struct sockaddr *) &lastFrom, fromlen);
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

void Serial_Receiver_State_Step()
{
	for (;;)
	{
		switch (State)
		{
		case Disable:
		{
			if (wifi_station_get_connect_status() == STATION_GOT_IP)
			{
				UART_ResetRxFifo(UART0);
				State = Idle;
			}
			break;
		}

		case Configure:
		{
			break;
		}

		case Idle:
		{
			if (!Serial_Tx_In_Progress && !GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
				Serial_Rx_In_Progress = true;

				Serial_Rx_Count = 0;
				UART_ResetRxFifo(UART0);
				BytesReceived = 0;
				Newline_Count = 0;
				Ring_Buffer_Init();

#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(0);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 0);
#endif
				stateTime = system_get_time();
				State = Receiving;
			}
			break;
		}

		case Receiving:
		{
			if(false){
//			if (Ring_Buffer_Has_Data())
//			{
//				Ring_Buffer_Get(Serial_Rx_Buffer);
//				printf("%c", *Serial_Rx_Buffer);

//				Ring_Buffer_Get(Serial_Rx_Buffer + BytesReceived);
//				printf("%d:'%c'\n", BytesReceived,
//						Serial_Rx_Buffer[BytesReceived]);
//
//				printf("1");
//				if (Serial_Rx_Buffer[BytesReceived++] == '\n')
//				{
////					printf("2\n");
//					++Newline_Count;
////					printf("3\n");
//				}
//				printf("4\n");
//
////				printf("newline:%d\n", Newline_Count);
////				printf("RxFifoIdx:%d\n", BytesReceived);
//
				if (Newline_Count >= CLAY_SERIAL_MESSAGE_NEWLINE_COUNT)
				{
					printf("enough newlines\n\n");

					//TODO: update message_init to not require null termination?
					Serial_Rx_Buffer[++BytesReceived] = '\0';

					Serial_Rx_In_Progress = false;

#if(CLAY_INTERRUPT_OUT_PIN == 16)
					gpio16_output_set(1);
#else
					GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif
					State = Parsing;
				}
			}
			else if (system_get_time() - stateTime > 1000000) //GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN)) //state transition
			{
#if(CLAY_INTERRUPT_OUT_PIN == 16)
				gpio16_output_set(1);
#else
				GPIO_OUTPUT(BIT(CLAY_INTERRUPT_OUT_PIN), 1);
#endif

				Serial_Rx_In_Progress = false;
				State = Idle;
			}
			break;
		}

		case Parsing:
		{
			printf("parsing\n");
			tempContent = strtok(Serial_Rx_Buffer, &Newline);

			printf("content: [%s]\n", tempContent);

			tempAddr = strtok(NULL, &Newline);

			printf("addr: [%s]\n", tempAddr);

			if (tempContent != NULL && tempAddr != NULL)
			{
				printf("not null, init message\n");
				Initialize_Message(&tempMsg, tempAddr, tempAddr, tempContent);
				printf("init message done\n");
			}

//			printf("queue message \n");
			WAIT_FOR_OUTGOING_QUEUE();
			Queue_Message(&outgoingMessageQueue, &tempMsg);
			RELEASE_OUTGOING_QUEUE();

			printf("queue message done, go to idle.\n\n\n");

			while (GPIO_INPUT_GET(CLAY_INTERRUPT_IN_PIN))
				;

			State = Idle;

			break;
		}

		case UDP_STATE_MAX:
		default:
		{
			break;
		}
		}

		//this delay matches the timeout interrupt delay (tout) we set in uart.c
//		vTaskDelay(2 / portTICK_RATE_MS);
	}
}

#endif
