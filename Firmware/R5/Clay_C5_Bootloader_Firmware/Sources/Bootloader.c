#include "Bootloader.h"

uint8_t bootloaderMode = TRUE; // Flag indicating if the unit is in bootloader mode.

/**
 * Verifies the current firmware in flash. Computes the checksum of the 
 * current flash and compares it to the expected value stored at the end 
 * of the flash memory.
 */
uint8_t Verify_Firmware () {
	return TRUE;
}

/**
 * Gets the checksum of the most recent firmware from the server and compares 
 * it to the computed checksum of the device's current firmware. This function 
 * is used to decide whether or not to update the firmware by calling 
 * Update_Firmware (...).
 * 
 * Returns TRUE if the checksums are the same. False if they are different.
 */
uint8_t Has_Latest_Firmware () {
	return FALSE;
}

/**
 * Calculates the checksum for the specified bytes. This function is used by 
 * Verify_Firmware_Bytes (...) to compute the checksum on the received block.
 */
uint32_t Calculate_Checksum_On_Bytes (const uint8_t *bytes, uint32_t length) {
	
}

/**
 * Verifies that the received block was successfully received.
 * 
 * Returns TRUE if the bytes are valid, and FALSE otherwise.
 */
uint8_t Verify_Firmware_Bytes (const uint8_t *bytes, uint32_t length) {
	
	// TODO: Extract the received checksum from the front of the received data.
	
	// TODO: Compute the checksum of the actual bytes constituting the received firmware segment.
	// TODO: i.e., Calculate_Checksum_On_Bytes (bytes + offset, length - offset);
	
	// TODO: Compare the extracted checksum (1) to the computed checksum (2).
	
	// TODO: If the checksums are equal, return TRUE. Otherwise, return FALSE;
	
	return TRUE;
}

/**
 * Writes the received block to flash and verifies that the correct data was written.
 * 
 * Returns TRUE if the bytes are valid, and FALSE otherwise.
 */
uint8_t Write_Firmware_Bytes (const uint8_t *bytes, uint32_t length) {
	
	// TODO: Write the received bytes to application memory in flash.
	
	return TRUE;
}

void Update_Firmware () {
	
	uint8_t result = NULL;
	uint32_t blockIndex = 0; // The current block index to receive, verify, and write to flash.
	uint32_t blockSize = 512; // The number of bytes to receive.
	uint32_t startByte = 0; // The first byte to receive in the firmware. This will be the first byte in the received block.
	
	char *address = "192.168.2.132";
	uint16_t port = 8080;
	
	char uriParameters[32] = { 0 };
	
	int connection = 4; // HACK: Get the connection used from Send_HTTP_GET_Request (...).
	
	// TODO: Get total size of firmware (from firmware description).
	uint32_t firmwareSize = 45108; // Total size (in bytes) of the firmware being received. // TODO: Receive this from preliminary HTTP request.
	uint32_t bytesReceived = 0; // Total number of verified bytes received so far.
	uint32_t bytesWritten = 0; // Total number of bytes written to flash.
	
	// Check firmware version
//	hasLatestFirmware = FALSE; // HACK
//	if (!hasLatestFirmware) {
	
	// Retrieve firmware if is hasn't yet been received in its entirety.
	while (bytesReceived < firmwareSize) {
		
		// TODO: Download the latest firmware via HTTP request
		
		// Get the new firmware in chunks, perform checksum on each one (retry if fail, continue to next chunk if success), write the verified chunk into flash
		startByte = blockIndex * blockSize; // Determine the first byte to receive in the block based on the current block index.
		sprintf (uriParameters, "/firmware?start=%d&size=%d", startByte, blockSize);
		Send_HTTP_GET_Request (address, port, uriParameters); // HTTP GET /firmware/version
		// TODO: Inside the Send_HTTP_GET_Request (...) function, block on ESP8266_Wait_For_Response (...), but only after disabling the other communications (namely, UDP broadcasts, since that will add to the ESP8266 buffer, causing the ESP8266_Wait_For_Response (...) function to erroneously proceed, and get stuck in a timer reset loop, since it always gets some data from the UDP broadcast).
		
		strncpy (firmwareBuffer, connectionDataQueue[connection], connectionDataQueueSize[connection]); // Copy the received data into a response buffer.
		
		// Verify the received data.
		if ((result = Verify_Firmware_Bytes (firmwareBuffer, firmwareBufferSize)) != NULL) {
			
			// Update the number of received bytes.
			bytesReceived = bytesReceived + firmwareBufferSize;
			
			// Write the received bytes to application memory in flash.
			if ((result = Write_Firmware_Bytes (firmwareBuffer, firmwareBufferSize)) != NULL) {
				
				// The byte was successfully written.
				bytesWritten = bytesWritten + firmwareBufferSize;
				
				// Advance to the next byte.
				blockIndex = blockIndex + 1;
				
			} else {
				
				// The byte was not successfully written. Retry?
				
			}
			
		} else {
			
			// TODO: Retry receiving the segment.
		}
		
		// 
	}
	
	// TODO: Upon successfully downloading, verifying, and writing flash to program memory, jump to program memory and start executing the new firmware.
}
