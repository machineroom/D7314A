/*
 *  This file contains the third stage of the dynamic loading of a C
 *  function which requires static, heap and i/o.
 */


#pragma IMS_off(stack_checking)


#include <stdio.h>

int hello_world( void )
{
  printf( "Hello world from child C.\n" );
  printf( "Goodbye world from child C.\n" );

  return 0;
}
