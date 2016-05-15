#ifndef INTERACTIVE_ASSEMBLY_H
#define INTERACTIVE_ASSEMBLY_H

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"
#include "RGB_LED.h"
#include "Message.h"

////Macros ////////////////////////////////////////////////////////
#define DEFAULT_BUTTON_HOLD_TIME 1000
#define DEFAULT_BUTTON_MODE_TIMEOUT 2000

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
extern int8_t button_mode;     // 0 = default, 1 = select channel
extern uint32_t button_mode_timeout;

////Function Prototypes ///////////////////////////////////////////

extern int8_t Enable_Interactive_Assembly();
extern void Request_Reset_Button();
extern void Request_Change_Selected_Channel();
extern void Change_Selected_Channel();
extern void Request_Change_Selected_Channel_Mode();
extern int8_t Process_Interactive_Assembly_Message(Message * message);

#endif
