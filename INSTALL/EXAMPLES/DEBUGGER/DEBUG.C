/***************************************
*
*  Debugger example:  debug.c
*
*  Example of debug support functions when used with
*  and without the debugger.
*  (see also debugger example file abort.c)
*
***************************************/


#include <stdio.h>
#include <stdlib.h>
#include <misc.h>


int
main (void)

{
	/*  0 will cause debug_assert () to fail assertion test  */
	int	x = 0;

	printf ("Program started\n");

	debug_message ("A debug message only within the debugger");

	printf ("Program being halted by debug_assert ()\n");
	debug_assert (x);

	printf ("Program being halted by debug_stop ()\n");
	debug_stop ();

	exit (EXIT_SUCCESS);
}
