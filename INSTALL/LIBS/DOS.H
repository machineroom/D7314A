/* @(#)dos.h	1.3 9/8/92 */

/* dos.h */
/* Copyright (C) Inmos Ltd, 1989 */

#ifndef __dos_h
#define __dos_h 1

/* The segment registers. */

struct SREGS 
{
   unsigned long cs;
   unsigned long ds;
   unsigned long es;
   unsigned long ss;
};

/* The word registers */

struct WORDREGS 
{
   unsigned long ax;
   unsigned long bx;
   unsigned long cx;
   unsigned long dx;
   unsigned long di;
   unsigned long si;
   struct SREGS sregs;
   unsigned char cflag;
};

/* The byte registers */

/* dummies are included to allow the byte_regs struct */
/* to correctly overlay the word_regs struct.         */

struct BYTEREGS 
{
   unsigned char al, ah, dum1, dum2;
   unsigned char bl, bh, dum3, dum4;
   unsigned char cl, ch, dum5, dum6;
   unsigned char dl, dh, dum7, dum8;
};

/* The regs union */

union REGS 
{
   struct WORDREGS x;
   struct BYTEREGS h;
};

/* pcpointer type defines an 8086 far pointer */

typedef unsigned long int pcpointer;

#pragma IMS_translate(to86, "to86%c")
#pragma IMS_translate(from86, "from86%c")
#pragma IMS_translate(segread, "segread%c")
#pragma IMS_translate(int86x, "int86x%c")
#pragma IMS_translate(int86, "int86%c")
#pragma IMS_translate(intdosx, "intdosx%c")
#pragma IMS_translate(intdos, "intdos%c")
#pragma IMS_translate(bdos, "bdos%c")
#pragma IMS_translate(alloc86, "alloc86%c")
#pragma IMS_translate(free86, "free86%c")

extern int       to86(int /*len*/, char * /*source*/, pcpointer /*dest*/);
extern int       from86(int /*len*/, pcpointer /*source*/, char * /*dest*/);
extern void      segread(struct SREGS * /*segregs*/);
extern int       int86x(int /*intno*/, union REGS * /*inregs*/, 
                        union REGS * /*outregs*/, struct SREGS * /*segregs*/);
extern int       int86(int /*intno*/, union REGS * /*inregs*/, 
                       union REGS * /*outregs*/);
extern int       intdosx(union REGS * /*inregs*/, union REGS * /*outregs*/, 
                         struct SREGS * /*segregs*/);
extern int       intdos(union REGS * /*inregs*/, union REGS * /*outregs*/);
extern int       bdos(int /*dosfn*/, int /*dosdx*/, int /*dosal*/);
extern pcpointer alloc86(int /*n*/);
extern void      free86(pcpointer /*p*/);

#endif
