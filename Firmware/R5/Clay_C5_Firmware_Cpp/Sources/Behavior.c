#include "Behavior.h"
#include "Drivers/ESP8266.h"
#include "Clock.h"

Behavior_Construct* behaviorCache;
Behavior_Construct* loop; // TODO: Create a separate Loop data structure.               
Behavior_Construct* currentBehaviorConstruct; // Pointer to the loop's current behavior.

uint8_t Reset_Unit () {
	
	Reset_Behavior ();
	
	Initialize_Channels ();
	Apply_Channels ();
	
	return TRUE;
}

// Remove behaviors constructs from loop
// Delete behaviors
// Set loop to null
// Delete behaviors
// Remove behavior constructs from cache
// Set cache to null
uint8_t Reset_Behavior () {
	
	Behavior_Construct *behaviorConstruct = NULL;
	Behavior *behavior = NULL;
	
	// Remove all behavior constructs from the loop.
	behaviorConstruct = loop; // Point the behavior construct to the first element in the the loop.
	while (behaviorConstruct != NULL) {
		
		// Remove the behavior from the loop.
		// This function:
		// (1) Removes the behavior construct associated with the specified behavior from the loop, 
		// (2) Updates the linked list of behavior constructs representing the loop to reflect the removal, and
		// (3) Deletes the behavior construct from memory.
		behavior = Remove_Behavior ((*behaviorConstruct).behavior);
		// NOTE: The behavior construct associated with the behavior is deleted in Remove_Behavior ((*behaviorConstruct).behavior), which calls Delete_Behavior_Construct (behaviorConstruct).
		
		// NOTE: The actual behavior associated with the behavior construct is deleted below, when deleting the cache.
		
		// Continue to the next behavior.
		behaviorConstruct = loop; // NOTE: This is similar to "behaviorConstruct = (*behaviorConstruct).next;" when removing behaviors.
	}
	
	behaviorConstruct = behaviorCache;
	while (behaviorConstruct != NULL) {
		
		behavior = Remove_Behavior_From_Cache ((*behaviorConstruct).behavior);
		
		Delete_Behavior (behavior);
		
		behaviorConstruct = behaviorCache; // NOTE: This is similar to "behaviorConstruct = (*behaviorConstruct).next;" when removing behaviors.
		
	}
}

Behavior_Construct* Create_Behavior_Construct (const char *behaviorUuid, const Behavior *behavior) {
	
	// Allocate memory for behavior construct.
	Behavior_Construct *behaviorConstruct = (Behavior_Construct *) malloc (sizeof (Behavior_Construct));
	
	// Allocate memory for the UUID for this behavior construct.
	// TODO: (*behaviorConstruct).uuid = (char *) malloc (strlen (uuid));
	// TODO: strcpy ((*behaviorConstruct).uuid, uuid); // Copy behavior construct content
	
	// Allocate memory for the UUID for this behavior.
	(*behaviorConstruct).behaviorUuid = (char *) malloc (strlen (behaviorUuid));
	strcpy ((*behaviorConstruct).behaviorUuid, behaviorUuid); // Copy the behavior construct's UUID
	
	// Assign the behavior construct to the specified behavior (or NULL).
	(*behaviorConstruct).behavior = (Behavior *) behavior;
	
	// Set up links for queue
	(*behaviorConstruct).previous = NULL;
	(*behaviorConstruct).next = NULL;
	
	return behaviorConstruct;
}

/**
 * NOTE: This does not free the behavior itself from memory!
 */
int8_t Delete_Behavior_Construct (Behavior_Construct *behaviorConstruct) {
	
	if (behaviorConstruct != NULL) {
		
		// TODO: Remove references to the message in the queue.

		// Free the behavior's UUID from memory
		free ((*behaviorConstruct).behaviorUuid);
		(*behaviorConstruct).behaviorUuid = NULL;
		
		// Free the behavior construct's UUID from memory
		// TODO: free ((*behaviorConstruct).uuid);
		// TODO: (*behaviorConstruct).uuid = NULL;
		
		// Free the message from memory
		free (behaviorConstruct);
		behaviorConstruct = NULL;
	}
	
	return TRUE;
}

uint8_t Initialize_Behavior_Cache () {
	behaviorCache = NULL;
	return TRUE;
}

int16_t Cache_Behavior (Behavior *behavior) {
	
	Behavior_Construct *previousBehaviorConstruct = NULL; // The behavior construct presently at the end of the list. This will be set as the previous behavior construct to the one created for the newly-cached behavior.
	uint16_t behaviorConstructCount = 0;
	
	// TODO: Consider checking the cache for the existing behavior. That, or note that doing it manually is required with Has_Cached_Behavior ().
	
	// Create a behavior construct to denote to the behavior.
	Behavior_Construct *behaviorConstruct = Create_Behavior_Construct ((*behavior).uuid, behavior);
	
	if (behaviorCache == NULL) {
		
		// The loop is empty, so add it to the loop as the only element.
		behaviorCache = behaviorConstruct;
		
		(*behaviorConstruct).previous = NULL;
		(*behaviorConstruct).next = NULL;
		
		behaviorConstructCount = 1;
		
		// Set the loop pointer to the only behavior
		
		//currentBehavior = behavior;
		
		
	} else {
		
		// Search for the last element in the queue.
		previousBehaviorConstruct = behaviorCache; // Get the front of the queue.
		behaviorConstructCount++;
		while ((*previousBehaviorConstruct).next != NULL) {
			previousBehaviorConstruct = (*previousBehaviorConstruct).next;
			behaviorConstructCount++;
		}
		
		// Update the linked list to add the message to the back of the queue.
		// (*message).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
		(*behaviorConstruct).previous = previousBehaviorConstruct;
		(*previousBehaviorConstruct).next = behaviorConstruct;
		behaviorConstructCount++;
		
	}
	
	return behaviorConstructCount;
}

Behavior* Get_Cached_Behavior_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL; 
	
	if (behaviorCache != NULL) {
		
		// Search for the behavior construct associated with the behavior that has the specified UUID.
		behaviorConstruct = behaviorCache; // Get the first behavior construct in the cache list.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return (*behaviorConstruct).behavior; // Return the behavior associated with the specified behavior construct.
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return NULL;
}

uint8_t Has_Cached_Behaviors () {
	return (behaviorCache != NULL ? TRUE : FALSE);
}

uint8_t Has_Cached_Behavior_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL;
	
	if (behaviorCache != NULL) {
		
		// Search for the last element in the queue.
		behaviorConstruct = behaviorCache; // Get the front of the queue.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return TRUE;
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return FALSE;
}

Behavior_Construct* Get_Cached_Behavior_Construct_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL; 
	
	if (behaviorCache != NULL) {
		
		// Search for the behavior construct associated with the behavior that has the specified UUID.
		behaviorConstruct = behaviorCache; // Get the first behavior construct in the cache list.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return behaviorConstruct; // Return the behavior associated with the specified behavior construct.
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return NULL;
}

Behavior* Remove_Behavior_From_Cache (Behavior *behavior) {
	
	Behavior_Construct *behaviorConstruct = NULL;
	
	// Get the behavior construct associated with the specified behavior.
	if (behavior != NULL && (*behavior).uuid != NULL) {
		behaviorConstruct = Get_Cached_Behavior_Construct_By_UUID ((*behavior).uuid);
	}
	
	if (behaviorConstruct != NULL && behaviorCache != NULL) {
		
		// Reference the behavior at the front of the queue.
		// behaviorConstruct = loop;
		
		// Update the linked list to remove the behavior from the front of the queue.
		if ((*behaviorConstruct).previous == NULL && (*behaviorConstruct).next != NULL) {
			
			// The behavior in the first in the loop.
			
			behaviorCache = (*behaviorConstruct).next; // Update the loop's first behavior to be the next one.
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			(*behaviorCache).next = NULL; // Update the the new first behavior in the loop so it doesn't link to a "previous" behavior.
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next != NULL) {
			
			// The behavior is within the loop. It has previous and next behaviors.
			
			(*(*behaviorConstruct).previous).next = (*behaviorConstruct).next; // Update the previous behavior to skip this behavior and point to the next behavior.
			
			(*(*behaviorConstruct).next).previous = (*behaviorConstruct).previous; // Update the next behavior skip this behavior and point to the previous behavior.
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next == NULL) {
			
			// The behavior is the last in the loop. It has previous behaviors only.
			
			(*(*behaviorConstruct).previous).next = NULL; // Update the previous behavior be the new last behavior in the loop. That is, make it point to no other behavior (and point to NULL).
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else {
			
			// There are no more behaviors in the loop, so remove all links and reset the loop to its "empty" state.
			
			behaviorCache = NULL; // Remove the link to any behaviors at the front of the loop.
			
			currentBehaviorConstruct = NULL; // Reset the current behavior to NULL, so no behavior will be performed.
			
			// Unlink the behaviors from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		}
		
		// Free the behavior construct from memory.
		// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
		Delete_Behavior_Construct (behaviorConstruct);
	}
	
	return NULL;
}

uint8_t Initialize_Behavior () {
	loop = NULL;
	currentBehaviorConstruct = NULL;
	return TRUE;
}

Behavior* Create_Behavior (const char *uuid, const char *content) {
	
	// Allocate memory for behavior construct.
	Behavior *behavior = (Behavior *) malloc (sizeof (Behavior));
	
	// Allocate memory for the UUID for this behavior.
	(*behavior).uuid = (char *) malloc (strlen (uuid));
	strcpy ((*behavior).uuid, uuid); // Copy behavior construct content
	
	// Allocate memory for the content (i.e., the starting symbol to the grammar defining Clay's behavior).
	(*behavior).content = (char *) malloc (strlen (content));
	strcpy ((*behavior).content, content); // Copy behavior construct content
	
	// TODO: Set up link to the behavior's loop. This will be NULL for the basic behaviors provided by the formal grammar defining Clay's physical behavior.
	
	return behavior;
}

int8_t Delete_Behavior (Behavior *behavior) {
	
	if (behavior != NULL) {
		
		// TODO: Remove references (i.e., set to NULL) to the specified behavior in the loop and cache.
		
		// Free the message's UUID from memory
		free ((*behavior).uuid);
		(*behavior).uuid = NULL;
		
		// Free the message's content from memory
		free ((*behavior).content);
		(*behavior).content = NULL;
		
		// Free the message from memory
		free (behavior);
		behavior = NULL;
		
		// TODO: Look for references to the behavior in behaviorCache and loop.
	}
	
	return TRUE;
}

int16_t Add_Behavior (Behavior *behavior) {
	// TODO: Consider changing to "int16_t Add_Behavior (char *behaviorUuid)" and search for the behavior in the local cache and universal repository.
	
	Behavior_Construct *previousBehaviorConstruct = NULL; // The behavior construct presently at the end of the list. This will be set as the previous behavior construct to the one created for the newly-cached behavior.
	uint16_t behaviorConstructCount = 0;
	
	// Create a behavior construct to denote to the behavior for the loop!
	// NOTE: This construct must be different than the construct for the behavior cache to preserve their unique link structures and prevent infinite looping during list traversal.
	Behavior_Construct *behaviorConstruct = Create_Behavior_Construct ((*behavior).uuid, behavior);
	
	// TODO: Consider checking of the behavior has a behavior construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Behavior () _before_ calling Add_Behavior.
	
	if (loop == NULL) {
		
		// The loop is empty, so add it to the loop as the only element.
		loop = behaviorConstruct;
		
		(*behaviorConstruct).previous = NULL;
		(*behaviorConstruct).next = NULL;
		
		behaviorConstructCount = 1;
		
		// Set the loop pointer to the only behavior
		
		currentBehaviorConstruct = behaviorConstruct;
		
		
	} else {
		
		// Search for the last element in the loop (represented as a list).
		previousBehaviorConstruct = loop; // Get the front of the queue.
		behaviorConstructCount++;
		while ((*previousBehaviorConstruct).next != NULL) {
			previousBehaviorConstruct = (*previousBehaviorConstruct).next;
			behaviorConstructCount++;
		}
		
		// Update the linked list to add the message to the back of the queue.
		// (*behaviorConstruct).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
		(*behaviorConstruct).previous = previousBehaviorConstruct;
		(*previousBehaviorConstruct).next = behaviorConstruct;
		behaviorConstructCount++;
		
	}
	
	return behaviorConstructCount;
}

int16_t Add_Before_Behavior (Behavior *behavior, Behavior *otherBehavior) {
	// TODO: Consider changing to "int16_t Add_Behavior (char *behaviorUuid)" and search for the behavior in the local cache and universal repository.
	
	Behavior_Construct *nextBehaviorConstruct = NULL; // The behavior construct presently at the end of the list. This will be set as the previous behavior construct to the one created for the newly-cached behavior.
	uint16_t behaviorConstructCount = 0;
	
	// Create a behavior construct to denote to the behavior for the loop!
	// NOTE: This construct must be different than the construct for the behavior cache to preserve their unique link structures and prevent infinite looping during list traversal.
	Behavior_Construct *behaviorConstruct = Create_Behavior_Construct ((*behavior).uuid, behavior);
	
	// TODO: Consider checking of the behavior has a behavior construct in the cache. If so reference that one. If not, create one. That, or note that doing it manually is required with Has_Cached_Behavior () _before_ calling Add_Behavior.
	
	if (loop == NULL) {
		
		// The loop is empty, so add it to the loop as the only element.
		loop = behaviorConstruct;
		
		(*behaviorConstruct).previous = NULL;
		(*behaviorConstruct).next = NULL;
		
		behaviorConstructCount = 1;
		
		// Set the loop pointer to the only behavior
		currentBehaviorConstruct = behaviorConstruct;
		
		
	} else {
		
		// Search for the last element in the loop (represented as a list).
		nextBehaviorConstruct = loop; // Get the front of the queue.
		behaviorConstructCount++;
		while (strncmp ((*nextBehaviorConstruct).behaviorUuid, (*otherBehavior).uuid, strlen ((*otherBehavior).uuid) != 0)) {
		//while ((*nextBehaviorConstruct).next != otherBehavior) {
			nextBehaviorConstruct = (*nextBehaviorConstruct).next;
			behaviorConstructCount++;
		}
		
		// Update the linked list to add the message to the back of the queue.
		// (*behaviorConstruct).previous = NULL; // NOTE: This should already be NULL at this point, so this is redundant, but adds some degree of robustness.
		
		// Link the new behavior into the loop.
		(*behaviorConstruct).previous = (*nextBehaviorConstruct).previous;
		(*behaviorConstruct).next = nextBehaviorConstruct;
		
		// Update the previous behavior (if it's not NULL)
		if ((*behaviorConstruct).previous != NULL) {
			(*(*behaviorConstruct).previous).next = behaviorConstruct;
		}
		
		// Update the next behavior
		(*nextBehaviorConstruct).previous = behaviorConstruct;
		
		// Update the loop's current behavior.
		if ((*behaviorConstruct).previous == NULL) {
			loop = behaviorConstruct; // Update the added behavior's links to the be the first in the loop.
		}
		
		behaviorConstructCount++;
		
	}
	
	return behaviorConstructCount;
}

Behavior* Remove_Behavior (Behavior *behavior) {
	
	Behavior_Construct *behaviorConstruct = NULL;
	
	// Get the behavior construct associated with the specified behavior.
	if (behavior != NULL && (*behavior).uuid != NULL) {
		behaviorConstruct = Get_Behavior_Construct_By_UUID ((*behavior).uuid);
	}
	
	if (behaviorConstruct != NULL && loop != NULL) {
		
		// Reference the behavior at the front of the queue.
		// behaviorConstruct = loop;
		
		// Update the linked list to remove the behavior from the front of the queue.
		if ((*behaviorConstruct).previous == NULL && (*behaviorConstruct).next != NULL) {
			
			// The behavior in the first in the loop.
			
			loop = (*behaviorConstruct).next; // Update the loop's first behavior to be the next one.
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			(*loop).next = NULL; // Update the the new first behavior in the loop so it doesn't link to a "previous" behavior.
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next != NULL) {
			
			// The behavior is within the loop. It has previous and next behaviors.
			
			(*(*behaviorConstruct).previous).next = (*behaviorConstruct).next; // Update the previous behavior to skip this behavior and point to the next behavior.
			
			(*(*behaviorConstruct).next).previous = (*behaviorConstruct).previous; // Update the next behavior skip this behavior and point to the previous behavior.
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next == NULL) {
			
			// The behavior is the last in the loop. It has previous behaviors only.
			
			(*(*behaviorConstruct).previous).next = NULL; // Update the previous behavior be the new last behavior in the loop. That is, make it point to no other behavior (and point to NULL).
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		} else {
			
			// There are no more behaviors in the loop, so remove all links and reset the loop to its "empty" state.
			
			loop = NULL; // Remove the link to any behaviors at the front of the loop.
			
			currentBehaviorConstruct = NULL; // Reset the current behavior to NULL, so no behavior will be performed.
			
			// Unlink the behaviors from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
		}
		
		// Free the behavior construct from memory.
		// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
		Delete_Behavior_Construct (behaviorConstruct);
	}
	
	return NULL;
}

uint8_t Has_Behaviors () {
	return (loop != NULL ? TRUE : FALSE);
}

uint8_t Has_Behavior_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL;
	
	if (loop != NULL) {
		
		// Search for the last element in the queue.
		behaviorConstruct = loop; // Get the front of the queue.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return TRUE;
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return FALSE;
}

Behavior* Get_Behavior_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL; 
	
	if (loop != NULL) {
		
		// Search for the behavior construct associated with the behavior that has the specified UUID.
		behaviorConstruct = loop; // Get the first behavior construct in the cache list.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return (*behaviorConstruct).behavior; // Return the behavior associated with the specified behavior construct.
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return NULL;
}

Behavior_Construct* Get_Behavior_Construct_By_UUID (char *behaviorUuid) {
	
	Behavior_Construct *behaviorConstruct = NULL; 
	
	if (loop != NULL) {
		
		// Search for the behavior construct associated with the behavior that has the specified UUID.
		behaviorConstruct = loop; // Get the first behavior construct in the cache list.
		while (behaviorConstruct != NULL) {
			if (strncmp (behaviorUuid, (*behaviorConstruct).behaviorUuid, strlen ((*behaviorConstruct).behaviorUuid)) == 0) {
				return behaviorConstruct; // Return the behavior associated with the specified behavior construct.
			}
			behaviorConstruct = (*behaviorConstruct).next;
		}
	}
	
	return NULL;
}

uint32_t behaviorStartTime = 0;
uint32_t behaviorWaitTime = 0;

/**
 * Performs the physical behavior for the specified behavior as it is defined 
 * by the formal grammar that defines the capabilities of Clay.
 * 
 * Presently, the grammar is implemented as a series of conditional statements.
 */
int8_t Perform_Behavior (Behavior *behavior) {
	
	int8_t status = NULL;
	int8_t result = NULL;
	char token[32] = { 0 };
	int tokenInt = 0;
	int i;
	
	char *behaviorContent = NULL;
	behaviorContent = (*behavior).content;
	
	if (behaviorStartTime == 0) {
		behaviorStartTime = Millis ();
	}
	
	// TODO: Queue the message rather than executing it immediately (unless specified)
	// TODO: Parse the message rather than brute force like this.
	// TODO: Decompose the behavior into atomic behaviors and perform them!
	
	// turn light 1 on
	// ^
	if ((status = getToken (behaviorContent, token, 0)) != NULL) { // status = getToken (message, token, 0);
			
		if (strncmp (token, "cause", strlen ("cause")) == 0) {
						
			// cause 1 effect 4
			// ^
			// TODO: Something like: cause TTOT TTOT effect TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT
			
			// Update the channels
			// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
//			status = getToken (behaviorContent, token, 1); // Cause
//			status = getToken (behaviorContent, token, 2); // Effect
			// TODO: Consider updating the cause conditions?: Update_Channel_State ()
			status = getToken (behaviorContent, token, 1); // Cause
			tokenInt = atoi (token) - 1;
			
			// TODO: Consider NOT automatically changing the I/O state of the cause. Maybe rely on setting the pin mode first!
			// TODO: Update all the input states and then update all the output states.

			updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
			updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_INPUT;
			updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
			updateChannelProfile[tokenInt].value = Get_Channel_Value (updateChannelProfile[tokenInt].number);
			
//			if (strncmp (token, "switch", strlen ("switch")) == 0) { 
			if (updateChannelProfile[tokenInt].value == CHANNEL_VALUE_TOGGLE_ON) {
				
				// TODO: Look for "effect"
				
				status = getToken (behaviorContent, token, 3); // Effect
				tokenInt = atoi (token) - 1;
				updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
				updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_OUTPUT;
				updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
				updateChannelProfile[tokenInt].value = CHANNEL_VALUE_TOGGLE_ON;
				
			} else if (updateChannelProfile[tokenInt].value == CHANNEL_VALUE_TOGGLE_OFF) {
				
				// TODO: Look for "effect"
				
				status = getToken (behaviorContent, token, 3); // Effect
				tokenInt = atoi (token) - 1;
				updateChannelProfile[tokenInt].enabled = CHANNEL_ENABLED;
				updateChannelProfile[tokenInt].direction = CHANNEL_DIRECTION_OUTPUT;
				updateChannelProfile[tokenInt].mode = CHANNEL_MODE_TOGGLE;
				updateChannelProfile[tokenInt].value = CHANNEL_VALUE_TOGGLE_OFF;
				
			}
			// TODO: Get the (cause, effect) condition.
			
			// TODO: Create (cause, effect) behavior.
			
			// Apply channel
			// TODO: Move this to a common place, maybe in Application in the loop logic.
//			if (effect is local) { // TODO: Get UUID of cause and effect units.
				Apply_Channels ();
//			} else if (effect is remote) {
//				Request_Remote_Apply_Channels ();
//			}
			
			result = TRUE;
			
		} else if (strncmp (token, "apply", strlen ("apply")) == 0) {
			
			// apply TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT TTOT
			// ^
			
			// Update the channels
			// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
			for (i = 0; i < 12; i++) {
				status = getToken (behaviorContent, token, 1 + i);
				
				// Set LED state
				if (token[0] == 'T') {
					updateChannelLightProfiles[i].enabled = TRUE;
					updateChannelLightProfiles[i].color = &onColor;
//					Set_LED_Output ((RGB_LED) (i + 1),  &onColor);
				} else {
					updateChannelLightProfiles[i].enabled = TRUE;
					updateChannelLightProfiles[i].color = &offColor;
//					Set_LED_Output ((RGB_LED) (i + 1),  &offColor);
				}
				
				// Update the GPIO states
				// TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
				// TODO: Make 0-indexing (or not) consistent with LEDs
//				Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);
				
				// Enable. Is the channel enabled?
				// TODO: Add an additional state to handle "no change" for channel
				updateChannelProfile[i].enabled = (token[1] == 'T' ? TRUE : FALSE); // HACK
				
				// Direction. Set channel direction. Is the channel an input or output?
				if (token[2] == 'I') {
					updateChannelProfile[i].direction = CHANNEL_DIRECTION_INPUT;
				} else if (token[2] == 'O') {
					updateChannelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
				} else if (token[2] == '-') {
					// NOTE: Don't change!
				}
				
				// Mode. Set channel mode. Is it a toggle (discrete switch), waveform (continuous analog signal), or pulse (e.g., PWM).
				if (token[3] == 'T') {
					updateChannelProfile[i].mode = CHANNEL_MODE_TOGGLE; // TODO: Rename this to MODE_TOGGLE
				} else if (token[3] == 'W') {
					updateChannelProfile[i].mode = CHANNEL_MODE_WAVEFORM;
				} else if (token[3] == 'P') {
					updateChannelProfile[i].mode = CHANNEL_MODE_PULSE;
				} else if (token[3] == '-') {
					// NOTE: Don't change!
				}
				
				// Value. Set channel value. This depends on the direction and mode of the channel.
				if (updateChannelProfile[i].direction == CHANNEL_DIRECTION_OUTPUT) {
					if (updateChannelProfile[i].mode == CHANNEL_MODE_TOGGLE) {
						// Assign the channel's value based on the received data.
						if (token[4] == 'H') {
							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_ON;
						} else if (token[4] == 'L') {
							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
						} else {
							// ERROR: Error. An unrecognized toggle value was specified.
						}
					} else if (updateChannelProfile[i].mode == CHANNEL_MODE_WAVEFORM) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else if (updateChannelProfile[i].mode == CHANNEL_MODE_PULSE) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else {
						// ERROR: Error. An invalid mode was specified.
					}
				} else if (updateChannelProfile[i].direction == CHANNEL_DIRECTION_INPUT) {
					// NOTE: The channel direction is input, so its value is set by the pin's voltage state.
					if (updateChannelProfile[i].mode == CHANNEL_MODE_TOGGLE) {
						// Assign the channel value based on the physical pin state.
						updateChannelProfile[i].value = Get_Channel_Value (updateChannelProfile[i].number);
						
//						if (token[4] == 'H') {
//							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_ON;
//						} else if (token[4] == 'L') {
//							updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
//						} else {
//							// ERROR: Error. An unrecognized toggle value was specified.
//						}
					} else if (updateChannelProfile[i].mode == CHANNEL_MODE_WAVEFORM) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else if (updateChannelProfile[i].mode == CHANNEL_MODE_PULSE) {
						// TODO: Assign the value differently, depending on the specified channel direction and mode.
						// TODO: Assign this based on the received data.
					} else {
						// ERROR: Error. An invalid mode was specified.
					}
				} else {
					// ERROR: Error. An unrecognized channel direction was specified.
				}
				// TODO: Apply individual channel here! Only the changed ones!
				
//				// Set GPIO state
//				// TODO: Add an additional state to handle "no change" for channel
//				if (token[1] == 'T') {
//					Enable_Channel ((i + 1), TRUE);
//				} else {
//					Enable_Channel ((i + 1), FALSE);
//				}
//				
//				// Set channel direction. Is the channel an input or output?
//				if (token[2] == 'O') {
//					Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				} else if (token[2] == 'I') {
//					Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//				}
				
//				if (tokenInt == 1) {
//					Set_LED_Output ((RGB_LED) (i + 1),  &onColor);
//				} else {
//					Set_LED_Output ((RGB_LED) (i + 1),  &offColor);
//				}
			}
			
			// Apply channel
			// TODO: Move this to a common place, maybe in Application in the loop logic.
			Apply_Channels ();
			Apply_Channel_Lights ();
			
			result = TRUE;
		
		} else if (strncmp (token, "change", strlen ("change")) == 0) { 
			
			// change lights to 1 0 1 1 0 1 0 1 0 0 1 1
			// ^
			
			if ((status = getToken (behaviorContent, token, 1)) != NULL) {
			
				// change lights to 1 0 1 1 0 1 0 1 0 0 1 1
				//        ^
				if (strncmp (token, "channel", strlen ("channel")) == 0) {
					
					if ((status = getToken (behaviorContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						// change channel to 1 0 1 1 0 1 0 1 0 0 1 1 1 0 1 1 0 1 0 1 0 0 1 1
						//                   ^                       ^
						
						/*
						// Update the LED states
						// TODO: Update the intermediate data structure and only update the actual LEDs when the state changes.
						for (i = 0; i < 12; i++) {
							status = getToken (behaviorContent, token, 3 + i);
							tokenInt = atoi (token);
							if (tokenInt == 1) {
								Set_LED_Output ((RGB_LED) (i + 1),  &onColor);
							} else {
								Set_LED_Output ((RGB_LED) (i + 1),  &offColor);
							}
						}
						
						// Update the GPIO states
						// TODO: Update the intermediate data structure and only update the actual GPIO when the state changes.
						for (i = 0; i < 12; i++) {
							status = getToken (behaviorContent, token, 3 + 12 + i);
							tokenInt = atoi (token);
							if (tokenInt == 1) {
								// TODO: Make 0-indexing (or not) consident with LEDs
//								Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//								Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_ON);
								// Update channel
								updateChannelProfile[i].enabled = TRUE; // HACK
								updateChannelProfile[i].direction = OUTPUT_CHANNEL;
								updateChannelProfile[i].mode = MODE_DIGITAL;
								updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_ON;
								// TODO: Apply individual channel here! Only the changed ones!
							} else {
								// TODO: Make 0-indexing (or not) consident with LEDs
//								Set_Channel ((i + 1), OUTPUT_CHANNEL, NULL);
//								Set_Channel_State ((i + 1), CHANNEL_VALUE_TOGGLE_OFF);
								// Update channel
								updateChannelProfile[i].enabled = TRUE; // HACK
								updateChannelProfile[i].direction = OUTPUT_CHANNEL;
								updateChannelProfile[i].mode = MODE_DIGITAL;
								updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
								// TODO: Apply individual channel here! Only the changed ones!
							}
						}
						// Apply channel
						Apply_Channels ();
						
						// Update the wait
						// TODO: Add this as a separate behavior!
						status = getToken (behaviorContent, token, 3 + 24);
						tokenInt = atoi (token);
//						Wait (tokenInt);
						
						result = TRUE;
						
//						if (strncmp (token, "on", strlen ("on")) == 0) {
//							
//							// Turn all LEDs on
//							for (i = 0; i < 12; i++) {
//								Set_Channel_State (i, CHANNEL_VALUE_TOGGLE_ON);
//							}
//							
//							result = TRUE;
//							
//						} else if (strncmp (token, "off", strlen ("off")) == 0) {
//							
//							// Turn all LEDs off
//							for (i = 0; i < 12; i++) {
//								Set_Channel_State (i, CHANNEL_VALUE_TOGGLE_OFF);
//							}
//							
//							result = TRUE;
//							
//						}
						*/
					}
					
				}
			
			}
			
		} else if (strncmp (token, "turn", strlen ("turn")) == 0) { 
			
			if ((status = getToken (behaviorContent, token, 1)) != NULL) {
			
				// turn lights on
				//      ^
				if (strncmp (token, "lights", strlen ("lights")) == 0) {
					
					if ((status = getToken (behaviorContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						// turn lights on
						//             ^
						if (strncmp (token, "on", strlen ("on")) == 0) {
							
							// Turn all LEDs on
							for (i = 0; i < 12; i++) {
								Set_Channel_Value (i, CHANNEL_VALUE_TOGGLE_ON);
							}
							
							result = TRUE;
							
						} else if (strncmp (token, "off", strlen ("off")) == 0) {
							
							// Turn all LEDs off
							for (i = 0; i < 12; i++) {
								Set_Channel_Value (i, CHANNEL_VALUE_TOGGLE_OFF);
							}
							
							result = TRUE;
							
						}
					}
				
				// turn light 1 on
				//      ^
				} else if (strncmp (token, "light", strlen ("light")) == 0) {
					
					if ((status = getToken (behaviorContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						if ((status = getToken (behaviorContent, token, 3)) != NULL) {
							
							// turn light 1 on
							//              ^
							if (strncmp (token, "on", strlen ("on")) == 0) {
								
								// Turn the specified LED off
								status = getToken (behaviorContent, token, 2);
								tokenInt = atoi (token);
								Set_LED_Output ((RGB_LED) tokenInt,  &onColor);
								
								result = TRUE;
								
							} else if (strncmp (token, "off", strlen ("off")) == 0) {
								
								// Turn the specified LED off
								status = getToken (behaviorContent, token, 2);
								tokenInt = atoi (token);
								Set_LED_Output ((RGB_LED) tokenInt,  &offColor);
								
								result = TRUE;
								
							}
						}
					}
					
				// turn channel 1 on
				//      ^
				} else if (strncmp (token, "channel", strlen ("channel")) == 0) {
					
					if ((status = getToken (behaviorContent, token, 2)) != NULL) { // TODO: Remove this! The parameter is used later.
						
						// turn channel 1 on
						//              ^
						
						if ((status = getToken (behaviorContent, token, 3)) != NULL) {
							
							// turn channel 1 on
							//                ^
							if (strncmp (token, "on", strlen ("on")) == 0) {
								
								// Turn the specified LED off
								status = getToken (behaviorContent, token, 2);
								tokenInt = atoi (token);
								Set_Channel_Value (tokenInt, CHANNEL_VALUE_TOGGLE_ON);
								
								result = TRUE;
								
							} else if (strncmp (token, "off", strlen ("off")) == 0) {
								
								// Turn the specified LED off
								status = getToken (behaviorContent, token, 2);
								tokenInt = atoi (token);
								Set_Channel_Value (tokenInt, CHANNEL_VALUE_TOGGLE_OFF);
								
								result = TRUE;
								
							}
						}
					}
					
				}
				
			}
			
		} else if (strncmp (token, "wait", strlen ("wait")) == 0) {
			
			if ((status = getToken (behaviorContent, token, 1)) != NULL) {
				
				// wait 500 ms
				//      ^
					
				// Set the behavior wait time (i.e., the time after the behavior before proceeding to the next one)
				status = getToken (behaviorContent, token, 1); // TODO: This is redundant. Remove redundancy!
				tokenInt = atoi (token);
				if (behaviorWaitTime == 0) {
					behaviorWaitTime = tokenInt;
				}
				
				// Check if the behavior's wait time has expired
				if ((Millis () - behaviorStartTime) > behaviorWaitTime) {
					behaviorStartTime = 0;
					behaviorWaitTime = 0;
					result = TRUE;
				} else {
					result = FALSE;
				}
				
			}
			
		} else if (strncmp (token, "say", strlen ("say")) == 0) {
			
			if ((status = getToken (behaviorContent, token, 1)) != NULL) {
				
				// wait 500 ms
				//      ^
					
				// Set the behavior wait time (i.e., the time after the behavior before proceeding to the next one)
				status = getToken (behaviorContent, token, 1);
				
				// TODO: Create string "say token"
				
				// TODO: Add parameter for "say" to specify maximum frequency of phrase
				// TODO: Add parameters for alternative phrases
				//Broadcast_UDP_Message ("say i should say something");
				Broadcast_UDP_Message (behaviorContent, 4445);
				// TODO: Queue_Outgoing_Message()
				
				result = TRUE;
				
			}
			
			// TODO: Add commands that render a graphical finger using Clay on your behalf, in response to commands, as if the computer is doing it! The computer can also point things out to you! It mirrors your behavior? Or shows up as "slip" under a behavior?
			// TODO: "touch at <x,y>"
			// TOOD: "drag to <x,y>"
			
		} else {
			
			result = TRUE;
			
		}
		
	} else {
		
		result = TRUE;
	}
	
	return result;
}
