/*
 *  This example function is about as simple as possible; it does not
 *  require any static, heap or i/o.  Hence it needs no harness, but
 *  the descriptor pragma is, as always, necessary.
 */


#pragma IMS_off(stack_checking)

int add3( int );
#pragma IMS_descriptor( add3, ansi_c, 0, 0, "" )


int add3( int i )
{
  return( i + 3 );
}
