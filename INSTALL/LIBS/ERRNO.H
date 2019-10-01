/* @(#)errno.h	1.2 7/15/92 */

/* errno.h: ANSI X3.159 1989 library header, section 4.1.3 */
/* Copyright (C) Codemist Ltd. */
/* Copyright (C) Inmos Ltd. 1989 */

#ifndef __errno_h
#define __errno_h

#pragma IMS_translate(errno, "_IMS_errno")

extern volatile int errno;


#define EDOM     1
#define ERANGE   2
#define ESIGNUM  3
#define EIO      4
#define EFILPOS  5
#define ENXIO    6
#define E2BIG    7
#define ENOEXEC  8
#define EBADF    9
#define ECHILD   10
#define EAGAIN   11
#define ENOMEM   12
#define EACCES   13
#define EFAULT   14
#define ENOTBLK  15
#define EBUSY    16
#define EEXIST   17
#define EXDEV    18
#define ENODEV   19
#define ENOTDIR  20
#define EISDIR   21
#define EINVAL   22
#define ENFILE   23
#define EMFILE   24
#define ENOTTY   25
#define ETXTBSY  26
#define EFBIG    27
#define ENOSPC   28
#define ESPIPE   29
#define EROFS    30
#define EMLINK   31
#define EPIPE    32
#define EPERM    33
#define ENOENT   34
#define ESRCH    35
#define EINTR    36
#define EDOS     37

#endif

/* end of errno.h */
