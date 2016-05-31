/*
 * Bootloader.c
 *
 *  Created on: Jan 9, 2016
 *      Author: thebh
 */

//includes
#include "WiFi.h"
#include "Application.h"
#include "bootloader.h"
#include "PE_Types.h"
#include "Cpu.h"
#include "stdlib.h"
#include "HTTP_Messages.h"
#include "Program_Flash.h"
//defines

//data types

//global vars -- this guy is placed at the end of RAM, 0x20007FF8. This is 8 bytes from the end, which is the size of the struct.
shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;
bool is_update_available;

//local vars

//function prototypes
static void boot_jump(uint32_t address);
static Message * WiFi_Send_With_Retries(Message * outgoing_message, uint32_t retry_count, uint32_t per_try_timeout_ms);
static Message * WiFi_Wait_For_Message(uint32_t timeout_ms);
static uint16_t Parse_Checksum_From_Message(Message * message);

//implementations

uint8_t Initialize_Bootloader() {
   is_update_available = FALSE;
   // TODO: Check value of SharedData.ApplicationUpdateAvailable and other shared data and configure state?
   SharedData.UpdateApplication = FALSE;
}

/**
 * Gets the checksum of the most recent firmware from the server and compares 
 * it to the computed checksum of the device's current firmware. This function 
 * is used to decide whether or not to update the firmware by calling 
 * Update_Firmware (...).
 * 
 * Returns TRUE if the checksums are the same. False if they are different.
 */
uint8_t Has_Latest_Firmware() {

   uint8_t result = TRUE;     // Return value. Default to true.
   uint16_t firmwareChecksum = 0;     // The stored checksum value.
   uint16_t latestFirmwareChecksum = 0;     // The checksum of the latest firmware.
   Message * response_message;

   char uriParameters[64] = { 0 };

   //TODO: do a proper version check.
   //sprintf(uriParameters, "/clay/firmware/version");

   // Retrieve firmware checksum from the server.
   sprintf(uriParameters, "/clay/firmware/checksum");

   response_message = WiFi_Send_With_Retries(Create_HTTP_GET_Request(FIRMWARE_SERVER_ADDRESS, local_address, uriParameters),
                                             5,
                                             5000);

   if (response_message != NULL) {
      latestFirmwareChecksum = Parse_Checksum_From_Message(response_message);
      Delete_Message(response_message);
      response_message = NULL;
   }

   // Get the stored checksum
   firmwareChecksum = Read_Program_Checksum();

   // Check if the checksum of the application firmware matches the checksum
   // of the latest firmware received from the server.
   if (firmwareChecksum != latestFirmwareChecksum) {
      result = FALSE;
   }

   return result;
}

//Returns true if an update is available and writes the ApplicationKey value so 
//        the bootloader will know that the application has run.
bool Update_Available() {

   // Check remote server to see if an update is available.
   // If so, indicate it by writing to the shared flash memory so the bootloader can read it.
   SharedData.ApplicationUpdateAvailable = !Has_Latest_Firmware();

   // Return the value stored in the shared memory application indicating
   // whether or not there's an update available.

   return SharedData.ApplicationUpdateAvailable;
}

/**
 * Disables all interrupts.
 */
void Disable_Interrupts() {
   NVICICER0 = 0xFFFFFFFF;
   NVICICER1 = 0xFFFFFFFF;
   NVICICER2 = 0xFFFFFFFF;
   NVICICER3 = 0xFFFFFFFF;
}

//Call to jump to the bootloader and update the application.
void Jump_To_Bootloader_And_Update_Application() {

   SharedData.UpdateApplication = TRUE;

   //change vector table offset register to application vector table
   SCB_VTOR = BOOT_START_ADDR & 0x1FFFFF80;

   //set stack pointer/pc to the reset interrupt.
   boot_jump(BOOT_START_ADDR);
}

//executes bootloader jump
static void boot_jump(uint32_t address) {
   //Load new stack pointer address
   asm("LDR SP, [R0]");
   //Load new program counter address
   asm("LDR PC, [R0,#4]");
}

////Local implementations /////////////////////////////////////////
static Message * WiFi_Send_With_Retries(Message * outgoing_message, uint32_t retry_count, uint32_t per_try_timeout_ms) {

   Message * result = NULL;
   Message * temp_outgoing_message;

   for (int i = 0; i < retry_count && result == NULL; ++i) {
      temp_outgoing_message = Create_Message();

      Set_Message_Type(temp_outgoing_message, outgoing_message->message_type);
      Set_Message_Source(temp_outgoing_message, outgoing_message->source);
      Set_Message_Destination(temp_outgoing_message, outgoing_message->destination);
      Set_Message_Content_Type(temp_outgoing_message, outgoing_message->content_type);
      Set_Message_Content(temp_outgoing_message, outgoing_message->content, outgoing_message->content_length);

      Wifi_Send(temp_outgoing_message);
      result = WiFi_Wait_For_Message(per_try_timeout_ms);
   }

   Delete_Message(outgoing_message);

   return result;
}

static Message * WiFi_Wait_For_Message(uint32_t timeout_ms) {

   Message * result = NULL;

   uint32_t start_time_ms = Millis();

   while (!Has_Messages(&incomingWiFiMessageQueue) && (Millis() - start_time_ms) < timeout_ms) {
      Monitor_Periodic_Events();
   }

   if (Has_Messages(&incomingWiFiMessageQueue)) {
      result = Wifi_Receive();
   }

   return result;
}

static uint16_t Parse_Checksum_From_Message(Message * message) {

   uint16_t rval = 0;

   if (message != NULL) {
      rval = (atoi(message->content));
   }

   return rval;
}
