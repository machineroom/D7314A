/* @(#)ctype.h	1.7 6/30/92 */

/* ctype.h: ANSI X3.159 1989 library header, section 4.3 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */

#ifndef __ctype_h
#define __ctype_h

#define __S 1            /* whitespace           */
#define __P 2            /* punctuation          */
#define __B 4            /* blank                */
#define __L 8            /* lower case letter    */
#define __U 16           /* upper case letter    */
#define __N 32           /* (decimal) digit      */
#define __C 64           /* control chars        */
#define __X 128          /* A-F and a-f          */


extern unsigned char _IMS_ctype[];

#define isalnum(c) (_IMS_ctype[c] & (__U+__L+__N))
extern int (isalnum)(int /*c*/);

#define isalpha(c) (_IMS_ctype[c] & (__U+__L))
extern int (isalpha)(int /*c*/);

#define iscntrl(c) (_IMS_ctype[c] & __C)
extern int (iscntrl)(int /*c*/);

#define isdigit(c) (((unsigned)(c)-'0') < 10)
extern int (isdigit)(int /*c*/);

#define isgraph(c) (_IMS_ctype[c] & (__L+__U+__N+__P))
extern int (isgraph)(int /*c*/);

#define islower(c) (((unsigned)(c)-'a') < 26)
extern int (islower)(int /*c*/);

#define isprint(c) (_IMS_ctype[c] & (__L+__U+__N+__P+__B))
extern int (isprint)(int /*c*/);

#define ispunct(c) (_IMS_ctype[c] & __P)
extern int (ispunct)(int /*c*/);

#define isspace(c) (_IMS_ctype[c] & __S)
extern int (isspace)(int /*c*/);

#define isupper(c) (((unsigned)(c)-'A') < 26)
extern int (isupper)(int /*c*/);

#define isxdigit(c) (_IMS_ctype[c] & (__N+__X))
extern int (isxdigit)(int /*c*/);

extern int tolower(int /*c*/);

extern int toupper(int /*c*/);

#pragma IMS_nosideeffects(tolower)
#pragma IMS_nosideeffects(toupper)

#endif

/* end of ctype.h */
