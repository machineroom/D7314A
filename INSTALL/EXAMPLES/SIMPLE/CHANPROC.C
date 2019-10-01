/* (c) Copyright INMOS Limited  1992. */

/* This program starts two processes, each of which writes a word of */
/* a message. The first one synchronises with the second after it    */
/* printed its word.                                                 */

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <channel.h>

/* The first word */
void hello_proc (Process * p, Channel * c)
{
  p = p;
  printf ("Hello ");
  ChanOutInt (c, 1);     /* tell the second part to go */
  return;
}

/* The second word */
void world_proc (Process * p, Channel * c)
{
  int k;
  
  p = p;
  k = ChanInInt (c);
  printf ("world\n");
  return;
}

int main (void)
{
  Process * hello, * world;
  Channel * sync;

  /* Set up the communication channel */
  sync = ChanAlloc ();

  /* Set up the new processes */
  hello = ProcAlloc (hello_proc, 0, 1, sync);
  world = ProcAlloc (world_proc, 0, 1, sync);
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
