#include <misc.h>
#include <channel.h>

int main()
{
  Channel *from_master;
  Channel *to_master;
  int *multiplier;
  int foo;

  multiplier  =     (int *)get_param(1);
  from_master = (Channel *)get_param(2);
  to_master   = (Channel *)get_param(3);
 
  foo = ChanInInt(from_master);

  while (foo >= 0)   
  {
    foo = foo * (*multiplier);

    ChanOutInt(to_master, foo);

    foo = ChanInInt(from_master);
  }
}
