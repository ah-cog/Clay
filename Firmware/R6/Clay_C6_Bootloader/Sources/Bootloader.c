#include "Bootloader.h"
#include "Drivers/program_flash.h"

//data types

//global vars -- this guy is placed at the end of RAM, 0x20007FF8. This is 8 bytes from the end, which is the size of the struct.
shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;

uint8_t bootloaderMode = TRUE;        // Flag indicating if the unit is in bootloader mode.

uint8_t Initialize_Bootloader () {
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
bool Has_User_Requested_Update ()
{
    bool rval = FALSE;

    // Check if the value of the "application key" is equal to the value 
    // written by the main application firmware. If so, the bootloader was 
    // jumped into from the main application. To indicate this, set the
    // return value to true.
    if (SharedData.ApplicationKey == APPLICATION_KEY_VALUE && SharedData.UpdateApplication)
    {
        rval = TRUE;
    }

    // Reset the "application key".
    SharedData.ApplicationKey = 0;

    return rval;
}

/**
 * Verifies the current firmware in flash. Computes the checksum of the 
 * current flash and compares it to the expected value stored at the end 
 * of the flash memory.
 */
uint8_t Verify_Firmware ()
{
	uint8_t status = NULL;
	uint8_t result = FALSE;
	uint16_t applicationChecksum = 0;
	uint32_t applicationSize = 0;
	
	// Read size of application firmware from flash memory.
	applicationSize = Read_Program_Size ();
	
	// Read the checksum of the application firmware from flash memory.
	applicationChecksum = Read_Program_Checksum ();
	
	// Check if the values are uninitialized (i.e., check if they haven't yet 
	// been written.
	if (applicationSize == 0xFFFFFFFF || applicationChecksum == 0xFFFF) {
		
		result = FALSE;
		
	} else {
	
		// Compute the checksum of the application firmware stored in flash.
		// i.e., Verify the correctness of the entire program that has been written to flash memory.
		//       To do so, compare the computed CRC-16 checksum to the stored CRC-16 checksum.
		if ((status = Verify_Firmware_Bytes (APP_START_ADDR, applicationSize, applicationChecksum)) != NULL)
		{
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
uint8_t Has_Latest_Firmware ()
{
	uint8_t result = TRUE; // Return value. Default to true.
	uint16_t firmwareChecksum = NULL; // The stored checksum value.
	uint16_t latestFirmwareChecksum = NULL; // The checksum of the latest firmware.
	
	char *address = FIRMWARE_SERVER_ADDRESS;
	uint16_t port = FIRMWARE_SERVER_PORT;
	char uriParameters[64] = { 0 };
	
	// Retrieve firmware checksum from the server.
	sprintf (uriParameters, "/clay/firmware/checksum/");
	Send_HTTP_GET_Request (address, port, uriParameters);
	latestFirmwareChecksum = atoi (httpResponseBuffer);
	
	// Get the stored checksum
	firmwareChecksum = Read_Program_Checksum ();
	
	// Check if the checksum of the application firmware matches the checksum 
	// of the latest firmware received from the server.
	if (firmwareChecksum != latestFirmwareChecksum) {
		result = FALSE;
	}
	
    //TODO: implement this. If the firmware IS out of date, set the value in the SharedData struct.
    return result;
}

/**
 * Performs a cyclic redundancy check (CRC) according to the CRC-16 algorithm.
 * 
 * This implementation is based on an implementation on StackOverflow 
 * (https://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum).
 */
uint16_t Calculate_Checksum_On_Bytes (const uint8_t *data, uint32_t size)
{
    uint16_t out = 0;
    int bits_read = 0, bit_flag;

    /* Sanity check: */
    if (data == NULL)
        return 0;

    while (size > 0)
    {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1;
        out |= (*data >> bits_read) & 1;        // item a) work from the least significant bits

        /* Increment bit counter: */
        bits_read++;
        if (bits_read > 7)
        {
            bits_read = 0;
            data++;
            size--;
        }

        /* Cycle check: */
        if (bit_flag)
            out ^= CRC16;

    }

    // item b) "push out" the last 16 bits
    int i;
    for (i = 0; i < 16; ++i)
    {
        bit_flag = out >> 15;
        out <<= 1;
        if (bit_flag)
            out ^= CRC16;
    }

    // item c) reverse the bits
    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for (; i != 0; i >>= 1, j <<= 1)
    {
        if (i & out) crc |= j;
    }

    return crc;
}

/**
 * Verifies that the received block was successfully received.
 * 
 * Returns true if the bytes are valid, and false otherwise.
 */
uint8_t Verify_Firmware_Bytes(const uint8_t *bytes, uint32_t length, uint16_t expected_checksum)
{
//    uint16_t received_checksum = bytes[0] | (bytes[1] << 8);
//    uint32_t computed_checksum = Calculate_Checksum_On_Bytes(bytes + 2, length - 2);
    uint32_t computed_checksum = Calculate_Checksum_On_Bytes (bytes, length);
    return expected_checksum == computed_checksum;
}

/**
 * Writes the received block to flash and verifies that the correct data was written.
 * 
 * Returns true if the bytes are valid, and false otherwise.
 */
uint8_t Write_Firmware_Bytes (uint32_t address, const uint8_t *bytes, uint32_t length)
{
    return Write_Program_Block (APP_START_ADDR + address, bytes, length) == 0;
}

/**
 * Retrieves the latest firmware from the firmware server and writes it to 
 * flash memory.
 */
uint8_t Update_Firmware()
{
	uint8_t status = NULL; // Stores the result of called functions, indicating the status of the operation of this function.
	uint8_t result = FALSE; // Return value. Default to false, indicating failure to update the firmware.
	uint32_t blockIndex = 0;        // The current block index to receive, verify, and write to flash.
	uint32_t blockSize = FIRMWARE_BLOCK_SIZE;        // The number of bytes to receive.
	uint32_t startByte = 0;        // The first byte to receive in the firmware. This will be the first byte in the received block.

	char *address = FIRMWARE_SERVER_ADDRESS;
	uint16_t port = FIRMWARE_SERVER_PORT;

	int connection = 4;        // HACK: Get the connection used from Send_HTTP_GET_Request (...).

	// TODO: Get total size of firmware (from firmware description).
	uint32_t firmwareSize = DEFAULT_FIRMWARE_SIZE; // Total size (in bytes) of the firmware being received.
	uint16_t firmwareChecksum = DEFAULT_FIRMWARE_CHECKSUM;
	int bytesReceived = 0; // Total number of verified bytes received so far.
	int bytesWritten = 0; // Total number of bytes written to flash.

    char uriParameters[64] = { 0 };

    // Erase application from flash before getting data.
    Erase_Program_Flash ();
    
    // Retrieve firmware size from the server.
    sprintf (uriParameters, "/clay/firmware/size/");
	Send_HTTP_GET_Request (address, port, uriParameters);        // HTTP GET /firmware/version
	httpResponseBuffer[httpResponseBufferSize] = NULL; // Terminate the buffer contents
	firmwareSize = atoi (httpResponseBuffer);
	
	/* Update the stored application firmware size and checksum.
	 * These are used to indicate what should be on the device. */
	
	// Write the size of the application firmware to flash.
	// The stored size is used in CRC-16 checksum computations.
	if ((status = Write_Program_Size (firmwareSize)) == 0) {
		// TODO: store result of above function and only return TRUE if it's been written successfully!
		
		// The firmware updated successfully, so read it back from flash and use it in 
		// the computation of the checksum below as a test of its correctness.
//		firmwareSize = Read_Program_Size ();
		
	} else {
		
		// The write to memory failed!
		
	}
	
	// Retrieve firmware checksum from the server.
	sprintf (uriParameters, "/clay/firmware/checksum/");
	Send_HTTP_GET_Request (address, port, uriParameters);
	httpResponseBuffer[httpResponseBufferSize] = NULL; // Terminate the buffer contents
	firmwareChecksum = (uint32_t) atoi (httpResponseBuffer);
	
	// Write checksum to flash and (TODO) verify it.
	if ((status = Write_Program_Checksum (firmwareChecksum)) == 0) {
		// TODO: store result of above function and only return TRUE if it's been written successfully!
		
//		// The firmware updated successfully, so reset the flag indicating a new firmware update is available.
//		SharedData.ApplicationUpdateAvailable = FALSE;
//		SharedData.UpdateApplication = FALSE;
					
		// Compare the computed checksum of the received data to the expected checksum.
		// If they're equal, return true, indicating that the firmware was successfully 
		// written to flash and verified.
//		return result = TRUE;
		
	} else {
		
		// The write to memory failed!
		
	}

	// Retrieve firmware if is hasn't yet been received in its entirety.
    while (bytesReceived < firmwareSize)
    {
        // TODO: Download the latest firmware via HTTP request

        // Get the new firmware in chunks, perform checksum on each one (retry if fail, continue to next chunk if success), write the verified chunk into flash
        startByte = blockIndex * blockSize;        // Determine the first byte to receive in the block based on the current block index.
        sprintf(uriParameters, "/clay/firmware/?startByte=%d&byteCount=%d", startByte, blockSize);
        Send_HTTP_GET_Request(address, port, uriParameters);        // HTTP GET /firmware/version
        // TODO: Inside the Send_HTTP_GET_Request (...) function, block on ESP8266_Wait_For_Response (...), but only after disabling the other communications (namely, UDP broadcasts, since that will add to the ESP8266 buffer, causing the ESP8266_Wait_For_Response (...) function to erroneously proceed, and get stuck in a timer reset loop, since it always gets some data from the UDP broadcast).

//        strncpy(firmwareBuffer, connectionDataQueue[connection], connectionDataQueueSize[connection]);        // Copy the received data into a response buffer.

        // Verify the received data.
//        if ((status = Verify_Firmware_Bytes(httpResponseBuffer, httpResponseBufferSize)) != NULL)
//        {
        
        	// TODO: Implement per-block checksum!
//        	if ((status = Verify_Firmware_Bytes (httpResponseBuffer, httpResponseBufferSize)) != NULL)
//        	{
//        	}

            // Update the number of received bytes.
            bytesReceived = bytesReceived + httpResponseBufferSize;

            // Write the received bytes to application memory in flash.
            if ((status = Write_Firmware_Bytes (startByte, httpResponseBuffer, httpResponseBufferSize)) != NULL)
            {

                // The byte was successfully written.
                bytesWritten = bytesWritten + httpResponseBufferSize;

                // Advance to the next byte.
                blockIndex = blockIndex + 1;

            }
            else
            {

                // The byte was not successfully written. Retry?

            }

//        }
//        else
//        {
//
//            // TODO: Retry receiving the segment.
//        }

        // 
    }
    
//    // Retrieve firmware checksum from the server.
//	sprintf (uriParameters, "/clay/firmware/checksum/");
//	Send_HTTP_GET_Request (address, port, uriParameters);
//	firmwareChecksum = atoi (httpResponseBuffer);
	
	// At this point, the number of bytes written (bytesWritten) should be 
	// equal to the size of the application firmware that was stored prior to 
	// downloading the firmware (retrievable with Read_Program_Size ()).
	
	// To test that the correct application firmware checksum and size were 
	// stored in flash, read those stored values and use them in the 
	// computation of the checksum.
	
	firmwareSize = Read_Program_Size (); // Read the application firmware size from flash memory.
	firmwareChecksum = Read_Program_Checksum (); // Read the application firmware checksum from flash memory.
    
    // Verify the correctness of the entire program that has been written to flash memory.
	// To do so, compare the computed CRC-16 checksum to the received (from the firmware 
	// server) then stored (to flash) then loaded (from flash) CRC-16 checksum.
	if ((status = Verify_Firmware_Bytes (APP_START_ADDR, firmwareSize, firmwareChecksum)) != NULL)
	{
//		// Write the size of the application firmware to flash.
//		// The stored size is used in CRC-16 checksum computations.
//		if ((status = Write_Program_Size (bytesWritten)) == 0) {
//			// TODO: store result of above function and only return TRUE if it's been written successfully!
//			
//			// The firmware updated successfully, so read it back from flash and use it in 
//			// the computation of the checksum below as a test of its correctness.
//			firmwareSize = Read_Program_Size ();
//			
//		} else {
//			
//			// The write to memory failed!
//			
//		}
//		
//    	// Write checksum to flash and (TODO) verify it.
//    	if ((status = Write_Program_Checksum (firmwareChecksum)) == 0) {
//			// TODO: store result of above function and only return TRUE if it's been written successfully!
//    		
//    		// The firmware updated successfully, so reset the flag indicating a new firmware update is available.
//    		SharedData.ApplicationUpdateAvailable = FALSE;
//    		SharedData.UpdateApplication = FALSE;
//						
//			// Compare the computed checksum of the received data to the expected checksum.
//			// If they're equal, return true, indicating that the firmware was successfully 
//			// written to flash and verified.
//			return result = TRUE;
//			
//    	} else {
//    		
//    		// The write to memory failed!
//    		
//    	}
		
		// The firmware updated successfully, so reset the flag indicating a new firmware update is available.
		SharedData.ApplicationUpdateAvailable = FALSE;
		SharedData.UpdateApplication = FALSE;
		
		result = TRUE;
	}
    
    return result;

// TODO: Upon successfully downloading, verifying, and writing flash to program memory, jump to program memory and start executing the new firmware.
//    Jump_To_Application();
}

/**
 * Writes the start address of the main application firmware to the program 
 * counter.
 */
void Update_Program_Counter (uint32_t address)
{
	// Load new stack pointer address
    asm("LDR SP, [R0]");
    // Load new program counter address
    asm("LDR PC, [R0,#4]");
}

/**
 * Disables all interrupts.
 */
void Disable_Interrupts ()
{
	NVICICER0 = 0xFFFFFFFF;
	NVICICER1 = 0xFFFFFFFF;
	NVICICER2 = 0xFFFFFFFF;
	NVICICER3 = 0xFFFFFFFF;
}

void Jump_To_Application ()
{
	//change vector table offset register to application vector table
    SCB_VTOR = APP_START_ADDR & 0x1FFFFF80;

    //set stack pointer/pc to the reset interrupt.
    Update_Program_Counter (APP_START_ADDR);
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
