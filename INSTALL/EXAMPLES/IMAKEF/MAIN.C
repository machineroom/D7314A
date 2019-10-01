#include <stdlib.h>
#include <process.h>

extern void hello(Process *p1);

extern void world(Process *p2);

int main()
{
  Process *p1, *p2;
 
  p1 = ProcAlloc(hello, 0, 0);
  if (p1 == NULL) 
    abort();

  p2 = ProcAlloc(world, 0, 0);
  if (p2 == NULL) 
    abort();
 
  ProcPar(p1, p2, NULL);
}

