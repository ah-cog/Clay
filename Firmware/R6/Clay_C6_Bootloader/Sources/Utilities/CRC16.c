/*
 * CRC16.c
 *
 *  Created on: May 7, 2016
 *      Author: thebh_000
 */

////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#include "CRC16.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////

////Local vars/////////////////////////////////////////////////////

////Local Prototypes///////////////////////////////////////////////

////Global implementations ////////////////////////////////////////

/**
 * Performs a cyclic redundancy check (CRC) according to the CRC-16 algorithm.
 *
 * This implementation is based on an implementation on StackOverflow
 * (https://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum).
 */
uint16_t Calculate_Checksum_On_Bytes(const uint8_t *data, uint32_t size) {

   uint16_t out = 0;
   int bits_read = 0, bit_flag;

   /* Sanity check: */
   if (data == NULL) return 0;

   while (size > 0) {
      bit_flag = out >> 15;

      /* Get next bit: */
      out <<= 1;
      out |= (*data >> bits_read) & 1;        // item a) work from the least significant bits

      /* Increment bit counter: */
      bits_read++;
      if (bits_read > 7) {
         bits_read = 0;
         data++;
         size--;
      }

      /* Cycle check: */
      if (bit_flag) out ^= CRC16;

   }

   // item b) "push out" the last 16 bits
   int i;
   for (i = 0; i < 16; ++i) {
      bit_flag = out >> 15;
      out <<= 1;
      if (bit_flag) out ^= CRC16;
   }

   // item c) reverse the bits
   uint16_t crc = 0;
   i = 0x8000;
   int j = 0x0001;
   for (; i != 0; i >>= 1, j <<= 1) {
      if (i & out) crc |= j;
   }

   return crc;
}

////Local implementations /////////////////////////////////////////
