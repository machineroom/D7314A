/* Copyright INMOS Limited 1988,1990,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#ifdef VMS

#include <descrip.h>
#include <ssdef.h>
#include <iodef.h>
#include <stdio.h>

#include "linkio.h"

#define RESET_BIT          0x0004
#define ANALYSE_BIT        0x0002
#define NO_BITS_SET        0x0000

#define DMA_THRESHOLD 2

char LinkName[128] = "sys$transputer";

static unsigned short chan;
struct dsc$descriptor_s _Link, *Link = &_Link;

static struct io_block {
   short           status;
   short           count;
   int             qt0_regs;
}               Io;

int QT0OpenLink(Name)
char *Name;
{
   int             status;

   if ((Name != NULL) && (*Name))
      strcpy(&LinkName[0], Name);

   Link->dsc$w_length = strlen(&LinkName[0]);
   Link->dsc$b_dtype = DSC$K_DTYPE_T;
   Link->dsc$b_class = DSC$K_CLASS_S;
   Link->dsc$a_pointer = &LinkName[0];

   status = sys$alloc(Link, 0, 0, 0, 0);
   if ((status != SS$_NORMAL) && (status != SS$_DEVALRALLOC))
      return ER_LINK_CANT;

   if (sys$assign(Link, &chan, 0, 0) != SS$_NORMAL)
      return ER_LINK_CANT;

   return (int) chan;
}

int QT0CloseLink(LinkId)
int LinkId;
{
   if (LinkId != (int) chan)
      return ER_LINK_BAD;
      
   if (!(sys$dassgn(chan) & 1))
      return ER_LINK_BAD;
      
   if (!(sys$dalloc(Link, 0) & 1))
      return ER_LINK_BAD;

   return SUCCEEDED;
}

int QT0ReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   int            QtTimeout = (Timeout/10)+1;
   int            res;
   
   if (LinkId != (int) chan)
      return ER_LINK_BAD;

   if (Count > DMA_THRESHOLD)
      res = sys$qiow(0, chan, (IO$_READVBLK | IO$M_TIMED), &Io, 0, 0, 
                                      Buffer, Count, QtTimeout, 0, 0, 0);                                    
   else    
      res = sys$qiow(0, chan, (IO$_READVBLK | IO$M_WORD | IO$M_TIMED), 
                           &Io, 0, 0, Buffer, Count, QtTimeout, 0, 0, 0);                          
                           
   if ((!(res & 1)) || (!(Io.status & 1))) {
      if ((Io.status == SS$_TIMEOUT) && (Io.count == 0))
         return 0;

      return ER_LINK_CANT;
   }

   return Io.count;
}

int QT0WriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   int            QtTimeout = (Timeout/10)+1;
   int            res;

   if (LinkId != (int) chan)
      return ER_LINK_BAD;

   if (Count > DMA_THRESHOLD)
      res = sys$qiow(0, chan, (IO$_WRITEVBLK | IO$M_TIMED), &Io, 0, 0, Buffer, Count, QtTimeout, 0, 0, 0);
   else
      res = sys$qiow(0, chan, (IO$_WRITEVBLK | IO$M_WORD | IO$M_TIMED), &Io, 0, 0, Buffer, Count, QtTimeout, 0, 0, 0);
      
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   return Io.count;
}

int QT0ResetLink(LinkId)
int LinkId;
{
   int            res;

   if (LinkId != (int) chan)
      return ER_LINK_BAD;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    RESET_BIT, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    NO_BITS_SET, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   return SUCCEEDED;
}

int QT0AnalyseLink(LinkId)
int LinkId;
{
   int            res;

   if (LinkId != (int) chan)
      return ER_LINK_BAD;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    ANALYSE_BIT, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    RESET_BIT|ANALYSE_BIT, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    ANALYSE_BIT, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   res = sys$qiow(0, chan, IO$_SETMODE, &Io, 0, 0, 
                                    NO_BITS_SET, 0, 0, 0, 0, 0);                                 
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   return SUCCEEDED;
}

int QT0TestError(LinkId)
int LinkId;
{
   int            res;

   res = sys$qiow(0, chan, IO$_SENSEMODE, &Io, 0, 0, 0, 0, 0, 0, 0, 0);
   if ((!(res & 1)) || (!(Io.status & 1)))
      return ER_LINK_CANT;

   if (Io.qt0_regs & 0x00010000)
      return 0;

   return 1;
}

int QT0TestRead(LinkId)
int LinkId;
{
   return 0;
}

int Qt0TestWrite(LinkId)
int LinkId;
{
   return 0;
}

#endif /* VMS  */
