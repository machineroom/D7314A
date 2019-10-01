/* Copyright INMOS Limited 1988,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include <dos.h>
#include <fcntl.h>

#include "ims_bcmd.h"
#include "linkio.h"

#define B008_RESET      (0)
#define B008_ANALYSE    (1)
#define B008_TIMEOUT    (2)

#define SET_FLAGS 0x03
#define READ_FLAGS 0x02

#define BINARY (32)
#define ISDEV (128)

#define DEFAULT_LINK "LINK1"
#define NULL_LINK -1

static int ActiveLink = NULL_LINK;

static void ioctl(Fd, Type, Func)
int Fd, Type;
struct IMS_IO *Func;
{
   union REGS      regs;

   regs.h.ah = 0x44;
   regs.h.al = (unsigned char) Type;
   regs.x.cx = sizeof(struct IMS_IO);
   regs.x.bx = Fd;
   regs.x.dx = (unsigned int) Func;

   int86(0x21, &regs, &regs);
}

int B008OpenLink(Name)
char *Name;
{
   union REGS      regs;

   if (ActiveLink != NULL_LINK)
      return ER_LINK_CANT;

   if ((Name == NULL) || (*Name == '\0'))
      Name = DEFAULT_LINK;

   if ((ActiveLink = open(Name, O_RDWR | O_BINARY)) < 0)
      return ER_LINK_CANT;

   regs.x.ax = 0x4400;           /* Get device info */
   regs.x.bx = ActiveLink;
   int86(0x21, &regs, &regs);

   if ((regs.h.dl & ISDEV) == 0) {
      close(ActiveLink);
      ActiveLink = NULL_LINK;
      return ER_NO_LINK;
   }

   regs.x.ax = 0x4401;           /* Set device info */
   regs.h.dh = 0;                /* set binary mode */ 
   regs.h.dl |= BINARY;
   int86(0x21, &regs, &regs);

   return ActiveLink;
}

int B008CloseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   close(ActiveLink);
   ActiveLink = NULL_LINK;

   return SUCCEEDED;
}

int B008ReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   flags.io_op = B008_TIMEOUT;
   flags.io_val = Timeout;
   ioctl(LinkId, SET_FLAGS, &flags);

   return read(LinkId, Buffer, Count);
}

int B008WriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   flags.io_op = B008_TIMEOUT;
   flags.io_val = Timeout;
   ioctl(LinkId, SET_FLAGS, &flags);

   return write(LinkId, Buffer, Count);
}

int B008ResetLink(LinkId)
int LinkId;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   flags.io_op = B008_RESET;
   ioctl(LinkId, SET_FLAGS, &flags);

   return SUCCEEDED;
}

int B008AnalyseLink(LinkId)
int LinkId;
{
   struct IMS_IO  flags;
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   flags.io_op = B008_ANALYSE;
   ioctl(LinkId, SET_FLAGS, &flags);

   return SUCCEEDED;
}

int B008TestError(LinkId)
int LinkId;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   ioctl(LinkId, READ_FLAGS, &flags);

   return (flags.io_val & 0x01);
}

int B008TestRead(LinkId)
int LinkId;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   ioctl(LinkId, READ_FLAGS, &flags);

   return (flags.io_val & 0x08);
}

int B008TestWrite(LinkId)
int LinkId;
{
   struct IMS_IO  flags;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   ioctl(LinkId, READ_FLAGS, &flags);

   return (flags.io_val & 0x04);
}
