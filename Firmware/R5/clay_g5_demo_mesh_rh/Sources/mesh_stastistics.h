/*
 * mesh_stastistics.h
 *
 *  Created on: Dec 1, 2015
 *      Author: thebh_000
 */

#ifndef MESH_STASTISTICS_H_
#define MESH_STASTISTICS_H_

#define TX_PERIOD_ARRAY_LENGTH  13

//tx & timinng vars -- used in main.cpp /////////////////////////////////////
//DON'T FORGET TO UPDATE  IF YOU CHANGE THE PERIOD VALUES IN THE ARRAY. THIS VALUE MUST BE UPDATED IN Mesh.h AND RHReliableDatagram.H AS WELL
extern uint32_t message_tx_period_ms_array[];
extern uint32_t current_message_period_index;
//DON'T FORGET TO UPDATE  IF YOU CHANGE THE PERIOD VALUES IN THE ARRAY. THIS VALUE MUST BE UPDATED IN Mesh.h AND RHReliableDatagram.H AS WELL

//collection time values
extern uint32_t start_time;
extern uint32_t collection_duration_s[];

//transmission accumulator vars
extern uint32_t * transmit_count_ptr;
extern uint32_t transmit_count_1[];
extern uint32_t transmit_count_2[];
extern uint32_t transmit_count_3[];
extern uint32_t * transmit_fail_ptr;

//tx failure accumulator vars
extern uint32_t transmit_fail_1[];
extern uint32_t transmit_fail_2[];
extern uint32_t transmit_fail_3[];

//tx return value accumulators
extern uint32_t ERROR_NONE_count[];                          //return value of 0
extern uint32_t ERROR_INVALID_LENGTH_count[];                //return value of 1
extern uint32_t ERROR_NO_ROUTE_count[];                      //return value of 2
extern uint32_t ERROR_TIMEOUT_count[];                       //return value of 3
extern uint32_t ERROR_NO_REPLY_count[];                      //return value of 4
extern uint32_t ERROR_UNABLE_TO_DELIVER_count[];             //return value of 5
extern uint8_t last_tx_return_value;

//tx time accumulators
extern uint32_t transmit_time_success_total[];
extern uint32_t transmit_time_fail_total[];

///rx vars -- used in mesh.c ////////////////////////////////////////////////
extern uint32_t messages_received_1[];
extern uint32_t messages_received_2[];
extern uint32_t messages_received_3[];

extern uint32_t alives_received_1[];
extern uint32_t alives_received_2[];
extern uint32_t alives_received_3[];

///retry/hw send vars -- used in RhReliableDatagram.c ///////////////////////
extern uint32_t RH_RelDG_retry_count[];
extern uint32_t RH_RelDG_total_send_count[];

#endif /* MESH_STASTISTICS_H_ */
