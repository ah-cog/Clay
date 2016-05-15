// TODO: Implement callback timer and timeout reset (like in JavaScript).

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"
#include "Interactive_Assembly.h"
#include "Button.h"
#include "Application.h"
#include "Message.h"

#include "UDP_Discovery_temp.h"

////Macros ////////////////////////////////////////////////////////

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
int8_t button_mode = 0;     // 0 = default, 1 = select channel
uint32_t button_mode_timeout = 0;

////Local vars/////////////////////////////////////////////////////
static Interactive_Assembly_Channel_State state;
static int8_t selected_channel = -1;
static int8_t changed_channel_mode = FALSE;

////Local Prototypes///////////////////////////////////////////////
static void Request_Remote_Channel();
static void Cancel_Last_Channel_Request();
static void Accept_Channel_Request();

////Global implementations ////////////////////////////////////////

int8_t Enable_Interactive_Assembly() {
   Button_Register_Release_Response(&Request_Change_Selected_Channel);
   Button_Register_Hold_Response(DEFAULT_BUTTON_HOLD_TIME, &Request_Change_Selected_Channel_Mode);
   state = INTERACTIVE_ASSEMBLY_NONE;
   return TRUE;
}

void Request_Reset_Button() {
   int i;

   // Reset button logic state
   button_mode = 0;
   button_mode_timeout = 0;
   selected_channel--;     //Don't reset to -1. Michael likes the selected channel to be remembered. Allows picking up where left off.

   changed_channel_mode = FALSE;

   // Reset the state of all lights
   for (i = 0; i < 12; i++) {
      proposed_light_profiles[i].enabled = TRUE;
      Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
   }

   state = INTERACTIVE_ASSEMBLY_NONE;
   Cancel_Last_Channel_Request();

   // Apply the new light states
   Apply_Channels();
   Apply_Channel_Lights();
}

void Request_Change_Selected_Channel() {

   if (state == INTERACTIVE_ASSEMBLY_NONE) {
      state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER;
   }

   button_mode_timeout = DEFAULT_BUTTON_MODE_TIMEOUT;

   if (changed_channel_mode == TRUE) {
      changed_channel_mode = FALSE;
   } else {
      Change_Selected_Channel();
   }
}

void Change_Selected_Channel() {
   int i;
   selected_channel = (selected_channel + 1) % 12;

   if (state == INTERACTIVE_ASSEMBLY_NONE || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {
      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {
         state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE;
      } else {
         state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER;
      }
   } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING) {
      state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE;
   }

   if (selected_channel >= 0 && selected_channel < 12) {

      // Reset the state of all lights
      for (i = 0; i < 12; i++) {
         proposed_light_profiles[i].enabled = TRUE;
         Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
      }

      // Set the state of the selected channel's light
      proposed_light_profiles[selected_channel].enabled = TRUE;

      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
         Set_Light_Color(&proposed_light_profiles[selected_channel], 50, 160, 200);
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE) {
         Set_Light_Color(&proposed_light_profiles[selected_channel], 250, 90, 20);
      }

      // TODO: Set the selected channel as input (if first device)

      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
         Request_Remote_Channel();
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE) {
         Accept_Channel_Request();
      }

      // Apply the new light states
      Apply_Channels();
      Apply_Channel_Lights();
   }
}

void Request_Change_Selected_Channel_Mode() {

   if (changed_channel_mode == FALSE) {
      if (state == INTERACTIVE_ASSEMBLY_NONE
          || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING
          || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
         if (state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {
            state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE;
         } else {
            state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER;
         }
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING) {
         state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE;
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
         state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER;
      }

      changed_channel_mode = TRUE;

      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
         Set_Light_Color(&proposed_light_profiles[selected_channel], 50, 160, 200);
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
         Set_Light_Color(&proposed_light_profiles[selected_channel], 250, 90, 20);
      }

      // TODO: Set the selected channel as input (if first device)

      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
         Request_Remote_Channel();
      }

      // Apply the new light states
      Apply_Channels();
      Apply_Channel_Lights();
   }
}

#define REQUEST_KEYWORD  "request"
#define ACCEPT_KEYWORD  "accept"
#define INPUT_KEYWORD  "input"
#define OUTPUT_KEYWORD "output"
#define CANCEL_KEYWORD "cancel"
static char interactive_assembly_message_type[20];
static char interactive_assembly_message_content[20];
static char remote_module_address[50];

int8_t Process_Interactive_Assembly_Message(Message * message) {

   //examples:
   //request interactive_assembly output
   //request interactive_assembly input
   //request interactive_assembly cancel
   //request interactive_assembly accept

   int8_t status = FALSE;
   int8_t result = FALSE;

   int token_count = 0;

   char *message_content = (*message).content;
   char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

   // Extract parameters
   result = Get_Token(message_content, interactive_assembly_message_type, 1);     // Get the message type (parameter index 1)
   result &= Get_Token(message_content, interactive_assembly_message_content, 2);     // Get the message content (parameter index 2)

   if (result) {

      if (strncmp(interactive_assembly_message_type, REQUEST_KEYWORD, strlen(REQUEST_KEYWORD)) == 0) {

         if (strncmp(interactive_assembly_message_content, INPUT_KEYWORD, strlen(INPUT_KEYWORD)) == 0) {
            state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING;
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING;
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, CANCEL_KEYWORD, strlen(CANCEL_KEYWORD)) == 0) {
            if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING
                || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING
                || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE
                || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE) {
               Request_Reset_Button();
            }
            result = TRUE;
         }
      } else if (strncmp(interactive_assembly_message_type, ACCEPT_KEYWORD, strlen(ACCEPT_KEYWORD)) == 0) {
         if (strncmp(interactive_assembly_message_content, INPUT_KEYWORD, strlen(INPUT_KEYWORD)) == 0) {
            if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
               //remote has the right config
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
               //remote has the right config
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, CANCEL_KEYWORD, strlen(CANCEL_KEYWORD)) == 0) {
            result = TRUE;
         }
      }
   }

   if (result && state != INTERACTIVE_ASSEMBLY_NONE) {
      //store the other guy's IP as remote.
      sprintf(remote_module_address, (*message).source);
      *(remote_module_address + strlen(remote_module_address) - 1) = '6';     //HACK: we need the port to be 4446

      //we can look up the remote address in the UDP discovery table if we want to know its uuid.
   }

   return result;
}

////Local implementations /////////////////////////////////////////
static void Request_Remote_Channel() {

   Message * m = NULL;
   if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {

      m = Create_Message("interactive_assembly request output");

   } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {

      m = Create_Message("interactive_assembly request input");
   }

   if (m != NULL) {

      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, broadcast_address_module);

      Wifi_Send(m);
   }
}

static void Cancel_Last_Channel_Request() {

   Message * m = Create_Message("interactive_assembly request cancel");
   Set_Message_Type(m, "udp");
   Set_Message_Source(m, local_address);
   Set_Message_Destination(m, broadcast_address_module);

   Wifi_Send(m);
}

static void Accept_Channel_Request() {

   Message * m;

   if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
      m = Create_Message("interactive_assembly accept input");
   } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE) {
      m = Create_Message("interactive_assembly accept output");
   }

   if (m != NULL) {
      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, remote_module_address);

      Wifi_Send(m);
   }
}
