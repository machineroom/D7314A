/* @(#)stdiored.h	1.3 6/15/92 */

/* stdiored.h: reduced version of stdio */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */

/*
 * stdiored.h declares enough so that sprintf and sscanf can be provided
 * in the reduced library.
 */

#ifndef __stdiored_h
#define __stdiored_h

#ifndef __size_t
#define __size_t 1
typedef unsigned int size_t;   /* from <stddef.h> */
#endif

typedef char *__va_list[1];       /* keep in step with <stdarg.h> */

#ifndef NULL
#  define NULL (void *)0                /* see <stddef.h> */
#endif

#pragma IMS_on(printf_checking)

extern int sprintf(char * /*s*/, const char * /*format*/, ...);

#pragma IMS_off(printf_checking)
#pragma IMS_on(scanf_checking)

extern int sscanf(const char * /*s*/, const char * /*format*/, ...);

#pragma IMS_off(scanf_checking)

extern int vsprintf(char * /*s*/, const char * /*format*/, __va_list /*arg*/);

#endif

/* end of stdiored.h */
