/* (c) Copyright INMOS Limited  1992. */

/* This program starts two processes, each of which */
/* writes a message. The processes are started twice, */
/* the second time swapping places in the parameter */
/* list of ProcPar. However, the order of the results */
/* to stdout is undefined.*/

#include <stdio.h>
#include <stdlib.h>
#include <process.h>

/* The first word */
void hello_proc (Process * p)
{
  p = p;
  printf ("Hello ");
  return;
}

/* The second word */
void world_proc (Process * p)
{
  p = p;
  printf ("world\n");
  return;
}

int main (void)
{
  Process * hello, * world;

  /* Set up the new processes */
  hello = ProcAlloc (hello_proc, 0, 0);
  world = ProcAlloc (world_proc, 0, 0);
  if ((hello == NULL) || (world == NULL))
  {
    printf ("Could not allocate process(es).\n");
    exit (EXIT_FAILURE);
  }

  /* Execute them both */
  ProcPar (hello, world, NULL);

  /* Try executing them in a different order in the list */
  ProcPar (world, hello, NULL);
  
  /* Clean up all the space it used */
  ProcAllocClean (hello);
  ProcAllocClean (world);

  exit (EXIT_SUCCESS);
}
