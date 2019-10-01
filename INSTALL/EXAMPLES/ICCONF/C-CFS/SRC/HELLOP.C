/*{{{  include files */
#include <stdio.h>
#include <stdlib.h>

#include <misc.h>
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (void)
{
    int Count = (int) *((long int *) get_param(3));

    while (Count-- > 0)
        printf("Hello world from C\n");

    exit(EXIT_SUCCESS);
}
/*}}}*/
/*}}}*/
