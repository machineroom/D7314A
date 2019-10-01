/*{{{  module header */
/*
-- ----------------------------------------------------------------------------
--
--     SCCS ID : @(#)  driver.c 1.1 91/06/26 13:42:25
--
--     Object Name : driver.c
--     Revision    : 1.1
--
--     (c) Copyright INMOS Limited.
--     All Rights Reserved.
--
--     DESCRIPTION
--         Main entry point for the INMOS driver program.
--
--     NOTES
--         None.
--
--     HISTORY
--         1-May-1990    Antony King    Created file.
--
-- ----------------------------------------------------------------------------
*/

static char SccsId[] = "@(#)  driver.c 1.1 91/06/26 13:42:25 Copyright INMOS Limited";
/*}}}*/

/*{{{  include files */
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <string.h>

#ifdef MSDOS
#include <process.h>
#endif

#ifdef VMS
#include <processes.h>
#endif
/*}}}*/

/*{{{  macro definitions */
#ifdef MSDOS
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if (_MSC_VER >= 700)
#define EXEC _execvpe
#else
#define EXEC execvpe
#endif
#endif

#ifdef VMS
#define EXIT_SUCCESS 1
#define EXIT_FAILURE 42

#define EXEC execve
#endif

#define SERVER_DEF "iserver"
#define SERVER_ENV "ISERVER"

#define SA "/sa"
#define SB "/sb"
#define SC "/sc"
#define SE "/se"
#define SI "/si"
#define SL "/sl"
#define SP "/sp"
#define SR "/sr"
#define SS "/ss"

#define EXTENSION ".btl"

#define IDUMP  "idump.btl"
#define IPROF  "iprof.btl"
#define IDEBUG "idebug.btl"
/*}}}*/

/*{{{  global procedures */
/*{{{  main */
int main (int Argc, char **Argv, char **Envp)
{
    int NewArgc = 0;
    char *NewArgv[100], *Server = NULL, *DriverName = *Argv;

    /*{{{  set up server arguments */
    if ((Server = getenv(SERVER_ENV)) == NULL)
        Server = SERVER_DEF;
    
    /*{{{  convert driver file name */
    while (*DriverName != '\0')
    {
        /*{{{   */
        if (isupper(*DriverName))
            *DriverName = (char) tolower(*DriverName);
        else if (*DriverName == '/')
            *DriverName = '\\';
        
        DriverName++;
        /*}}}*/
    }
    
    (void) strcpy(strrchr(*Argv, '.'), EXTENSION);
    /*}}}*/
    
    NewArgv[NewArgc++] = Server;
    
    if (strstr(*Argv, IDEBUG) == NULL)
    {
        /*{{{   */
        if ((strstr(*Argv, IDUMP) == NULL) && (strstr(*Argv, IPROF) == NULL))
        {
            /*{{{   */
            NewArgv[NewArgc++] = SE;
            NewArgv[NewArgc++] = SR;
            /*}}}*/
        }
        else
            NewArgv[NewArgc++] = SA;
        /*}}}*/
    }
    else
    {
        /*{{{   */
        if (Argc == 1)
        {
            /*{{{   */
            NewArgv[NewArgc++] = SE;
            NewArgv[NewArgc++] = SR;
            /*}}}*/
        }
        /*}}}*/
    }
    NewArgv[NewArgc++] = SS;
    NewArgv[NewArgc++] = SC;
    
    while (*Argv != NULL)
        NewArgv[NewArgc++] = *Argv++;
    NewArgv[NewArgc] = *Argv;
    /*}}}*/
    
    if (EXEC(Server, NewArgv, Envp) == -1)
    {
        /*{{{   */
        fprintf(stderr, "Fatal-driver- unable to execute '%s', %s\n", Server, strerror(errno));
        exit(EXIT_FAILURE);
        /*}}}*/
    }
    else
        exit(EXIT_SUCCESS);

    return(EXIT_SUCCESS);
}
/*}}}*/
/*}}}*/
