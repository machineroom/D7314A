/***************************************
*
*  Debugger example:  free.c
*
*  Cause a run time error by freeing a pointer not
*  allocated via malloc, calloc or realloc.
*
*  Also note that the debugger detects that ptr is
*  not word-aligned when ptr is inspected.
*
*  Debugger will locate to free (ptr) function call.
*
***************************************/


#include <stdlib.h>


int
main (void)

{
	
	/*  a random(ish) value other than NULL  */
	int*	ptr = (void *) 41;

	free (ptr);

	exit (EXIT_SUCCESS);
}
