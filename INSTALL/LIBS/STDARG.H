/* @(#)stdarg.h	1.2 6/5/92 */

/* stdarg.h: ANSI X3.159 1989  library header, section 4.8 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1990, 1990, 1991, 1992 */


#ifndef __stdarg_h
#define __stdarg_h

/* N.B. <stdio.h> is required to declare vfprintf() without defining      */
/* va_list.  Clearly the type __va_list there must keep in step.          */
typedef char *va_list[1];       /* see <stdio.h> */


/* Note that ___type is a syntactic item a bit like the type qualifiers   */
/* 'static', 'register', 'const' etc except that it has no effect! Its    */
/* purpose is to indicate when a type is being introduced and thus        */
/* help (a bit) when the user gets the args to va_arg the wrong way round */

#define __alignof(type) \
   ((char *)&(((struct{char __member1; \
                       ___type type __member2;}*) 0)->__member2) - \
    (char *)0)
#define __alignuptotype(ptr,type) \
   ((char *)((int)(ptr) + (__alignof(type)-1) & ~(__alignof(type)-1)))


#define va_start(ap,parmN) ((void)(*(ap) = (char *)&(parmN) + sizeof(parmN)))

#if _PTYPE == '2' || _PTYPE == '3'
#define va_arg(ap,type) \
   (___assert(((___typeof(___type type) & 0x410) == 0x410) || \
              ((___typeof(___type type) & 0x481) == 0), \
              "Illegal type used with va_arg"), \
   *(___type type *)((*(ap)=__alignuptotype(*(ap),type)+sizeof(___type type))-\
                     sizeof(___type type)))
#else
#define va_arg(ap,type) \
   (___assert((___typeof(___type type) & 0x481) == 0, \
              "Illegal type used with va_arg"), \
   *(___type type *)((*(ap)=__alignuptotype(*(ap),type)+sizeof(___type type))-\
                     sizeof(___type type)))
#endif

#define va_end(ap) ((void)(*(ap) = (char *)-256))

#endif

/* end of stdarg.h */
