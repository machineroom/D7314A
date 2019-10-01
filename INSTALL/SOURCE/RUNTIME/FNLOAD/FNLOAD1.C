/* @(#)fnload1.c	1.9 10/1/92 */
/* Copyright (C) INMOS Ltd, 1992 */

/*****************************************************************************
 *                                                                           *
 * This file contains the first stage of the dynamic loading of C functions. *
 * This source is used to build the entry point c_fnload_stage1.  This       *
 * should be linked with either clibs.lnk or clibsrd.lnk depending on        *
 * whether one wants the full or reduced library.                            *
 *                                                                           *
 * This startup code should be modified to suit the function that is to be   *
 * called once initialisations have been done.                               *
 *                                                                           *
 * STAGE 1 : a) initialise the static area.                                  *
 *           b) call stage 2 and bootstrap the gsb.                          *
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

#include <channel.h>  /* for type Channel */
#include <stddef.h>   /* for size_t */

/*****************************************************************************
 *                                                                           *
 * Declare the initialise_static routine. This routine initialises the static*
 * area. Each routine in C expects a hidden first parameter which is the     *
 * address of the base of the static area, the gsb. We declare the function  *
 * as 'nolink' so that we can pass the gsb explicitly. The definition of     *
 * initialise_static is not declared as 'nolink' and so it obtains the first *
 * parameter that we pass here as if it were the hidden gsb.                 *
 * The function's identifier is translated so as not to invade the user's    *
 * name space.                                                               *
 *                                                                           *
 *****************************************************************************/

#pragma IMS_translate(initialise_static, "initialise_static%c")

extern int initialise_static(void *hidden_gsb, char *area_start, 
                             unsigned int area_size, 
                             unsigned int available_size);

#pragma IMS_nolink(initialise_static)

/*****************************************************************************
 *                                                                           *
 * Declare the next stage of the dynamic loading startup. As for             *
 * initialise_static we declare the function as 'nolink' so that we can pass *
 * the gsb explicitly. The definition of the next stage is not declared as   *
 * 'nolink' and so it obtains the first parameter that we pass here as if it *
 * were the hidden gsb. When it in turn calls the application code the gsb   *
 * will be passed implicitly.  In this way we 'bootstrap' the hidden gsb     *
 * into the system.                                                          *
 *                                                                           *
 *****************************************************************************/

extern int c_fnload_stage2( void* hidden_gsb,
                            void* stack_addr,  size_t stack_size_in_bytes,
                            void* heap_addr,   size_t heap_size_in_bytes,
                            Channel* in,       Channel* out,
                            /* application function parameters next */
                            .... );
#pragma IMS_nolink(c_fnload_stage2)

/*****************************************************************************
 *                                                                           *
 * Declare the first stage of the dynamic loading startup. It must be        *
 * declared before its definition to follow the rules of the IMS_descriptor  *
 * pragma.  We do not declare the function as 'nolink' because it will       *
 * generally be called via a pointer to it, and as such at the calling point *
 * a hidden gsb will be passed; we let this gsb be absorbed and then not     *
 * used.                                                                     *
 *                                                                           *
 *****************************************************************************/

int c_fnload_stage1( void* stack_addr,  size_t stack_size_in_bytes,
                     void* static_addr, size_t static_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out,
                     /* application function parameters next */
                     ....);
#pragma IMS_descriptor(c_fnload_stage1, ansi_c, 0, 0, "" )


/*****************************************************************************
 *                                                                           *
 * Define the first stage of the runtime startup.                            *
 *                                                                           *
 *****************************************************************************/

int c_fnload_stage1( void* stack_addr,  size_t stack_size_in_bytes,
                     void* static_addr, size_t static_size_in_bytes,
                     void* heap_addr,   size_t heap_size_in_bytes,
                     Channel* in,       Channel* out,
                     /* application function parameters next */
                     .... )
{
  /**************************************************************************
   * Initialise the static area. Note that initialise_static actually       *
   * returns 1 if an error occurs. We do not check this here as the only way*
   * error can occur is if the third parameter is greater than the fourth.  *
   * In this case they are always the same so we are guaranteed not to      *
   * obtain the error. If this should be changed in any way then the error  *
   * should be checked as follows:                                          *
   *                                                                        *
   *   #include <misc.h>                                                    *   
   *                                                                        *
   *   if (initialise_static(...))                                          *
   *     halt_processor();                                                  *
   *                                                                        *
   * A different error action can be performed if desired.                  *
   *                                                                        *
   * If no static area is required then the following call can be omitted.  *
   * Note that if this call is omitted then everything else up to the call  *
   * to the application code must be omitted also because rest of the       *
   * startup code depends on a static area being present. In this case the  *
   * application code can be called directly from this routine thereby      *
   * omitting the stage2 startup.  The method for doing this is as follows: *
   *                                                                        *
   *    Declare it at the top of this file with void *hidden_gsb as the     *
   *    first parameter, apply the IMS_nolink pragma to it in this file     *
   *    ONLY, and call it with NULL as the first parameter - this will      *
   *    bootstrap the hidden gsb parameter.                                 *
   **************************************************************************/

  initialise_static(static_addr, (char *)static_addr,
                    (unsigned int)static_size_in_bytes,
                    (unsigned int)static_size_in_bytes );

  /**************************************************************************
   * Call the next stage of the startup code.  In calling the next stage    * 
   * we bootstrap the hidden gsb parameter.  This is achieved by declaring  *
   * the next stage as 'nolink' function in this file and explicitly        *
   * passing the static pointer as the first parameter.  The definition of  *
   * the next stage in its file is not nolinked and so the first parameter  *
   * passed from here appears there as the hidden gsb.                      *
   **************************************************************************/

  return c_fnload_stage2( static_addr,
                          stack_addr,  stack_size_in_bytes,
                          heap_addr,   heap_size_in_bytes,
                          in,          out,
                          /* application function parameters next */
                          ....);
}
