#include "Behavior.h"

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

uint8_t Initialize_Loop () {
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

Behavior* Remove_Behavior (Behavior *behavior) {
	
	Behavior_Construct *behaviorConstruct = NULL;
	
	// Get the behavior construct associated with the specified behavior.
	if (behavior != NULL && (*behavior).uuid != NULL) {
		behaviorConstruct = Get_Behavior_Construct_By_UUID ((*behavior).uuid);
	}
	
	if (loop != NULL) {
		
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
			
			// Free the behavior construct from memory.
			// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
			Delete_Behavior_Construct (behaviorConstruct);
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next != NULL) {
			
			// The behavior is within the loop. It has previous and next behaviors.
			
			(*(*behaviorConstruct).previous).next = (*behaviorConstruct).next; // Update the previous behavior to skip this behavior and point to the next behavior.
			
			(*(*behaviorConstruct).next).previous = (*behaviorConstruct).previous; // Update the next behavior skip this behavior and point to the previous behavior.
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
			// Free the behavior construct from memory.
			// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
			Delete_Behavior_Construct (behaviorConstruct);
			
		} else if ((*behaviorConstruct).previous != NULL && (*behaviorConstruct).next == NULL) {
			
			// The behavior is the last in the loop. It has previous behaviors only.
			
			(*(*behaviorConstruct).previous).next = NULL; // Update the previous behavior be the new last behavior in the loop. That is, make it point to no other behavior (and point to NULL).
			
			// TODO: Check the state of the loop pointer, and update it if it points to the behavior being removed!
			
			// Unlink the behavior from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
			// Free the behavior construct from memory.
			// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
			Delete_Behavior_Construct (behaviorConstruct);
			
		} else {
			
			// There are no more behaviors in the loop, so remove all links and reset the loop to its "empty" state.
			
			loop = NULL; // Remove the link to any behaviors at the front of the loop.
			
			currentBehaviorConstruct = NULL; // Reset the current behavior to NULL, so no behavior will be performed.
			
			// Unlink the behaviors from linked list to finish dequeuing process.
			(*behaviorConstruct).previous = NULL;
			(*behaviorConstruct).next = NULL;
			
			// Free the behavior construct from memory.
			// TODO: Consider keeping it in a temporary cache for a short amount of time in case it is being reused. This might not be worth it!
			Delete_Behavior_Construct (behaviorConstruct);
			
		}
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
	
//	D(printf("messageContent = %s\r\n", messageContent));
	
	// TODO: Decompose the behavior into atomic behaviors and perform them!
	
	// turn light 1 on
	// ^
	if ((status = getToken (behaviorContent, token, 0)) != NULL) { // status = getToken (message, token, 0);

		if (strncmp (token, "turn", strlen ("turn")) == 0) {
			
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
								Set_Channel_State (i, ON_CHANNEL);
							}
							
							result = TRUE;
							
						} else if (strncmp (token, "off", strlen ("off")) == 0) {
							
							// Turn all LEDs off
							for (i = 0; i < 12; i++) {
								Set_Channel_State (i, OFF_CHANNEL);
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
								Set_Channel_State (tokenInt, ON_CHANNEL);
								
								result = TRUE;
								
							} else if (strncmp (token, "off", strlen ("off")) == 0) {
								
								// Turn the specified LED off
								status = getToken (behaviorContent, token, 2);
								tokenInt = atoi (token);
								Set_Channel_State (tokenInt, OFF_CHANNEL);
								
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
				Broadcast_UDP_Message ("say hey", 4445);
				
				result = TRUE;
				
			}
			
			// TODO: Add commands that render a graphical finger using Clay on your behalf, in response to commands, as if the computer is doing it! The computer can also point things out to you! It mirrors your behavior? Or shows up as "slip" under a behavior?
			// TODO: "touch at <x,y>"
			// TOOD: "drag to <x,y>"
			
		} else if (strncmp (token, "ping", strlen ("ping")) == 0) {
			
			if ((status = getToken (behaviorContent, token, 1)) != NULL) {
			
				// turn lights on
				//      ^
				if (strncmp (token, "lights", strlen ("lights")) == 0) {
				
					// Queue_Outgoing_Message ("pong <ip>"); // TODO: Send this via UDP datagram.
					// Send_UDP_Message()
//					printf("got ping\r\n");
					Broadcast_UDP_Message ("pong <ip>");
					
					result = TRUE;
					
				}
				
			}
			
		} else {
//			D(printf ("WTFping\r\n"));
		}
		
	} else {
//		D(printf ("status = %d\r\n", status));
	}
	
	return result;
}
