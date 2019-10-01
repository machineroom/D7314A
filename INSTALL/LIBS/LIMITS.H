/* @(#)limits.h	1.4 6/5/92 */

/* limits.h: ANSI X3.159 1989 library header, section 2.2.4.2 */
/* Copyright (C) A.C. Norman and A. Mycroft */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __limits_h
#define __limits_h

#define CHAR_BIT 8
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#ifdef __SIGNED_CHAR__
#define CHAR_MIN (-128)
#define CHAR_MAX 127
#else
#define CHAR_MIN 0
#define CHAR_MAX 255
#endif

#define MB_LEN_MAX 1

#define SHRT_MIN  (~0x7fff)
#define SHRT_MAX  0x7fff
#define USHRT_MAX 65535U

#if _PTYPE != '2' && _PTYPE != '3'
/* These values are for a 32 bit transputer */
#define INT_MIN   (~0x7fffffff) 
#define INT_MAX   0x7fffffff
#define UINT_MAX  0xffffffff
#else
/* These values are for a 16 bit transputer */
#define INT_MIN   (~0x7fff) 
#define INT_MAX   0x7fff
#define UINT_MAX  0xffff
#endif

#define LONG_MIN  (~0x7fffffffL)
#define LONG_MAX  0x7fffffffL
#define ULONG_MAX 0xffffffffUL

#endif

/* end of limits.h */
