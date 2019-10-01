/***************************************
*
*  Debugger example:  abort.c
*
*  Example of forcing a C program to HALT the
*  processor for post-mortem analysis regardless
*  of the error mode it has been configured in.
*
*  Use of the debug support functions is encouraged
*  as an alternative (see debugger example file debug.c
*  for further details).
*
***************************************/


#include <stdio.h>
#include <stdlib.h>
#include <misc.h>
#include <assert.h>


int
main (void)

{
	/*  0 will cause assert () to fail assertion test  */
	int	x = 0;

	printf ("Program started\n");

	/*  override normal abort action  */
	set_abort_action (ABORT_HALT);

	printf ("Program being halted by assert ()\n");
	assert (x);

	printf ("Program being halted by abort ()\n");
	abort ();

	exit (EXIT_SUCCESS);
}
