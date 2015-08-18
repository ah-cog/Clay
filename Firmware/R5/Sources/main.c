/* ###################################################################
**     Filename    : main.c
**     Project     : clay_demo_serial1_console
**     Processor   : MK20DX256VLL7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-08-16, 18:35, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CsIO1.h"
#include "IO1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int value;
  int i;
  int flag;
  char buffer[64] = { 0 };
  int ch = (int) 'a';

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  for (;;) {
	  printf ("Clay\r\n");
	  
	  /*
	  printf ("What's your name?\r\n");
	  printf ("> ");
	  scanf  ("%s", buffer);
	  printf ("Hey %s.\r\n", buffer);
	  
	  printf ("How many Clay do you want?\r\n");
	  printf ("> ");
	  scanf  ("%i", &value);
	  printf ("I'm on it. You'll soon have %i bits of Clay.\r\n", value);
	  */
	  
//	  printf ("Continue? (y/n)\r\n");
//	  while (buffer[0] != 'n') {
//		  fgets (buffer, sizeof (buffer), stdin);
//		  printf ("%s", buffer);
//	  }
	  
	  /*
	  // Simple real-time I/O
	  do {
		  ch = getchar (); // ch = getc (stdin);
		  putchar (ch); // printf ("%c", ch);
		  fflush (stdin);
		  fflush (stdout);
	  } while (ch != '.'); // Read characters until the '.' character is entered. This could be replaced with '\n' or another character, or a different condition.
	  */
	  
	  /*
	  // Read a line into a buffer (until "\r\n" is received)
	  i = 0;
	  do {
		  buffer[i] = getchar ();
		  putchar (buffer[i]);
		  if (buffer[i] == '\r') { printf ("<return>"); }
		  if (buffer[i] == '\n') { printf ("<newline>"); }
		  i++;
		  fflush (stdin);
		  fflush (stdout);
	  } while (i > 1 ? !(buffer[i - 1] == '\r' && buffer[i] == '\n') : TRUE); // Read characters until the '.' character is entered. This could be replaced with '\n' or another character, or a different condition.
	  */
	  
	  // "REPL" framework
	  for (;;) {
		  i = 0;
		  flag = 0;
		  ch = (int) 0;
		  printf (">");
		  do {
			  ch = getchar (); // ch = getc (stdin);
			  buffer[i++] = ch; // Append the character to the buffer.
			  putchar (ch); // Echo the character.
			  if (ch == '\n') { /* printf ("<newline>"); */ flag = 1; } // Show when a newline character is entered.
		  } while (flag == 0);
		  buffer[i] = '\0'; // Terminate the string
		  printf ("%s", buffer);
	  }
	  
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
