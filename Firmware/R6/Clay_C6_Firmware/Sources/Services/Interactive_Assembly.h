#ifndef INTERACTIVE_ASSEMBLY_H
#define INTERACTIVE_ASSEMBLY_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include "RGB_LED.h"

#define DEFAULT_BUTTON_HOLD_TIME 1000
#define DEFAULT_BUTTON_MODE_TIMEOUT 2000

extern int8_t button_mode; // 0 = default, 1 = select channel
extern uint32_t button_mode_timeout;
extern int8_t selected_channel;
extern int8_t selected_channel_mode;
extern int8_t changed_channel_mode;

extern int8_t Enable_Interactive_Assembly ();
extern void Request_Reset_Button ();
extern void Request_Change_Selected_Channel ();
extern void Change_Selected_Channel ();
extern void Request_Change_Selected_Channel_Mode ();

#endif
