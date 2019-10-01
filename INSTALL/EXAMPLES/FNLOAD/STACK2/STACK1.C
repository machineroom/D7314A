/*
 *  This file contains the first stage of the dynamic loading of a C
 *  function which requires static, heap, i/o, stack checking and
 *  to be able to call max_stack_usage().
 *
 *  This source is used to build the entry point c_fnload_stage1.
 *
 *  STAGE 1 : a) initialise the static area.
 *            b) call stage 2 and bootstrap the gsb.
 *
 */


#pragma IMS_off(stack_checking)

#include <channel.h>  /* for type Channel */
#include <stddef.h>   /* for size_t */


#pragma IMS_translate(initialise_static, "initialise_static%c")
extern int initialise_static(void *hidden_gsb, char *area_start, 
                             unsigned int area_size, 
                             unsigned int available_size);
#pragma IMS_nolink(initialise_static)


extern int c_fnload_stage2(void* hidden_gsb,
                           void* stack_addr,  size_t stack_size_in_bytes,
                           void* heap_addr,   size_t heap_size_in_bytes,
                           Channel* in,       Channel* out );
#pragma IMS_nolink(c_fnload_stage2)



int c_fnload_stage1( void* static_addr, size_t static_size_in_bytes,
                     void* stack_addr,  size_t stack_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out );
#pragma IMS_descriptor(c_fnload_stage1, ansi_c, 0, 0, "" )



int c_fnload_stage1( void* static_addr, size_t static_size_in_bytes,
                     void* stack_addr,  size_t stack_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out )
{
  initialise_static(static_addr, (char *)static_addr,
                    (unsigned int)static_size_in_bytes,
                    (unsigned int)static_size_in_bytes );

  return c_fnload_stage2( static_addr,
                          stack_addr,  stack_size_in_bytes,
                          heap_addr,   heap_size_in_bytes,
                          in,          out );
}
