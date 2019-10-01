/* @(#)iocntrl.h	1.1 3/25/91 */

/* iocntrl.h */
/* Copyright (C) Inmos Ltd. 1989 */

#ifndef __iocntrl_h
#define __iocntrl_h 1

/* whence values for lseek() */
#define	L_SET		0	/* absolute offset */
#define	L_INCR		1	/* relative to current offset */
#define	L_XTND		2	/* relative to end of file */

/* modes for open() */
#define	O_RDONLY	0x00
#define	O_WRONLY	0x01
#define	O_RDWR		0x02
#define	O_APPEND	0x04
#define	O_TRUNC		0x10
#define O_BINARY	0x80
#define O_TEXT		0x00
#define	O_CREAT		0x08
#define	O_EXCL		0x20
#define	O_SYNC		0x40

/* unix like function prototypes */

#pragma IMS_translate(close, "close%c")
#pragma IMS_translate(filesize, "filesize%c")
#pragma IMS_translate(isatty, "isatty%c")
#pragma IMS_translate(lseek, "lseek%c")
#pragma IMS_translate(open, "open%c")
#pragma IMS_translate(read, "read%c")
#pragma IMS_translate(unlink, "unlink%c")
#pragma IMS_translate(write, "write%c")
#pragma IMS_translate(creat, "creat%c")

extern int  close(int /*fd*/);
extern long filesize(int /*fd*/);
extern int  isatty(int /*fd*/);
extern int  lseek(int /*fd*/, long /*offset*/, int /*origin*/);
extern int  open(char * /*name*/, int /*flags*/);
extern int  read(int /*fd*/, char * /*buf*/, int /*n*/);
extern int  unlink(char * /*name*/);
extern int  write(int /*fd*/, char * /*buf*/, int /*n*/);
extern int  creat(char * /*name*/, int /*flags*/);

/* other i/o functions */

#pragma IMS_translate(pollkey, "pollkey%c")
#pragma IMS_translate(getkey,  "getkey%c")
#pragma IMS_translate(server_transaction, "server_transaction%c")

extern int pollkey(void);
extern int getkey(void);
extern int server_transaction(char * /*message*/, int /*length*/, 
                              char * /*reply*/);

#endif
