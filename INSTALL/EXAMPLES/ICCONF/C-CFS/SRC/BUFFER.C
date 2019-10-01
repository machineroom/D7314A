/*{{{  include files */
#include <stdlib.h>

#include <misc.h>
#include <channel.h>
/*}}}*/

/*{{{  static procedures */
/*{{{  ChanInInt32 */
static long int ChanInInt32 (Channel *Input)
{
    long int Value = 0;

    ChanIn(Input, &Value, sizeof(Value));

    return(Value);
}
/*}}}*/

/*{{{  ChanOutInt32 */
static void ChanOutInt32 (Channel *Output, long int Value)
{
    ChanOut(Output, &Value, sizeof(Value));
}
/*}}}*/
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    Channel *Input = get_param(1);
    Channel *Output = get_param(2);

    while (1)
        ChanOutInt32(Output, ChanInInt32(Input));
}
/*}}}*/
/*}}}*/
