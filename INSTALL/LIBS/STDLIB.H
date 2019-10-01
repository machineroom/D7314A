/* @(#)stdlib.h	1.5 6/30/92 */

/* stdlib.h: ANSI X3.159 1989 library header, section 4.10 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __stdlib_h
#define __stdlib_h

#ifndef __size_t
#  define __size_t 1
   typedef unsigned int size_t;   /* from <stddef.h> */
#endif

#ifndef __wchar_t
   typedef int wchar_t;           /* from <stddef.h> */
#  define __wchar_t 1
#endif

#ifndef NULL
#  define NULL (void *)0                  /* from <stddef.h> */
#endif

typedef struct div_t { int quot, rem; } div_t;

typedef struct ldiv_t { long int quot, rem; } ldiv_t;

#define EXIT_FAILURE -9999
#define EXIT_SUCCESS  9999

#if _PTYPE == '2' || _PTYPE == '3'
#define RAND_MAX 0x7fff
#else
#define RAND_MAX 0x7fffffff
#endif  

#define MB_CUR_MAX 1


extern double atof(const char * /*nptr*/);
extern int atoi(const char * /*nptr*/);
extern long int atol(const char * /*nptr*/);
extern double strtod(const char * /*nptr*/, char ** /*endptr*/);
extern long int strtol(const char * /*nptr*/, char ** /*endptr*/, int /*base*/);
extern unsigned long int strtoul(const char * /*nptr*/,
                                       char ** /*endptr*/, int /*base*/);
extern int rand(void);
extern void srand(unsigned int /*seed*/);
extern void *calloc(size_t /*nmemb*/, size_t /*size*/);
extern void free(void * /*ptr*/);
extern void *malloc(size_t /*size*/);
extern void *realloc(void * /*ptr*/, size_t /*size*/);
extern void abort(void);
extern int  atexit(void (* /*func*/)(void));
extern void exit(int /*status*/);
extern char *getenv(const char * /*name*/);
extern int  system(const char * /*string*/);
extern void *bsearch(const void *key, const void * /*base*/,
              size_t /*nmemb*/, size_t /*size*/,
              int (* /*compar*/)(const void *, const void *));
extern void qsort(void * /*base*/, size_t /*nmemb*/, size_t /*size*/,
           int (* /*compar*/)(const void *, const void *));
extern int abs(int /*j*/);
extern div_t div(int /*numer*/, int /*denom*/);
extern long int labs(long int /*j*/);
extern ldiv_t ldiv(long int /*numer*/, long int /*denom*/);
extern int mblen(const char * /*s*/, size_t /*n*/);
extern int mbtowc(wchar_t * /*pwc*/, const char * /*s*/, size_t /*n*/);
extern int wctomb(char * /*s*/, wchar_t /*wchar*/);
extern size_t mbstowcs(wchar_t * /*pwcs*/, const char * /*s*/, size_t /*n*/);
extern size_t wcstombs(char * /*s*/, const wchar_t * /*pwcs*/, size_t /*n*/);

#pragma IMS_nosideeffects(abs)
#pragma IMS_nosideeffects(labs)
#pragma IMS_nosideeffects(div)
#pragma IMS_nosideeffects(ldiv)
#pragma IMS_nosideeffects(mblen)

#endif

/* end of stdlib.h */
