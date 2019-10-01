/* @(#)centryd1.c	1.9 10/1/92 */ 
/* Copyright (C) INMOS Ltd, 1992 */

/*****************************************************************************
 *                                                                           *
 * This file contains the first stage of the C runtime startup code for use  *
 * in configured systems. This source is used to build the entry points:     *
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

#include "config.h"

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
 * Declare the next stage of the runtime startup. As for initialise_static   *
 * we declare the function as 'nolink' so that we can pass the gsb           *
 * explicitly. The definition of the next stage is not declared as 'nolink'  *
 * and so it obtains the first parameter that we pass here as if it were the *
 * hidden gsb. When it in turn calls main the gsb will be passed implicitly. *
 * In this way we 'bootstrap' the hidden gsb into the system.                *
 * It is translated so as not to invade the user's name space.               *
 *                                                                           *
 *****************************************************************************/

#pragma IMS_translate(CENTRYD_stage2, "CENTRYD_stage2%c")

extern void CENTRYD_stage2(void *hidden_gsb, struct Conf_Process *pdata);

#pragma IMS_nolink(CENTRYD_stage2)

/*****************************************************************************
 *                                                                           *
 * Declare the first stage of the runtime startup. It must be declared       *
 * before its definition to follow the rules of the IMS_nolink and           *
 * IMS_descriptor pragmas. The name of the routine is different for the      *
 * reduced and full versions. We declare the function as 'nolink' because it *
 * will be called as if it were written in occam and occam does not have a   *
 * hidden first parameter. Because this function is to be called as if it    *
 * were occam we also provide an occam style descriptor.                     *
 * It is translated so as not to invade the user's name space.               *
 *                                                                           *
 *****************************************************************************/

#ifndef REDUCED

/* Version for the full library */

#pragma IMS_translate(CENTRYD, "C.ENTRYD")

void CENTRYD(struct Conf_Process *pdata);

#pragma IMS_nolink(CENTRYD)

#pragma IMS_descriptor(CENTRYD, occam_harness, 5, 0, \
                       "PROC C.ENTRYD([18]INT ProcessData)\n  SEQ\n:")

#else /* REDUCED */

/* Version for the reduced library */

#pragma IMS_translate(CENTRYD_RC, "C.ENTRYD.RC")

void CENTRYD_RC(struct Conf_Process *pdata);

#pragma IMS_nolink(CENTRYD_RC)

#pragma IMS_descriptor(CENTRYD_RC, occam_harness, 5, 0, \
                       "PROC C.ENTRYD.RC([18]INT ProcessData)\n  SEQ\n:")

#endif /* REDUCED */

/*****************************************************************************
 *                                                                           *
 * Define the first stage of the runtime startup.                            *
 *                                                                           *
 *****************************************************************************/

#ifndef REDUCED

void CENTRYD(struct Conf_Process *pdata) 

#else  /* REDUCED */

void CENTRYD_RC(struct Conf_Process *pdata) 

#endif /* REDUCED */
{
  /**************************************************************************
   * Initialise the static area. Note that initialise static actually       *
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
   * to main must be omitted also because the rest of the startup code      *
   * depends on a static area being present. In this case main can be called*
   * directly from from this routine thereby omitting the stage2 startup.   *
   * The method for doing this is as follows:                               *
   *                                                                        *
   *   1) Declare main at the top of the file using the following:          *
   *                                                                        *
   *     #include <channel.h>                                               *
   *     #include <stddef.h>                                                *
   *     extern int main(void *hidden_gsb, int argc, char **argv,           *
   *                     char **envp,                                       *
   *                     Channel *in[], int inlen,                          *
   *                     Channel *out[], int outlen);                       *
   *                                                                        *
   *     #pragma IMS_nolink(main)                                           *
   *                                                                        *
   *   2) Remove the call to initialise_static.                             *
   *                                                                        *
   *   3) Replace the call to CENTRYD_stage2 with a call to main:           *
   *                                                                        *
   *      main(NULL, 0, NULL, NULL, NULL, 0, NULL, 0);                      *
   *                                                                        *
   **************************************************************************/

  initialise_static(pdata->StaticAddr, pdata->StaticAddr, 
                    pdata->StaticSize, pdata->StaticSize);

  /**************************************************************************
   * Call the next stage of the startup code. In calling the next stage     * 
   * we bootstrap the hidden gsb parameter. This is achieved by declaring   *
   * the next stage as  'nolink' function in this file and explicitly       *
   * passing the static pointer as the first parameter. The definition of   *
   * the next stage in its file is not nolinked and so the first parameter  *
   * passed from here appears there as the hidden gsb.                      *
   **************************************************************************/

  CENTRYD_stage2(pdata->StaticAddr, pdata);

}
