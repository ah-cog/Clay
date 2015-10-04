#ifndef MESSENGER_H
#define MESSENGER_H

#ifndef __PE_Types_H
#include "PE_Types.h"
#endif

#include <stdio.h>
#include <string.h>

#include "Utilities/String.h"

#include "Timer_1ms.h"
#include "GPIO.h"
#include "Drivers/PCA9552.h"

int8_t Process_Message (const char *message);

#endif /* MESSENGER_H */
