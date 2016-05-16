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
typedef enum
{
   INTERACTIVE_ASSEMBLY_NONE,                       //nothing happening; haven't received any button presses
   INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER,         //received button press locally first
   INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE,     //user pushed the button on this module after receiving a message telling it to be input
   INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING,        //received message saying we should be config'd as input
   INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER,        //received button press locally first
   INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE,     //user pushed the button on this module after receiving a message telling it to be output
   INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING,       //received message saying we should be config'd as output.
   INTERACTIVE_ASSEMBLY_CHANNEL_STATE_MAX
} Interactive_Assembly_Channel_State;

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
extern void Interactive_Assembly_Periodic_Call();
#endif
