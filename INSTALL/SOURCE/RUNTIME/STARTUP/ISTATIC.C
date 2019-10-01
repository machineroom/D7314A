/* @(#)istatic.c	1.7 6/30/92 */

/* istatic.c */
/* Copyright (C) Inmos Ltd, 1990, 1991, 1992 */

/*****************************************************************************
 *                                                                           *
 * This file contains the code which initialises the static area. The static *
 * area is first initialised to all zeros. Each module which contains static * 
 * has an associated initialisation routine which is responsible for         *
 * initialising all the non-zero static data for that module. All these      *
 * functions are placed onto a "static initialisation chain" by the linker.  *
 * The code in this file walks the static initialisation chain calling each  *
 * function on the chain as it goes. Each entry on the chain is made up of a *
 * header and a function. The header is a word which contains the byte offset*
 * from itself to the header of the next entry in the chain (or zero if this *
 * is the end of the chain). Directly following the header comes the         *
 * initialisation function itself. Thus an entry has the following form:     *
 *                          +---------------------------------+              *
 *   word address n     --> | offset to next entry in bytes   |              *
 *                          +---------------------------------+              *
 *   word address n + 1 --> | first 4 bytes of routine        |              *
 *                          +---------------------------------+              *
 *                          :                                 :              *
 *                          +---------------------------------+              *
 *   word address n + m --> | routine ends with ret           |              *
 *                          +---------------------------------+              *
 * The end of the chain is marked by an offset of zero at the head of the    *
 * entry.                                                                    *
 * The only parameter required by each initialisation function is the pointer*
 * to the base of static, the global static base (gsb). This is passed       *
 * implicitly as a hidden parameter.                                         *
 *                                                                           *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "startup.h"
#include "uglobal.h"

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
 * initialise_static   initialise the static area                            *
 *                     area_start : pointer to the base of the static area.  *
 *                     area_size  : The size of the static area required     *
 *                                  in bytes.                                *
 *                available_size  : The size of area available for use as    *
 *                                  a static area in bytes.                  *
 *                                                                           *
 * Note that the name is translated so that it does not invade the user's    *
 * name space.                                                               *
 *                                                                           *
 *****************************************************************************/

#pragma IMS_translate(initialise_static, "initialise_static%c")

int initialise_static(char *area_start, unsigned int area_size, 
                      unsigned int available_size)
{
  /***************************************************************************
   * local variables. In walking the chain we need to convert between object *
   * pointers and function pointers. We use the initfunc union to achieve    *
   * this.                                                                   *
   ***************************************************************************/
   
  union initfunc
    {
      int *codeptr;
      void (*initfunc)(void);
    } current, temp;

  /***************************************************************************
   * Check that we have enough space to create a static area. This test is   *
   * only required in situations where the area_size and available_size      *
   * parameters can differ, e.g. when called from occam using init.static or *
   * when using the MAIN.ENTRY, PROC.ENTRY or PROC.ENTRY.RC entry points.    *
   ***************************************************************************/

  if (area_size > available_size)
    return 1;

  /***************************************************************************
   * Clear the static area to zero. Thus all uninitialised static becomes    *
   * zero as is required by ANSI. Note that the following could be achieved  *
   * using the following call to memset:                                     *
   *   memset(area_start, 0, area_size);                                     *
   * But the use of a dedicated loop here reduces the runtime-overhead by    *
   * avoiding pulling in the memset module.                                  * 
   ***************************************************************************/
  
  {
    int *ptr; 

    for (ptr = (int *)area_start;
         ptr < (int *)((unsigned int)area_start + area_size);
         ptr++)
      *ptr = 0;
  }

  /***************************************************************************
   * Find the start of the static initialisation chain. This requires the use*
   * of a special linker patch. See the file getinit.s. current.codeptr is   *
   * set to point to a word in memory which contains a byte offset to the    *
   * first entry on the chain.                                               *
   ***************************************************************************/

  current.codeptr = get_init_chain_start();

  /***************************************************************************
   * Walk along the static initialisation chain calling each routine as we go*
   ***************************************************************************/

  while (*(current.codeptr) != 0)
  {
    current.codeptr = (int *)((unsigned int)current.codeptr + 
                              *(current.codeptr));
    temp.codeptr = current.codeptr + 1;
    (*(temp.initfunc))();                           /* gsb passed implicitly */
  }
  return 0;
}
 
