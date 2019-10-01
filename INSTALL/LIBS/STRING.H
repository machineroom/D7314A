/* @(#)string.h	1.5 6/30/92 */

/* string.h: ANSI X3.159 1989 library header, section 4.11 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __string_h
#define __string_h

#ifndef __size_t
#define __size_t 1
typedef unsigned int size_t;   /* from <stddef.h> */
#endif

#ifndef NULL
#define NULL (void *)0
#endif


extern void  *memcpy(void * /*s1*/, const void * /*s2*/, size_t /*n*/);
extern void  *memmove(void * /*s1*/, const void * /*s2*/, size_t /*n*/);
extern char  *strcpy(char * /*s1*/, const char * /*s2*/);
extern char  *strncpy(char * /*s1*/, const char * /*s2*/, size_t /*n*/);
extern char  *strcat(char * /*s1*/, const char * /*s2*/);
extern char  *strncat(char * /*s1*/, const char * /*s2*/, size_t /*n*/);
extern int    memcmp(const void * /*s1*/, const void * /*s2*/, size_t /*n*/);
extern int    strcmp(const char * /*s1*/, const char * /*s2*/);
extern int    strncmp(const char * /*s1*/, const char * /*s2*/, size_t /*n*/);
extern int    strcoll(const char * /*s1*/, const char * /*s2*/);
extern size_t strxfrm(char * /*s1*/, const char * /*s2*/, size_t /*n*/);
extern void  *memchr(const void * /*s*/, int /*c*/, size_t /*n*/);
extern char  *strchr(const char * /*s*/, int /*c*/);
extern size_t strcspn(const char * /*s1*/, const char * /*s2*/);
extern char  *strpbrk(const char * /*s1*/, const char * /*s2*/);
extern char  *strrchr(const char * /*s*/, int /*c*/);
extern size_t strspn(const char * /*s1*/, const char * /*s2*/);
extern char  *strstr(const char * /*s1*/, const char * /*s2*/);
extern char  *strtok(char * /*s1*/, const char * /*s2*/);
extern void  *memset(void * /*s*/, int /*c*/, size_t /*n*/);
extern char  *strerror(int /*errnum*/);
extern size_t strlen(const char * /*s*/);

#pragma IMS_builtin_inline(memcpy)
#pragma IMS_builtin_inline(strcpy)

#pragma IMS_nosideeffects(memcmp)
#pragma IMS_nosideeffects(strcmp)
#pragma IMS_nosideeffects(strncmp)
#pragma IMS_nosideeffects(strcoll)
#pragma IMS_nosideeffects(memchr)
#pragma IMS_nosideeffects(strchr)
#pragma IMS_nosideeffects(strcspn)
#pragma IMS_nosideeffects(strpbrk)
#pragma IMS_nosideeffects(strrchr)
#pragma IMS_nosideeffects(strspn)
#pragma IMS_nosideeffects(strstr)
#pragma IMS_nosideeffects(strlen)


#endif

/* end of string.h */
