/* Copyright INMOS Limited 1988,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include <root.h>

#include "intio.h"

#define NULL_LINK -1

static int     ActiveLink = NULL_LINK;
#define SUBSYSTEM_RESET    (0x0000000)
#define SUBSYSTEM_ANALYSE  (SUBSYSTEM_RESET + 4)
#define SUBSYSTEM_ERROR    (SUBSYSTEM_RESET)

#define PAUSE {int i; for (i=0;i<10000;i++); }

int HELIOSOpenLink(Name)
char *Name;
{
   LinkInfo       *l;
   LinkConf        Linkconf[4];
   int             i;

   if (ActiveLink != NULL_LINK)
      return ER_LINK_BAD;

   if (sscanf(Name, "%x", &ActiveLink) != 1)
      ActiveLink = 2;

   if (ActiveLink > 3 || ActiveLink < 0)
      return ER_LINK_BAD;

   l = *(GetRoot()->Links) + ActiveLink;
   if ((l->Mode == 2) && (l->State != 6))
      return ER_LINK_BUSY;

   /*
    * This is not implemented LinkData(i, &intinfo[i] )) so...
    */

   for (i = 0; i < 4; i++) {
      Linkconf[i].Flags = 0;
      Linkconf[i].Mode = 2;     /* intelligent  */
      Linkconf[i].State = 3;
      Linkconf[i].Id = i;
   }

   Linkconf[ActiveLink].Mode = 1;       /* dumb  */

   if (Reconfigure(Linkconf) < 0)
      return ER_LINK_CANT;

   return ActiveLink;
}

int HELIOSCloseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   ActiveLink = NULL_LINK;

   return SUCCEEDED;
}

int HELIOSReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (LinkIn((word) Count, LinkId, (void *) Buffer, Timeout * (OneSec / 10)) < 0)
      return ER_LINK_CANT;

   return Count;
}

int HELIOSWriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (LinkOut((word) Count, LinkId, (void *) Buffer, Timeout * (OneSec / 10)) < 0)
      return ER_LINK_CANT;

   return Count;
}

int HELIOSResetLink(LinkId)
int LinkId;
{
   int            *m;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   m = (int *) SUBSYSTEM_RESET;
   *m = 0;
   m = (int *) SUBSYSTEM_ANALYSE;
   *m = 0;
   PAUSE;
   m = (int *) SUBSYSTEM_RESET;
   *m = 1;
   PAUSE;
   m = (int *) SUBSYSTEM_RESET;
   *m = 0;
   PAUSE;

   return SUCCEEDED;
}

int HELIOSAnalyseLink(LinkId)
int LinkId;
{
   int            *m;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   m = (int *) SUBSYSTEM_ANALYSE;
   *m = 0;
   PAUSE;
   m = (int *) SUBSYSTEM_ANALYSE;
   *m = 1;
   PAUSE;
   m = (int *) SUBSYSTEM_RESET;
   *m = 1;
   PAUSE;
   m = (int *) SUBSYSTEM_RESET;
   *m = 0;
   PAUSE;
   m = (int *) SUBSYSTEM_ANALYSE;
   *m = 0;
   PAUSE;

   return SUCCEEDED;
}

int HELIOSTestError(LinkId)
int LinkId;
{
   int            *m;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   m = (int *) SUBSYSTEM_ERROR;

   return *m & 1;
}

int HELIOSTestRead(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return 0;
}

int HELIOSTestWrite(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return 0;
}
