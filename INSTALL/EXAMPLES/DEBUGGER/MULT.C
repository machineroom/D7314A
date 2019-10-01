/***************************************
*
*  Debugger example:  mult.c (forms cpair)
*
*  Forms one of two parallel C processes
*  on different processors (see cpair.cfs).
*
*  Note: because master.c is linked in full
*        library mode this function must use
*        the reduced stdiored.h header file
*        and be linked in reduced library mode.
*
***************************************/


#include <stdiored.h>
#include <stdlib.h>
#include <misc.h>
#include <channel.h>


int
main (int argc, char* argv[])

{
	Channel*	from_master;
	Channel*	to_master;
	int*		multiplier;
	int		foo;

	/*  these match the order in cpair.cfs  */
	from_master = (Channel *) get_param (1);
	to_master   = (Channel *) get_param (2);
	multiplier  =     (int *) get_param (3);
 
	foo = ChanInInt (from_master);

	while (foo >= 0)   {
		foo = foo * (*multiplier);

		ChanOutInt (to_master, foo);

		foo = ChanInInt (from_master);
	}

	exit (EXIT_SUCCESS);
}
