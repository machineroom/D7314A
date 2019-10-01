/* @(#)signal.h	1.2 6/5/92 */

/* signal.h: ANSI X3.159 1989 library header, section 4.7 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */


#ifndef __signal_h
#define __signal_h

typedef int sig_atomic_t;

#pragma IMS_translate(IgnoreSignalHandler, "IgnoreSignalHandler%c")
#pragma IMS_translate(DefaultSignalHandler, "DefaultSignalHandler%c")
#pragma IMS_translate(ErrorSignalMarker, "ErrorSignalMarker%c")

extern void IgnoreSignalHandler(int);
extern void DefaultSignalHandler(int);
extern void ErrorSignalMarker(int);

#define SIG_DFL (void (*)(int))DefaultSignalHandler
#define SIG_ERR (void (*)(int))ErrorSignalMarker
#define SIG_IGN (void (*)(int))IgnoreSignalHandler

#define SIGABRT  1   /* abort                             */
#define SIGFPE   2   /* arithmetic exception              */
#define SIGILL   3   /* illegal instruction               */
#define SIGINT   4   /* attention request from user       */
#define SIGSEGV  5   /* bad memory access                 */
#define SIGTERM  6   /* termination request               */
#define SIGIO    7   /* input/output possible signal      */
#define SIGURG   8   /* urgent condition on IO channel    */
#define SIGPIPE  9   /* write on pipe with no one to read */
#define SIGSYS   10  /* bad argument to system call       */
#define SIGALRM  11  /* alarm clock                       */
#define SIGWINCH 12  /* window changed                    */
#define SIGLOST  13  /* resource lost                     */
#define SIGUSR1  14  /* user defined signal 1             */
#define SIGUSR2  15  /* user defined signal 2             */
#define SIGUSR3  16  /* user defined signal 3             */


extern void (*signal (int /*sig*/, void (* /*func*/ )(int)))(int);
extern int raise(int /*sig*/);

#endif

/* end of signal.h */
