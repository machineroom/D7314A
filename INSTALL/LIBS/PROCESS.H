/* @(#)process.h	1.13 6/30/92 */

/* process.h */
/* Copyright (C) Inmos Ltd. 1989 */

#ifndef __process_h
#define __process_h

#pragma IMS_conn_v1()

#include <channel.h>

typedef struct Process Process;
struct Process 
       {
          Process *link;        /* list of runnable/sleeping (MUST BE FIRST)*/
          int wsret;            /* location of endp wp */
          int *wbase;           /* pointer to bottom of workspace */
          int wsize;            /* size of work space pointer */
          int *wp;              /* inital wp */
          int psize;            /* number of word sized parameters */
          void (*ofunc)();      /* pointer to function (process) */
          Channel chan;         /* Used to indicate state */
       };

extern Process *_IMS_AllProc;

#pragma IMS_translate(ProcParList, "ProcParList%c")
#pragma IMS_translate(ProcReschedule, "ProcReschedule%c")
#pragma IMS_translate(ProcAlloc, "ProcAlloc%c")
#pragma IMS_translate(ProcInit, "ProcInit%c")
#pragma IMS_translate(ProcParam, "ProcParam%c")
#pragma IMS_translate(ProcTime, "ProcTime%c")
#pragma IMS_translate(ProcGetPriority, "ProcGetPriority%c")
#pragma IMS_translate(ProcRun, "ProcRun%c")
#pragma IMS_translate(ProcRunHigh, "ProcRunHigh%c")
#pragma IMS_translate(ProcRunLow, "ProcRunLow%c")
#pragma IMS_translate(ProcPar, "ProcPar%c")
#pragma IMS_translate(ProcPriPar, "ProcPriPar%c")
#pragma IMS_translate(ProcAlt, "ProcAlt%c")
#pragma IMS_translate(ProcAltList, "ProcAltList%c")
#pragma IMS_translate(ProcSkipAlt, "ProcSkipAlt%c")
#pragma IMS_translate(ProcSkipAltList, "ProcSkipAltList%c")
#pragma IMS_translate(ProcTimerAlt, "ProcTimerAlt%c")
#pragma IMS_translate(ProcTimerAltList, "ProcTimerAltList%c")
#pragma IMS_translate(ProcTimePlus, "ProcTimePlus%c")
#pragma IMS_translate(ProcTimeMinus, "ProcTimeMinus%c")
#pragma IMS_translate(ProcTimeAfter, "ProcTimeAfter%c")
#pragma IMS_translate(ProcAfter, "ProcAfter%c")
#pragma IMS_translate(ProcWait, "ProcWait%c")
#pragma IMS_translate(ProcStop, "ProcStop%c")
#pragma IMS_translate(ProcInitClean, "ProcInitClean%c")
#pragma IMS_translate(ProcAllocClean, "ProcAllocClean%c")
#pragma IMS_translate(ProcJoin, "ProcJoin%c")
#pragma IMS_translate(ProcJoinList, "ProcJoinList%c")

extern Process *ProcAlloc(void (* /*func*/)(), int /*wsize*/, 
                          int /*psize*/, ...);
extern int      ProcInit(Process * /*p*/, void (* /*func*/)(), 
                         int * /*ws*/, int /*wsize*/, 
                         int /*psize*/, ...);	
extern void     ProcParam(Process * /*sf*/, ...);
extern int      ProcTime(void);
extern int      ProcGetPriority(void);
extern void     ProcReschedule(void);
extern void     ProcRun(Process * /*p*/);
extern void     ProcRunHigh(Process * /*p*/);
extern void     ProcRunLow(Process * /*p*/);
extern void     ProcPar(Process * /*p1*/, ...);
extern void     ProcParList(Process ** /*plist*/);
extern void     ProcPriPar(Process * /*phigh*/, Process * /*plow*/);
extern int      ProcAlt(Channel * /*c1*/, ...); 
extern int      ProcAltList(Channel ** /*clist*/);
extern int      ProcSkipAlt(Channel * /*c1*/, ...);
extern int      ProcSkipAltList(Channel ** /*clist*/);
extern int      ProcTimerAlt(int /*time*/, Channel * /*c1*/, ...);
extern int      ProcTimerAltList(int /*time*/, Channel ** /*clist*/);
extern int      ProcTimePlus(const int /*a*/, const int /*b*/);
extern int      ProcTimeMinus(const int /*a*/, const int /*b*/);
extern int      ProcTimeAfter(const int /*a*/, const int /*b*/);
extern void     ProcAfter(int /*x*/);
extern void     ProcWait(int /*x*/);
extern void     ProcStop(void);
extern void     ProcInitClean(Process * /*p*/);
extern void     ProcAllocClean(Process * /*p*/);
extern int      ProcJoin(Process * /*p1*/, ...); 
extern int      ProcJoinList(Process ** /*plist*/);

#pragma IMS_builtin_inline(ProcReschedule)
#pragma IMS_builtin_inline(ProcGetPriority)
#pragma IMS_builtin_inline(ProcTime)

#pragma IMS_nosideeffects(ProcTime)
#pragma IMS_nosideeffects(ProcGetPriority)
#pragma IMS_nosideeffects(ProcTimePlus)
#pragma IMS_nosideeffects(ProcTimeMinus)
#pragma IMS_nosideeffects(ProcTimeAfter)

#define PROC_HIGH 0
#define	PROC_LOW  1

#define CLOCKS_PER_SEC_HIGH	1000000
#define CLOCKS_PER_SEC_LOW	15625

#endif

