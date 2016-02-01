/*
 * meshTest.c
 *
 *  Created on: Dec 22, 2015
 *      Author: Ben
 */

///includes /////////////////////////////////////////////////////////
#include "MeshTest.h"
#include "Mesh.h"
#include "wirish.h"
#include "mesh_stastistics.h"

extern "C"{
#include "Clock.h"
#include "mpu_9250_driver.h"
#include "LED1.h"
#include "LED2.h"
#include "PE_Types.h"
#include "RHRouter.h"
#include "RGB_LED.h"
}

///defines /////////////////////////////////////////////////////////
#if(ADDRESS_1 || ADDRESS_2 || ADDRESS_3)
#define TRANSMIT                1
#else
#define TRANSMIT                0
#endif

///local vars //////////////////////////////////////////////////////
static uint32_t mode_start_time = 0;
static uint8_t mesh_mode = 0;
static uint8_t rx_led_toggle = 0;

static uint8_t hb_led_count = 0;

uint8_t last_tx_return_value;

static uint32_t size = sizeof(mpu_values) - 2;
static mpu_values local_imu_data =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static mpu_values remote_imu_data =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#if ENABLE_DIAGNOSTIC_LED
static Color_RGB colors[] =
{
	{	LED_MODE_OFF, LED_MODE_OFF, LED_MODE_OFF},        //off 0
	{	LED_MODE_MED, LED_MODE_MED, LED_MODE_OFF},        //rg 1
	{	LED_MODE_OFF, LED_MODE_MED, LED_MODE_MED},        //gb 2
	{	LED_MODE_MED, LED_MODE_OFF, LED_MODE_MED},        //rb 3
	{	LED_MODE_MED, LED_MODE_OFF, LED_MODE_OFF},        //r 4
	{	LED_MODE_OFF, LED_MODE_MED, LED_MODE_OFF},        //g 5
	{	LED_MODE_OFF, LED_MODE_OFF, LED_MODE_MED},        //b 6
};
#endif

static int target_address = 2;
static uint32_t tx_start;
static uint32_t tx_time;
static bool Initialized = FALSE;

///prototypes //////////////////////////////////////////////////////
static void update_imu_leds(const mpu_values * remote_imu_data, Color_RGB colors[]);
static void upcount_hb_leds();
static void update_mesh_mode(uint8_t * data, uint8_t len);
static void mesh_update_imu_leds(uint8_t * data, uint8_t len);
static void complete_experiment_and_send();

extern "C"
{
void MeshTestLoop()
{
//	Enable_LEDs();
//
//	Enable_Clock();
//	Start_Clock();
	upcount_hb_leds();

//	Enable_PCA9552();
	upcount_hb_leds();

//	Start_MPU9250();
	upcount_hb_leds();

	mesh_init();
	mesh_register_callback(MESH_CMD_UPDATE_IMU_DATA, mesh_update_imu_leds);
	mesh_register_callback(MESH_CMD_CHANGE_MESH_MODE, update_mesh_mode);

	upcount_hb_leds();

	//mesh diagnostic LEDs.
	// TX
	//     rgb 4 is green when last tx was successful, red if not.
	//     rgb 5 shows last address sent to. red when last sent to address 1, green when last sent to 2, blue when last sent to 3
	// RX
	//     led 1 is toggled when an IMU update message is received
	//     rgb 1 is red when address 1 sent the last message, green when address 2, blue when address 3
	//     rgb 7 is green when the NRF driver is receiving a message in the 'available' method.
	//     rgb 8 is blue when no message received, green when message received
	//     rgb 9 is blue when last received message was address broadcast, green when it was application message.
	//     rgb 11 is green when last node search message was direct, blue when indirect, and is only updated when this board was the target of the search
	//     rgb 12 is whether the received node search message was for this node or for another node. green means for this node, blue means another

	//used to make sure these variables get initialized. they'll never be accessed otherwise.

	start_time = Millis();
	setup_next_experiment();

	for (;;)
	{
		MeshTestLoopStep();
		if (tick_1ms)
		{
			tick_1ms = FALSE;
		}

		if (tick_250ms)
		{
			tick_250ms = FALSE;
		}

		if (tick_500ms)
		{
			tick_500ms = FALSE;
			upcount_hb_leds();
		}
	}
}

void MeshTestLoopStep()
{
	if (!Initialized)
	{
		Start_Mesh();
		mesh_register_callback(MESH_CMD_UPDATE_IMU_DATA, mesh_update_imu_leds);
		mesh_register_callback(MESH_CMD_CHANGE_MESH_MODE, update_mesh_mode);
		Initialized = TRUE;
	}

	if ((experiment_data.settings.message_transmission_count && transmissions_sent_for_this_experiment >= experiment_data.settings.message_transmission_count) || (experiment_data.settings.experiment_duration_ms && (Millis() - start_time) >= experiment_data.settings.experiment_duration_ms))
	{
		send_data_and_setup_next_experiment();
	}

	mesh_process_commands();

#if TRANSMIT
	if ((Millis() - mode_start_time) > (experiment_data.settings.mesh_tx_period_max_ms ? random(experiment_data.settings.mesh_tx_period_min_ms, experiment_data.settings.mesh_tx_period_max_ms) : experiment_data.settings.mesh_tx_period_min_ms))
	{
		mode_start_time = Millis();

		//update the target address
#if ADDRESS_3 || ADDRESS_1              //address 3 or address 1 will send to 2 occasionally
		if (target_address == 2)
#elif ADDRESS_2             //address 2 will send to address 1 (so will address 3, but that's covered in the 'else' below)
		if (target_address == 1)
#endif
		{
#if ADDRESS_3                           //address 3 needs to switch up and send to 2 instead of 1 at this point.
			target_address = 1;
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_5, colors + 4);
#endif
#elif ADDRESS_2 || ADDRESS_1            //on module with address 2 at this point, we're sending to 1. on module with address 1, we're sending to 2. in either case, we need to send to 3 on the next iteration.
			target_address = 3;
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_5, colors + 6);
#endif
#endif
		}
		else
		{
#if ADDRESS_3 || ADDRESS_1              //on module with address 3, we last sent to 1, on module with address 1, we last sent to 3. in both cases, the next address we need to send to is address 2
			target_address = 2;
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_5, colors + 5);
#endif
#elif ADDRESS_2                         //on module with address 2, we last sent to 3, so we need to send to 1 next.
			target_address = 1;
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_5, colors + 4);
#endif
#endif
		}

		//read the mpu and prepare the command to be sent
		get_mpu_readings(&local_imu_data);

		uint8_t tx_buf[sizeof(local_imu_data) - 2];
		tx_buf[0] = MESH_CMD_UPDATE_IMU_DATA;

		for (uint32_t i = 0; i < sizeof(local_imu_data) - 4; ++i)
		{
			tx_buf[i + 1] = local_imu_data.bytes[i];
		}

		tx_buf[sizeof(local_imu_data) - 3] = MESH_CMD_TERMINATION;

		//send the message
		tx_start = Millis();
		//            last_tx_return_value = mesh_tx(tx_buf, sizeof(local_imu_data) - 4, target_address);
		last_tx_return_value = mesh_tx(tx_buf, 22, target_address);        //32(NRF max payload size) - 4 for radiohead's NRF packet header, 5 for radiohead's routed packet header, 1 for radiohead's other packet header
		tx_time = Millis() - tx_start;

		//update return value accumulators
		switch (last_tx_return_value)
		{
		case RH_ROUTER_ERROR_NONE:
		{
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_4, colors + 5);
#endif
			experiment_data.transmit_time_success_total_ms += tx_time;
			++experiment_data.ERROR_NONE_count;
			break;
		}
		case RH_ROUTER_ERROR_INVALID_LENGTH:
		{
			++experiment_data.ERROR_INVALID_LENGTH_count;
			break;
		}
		case RH_ROUTER_ERROR_NO_ROUTE:
		{
			++experiment_data.ERROR_NO_ROUTE_count;
			break;
		}
		case RH_ROUTER_ERROR_TIMEOUT:
		{
			++experiment_data.ERROR_TIMEOUT_count;
			break;
		}
		case RH_ROUTER_ERROR_NO_REPLY:
		{
			++experiment_data.ERROR_NO_REPLY_count;
			break;
		}
		case RH_ROUTER_ERROR_UNABLE_TO_DELIVER:
		{
			++experiment_data.ERROR_UNABLE_TO_DELIVER_count;
			break;
		}
		default:
		{
			break;
		}
		}

		//increment transmit counter
		++experiment_data.tx_messages_sent[target_address - 1];
		++transmissions_sent_for_this_experiment;

		//increment fail counter if necessary
		if (last_tx_return_value > 0)
		{
#if ENABLE_DIAGNOSTIC_LED
			Set_LED_Output(RGB_4, colors + 4);
#endif

			++(experiment_data.tx_messages_failed[target_address - 1]);
			experiment_data.transmit_time_fail_total_ms += tx_time;
		}

		mode_start_time = Millis();
	}
#endif

}

}

#if ENABLE_DIAGNOSTIC_LED
static void update_imu_leds(const mpu_values* remote_imu_data, Color_RGB colors[])
{
	if (remote_imu_data->values.accel.val.x < 50)
	{
		Set_LED_Output(RGB_12, colors + 1);        //-x
		Set_LED_Output(RGB_4, colors + 0);//+x
	}
	else if (remote_imu_data->values.accel.val.x > 50)
	{
		Set_LED_Output(RGB_12, colors + 0);        //-x
		Set_LED_Output(RGB_4, colors + 1);//+x
	}

	if (remote_imu_data->values.accel.val.y < 50)
	{
		Set_LED_Output(RGB_1, colors + 1);        //-y
		Set_LED_Output(RGB_9, colors + 0);//+y
	}
	else if (remote_imu_data->values.accel.val.y > 50)
	{
		Set_LED_Output(RGB_1, colors + 0);        //-y
		Set_LED_Output(RGB_9, colors + 1);//+y
	}

	if (remote_imu_data->values.accel.val.z > 0)        //+z
	{
		Set_LED_Output(RGB_10, colors + 1);
		Set_LED_Output(RGB_7, colors + 1);
		Set_LED_Output(RGB_6, colors + 1);
		Set_LED_Output(RGB_3, colors + 1);
	}
	else if (remote_imu_data->values.accel.val.z < 0)        //-z
	{
		Set_LED_Output(RGB_10, colors + 3);
		Set_LED_Output(RGB_7, colors + 3);
		Set_LED_Output(RGB_6, colors + 3);
		Set_LED_Output(RGB_3, colors + 3);
	}

	if (std::abs(remote_imu_data->values.mag.val.y)
			>= std::abs(remote_imu_data->values.mag.val.x))
	{
		if (remote_imu_data->values.mag.val.y > 0)
		{
			//strongest magnetic field towards y+
			Set_LED_Output(RGB_11, colors);//y-
			Set_LED_Output(RGB_8, colors);//x+
			Set_LED_Output(RGB_5, colors + 1);//y+
			Set_LED_Output(RGB_2, colors);//x-
		}
		else
		{
			//strongest magnetic field towards y-
			Set_LED_Output(RGB_11, colors + 1);//y-
			Set_LED_Output(RGB_8, colors);//x+
			Set_LED_Output(RGB_5, colors);//y+
			Set_LED_Output(RGB_2, colors);//x-
		}
	}
	else
	{
		if (remote_imu_data->values.mag.val.x > 0)
		{
			//strongest magnetic field towards x+
			Set_LED_Output(RGB_11, colors);//y-
			Set_LED_Output(RGB_8, colors + 1);//x+
			Set_LED_Output(RGB_5, colors);//y+
			Set_LED_Output(RGB_2, colors);//x-
		}
		else
		{
			//strongest magnetic field towards x-
			Set_LED_Output(RGB_11, colors);//y-
			Set_LED_Output(RGB_8, colors);//x+
			Set_LED_Output(RGB_5, colors);//y+
			Set_LED_Output(RGB_2, colors + 1);//x-
		}
	}
}
#endif

static void upcount_hb_leds()
{
//    LED1_PutVal(LED1_DeviceData, !(hb_led_count & 0x02));
	LED2_PutVal(NULL, !(hb_led_count & 0x01));
	hb_led_count = (hb_led_count + 1) % 4;
}

static void update_mesh_mode(uint8_t * data, uint8_t len)
{
	if (len < 2)
		return;
	mesh_mode = data[1];
}

static void mesh_update_imu_leds(uint8_t * data, uint8_t len)
{
	LED1_PutVal(NULL, rx_led_toggle);
	rx_led_toggle = !rx_led_toggle;
}

