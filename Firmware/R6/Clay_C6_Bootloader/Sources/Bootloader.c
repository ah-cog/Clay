////Includes //////////////////////////////////////////////////////
#include "MK64F12.h"
#include "Clock.h"
#include "WiFi.h"
#include "Bootloader.h"
#include "program_flash.h"
#include "HTTP_Messages.h"
#include "CRC16.h"

////Macros ////////////////////////////////////////////////////////
#define ADDRESS_STRING_LENGTH 30
#define REQUEST_WAIT_TIME_ms  1000

#define FIRST_PARAMETER  0
#define SECOND_PARAMETER 1
#define THIRD_PARAMETER  2
#define FOURTH_PARAMETER 3
#define FIFTH_PARAMETER  4
#define SIXTH_PARAMETER  5

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
//this guy is placed at the end of RAM, 0x20027FF8. This is 8 bytes from the end, which is the size of the struct.
shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;

uint8_t bootloaderMode = TRUE;        // Flag indicating if the unit is in bootloader mode.

bool wifi_connected;
bool local_address_received;

////Local vars/////////////////////////////////////////////////////
static char local_address[ADDRESS_STRING_LENGTH];

////Local Prototypes///////////////////////////////////////////////
static Message * WiFi_Send_With_Retries(Message * outgoing_message, uint32_t retry_count, uint32_t per_try_timeout_ms);
static Message * WiFi_Wait_For_Message(uint32_t timeout_ms);
static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern);
static uint32_t Parse_Size_From_Message(Message * message);
static uint16_t Parse_Checksum_From_Message(Message * message);

////Global implementations ////////////////////////////////////////

//data types

//TODO: place bootloader version in ROM.
//TODO: place app version in app ROM.

uint8_t Initialize_Bootloader() {

   uint8_t result = FALSE;

//	// Reset the status of the availability of a new update.
//	// The bootloader checks with the firmware server to see if there's an update available.
//	SharedData.ApplicationUpdateAvailable = FALSE;

   // Initialize the bootloader if it was not invoked from the application
   if (SharedData.ApplicationKey != APPLICATION_KEY_VALUE) {

      // Reset the status of the availability of a new update.
      // The bootloader checks with the firmware server to see if there's an update available.
      SharedData.ApplicationUpdateAvailable = FALSE;

      // Reset the request to update firmware
      SharedData.UpdateApplication = FALSE;
   }

   result = TRUE;

   return result;
}

/**
 * Returns true if the user requests a firmware update. In essence, this 
 * determines whether or not the update was acknowledged and explicitly 
 * approved by the user.
 * 
 * This is called every time the bootloader is executed (i.e., every time the 
 * device receives power).
 * 
 * This function checks if the "application key" (ApplicationKey) is set to 
 * the particular "signature" value that is only written when the main 
 * application firmware is executed. If the "application key" is equal to this 
 * value, the main application firmware must have been executed prior to 
 * the bootloader, indicating that the main application jumped back into 
 * the bootloader. This is usually done to start the firmware update process.
 * 
 * Before returning, this function will always reset the "application key" 
 * (ApplicationKey) to 0.
 */
bool Has_User_Requested_Update() {

   bool result = FALSE;

   // Check if the value of the "application key" is equal to the value
   // written by the main application firmware. If so, the bootloader was
   // jumped into from the main application. To indicate this, set the
   // return value to true.
   if (SharedData.ApplicationKey == APPLICATION_KEY_VALUE && SharedData.UpdateApplication) {
      result = TRUE;
   }

   // Reset the "application key".
   SharedData.ApplicationKey = 0;

   return result;
}

/**
 * Verifies the current firmware in flash. Computes the checksum of the 
 * current flash and compares it to the expected value stored at the end 
 * of the flash memory.
 */
uint8_t Verify_Firmware() {

   uint8_t status = NULL;
   uint8_t result = FALSE;
   uint16_t applicationChecksum = 0;
   uint32_t applicationSize = 0;

   // Read size of application firmware from flash memory.
   applicationSize = Read_Program_Size();

   // Read the checksum of the application firmware from flash memory.
   applicationChecksum = Read_Program_Checksum();

   // Check if the values are uninitialized (i.e., check if they haven't yet
   // been written.
   if (applicationSize == 0xFFFFFFFF || applicationChecksum == 0xFFFF) {

      result = FALSE;

   } else {

      // Compute the checksum of the application firmware stored in flash.
      // i.e., Verify the correctness of the entire program that has been written to flash memory.
      //       To do so, compare the computed CRC-16 checksum to the stored CRC-16 checksum.
      if ((status = Verify_Firmware_Bytes((uint8_t *) APP_START_ADDR, applicationSize, applicationChecksum)) != FALSE) {
         // The computed checksum is the same as the stored checksum, so set the return value to true.
         result = TRUE;
      }

   }

   return result;
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
   //sprintf(uriParameters, "/clay/firmware/version/");

   // Retrieve firmware checksum from the server.
   sprintf(uriParameters, "/clay/firmware/checksum");

   //TODO: implement HTTP Get
   //Send message
   //wait for response, calling WiFi_State_Step
   //get the message back

   response_message = WiFi_Send_With_Retries(Create_HTTP_GET_Request(FIRMWARE_SERVER_ADDRESS, local_address, uriParameters),
                                             5,
                                             500);

   if (response_message != NULL) {
      latestFirmwareChecksum = Parse_Checksum_From_Message(response_message);
      Delete_Message(response_message);
      response_message = NULL;
   }

//   latestFirmwareChecksum = atoi(httpResponseBuffer);

   // Get the stored checksum
   firmwareChecksum = Read_Program_Checksum();

   // Check if the checksum of the application firmware matches the checksum
   // of the latest firmware received from the server.
   if (firmwareChecksum != latestFirmwareChecksum) {
      result = FALSE;
   }

   //TODO: implement this. If the firmware IS out of date, set the value in the SharedData struct.
   return result;
}

/**
 * Verifies that the received block was successfully received.
 * 
 * Returns true if the bytes are valid, and false otherwise.
 */
uint8_t Verify_Firmware_Bytes(const uint8_t *bytes, uint32_t length, uint16_t expected_checksum) {

//    uint16_t received_checksum = bytes[0] | (bytes[1] << 8);
//    uint32_t computed_checksum = Calculate_Checksum_On_Bytes(bytes + 2, length - 2);
   uint32_t computed_checksum = Calculate_Checksum_On_Bytes(bytes, length);
   return expected_checksum == computed_checksum;
}

/**
 * Writes the received block to flash and verifies that the correct data was written.
 * 
 * Returns true if the bytes are valid, and false otherwise.
 */
uint8_t Write_Firmware_Bytes(uint32_t address, const uint8_t *bytes, uint32_t length) {

   if (address < APP_START_ADDR || address > APP_END_ADDR) {
      return 0;
   }

   return Write_Program_Block(address, bytes, length) == 0;
}

/**
 * Retrieves the latest firmware from the firmware server and writes it to 
 * flash memory.
 */
uint8_t Update_Firmware() {
   uint8_t status = NULL;     // Stores the result of called functions, indicating the status of the operation of this function.
   uint8_t result = FALSE;     // Return value. Default to false, indicating failure to update the firmware.
   uint32_t block_index = 0;        // The current block index to receive, verify, and write to flash.
   uint32_t block_size = FIRMWARE_BLOCK_SIZE;        // The number of bytes to receive.
   uint32_t start_byte = 0;       // The first byte to receive in the firmware. This will be the first byte in the received block.

   Message * message;

   // TODO: Get total size of firmware (from firmware description).
   uint32_t firmware_size = DEFAULT_FIRMWARE_SIZE;     // Total size (in bytes) of the firmware being received.
   uint16_t firmware_checksum = DEFAULT_FIRMWARE_CHECKSUM;
   int bytes_received = 0;     // Total number of verified bytes received so far.
   int bytes_written = 0;     // Total number of bytes written to flash.
   Message * response_message;

   char uri_parameters[64] = { 0 };

   // Erase application from flash before getting data.
   Erase_Program_Flash();

   // Retrieve firmware size from the server.
   sprintf(uri_parameters, "/clay/firmware/size");

   response_message = WiFi_Send_With_Retries(Create_HTTP_GET_Request(FIRMWARE_SERVER_ADDRESS, local_address, uri_parameters),
                                             1,
                                             500);
   if (response_message != NULL) {
      firmware_size = Parse_Size_From_Message(response_message);
      Delete_Message(response_message);
      response_message = NULL;
   }

   /* Update the stored application firmware size and checksum.
    * These are used to indicate what should be on the device. */

   // Write the size of the application firmware to flash.
   // The stored size is used in CRC-16 checksum computations.
   if ((status = Write_Program_Size(firmware_size)) == 0) {
      // TODO: store result of above function and only return TRUE if it's been written successfully!

      // The firmware updated successfully, so read it back from flash and use it in
      // the computation of the checksum below as a test of its correctness.
//		firmwareSize = Read_Program_Size ();

   }

   // Retrieve firmware checksum from the server.
   sprintf(uri_parameters, "/clay/firmware/checksum");
   response_message = WiFi_Send_With_Retries(Create_HTTP_GET_Request(FIRMWARE_SERVER_ADDRESS, local_address, uri_parameters),
                                             5,
                                             500);
   if (response_message != NULL) {
      firmware_checksum = Parse_Checksum_From_Message(response_message);
      Delete_Message(response_message);
      response_message = NULL;
   }

   // Write checksum to flash and (TODO) verify it.
   if (firmware_size > 0 && firmware_checksum > 0 && (status = Write_Program_Checksum(firmware_checksum)) == 0) {
      // TODO: store result of above function and only return TRUE if it's been written successfully!

//		// The firmware updated successfully, so reset the flag indicating a new firmware update is available.
//		SharedData.ApplicationUpdateAvailable = FALSE;
//		SharedData.UpdateApplication = FALSE;

      // Compare the computed checksum of the received data to the expected checksum.
      // If they're equal, return true, indicating that the firmware was successfully
      // written to flash and verified.
//		return result = TRUE;

   }

   // Retrieve firmware if is hasn't yet been received in its entirety.
   while (bytes_received < firmware_size) {

      start_byte = block_index * block_size;     // Determine the first byte to receive in the block based on the current block index.
      sprintf(uri_parameters, "/clay/firmware/?startByte=%d&byteCount=%d", start_byte, block_size);
      response_message = WiFi_Send_With_Retries(Create_HTTP_GET_Request(FIRMWARE_SERVER_ADDRESS, local_address, uri_parameters),
                                                5,
                                                500);

      if (response_message != NULL) {
         bytes_received += response_message->content_length;

         Write_Firmware_Bytes(start_byte, response_message->content, bytes_received);

         // TODO: Implement per-block length/checksum fields on server messages.

         //verify message
         //retry if necessary
         // Update the number of received bytes.
         // Write the received bytes to application memory in flash.

         Delete_Message(response_message);
         response_message = NULL;

         // Advance to the next byte.
         block_index = block_index + 1;
      }
   }

   if (Verify_Firmware()) {
      // The firmware updated successfully, so reset the flag indicating a new firmware update is available.
      SharedData.ApplicationUpdateAvailable = FALSE;
      SharedData.UpdateApplication = FALSE;

      result = TRUE;
   } else {
      //start over. max retries?
   }

   return result;
}

/**
 * Writes the start address of the main application firmware to the program 
 * counter.
 */
void Update_Program_Counter(uint32_t address) {
// Load new stack pointer address
   asm("LDR SP, [R0]");
// Load new program counter address
   asm("LDR PC, [R0,#4]");
}

void Jump_To_Application() {
//change vector table offset register to application vector table
   SCB_VTOR = APP_START_ADDR & 0x1FFFFF80;

//set stack pointer/pc to the reset interrupt.
   Update_Program_Counter(APP_START_ADDR);
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

bool Get_WiFi_Connection_Status() {
   bool result = FALSE;
   Message * response;

   if (WiFi_Request_Get_Connection_Status()) {

      if ((response = WiFi_Wait_For_Message(REQUEST_WAIT_TIME_ms)) != NULL) {

         result = Parse_Wifi_Connection_Message(response);

         Delete_Message(response);
      }
   }

   return result;
}

bool Parse_Wifi_Connection_Message(Message * response) {

   bool result = FALSE;
   int token_count = 0;

   token_count = Get_Token_Count((*response).content);

   if (Message_Content_Parameter_Equals(response, FIRST_PARAMETER, "wifi")) {
      if (Message_Content_Parameter_Equals(response, SECOND_PARAMETER, "connected")) {
         result = TRUE;
      } else if (Message_Content_Parameter_Equals(response, SECOND_PARAMETER, "disconnected")) {
         result = FALSE;
      }
   }

   return result;
}

bool Get_Local_Address() {

   bool result = FALSE;
   Message * response;

   if (WiFi_Request_Get_Internet_Address()) {
      //wait for response

      if ((response = WiFi_Wait_For_Message(REQUEST_WAIT_TIME_ms)) != NULL) {

         result = Parse_Wifi_Address_Message(response);

         Delete_Message(response);
      }

   }

   return result;
}

bool Parse_Wifi_Address_Message(Message * response) {

   bool result = false;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
   int token_count = 0;

   if (Message_Content_Parameter_Equals(response, FIRST_PARAMETER, "wifi")) {
      if (Message_Content_Parameter_Equals(response, SECOND_PARAMETER, "address")) {

         Get_Token((*response).content, token, THIRD_PARAMETER);
         sprintf(local_address, "%s:%d", token, 3000);

         result = true;
      }
   }

   return result;
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

static uint8_t Message_Content_Parameter_Equals(Message *message, int token_index, const char *pattern) {

   int8_t status = NULL;
   int8_t result = NULL;
   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };
   if ((status = Get_Token(message_content, token, token_index)) != 0) {
      if (strncmp(token, pattern, strlen(pattern)) == 0) {
         return TRUE;
      }
   }
   return FALSE;
}

static uint32_t Parse_Size_From_Message(Message * message) {
   uint32_t rval = 0;

   if (message != NULL) {
      rval = atoi(message->content);
   }

   return rval;
}

static uint16_t Parse_Checksum_From_Message(Message * message) {

   uint16_t rval = 0;

   if (message != NULL) {
      rval = (atoi(message->content));
   }

   return rval;
}

static uint32_t Parse_Version_From_Message(Message * message) {

   uint32_t rval = 0;

   if (message != NULL) {
      rval = (atoi(message->content));
   }

   return rval;

   return rval;
}

////CRC test code, tested against http://www.lammertbies.nl/comm/info/crc-calculation.html 
////vars
//uint16_t result[11] = { 0 };
//static unsigned char* testchars[11] = {          //should be this value
//        { "hello" },                             //0x34D2
//        { "helloholol moore goobon" },           //0x6498
//        { "saoeubskcso" },                       //0x7378
//        { "123456789" },                         //0xBB3D
//        { "aoeuaoeuueoaueoa" },                  //0x2F4A
//        { "',.p',.pp.,'" },                      //0x132A
//        { "qkj;xkuux.yxy" },                     //0x0B87
//        { "okbsncvsaklrocsb" },                  //0x20F1
//        { "oknkbonbknoobknoknb" },               //0x0990
//        { "cnusda" },                            //0xA5E0
//        { "goodbye" } };                         //0xC596
//
////code    
//for (;;)
//{
//    int i;
//    for (i = 0; i < 11; ++i)
//    {
//        result[i] = gen_crc16(testchars[i], strlen(testchars[i]));
//    }
//}
