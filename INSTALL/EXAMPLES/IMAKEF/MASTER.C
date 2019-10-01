#include <stdio.h>
#include <misc.h>
#include <channel.h>
#include <stdlib.h>

int main()
{
  Channel *from_mult;
  Channel *to_mult;
  int i;

  from_mult = (Channel *)get_param(3);
  to_mult   = (Channel *)get_param(4);

  for (i = 1; i < 20; ++i)   
  {
    int val;

    printf("Sending %d\n", i);
    ChanOutInt(to_mult, i);

    val = ChanInInt(from_mult);
    printf("Received %d\n", val);
  }

  ChanOutInt(to_mult, -1);    

  exit(EXIT_SUCCESS);
}
