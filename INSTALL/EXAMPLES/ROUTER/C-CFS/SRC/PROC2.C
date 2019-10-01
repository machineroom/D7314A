#include <misc.h>
#include <channel.h>

#define bus_width 8

int main( void )
{
  Channel **in_chan = get_param(1) ;
  Channel **out_chan = get_param(2) ;
  int i ;

  for ( i = 0 ; i < bus_width ; i++ )
  {
    char ch = ChanInChar( in_chan[i] );

    ChanOutChar( out_chan[i], (char) i );

    if ( ((int) ch) != i )
      __asm { seterr; }
  }
}
