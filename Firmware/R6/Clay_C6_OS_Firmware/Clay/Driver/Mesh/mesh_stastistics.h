/*
 * mesh_stastistics.h
 *
 *  Created on: Dec 1, 2015
 *      Author: thebh_000
 */

#ifndef MESH_STASTISTICS_H_
#define MESH_STASTISTICS_H_

#ifndef MESH_H_
#include "Mesh.h"
#endif

#define MAX_NODE_COUNT     3

#define EXPERIMENT_DURATION_S     0
#define TX_MESSAGE_COUNT          100

typedef struct
{
	mesh_radio_tx_attenuation tx_attenuation;        //not yet implemented
	mesh_radio_datarate mesh_datarate;          //not yet implemented
	uint8_t spi_datarate;                       //not yet implemented in hardware SPI, RH_NRF24.cpp, or mesh.c

	//hardware retries
	uint8_t radio_retry_count;
	mesh_HW_retry_interval retry_interval;
	bool randomize_hw_retry_count;
	bool randomize_hw_retry_timeout;

	//RH retries: if max == 0, min will be used as the
	//  value. otherwise, value will be random number
	//  bounded by min and max.
	uint8_t min_rh_retry_count;
	uint8_t max_rh_retry_count;
	uint16_t min_rh_retry_timeout_ms;
	uint16_t max_rh_retry_timeout_ms;

	//send period: if max == 0, min will be used as the
	//  period. otherwise, period will be random number
	//  bounded by min and max.
	uint8_t mesh_tx_period_min_ms;
	uint8_t mesh_tx_period_max_ms;

	//check the CD bit in the mesh radio before attempting to send
	bool check_channel_clear_before_tx;         //not yet implemented in RH_NRF24.c or mesh.c

	//Use DMA to communicate with the radio
	bool dma_enabled;                           //not yet implemented anywhere.

	//amount of data to collect for the experiment.
	//  if transmission count is set,
	//      then message_transmission_count messages will
	//      be collected.
	//  if experiment_duration_ms is set,
	//      then messages will be sent until
	//      experiment_duration_ms milliseconds have passed
	//  if both are set, the experiment will end after one
	//      of the values is exceeded.
	uint32_t message_transmission_count;
	uint32_t experiment_duration_ms;

	//whether or not the address of this node is broadcast periodically.
	bool send_alive_messages;
	uint32_t alive_message_period;

	//size of transmitted data
	uint8_t tx_packet_length;        //maximum value is 22
} mesh_experiment_settings;

typedef struct
{
	mesh_experiment_settings settings;

	//actual message duration
	uint32_t experiment_duration_ms;

	//number of messages sent
	uint32_t tx_messages_sent[MAX_NODE_COUNT];
	uint32_t tx_messages_failed[MAX_NODE_COUNT];

	//return value accumulators
	uint32_t ERROR_NONE_count;                          //return value of 0
	uint32_t ERROR_INVALID_LENGTH_count;                //return value of 1
	uint32_t ERROR_NO_ROUTE_count;                      //return value of 2
	uint32_t ERROR_TIMEOUT_count;                       //return value of 3
	uint32_t ERROR_NO_REPLY_count;                      //return value of 4
	uint32_t ERROR_UNABLE_TO_DELIVER_count;             //return value of 5

	//accumulators for sends from radiohead to the hardware
	uint32_t RH_retry_count;
	uint32_t RH_total_send_count;

	///rx message accumulators
	uint32_t messages_received[MAX_NODE_COUNT + 1];
	uint32_t alives_received[MAX_NODE_COUNT + 1];

	//tx time accumulators
	uint32_t transmit_time_success_total_ms;
	uint32_t transmit_time_fail_total_ms;

	//routing statistics
	uint32_t do_arp_time_total_ms;        //successful route searches only
	uint32_t do_arp_success_count;        //number of times a route was successfully found.
	uint32_t route_table_miss;          //number of times no route found and doArp called

	//rx interrupt statistics
	uint32_t rx_interrupt_time_total_ms;
	uint32_t rx_interrupt_count;

	//node information
	uint8_t detected_node_count;
} mesh_experiment_data;

extern mesh_experiment_data experiment_data;
extern uint32_t transmissions_sent_for_this_experiment;
extern uint32_t start_time;

//call to randomize parameters for next experiment.
extern void send_data_and_setup_next_experiment();

extern void setup_next_experiment();

extern void settings_to_string(mesh_experiment_settings * settings, uint8_t * string);

extern void experiment_data_to_string(mesh_experiment_data * data, uint8_t * string);

extern bool transmit_data(mesh_experiment_data * data);

#endif /* MESH_STASTISTICS_H_ */
