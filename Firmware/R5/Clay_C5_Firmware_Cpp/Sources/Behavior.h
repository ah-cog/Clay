#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities/Debug.h"
#include "Utilities/String.h"

#include "Timer_1ms.h"
//#include "Clock.h"
#include "GPIO.h"
#include "Drivers/PCA9552.h"

#ifndef DEFAULT_UUID_LENGTH
#define DEFAULT_UUID_LENGTH 37
#endif

#define BEHAVIOR_UUID_LENGTH DEFAULT_UUID_LENGTH // i.e., 36 bytes plus one more for NULL terminating character.

// TODO: Define behavior performance speed (in Hz)

typedef struct Behavior {
	char *uuid;
	char *content; // TODO: Update this to point to the behavior's structure.
	
	// TODO: Loop *loop; -OR- Behavior_Sequence loop;
} Behavior;

Behavior* Create_Behavior (const char *uuid, const char *content); // TODO: Add by UUID (for streaming in) or atomic behavior
int8_t Delete_Behavior (Behavior *behavior);

/**
 * The behavior construct points to a behavior and provides a linked list 
 * mechanism for the behavior repository and loops.
 */
typedef struct Behavior_Construct {
	// TODO: char *uuid; // The UUID of the behavior construct.
	char *behaviorUuid; // The UUID of the behavior.
	Behavior *behavior; // The pointer to the behavior (if it's present in memory) or NULL (if it's not present in memory).
	
	struct Behavior_Construct *previous;
	struct Behavior_Construct *next;
} Behavior_Construct;

Behavior_Construct* Create_Behavior_Construct (const char *behaviorUuid, const Behavior *behavior);
int8_t Delete_Behavior_Construct (Behavior_Construct *behaviorConstruct);

// Behavior Cache
// The local behavior cache.

extern Behavior_Construct* behaviorCache;

uint8_t Reset_Unit ();

uint8_t Initialize_Behavior_Cache ();
int16_t Cache_Behavior (Behavior *behavior);
Behavior* Get_Cached_Behavior_By_UUID (char *behaviorUuid);
Behavior_Construct* Get_Cached_Behavior_Construct_By_UUID (char *behaviorUuid);
uint8_t Has_Cached_Behaviors ();
uint8_t Has_Cached_Behavior_By_UUID (char *uuid);
Behavior* Remove_Behavior_From_Cache (Behavior *behavior);

extern Behavior_Construct* loop; // TODO: Create a separate Loop data structure.
extern Behavior_Construct* currentBehaviorConstruct; // Pointer to the loop's current behavior.

uint8_t Initialize_Behavior ();

int16_t Add_Behavior (Behavior *behavior); // TODO: int16_t Add_Behavior (Behavior *loop, Behavior *behavior);
int16_t Add_Before_Behavior (Behavior *behavior, Behavior *otherBehavior);
Behavior* Remove_Behavior (Behavior *behavior); // TODO: Behavior* Remove_Behavior (Behavior *loop, Behavior *behavior);
uint8_t Has_Behaviors ();
uint8_t Has_Behavior_By_UUID (char *behaviorUuid);
Behavior_Construct* Get_Behavior_Construct_By_UUID (char *behaviorUuid);
Behavior* Get_Behavior_By_UUID (char *behaviorUuid);

int8_t Perform_Behavior (Behavior *behavior);

// Unit

void Reset_Behavior ();

#endif /* BEHAVIOR_H_ */
