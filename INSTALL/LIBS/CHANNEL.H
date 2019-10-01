/* @(#)channel.h	1.9 6/30/92 */

/* channel.h */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */

#ifndef __channel_h
#define __channel_h

#pragma IMS_on(channel_pointers)

typedef	const volatile void *Channel;

#pragma IMS_translate(ChanAlloc, "ChanAlloc%c")
#pragma IMS_translate(ChanInit, "ChanInit%c")
#pragma IMS_translate(ChanReset, "ChanReset%c")
#pragma IMS_translate(ChanIn, "ChanIn%c")
#pragma IMS_translate(ChanOut, "ChanOut%c")
#pragma IMS_translate(ChanInInt, "ChanInInt%c")
#pragma IMS_translate(ChanInChar, "ChanInChar%c")
#pragma IMS_translate(ChanOutInt, "ChanOutInt%c")
#pragma IMS_translate(ChanOutChar, "ChanOutChar%c")
#pragma IMS_translate(ChanOutTimeFail, "ChanOutTimeFail%c")
#pragma IMS_translate(ChanOutChanFail, "ChanOutChanFail%c")
#pragma IMS_translate(ChanInTimeFail, "ChanInTimeFail%c")
#pragma IMS_translate(ChanInChanFail, "ChanInChanFail%c")
#pragma IMS_translate(DirectChanIn, "DirectChanIn%c")
#pragma IMS_translate(DirectChanInChar, "DirectChanInChar%c")
#pragma IMS_translate(DirectChanInInt, "DirectChanInInt%c")
#pragma IMS_translate(DirectChanOut, "DirectChanOut%c")
#pragma IMS_translate(DirectChanOutChar, "DirectChanOutChar%c")
#pragma IMS_translate(DirectChanOutInt, "DirectChanOutInt%c")

extern void          ChanOut(Channel * /*chan*/, void * /*cp*/, int /*cnt*/);
extern void          ChanIn(Channel * /*chan*/, void * /*cp*/, int /*cnt*/);
extern Channel	    *ChanAlloc(void);
extern void          ChanInit(Channel * /*c*/);
extern int           ChanReset(Channel * /*c*/);
extern void          ChanOutChar(Channel * /*c*/, unsigned char /*ch*/);
extern void          ChanOutInt(Channel * /*c*/, int /*n*/);
extern unsigned char ChanInChar(Channel * /*c*/);
extern int           ChanInInt(Channel * /*c*/);
extern int           ChanOutTimeFail(Channel * /*chan*/, void * /*cp*/, 
                                     int /*cnt*/, int /*time*/);
extern int           ChanOutChanFail(Channel * /*chan*/, void * /*cp*/, 
                                     int /*cnt*/, Channel * /*failchan*/);
extern int           ChanInTimeFail(Channel * /*chan*/, void * /*cp*/, 
                                    int /*cnt*/, int /*time*/);
extern int           ChanInChanFail(Channel * /*chan*/, void * /*cp*/, 
                                    int /*cnt*/, Channel * /*failchan*/);
extern void          DirectChanIn(Channel * /*c*/, void * /*cp*/, 
                                  int /*count*/);
extern unsigned char DirectChanInChar(Channel * /*c*/);
extern int           DirectChanInInt(Channel * /*c*/);
extern void          DirectChanOut(Channel * /*c*/, void * /*cp*/, 
                                   int /*count*/);
extern void          DirectChanOutChar(Channel * /*c*/, unsigned char /*ch*/);
extern void          DirectChanOutInt(Channel * /*c*/, int /*n*/);


#pragma IMS_builtin_inline(DirectChanIn)
#pragma IMS_builtin_inline(DirectChanInChar)
#pragma IMS_builtin_inline(DirectChanInInt)
#pragma IMS_builtin_inline(DirectChanOut)
#pragma IMS_builtin_inline(DirectChanOutChar)
#pragma IMS_builtin_inline(DirectChanOutInt)

		
/* Remember that code intended for breakpoint debugging may not
   work if the following physical link values are used.	         */

#if _PTYPE == '2' || _PTYPE == '3'

/* Addresses for physical links on 16 bit transputers */

#define	LINK0OUT	((Channel *) 0x8000)
#define LINK1OUT	((Channel *) 0x8002)
#define LINK2OUT	((Channel *) 0x8004)
#define LINK3OUT	((Channel *) 0x8006)
#define	LINK0IN		((Channel *) 0x8008)
#define	LINK1IN		((Channel *) 0x800a)
#define	LINK2IN		((Channel *) 0x800c)
#define	LINK3IN		((Channel *) 0x800e)

/* Address of event pin on 16 bit transputers */

#define EVENT		((Channel *) 0x8010)

#define NotProcess_p    0x8000

#else

/* Address for physical links on 32 bit transputers */

#define	LINK0OUT	((Channel *) 0x80000000)
#define LINK1OUT	((Channel *) 0x80000004)
#define LINK2OUT	((Channel *) 0x80000008)
#define LINK3OUT	((Channel *) 0x8000000c)
#define	LINK0IN		((Channel *) 0x80000010)
#define	LINK1IN		((Channel *) 0x80000014)
#define	LINK2IN		((Channel *) 0x80000018)
#define	LINK3IN		((Channel *) 0x8000001c)

/* Address of event pin on 32 bit transputers */
#define EVENT		((Channel *) 0x80000020)

#define NotProcess_p    0x80000000

#endif


#endif
