/* (c) Copyright INMOS Limited  1992. */

#include <stdlib.h>

extern void hellosep (void);
extern void worldsep (void);

int main (void)
{
  hellosep ();
  worldsep ();
  return (EXIT_SUCCESS);
}

