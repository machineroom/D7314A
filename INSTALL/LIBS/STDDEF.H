/* @(#)stddef.h	1.2 6/5/92 */

/* stddef.h: ANSI X3.159 1989 library header, section 4.1.5 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __stddef_h
#define __stddef_h

typedef int ptrdiff_t;

#ifndef __size_t
#  define __size_t 1
typedef unsigned int size_t;   /* others (e.g. <stdio.h>) define */
#endif

#ifndef __wchar_t
#  define __wchar_t 1
typedef int wchar_t;                         /* also in <stdlib.h> */
#endif

#ifndef NULL  /* this hack is so that <stdio.h> can also define it */
#  define NULL (void *)0
#endif

#define offsetof(type, member) \
    ((size_t)((char *)&(((___type type *)0)->member) - (char *)0))

#endif

/* end of stddef.h */
