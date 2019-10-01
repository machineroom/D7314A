/* @(#)semaphor.h	1.7 6/30/92 */

/* semaphor.h */
/* Copyright (C) Inmos Ltd. 1989, 1990, 1991, 1992 */

#ifndef __semaphore_h
#define __semaphore_h

#include <channel.h>

typedef	struct Semaphore Semaphore;


typedef	struct _IMS_SemPacket _IMS_SemPacket;
typedef	struct _IMS_Sim_Semaphore _IMS_Sim_Semaphore;

struct _IMS_SemPacket 
       {
         Channel          __post;   /* synchronisation channel */
	 _IMS_SemPacket  *__next;   /* pointer to next packet in sem chain */
       };

struct _IMS_Sim_Semaphore 
       {
 	 unsigned int    __value; 	/* value of semaphore */
	 _IMS_SemPacket  *__head;	/* Head of list of waiting processes */
	 _IMS_SemPacket  *__tail;	/* Tail of list of waiting processes */
       };

struct Semaphore 
       {
 	 unsigned int       __value;    /* value of semaphore */
	 _IMS_SemPacket    *__head;     /* Head of list of waiting processes */
	 _IMS_SemPacket    *__tail;     /* Tail of list of waiting processes */
         _IMS_Sim_Semaphore __lo_sem;   /* low priority exclusion semaphore */
         _IMS_Sim_Semaphore __hi_sem;   /* high priority exclusion semaphore */
         int                __lo_using; /* flag to indicate use by low pri process */
         Channel            __hi_chan;  /* high priority exclusion channel */
       };

#define	SEMAPHOREINIT(initvalue) \
                      {(initvalue),NULL,NULL,{1,NULL,NULL},{1,NULL,NULL}, \
                       0,(Channel)NotProcess_p}


#pragma IMS_translate(SemWait, "SemWait%c")
#pragma IMS_translate(SemSignal, "SemSignal%c")
#pragma IMS_translate(SemInit, "SemInit%c")
#pragma IMS_translate(SemAlloc, "SemAlloc%c")

extern void       (SemWait)(Semaphore * /*s*/);
extern void       (SemSignal)(Semaphore * /*s*/);
extern void       SemInit(Semaphore * /*s*/, int /*initvalue*/);
extern Semaphore *SemAlloc(int /*initvalue*/);

#endif
