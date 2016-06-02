////Includes //////////////////////////////////////////////////////
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

#include "Application.h"
#include "GPIO.h"
#include "Message.h"
#include "Message_Queue.h"

#include "PWM_Utils.h"

#include "GPIO_PTB.h"
#include "GPIO_PTC.h"
//#include "GPIO_PTD.h"
#include "GPIO_PTE.h"

#include "ADC1.h"
#include "PWM_OUT_1.h"

#include "UDP_Discovery_temp.h"

//TODO: lose ADC calibration
//      get channel hardware put into this code
//      document channel hardware on notion

////Macros ////////////////////////////////////////////////////////

//these are here to preserve the indexing when ptb4 and 6 are assigned to PWM and ADC
#ifndef GPIO_PTB_IO_4_MASK
#define GPIO_PTB_IO_4_MASK 0
#endif

#ifndef GPIO_PTB_IO_6_MASK
#define GPIO_PTB_IO_6_MASK 0
#endif

#ifndef GPIO_PTD_IO_12_MASK
#define GPIO_PTD_IO_12_MASK 0
#endif

#ifndef GPIO_PTE_IO_2_MASK
#define GPIO_PTE_IO_2_MASK 0
#endif

#ifndef GPIO_PTE_IO_3_MASK
#define GPIO_PTE_IO_3_MASK 0
#endif

////Typedefs  /////////////////////////////////////////////////////

////Globals   /////////////////////////////////////////////////////
Channel_Profile updated_channel_profile[CHANNEL_COUNT];
Channel_Profile channel_profile[CHANNEL_COUNT];

Observable_Device platform_observable_profiles[CHANNEL_COUNT];

////Local vars/////////////////////////////////////////////////////

static LDD_TDeviceData * PTB_data = NULL;
static LDD_TDeviceData * PTC_data = NULL;
static LDD_TDeviceData * PTD_data = NULL;
static LDD_TDeviceData * PTE_data = NULL;

static LDD_TDeviceData * ADC0_data = NULL;
static LDD_TDeviceData * ADC1_data = NULL;
static LDD_TDeviceData * PWM_OUT_1_data = NULL;
static LDD_TDeviceData * PWM_OUT_2_data = NULL;
static LDD_TDeviceData * PWM_OUT_3_data = NULL;
static LDD_TDeviceData * PWM_OUT_4_data = NULL;

////Local Prototypes///////////////////////////////////////////////
static bool Channel_Enable_Toggle(Channel_Number number);
static bool Channel_Enable_Waveform(Channel_Number number);
static bool Channel_Enable_Pulse(Channel_Number number);

static void Channel_Disable_Toggle(Channel_Number number);
static void Channel_Disable_Waveform(Channel_Number number);
static void Channel_Disable_Pulse(Channel_Number number);

static int32_t Channel_Read_Toggle(Channel_Number number);
static int32_t Channel_Read_Waveform(Channel_Number number);

static int32_t Channel_Write_Toggle(Channel_Number number, int32_t data);
static int32_t Channel_Write_Pulse(Channel_Number number, LDD_PPG_Tfloat period_s, uint16_t ratio);

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Waveform(Channel_Number number, Channel_Direction direction);
static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction);

static void Channel_Apply_Output(Channel_Number number);

static void Initialize_Hardware_Interface();
static void Initialize_Channel_Hardware_Interface(Channel_Number number);

Propagator* Create_Propagator(Observable *source, char *source_key, Observable *destination, char *destination_key) {

   // Create propagator
   Propagator *propagator = (Propagator *) malloc(sizeof(Propagator));

   // Source
   (*propagator).source = source;

   // Reserve memory for the source key and copy the key into it
//	(*propagator).source_key = (char *) malloc (strlen (source_key) + 1);
//	memset ((*propagator).source_key, '\0', strlen (source_key) + 1);
//	memcpy ((*propagator).source_key, source_key, strlen (source_key));

// Destination
   (*propagator).destination = destination;

   // Reserve memory for the destination key and copy the key into it
//	(*propagator).destination_key = (char *) malloc (strlen (destination_key) + 1);
//	memset ((*propagator).destination_key, '\0', strlen (destination_key) + 1);
//	memcpy ((*propagator).destination_key, destination_key, strlen (destination_key));

// List
   (*propagator).previous = NULL;
   (*propagator).next = NULL;

   return propagator;
}

void Delete_Propagator(Propagator *propagator) {
   if (propagator != NULL) {

      // Source Key
//		if ((*propagator).source_key != NULL) {
//			free ((*propagator).source_key);
//			(*propagator).source_key = NULL;
//		}

// Destination Key
//		if ((*propagator).destination_key != NULL) {
//			free ((*propagator).destination_key);
//			(*propagator).destination_key = NULL;
//		}

// Observable
      free(propagator);
      propagator = NULL;
   }
}

int16_t Add_Propagator(Observable *observable, Propagator *propagator) {

   Propagator *previous_propagator = NULL;     // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.

   // Create a action construct to denote to the action for the loop!
   // NOTE: This construct must be different than the construct for the action cache to preserve their unique link structures and prevent infinite looping during list traversal.
//	Event *event = Create_Event ((*action).uuid, action);

   // TODO: Consider checking of the action has a action construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Action () _before_ calling Add_Action.

   if ((*observable).propagators == NULL) {

      // The loop is empty, so add it to the loop as the only element.
      (*observable).propagators = propagator;

      (*propagator).previous = NULL;
      (*propagator).next = NULL;

   } else {

      // Search for the last element in the list
      previous_propagator = (*observable).propagators;     // Get the front of the queue.
      while ((*previous_propagator).next != NULL) {
         previous_propagator = (*previous_propagator).next;
      }

      // Update the list linkage to add the message to the back of the list
      (*propagator).previous = previous_propagator;
      (*previous_propagator).next = propagator;
   }
}

uint8_t Has_Propagators(Observable *observable) {
   return (*observable).propagators != NULL;
}

bool Has_Propagator(Observable *source, char *source_key, Observable *destination, char *destination_key) {

   bool result = FALSE;

   if (source != NULL) {

      Propagator *propagator = NULL;

      if ((*source).propagators != NULL) {
         propagator = (*source).propagators;     // Get the first propagator in the list.
         while (propagator != NULL && (*propagator).source != NULL && (*propagator).destination != NULL) {

            // TODO: Compare key of each propagator until the same one is found or it is not found at all
//				if ((strncmp ((*propagator).source_key, source_key, strlen (source_key)) == 0)
//						&& ((*propagator).destination == destination)
//						&& (strncmp ((*propagator).destination_key, destination_key, strlen (destination_key)) == 0)) {
            if ((*propagator).source == source && (*propagator).destination == destination) {
               result = TRUE;
               break;
            }

            propagator = (*propagator).next;
         }
      }
   }

   return result;
}

Propagator* Remove_Propagator(Observable *observable, Propagator *propagator) {

   if (propagator != NULL && observable != NULL) {

      // Update the linked list to remove the action from the front of the queue.
      if ((*propagator).previous == NULL && (*propagator).next != NULL) {

         // The action in the first in the loop.

         (*observable).propagators = (*propagator).next;     // Update the loop's first action to be the next one.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         (*((*observable).propagators)).next = NULL;     // Update the the new first action in the loop so it doesn't link to a "previous" action.

         // Unlink the action from linked list to finish dequeuing process.
         (*propagator).previous = NULL;
         (*propagator).next = NULL;

      } else if ((*propagator).previous != NULL && (*propagator).next != NULL) {

         // The action is within the loop. It has previous and next actions.

         (*(*propagator).previous).next = (*propagator).next;     // Update the previous action to skip this action and point to the next action.

         (*(*propagator).next).previous = (*propagator).previous;     // Update the next action skip this action and point to the previous action.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*propagator).previous = NULL;
         (*propagator).next = NULL;

      } else if ((*propagator).previous != NULL && (*propagator).next == NULL) {

         // The action is the last in the loop. It has previous actions only.

         (*(*propagator).previous).next = NULL;     // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*propagator).previous = NULL;
         (*propagator).next = NULL;

      } else {

         // There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

         observable = NULL;     // Remove the link to any actions at the front of the loop.

         // Unlink the actions from linked list to finish dequeuing process.
         (*propagator).previous = NULL;
         (*propagator).next = NULL;

      }

      // Free the action construct from memory.
      // TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!

      PE_DEBUGHALT();

      Delete_Observable(propagator);  //TODO: is this supposed to be Delete_Propagator?
   }

   return NULL;
}

// <Data Flow>
Observable* Create_Observable(const char *key, int8_t content_type, void *content) {

   Observable *observable = (Observable *) malloc(sizeof(Observable));

   // Default UUID is NULL. NULL UUID means the observable is for the device.
   (*observable).device_uuid = NULL;

   (*observable).provider_uuid = NULL;

   // Allocate memory for the key and copy the key into it
   (*observable).key = (char *) malloc(strlen(key) + 1);
   memset((*observable).key, '\0', strlen(key) + 1);
   memcpy((*observable).key, key, strlen(key));

   // Set the type
   (*observable).content_type = content_type;

   // Allocate memory for the data and copy the data into it
   if (content_type == CONTENT_TYPE_INT16) {
      (*observable).content = (int16_t *) malloc(sizeof(int16_t));
      int16_t typed_content = *((int16_t *) content);
      *((int16_t *) (*observable).content) = typed_content;
   } else if (content_type == CONTENT_TYPE_INT32) {
      (*observable).content = (int32_t *) malloc(sizeof(int32_t));
      int32_t typed_content = *((int32_t *) content);
      *((int32_t *) (*observable).content) = typed_content;
   } else if (content_type == CONTENT_TYPE_FLOAT) {
      (*observable).content = (float *) malloc(sizeof(float));
      float typed_content = *((float *) content);
      *((float *) (*observable).content) = typed_content;
   } else if (content_type == CONTENT_TYPE_DOUBLE) {
      (*observable).content = (double *) malloc(sizeof(double));
      double typed_content = *((double *) content);
      *((double *) (*observable).content) = typed_content;
   }

   // List
   (*observable).previous = NULL;
   (*observable).next = NULL;

   // Propagators
   (*observable).propagators = NULL;

   return observable;
}

void Delete_Observable(Observable *observable) {
   if (observable != NULL) {

      // Key
      if ((*observable).key != NULL) {
         free((*observable).key);
         (*observable).key = NULL;
      }

      // Data
      if ((*observable).content != NULL) {
         free((*observable).content);
         (*observable).content = NULL;
      }

      // Observable
      free(observable);
      observable = NULL;

      // TODO: Free list of observables
   }
}

void Set_Observable_Device_UUID(Observable *observable, char *device_uuid) {

   if (observable != NULL) {
      // Allocate memory for the device UUID identifying the device with the observable, then copy the UUID into it
      (*observable).device_uuid = (char *) malloc(strlen(device_uuid) + 1);
      memset((*observable).device_uuid, '\0', strlen(device_uuid) + 1);
      memcpy((*observable).device_uuid, device_uuid, strlen(device_uuid));
   }
}

void Set_Observable_Provider_UUID(Observable *observable, char *provider_uuid) {

   if (observable != NULL) {
      // Allocate memory for the device UUID identifying the device with the observable, then copy the UUID into it
      (*observable).provider_uuid = (char *) malloc(strlen(provider_uuid) + 1);
      memset((*observable).provider_uuid, '\0', strlen(provider_uuid) + 1);
      memcpy((*observable).provider_uuid, provider_uuid, strlen(provider_uuid));
   }
}

void Set_Observable_Content(Observable *observable, int8_t content_type, void *content) {

   // Update the content type.
   (*observable).content_type = content_type;

   // Allocate memory for the data and copy the data into it (type-casting appropriately)
   if ((*observable).content_type == CONTENT_TYPE_INT16) {
      *((int16_t *) (*observable).content) = *((int16_t *) content);
   } else if ((*observable).content_type == CONTENT_TYPE_INT32) {
      *((int32_t *) (*observable).content) = *((int32_t *) content);
   } else if ((*observable).content_type == CONTENT_TYPE_FLOAT) {
      *((float *) (*observable).content) = *((float *) content);
   } else if ((*observable).content_type == CONTENT_TYPE_DOUBLE) {
      *((double *) (*observable).content) = *((double *) content);
   }

   // TODO: Add check for triggers?

   // Propagate
   if (Has_Propagators(observable)) {
      Propagate(observable);
   }
}

// void Propagate (Channel_Profile *source_channel_profile, Channel_Profile *destination_channel_profile, char *observable_key) {
void Propagate(Observable *observable) {

   if (observable != NULL) {

      Propagator *propagator = NULL;

      if ((*observable).propagators != NULL) {
         propagator = (*observable).propagators;     // Get the first propagator in the list.
         while (propagator != NULL) {

            // <HACK>
//				int16_t scaled_content = (int16_t) Scale_Adc_Counts_To_Servo_Range((*((*propagator).source)).content);

//				int servo_max_voltage_before_end_stop = 56645;
            //int32_t voltage_mv = *((int32_t *) (*((*propagator).source)).content);
            int32_t voltage_mv = Get_Observable_Data_Int32((*propagator).source);

            //limiting to keep in range.
            if (voltage_mv > 56645) {
               voltage_mv = 56645;
            }

            int16_t scaled_content = (int16_t) (voltage_mv * 0.08844f + 57700);
            //                        ^ TODO: Always cast to the source data to the destination data type.
            // </HACK>

            char *this_device_uuid = Get_Unit_UUID();
            if ((*((*propagator).destination)).device_uuid == NULL
                || strncmp((*((*propagator).destination)).device_uuid, this_device_uuid, strlen(this_device_uuid)) == 0) {
               // The destination observable is on this device
               // Set the content (and continue propagation), casting to the destination observable's type.
               Set_Observable_Content((*propagator).destination, (*((*propagator).destination)).content_type, &scaled_content);
               //				Set_Observable_Content ((*propagator).destination, (*((*propagator).source)).content_type, (*((*propagator).source)).content);
            } else {
               // The destination observable is on another device, so look up that device's
               // address, if available, and if so, send message to that device with the
               // observable's data.

               // TODO: Check mesh address tables to see if the device is in the local mesh
               // TODO: (if the above fails) Look for the device in the LAN device table
               // TODO: (if the previous two fail) Send message to remote server that will deliver the message to the device (if connected)

               Observable *source_observable = (*propagator).source;
               Observable *destination_observable = (*propagator).destination;

               char destination_device_internet_address[32] = { 0 };
               // TODO: Get_Device_Address (char *destination_device_uuid)]
               remote_clay_module *destination_device = Get_Device_By_UUID((*destination_observable).device_uuid);

               // Create message containing the (scaled) content to propagate to an observable on the destination device
               // e.g., "set [device <uuid>] provider "00000000-0000-0000-0000-000000000004" observable "pulse_duty_cycle" content "scaled_output"
               char message_content[128] = { 0 };

               // <SERIALIZE OBSERVABLE CONTENT>
               // Get the observable data encoded as a string for sending in a message.
               char serialized_observable_content[32] = { 0 };
               if ((*source_observable).content_type == CONTENT_TYPE_INT16) {
                  // Serialize
                  int16_t observable_content = Get_Observable_Data_Int16(source_observable);
                  sprintf(serialized_observable_content, "%d", observable_content);
               } else if ((*source_observable).content_type == CONTENT_TYPE_INT32) {

                  int32_t observable_content = Get_Observable_Data_Int32(source_observable);

                  // <TRANSFORM DATA: /SCALE/MAP/ETC.>
                  // <HACK>
                  // Apply transformations
                  //limiting to keep in range.
                  if (observable_content > 56645) {
                     observable_content = 56645;
                  }
                  int16_t scaled_observable_content = (int16_t) (observable_content * 0.08844f + 57700);
                  //                        ^ TODO: Always cast to the source data to the destination data type.
                  // </HACK>
                  // </TRANSFORM DATA>

                  // Serialize
                  sprintf(serialized_observable_content, "%d", scaled_observable_content);
                  // sprintf (serialized_observable_content, "%d", observable_content);
               } else if ((*source_observable).content_type == CONTENT_TYPE_FLOAT) {
                  // Serialize
                  float observable_content = Get_Observable_Data_Float(source_observable);
                  // sprintf (serialized_observable_content, "%0.6f", (*observable).content);
                  sprintf(serialized_observable_content, "%f", observable_content);
               } else if ((*source_observable).content_type == CONTENT_TYPE_DOUBLE) {
                  // Serialize
                  double observable_content = Get_Observable_Data_Double(source_observable);
                  // sprintf (serialized_observable_content, "%0.6f", (*observable).content);
                  sprintf(serialized_observable_content, "%f", observable_content);
               }
               // </SERIALIZE OBSERVABLE CONTENT>

               // Create message content
               sprintf(message_content,
                       "set provider %s observable %s type %d content %s",
                       (*destination_observable).provider_uuid,
                       (*destination_observable).key,
                       (*source_observable).content_type,
                       serialized_observable_content);

               if (Get_Message_Count(&outgoingMessageQueue) < 5 && Get_Message_Count(&outgoingWiFiMessageQueue) < 5) {

                  // <CREATE MESSAGE>
                  // Create message to send
                  //Message *message = Create_Message("set provider <uuid> observable <key> content <content>"); // set observable <key> content <content>
                  Message *message = Create_Message();
                  Set_Message_Type(message, "udp");     // TODO: In order, try mesh, LAN, WAN
                  Set_Message_Content(message, message_content, strlen(message_content));
                  char this_device_internet_address[32] = { 0 };
                  sprintf(this_device_internet_address, "%s:4446", local_address);     // is this correct?
                  Set_Message_Source(message, this_device_internet_address);     // <HACK />

                  char destination_device_address[32] = { 0 };
                  strncpy(destination_device_address, (*destination_device).address, strlen((*destination_device).address));
                  char *port_index = strstr(destination_device_address, ":") + 1;
                  port_index[0] = '\0';
                  strcat(destination_device_address, "4446");
                  // Set_Message_Destination (message, "192.168.1.255:4446");
                  //sprintf (destination_device_internet_address, "%s:4446", (*destination_device).address);
                  Set_Message_Destination(message, destination_device_address);
                  // </CREATE MESSAGE>

                  // Queue the outgoing message
                  Queue_Message(&outgoingMessageQueue, message);
               }

               // TODO: Handle the message on the remote device with the following code...
               /*
                // Set the content (and continue propagation), casting to the destination observable's type.
                Set_Observable_Content ((*propagator).destination, (*((*propagator).destination)).content_type, &scaled_content);
                //				Set_Observable_Content ((*propagator).destination, (*((*propagator).source)).content_type, (*((*propagator).source)).content);
                */
            }

            propagator = (*propagator).next;
         }
      }
   }
}

int8_t Get_Observable_Type(Observable *observable) {
   return (*observable).content_type;
}

int16_t Get_Observable_Data_Int16(Observable *observable) {
   return *((int16_t *) (*observable).content);
}

int32_t Get_Observable_Data_Int32(Observable *observable) {
   return *((int32_t *) (*observable).content);
}

float Get_Observable_Data_Float(Observable *observable) {
   return *((float *) (*observable).content);
}

double Get_Observable_Data_Double(Observable *observable) {
   return *((double *) (*observable).content);
}

Observable_Set* Create_Observable_Set(char *provider_uuid) {
   Observable_Set *observable_set = (Observable_Set *) malloc(sizeof(Observable_Set));

   // UUID of Provider
   (*observable_set).provider_uuid = (char *) malloc(strlen(provider_uuid) + 1);
   memset((*observable_set).provider_uuid, '\0', strlen(provider_uuid) + 1);
   memcpy((*observable_set).provider_uuid, provider_uuid, strlen(provider_uuid));

   (*observable_set).first_observable = NULL;

   (*observable_set).next = NULL;
   (*observable_set).previous = NULL;

   return observable_set;
}

void Delete_Observable_Set(Observable_Set *observable_set) {

   // TODO: Free individual observables

   free(observable_set);
   observable_set = NULL;
}

int16_t Add_Observable(Observable_Set *observable_set, Observable *observable) {
   Observable *previous_observable = NULL;     // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.
   uint16_t observable_count = 0;

   // Create a action construct to denote to the action for the loop!
   // NOTE: This construct must be different than the construct for the action cache to preserve their unique link structures and prevent infinite looping during list traversal.
//	Event *event = Create_Event ((*action).uuid, action);

   // TODO: Consider checking of the action has a action construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Action () _before_ calling Add_Action.

   if ((*observable_set).first_observable == NULL) {

      // The loop is empty, so add it to the loop as the only element.
      (*observable_set).first_observable = observable;

      (*observable).previous = NULL;
      (*observable).next = NULL;

   } else {

      // Search for the last element in the list
      previous_observable = (*observable_set).first_observable;     // Get the front of the queue.
      while ((*previous_observable).next != NULL) {
         previous_observable = (*previous_observable).next;
      }

      // Update the list linkage to add the message to the back of the list
      (*observable).previous = previous_observable;
      (*previous_observable).next = observable;
   }
}

Observable* Remove_Observable(Observable_Set *observable_set, Observable *observable) {

   if (observable != NULL && observable_set != NULL) {

      // Update the linked list to remove the action from the front of the queue.
      if ((*observable).previous == NULL && (*observable).next != NULL) {

         // The action in the first in the loop.

         (*observable_set).first_observable = (*observable).next;     // Update the loop's first action to be the next one.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         (*((*observable_set).first_observable)).next = NULL;     // Update the the new first action in the loop so it doesn't link to a "previous" action.

         // Unlink the action from linked list to finish dequeuing process.
         (*observable).previous = NULL;
         (*observable).next = NULL;

      } else if ((*observable).previous != NULL && (*observable).next != NULL) {

         // The action is within the loop. It has previous and next actions.

         (*(*observable).previous).next = (*observable).next;     // Update the previous action to skip this action and point to the next action.

         (*(*observable).next).previous = (*observable).previous;     // Update the next action skip this action and point to the previous action.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*observable).previous = NULL;
         (*observable).next = NULL;

      } else if ((*observable).previous != NULL && (*observable).next == NULL) {

         // The action is the last in the loop. It has previous actions only.

         (*(*observable).previous).next = NULL;     // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*observable).previous = NULL;
         (*observable).next = NULL;

      } else {

         // There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

         observable_set = NULL;     // Remove the link to any actions at the front of the loop.

         // Unlink the actions from linked list to finish dequeuing process.
         (*observable).previous = NULL;
         (*observable).next = NULL;

      }

      // Free the action construct from memory.
      // TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
      Delete_Observable(observable);
   }

   return NULL;
}

uint8_t Has_Observables(Observable_Set *observable_set) {
   return (*observable_set).first_observable != NULL;
}

Observable* Get_Observable(Observable_Set *observable_set, char *key) {
   Observable *observable = NULL;

   if ((*observable_set).first_observable != NULL) {
      observable = (*observable_set).first_observable;     // Get the first action construct in the cache list.
      while (observable != NULL) {
         if (strncmp(key, (*observable).key, strlen((*observable).key)) == 0) {
            return observable;     // Return the action associated with the specified action construct.
         }
         observable = (*observable).next;
      }
   }

   return NULL;
}

Observable* Get_Observable_By_Index(Observable_Set *observable_set, int index) {
   Observable *observable = NULL;
   int current_index = -1;

   if ((*observable_set).first_observable != NULL) {
      observable = (*observable_set).first_observable;     // Get the first action construct in the cache list.
      current_index = 0;
      while (observable != NULL) {
         if (current_index == index) {
            return observable;     // Return the action associated with the specified action construct.
         }
         observable = (*observable).next;
         current_index++;
      }
   }

   return NULL;
}

Observable_Interface* Create_Observable_Interface() {
   Observable_Interface *observable_interface = (Observable_Interface *) malloc(sizeof(Observable_Interface));

//	// Allocate memory for the device UUID identifying the device with the observable, then copy the UUID into it
//	(*observable_interface).uuid = (char *) malloc (strlen (uuid) + 1);
//	memset ((*observable_interface).uuid, '\0', strlen (uuid) + 1);
//	memcpy ((*observable_interface).uuid, uuid, strlen (uuid));

   // List of observable providers
   (*observable_interface).first_observable_provider = NULL;

   return observable_interface;
}

void Delete_Observable_Interface(Observable_Interface *observable_interface) {

   // TODO: Free observables in (*observable_interface).observable_set
   // TODO: Free (*observable_interface).observable_set

   free(observable_interface);
   observable_interface = NULL;
}

int16_t Add_Observable_Provider(Observable_Interface *observable_interface, Observable_Set *observable_provider) {
   Observable_Set *previous_observable_provider = NULL;     // The action construct presently at the end of the list. This will be set as the previous action construct to the one created for the newly-cached action.

   if ((*observable_interface).first_observable_provider == NULL) {

      // The list is empty, so add it to the list as the first and only element.
      (*observable_interface).first_observable_provider = observable_provider;

      (*observable_provider).previous = NULL;
      (*observable_provider).next = NULL;

   } else {

      // Search for the last element in the list
      previous_observable_provider = (*observable_interface).first_observable_provider;     // Get the front of the queue.
      while ((*previous_observable_provider).next != NULL) {
         previous_observable_provider = (*previous_observable_provider).next;
      }

      // Update the list linkage to add the message to the back of the list
      (*observable_provider).previous = previous_observable_provider;
      (*previous_observable_provider).next = observable_provider;
   }
}

Observable_Set* Remove_Observable_Provider(Observable_Interface *observable_interface, Observable_Set *observable_provider) {

   if (observable_provider != NULL && observable_interface != NULL) {

      // Update the linked list to remove the action from the front of the queue.
      if ((*observable_provider).previous == NULL && (*observable_provider).next != NULL) {

         // The action in the first in the loop.

         (*observable_interface).first_observable_provider = (*observable_provider).next;     // Update the loop's first action to be the next one.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         (*((*observable_interface).first_observable_provider)).next = NULL;     // Update the the new first action in the loop so it doesn't link to a "previous" action.

         // Unlink the action from linked list to finish dequeuing process.
         (*observable_provider).previous = NULL;
         (*observable_provider).next = NULL;

      } else if ((*observable_provider).previous != NULL && (*observable_provider).next != NULL) {

         // The action is within the loop. It has previous and next actions.

         (*(*observable_provider).previous).next = (*observable_provider).next;     // Update the previous action to skip this action and point to the next action.

         (*(*observable_provider).next).previous = (*observable_provider).previous;     // Update the next action skip this action and point to the previous action.

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*observable_provider).previous = NULL;
         (*observable_provider).next = NULL;

      } else if ((*observable_provider).previous != NULL && (*observable_provider).next == NULL) {

         // The action is the last in the loop. It has previous actions only.

         (*(*observable_provider).previous).next = NULL;     // Update the previous action be the new last action in the loop. That is, make it point to no other action (and point to NULL).

         // TODO: Check the state of the loop pointer, and update it if it points to the action being removed!

         // Unlink the action from linked list to finish dequeuing process.
         (*observable_provider).previous = NULL;
         (*observable_provider).next = NULL;

      } else {

         // There are no more actions in the loop, so remove all links and reset the loop to its "empty" state.

         observable_interface = NULL;     // Remove the link to any actions at the front of the loop.

         // Unlink the actions from linked list to finish dequeuing process.
         (*observable_provider).previous = NULL;
         (*observable_provider).next = NULL;

      }

      // Free the action construct from memory.
      // TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
      Delete_Observable_Set(observable_provider);
   }

   return NULL;
}

uint8_t Has_Observable_Providers(Observable_Interface *observable_interface) {
   return (*observable_interface).first_observable_provider != NULL;
}

Observable_Set* Get_Observable_Provider(Observable_Interface *observable_interface, char *provider_uuid) {
   Observable_Set *observable_provider = NULL;

   if ((*observable_interface).first_observable_provider != NULL) {
      observable_provider = (*observable_interface).first_observable_provider;     // Get the first action construct in the cache list.
      while (observable_provider != NULL) {
         if (strncmp(provider_uuid, (*observable_provider).provider_uuid, strlen((*observable_provider).provider_uuid)) == 0) {
            return observable_provider;     // Return the action associated with the specified action construct.
         }
         observable_provider = (*observable_provider).next;
      }
   }

   return NULL;
}

Observable_Set* Get_Observable_Provider_By_UUID(Observable_Interface *observable_interface, char *provider_uuid) {
   Observable_Set *observable_provider = NULL;

   if ((*observable_interface).first_observable_provider != NULL) {
      observable_provider = (*observable_interface).first_observable_provider;     // Get the first action construct in the cache list.
      while (observable_provider != NULL) {
         if (strncmp((*observable_provider).provider_uuid, provider_uuid, strlen(provider_uuid)) == 0) {
            return observable_provider;     // Return the action associated with the specified action construct.
         }
         observable_provider = (*observable_provider).next;
      }
   }

   return NULL;
}
// </Data Flow>

////Global implementations ////////////////////////////////////////
// Profile
int8_t Initialize_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {
      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number) i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      updated_channel_profile[i].data = &platform_observable_profiles[i];

//      updated_channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
//      updated_channel_profile[i].waveform_sample_value = -1;
//      updated_channel_profile[i].pulse_period_seconds = 0;
//      updated_channel_profile[i].pulse_duty_cycle = 0;

      // <OPTIMIZE>
      char *provider_uuid[12] = { "00000000-0000-0000-0000-000000000001",
                                  "00000000-0000-0000-0000-000000000002",
                                  "00000000-0000-0000-0000-000000000003",
                                  "00000000-0000-0000-0000-000000000004",
                                  "00000000-0000-0000-0000-000000000005",
                                  "00000000-0000-0000-0000-000000000006",
                                  "00000000-0000-0000-0000-000000000007",
                                  "00000000-0000-0000-0000-000000000008",
                                  "00000000-0000-0000-0000-000000000009",
                                  "00000000-0000-0000-0000-000000000010",
                                  "00000000-0000-0000-0000-000000000011",
                                  "00000000-0000-0000-0000-000000000012" };
      updated_channel_profile[i].observable_set = Create_Observable_Set(provider_uuid[i]);

      Observable *observable = NULL;
      Observable_Set *observable_set = updated_channel_profile[i].observable_set;
      int32 default_content_int32 = CHANNEL_VALUE_TOGGLE_ON;
      observable = Create_Observable("toggle_value", CONTENT_TYPE_INT32, &default_content_int32);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      default_content_int32 = -1;
      observable = Create_Observable("waveform_sample_value", CONTENT_TYPE_INT32, &default_content_int32);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      float default_content_float = 0;
      observable = Create_Observable("pulse_period_seconds", CONTENT_TYPE_FLOAT, &default_content_float);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      int16_t default_content_int16 = 0;
      observable = Create_Observable("pulse_duty_cycle", CONTENT_TYPE_INT16, &default_content_int16);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);
      // </OPTIMIZE>

      // Initialize channel profile
      channel_profile[i].number = (Channel_Number) i;
      channel_profile[i].enabled = FALSE;
      channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      channel_profile[i].type = CHANNEL_TYPE_TOGGLE;
      channel_profile[i].data = &platform_observable_profiles[i];

//      channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
//      channel_profile[i].waveform_sample_value = -1;
//      channel_profile[i].pulse_period_seconds = 0;
//      channel_profile[i].pulse_duty_cycle = 0;

      // <OPTIMIZE>
//		char *provider_uuid = Get_Unit_UUID();
      channel_profile[i].observable_set = Create_Observable_Set(provider_uuid[i]);

      observable_set = channel_profile[i].observable_set;
      default_content_int32 = CHANNEL_VALUE_TOGGLE_ON;
      observable = Create_Observable("toggle_value", CONTENT_TYPE_INT32, &default_content_int32);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      default_content_int32 = -1;
      observable = Create_Observable("waveform_sample_value", CONTENT_TYPE_INT32, &default_content_int32);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      default_content_float = 0;
      observable = Create_Observable("pulse_period_seconds", CONTENT_TYPE_FLOAT, &default_content_float);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      default_content_int16 = 0;
      observable = Create_Observable("pulse_duty_cycle", CONTENT_TYPE_INT16, &default_content_int16);
      Set_Observable_Provider_UUID(observable, provider_uuid[i]);
      Add_Observable(observable_set, observable);

      // Expose the observables for this provider
      Add_Observable_Provider(observable_interface, channel_profile[i].observable_set);
      // </OPTIMIZE>

   }

   Initialize_Hardware_Interface();

   return TRUE;
}

// Profile
int8_t Reset_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Initialize update channel profile
      updated_channel_profile[i].number = (Channel_Number) i;
      updated_channel_profile[i].enabled = FALSE;
      updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;

//      updated_channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
//      updated_channel_profile[i].waveform_sample_value = -1;
//      updated_channel_profile[i].pulse_period_seconds = 0;
//      updated_channel_profile[i].pulse_duty_cycle = 0;
   }

   return TRUE;
}

static void Hack_Propagate(Channel_Profile *source_channel_profile,
                           Channel_Profile *destination_channel_profile,
                           char *observable_key) {

   // Part 1:

   // Get observable set from source channel profile...
   // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
   Observable_Set *source_observable_set = (*source_channel_profile).observable_set;
   Observable *source_observable = NULL;

   // ...then get data from channel profile...
   source_observable = Get_Observable(source_observable_set, observable_key);
//	int16_t source_content = Get_Observable_Data_Int16 (source_observable);
//	int8_t source_content_type = (*source_observable).content_type;

//	source_observable = Get_Observable (observable_set, "pulse_period_seconds");
//	float pulse_period_seconds = Get_Observable_Data_Float (source_observable);

   // Part 2:

   // Get observable set for destination channel profile...
   Observable_Set *destination_observable_set = (*destination_channel_profile).observable_set;
   Observable *destination_observable = NULL;

   // ...then get data from channel profile...
   destination_observable = Get_Observable(destination_observable_set, observable_key);

   // ...then update the date.
   // int32_t data = Channel_Get_Data(updated_channel_profile[i].number);
   // <HACK> (Only works on non-strings since copies with assignment operator.)
   Set_Observable_Content(destination_observable, (*source_observable).content_type, (*source_observable).content);
   // </HACK>
}

// Profiles -> Hardware
// TODO: Apply only changes! Compare current state to previous state or to actual hardware state. The former might be faster, but it's less "ground truth."
int8_t Apply_Channels() {
   int i;

   for (i = 0; i < CHANNEL_COUNT; i++) {

      if (updated_channel_profile[i].enabled = TRUE) {

         // Check if the mode change. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].type != channel_profile[i].type) {

            // Update mode.
            channel_profile[i].type = updated_channel_profile[i].type;

            // Apply mode.
            Channel_Set_Type(channel_profile[i].number, channel_profile[i].type);
         }

         // Check if the direction changed. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].direction != channel_profile[i].direction) {

            // Update direction.
            channel_profile[i].direction = updated_channel_profile[i].direction;

            // Apply direction.
            Channel_Set_Direction(channel_profile[i].number, channel_profile[i].direction);
         }

         // Check if the enable state changed. Apply the corresponding transform.
         if (updated_channel_profile[i].enabled != channel_profile[i].enabled) {
            if (updated_channel_profile[i].enabled) {
               Channel_Enable(channel_profile[i].number);
            } else {
               Channel_Disable(channel_profile[i].number);
            }
         }

         // Check if the value change. Apply the corresponding transform if it changed.
         if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
//         if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT
//             && (channel_profile[i].toggle_value != updated_channel_profile[i].toggle_value
//                 || channel_profile[i].waveform_sample_value != updated_channel_profile[i].waveform_sample_value
//                 || channel_profile[i].pulse_period_seconds != updated_channel_profile[i].pulse_period_seconds
//                 || channel_profile[i].pulse_duty_cycle != updated_channel_profile[i].pulse_duty_cycle)) {

//            channel_profile[i].toggle_value = updated_channel_profile[i].toggle_value;
//            channel_profile[i].waveform_sample_value = updated_channel_profile[i].waveform_sample_value;
//            channel_profile[i].pulse_period_seconds = updated_channel_profile[i].pulse_period_seconds;
//            channel_profile[i].pulse_duty_cycle = updated_channel_profile[i].pulse_duty_cycle;

//        	 channel_profile[i].data->toggle_value = updated_channel_profile[i].data->toggle_value;
//        	 channel_profile[i].data->waveform_sample_value = updated_channel_profile[i].data->waveform_sample_value;
//        	 channel_profile[i].data->pulse_period_seconds = updated_channel_profile[i].data->pulse_period_seconds;
//        	 channel_profile[i].data->pulse_duty_cycle = updated_channel_profile[i].data->pulse_duty_cycle;

            /*
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "toggle_value");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "waveform_sample_value");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "pulse_period_seconds");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "pulse_duty_cycle");
             */

            // TODO: Propagate update_channel_profile state to channel_profile state
            // Apply value.
            Channel_Apply_Output((Channel_Number) i);

         } else if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
//            channel_profile[i].toggle_value = updated_channel_profile[i].toggle_value;
//            channel_profile[i].waveform_sample_value = updated_channel_profile[i].waveform_sample_value;
//            channel_profile[i].pulse_period_seconds = updated_channel_profile[i].pulse_period_seconds;
//            channel_profile[i].pulse_duty_cycle = updated_channel_profile[i].pulse_duty_cycle;

//        	 channel_profile[i].data->toggle_value = updated_channel_profile[i].data->toggle_value;
//        	 channel_profile[i].data->waveform_sample_value = updated_channel_profile[i].data->waveform_sample_value;
//        	 channel_profile[i].data->pulse_period_seconds = updated_channel_profile[i].data->pulse_period_seconds;
//        	 channel_profile[i].data->pulse_duty_cycle = updated_channel_profile[i].data->pulse_duty_cycle;

            /*
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "toggle_value");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "waveform_sample_value");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "pulse_period_seconds");
             Hack_Propagate (&updated_channel_profile[i], &channel_profile[i], "pulse_duty_cycle");
             */

            // TODO: Propagate update_channel_profile state to channel_profile state
         }

      } else if (updated_channel_profile[i].enabled == FALSE
                 && updated_channel_profile[i].enabled != channel_profile[i].enabled) {

         // Apply direction and mode.
         Channel_Set_Direction(channel_profile[i].number, CHANNEL_DIRECTION_OUTPUT);

         // Apply mode.
         Channel_Set_Type(channel_profile[i].number, CHANNEL_TYPE_TOGGLE);

         // Apply value.
         Channel_Set_Data(channel_profile[i].number, CHANNEL_VALUE_TOGGLE_OFF);

      }
   }

   return TRUE;
}

bool Channel_Enable_All() {

   bool result = TRUE;

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      result &= Channel_Enable((Channel_Number) i);
   }

   return result;
}

void Channel_Disable_All() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      Channel_Disable((Channel_Number) i);
   }
}

bool Channel_Enable(Channel_Number number) {

   bool rval = FALSE;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         rval = Channel_Enable_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         rval = Channel_Enable_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         rval = Channel_Enable_Pulse(number);
         break;
      }

      case CHANNEL_TYPE_COUNT: {
         rval = FALSE;
         break;
      }

      default: {
         break;
      }
   }

   if (rval) {
      channel_profile[number].enabled = TRUE;
   }

   return rval;
}

void Channel_Disable(Channel_Number number) {

   channel_profile[number].enabled = FALSE;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         Channel_Disable_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         Channel_Disable_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         Channel_Disable_Pulse(number);
         break;
      }

      case CHANNEL_TYPE_COUNT: {
         break;
      }

      default: {
         break;
      }
   }

//   channel_profile[number].enabled = FALSE;
}

bool Channel_Set_Type(Channel_Number number, Channel_Type type) {

   bool result = FALSE;

   Channel_Disable(number);

   channel_profile[number].type = type;

   Channel_Enable(number);

   return result;
}

Channel_Type Channel_Get_Type(Channel_Number number) {
   return channel_profile[number].type;
}

// Hardware
int32_t Channel_Set_Direction(Channel_Number number, Channel_Direction direction) {

   int32_t rval = -1;

   // Update Hardware
   switch (channel_profile[number].type) {
      case CHANNEL_TYPE_TOGGLE: {
         rval = Channel_Set_Direction_Toggle(number, direction);
         break;
      }
      case CHANNEL_TYPE_WAVEFORM: {
         rval = Channel_Set_Direction_Waveform(number, direction);
         break;
      }
      case CHANNEL_TYPE_PULSE: {
         rval = Channel_Set_Direction_Pulse(number, direction);
         break;
      }
      default: {
         break;
      }
   }

   if (rval == 0) {
      // Update Profile
      channel_profile[number].direction = direction;
   }

   return rval;
}

Channel_Direction Channel_Get_Direction(Channel_Number number) {
   return channel_profile[number].direction;
}

// MG: (?) <HACK /> What is going on here?
int32_t Channel_Set_Data(Channel_Number number, int32_t data) {

   int32_t result = -1;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {

         result = Channel_Write_Toggle(number, data);

         if (result != -1) {
//            channel_profile[number].data->toggle_value = data;

            // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

            // Get observable set...
            Observable_Set *observable_set = channel_profile[number].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable(observable_set, "toggle_value");

            // ...then update the date.
            Set_Observable_Content(observable, CONTENT_TYPE_INT32, &data);

            // </OPTIMIZE>
         }

         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         // Unsupported. Only ADC is available in the hardware right now.
         break;
      }

      case CHANNEL_TYPE_PULSE: {

//         result = Channel_Write_Pulse(number, data, channel_profile[number].data->pulse_duty_cycle);

         // <OPTIMIZE>

         // Get observable set...
         // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
         Observable_Set *observable_set = channel_profile[number].observable_set;
         Observable *observable = NULL;

         // ...then get data from channel profile...
         observable = Get_Observable(observable_set, "pulse_duty_cycle");
         int16_t pulse_duty_cycle = Get_Observable_Data_Int16(observable);

         // ...then write the output to hardware.
         result = Channel_Write_Pulse(number, data, pulse_duty_cycle);

         // </OPTIMIZE>

         if (result != -1) {
//            channel_profile[number].data->pulse_period_seconds = data;

            // <OPTIMIZE>

            // Get observable set...
            Observable_Set *observable_set = channel_profile[number].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable(observable_set, "pulse_period_seconds");

            // ...then update the data.
            Set_Observable_Content(observable, CONTENT_TYPE_FLOAT, &data);

            // </OPTIMIZE>
         }

         break;
      }

      case CHANNEL_TYPE_COUNT:
      default: {
         break;
      }
   }

   return result;
}

int32_t Channel_Get_Data(Channel_Number number) {

   int32_t result = -1;

   switch (channel_profile[number].type) {

      case CHANNEL_TYPE_TOGGLE: {
         result = Channel_Read_Toggle(number);
         break;
      }

      case CHANNEL_TYPE_WAVEFORM: {
         result = Channel_Read_Waveform(number);
         break;
      }

      case CHANNEL_TYPE_PULSE: {
         //TODO: hook up frequency read somewhere. Probably should call it a different pin type frequency_in or counter or something like that.
         break;
      }

      case CHANNEL_TYPE_COUNT:
      default: {
         break;
      }
   }

   return result;
}

// Function called to update the data sources for GPIO.
void Channel_Periodic_Call() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      if (channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
         switch (channel_profile[i].type) {
            case CHANNEL_TYPE_WAVEFORM: {
//               updated_channel_profile[i].data->waveform_sample_value = Channel_Get_Data((Channel_Number) i);

               // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

               // Get observable set...
//				Observable_Set *observable_set = updated_channel_profile[i].observable_set;
               Observable_Set *observable_set = channel_profile[i].observable_set;
               Observable *observable = NULL;

               // ...then get data from channel profile...
               observable = Get_Observable(observable_set, "waveform_sample_value");

               // ...then update the date.
               int32_t data = Channel_Get_Data((Channel_Number) i);
               Set_Observable_Content(observable, CONTENT_TYPE_INT32, &data);

               // </OPTIMIZE>

               // data->waveform_sample_value = Channel_Get_Data((Channel_Number) i);
               // data->notifyAll(); // including updated_channel_profile[i]
               break;
            }
            case CHANNEL_TYPE_TOGGLE: {
//               updated_channel_profile[i].data->toggle_value = Channel_Get_Data((Channel_Number) i);

               // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

               // Get observable set...
               Observable_Set *observable_set = channel_profile[i].observable_set;
               Observable *observable = NULL;

               // ...then get data from channel profile...
               observable = Get_Observable(observable_set, "toggle_value");

               // ...then update the date.
               int32_t data = Channel_Get_Data((Channel_Number) i);
               Set_Observable_Content(observable, CONTENT_TYPE_INT32, &data);

               // </OPTIMIZE>

               break;
            }
            default: {
               break;
            }
         }
      }
   }

// <HACK>
   Apply_Channels();
// </HACK>
}

////Local implementations /////////////////////////////////////////

// i.e., Digital
static bool Channel_Enable_Toggle(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return FALSE;

   switch (channel_profile[number].data->mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {
         if (PTB_data == NULL) {
            PTB_data = GPIO_PTB_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_PTC: {
         if (PTC_data == NULL) {
            PTC_data = GPIO_PTC_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_PTD: {
//         if (PTD_data == NULL) {
//            PTD_data = GPIO_PTD_Init(NULL);
//         }
         break;
      }

      case MCU_GPIO_PORT_PTE: {
         if (PTE_data == NULL) {
            PTE_data = GPIO_PTE_Init(NULL);
         }
         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return TRUE;
}

// i.e., Analog
static bool Channel_Enable_Waveform(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return FALSE;

   bool rval = FALSE;

   switch (channel_profile[number].data->mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {

         //TODO: Config ADC0 . we'll have to share it with the vbat adc line.

         ADC0_data = ADC0_Init(NULL);

         ADC0_StartCalibration(ADC0_data);

         while (!ADC0_GetMeasurementCompleteStatus(ADC0_data))
            ;

         LDD_TError adcCalOk = ADC0_GetCalibrationResultStatus(ADC0_data);
         rval = TRUE;

         break;
      }

      case MCU_ADC1: {

         ADC1_data = ADC1_Init(NULL);

         ADC1_StartCalibration(ADC1_data);

         while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
            ;

         LDD_TError adcCalOk = ADC1_GetCalibrationResultStatus(ADC1_data);

         rval = TRUE;
         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

// i.e., PWM
static bool Channel_Enable_Pulse(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return FALSE;

   bool rval = FALSE;

   switch (channel_profile[number].data->mcu_hardware_profile.pwm_interface->pwm_channel) {
      case MCU_PWM_OUT_1: {

         LDD_TError err;

         PWM_OUT_1_data = PWM_OUT_1_Init(NULL);

         err = PWM_OUT_1_SetFrequencyHz(PWM_OUT_1_data, 0);
         PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);

         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_2: {

         //PWM_OUT_2 not implemented
//         LDD_TError err;
//
//         PWM_OUT_2_data = PWM_OUT_2_Init(NULL);
//
//         err = PWM_OUT_2_SetFrequencyHz(PWM_OUT_2_data, 0);
//         PWM_OUT_2_SetRatio16(PWM_OUT_2_data, 0);
//
//         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_3: {

         //PWM_OUT_3 not implemented
         LDD_TError err;

         PWM_OUT_3_data = PWM_OUT_3_Init(NULL);

         err = PWM_OUT_3_SetFrequencyHz(PWM_OUT_3_data, 0);
         PWM_OUT_3_SetRatio16(PWM_OUT_3_data, 0);

         rval = TRUE;

         break;
      }

      case MCU_PWM_OUT_4: {

         //PWM_OUT_4 not implemented
//         LDD_TError err;
//
//         PWM_OUT_4_data = PWM_OUT_4_Init(NULL);
//
//         err = PWM_OUT_4_SetFrequencyHz(PWM_OUT_4_data, 0);
//         PWM_OUT_4_SetRatio16(PWM_OUT_4_data, 0);
//
//         rval = TRUE;

         break;
      }

      default: {
         break;
      }
   }

   return rval;

}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Read_Toggle(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int32_t result = -1;

   switch (channel_profile[number].data->mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         result =
               (GPIO_PTB_GetPortValue(PTB_data) & channel_profile[number].data->mcu_hardware_profile.digital_interface->mask) ? 1 :
                                                                                                                                0;

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         result =
               (GPIO_PTC_GetPortValue(PTC_data) & channel_profile[number].data->mcu_hardware_profile.digital_interface->mask) ? 1 :
                                                                                                                                0;

         break;
      }

      case MCU_GPIO_PORT_PTD: {

//         result =
//               (GPIO_PTD_GetPortValue(PTD_data) & channel_profile[number].mcu_hardware_profile.digital_interface->mask) ? 1 : 0;

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         result =
               (GPIO_PTE_GetPortValue(PTE_data) & channel_profile[number].data->mcu_hardware_profile.digital_interface->mask) ? 1 :
                                                                                                                                0;

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return result;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Read_Waveform(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return -1;

   int rval;

   switch (channel_profile[number].data->mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {

         ADC0_SelectSampleGroup(ADC0_data, channel_profile[number].data->mcu_hardware_profile.adc_interface->sample_group);

         //tell the ADC to start a measurement.
         ADC0_StartSingleMeasurement(ADC0_data);

         //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
         while (!ADC0_GetMeasurementCompleteStatus(ADC0_data))
            ;

         //get the value
         ADC0_GetMeasuredValues(ADC0_data, &rval);

         break;
      }

      case MCU_ADC1: {
         ADC1_SelectSampleGroup(ADC1_data, channel_profile[number].data->mcu_hardware_profile.adc_interface->sample_group);

         //tell the ADC to start a measurement.
         ADC1_StartSingleMeasurement(ADC1_data);

         //Block while it measures. You could alternatively do this elsewhere. We may want to periodically read and cache the adc value for each active channel to avoid this
         while (!ADC1_GetMeasurementCompleteStatus(ADC1_data))
            ;

         //get the value
         ADC1_GetMeasuredValues(ADC1_data, &rval);

         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Write_Toggle(Channel_Number number, int32_t data) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int32_t result = 0;

   switch (channel_profile[number].data->mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         if (data) {
            GPIO_PTB_SetPortBits(PTB_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTB_ClearPortBits(PTB_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (data) {
            GPIO_PTC_SetPortBits(PTC_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTC_ClearPortBits(PTC_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

//         if (data) {
//            GPIO_PTD_SetPortBits(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
//         } else {
//            GPIO_PTD_ClearPortBits(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
//         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (data) {
            GPIO_PTE_SetPortBits(PTE_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {
            GPIO_PTE_ClearPortBits(PTE_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         }

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return result;
}

// Hardware. General-purpose GPIO control.
static int32_t Channel_Write_Pulse(Channel_Number number, LDD_PPG_Tfloat period_s, uint16_t ratio) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return -1;

   int32_t rval = 0;

   switch (channel_profile[number].data->mcu_hardware_profile.pwm_interface->pwm_channel) {
      case MCU_PWM_OUT_1: {

         if (period_s > 0 && ratio > 0) {

            //set the frequency
            PWM_OUT_1_SetPeriodReal(PWM_OUT_1_data, period_s);     //50 hz for motor drive

            //this is how we set the ratio. The ratio is set by a 16-bit value. We scale a percentage up to the full scale of that 16 bit value. example: 50% = 32768
            PWM_OUT_1_SetRatio16(PWM_OUT_1_data, ratio);     //when changing frequency, fix the ratio
         } else {

            //if we set the ratio to 0, the output will never change states.
            PWM_OUT_1_SetRatio16(PWM_OUT_1_data, 0);
         }

         break;
      }

      case MCU_PWM_OUT_2: {
         break;
      }

      case MCU_PWM_OUT_3: {

         if (period_s > 0 && ratio > 0) {

            //set the frequency
            PWM_OUT_3_SetPeriodReal(PWM_OUT_1_data, period_s);     //50 hz for motor drive

            //this is how we set the ratio. The ratio is set by a 16-bit value. We scale a percentage up to the full scale of that 16 bit value. example: 50% = 32768
            PWM_OUT_3_SetRatio16(PWM_OUT_1_data, ratio);     //when changing frequency, fix the ratio
         } else {

            //if we set the ratio to 0, the output will never change states.
            PWM_OUT_3_SetRatio16(PWM_OUT_1_data, 0);
         }

         break;
      }

      case MCU_PWM_OUT_4: {
         break;
      }

      default: {
         break;
      }
   }

   return rval;
}

static int32_t Channel_Set_Direction_Toggle(Channel_Number number, Channel_Direction direction) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return -1;

   int rval = 0;

   switch (channel_profile[number].data->mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTB_SetPortInputDirection(PTB_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {

//            GPIO_PTB_SetPortOutputDirection(PTB_data,
//                                            channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
//                                            channel_profile[number].data->toggle_value);

            // <OPTIMIZE>

            // Get observable set...
            // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
            Observable_Set *observable_set = channel_profile[number].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable(observable_set, "toggle_value");
            int32_t toggle_value = Get_Observable_Data_Int32(observable);

            // </OPTIMIZE>

            GPIO_PTB_SetPortOutputDirection(PTB_data,
                                            channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
                                            toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_PTC: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTC_SetPortInputDirection(PTC_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {
//            GPIO_PTC_SetPortOutputDirection(PTC_data,
//                                            channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
//                                            channel_profile[number].data->toggle_value);

            // <OPTIMIZE>

            // Get observable set...
            // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
            Observable_Set *observable_set = channel_profile[number].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable(observable_set, "toggle_value");
            int32_t toggle_value = Get_Observable_Data_Int32(observable);

            // </OPTIMIZE>

            GPIO_PTC_SetPortOutputDirection(PTC_data,
                                            channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
                                            toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_PTD: {

//         if (direction == CHANNEL_DIRECTION_INPUT) {
//            GPIO_PTD_SetPortInputDirection(PTD_data, channel_profile[number].mcu_hardware_profile.digital_interface->mask);
//         } else {
//            GPIO_PTD_SetPortOutputDirection(PTD_data,
//                                            channel_profile[number].mcu_hardware_profile.digital_interface->mask,
//                                            channel_profile[number].toggle_value);
//         }

         break;
      }

      case MCU_GPIO_PORT_PTE: {

         if (direction == CHANNEL_DIRECTION_INPUT) {
            GPIO_PTE_SetPortInputDirection(PTE_data, channel_profile[number].data->mcu_hardware_profile.digital_interface->mask);
         } else {
//        	 GPIO_PTE_SetPortOutputDirection(PTE_data,
//        	                                             channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
//        	                                             channel_profile[number].data->toggle_value);

            // <OPTIMIZE>

            // Get observable set...
            // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
            Observable_Set *observable_set = channel_profile[number].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable(observable_set, "toggle_value");
            int32_t toggle_value = Get_Observable_Data_Int32(observable);

            // </OPTIMIZE>

            GPIO_PTE_SetPortOutputDirection(PTE_data,
                                            channel_profile[number].data->mcu_hardware_profile.digital_interface->mask,
                                            toggle_value);
         }

         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }

   return rval;
}

static int32_t Channel_Set_Direction_Waveform(Channel_Number number, Channel_Direction direction) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_WAVEFORM)
       || channel_profile[number].type != CHANNEL_TYPE_WAVEFORM) return -1;

//HACK
   if (direction == CHANNEL_DIRECTION_INPUT) {
      return 0;
   } else {
      return -1;
   }
}

static int32_t Channel_Set_Direction_Pulse(Channel_Number number, Channel_Direction direction) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return -1;

//HACK
   if (direction == CHANNEL_DIRECTION_OUTPUT) {
      return 0;
   } else {
      return -1;
   }
}

static void Channel_Disable_Toggle(Channel_Number number) {

//TODO: this needs some more work when we get to the point where we're able to reconfig pins for different operations.
//      the code below would disable the ports, but the ports are currently shared between I/O pins.
   return;

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_TOGGLE)
       || channel_profile[number].type != CHANNEL_TYPE_TOGGLE) return;

   switch (channel_profile[number].data->mcu_hardware_profile.digital_interface->port) {
      case MCU_GPIO_PORT_PTB: {
         if (PTB_data != NULL) {
            GPIO_PTB_Deinit(PTB_data);
            PTB_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_PTC: {
         if (PTC_data != NULL) {
            GPIO_PTC_Deinit(PTC_data);
            PTC_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_PTD: {
//         if (PTD_data != NULL) {
//            GPIO_PTD_Deinit(PTD_data);
//            PTD_data = NULL;
//         }
         break;
      }

      case MCU_GPIO_PORT_PTE: {
         if (PTE_data != NULL) {
            GPIO_PTE_Deinit(PTE_data);
            PTE_data = NULL;
         }
         break;
      }

      case MCU_GPIO_PORT_COUNT:
      default: {
         break;
      }
   }
}

static void Channel_Disable_Waveform(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return;

   switch (channel_profile[number].data->mcu_hardware_profile.adc_interface->adc_channel) {
      case MCU_ADC0: {

         //ADC0 doesn't get de-initialized. we use it for other things.

         break;
      }

      case MCU_ADC1: {

         //TODO: check for other ADC's still live before de-init. We'll have to figure out how to free the pin back up for reassignment.
         if (ADC1_data != NULL) {
            ADC1_Deinit(ADC1_data);
            ADC1_data = NULL;
         }

         break;
      }

      default: {
         break;
      }
   }
}

static void Channel_Disable_Pulse(Channel_Number number) {

   if (!(channel_profile[number].data->mcu_hardware_profile.supported_interfaces & CHANNEL_TYPE_PULSE)
       || channel_profile[number].type != CHANNEL_TYPE_PULSE) return;

   switch (channel_profile[number].data->mcu_hardware_profile.pwm_interface->pwm_channel) {
      case MCU_PWM_OUT_1: {

         if (PWM_OUT_1_data != NULL) {
            PWM_OUT_1_Deinit(PWM_OUT_1_data);
            PWM_OUT_1_data = NULL;
         }

         break;
      }

      case MCU_PWM_OUT_2: {
         break;
      }

      case MCU_PWM_OUT_3: {

         if (PWM_OUT_3_data != NULL) {
            PWM_OUT_3_Deinit(PWM_OUT_3_data);
            PWM_OUT_3_data = NULL;
         }

         break;
      }

      case MCU_PWM_OUT_4: {
         break;
      }

      default: {
         break;
      }
   }
}

static void Channel_Apply_Output(Channel_Number number) {

   switch (channel_profile[number].type) {
      case CHANNEL_TYPE_PULSE: {
//         Channel_Write_Pulse(number, channel_profile[number].data->pulse_period_seconds, channel_profile[number].data->pulse_duty_cycle);

         // Get observable set...
         // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
         Observable_Set *observable_set = channel_profile[number].observable_set;
         Observable *observable = NULL;

         // ...then get data from channel profile...
         observable = Get_Observable(observable_set, "pulse_duty_cycle");
         int16_t pulse_duty_cycle = (int16_t) Get_Observable_Data_Int16(observable);
         // TODO: int16_t pulse_duty_cycle = (int16_t) Get_Observable_Data (&platform_observable_profiles[number], "pulse_duty_cycle");

         observable = Get_Observable(observable_set, "pulse_period_seconds");
         float pulse_period_seconds = Get_Observable_Data_Float(observable);

         // ...then write the output to hardware.
         Channel_Write_Pulse(number, pulse_period_seconds, pulse_duty_cycle);

         break;
      }
      case CHANNEL_TYPE_TOGGLE: {
//         Channel_Write_Toggle(number, channel_profile[number].data->toggle_value);

         // Get observable set...
         // TODO: (?) Observable_Set *observable_set = platform_observable_profiles[number].observable_set;
         Observable_Set *observable_set = channel_profile[number].observable_set;
         Observable *observable = NULL;

         // ...then get data from channel profile...
         observable = Get_Observable(observable_set, "toggle_value");
         int32_t toggle_value = Get_Observable_Data_Int32(observable);

         // ...then write the output to hardware.
         Channel_Write_Toggle(number, toggle_value);
         break;
      }
      default: {
         break;
      }
   }

}

static void Initialize_Hardware_Interface() {

   for (int i = 0; i < CHANNEL_COUNT; ++i) {
      Initialize_Channel_Hardware_Interface((Channel_Number) i);
   }
}

void Set_Observable_Provider_Device_UUID(Observable_Set *observable_provider, char *device_uuid) {

   if (observable_provider != NULL) {
      // Allocate memory for the device UUID identifying the device with the observable, then copy the UUID into it
      (*observable_provider).device_uuid = (char *) malloc(strlen(device_uuid) + 1);
      memset((*observable_provider).device_uuid, '\0', strlen(device_uuid) + 1);
      memcpy((*observable_provider).device_uuid, device_uuid, strlen(device_uuid));
   }
}

/**
 * Initialize the platform. Essentially, this sets up the hardware abstraction
 * layer (HAL) for use by Clay's system architecture.
 *
 * This exposes features of the physical device to Clay.
 */
static void Initialize_Channel_Hardware_Interface(Channel_Number number) {

//   MCU_GPIO_Profile *profile = &channel_profile[number].mcu_hardware_profile;

   MCU_GPIO_Profile *profile = &platform_observable_profiles[number].mcu_hardware_profile;

//	channel_profile[i].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
//	channel_profile[i].waveform_sample_value = -1;
//	channel_profile[i].pulse_period_seconds = 0;
//	channel_profile[i].pulse_duty_cycle = 0;

   // Set default data
//	platform_observable_profiles[number].toggle_value = CHANNEL_VALUE_TOGGLE_OFF;
//	platform_observable_profiles[number].waveform_sample_value = -1;
//	platform_observable_profiles[number].pulse_period_seconds = 0;
//	platform_observable_profiles[number].pulse_duty_cycle = 0;

   char *provider_uuid[12] = { "00000000-0000-0000-0000-000000000001",
                               "00000000-0000-0000-0000-000000000002",
                               "00000000-0000-0000-0000-000000000003",
                               "00000000-0000-0000-0000-000000000004",
                               "00000000-0000-0000-0000-000000000005",
                               "00000000-0000-0000-0000-000000000006",
                               "00000000-0000-0000-0000-000000000007",
                               "00000000-0000-0000-0000-000000000008",
                               "00000000-0000-0000-0000-000000000009",
                               "00000000-0000-0000-0000-000000000010",
                               "00000000-0000-0000-0000-000000000011",
                               "00000000-0000-0000-0000-000000000012" };

   platform_observable_profiles[number].observable_provider = Create_Observable_Set(provider_uuid[number]);

   Observable *observable = NULL;
   Observable_Set *observable_set = platform_observable_profiles[number].observable_provider;
   int32 default_content_int32 = CHANNEL_VALUE_TOGGLE_ON;
   observable = Create_Observable("toggle_value", CONTENT_TYPE_INT32, &default_content_int32);
   Set_Observable_Provider_UUID(observable, provider_uuid[number]);
   Add_Observable(observable_set, observable);

   default_content_int32 = -1;
   observable = Create_Observable("waveform_sample_value", CONTENT_TYPE_INT32, &default_content_int32);
   Set_Observable_Provider_UUID(observable, provider_uuid[number]);
   Add_Observable(observable_set, observable);

   float default_content_float = 0;
   observable = Create_Observable("pulse_period_seconds", CONTENT_TYPE_FLOAT, &default_content_float);
   Set_Observable_Provider_UUID(observable, provider_uuid[number]);
   Add_Observable(observable_set, observable);

   int16_t default_content_int16 = 0;
   observable = Create_Observable("pulse_duty_cycle", CONTENT_TYPE_INT16, &default_content_int16);
   Set_Observable_Provider_UUID(observable, provider_uuid[number]);
   Add_Observable(observable_set, observable);

//	observable = Get_Observable (observable_set, "toggle_value");
//	platform_observable_profiles[number].toggle_value = Get_Observable_Data_Int32 (observable);
//
//	observable = Get_Observable (observable_set, "waveform_sample_value");
//	platform_observable_profiles[number].waveform_sample_value = Get_Observable_Data_Int32 (observable);
//
//	observable = Get_Observable (observable_set, "pulse_period_seconds");
//	platform_observable_profiles[number].pulse_period_seconds = Get_Observable_Data_Float (observable);
//	observable = Get_Observable (observable_set, "pulse_duty_cycle");
//	platform_observable_profiles[number].pulse_duty_cycle = Get_Observable_Data_Int16 (observable);

   // Set up platform-specific configuration
   switch (number) {

      case CHANNEL_1: {
         //      1,PTE1,LLWU_P0,ADC1_SE5a,SPI1_SOUT,UART1_RX,SDHC_D0,I2C1_SCL,SPI1_SIN

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_1_MASK;

         //         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;
         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_2: {
         //      2,PTE2,LLWU_P1,ADC0_DP2,ADC1_SE6a,SPI1_SCK,UART1_CTS_b,SDHC0_DCLK

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 1;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_2_MASK;

//         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;
         profile->supported_interfaces = CHANNEL_TYPE_WAVEFORM;

         break;
      }

      case CHANNEL_3: {
         //      3,PTE3,ADC0_DM2,ADC1_SE7a,SPI1_SIN,UART1_RTS_b,SDHC0_CMD,SPI1_SOUT

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTE;
         profile->digital_interface->mask = GPIO_PTE_IO_3_MASK;

//         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM;
         profile->supported_interfaces = CHANNEL_TYPE_WAVEFORM;

         break;
      }

      case CHANNEL_4: {

         //      4,PTB18,CAN0_TX,FTM2_CH0,I2S0_TX_BCLK,FTM2_QD_PHA7,PTB21,SPI2_SCK,CMP1_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_4_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_1;

//         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_PULSE;
         profile->supported_interfaces = CHANNEL_TYPE_PULSE;

         break;
      }

      case CHANNEL_5: {
         //      5,PTB19,CAN0_RX,FTM2_CH1,I2S0_TX_FS,FTM2_QD_PHA

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_5_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_2;

         //         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_PULSE;
         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_6: {

         //      6,PTB0,LLWU_P5,ADC0_SE8,ADC1_SE8,I2C0_SCL,FTM1_CH0,FTM1_QD_PHA

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->adc_interface->adc_channel = MCU_ADC1;
         profile->adc_interface->sample_group = 0;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_6_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_3;

//         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;
         profile->supported_interfaces = CHANNEL_TYPE_PULSE;

         break;
      }

      case CHANNEL_7: {
         //      7,PTB21,SPI2_SCK,CMP1_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_7_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_8: {
         //      8,PTB22,SPI2_SOUT,CMP2_OUT

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_8_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_9: {
         //      9,PTB23,SPI2_SIN,SPI0_PCS5

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTB;
         profile->digital_interface->mask = GPIO_PTB_IO_9_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_10: {
         //      10,PTC16,UART3_RX

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTC;
         profile->digital_interface->mask = GPIO_PTC_IO_10_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_11: {
         //      11,PTC17,UART3_TX

         profile->adc_interface = NULL;
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = NULL;

         profile->digital_interface->port = MCU_GPIO_PORT_PTC;
         profile->digital_interface->mask = GPIO_PTC_IO_11_MASK;

         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE;

         break;
      }

      case CHANNEL_12: {
         //      12,PTD6,LLWU_P16,ADC0_SE7b,SPI0_PCS3,UART0_RX,FTM0_CH6,FTM0_FLT0,SPI1_SOUT

         profile->adc_interface = calloc(1, sizeof(MCU_GPIO_ADC_Interface));
         profile->digital_interface = calloc(1, sizeof(MCU_GPIO_Digital_Interface));
         profile->pwm_interface = calloc(1, sizeof(MCU_GPIO_PWM_Interface));

         profile->adc_interface->adc_channel = MCU_ADC0;
         profile->adc_interface->sample_group = 2;

         profile->digital_interface->port = MCU_GPIO_PORT_PTD;
         profile->digital_interface->mask = GPIO_PTD_IO_12_MASK;

         profile->pwm_interface->pwm_channel = MCU_PWM_OUT_4;

//         profile->supported_interfaces = CHANNEL_TYPE_TOGGLE | CHANNEL_TYPE_WAVEFORM | CHANNEL_TYPE_PULSE;
         profile->supported_interfaces = CHANNEL_TYPE_WAVEFORM;

         break;
      }

      default: {
         break;
      }

   }

}
