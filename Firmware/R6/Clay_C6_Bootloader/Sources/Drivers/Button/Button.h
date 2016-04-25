#ifndef BUTTON_H
#define BUTTON_H

//extern bool Is_Button_Pressed ();

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

////Macros ////////////////////////////////////////////////////////
#define BUTTON_CALLBACK_COUNT 10

////Typedefs  /////////////////////////////////////////////////////
typedef void (*Button_Handler)(void);

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////

extern bool Button_Enable();
extern void Button_Disable();
extern bool Button_Get_Status();

extern bool Button_Register_Press_Response(Button_Handler handler);
extern void Button_Unregister_Press_Response(Button_Handler handler);

extern bool Button_Register_Hold_Response(uint32_t duration_ms, Button_Handler handler);
extern void Button_Unregister_Hold_Response(Button_Handler handler);

extern bool Button_Register_Release_Response(Button_Handler handler);
extern void Button_Unregister_Release_Response(Button_Handler handler);

extern void Button_Periodic_Call();
extern void Button_Event_Handler();

#endif
