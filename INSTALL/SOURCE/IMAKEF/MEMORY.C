/* CMSIDENTIFIER
   PLAY:MEMORY_C@400.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*****************************************************************************
 *
 *   Object Name : memory.c
 *   Revision    : 1
 *
 *   Copyright (c) Inmos Ltd, 1988
 *   All rights reserved.
 *
 *   DESCRIPTION : defines the *my_allocate function which mallocs memory
 *
 *   DOCUMENTS   : The Buildmake Program, 16th May 1988 (R Knagg)
 *                 Buildmake Technical Documentation, May 31st 1988 (R Knagg)
 *
 *   HISTORY     : Created by Ray Knagg, 1st June 1988
 *
 *****************************************************************************/

#include <stdio.h>
#include "inmos.h"
#include "struct.h"
#include "header.h"

PUBLIC void *my_allocate(size)
INT size;
{
  char *new;

  new = malloc(size);

  if(new == NULL)
    error("malloc failed", "");

  return(new);
}
