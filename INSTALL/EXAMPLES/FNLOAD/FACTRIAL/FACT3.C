/*
 *  Third stage of example which returns value through the
 *  parameter list as well as via function result.
 */


/* ensure that stack checking is switched on */
#pragma IMS_on( stack_checking )


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <process.h>
#include <limits.h>

#define DIM(array) ( sizeof( (array) ) / sizeof( (array)[0] ) )
#define BACKSPACE '\x08' /* ASCII BS */
#define DELAY  (CLOCKS_PER_SEC / 6)


static void spin(void)
{
  static unsigned int i = 0;
  char spokes[] = { '|', '/', '-', '\\' };

  printf( "%c%c", BACKSPACE, spokes[ i % DIM(spokes) ] );
  fflush( stdout );
  i++;
  ProcWait((int)DELAY);
}


int factorial( unsigned int number,
               unsigned long int* ptr_to_answer )
/*
   Purpose:   To calculate the factorial of a number.
   Returned:  Whether the calculation was successful or not:
              EXIT_SUCCESS for success; EXIT_FAILURE for failure
   In:        number - the non-negative number to calculate the
              factorial of
   Out:       *ptr_to_answer - the factorial of 'number' (number!)
              if the operation was successful; undefined otherwise
   Notes:     Failure will be returned if the factorial calculation
              would cause overflow.
*/
{
  int result = EXIT_SUCCESS;
  int i;

  for ( i = 0; i < number; i++ )
    putchar( '.' );
  putchar( ' ' );
  spin();
  if (number == 0)
    *ptr_to_answer = 1;
  else
    {
      unsigned long int fact;

      fact = number;
      while (number > 1)
        {
          spin();
          number--;
          if ( fact <= (ULONG_MAX / number) )
            fact = fact * number;
          else
            {
              result = EXIT_FAILURE;
              break;
            }
        }
      *ptr_to_answer = fact;
    }
  printf( "\n" );
  return result;
}
