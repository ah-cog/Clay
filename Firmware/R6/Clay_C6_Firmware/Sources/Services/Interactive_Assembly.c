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
#define BLINK_KEYWORD "blink"

#define CHANNEL_BLINK_TIMEOUT_ms        3000           //the time between blinks.
#define CHANNEL_BLINK_TIME_ms           250            //the time the channel light is off for.
#define CHANNEL_CONNECTION_TIMEOUT      CHANNEL_BLINK_TIMEOUT_ms * 10
#define OUTPUT_BLINK_COUNT              2

#define ADDRESS_STR_LENGTH 50
#define WIFI_STATE_STEPS   5

#define IS_INPUT(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE || x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_DESTINATION)
#define IS_OUTPUT(x)    (x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SOURCE || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_DESTINATION)
#define IS_SOURCE(x)    (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SOURCE)
#define IS_SLAVE(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_DESTINATION || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_DESTINATION)
#define IS_PENDING(x)     (x == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING || x == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING)

////Typedefs  /////////////////////////////////////////////////////
typedef struct
{
   bool channel_active;
   Interactive_Assembly_Channel_State state;

   bool blinked;

   uint32_t blink_count;
   uint32_t blink_time;
   uint32_t last_message_time;
   int8_t local_channel;

   int8_t remote_channel;
   char remote_module_address[ADDRESS_STR_LENGTH];
} Interactive_Assembly_Channel;

////Globals   /////////////////////////////////////////////////////
int8_t interactive_assembly_using_lights;

////Local vars/////////////////////////////////////////////////////
RGB_Color channel_colors[CHANNEL_COUNT] = { { 45, 0, 0 },
                                            { 0, 45, 0 },
                                            { 0, 0, 45 },
                                            { 22, 22, 0 },
                                            { 0, 22, 22 },
                                            { 22, 0, 22 },
                                            { 0, 45, 10 },
                                            { 10, 0, 45 },
                                            { 45, 10, 0 },
                                            { 10, 45, 0 },
                                            { 0, 10, 45 },
                                            { 45, 0, 10 } };

static Interactive_Assembly_Channel_State requested_state;
static char requesting_module_address[ADDRESS_STR_LENGTH];
static int8_t requesting_module_channel;
static int32_t request_time_ms;

static int8_t button_mode;
static uint32_t button_mode_start_time;

static int8_t selected_channel = -1;
static int8_t changed_channel_mode = FALSE;

static char interactive_assembly_message_type[20];
static char interactive_assembly_message_content[20];
static char interactive_assembly_message_source[20];
static char interactive_assembly_message_destination[20];

static const char * channel_state_format = "interactive_assembly %d %d update %d";
static char channel_state_message_buffer[50];

static const char * channel_request_format = "interactive_assembly %d %d request %s";
static char channel_request_message_buffer[50];

static const char * channel_accept_format = "interactive_assembly %d %d accept %s";
static char channel_accept_message_buffer[50];

static const char * channel_cancel_format = "interactive_assembly %d %d request cancel";
static char channel_cancel_message_buffer[50];

static const char * channel_blink_format = "interactive_assembly %d %d request blink";
static char channel_blink_message_buffer[50];

static uint32_t last_reported_value;
static int8_t active_channel_count;

static Interactive_Assembly_Channel channels[CHANNEL_COUNT] = { 0 };

////Local Prototypes///////////////////////////////////////////////
static void Request_Remote_Channel(int8_t channel);
static void Cancel_Channel_Request(int8_t channel);
static void Cancel_Channel_Request_Specific(int8_t local_channel, int8_t remote_channel, char * remote_address);
static void Accept_Channel_Request(int8_t channel);
static void Accept_Channel_Request_Specific(int8_t channel, char * accept_content);
static void Request_Remote_Blink(int8_t channel);
static void Interactive_Assembly_Apply_State(Interactive_Assembly_Channel_State new_state, bool local_initiated, int8_t channel);
static void Interactive_Assembly_Update_Leds();
static Interactive_Assembly_Channel * Get_Channel_By_Local(int8_t local_channel);
static Interactive_Assembly_Channel * Get_Channel_By_Remote(int8_t local_channel);
static void Request_Reset_Channel(int8_t channel);
static void Cancel_Pending_Request();
static void Set_Channel_Blinked(int8_t channel);

////Global implementations ////////////////////////////////////////

int8_t Enable_Interactive_Assembly() {

   Button_Register_Release_Response(&Request_Change_Selected_Channel);
   Button_Register_Hold_Response(DEFAULT_BUTTON_HOLD_TIME, &Request_Change_Selected_Channel_Mode);

   interactive_assembly_using_lights = FALSE;
   button_mode = FALSE;
   button_mode_start_time = 0;
   active_channel_count = 0;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      channels[i].channel_active = FALSE;
      channels[i].state = INTERACTIVE_ASSEMBLY_NONE;
      channels[i].remote_channel = -1;
      channels[i].blinked = FALSE;
      channels[i].blink_time = 0;

      memset(channels[i].remote_module_address, 0, ADDRESS_STR_LENGTH);
   }

   return TRUE;
}

void Request_Reset_Button() {

   if (!channels[selected_channel].channel_active) {
      Request_Reset_Channel(selected_channel);
   }

   // Reset button logic state
   button_mode = 0;
   button_mode_start_time = 0;
   selected_channel--;     //Don't reset to -1. Michael likes the selected channel to be remembered. Allows picking up where left off.

   changed_channel_mode = FALSE;
}

void Request_Change_Selected_Channel() {

   if (changed_channel_mode == TRUE) {
      changed_channel_mode = FALSE;
   } else {
      Change_Selected_Channel();
   }
}

void Change_Selected_Channel() {

   if (!channels[selected_channel > 0 ? selected_channel : 0].channel_active) {
      channels[selected_channel > 0 ? selected_channel : 0].state = INTERACTIVE_ASSEMBLY_NONE;
      Interactive_Assembly_Update_Leds();
   }

   selected_channel = (selected_channel + 1) % 12;

   while (channels[selected_channel].channel_active) {
      selected_channel = (selected_channel + 1) % 12;
   }

   Interactive_Assembly_Channel_State new_state = channels[selected_channel].state;

   button_mode_start_time = Millis();

   if (!channels[selected_channel].channel_active) {

      if (IS_PENDING(requested_state)) {
         channels[selected_channel].channel_active = TRUE;
         channels[selected_channel].local_channel = selected_channel;

         new_state = requested_state - 1;
         //copy request vars into channel
         channels[selected_channel].remote_channel = requesting_module_channel;
         sprintf(channels[selected_channel].remote_module_address, requesting_module_address);

         Cancel_Pending_Request();
      } else {
         new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE;
      }

      //apply the state.
      Interactive_Assembly_Apply_State(new_state, TRUE, selected_channel);
   }
}

void Request_Change_Selected_Channel_Mode() {

   //we don't currently support changing the channel direction once the channel has been established.
   if (channels[selected_channel > 0 ? selected_channel : 0].channel_active) {
      //TODO: better feedback?
      changed_channel_mode = TRUE;     //set this so we don't increment selected_channel.
      return;
   }

   Interactive_Assembly_Channel_State new_state = channels[selected_channel > 0 ? selected_channel : 0].state;

   if (changed_channel_mode == FALSE) {
      if (IS_PENDING(requested_state)) {

         if (!channels[selected_channel].channel_active) {
            channels[selected_channel].channel_active = TRUE;
            channels[selected_channel].local_channel = selected_channel;

            //copy request vars into channel
            channels[selected_channel].state = requested_state - 1;     //pending state is always defined as the destination state + 1
            channels[selected_channel].remote_channel = requesting_module_channel;
            sprintf(channels[selected_channel].remote_module_address, requesting_module_address);

            Cancel_Pending_Request();
         }
      } else {
         if (channels[selected_channel].state == INTERACTIVE_ASSEMBLY_NONE
             || channels[selected_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SOURCE) {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE;
         } else if (channels[selected_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE) {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SOURCE;
         } else if (channels[selected_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_DESTINATION) {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_DESTINATION;
         } else if (channels[selected_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_DESTINATION) {
            new_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_DESTINATION;
         }
      }

      changed_channel_mode = TRUE;

      Interactive_Assembly_Apply_State(new_state, TRUE, selected_channel);
   }
}

char token[MAXIMUM_MESSAGE_LENGTH] = { 0 };

int8_t Process_Interactive_Assembly_Message(Message * message) {

   //examples:
   //interactive_assembly <source> <dest> <message type> <message content>
   //interactive_assembly 1 1 request output
   //interactive_assembly 2 1 request input
   //interactive_assembly 3 7 cancel request
   //interactive_assembly 4 12 accept input

   int8_t status = FALSE;
   int8_t result = FALSE;

   int token_count = 0;

   char *message_content = (*message).content;
   memset(token, 0, MAXIMUM_MESSAGE_LENGTH);

   int8_t local_channel;
   int8_t remote_channel;
   Interactive_Assembly_Channel * local_channel_info = NULL;

   // Extract parameters
   result = Get_Token(message_content, interactive_assembly_message_source, 1);
   result &= Get_Token(message_content, interactive_assembly_message_destination, 2);
   result &= Get_Token(message_content, interactive_assembly_message_type, 3);
   result &= Get_Token(message_content, interactive_assembly_message_content, 4);

   local_channel = atoi(interactive_assembly_message_destination);
   remote_channel = atoi(interactive_assembly_message_source);

   if (result) {

      //this way we have a sure reference to the channel we have a message for, if it's initialized.
      if (remote_channel >= 0) {
         local_channel_info = Get_Channel_By_Remote(remote_channel);

         //and we make sure we have the right local channel if we're connected to a channel but it doesn't know who we are yet (pretty much always a cancel.)
         if (local_channel_info != NULL && local_channel == -1) {
            local_channel = (*local_channel_info).local_channel;
         }
      }

      if (strncmp(interactive_assembly_message_type, REQUEST_KEYWORD, strlen(REQUEST_KEYWORD)) == 0) {

         if (strncmp(interactive_assembly_message_content, INPUT_KEYWORD, strlen(INPUT_KEYWORD)) == 0) {
            //received request to set up channel as input
            requested_state = INTERACTIVE_ASSEMBLY_LOCAL_INPUT_PENDING;
            requesting_module_channel = remote_channel;
            request_time_ms = Millis();
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            //received request to set up channel as output
            requested_state = INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_PENDING;
            requesting_module_channel = remote_channel;
            request_time_ms = Millis();
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, CANCEL_KEYWORD, strlen(CANCEL_KEYWORD)) == 0) {

            //this means we got a cancel from a remote channel we're connected to.
            if (local_channel_info != NULL) {
               Request_Reset_Channel(local_channel);
            }

            //HACK: strncmp on length - 1 because the last digit of the port doesn't match.
            if (remote_channel == requesting_module_channel
                && strncmp(requesting_module_address, (*message).source, strlen(requesting_module_address) - 1) == 0) {
               Cancel_Pending_Request();
            }

            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, BLINK_KEYWORD, strlen(BLINK_KEYWORD)) == 0) {
            Set_Channel_Blinked(local_channel);
            channels[local_channel].blink_count = OUTPUT_BLINK_COUNT - 1;     //already blinked once.
            channels[local_channel].last_message_time = Millis();
            Accept_Channel_Request_Specific(local_channel, BLINK_KEYWORD);
         }
      } else if (strncmp(interactive_assembly_message_type, ACCEPT_KEYWORD, strlen(ACCEPT_KEYWORD)) == 0) {
         if (strncmp(interactive_assembly_message_content, INPUT_KEYWORD, strlen(INPUT_KEYWORD)) == 0) {
            if (channels[local_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_OUTPUT_SOURCE
                && !channels[local_channel].channel_active) {
               //remote has the right config
               button_mode_start_time = 0;
               channels[local_channel].channel_active = TRUE;
               channels[local_channel].remote_channel = remote_channel;
               sprintf(channels[local_channel].remote_module_address, (*message).source);
               *(channels[local_channel].remote_module_address + strlen(channels[local_channel].remote_module_address) - 1) = '6';     //HACK: we need the port to be 4446
               channels[local_channel].last_message_time = Millis();
               Interactive_Assembly_Update_Leds();
            } else {
               if (!channels[local_channel].channel_active) {
                  //remote has wrong config. tell it to cancel
                  channels[local_channel].remote_channel = remote_channel;
                  sprintf(channels[local_channel].remote_module_address, (*message).source);
                  *(channels[local_channel].remote_module_address + strlen(channels[local_channel].remote_module_address) - 1) = '6';     //HACK: we need the port to be 4446
                  Request_Reset_Channel(local_channel);
               } else {
                  //received a second accept message. send a cancel back to the originator.
                  Cancel_Channel_Request_Specific(local_channel, remote_channel, (*message).source);
               }
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, OUTPUT_KEYWORD, strlen(OUTPUT_KEYWORD)) == 0) {
            if (channels[local_channel].state == INTERACTIVE_ASSEMBLY_LOCAL_INPUT_SOURCE
                && !channels[local_channel].channel_active) {
               //remote has the right config
               button_mode_start_time = 0;
               channels[local_channel].channel_active = TRUE;
               channels[local_channel].remote_channel = remote_channel;
               sprintf(channels[local_channel].remote_module_address, (*message).source);
               *(channels[local_channel].remote_module_address + strlen(channels[local_channel].remote_module_address) - 1) = '6';     //HACK: we need the port to be 4446
               channels[local_channel].last_message_time = Millis();
               Interactive_Assembly_Update_Leds();
            } else {
               if (!channels[local_channel].channel_active) {
                  //remote has wrong config. tell it to cancel
                  channels[local_channel].remote_channel = remote_channel;
                  sprintf(channels[local_channel].remote_module_address, (*message).source);
                  *(channels[local_channel].remote_module_address + strlen(channels[local_channel].remote_module_address) - 1) = '6';     //HACK: we need the port to be 4446
                  Request_Reset_Channel(local_channel);
               } else {
                  //received a second accept message. send a cancel back to the originator.
                  Cancel_Channel_Request_Specific(local_channel, remote_channel, (*message).source);
               }
            }
            result = TRUE;
         } else if (strncmp(interactive_assembly_message_content, BLINK_KEYWORD, strlen(BLINK_KEYWORD)) == 0) {
            channels[local_channel].last_message_time = Millis();
         }
      } else if (strncmp(interactive_assembly_message_type, UPDATE_KEYWORD, strlen(UPDATE_KEYWORD)) == 0) {
         //received state from remote. update the output.
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //you can probably ignore or even remove this code. it was for the hacky way i tried to transmit data before. /////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      }
   }

   if (result && IS_PENDING(requested_state)) {

      sprintf(requesting_module_address, (*message).source);
      *(requesting_module_address + strlen(requesting_module_address) - 1) = '6';     //HACK: we need the port to be 4446

      //we can look up the remote address in the UDP discovery table if we want to know its uuid.
   }

   return result;
}

void Interactive_Assembly_Periodic_Call() {

   if (IS_PENDING(requested_state) && (Millis() - request_time_ms) >= DEFAULT_BUTTON_MODE_TIMEOUT) {
      Cancel_Pending_Request();
   }

   if ((button_mode_start_time != 0) && ((Millis() - button_mode_start_time) > DEFAULT_BUTTON_MODE_TIMEOUT)) {
      // Check if the button mode timer expired
      Request_Reset_Button();
      button_mode_start_time = 0;
   }

   active_channel_count = 0;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      if (channels[i].channel_active) {

         ++active_channel_count;

         if (channels[i].blinked && ((Millis() - channels[i].blink_time) > CHANNEL_BLINK_TIME_ms)) {
            channels[i].blinked = FALSE;
            Interactive_Assembly_Update_Leds();

            if (IS_INPUT(channels[i].state)) {
               Request_Remote_Blink(i);
            }

         } else if (IS_INPUT(channels[i].state) && ((Millis() - channels[i].blink_time) > (CHANNEL_BLINK_TIMEOUT_ms))) {
            Set_Channel_Blinked(i);
         } else if (IS_OUTPUT(channels[i].state)
                    && ((Millis() - channels[i].blink_time) > (2 * CHANNEL_BLINK_TIME_ms))
                    && channels[i].blink_count > 0) {
            Set_Channel_Blinked(i);
            --channels[i].blink_count;
         } else if ((Millis() - channels[i].last_message_time) >= CHANNEL_CONNECTION_TIMEOUT) {
            Request_Reset_Channel(i);
         }
      }
   }
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //if you need a periodic place to read data or do anything periodic related to interactive assembly (animations,callbacks, other state vars, etc),/
   //    then use this function. /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

////Local implementations /////////////////////////////////////////
static void Request_Remote_Channel(int8_t channel) {

   Message * m = NULL;

   if (IS_INPUT(channels[channel].state)) {

      sprintf(channel_request_message_buffer, channel_request_format, channel, channels[channel].remote_channel,
      OUTPUT_KEYWORD);
      m = Create_Message();
      Set_Message_Content(m, channel_request_message_buffer, strlen(channel_request_message_buffer));
      Set_Message_Content_Type(m, "text");
   } else if (IS_OUTPUT(channels[channel].state)) {

      sprintf(channel_request_message_buffer, channel_request_format, channel, channels[channel].remote_channel,
      INPUT_KEYWORD);
      m = Create_Message();
      Set_Message_Content(m, channel_request_message_buffer, strlen(channel_request_message_buffer));
      Set_Message_Content_Type(m, "text");
   }

   if (m != NULL) {

      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);

      if (channels[channel].channel_active) {
         Set_Message_Destination(m, channels[channel].remote_module_address);
      } else {
         Set_Message_Destination(m, broadcast_address_module);
      }

      Wifi_Send(m);
      //HACK: tryna make sure we get our message out asap
      for (int i = 0; i < WIFI_STATE_STEPS; ++i) {
         Wifi_State_Step();
      }
   }
}

static void Cancel_Channel_Request(int8_t channel) {
   Cancel_Channel_Request_Specific(channel, channels[channel].remote_channel,

   broadcast_address_module);
}

static void Cancel_Channel_Request_Specific(int8_t local_channel, int8_t remote_channel, char * remote_address) {

   sprintf(channel_cancel_message_buffer, channel_cancel_format, local_channel, remote_channel);

   Message * m = Create_Message();
   if (m != NULL) {
      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, remote_address);
      Set_Message_Content(m, channel_cancel_message_buffer, strlen(channel_cancel_message_buffer));
      Set_Message_Content_Type(m, "text");
      Wifi_Send(m);
      //HACK: tryna make sure we get our message out asap
      for (int i = 0; i < WIFI_STATE_STEPS; ++i) {
         Wifi_State_Step();
      }
   }
}

static void Accept_Channel_Request(int8_t channel) {

   if (IS_INPUT(channels[channel].state)) {
      Accept_Channel_Request_Specific(channel, INPUT_KEYWORD);
   } else if (IS_OUTPUT(channels[channel].state)) {
      Accept_Channel_Request_Specific(channel, OUTPUT_KEYWORD);
   }
}

static void Accept_Channel_Request_Specific(int8_t channel, char * accept_content) {

   Message * m;

   sprintf(channel_accept_message_buffer, channel_accept_format, channel, channels[channel].remote_channel, accept_content);
   m = Create_Message();

   if (m != NULL) {
      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, channels[channel].remote_module_address);
      Set_Message_Content(m, channel_accept_message_buffer, strlen(channel_accept_message_buffer));
      Set_Message_Content_Type(m, "text");

      Wifi_Send(m);
      //HACK: tryna make sure we get our message out asap
      for (int i = 0; i < WIFI_STATE_STEPS; ++i) {
         Wifi_State_Step();
      }
   }
}

static void Request_Remote_Blink(int8_t channel) {

   Message * m;

   sprintf(channel_blink_message_buffer, channel_blink_format, channel, channels[channel].remote_channel);
   m = Create_Message();

   if (m != NULL) {
      Set_Message_Type(m, "udp");
      Set_Message_Source(m, local_address);
      Set_Message_Destination(m, channels[channel].remote_module_address);
      Set_Message_Content(m, channel_blink_message_buffer, strlen(channel_blink_message_buffer));
      Set_Message_Content_Type(m, "text");

      Wifi_Send(m);
      //HACK: tryna make sure we get our message out asap
      for (int i = 0; i < WIFI_STATE_STEPS; ++i) {
         Wifi_State_Step();
      }
   }
}

static void Interactive_Assembly_Apply_State(Interactive_Assembly_Channel_State new_state,
bool local_initiated,
                                             int8_t channel) {

   if (new_state == INTERACTIVE_ASSEMBLY_NONE) {
      Request_Reset_Channel(channel);
   } else if (IS_PENDING(new_state)) {
      //should never happen
   } else {

      if (IS_INPUT(new_state)) {
         if (!IS_INPUT(channels[channel].state)) {

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //set up channel as input here. ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////channels[channel].remote_channel - contains the remote channel to be config'd as input//////////////////////////////////////////////////
            ///////////channels[channel].local_channel - contains the local channel to be config'd as output///////////////////////////////////////////////////
            ///////////channels[channel].remote_module_address - contains address string of the remote module with the UDP rx port appended////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            updated_channel_profile[channel].direction = CHANNEL_DIRECTION_INPUT;
         }

         channels[channel].state = new_state;

      } else if (IS_OUTPUT(new_state)) {
         if (!IS_OUTPUT(channels[channel].state)) {

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //set up channel as output here. //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////channels[channel].remote_channel - contains the remote channel to be config'd as input//////////////////////////////////////////////////
            ///////////channels[channel].local_channel - contains the local channel to be config'd as output///////////////////////////////////////////////////
            ///////////channels[channel].remote_module_address - contains address string of the remote module with the UDP rx port appended////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            updated_channel_profile[selected_channel].direction = CHANNEL_DIRECTION_OUTPUT;
         }

         channels[channel].state = new_state;
      }

      Interactive_Assembly_Update_Leds();

      //send acknowledge.
      if (local_initiated && channels[channel].channel_active && IS_SLAVE(channels[channel].state)) {
         //accepted a pending channel response.
         Accept_Channel_Request(channel);
         channels[channel].last_message_time = Millis();
         button_mode_start_time = 0;
      } else if (local_initiated) {
         //requested a change in the channel or a new channel to be created
         Request_Remote_Channel(channel);
      } else {
         //received a request to change the channel
         Accept_Channel_Request(channel);
         channels[channel].last_message_time = Millis();
      }
   }
}

static void Interactive_Assembly_Update_Leds() {

   interactive_assembly_using_lights = FALSE;

// Reset the state of all lights
   for (int i = 0; i < 12; i++) {
      proposed_light_profiles[i].enabled = TRUE;

      if (channels[i].state == INTERACTIVE_ASSEMBLY_NONE) {
         Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
      } else if (IS_INPUT(channels[i].state)) {
         interactive_assembly_using_lights = TRUE;

         if (channels[i].channel_active) {
            if (channels[i].blinked) {
               Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
            } else if (IS_SOURCE(channels[i].state)) {
               Set_Light_Color(&proposed_light_profiles[i], channel_colors[i].R, channel_colors[i].G, channel_colors[i].B);
            } else {
               Set_Light_Color(&proposed_light_profiles[i],
                               channel_colors[channels[i].remote_channel].R,
                               channel_colors[channels[i].remote_channel].G,
                               channel_colors[channels[i].remote_channel].B);
            }
         } else {
            Set_Light_Color(&proposed_light_profiles[i], 100, 160, 250);
         }

      } else if (IS_OUTPUT(channels[i].state)) {
         interactive_assembly_using_lights = TRUE;

         if (channels[i].channel_active) {

            if (channels[i].blinked) {
               Set_Light_Color(&proposed_light_profiles[i], 0, 0, 0);
            } else if (IS_SOURCE(channels[i].state)) {
               Set_Light_Color(&proposed_light_profiles[i], channel_colors[i].R, channel_colors[i].G, channel_colors[i].B);
            } else {
               Set_Light_Color(&proposed_light_profiles[i],
                               channel_colors[channels[i].remote_channel].R,
                               channel_colors[channels[i].remote_channel].G,
                               channel_colors[channels[i].remote_channel].B);
            }
         } else {
            Set_Light_Color(&proposed_light_profiles[i], 250, 160, 100);
         }
      }
   }

// Apply the new light states
   Apply_Channels();
   Apply_Channel_Lights();
}

static Interactive_Assembly_Channel * Get_Channel_By_Local(int8_t local_channel) {

   Interactive_Assembly_Channel * result = NULL;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      if (channels[i].channel_active && channels[i].local_channel == local_channel) {
         result = channels + i;
         break;
      }
   }

   return result;
}

static Interactive_Assembly_Channel * Get_Channel_By_Remote(int8_t local_channel) {

   Interactive_Assembly_Channel * result = NULL;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      if (channels[i].channel_active && channels[i].remote_channel == local_channel) {
         result = channels + i;
         break;
      }
   }

   return result;
}

static void Request_Reset_Channel(int8_t channel) {

   channels[channel].channel_active = FALSE;
   channels[channel].state = INTERACTIVE_ASSEMBLY_NONE;
   Cancel_Channel_Request(channel);
   Interactive_Assembly_Update_Leds();
}

static void Cancel_Pending_Request() {
   memset(requesting_module_address, 0, ADDRESS_STR_LENGTH);
   requested_state = INTERACTIVE_ASSEMBLY_NONE;
   requesting_module_channel = -1;
}

static void Set_Channel_Blinked(int8_t channel) {
   channels[channel].blink_time = Millis();
   channels[channel].blinked = TRUE;

   Interactive_Assembly_Update_Leds();
}
