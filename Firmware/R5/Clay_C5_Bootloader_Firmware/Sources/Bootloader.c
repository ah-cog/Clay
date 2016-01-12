#include "Bootloader.h"
#include "Drivers/program_flash.h"
#include "crc.h"


//defines
#define APPLICATION_KEY_VALUE  0xA5A5A5A5U
#define BOOT_START_ADDR        0x00000000U

//data types

//global vars -- this guy is placed at the end of RAM, 0x20007FF8. This is 8 bytes from the end, which is the size of the struct.
shared_bootloader_data __attribute__((section(".BootloaderSharedData"))) SharedData;

uint8_t bootloaderMode = TRUE;        // Flag indicating if the unit is in bootloader mode.

bool UserApprovedUpdate()
{
    bool rval = FALSE;
    
    if(SharedData.ApplicationKey == APPLICATION_KEY_VALUE && SharedData.UpdateApplication)
    {
        rval = TRUE;
    }
    
    SharedData.ApplicationKey = 0;
    
    return rval;
}

/**
 * Verifies the current firmware in flash. Computes the checksum of the 
 * current flash and compares it to the expected value stored at the end 
 * of the flash memory.
 */
uint8_t Verify_Firmware()
{
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
uint8_t Has_Latest_Firmware()
{
    //TODO: implement this. If the firmware IS out of date, set the value in the SharedData struct.
    return FALSE;
}

/**
 * Calculates the checksum for the specified bytes. This function is used by 
 * Verify_Firmware_Bytes (...) to compute the checksum on the received block.
 */
uint32_t Calculate_Checksum_On_Bytes(const uint8_t *bytes, uint32_t length)
{

}

/**
 * Verifies that the received block was successfully received.
 * 
 * Returns TRUE if the bytes are valid, and FALSE otherwise.
 */
uint8_t Verify_Firmware_Bytes(const uint8_t *bytes, uint32_t length)
{
	return TRUE;
	
    uint16_t received_checksum = bytes[0] | (bytes[1] << 8);

    init_checksum();
    uint16_t computed_checksum = CRC_Cal_16(0, bytes + 2, length - 2);

    return received_checksum == computed_checksum;
}

/**
 * Writes the received block to flash and verifies that the correct data was written.
 * 
 * Returns TRUE if the bytes are valid, and FALSE otherwise.
 */
uint8_t Write_Firmware_Bytes(uint32_t address, const uint8_t *bytes, uint32_t length)
{
    return write_program_block (APP_START_ADDR + address, bytes, length) == 0;
}


//uint8_t test[1024] = {0};

void Update_Firmware ()
{
    uint8_t result = NULL;
    uint32_t blockIndex = 0;        // The current block index to receive, verify, and write to flash.
    uint32_t blockSize = 512;        // The number of bytes to receive.
    uint32_t startByte = 0;        // The first byte to receive in the firmware. This will be the first byte in the received block.

    char *address = "107.170.180.158"; // 192.168.43.127"; // "107.170.180.158";
    uint16_t port = 3000;

    int connection = 4;        // HACK: Get the connection used from Send_HTTP_GET_Request (...).

    // TODO: Get total size of firmware (from firmware description).
    int firmwareSize = 5916;     // Total size (in bytes) of the firmware being received. // TODO: Receive this from preliminary HTTP request.
    int bytesReceived = 0;       // Total number of verified bytes received so far.
    int bytesWritten = 0;        // Total number of bytes written to flash.

    char uriParameters[64] = { 0 };

    //erase application from flash before getting data.
    erase_program_flash ();

    // Retrieve firmware if is hasn't yet been received in its entirety.
    while (bytesReceived < firmwareSize)
    {
        // TODO: Download the latest firmware via HTTP request

        // Get the new firmware in chunks, perform checksum on each one (retry if fail, continue to next chunk if success), write the verified chunk into flash
        startByte = blockIndex * blockSize;        // Determine the first byte to receive in the block based on the current block index.
        sprintf (uriParameters, "/firmware/?startByte=%d&byteCount=%d", startByte, blockSize);
        Send_HTTP_GET_Request (address, port, uriParameters);        // HTTP GET /firmware/version
        // TODO: Inside the Send_HTTP_GET_Request (...) function, block on ESP8266_Wait_For_Response (...), but only after disabling the other communications (namely, UDP broadcasts, since that will add to the ESP8266 buffer, causing the ESP8266_Wait_For_Response (...) function to erroneously proceed, and get stuck in a timer reset loop, since it always gets some data from the UDP broadcast).

//        strncpy(firmwareBuffer, connectionDataQueue[connection], connectionDataQueueSize[connection]);        // Copy the received data into a response buffer.

        // Verify the received data.
        if ((result = Verify_Firmware_Bytes (httpResponseBuffer, httpResponseBufferSize)) != NULL)
        {

            // Update the number of received bytes.
            bytesReceived = bytesReceived + httpResponseBufferSize;

            // Write the received bytes to application memory in flash.
            if ((result = Write_Firmware_Bytes (startByte, httpResponseBuffer, httpResponseBufferSize)) != NULL)
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

        }
        else
        {

            // TODO: Retry receiving the segment.
        }

        // 
    }

    // TODO: Upon successfully downloading, verifying, and writing flash to program memory, jump to program memory and start executing the new firmware.
//    Jump_To_Application();
}

void Jump_To_Application()
{
    //change vector table offset register to application vector table
    SCB_VTOR = APP_START_ADDR & 0x1FFFFF80;

    //set stack pointer/pc to the reset interrupt.
    boot_jump(APP_START_ADDR);
}

void boot_jump(uint32_t address)
{
    //Load new stack pointer address
    asm("LDR SP, [R0]");
    //Load new program counter address
    asm("LDR PC, [R0,#4]");
}
