/***************************************
*
*  Debugger example:  stack.c
*
*  An example of overflowing the stack and
*  using the debugger to locate.
*
*  Must be compiled with stack checking enabled.

*  We use a #pragma to force stack checking to be enabled
*  from the source code rather than by compiler options.
*
***************************************/


#include <stdlib.h>


#pragma IMS_on (stack_checking)		/*  force stack checking  */


void
foo (int a)

{
	foo (a);
}


int
main (void)

{
	foo (42);

	exit (EXIT_SUCCESS);
}
