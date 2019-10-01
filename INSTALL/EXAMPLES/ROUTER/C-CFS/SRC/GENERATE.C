#include <misc.h>
#include <channel.h>

int main( void )
{
  Channel **out_chan = get_param(1) ;

  ChanOutChar( out_chan[0], (char) 0 );
  ChanOutChar( out_chan[1], (char) 1 );
}
