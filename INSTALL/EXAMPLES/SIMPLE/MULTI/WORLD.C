/* (c) Copyright INMOS Limited  1992. */

#include <string.h>
#include <channel.h>
#include <misc.h>

/* This program is loaded onto a second node and merely transfers a */
/* single word to another process for printing.                     */

int main()
  {
    int i;
    Channel * out_chan;                   /* channel for output */
    static char * word = "World";
    
    out_chan = (Channel *) get_param (1); /* get the actual channel */
    for (i = 0; i <= strlen(word); ++i)
    {
      ChanOutChar (out_chan, word[i]);
    }
  }

