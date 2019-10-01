/* Copyright INMOS Limited 1988,1990,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>

#include "ims_bcmd.h"
#include "linkio.h"

#define NULL_LINK -1

extern int errno;

static int ActiveLink = NULL_LINK;
static int TheCurrentTimeout = -1;

int S386OpenLink(Name)
char *Name;
{
   static char     DefaultDevice[] = "/dev/bxiii0";

   /* Already open ? */
   if (ActiveLink != NULL_LINK)
      return ER_LINK_CANT;

   /* Use default name ? */
   if ((Name == NULL) || (*Name == '\0')) {
      if ((ActiveLink = open(DefaultDevice, O_RDWR)) >= 0)
         return ActiveLink;
   }
   else {
      if ((ActiveLink = open(Name, O_RDWR)) >= 0)
         return ActiveLink;
   }

   if (errno == EBUSY)
      return ER_LINK_BUSY;
   else if (errno == ENOENT)
      return ER_LINK_SYNTAX;
   else if ((errno == ENXIO) || (errno == ENODEV))
      return ER_NO_LINK;

   return ER_LINK_CANT;
}

int S386CloseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return -1;

   close(ActiveLink);
   ActiveLink = NULL_LINK;

   return SUCCEEDED;
}

int S386ReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   if (Timeout && (Timeout != TheCurrentTimeout)) {
      io.set.op = SETTIMEOUT;
      io.set.val = Timeout;
      if (ioctl(LinkId, SETFLAGS, &io, flag) == -1)
         return ER_LINK_BAD;

      TheCurrentTimeout = Timeout;
   }

   return read(LinkId, Buffer, Count);
}

int S386WriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_BAD;

   if (Timeout && (Timeout != TheCurrentTimeout)) {
      io.set.op = SETTIMEOUT;
      io.set.val = Timeout;
      if (ioctl(LinkId, SETFLAGS, &io, flag) == -1)
         return ER_LINK_BAD;

      TheCurrentTimeout = Timeout;
   }

   return write(LinkId, Buffer, Count);
}

int S386ResetLink(LinkId)
int LinkId;
{
   int             flag;
   union B008_IO   io;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   io.set.op = RESET;
   if (ioctl(LinkId, SETFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return SUCCEEDED;
}

int S386AnalyseLink(LinkId)
int LinkId;
{
   int             flag;
   union B008_IO   io;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   io.set.op = ANALYSE;

   if (ioctl(LinkId, SETFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return SUCCEEDED;
}

int S386TestError(LinkId)
int LinkId;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (ioctl(LinkId, READFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return (int) io.status.error_f;
}

int S386TestRead(LinkId)
int LinkId;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (ioctl(LinkId, READFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return (int) io.status.read_f;
}

int S386TestWrite(LinkId)
int LinkId;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (ioctl(LinkId, READFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return (int) io.status.write_f;
}

int SetDma(LinkId, Mode)
int LinkId;
char Mode;
{
   union B008_IO   io;
   int             flag;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Mode == 'r')
      io.set.op = SETREADDMA;
   else if (Mode == 'w')
      io.set.op = SETWRITEDMA;
   else if (Mode == 'n')
      io.set.op = RESETDMA;
   else
      return ER_LINK_BAD;

   if (ioctl(LinkId, SETFLAGS, &io, flag) == -1)
      return ER_LINK_BAD;

   return SUCCEEDED;
}
