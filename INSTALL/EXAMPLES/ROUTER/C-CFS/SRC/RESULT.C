#include <misc.h>
#include <channel.h>

#define bus_width 8

int main( void )
{
  Channel *in_chan = get_param(1) ;
  Channel *out_chan = get_param(2) ;
  Channel *cntl_chan = get_param(3) ;

  ChanInChar( in_chan );
  ChanInChar( cntl_chan );
  ChanOutChar( out_chan, (char) 0 );
}
