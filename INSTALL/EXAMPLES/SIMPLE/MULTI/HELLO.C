/* (c) Copyright INMOS Limited  1992. */

#include <stdio.h>
#include <channel.h>
#include <misc.h>

/* This program is loaded onto the root processor of a two-proc network */
/* It puts out the first word of a message, acquires the second         */
/* word from a channel, and then prints it.                             */

int main()
  {
    int i;
    Channel * in_chan;                    /* channel to get second word from */
    char buffer[101];                     /* buffer to hold second word */

    in_chan = (Channel *) get_param (3);  /* get the actual channel */
    printf("\nHello ");                   /* first word output */

    for (i = 0; i < 100; ++i)
    {
      buffer[i] = ChanInChar (in_chan);
      if (buffer[i] == '\0')
        break;
    }
    printf ("%s\n", buffer);
  }

