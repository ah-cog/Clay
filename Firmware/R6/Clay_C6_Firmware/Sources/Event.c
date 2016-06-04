#include "Event.h"
#include "UUID.h"
#include "Clock.h"

uint8_t Reset_Device () {

	// TODO: Reset_Timeline ();

	Initialize_Channels ();
	Apply_Channels ();

	return TRUE;
}

Event* Create_Event (char *uuid, Action *action, char *state) {

	// Allocate memory for action construct.
	Event *event = (Event *) malloc (sizeof(Event));

	// Allocate memory for the UUID for this action construct.
	// TODO: (*actionConstruct).uuid = (char *) malloc (strlen (uuid));
	// TODO: strcpy ((*actionConstruct).uuid, uuid); // Copy action construct content

	// UUID
	(*event).uuid = (char *) malloc (strlen (uuid) + 1);
	strncpy ((*event).uuid, uuid, strlen (uuid)); // Copy the action construct's UUID
	(*event).uuid[strlen (uuid)] = 0;

	// Context
	(*event).context = NULL;

	// Trigger: Initialize trigger
	(*event).trigger = NULL;

	// Repetition: Initialize repetition type
	(*event).repeat_period = 0;

	// Action: Assign the action construct to the specified action (or NULL).
	(*event).action = (Action *) action;

	// State. Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's action).
	if (state != NULL) {
		(*event).state = (char *) malloc (strlen (state) + 1);
		strncpy ((*event).state, state, strlen (state)); // Copy action construct content
		(*event).state[strlen (state)] = 0;
	} else {
		(*event).state = NULL;
	}

	// Set up links for queue
	(*event).previous = NULL;
	(*event).next = NULL;

	// Set up bookkeeping
	(*event).start_time = 0;

	return event;
}

/**
 * NOTE: This does not free the action itself from memory!
 */
int8_t Delete_Event (Event *event) {

	if (event != NULL) {

		// TODO: Remove references to the message in the queue.

		// Free the action's UUID from memory
		free ((*event).uuid);
		(*event).uuid = NULL;

		// Free the message's content from memory
		free ((*event).state);
		(*event).state = NULL;

		// Free the message from memory
		free (event);
		event = NULL;
	}

	return TRUE;
}

void Set_Event_Context (Event *event, char *context) {
	if (context != NULL) {

		// Free previous state
		if ((*event).context != NULL) {
			free ((*event).context);
		}

		// Copy new state
		(*event).context = (char *) malloc (strlen (context) + 1);
		strncpy ((*event).context, context, strlen (context)); // Copy action construct content
		(*event).context[strlen (context)] = '\0';
	}
}

void Set_Event_State (Event *event, char *state) {
	if (state != NULL) {

		// Free previous state
		if ((*event).state != NULL) {
			free ((*event).state);
		}

		// Copy new state
		(*event).state = (char *) malloc (strlen (state) + 1);
		strncpy ((*event).state, state, strlen (state)); // Copy action construct content
		(*event).state[strlen (state)] = '\0';
	}
}

void Set_Event_Trigger (Event *event, Trigger *trigger) {
	if (event != NULL) {
		(*event).trigger = trigger;
	}
}

static int8_t Perform_Observable_Update_Action (char *state) {

   //TODO: review usage of stacked buffers. this function uses 416 bytes of stack.

   int8_t status = NULL;
   int8_t result = NULL;
   char token[256] = { 0 }; // TODO: Reduce this back down to 128 if possible!
   int tokenInt = 0;
   int i;

   // e.g., "TIT:none TIT:none TIW:none TOP:3,'waveform-sample-value'|'pulse_duty_cycle' TIT:none TIT:none TIT:none TIT:none TIT:none TIT:none TIT:none TIT:none"

   // TODO:
   // - split by ':'
   // - split by ';' and iterate through each (to combine input stream/have multiple input streams)
   // - split by ',' to get (channel, key) tuple of source
   // - remove ' quotes around observable keys for channels...

   // Update the channels
   // TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
   for (i = 0; i < CHANNEL_COUNT; i++) {

      // Get state of channel at index i (number i + 1)
      status = Get_Token(state, token, i);     // e.g., "TITL"

      // Update the GPIO states
      // TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
      // TODO: Make 0-indexing (or not) consistent with LEDs
//				Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);

      // Enable. Is the channel enabled?
      // TODO: Add an additional state to handle "no change" for channel
      updated_channel_profile[i].enabled = (token[0] == 'T' ? TRUE : FALSE);     // HACK

      // Direction. Set channel direction. Is the channel an input or output?
      if (token[1] == 'I') {
         updated_channel_profile[i].direction = CHANNEL_DIRECTION_INPUT;
      } else if (token[1] == 'O') {
         updated_channel_profile[i].direction = CHANNEL_DIRECTION_OUTPUT;
      }

      // Mode. Set channel mode. Is it a toggle (discrete switch), waveform (continuous analog signal), or pulse (e.g., PWM).
      if (token[2] == 'T') {
         updated_channel_profile[i].type = CHANNEL_TYPE_TOGGLE;     // TODO: Rename this to MODE_TOGGLE
      } else if (token[2] == 'W') {
         updated_channel_profile[i].type = CHANNEL_TYPE_WAVEFORM;
      } else if (token[2] == 'P') {
         updated_channel_profile[i].type = CHANNEL_TYPE_PULSE;
      }

      // Value. Set channel value. This depends on the direction and mode of the channel.
      if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
         if (updated_channel_profile[i].type == CHANNEL_TYPE_TOGGLE) {
            // Assign the channel's value based on the received data.
            if (token[3] == 'H') {
//                   updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_ON;

//               updated_channel_profile[i].data->toggle_value = CHANNEL_VALUE_TOGGLE_ON;

               // <OPTIMIZE>
               Observable_Set *observable_set = updated_channel_profile[i].observable_set;
               Observable *observable = NULL;

               // ...then get data from channel profile...
               observable = Get_Observable (observable_set, "toggle_value");

               // ...then update the date.
               int32 default_content_int32 = CHANNEL_VALUE_TOGGLE_ON;
               Set_Observable_Content (observable, CONTENT_TYPE_INT32, &default_content_int32);
               // </OPTIMIZE>

            } else if (token[3] == 'L') {
//                   updated_channel_profile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

//               updated_channel_profile[i].data->toggle_value = CHANNEL_VALUE_TOGGLE_OFF;

            	// <OPTIMIZE>
			   Observable_Set *observable_set = updated_channel_profile[i].observable_set;
			   Observable *observable = NULL;

			   // ...then get data from channel profile...
			   observable = Get_Observable (observable_set, "toggle_value");

			   // ...then update the date.
			   int32 default_content_int32 = CHANNEL_VALUE_TOGGLE_OFF;
			   Set_Observable_Content (observable, CONTENT_TYPE_INT32, &default_content_int32);
			   // </OPTIMIZE>
            } else {
               // ERROR: Error. An unrecognized toggle value was specified.
            }
         } else if (updated_channel_profile[i].type == CHANNEL_TYPE_WAVEFORM) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else if (updated_channel_profile[i].type == CHANNEL_TYPE_PULSE) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.

        	 // e.g., "TOP:3,'waveform-sample-value'|'pulse_duty_cycle';F,0.02|'pulse_period_seconds'"
        	 //            ^
        	 // e.g., "TOP:none"

        	 char *channel_observable_data_source = NULL; // everything after ':'
        	 char *observable_description = NULL;
        	 char *next_observable_description = NULL;
        	 char *first_output = NULL;
        	 char *second_output = NULL;
        	 char *source_channel_number_and_observable = NULL;
        	 char *source_device_uuid = NULL;
        	 char *source_channel_number = NULL;
        	 char *source_observable_key = NULL;
        	 char *destination_observable_key = NULL;

        	 channel_observable_data_source = strtok (token, ":"); // "TOP"
        	 channel_observable_data_source = token + strlen (channel_observable_data_source) + 1; // "3,'waveform_sample_value'|'pulse_duty_cycle';F,0.02|'pulse_period_seconds'"

        	 observable_description = strtok (channel_observable_data_source, ";");
        	 next_observable_description = channel_observable_data_source + strlen (observable_description) + 1;
        	 while (observable_description != NULL) {

        		 // first observable: "3,'waveform_sample_value'|'pulse_duty_cycle'"
				 source_channel_number_and_observable = strtok (observable_description, "|"); // "3,'waveform_sample_value'"

				 destination_observable_key = strtok (NULL, "|") + 1; // "'pulse_duty_cycle'"
				 destination_observable_key[strlen (destination_observable_key) - 1] = '\0';

				 // Device UUID
				 source_device_uuid = strtok (source_channel_number_and_observable, ","); // "'pulse_duty_cycle';F,0.02|'pulse_period_seconds'"
				 char *destination_device_uuid = Get_Unit_UUID();
				 bool souce_device_equals_destination_device = false;

				 // Is the content source provided by this device or a another device?
				 if (strncmp (source_device_uuid, destination_device_uuid, strlen (destination_device_uuid)) == 0) {
					 souce_device_equals_destination_device = true;
				 } else {
					 souce_device_equals_destination_device = false;
				 }

				 // Get observable provider associated with the other device

				 if (souce_device_equals_destination_device) { // <HACK />

					 source_channel_number = strtok (NULL, ","); // "'pulse_duty_cycle';F,0.02|'pulse_period_seconds'"
					 if (strncmp (source_channel_number, "F", strlen ("F")) == 0) {
						 source_observable_key = strtok (NULL, ","); // "F,0.02"
						 source_observable_key[strlen (source_observable_key)] = '\0';

						 // TODO: Create "Constant Observable" and set it as the source!

						 // F,0.02|'pulse_period_seconds'"

						 // Observable_Set *source_observable_set = channel_profile[source_channel_index].observable_set;
						 Observable_Set *destination_observable_set = channel_profile[i].observable_set;

						 Observable *destination_observable = Get_Observable (destination_observable_set, destination_observable_key);
						 float content_float = strtof (source_observable_key, NULL); // ((float) atoi(frequency_str) / 1000000);
						 Set_Observable_Content (destination_observable, CONTENT_TYPE_FLOAT, &content_float);

						 // <HACK>

						 // </HACK>

					 } else {
						 source_observable_key = strtok (NULL, ",") + 1; // "3,'waveform-sample-value'"
						 source_observable_key[strlen (source_observable_key) - 1] = '\0';

						 int16_t source_channel_index = atoi (source_channel_number) - 1;

						 // <HACK>

						 // Propagate state

						 Observable_Set *source_observable_set = channel_profile[source_channel_index].observable_set;
						 Observable_Set *destination_observable_set = channel_profile[i].observable_set;

						 if (!Has_Propagator (Get_Observable (source_observable_set, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
							   source_observable_key,
							   Get_Observable (destination_observable_set, destination_observable_key),
							   destination_observable_key)) {

							 Propagator *propagator = Create_Propagator (
							   Get_Observable (source_observable_set, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
							   source_observable_key,
							   Get_Observable (destination_observable_set, destination_observable_key),
							   destination_observable_key);
							 Add_Propagator (
							   Get_Observable (source_observable_set, source_observable_key),
							   propagator);

						 }


		 //				 Apply_Channels();

					   // </HACK>
					 }
				 }

        		 // Get the next observable description
        		 observable_description = strtok (next_observable_description, ";");
        		 next_observable_description = next_observable_description + strlen (observable_description) + 1;
        	 }

//        	 // TODO: Replace this with a loop that gets each structure description
//        	 first_output = strtok (channel_observable_data_source, ";");
//        	 second_output = strtok (NULL, ";");
//
//        	 // first observable: "3,'waveform_sample_value'|'pulse_duty_cycle'"
//        	 source_channel_number_and_observable = strtok (first_output, "|"); // "3,'waveform_sample_value'"
//        	 destination_observable_key = strtok (NULL, "|") + 1; // "'pulse_duty_cycle'"
//        	 destination_observable_key[strlen (destination_observable_key) - 1] = '\0';
//
//        	 source_channel_number = strtok (source_channel_number_and_observable, ","); // "3,'waveform_sample_value'"
//        	 source_observable_key = strtok (NULL, ",") + 1; // "3,'waveform-sample-value'"
//        	 source_observable_key[strlen (source_observable_key) - 1] = '\0';
//
//        	 // second observable: "F,0.02|'pulse_period_seconds'"
//			 source_channel_number_and_observable = strtok (second_output, "|"); // "3,'waveform_sample_value'"
//			 destination_observable_key = strtok (NULL, "|") + 1; // "'pulse_duty_cycle'"
//			 destination_observable_key[strlen (destination_observable_key) - 1] = '\0';
//
//			 source_channel_number = strtok (source_channel_number_and_observable, ","); // "3,'waveform_sample_value'"
//			 source_observable_key = strtok (NULL, ",") + 1; // "3,'waveform-sample-value'"
//			 source_observable_key[strlen (source_observable_key) - 1] = '\0';


//        	 Get_Token_With_Delimiter (token, ':', '\'', channel_observable_data_source, 1); // "3,'waveform-sample-value'|'pulse_duty_cycle'"

//        	 if (strncmp (channel_observable_data_source, "none", strlen ("none")) != 0) {
//
//				 Get_Token_With_Delimiter (channel_observable_data_source, '|', '\'', source_channel_number_and_observable, 0); // "3,'waveform-sample-value'"
//				 Get_Token_With_Delimiter (channel_observable_data_source, ',', '\'', source_observable_key, 1); // "'pulse_duty_cycle'"
//
//				 Get_Token_With_Delimiter (source_channel_number_and_observable, ',', '\'', source_channel_number, 0); // "3"
//				 Get_Token_With_Delimiter (source_channel_number_and_observable, ',', '\'', source_observable_key, 1); // "waveform-sample-value"
//
//				 Get_Token_With_Delimiter (source_channel_number_and_observable, ',', '\'', destination_observable_key, 0); // "pulse_duty_cycle"
//
//				 int16_t source_channel_index = atoi (source_channel_number) - 1;
//
//				 // <HACK>
//
//				 // Propagate state
//
//				 Observable_Set *source_observable_set = channel_profile[source_channel_index].observable_set;
//				 Observable_Set *destination_observable_set = channel_profile[i].observable_set;
//
//				 if (!Has_Propagator (Get_Observable (source_observable_set, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
//					   source_observable_key,
//					   Get_Observable (destination_observable_set, destination_observable_key),
//					   destination_observable_key)) {
//
//					 Propagator *propagator = Create_Propagator (
//					   Get_Observable (source_observable_set, source_observable_key), // Get_Observable (source_observable_set, "waveform_sample_value"),
//					   source_observable_key,
//					   Get_Observable (destination_observable_set, destination_observable_key),
//					   destination_observable_key);
//					 Add_Propagator (
//					   Get_Observable (source_observable_set, source_observable_key),
//					   propagator);
//
//				 }


//				 Apply_Channels();

			   // </HACK>


//        	 }

//            char * frequency_str = token + 4;
//            char * duty_str = strchr(token, DEFAULT_TOKEN_PARAMETER_DELIMITER) + 1;
//            *(duty_str - 1) = '\0';     //do this so we can use atoi
//
//            Observable *observable = NULL;
//            //Observable_Set *observable_set = updated_channel_profile[i].observable_set;
//            Observable_Set *observable_set = channel_profile[i].observable_set;
//
////            THIS IS OVERWRITING THE VALUE PROPAGATED FROM THE INPUT! OPEN FOR 1 PROPAGATION EVERY TIME THIS EXECUTES (LIKE A DOOR)! CAN ALSO SET UP SO IT USES CONTINUOUS PROPAGATION.
////            -- TEST THIS BY JUST COMMENTING OUT THE CODE BELOW THAT CALLS "Set_Observable_Content"
//
//            observable = Get_Observable (observable_set, "pulse_period_seconds");
//            float content_float = strtof(frequency_str, NULL); // ((float) atoi(frequency_str) / 1000000);
//            Set_Observable_Content (observable, CONTENT_TYPE_FLOAT, &content_float);
////            updated_channel_profile[i].data->pulse_period_seconds = ((float) atoi(frequency_str) / 1000000);
//
//            observable = Get_Observable (observable_set, "pulse_duty_cycle");
//			int16_t content_int16 = (int16_t) atoi (duty_str);
//			Set_Observable_Content (observable, CONTENT_TYPE_INT16, &content_int16);
////            updated_channel_profile[i].data->pulse_duty_cycle = atoi(duty_str);
//
//            //restore the delimiter in case it's needed later.
//            *(duty_str - 1) = DEFAULT_TOKEN_PARAMETER_DELIMITER;

         } else {
            // ERROR: Error. An invalid mode was specified.
         }
      } else if (updated_channel_profile[i].direction == CHANNEL_DIRECTION_INPUT) {
         // NOTE: The channel direction is input, so its value is set by the pin's voltage state.
         if (updated_channel_profile[i].type == CHANNEL_TYPE_TOGGLE) {
            // Assign the channel value based on the physical pin state.
//        	 updated_channel_profile[i].data->toggle_value = Channel_Get_Data(updated_channel_profile[i].number);

        	 // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

        	 // Get observable set...
        	 Observable_Set *observable_set = channel_profile[i].observable_set;
        	 Observable *observable = NULL;

        	 // ...then get data from channel profile...
        	 observable = Get_Observable (observable_set, "toggle_value");

        	 // ...then update the date.
        	 int32_t data = Channel_Get_Data(updated_channel_profile[i].number);
        	 Set_Observable_Content (observable, CONTENT_TYPE_INT32, &data);

        	 // </OPTIMIZE>

         } else if (updated_channel_profile[i].type == CHANNEL_TYPE_WAVEFORM) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
//            updated_channel_profile[i].data->waveform_sample_value = Channel_Get_Data(updated_channel_profile[i].number);

            // <OPTIMIZE> (Optimize syntax to be smaller, preferably one line.)

            // Get observable set...
            Observable_Set *observable_set = channel_profile[i].observable_set;
            Observable *observable = NULL;

            // ...then get data from channel profile...
            observable = Get_Observable (observable_set, "waveform_sample_value");

            // ...then update the date.
//            int32_t data = Channel_Get_Data(updated_channel_profile[i].number);
            int32 waveform_sample_value = Get_Observable_Data_Int32 (observable);
//            Set_Observable_Content (observable, CONTENT_TYPE_INT32, &data);

            // </OPTIMIZE>

         } else if (updated_channel_profile[i].type == CHANNEL_TYPE_PULSE) {
            // TODO: Assign the value differently, depending on the specified channel direction and mode.
            // TODO: Assign this based on the received data.
         } else {
            // ERROR: Error. An invalid mode was specified.
         }
      } else {
         // ERROR: Error. An unrecognized channel direction was specified.
      }
   }

   // Apply channel
   // TODO: Move this to a common place, maybe in Application in the loop logic.
   Apply_Channels();
//	Apply_Channel_Lights ();

   result = TRUE;

   return result;
}

/**
 * Performs the physical action for the specified action as it is defined
 * by the formal grammar that defines the capabilities of Clay.
 *
 * Presently, the grammar is implemented as a series of conditional statements.
 */
int8_t Process_Event (Event *event) {

	int8_t result = FALSE;

	uint8_t is_triggered = FALSE;

	uint32_t millis;

	// Check if event's action or state are not yet assigned.
	if ((*event).action == NULL || (*event).state == NULL) {
		return TRUE;
	}

	// Context
	// TODO: Create a "no change" default context (maybe that's just NULL, but it should be defined IN CLAY'S LANGUAGE, so Clay can lift off from C)
	if ((*event).context != NULL) {
		Perform_Observable_Update_Action ((*event).context);
	}

	// Trigger. Check event trigger, and only call script if it is met.
	if ((*event).trigger != NULL) {
		// TODO: Check if condition was met. If so, perform action. If not, proceed to next action.
		Message *msg = Peek_Message (&incomingMessageQueue);
		if (msg != NULL) {
			if (strncmp ((*msg).content, (*((*event).trigger)).message_content, strlen ((*((*event).trigger)).message_content)) == 0) {
				is_triggered = TRUE;
			}
		}
	} else {
		is_triggered = TRUE;
	}

	if (is_triggered == TRUE) {

		// Record event start time.
		if ((*event).start_time == 0) {
			(*event).start_time = Millis ();
		}

		// TODO: Queue the message rather than executing it immediately (unless specified)
		// TODO: Parse the message rather than brute force like this.
		// TODO: Decompose the action into atomic actions and perform them!

	//	if (action_wait_time == 0) {
	//		pause_duration_integer = atoi (token);
	//		action_wait_time = pause_duration_integer;
	//	}

		// Check if the action's wait time has expired
		millis = Millis ();
		if ((millis - (*event).start_time) >= (*event).repeat_period) {
			(*event).start_time = 0;
			result = Perform_Action ((*event).action, (*event).state);
		} else if ((millis - (*event).start_time) < (*event).repeat_period) {
			result = 2; // 2 means waiting... (pausing on event...)
		}
//		else {
//			result = FALSE;
//		}
	}

	return result;
}


