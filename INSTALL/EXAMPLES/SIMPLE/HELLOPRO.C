/* (c) Copyright INMOS Limited  1992. */

/* This program starts a process to put out a simple message to stdout */

#include <stdio.h>
#include <stdlib.h>
#include <process.h>

/* The process is declared as a function */
void hello_proc (Process * p)
{
  p = p;
  printf ("Hello, world.\n");
  return;
}

int main (void)
{
  Process * hello;

  /* Set up the new process */
  hello = ProcAlloc (hello_proc, 0, 0);
  if (hello == NULL)
  {
    printf ("Could not allocate process.\n");
    exit (EXIT_FAILURE);
  }

  /* Start it running */
  ProcRun (hello);
  
  /* Wait for the processes to join up again */
  ProcJoin (hello, NULL);

  /* Clean up all the space it used */
  ProcAllocClean (hello);

  exit (EXIT_SUCCESS);
}
