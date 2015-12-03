/*
 * mesh_statistics.c
 *
 *  Created on: Dec 2, 2015
 *      Author: thebh_000
 */

#include <stdio.h>

#ifndef MESH_STASTISTICS_H_
#include "mesh_stastistics.h"
#endif

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

#ifndef _wirish_h
#include"wirish.h"
#endif 

#ifndef MESH_H_
#include "Mesh.h"
#endif

mesh_experiment_data experiment_data;
uint32_t transmissions_sent_for_this_experiment;
uint32_t start_time;

//(max value of unsigned 32 bit value in decimal (10) + comma) * number of values + null + extra space for strings/other shit.
uint8_t tx_string[500];
//(max value of unsigned 32 bit value in decimal (10) + comma) * number of values + null + extra space for strings/other shit.
char settings_string[150];
//(max value of unsigned 32 bit value in decimal (10) + comma) * number of values + null  
char tx_sent_str[MAX_NODE_COUNT * 11 + 1];
char tx_fail_str[MAX_NODE_COUNT * 11 + 1];
char msg_rx_str[(MAX_NODE_COUNT + 1) * 11 + 1];
char alive_rx_str[(MAX_NODE_COUNT + 1) * 11 + 1];

uint32_t experiment_index = 0;

static void print_uint32_array(uint32_t * data, uint8_t count, char * string);

void send_data_and_setup_next_experiment()
{
    transmit_data(&experiment_data);
    setup_next_experiment();
}

void setup_next_experiment()
{

    //not implemented
    if (0)
    {
        experiment_data.settings.tx_attenuation = _0dBm;        //not yet implemented
    }
    else
    {
        experiment_data.settings.tx_attenuation = _0dBm;
    }

    if (0)
    {
        experiment_data.settings.mesh_datarate = _2Mbps;        //not yet implemented
    }
    else
    {
        experiment_data.settings.mesh_datarate = _2Mbps;

    }

    if (0)
    {
        experiment_data.settings.spi_datarate = 0xFF;           //not yet implemented in hardware SPI, RH_NRF24.cpp, or mesh.c
    }
    else
    {
        experiment_data.settings.spi_datarate = 0xFF;
    }

    if (experiment_index < 60)
    {
        experiment_data.settings.randomize_hw_retry_count = random(0, 1);
        experiment_data.settings.randomize_hw_retry_timeout = !experiment_data.settings.randomize_hw_retry_count;
    }
    else
    {
        experiment_data.settings.randomize_hw_retry_count = false;
        experiment_data.settings.randomize_hw_retry_timeout = false;
    }

    if (experiment_index < 60)
    {
        experiment_data.settings.radio_retry_count = random(0, 15);
    }
    else
    {
        experiment_data.settings.radio_retry_count = 15;
    }

    if (experiment_index < 60)
    {
        experiment_data.settings.retry_interval = (mesh_HW_retry_interval) random(0, 15);
    }
    else
    {
        experiment_data.settings.retry_interval = _500uS;
    }

    if (60 <= experiment_index && experiment_index < 90)
    {
        experiment_data.settings.min_rh_retry_count = random(0, 15);
        experiment_data.settings.max_rh_retry_count = (random(0, 1) ? random(experiment_data.settings.min_rh_retry_count + 10, 3000) : 0);
    }
    else
    {
        experiment_data.settings.min_rh_retry_count = 3;
        experiment_data.settings.max_rh_retry_count = 0;
    }

    if (90 <= experiment_index && experiment_index < 120)
    {
        experiment_data.settings.min_rh_retry_timeout_ms = random(10, 3000);
        experiment_data.settings.max_rh_retry_timeout_ms = (random(0, 1) ? random(experiment_data.settings.min_rh_retry_timeout_ms + 10, 3000) : 0);
    }
    else
    {
        experiment_data.settings.min_rh_retry_timeout_ms = 10;
        experiment_data.settings.max_rh_retry_timeout_ms = 0;
    }

    if (120 <= experiment_index && experiment_index < 150)
    {
        experiment_data.settings.mesh_tx_period_min_ms = random(10, 3000);
        experiment_data.settings.mesh_tx_period_max_ms = (random(0, 1) ? random(experiment_data.settings.mesh_tx_period_min_ms + 10, 3000) : 0);
    }
    else
    {
        experiment_data.settings.mesh_tx_period_min_ms = 50;
        experiment_data.settings.mesh_tx_period_max_ms = 0;
    }

    //not implemented
    if (0)
    {
        experiment_data.settings.check_channel_clear_before_tx = false;         //not yet implemented in RH_NRF24.c or mesh.c
    }
    else
    {
        experiment_data.settings.check_channel_clear_before_tx = false;
    }

    //not implemented
    if (0)
    {
        experiment_data.settings.dma_enabled = false;                           //not yet implemented anywhere.
    }
    else
    {
        experiment_data.settings.dma_enabled = false;
    }

    //not implemented
    if (0)
    {
        experiment_data.settings.send_alive_messages = true;
        experiment_data.settings.alive_message_period = 5000;
    }
    else
    {
        experiment_data.settings.send_alive_messages = true;
        experiment_data.settings.alive_message_period = 5000;
    }

    //not implemented
    if (0)
    {
        experiment_data.settings.tx_packet_length = 18;
    }
    else
    {
        experiment_data.settings.tx_packet_length = 18;
    }

    //not modified
    experiment_data.settings.message_transmission_count = 100;
    experiment_data.settings.experiment_duration_ms = 0;

    re_init_mesh_retries();

    experiment_index = (experiment_index + 1) % 180;

    //reset counters
    transmissions_sent_for_this_experiment = 0;
    start_time = power_on_time_msec - start_time;
}

void settings_to_string(mesh_experiment_settings * settings, uint8_t * string)
{
    sprintf((char*) string,
            "%u,%u,%u,%u,%u,%s,%s,%lu,%lu,%lu,%lu,%lu,%lu,%s,%s,%lu,%lu,%s,%lu,%lu",
            (uint8_t) settings->tx_attenuation,
            (uint8_t) settings->mesh_datarate,
            settings->spi_datarate,
            (uint8_t) settings->radio_retry_count,
            (uint8_t) settings->retry_interval,
            settings->randomize_hw_retry_count ? "true" : "false",
            settings->randomize_hw_retry_timeout ? "true" : "false",
            settings->min_rh_retry_count,
            settings->max_rh_retry_count,
            settings->min_rh_retry_timeout_ms,
            settings->max_rh_retry_timeout_ms,
            settings->mesh_tx_period_min_ms,
            settings->mesh_tx_period_max_ms,
            settings->check_channel_clear_before_tx ? "true" : "false",
            settings->dma_enabled ? "true" : "false",
            settings->message_transmission_count,
            settings->experiment_duration_ms,
            settings->send_alive_messages ? "true" : "false",
            settings->alive_message_period,
            settings->tx_packet_length
            );
}

void experiment_data_to_string(mesh_experiment_data * data, uint8_t * string)
{
    settings_to_string(&(data->settings), (uint8_t *) settings_string);

    print_uint32_array(data->tx_messages_sent, MAX_NODE_COUNT, tx_sent_str);
    print_uint32_array(data->tx_messages_failed, MAX_NODE_COUNT, tx_fail_str);
    print_uint32_array(data->messages_received, MAX_NODE_COUNT + 1, msg_rx_str);
    print_uint32_array(data->alives_received, MAX_NODE_COUNT + 1, alive_rx_str);

    sprintf((char*) string,
            "%s,%lu,%s%s%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%s%s%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu\r\n",
            settings_string,
            data->experiment_duration_ms,
            tx_sent_str,
            tx_fail_str,
            data->ERROR_NONE_count,
            data->ERROR_INVALID_LENGTH_count,
            data->ERROR_NO_ROUTE_count,
            data->ERROR_TIMEOUT_count,
            data->ERROR_NO_REPLY_count,
            data->ERROR_UNABLE_TO_DELIVER_count,
            data->RH_retry_count,
            data->RH_total_send_count,
            msg_rx_str,
            alive_rx_str,
            data->transmit_time_success_total_ms,
            data->transmit_time_fail_total_ms,
            data->do_arp_time_total_ms,
            data->do_arp_success_count,
            data->route_table_miss,
            data->rx_interrupt_time_total_ms,
            data->rx_interrupt_count,
            data->detected_node_count
            );
}

//send data to the collection server
bool transmit_data(mesh_experiment_data * data)
{
    bool rval = false;

    experiment_data_to_string(data, tx_string);

    int d = strlen((char*) tx_string);

    return rval;
}

static void print_uint32_array(uint32_t * data, uint8_t count, char * string)
{
    uint32_t offset = 0;
    for (uint8_t i = 0; i < count; ++i)
    {
        offset += sprintf(string + offset, "%lu,", data[i]);
    }
}

////max length of string with the following vars is 446 bytes
//data->settings.tx_attenuation = _0dBm;
//data->settings.mesh_datarate = _2Mbps;
//data->settings.spi_datarate = 0xFF;
//data->settings.radio_retry_count = 15;
//data->settings.retry_interval = (mesh_HW_retry_interval) 0xF;
//data->settings.randomize_hw_retry_count = false;
//data->settings.randomize_hw_retry_timeout = false;
//data->settings.min_rh_retry_count = 0xFFFFFFFF - 27;
//data->settings.max_rh_retry_count = 0xFFFFFFFF - 26;
//data->settings.min_rh_retry_timeout_ms = 0xFFFFFFFF - 25;
//data->settings.max_rh_retry_timeout_ms = 0xFFFFFFFF - 24;
//data->settings.mesh_tx_period_min_ms = 0xFFFFFFFF - 23;
//data->settings.mesh_tx_period_max_ms = 0xFFFFFFFF - 22;
//data->settings.check_channel_clear_before_tx = false;
//data->settings.dma_enabled = false;
//data->settings.message_transmission_count = 0xFFFFFFFF - 21;
//data->settings.experiment_duration_ms = 0xFFFFFFFF - 20;
//data->settings.send_alive_messages = false;
//data->settings.alive_message_period = 0xFFFFFFFF - 19;
//data->settings.tx_packet_length = 0xFFFFFFFF - 18;
//data->experiment_duration_ms = 0xFFFFFFFF - 17;
////end of settings
//for (int i = 0; i < MAX_NODE_COUNT; ++i)
//{
//    data->tx_messages_sent[i] = 0xFFFFFFFF - i;
//    data->tx_messages_failed[i] = 0xFFFFFFFF - (i * 2);
//}
//data->ERROR_NONE_count = 0xFFFFFFFF - 16;
//data->ERROR_INVALID_LENGTH_count = 0xFFFFFFFF - 15;
//data->ERROR_NO_ROUTE_count = 0xFFFFFFFF - 14;
//data->ERROR_TIMEOUT_count = 0xFFFFFFFF - 13;
//data->ERROR_NO_REPLY_count = 0xFFFFFFFF - 12;
//data->ERROR_UNABLE_TO_DELIVER_count = 0xFFFFFFFF - 11;
//data->RH_retry_count = 0xFFFFFFFF - 10;
//data->RH_total_send_count = 0xFFFFFFFF - 9;
//for (int i = 0; i < MAX_NODE_COUNT + 1; ++i)
//{
//    data->messages_received[i] = 0xFFFFFFFF - i;
//    data->alives_received[i] = 0xFFFFFFFF - (i * 2);
//}
//data->transmit_time_success_total_ms = 0xFFFFFFFF - 8;
//data->transmit_time_fail_total_ms = 0xFFFFFFFF - 7;
//data->do_arp_time_total_ms = 0xFFFFFFFF - 6;
//data->do_arp_success_count = 0xFFFFFFFF - 5;
//data->route_table_miss = 0xFFFFFFFF - 4;
//data->rx_interrupt_time_total_ms = 0xFFFFFFFF - 3;
//data->rx_interrupt_count = 0xFFFFFFFF - 2;
//data->detected_node_count = 0xFFFFFFFF - 1;
