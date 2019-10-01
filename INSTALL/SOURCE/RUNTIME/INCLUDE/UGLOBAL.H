/* @(#)uglobal.h	1.8 8/27/92 */

/* uglobal.h */
/* Copyright (C) Inmos Ltd, 1992 */

#ifndef __uglobal_h
#define __uglobal_h

#include "config.h"
#include <setjmp.h>
#include <time.h>

/*****************************************************************************
 * Some useful macros                                                        *
 *   TRUE              : Boolean true.                                       *
 *   FALSE             : Boolean false.                                      *
 *   REPEAT_BIT        : Bit set in _IMS_entry_term_mode if exit_repeat used.*
 *   TERM_BIT          : Bit set in _IMS_entry_term_mode if exit_terminate   *
 *                       used.                                               *
 *   SPS_SUCCESS       : iserver return status for success.                  *
 *   SPS_FAILURE       : iserver return status for failure.                  *
 *   SBRK_REQUEST      : The default size by which sbrk increases the heap.  *
 *****************************************************************************/

#define TRUE  1
#define FALSE 0

#define REPEAT_BIT 1
#define TERM_BIT   2

#define SPS_SUCCESS  999999999L
#define SPS_FAILURE -999999999L

#if _PTYPE == '2' || _PTYPE == '3'
#define SBRK_REQUEST 1024                           /* for 16 bit processors */
#else
#define SBRK_REQUEST 4096                           /* for 32 bit processors */
#endif

/*****************************************************************************
 * Runtime system global variables                                           *
 *                                                                           *  
 *   _IMS_heap_start         : Pointer to start of heap                      *
 *   _IMS_heap_size          : Size of heap in bytes                         *
 *   _IMS_heap_init_implicit : Flag used to determine whether heap           *
 *                             initialisation occurs implicitly on the first *
 *                             use of a memory allocation function or whether*
 *                             an explicit initialisation is required. In    *
 *                             this runtime system implicit heap             *
 *                             initialisation is used so this flag must      *
 *                             always be set to TRUE.                        *
 *   _IMS_PData              : Pointer to configuration process structure.   *
 *   _IMS_startenv           : Position for exit to longjmp to.              *
 *   _IMS_StartTime          : Used by clock to calculate elapsed time.      *
 *   _IMS_clock_priority     : Used by clock to ensure same priority as      *
 *                             startup.                                      *
 *   _IMS_stack_limit        : Used by stack checking.                       *
 *   _IMS_stack_base         : Used by stack checking.                       *
 *   _IMS_retval             : The value to be returned by main or via exit. *
 *   _IMS_entry_term_mode    : Used to determine which version of exit used. *
 *   _IMS_sbrk_alloc_request : The size of block which sbrk adds to the      *
 *                             memory space available to malloc.             *
 *                                                                           *  
 *****************************************************************************/

extern int                 *_IMS_heap_start;
extern unsigned int         _IMS_heap_size;         
extern int                  _IMS_heap_init_implicit;            
extern struct Conf_Process *_IMS_PData;
extern jmp_buf              _IMS_startenv;
extern clock_t              _IMS_StartTime; 
extern int                  _IMS_clock_priority;
extern int                 *_IMS_stack_limit;
extern int                 *_IMS_stack_base; 
extern int                  _IMS_retval; 
extern int                  _IMS_entry_term_mode;
extern unsigned int         _IMS_sbrk_alloc_request;

#endif
/* end of uglobal.h */

