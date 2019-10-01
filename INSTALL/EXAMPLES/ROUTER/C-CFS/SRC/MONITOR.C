#include <misc.h>
#include <stdlib.h>
#include <channel.h>

int main( void )
{
  Channel **res_chan = get_param(3) ;
  Channel **cntl_chan = get_param(4) ;

  ChanInChar( res_chan[0] );
  ChanInChar( res_chan[1] );
  ChanOutChar( cntl_chan[0], (char) 0 );
  ChanOutChar( cntl_chan[1], (char) 0 );
  ChanOutChar( cntl_chan[2], (char) 0 );
  ChanOutChar( cntl_chan[3], (char) 0 );

  exit(EXIT_SUCCESS);
}
