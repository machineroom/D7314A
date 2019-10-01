/* @(#)setjmp.h	1.3 6/30/92 */

/* setjmp.h: ANSI X3.159 1989 library header, section 4.6 */
/* Copyright (C) A.C. Norman and A. Mycroft */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __setjmp_h
#define __setjmp_h

#define __JMP_BUF_SIZE 2 /* at least 2 words for setjmp and longjmp */

typedef int jmp_buf[__JMP_BUF_SIZE];

#pragma IMS_translate(_setjmp, "setjmp%c")

extern int _setjmp(jmp_buf /*env*/);

#define setjmp(env) (_setjmp(env))

extern void longjmp(jmp_buf /*env*/, int /*val*/);


#endif

/* end of setjmp.h */
