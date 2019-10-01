/* @(#)fnload2.c	1.18 10/1/92 */
/* Copyright (C) INMOS Ltd, 1992 */

/*****************************************************************************
 *                                                                           *
 * This file contains the second stage of the dynamic loading of C           *
 * functions.  This source is used to build the entry point c_fnload_stage2. *
 * This should be linked with either clibs.lnk or clibsrd.lnk depending on   *
 * whether one wants the full or reduced library.                            *
 *                                                                           *
 * This startup code should be modified to suit the function that is to be   *
 * called once initialisations have been done.                               *
 *                                                                           *
 * Note that this code relies on the presence of a static area. If no        *
 * static area is required then the application code can be called directly  *
 * from the first stage and this stage may be omitted.  See the file         *
 * fnload1.c for more information.                                           *
 *                                                                           *
 * FULL STAGE 2 :    a) Set up bounds of stack.                              *
 *                   b) Set up heap.                                         *
 *                   c) Set up I/O system and host system type.              *
 *                   d) Save return point for exit.                          *
 *                   e) Set up clock.                                        *
 *                   f) Call application code.                               *
 *                                                                           *  
 * REDUCED STAGE 2 : a) Set up bounds of stack.                              *
 *                   b) Set up heap.                                         *
 *                   c) Save return point for exit.                          *
 *                   d) Set up clock.                                        *
 *                   e) Call application code.                               *
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

/****************************************************************************
 * A gsb is expected as a hidden parameter to c_fnload_stage2               *
 ****************************************************************************/

int c_fnload_stage2( void* stack_addr,  size_t stack_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out,
                     /* application function parameters next */
                     .... )
{

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

  _IMS_stack_limit = (int *)stack_addr;
  _IMS_stack_base  = (int *)((size_t)stack_addr + stack_size_in_bytes);

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

  _IMS_heap_start         = (int *)heap_addr;
  _IMS_heap_size          = (unsigned int)heap_size_in_bytes;
  _IMS_heap_init_implicit = TRUE;
  _IMS_sbrk_alloc_request = SBRK_REQUEST;


  /**************************************************************************
   * Set up the host link information.  This is not required in a reduced   *
   * system.                                                                *
   **************************************************************************/

  set_host_link(in, out);

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
   * Call setjmp to mark the return position for a call to exit. The setjmp *
   * is only required as long as a call to exit() is subsequently used.     *
   **************************************************************************/

  if (setjmp(_IMS_startenv) == 0)
  {
    /************************************************************************
     * Set up start time and priority for clock(). This allows the clock    *
     * function to calculate the elapsed time since the application code    *
     * started.                                                             *
     ************************************************************************/

    _IMS_clock_priority = ProcGetPriority();
    _IMS_StartTime = (clock_t)ProcTime();

    /************************************************************************
     * Call the application code.  We call the function as an argument to   *
     * exit. Thus, returning from the application code is like a call to    *
     * exit with the return value from the application code, the idea being *
     * that this will clean up this child code and set _IMS_retval ready to *
     * return that value to stage1.                                         *
     * Note that the server is not terminated by this code.                 *
     ************************************************************************/

    exit(application_function(....));
  }
  return _IMS_retval;
}

