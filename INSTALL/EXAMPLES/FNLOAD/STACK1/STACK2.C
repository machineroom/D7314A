/*
 *  This file contains the second stage of the dynamic loading of a C
 *  function which requires static, heap, i/o, stack checking and
 *  to be able to call max_stack_usage().
 *
 *  This source is used to build the entry point c_fnload_stage2.
 *
 *  Note that this code relies on the presence of a static area.
 *
 */


#pragma IMS_off(stack_checking)

#include <setjmp.h>     /* for setjmp  */
#include <channel.h>    /* for Channel */
#include <stdlib.h>     /* for exit    */
#include "uglobal.h"    /* for globals */
#include "startup.h"    /* for set_host_link and io_and_hostinfo_init */


int stack_overflow(void);

int c_fnload_stage2( void* stack_addr,  size_t stack_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out )
{
  _IMS_stack_limit        = (int *)stack_addr;
  _IMS_stack_base         = (int *)((size_t)stack_addr + stack_size_in_bytes);

  _IMS_heap_start         = (int *)heap_addr;
  _IMS_heap_init_implicit = TRUE;
  _IMS_heap_size          = (unsigned int)heap_size_in_bytes;
  _IMS_sbrk_alloc_request = SBRK_REQUEST;


  set_host_link(in, out);
  io_and_hostinfo_init();


  if (setjmp(_IMS_startenv) == 0)
    {
      exit(stack_overflow());
    }
  return _IMS_retval;
}
