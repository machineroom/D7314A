/***************************************
*
*  Debugger example:  master.c (forms cpair)
*
*  Forms one of two parallel C processes
*  on different processors (see cpair.cfs).
*
*
*  Note: because this function talks to the
*        host via the C library FILE I/O system
*        it must use the stdio.h header file and
*        be linked in full library mode.
*
***************************************/


#include <stdio.h>
#include <stdlib.h>
#include <misc.h>
#include <channel.h>

 
int
main (int argc, char* argv[])

{
	Channel*	from_mult;
	Channel*	to_mult;
	int		i;

	/*  params 1 and 2 used by stdio  */
	from_mult = (Channel *) get_param (3);
	to_mult   = (Channel *) get_param (4);

	for (i = 0; i < 5; ++i)   {
		int	val;

		printf ("Sending: %2d  -  ", i);

		/*******************
		*  flush stdout in case we set a breakpoint
		*  before the following printf ()
		*******************/
		fflush (stdout);

		ChanOutInt (to_mult, i);

		val = ChanInInt (from_mult);
		printf ("Received: %2d\n", val);
	}

	/*  inform multiplier that we have finished  */
	ChanOutInt (to_mult, -1);

	exit_terminate (EXIT_SUCCESS);
}
