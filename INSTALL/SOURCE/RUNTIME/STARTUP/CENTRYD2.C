/* @(#)centryd2.c	1.18 10/1/92 */
/* Copyright (C) INMOS Ltd, 1992 */

/*****************************************************************************
 *                                                                           *
 * This file contains the second stage of the C runtime startup code for     *
 * use in configured systems. This source is used to build the entry         *
 * points:                                                                   *
 *                                                                           *
 *   C.ENTRYD    : linked using cstartup.lnk                                 *
 *   C.ENTRYD.RC : linked using cstartrd.lnk                                 *
 *                                                                           *
 * The reduced version is obtained by defining the REDUCED preprocessor      *
 * symbol.                                                                   *
 *                                                                           *
 * By modifying this code it is possible to greatly reduce the size of       *
 * runtime overhead which is added by the standard C entry points.           *
 *                                                                           *
 * Note that this code relies on the presence of a static area. If no        *
 * static area is required then main() can be called directly from the       *
 * first stage and this stage may be omitted. See the file centryd1.c for    *
 * more information.                                                         *
 *                                                                           *
 * FULL STAGE 2 :    a) Set up bounds of stack.                              *
 *                   b) Set up heap.                                         *
 *                   c) Set up pointer to configuration process structure.   *
 *                   d) Set up I/O system and host system type.              *
 *                   e) Get command line args.                               *
 *                   f) Save return point for exit.                          *
 *                   g) Set up clock.                                        *
 *                   h) Call main.                                           *
 *                   i) Terminate server if required                         *
 *                                                                           *  
 * REDUCED STAGE 2 : a) Set up bounds of stack.                              *
 *                   b) Set up heap.                                         *
 *                   c) Set up pointer to configuration process structure.   *
 *                   d) Save return point for exit.                          *
 *                   e) Set up clock.                                        *
 *                   f) Call main.                                           *
 *                                                                           *  
 * Note that the order in which the above tasks are done is significant.     *
 * Changing the order may cause the system to fail.                          *
 *                                                                           *  
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 * Make sure stack checking is disabled when this file is compiled. Stack    *
 * checking must not be enabled in the start up code because global data     *
 * required by the stack checking code is not set up yet.                    *
 *                                                                           *
 *****************************************************************************/

#pragma IMS_off(stack_checking)

/*****************************************************************************
 *                                                                           *
 * Include files.                                                            *
 *                                                                           *
 *****************************************************************************/

#include <setjmp.h>     /* for setjmp                       */
#include <channel.h>    /* for Channel                      */
#include <stddef.h>     /* for NULL                         */
#include <stdlib.h>     /* for exit                         */
#include <process.h>    /* for ProcTime and ProcGetPriority */
#include "uglobal.h"    /* for globals                      */
#include "startup.h"    /* for startup internal functions   */
#include <misc.h>       /* for get_param                    */
#include "config.h"     /* for Conf_Process                 */

/*****************************************************************************
 *                                                                           *
 * Declare main using the INMOS standard argument list.                      *
 *                                                                           *  
 *****************************************************************************/
 
extern int main(int argc, char **argv, char **envp, 
                Channel *in[], int inlen,
                Channel *out[], int outlen);

/*****************************************************************************
 *                                                                           *
 * Define the second stage routine. The name is translated to avoid invading *
 * the user's name space.                                                    *
 *                                                                           *
 *****************************************************************************/

#pragma IMS_translate(CENTRYD_stage2, "CENTRYD_stage2%c")

void CENTRYD_stage2(struct Conf_Process *pdata) 
{
#ifndef REDUCED
  /**************************************************************************
   * Local variables, required if command line arguments are needed. Not    *
   * required in a reduced system.                                          *
   **************************************************************************/
  
  int argc = 0;
  char **argv;
#endif /* REDUCED */


  /**************************************************************************
   *                                                                        *
   * Set up the bounds of the stack for the main thread of execution. These *
   * globals are used by the following:                                     *
   *   1. Stack checking.                                                   *
   *   2. The get_details_of_free_stack_space function.                     *
   *   3. Parallel processes (use of ProcAlloc and ProcInit).               *
   *   4. The max_stack_usage function.                                     *
   * If any of these features are used then the following initialisations   *
   * may not be omitted.                                                    *
   *                                                                        *
   *    _IMS_stack_limit        : The maximum extent to which the stack can *
   *                              grow. Note that the stack is a falling    *
   *                              stack.                                    *
   *    _IMS_stack_base         : Pointer to base of stack.                 *
   *                                                                        *
   **************************************************************************/

  _IMS_stack_limit = (int *)((unsigned int)pdata->StackAddr - 
                             pdata->StackSize);
  _IMS_stack_base  = (int *)(pdata->StackAddr);

  /**************************************************************************
   *                                                                        *
   * Set up the heap. If no heap is required then these initialisations can *
   * be omitted.                                                            *
   * Note that a heap must be set up if the full library is being used.     *
   *   _IMS_heap_start         : A pointer to the base of the heap.         *
   *   _IMS_heap_init_implicit : A boolean which is set to TRUE if the heap *
   *                             is initialised implicitly on the first call*
   *                             of a memory allocation function. This must *
   *                             always be set to TRUE otherwise the heap   *
   *                             allocation functions will fail.            *
   *   _IMS_heap_size          : The size of the heap memory region in      *
   *                             bytes.                                     *
   *   _IMS_sbrk_alloc_request : The size of block which sbrk adds to the   *
   *                             memory space available to malloc.          *
   **************************************************************************/

  _IMS_heap_start         = (int *)(pdata->HeapAddr);
  _IMS_heap_size          = pdata->HeapSize;
  _IMS_heap_init_implicit = TRUE;
  _IMS_sbrk_alloc_request = SBRK_REQUEST;

  /**************************************************************************
   * Set up the global variable which is used by some functions to obtain   *
   * a pointer to the configuration process structure set up by the         *
   * configurer.                                                            *
   * The following functions make use of this global:                       *
   *   1. get_param                                                         *
   *   2. get_bootlink_channels                                             *
   *   3. get_details_of_free_memory                                        *
   * If none of these functions are used then this initialisation may be    *
   * omitted.                                                               *
   * Note that get_param is used below, so that if the initialisation of    *
   * _IMS_PData is omitted then make sure that the call to get_param below  *
   * is not required, and hence omitted.                                    *
   **************************************************************************/

  _IMS_PData = pdata;

#ifndef REDUCED

  /**************************************************************************
   * Set up the host link information. The runtime system assumes that the  *
   * first two configuration parameters are channels fromserver and         *
   * toserver respectively. This is not required in a reduced system.       *
   **************************************************************************/

  {
    Channel *in, *out;

    in  = (Channel *)get_param(1);
    out = (Channel *)get_param(2);
    set_host_link(in, out);
  }

  /**************************************************************************
   * Set up the I/O system and obtain the host type. The I/O system         *
   * consists of three layers and all three are set up by this call.        *
   * The host information is required so that the I/O system can determine  *
   * the type of the host file system. Note that this means that the        *
   * host_info function is only available as long as the following is       *
   * called. The host link information must have been set up before the I/O *
   * system is initialised. This is not required in a reduced system.       *
   * A heap must have been set up in order for this call to succeed.        *
   **************************************************************************/

  io_and_hostinfo_init();

  /**************************************************************************
   * Obtain the command line arguments. This requires the automatics        *
   * defined at the top of this routine.                                    *
   * The host link must have been set before the command line arguments can *
   * be obtained. This is not required in a reduced system.                 *
   * If this is omitted then the call to main must be modified so that it   *
   * does not use the argc and argv local variables.                        *
   **************************************************************************/

  GetArgsMyself(&argc, &argv);

#endif /* REDUCED */  

  /**************************************************************************
   * Call setjmp to mark the return position for a call to exit. The setjmp *
   * is only required as long as a call to exit() is subsequently used.     *
   **************************************************************************/

  if (setjmp(_IMS_startenv) == 0)
  {
    /************************************************************************
     * Set up start time and priority for clock(). This allows the clock    *
     * function to calculate the elapsed time since the program started.    *
     ************************************************************************/

    _IMS_clock_priority = ProcGetPriority();
    _IMS_StartTime = (clock_t)ProcTime();

    /************************************************************************
     * Call main. We call main as an argument to exit. Thus returning from  *
     * main is like a call to exit. The call to exit ensures that ANSI      *
     * behaviour on closing open files etc. is followed. Note that the      *
     * reduced case also sets up argc and argv as required by ANSI.         *
     * If ANSI behaviour is not important then a minimal call to main which *
     * still returns the result of main to the environment is as follows:   *
     *   _IMS_retval = main(0, NULL, NULL, NULL, 0, NULL, 0);               *
     * Since only those systems which terminate the server can return a     *
     * value to the calling environment then we only need to store to       *
     * _IMS_retval if we subsequently call terminate_server.                *
     ************************************************************************/

#ifndef REDUCED
    exit(main(argc, argv, NULL, NULL, 0, NULL, 0));
#else /* REDUCED */
    {
      char *argv[2] = { "", NULL };

      exit(main(1, argv, NULL, NULL, 0, NULL, 0));
    }
#endif /* REDUCED */
  }
#ifndef REDUCED

  /**************************************************************************
   * main has returned, we must now decide whether to terminate the server. * 
   * Not required for the reduced case.                                     *
   * We terminate the server only if exit_terminate was called.             *
   * The global variable _IMS_entry_term_mode can be used to decide whether *
   * exit, exit_repeat, exit_terminate or exit_noterminate was called to    *
   * exit the program. exit_repeat and exit_terminate act like exit in      *
   * the configured case so we only worry about whether exit_noterminate is *
   * called. If exit_noterminate is called the bit 2 of _IMS_entry_term_mode*
   * is clear. If this level of control is not required the test or the call*
   * to exit_terminate or both can be omitted.                              *
   * The return value of the program is stored in _IMS_retval by exit. We   *
   * must convert the special values for EXIT_SUCCESS and EXIT_FAILURE to   *
   * their iserver counterparts sps.success and sps.failure. Note that we   *
   * need a long value to contain the server status which is a 32 bit value *
   * on all processors.                                                     *
   **************************************************************************/

  if ((_IMS_entry_term_mode & TERM_BIT) != 0)
  {
    long int status = (long int)_IMS_retval;
    if (status == EXIT_SUCCESS)
      status = SPS_SUCCESS;
    else if (status == EXIT_FAILURE)
      status = SPS_FAILURE;
    terminate_server(status);
  }

#endif /* REDUCED */
}

