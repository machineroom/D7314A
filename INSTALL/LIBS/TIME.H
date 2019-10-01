/* @(#)time.h	1.5 6/17/92 */

/* time.h: ANSI X3.159 1989 library header, section 4.12 */
/* Copyright (C) Codemist Ltd. */
/* version 0.02 */
/* Copyright (C) Inmos Ltd. 1989 */


#ifndef __time_h
#define __time_h

#ifndef __size_t
#define __size_t 1
typedef unsigned int size_t;   /* from <stddef.h> */
#endif

#ifndef NULL
#  define NULL (void *)0
#endif

typedef unsigned int clock_t;    
typedef unsigned long time_t;     

/*
 * CLOCKS_PER_SEC is 1000000 if high priority process.
 * CLOCKS_PER_SEC is 15625 if low priority process.
 * The defines for CLOCKS_PER_SEC_HIGH and CLOCKS_PER_SEC_LOW are in process.h
 */

#pragma IMS_translate(___IMS_ProcGetPriority, "ProcGetPriority%c")
extern int ___IMS_ProcGetPriority(void);
#pragma IMS_builtin_inline (___IMS_ProcGetPriority)
#define CLOCKS_PER_SEC (___IMS_ProcGetPriority() == 0 ? 1000000 : 15625)


struct tm {
  int tm_sec;   /* seconds after the minute, 0 to 60
                   (0 - 60 allows for the occasional leap second) */
  int tm_min;   /* minutes after the hour, 0 to 59 */
  int tm_hour;  /* hours since midnight, 0 to 23 */
  int tm_mday;  /* day of the month, 1 to 31 */
  int tm_mon;   /* months since January, 0 to 11 */
  int tm_year;  /* years since 1900 */
  int tm_wday;  /* days since Sunday, 0 to 6 */
  int tm_yday;  /* days since January 1, 0 to 365 */
  int tm_isdst; /* Daylight Savings Time flag */
};

extern clock_t clock(void);
extern double difftime(time_t /*time1*/, time_t /*time0*/);
extern time_t mktime(struct tm * /*timeptr*/);
extern time_t time(time_t * /*timer*/);
extern char *asctime(const struct tm * /*timeptr*/);
extern char *ctime(const time_t * /*timer*/);
extern struct tm *gmtime(const time_t * /*timer*/);
extern struct tm *localtime(const time_t * /*timer*/);
extern size_t strftime(char * /*s*/, size_t /*maxsize*/,
                       const char * /*format*/, const struct tm * /*timeptr*/);

#pragma IMS_nosideeffects(clock)
#pragma IMS_nosideeffects(difftime)

#endif

/* end of time.h */
