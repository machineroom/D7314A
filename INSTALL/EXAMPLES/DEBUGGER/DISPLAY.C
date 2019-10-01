/***************************************
*
*  Debugger example:  display.c
*
*  Example of how the debugger displays objects
*  (as shown in the debugger chapter).
*
*  Run the program to stop at debug_stop ()
*  and start inspecting !
*
***************************************/


#include <stdlib.h>
#include <misc.h>


int
main (void)

{
	enum colour { red = 1 };  
	struct Many   {
		int	a;
		double	b; 
	};

	enum colour	shoe = red; 
	struct Many	many = { -42, 2.0 };        

	int	answer   = 42;
	char	key      = 'A';
	char	string[] = "bye";
	char*	ptr      = string;
	short	iarray[] = { 1, 2, 3, 4 }; 


	/*  run the program to stop here  */
	debug_stop ();

	exit (EXIT_SUCCESS);
}
