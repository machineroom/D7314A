/* @(#)assert.h	1.3 6/5/92 */

/* assert.h: ANSI X3.159 1989 library header, section 4.2 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */

#ifndef __assert_h
#  define __assert_h
#else
#  undef assert
#endif

extern void _IMS_assert_fail(char *, char *, int);

#ifdef NDEBUG
#  define assert(ignore) ((void)0)
#else
#  define assert(e) ((e) ? (void)0 : _IMS_assert_fail(#e, __FILE__, __LINE__))
#endif

/* end of assert.h */
