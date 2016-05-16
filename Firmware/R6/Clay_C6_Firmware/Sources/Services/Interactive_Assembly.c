// TODO: Implement callback timer and timeout reset (like in JavaScript).

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"
#include "Interactive_Assembly.h"
#include "Button.h"
#include "Application.h"
#include "Message.h"

#include "GPIO.h"

#include "UDP_Discovery_temp.h"

////Macros ////////////////////////////////////////////////////////
#define REQUEST_KEYWORD  "request"
#define ACCEPT_KEYWORD  "accept"
#define UPDATE_KEYWORD  "update"
#define INPUT_KEYWORD  "input"
#define OUTPUT_KEYWORD "output"
#define CANCEL_KEYWORD "cancel"

#define IS_INPUT(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE)
#define IS_OUTPUT(x)    (x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE)
#define IS_MASTER(x)    (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER)
#define IS_SLAVE(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE)
#define IS_PENDING(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING)

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
int8_t button_mode = 0;     // 0 = default, 1 = select channel
uint32_t button_mode_timeout = 0;

////Local vars/////////////////////////////////////////////////////
static Interactive_Assembly_Channel_State state;
static int8_t selected_channel = -1;
static int8_t changed_channel_mode = FALSE;

static char interactive_assembly_message_type[20];
static char interactive_assembly_message_content[20];
static char remote_module_address[50];

static bool channel_active;

////Local Prototypes///////////////////////////////////////////////
static void Request_Remote_Channel();
static void Cancel_Channel_Request();
static void Accept_Channel_Request();
static void Interactive_Assembly_Apply_State(Interactive_Assembly_Channel_State new_state, bool local_initiated);

////Global implementations ////////////////////////////////////////

int8_t Enable_Interactive_Assembly() {
   Button_Register_Release_Response(&Request_Change_Selected_Channel);
   Button_Register_Hold_Response(DEFAULT_BUTTON_HOLD_TIME, &Request_Change_Selected_Channel_Mode);
   state = INTERACTIVE_ASSEMBLY_NONE;
   channel_active = FALSE;
   return TRUE;
}

void Request_Reset_Button() {

   // Reset button logic state
   button_mode = 0;
   button_mode_timeout = 0;
   channel_active = FALSE;
   selected_channel--;     //Don't reset to -1. Michael likes the selected channel to be remembered. Allows picking up where left off.

   changed_channel_mode = FALSE;

   // Reset the state of all lights
   for (int i = 0; i < 12; i++) {
      proposed_light_profiles[i].enabled = TRUE;
      Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
   }

   state = INTERACTIVE_ASSEMBLY_NONE;
   Cancel_Channel_Request();

   // Apply the new light states
   Apply_Channels();
   Apply_Channel_Lights();
}

void Request_Change_Selected_Channel() {

   button_mode_timeout = DEFAULT_BUTTON_MODE_TIMEOUT;

   if (changed_channel_mode == TRUE) {
      changed_channel_mode = FALSE;
   } else {
      Change_Selected_Channel();
   }
}

void Change_Selected_Channel() {

   Interactive_Assembly_Channel_State new_state = state;

   selected_channel = (selected_channel + 1) % 12;

   if (state == INTERACTIVE_ASSEMBLY_NONE || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {

      if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE;
      } else {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER;
      }

   } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING) {
      new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE;
   }

   //apply the state.
   Interactive_Assembly_Apply_State(new_state, TRUE);
}

void Request_Change_Selected_Channel_Mode() {

   Interactive_Assembly_Channel_State new_state = state;

   if (changed_channel_mode == FALSE) {
      if (state == INTERACTIVE_ASSEMBLY_NONE
          || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING
          || state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
         if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING) {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE;
         } else {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER;
         }
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING) {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE;
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER;
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE;     //we remain the 'slave', but maybe we need a different term for this now that it's not really a slave anymore, or maybe we need to do away with these states?
      } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE) {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE;     //we remain the 'slave', but maybe we need a different term for this now that it's not really a slave anymore, or maybe we need to do away with these states?
      }

      changed_channel_mode = TRUE;

      Interactive_Assembly_Apply_State(new_state, TRUE);
   }
}

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
            if (!channel_active) {
               //received request to set up channel as input
               state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING;
            } else {
               //already connected, remote requested that we change to an input
               if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
                  Interactive_Assembly_Apply_State(INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER, FALSE);
               } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
                  Interactive_Assembly_Apply_State(INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE, FALSE);
               }
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            if (!channel_active) {
               //received request to set up channel as output
               state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING;
            } else {
               //already connected, remote requested that we change to an output
               if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
                  Interactive_Assembly_Apply_State(INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER, FALSE);
               } else if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE) {
                  Interactive_Assembly_Apply_State(INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SLAVE, FALSE);
               }
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, CANCEL_KEYWORD, strlen(CANCEL_KEYWORD)) == 0) {
            if (channel_active) {
               Request_Reset_Button();
            }
            result = TRUE;
         }
      } else if (strncmp(interactive_assembly_message_type, ACCEPT_KEYWORD, strlen(ACCEPT_KEYWORD)) == 0) {
         if (strncmp(interactive_assembly_message_content, INPUT_KEYWORD, strlen(INPUT_KEYWORD)) == 0) {
            if (state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_MASTER) {
               //remote has the right config
               button_mode_timeout = 0;
               channel_active = TRUE;
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            if (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER) {
               //remote has the right config
               button_mode_timeout = 0;
               channel_active = TRUE;
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, CANCEL_KEYWORD, strlen(CANCEL_KEYWORD)) == 0) {
            //remote cancelled
            Request_Reset_Button();
            result = TRUE;
         }
      } else if (strncmp(interactive_assembly_message_type, UPDATE_KEYWORD, strlen(UPDATE_KEYWORD)) == 0) {
         //received state from remote. update the output.

         ////Process received data here, if not already handled by the observer/propagator

         Channel_Set_Data(selected_channel, atoi(interactive_assembly_message_content));
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

static char * channel_state_format = "interactive_assembly update %d";
static char channel_state_message_buffer[50];
static uint32_t last_reported_value;

void Interactive_Assembly_Periodic_Call() {

   if (channel_active && (state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_MASTER || state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SLAVE)) {
      //read the value and send it to the remote
      int32_t channel_state = Channel_Get_Data((Channel_Number) selected_channel);

      if (last_reported_value != channel_state) {

         /////this is a place where we can poll the data and send it to the remote, if that isn't already handled by the observer/propagator

         sprintf(channel_state_message_buffer, channel_state_format, channel_state);
         Message * m = Create_Message(channel_state_message_buffer);
         Set_Message_Type(m, "udp");
         Set_Message_Destination(m, remote_module_address);
         Set_Message_Source(m, local_address);

         Wifi_Send(m);
         last_reported_value = channel_state;
      }
   }
}

////Local implementations /////////////////////////////////////////
static void Request_Remote_Channel() {

   Message * m = NULL;
   if (IS_INPUT(state)) {

      m = Create_Message("interactive_assembly request output");

   } else if (IS_OUTPUT(state)) {

      m = Create_Message("interactive_assembly request input");
   }

   if (m != NULL) {

      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);

      if (channel_active) {
         Set_Message_Destination(m, remote_module_address);
      } else {
         Set_Message_Destination(m, broadcast_address_module);
      }

      Wifi_Send(m);
   }
}

static void Cancel_Channel_Request() {

   Message * m = Create_Message("interactive_assembly request cancel");
   Set_Message_Type(m, "udp");
   Set_Message_Source(m, local_address);

   if (channel_active) {
      Set_Message_Destination(m, remote_module_address);
   } else {
      Set_Message_Destination(m, broadcast_address_module);
   }

   Wifi_Send(m);
}

static void Accept_Channel_Request() {

   Message * m;

   if (IS_INPUT(state)) {
      m = Create_Message("interactive_assembly accept input");
   } else if (IS_OUTPUT(state)) {
      m = Create_Message("interactive_assembly accept output");
   }

   if (m != NULL) {
      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, remote_module_address);

      Wifi_Send(m);
   }
}

static void Interactive_Assembly_Apply_State(Interactive_Assembly_Channel_State new_state, bool local_initiated) {

   if (new_state == INTERACTIVE_ASSEMBLY_NONE) {
      Request_Reset_Button();
   } else if (IS_PENDING(new_state)) {
      //should never happen
   } else {

      if (IS_INPUT(new_state)) {
         if (!IS_INPUT(state)) {
            ////Update channel direction here///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            updated_channel_profile[selected_channel].direction = CHANNEL_DIRECTION_INPUT;
         }

         // Reset the state of all lights
         for (int i = 0; i < 12; i++) {
            proposed_light_profiles[i].enabled = TRUE;
            Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
         }

         Set_Light_Color(&proposed_light_profiles[selected_channel], 50, 160, 200);

         state = new_state;

      } else if (IS_OUTPUT(new_state)) {
         if (!IS_OUTPUT(state)) {
            ////Update channel direction here///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            updated_channel_profile[selected_channel].direction = CHANNEL_DIRECTION_OUTPUT;
         }

         // Reset the state of all lights
         for (int i = 0; i < 12; i++) {
            proposed_light_profiles[i].enabled = TRUE;
            Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
         }

         Set_Light_Color(&proposed_light_profiles[selected_channel], 250, 90, 20);

         state = new_state;

      }

      //send acknowledge.
      if (local_initiated && !channel_active && IS_SLAVE(state)) {
         //accepted a pending channel response.
         Accept_Channel_Request();
         button_mode_timeout = 0;
         channel_active = TRUE;
      } else if (local_initiated) {
         //requested a change in the channel or a new channel to be created
         Request_Remote_Channel();
      } else {
         //received a request to change the channel
         Accept_Channel_Request();
      }
   }

   // Apply the new light states
   Apply_Channels();
   Apply_Channel_Lights();
}
