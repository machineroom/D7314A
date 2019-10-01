/*
 *  Third stage of example of overflowing the stack and
 *  having this reported by the runtime library.
 */


/* ensure that stack checking is switched on */
#pragma IMS_on( stack_checking )


#include <stdio.h>
#include <misc.h>

void foo( int a )
{
  char stack_eating_array[ 128 ];

  stack_eating_array[4] = 's';
  printf( "max_stack_usage() gives %ld bytes\n", max_stack_usage() );
  foo (a);
}


int stack_overflow( void )
{
  printf( "stack_overflow: started\n" );

  foo (42);

  printf( "stack_overflow: finished\n" );
  return 0;
}
