/*
 * app_nrf24l01.c
 *
 *  Created on: Oct 1, 2015
 *      Author: Ben
 */

// includes //////////////////
#include "app_nrf24l01.h"

#ifndef SYSTEM_TICK_H_
#include "system_tick.h"
#endif

// defines ///////////////////
#define TX_TIMEOUT_MS        1000

// structs ///////////////////

// global vars ///////////////

// local vars ////////////////
static uint8_t mesh_tx_buf[128];
static uint8_t mesh_rx_buf[128];

static volatile uint8_t isr_flag;
static volatile uint8_t tx_in_progress;
static volatile uint8_t isr_flag;

static volatile uint8_t status_reg;
static volatile uint32_t tx_time_ms;

static volatile uint8_t rx_data_ready;
static volatile uint32_t rx_data_count;

// prototypes ////////////////
static void set_tx_destination_address(uint32_t destination);
static void mesh_listen();

// implementations ///////////

void mesh_init(bool prx)
{
    RF1_Init();

    RF1_WriteRegister(RF1_CONFIG, 0);        //power down
    delay_n_msec(20);

    RF1_WriteRegister(RF1_RX_PW_P0, 24);        //set payload size

    RF1_WriteRegister(RF1_RF_CH, MESH_CHANNEL_NUMBER);                           // set channel

    RF1_WriteRegister(RF1_SETUP_AW, MESH_RADIO_ADDRESS_WIDTH);          //set address width

    mesh_tx_buf[0] = (MESH_RADIO_ADDRESS_GLOBAL & 0xFF);
    mesh_tx_buf[1] = ((MESH_RADIO_ADDRESS_GLOBAL >> 8) & 0xFF);
    mesh_tx_buf[2] = ((MESH_RADIO_ADDRESS_GLOBAL >> 16) & 0xFF);
    mesh_tx_buf[3] = ((MESH_RADIO_ADDRESS_GLOBAL >> 24) & 0xFF);
    mesh_tx_buf[4] = 0x00;
    RF1_WriteRegisterData(RF1_RX_ADDR_P0, mesh_tx_buf, 5);              //set global address as pipe 0
    RF1_WriteRegisterData(RF1_TX_ADDR, mesh_tx_buf, 5);                 //set global address as tx destination

    RF1_WriteRegister(RF1_EN_RXADDR, RF1_EN_RXADDR_ERX_P0);            //enable pipe 0

    //enter rx mode, this is the typical idle state for the device
    if (prx)
    {
        RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_RECEIVE_CONFIG);
        RF1_WriteRegister(RF1_EN_AA, RF1_EN_AA_ENAA_P0);
    }
    else
    {
        //set up .75ms retry delay, 15 retries
        RF1_WriteRegister(RF1_SETUP_RETR, RF1_SETUP_RETR_ARD_750 | RF1_SETUP_RETR_ARC_15);

        //enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR
        RF1_WriteRegister(RF1_EN_AA, RF1_EN_AA_ENAA_P0);

        RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_TRANSMIT_CONFIG);
    }
}

void mesh_state_update()
{
    uint8_t readbytes = RF1_ReadRegister(RF1_RX_PW_P0);
    status_reg = RF1_GetStatus();
    if (isr_flag)
    { /* check if we have received an interrupt */
        isr_flag = FALSE; /* reset interrupt flag */
        if (status_reg & RF1_STATUS_RX_DR)
        { /* data received interrupt */
            RF1_ResetStatusIRQ(RF1_STATUS_RX_DR); /* clear bit */
            if (readbytes > 0)
            {
                RF1_RxPayload(mesh_rx_buf, readbytes);
                rx_data_count = readbytes;
                rx_data_ready = TRUE;
            }
        }
        if (status_reg & RF1_STATUS_TX_DS)
        { /* data sent interrupt */
            tx_time_ms = 0; /* reset timeout counter */
            tx_in_progress = FALSE;
            RF1_ResetStatusIRQ(RF1_STATUS_TX_DS); /* clear bit */
#if !MESH_TRANSMIT
            mesh_listen();
#endif
        }
        if (status_reg & RF1_STATUS_MAX_RT)
        { /* retry timeout interrupt */
            RF1_ResetStatusIRQ(RF1_STATUS_MAX_RT); /* clear bit */
            tx_in_progress = FALSE;
            tx_time_ms = 0;
#if!MESH_TRANSMIT
            mesh_listen();
#endif
        }

        if (tx_in_progress && (power_on_time_msec - tx_time_ms) > TX_TIMEOUT_MS)
        {
            tx_in_progress = FALSE;
        }
    }
}

void mesh_send_string(uint8_t * tx_buf, uint32_t length, uint32_t destinationAddress)
{
    if (!tx_in_progress && !isr_flag)
    {
        RF1_ResetStatusIRQ(RF1_STATUS_RX_DR | RF1_STATUS_TX_DS | RF1_STATUS_MAX_RT);

        RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_TRANSMIT_CONFIG);

        delay_n_msec(3);

        set_tx_destination_address(destinationAddress);
        RF1_TxPayload(tx_buf, length);
        tx_time_ms = power_on_time_msec;
        tx_in_progress = TRUE;
    }
}

void mesh_broadcast_string(uint8_t * tx_buf, uint32_t length)
{
    mesh_send_string(tx_buf, length, MESH_RADIO_ADDRESS_GLOBAL);
}

//returns number of bytes actually retrieved into rx_buf
int mesh_receive_string(uint8_t * rx_buf, uint32_t length)
{
    int rval = -1;

    mesh_listen();

    if (rx_data_ready)
    {
        rval = (rx_data_count > length ? length : rx_data_count);
        rx_data_ready = FALSE;

        for (int i = 0; i < rval; ++i)
        {
            rx_buf[i] = mesh_rx_buf[i];
        }
    }

    return rval;
}

extern void mesh_interrupt_handler()
{
    CE1_ClrVal();
    isr_flag = TRUE;
    tx_in_progress = FALSE;
}

static void set_tx_destination_address(uint32_t destination)
{
    mesh_tx_buf[0] = (destination & 0xFF);
    mesh_tx_buf[1] = ((destination >> 8) & 0xFF);
    mesh_tx_buf[2] = ((destination >> 16) & 0xFF);
    mesh_tx_buf[3] = ((destination >> 24) & 0xFF);
    RF1_WriteRegisterData(RF1_TX_ADDR, mesh_tx_buf, 4);              //set global address as pipe 0
}

//idle state of mesh radio. sit here and listen for incoming data.
static void mesh_listen()
{
    RF1_ResetStatusIRQ(RF1_STATUS_RX_DR | RF1_STATUS_TX_DS | RF1_STATUS_MAX_RT);
    RF1_WriteRegister(RF1_CONFIG, MESH_RADIO_RECEIVE_CONFIG);
    RF1_StartRxTx();
}
