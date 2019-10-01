/* Copyright INMOS Limited 1988,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include "linkio.h"

#define NULL_link -1

static int ActiveLink = NULL_LINK;

#define TICKS_PER_SEC         18    /* Ish */

#ifdef NEC                      /* its really a B010/B015 */
#define C012_DEFAULT_BASE   0xd0
#define C012_IDR_OFFSET        0
#define C012_ODR_OFFSET        2
#define C012_ISR_OFFSET        4
#define C012_OSR_OFFSET        6
#define C012_RESET_OFFSET      8
#define C012_ERROR_OFFSET      8
#define C012_ANALYSE_OFFSET   10
#else
#define C012_DEFAULT_BASE  0x150
#define C012_IDR_OFFSET        0
#define C012_ODR_OFFSET        1
#define C012_ISR_OFFSET        2
#define C012_OSR_OFFSET        3
#define C012_RESET_OFFSET     16
#define C012_ERROR_OFFSET     16
#define C012_ANALYSE_OFFSET   17
#endif /* NEC */

unsigned int C012_base, C012_idr, C012_odr, C012_isr, C012_osr;
unsigned int C012_reset, C012_error, C012_analyse;

/* Unfortunately for the NEC-PC we still have to guess a small delay */
static unsigned int timenow()
{
#ifdef NEC
   static unsigned int  Time=0;
   int   i;
   
#pragma loop_opt(off)
   for (i=0; i<10000; i++)
      ;
#pragma loop_opt(on)
   
   Time++;
   
   return Time;
#else
   register unsigned int far  *bios_timer = (unsigned int far *) 0x0040006c;
   
   return *bios_timer;
#endif /* NEC */
}

static unsigned int timeafter(delay)
unsigned int delay;
{
   unsigned int   nticks = (delay*TICKS_PER_SEC)/10;
   
   return (timenow() + nticks);
}

static void waitfor(delay)
unsigned int delay;
{
   delay = timeafter(delay);
   
   while (timenow() <= delay)
      ;
}

int B004OpenLink(Name)
char *Name;
{
   if (ActiveLink != NULL_link)
      return ER_LINK_CANT;

   if ((Name == NULL) || (*Name == '\0'))
      C012_base = C012_DEFAULT_BASE;
   else if ((sscanf(Name, "#%x", &C012_base) != 1) &&
            (sscanf(Name, "%x", &C012_base) != 1)) 
      return ER_LINK_BAD;

   C012_idr     = C012_base + C012_IDR_OFFSET;
   C012_odr     = C012_base + C012_ODR_OFFSET;
   C012_isr     = C012_base + C012_ISR_OFFSET;
   C012_osr     = C012_base + C012_OSR_OFFSET;
   C012_reset   = C012_base + C012_RESET_OFFSET;
   C012_error   = C012_base + C012_ERROR_OFFSET;
   C012_analyse = C012_base + C012_ANALYSE_OFFSET;

   ActiveLink = 1;

   return ActiveLink;
}

int B004CloseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   ActiveLink = NULL_LINK;

   return SUCCEEDED;
}

#ifndef B4ASM

int B004ReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   register int   n, l;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;
      
   Timeout = (int) timeafter(Timeout);

   for (n = 0; Count--; n++) {
      for (l = 0;;)
         if (inp(C012_isr) & 1) {
            *Buffer++ = inp(C012_idr) & 0xff;
            break;
         }
         else {
            if (timenow() > Timeout)
               return n;
            kbhit();
         }
   }

   return n;
}

int B004WriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   register int   n, l;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   Timeout = (int) timeafter(Timeout);
   
   for (n = 0; Count--; n++) {
      for (l = 0;;)
         if (inp(C012_osr) & 1) {
            outp(C012_odr, (*Buffer++ & 0xff));
            break;
         }
         else {
            if (timenow() > Timeout)
               return n;
            kbhit();
         }
   }

   return n;
}
#endif /* B4ASM */

int B004ResetLink(LinkId)
int LinkId;
{
   int             i;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   outp(C012_analyse, 0);       /* deassert analyse  */
   waitfor(1);
   outp(C012_reset, 0);         /* deassert reset    */
   waitfor(1);
   outp(C012_reset, 1);         /* assert reset      */
   waitfor(1);
   outp(C012_reset, 0);         /* deassert reset    */
   waitfor(1);

   return SUCCEEDED;
}

int B004AnalyseLink(LinkId)
int LinkId;
{
   int             i;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   outp(C012_analyse, 0);       /* deassert analyse  */
   waitfor(1);
   outp(C012_analyse, 1);       /* assert analyse    */
   waitfor(1);
   outp(C012_reset, 1);         /* assert reset      */
   waitfor(1);
   outp(C012_reset, 0);         /* deassert reset    */
   waitfor(1);
   outp(C012_analyse, 0);       /* deassert analyse  */
   waitfor(1);

   return SUCCEEDED;
}

int B004TestError(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (inp(C012_error) & 1) ? 0 : 1;
}

int B004TestRead(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (inp(C012_isr) & 1) ? 1 : 0;
}

int B004TestWrite(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (inp(C012_osr) & 1) ? 1 : 0;
}
