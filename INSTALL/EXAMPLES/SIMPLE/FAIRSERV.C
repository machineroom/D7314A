/* (c) Copyright INMOS Limited  1992. */

/* This program starts two processes, each of which writes a word of */
/* a message. The first one synchronises with the second after it    */
/* printed its word. The message is converted to upper case by a     */
/* server.                                                           */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <channel.h>

static char buffer[100];
static int lenbuf;

static void serve (int i, Channel * ins[], Channel * outs[])
{
  char data;
  
  buffer[lenbuf] = '0'+i;
  lenbuf += 1;
  /* read and convert data */
  data = ChanInChar (ins[i]);
  if (islower(data)) data = toupper(data);

  /* output it along corresponding channel */
  ChanOutChar (outs[i], data);
  return;
}

/* The server is defined */
void upserve (Process * p, Channel * ins[], Channel * outs[])
{
  size_t n;
  int k, i;

  p = p;
  /* Find the size of the array of channels */
  for (n = 0; ins[n] != NULL; ++n)
    ;
  /* Loop forever, this process never terminates */
  while (n > 0)
  {
    /* wait for an input */
    k = ProcAltList (ins);

    /* handle the request */
    serve (k, ins, outs);
    k += 1;

    /* search remainder of the array until none to do */
    while ((i = ProcSkipAltList (&(ins[k]))) >= 0)
    {
      serve (i+k, ins, outs);
      k += i+1;
    }
  }
  return;
}

/* The first word */
void hello_proc (Process * p, Channel * c, Channel * ask, Channel * reply)
{
  char word[] = "Hello, ";
  size_t i;
  
  p = p;
  for (i = 0; i < strlen(word); ++i)
  {
    ChanOutChar (ask, word[i]);
    word[i] = ChanInChar (reply);
  }
  printf ("%s", word);
  ChanOutInt (c, 1);     /* tell the second part to go */
  return;
}

/* The second word */
void world_proc (Process * p, Channel * c, Channel * ask, Channel * reply)
{
  char word[] = "world\n";
  int k;
  size_t i;
  
  p = p;
  for (i = 0; i < strlen(word); ++i)
  {
    ChanOutChar (ask, word[i]);
    word[i] = ChanInChar (reply);
  }
  k = ChanInInt (c);
  printf ("%s", word);
  return;
}

int main (void)
{
  /* Specify the server and its channels */
  Process * server;
  Channel * ask[3], * reply[3];
  size_t k;
  
  /* Specify the worker processes */
  Process * hello, * world;
  Channel * sync;

  /* Initialise the server channels */
  for (k = 0; k <= 1; ++k)
  {
    ask[k] = ChanAlloc ();
    reply[k] = ChanAlloc ();
  }
  ask[2] = reply[2] = NULL;

  /* Start up the server */
  server = ProcAlloc (upserve, 0, 2, ask, reply);
  if (server == NULL)
  {
    printf ("Could not establish server\n");
    exit (EXIT_FAILURE);
  }
  ProcRun (server);
  
  /* Set up the communication channel between workers */
  sync = ChanAlloc ();

  /* Set up the new processes */
  hello = ProcAlloc (hello_proc, 0, 3, sync, ask[0], reply[0]);
  world = ProcAlloc (world_proc, 0, 3, sync, ask[1], reply[1]);
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

  printf ("%s", buffer);

  exit (EXIT_SUCCESS);
}
