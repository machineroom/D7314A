-- @(#)getinit.s	1.3 6/30/92 

-- getinit.s
-- Copyright (C) INMOS Ltd, 1990, 1991, 1992
-- version 1.0

-- ***************************************************************************
-- *                                                                         *
-- * This code defines the function get_init_chain_start. Its C prototype    *
-- * would be :                                                              *
-- *   int *get_init_chain_start(void);                                      *
-- * The function issues a maininit patch which defines a word into which    *
-- * linker will patch the offset (in words) to the first entry on the       *
-- * static initialisation chain. This function returns a pointer to that    *
-- * word. The static initialisation function can then use the pointer to    *
-- * find the static initialisation chain.                                   *
-- * This file must be preprocessed using the icc preprocessor before being  *
-- * assembled.                                                              *
-- *                                                                         *
-- ***************************************************************************

-- ***************************************************************************
-- * First we issue the patch. Note that the size of the patch differs on    *
-- * 16 and 32 bit processors.                                               *
-- ***************************************************************************

     align
.mainlab:
     maininit
#if _PTYPE == '2' || _PTYPE == '3'
     blkb 2, #20, #20
#else
     blkb 4, #20, #20, #20, #20
#endif

-- ***************************************************************************
-- * Define the function. We hand translate the name so that it does not     *
-- * invade the user name space. The function loads the address of the       *
-- * patched word into the A register and then returns. This follows the     *
-- * C function return conventions.                                          *
-- ***************************************************************************

     align
get_init_chain_start%c:
     global get_init_chain_start%c
     ldc (.mainlab - .label)
     ldpi
.label:

     ret

-- ***************************************************************************
-- * It is possible that we may be called in a situation where there are no  *
-- * other files which contain init patches. A maininit patch which is issued*
-- * in such a situation will cause the linker to fail. In order to guard    *
-- * against such an eventuality we define a dummy init routine here.        *
-- ***************************************************************************

     align
     init
#if _PTYPE == '2' || _PTYPE == '3'
     blkb 2, #20, #20
#else
     blkb 4, #20, #20, #20, #20
#endif
     ret     

