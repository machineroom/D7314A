/* Copyright INMOS Limited 1988,1990,1991 */
/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <pwd.h>

#include "linkio.h"

/* #define TRACE */

extern char    *rindex();
extern caddr_t  mmap();

#define NULL_LINK -1
#define LINK_TIMEOUT 100000

#define TRUE      1
#define FALSE     0

#define HOLDTIME     100000     /* Reset & analyse hold time in microseconds */

#define LOCK_FILE_ROOT "/tmp/B011@"
#define VME_DEVICE "/dev/vme24d32"

#define DEFAULT_BASE_ADDRESS 0x800000   /* Address set on the B011 */
#define PAGESIZE 8192           /* As returned by pagesize(1) */

static struct B011Layout {
   char            d0[PAGESIZE - 32];   /* Space                   */
   char            d1[3];
   char            ResetAndError;       /* Reset and error         */
   char            d2[3];
   char            Analyse;     /* Analyse                 */
   char            d3[17];
   char            Idr;         /* Input data register     */
   char            d4;
   char            Odr;         /* Output data register    */
   char            d5;
   char            Isr;         /* Input status register   */
   char            d6;
   char            Osr;         /* Output status register  */
   char            d7;
} *B;

static int BaseAddress;
static LockFileName[32];
static int ActiveLink = NULL_LINK;
static int BoardPresent = FALSE;

static int LockBoard(Address)
int Address;
{
   char            String[128], *c;
   FILE           *LockFd;
   long int        Seconds;
   struct passwd  *pw;
   sprintf(LockFileName, "%s%X", LOCK_FILE_ROOT, Address);

   if ((LockFd = fopen(LockFileName, "r")) != NULL) {
      if (fgets(String, 127, LockFd) == NULL)
         strcpy(String, "???");
      else if ((c = rindex(String, '\n')) != NULL)
         *c = '\0';

      if (fgets(String, 99, LockFd) == NULL)
         strcpy(String, "?");
      else if ((c = rindex(String, '\n')) != NULL)
         *c = '\0';

      (void) fclose(LockFd);
      return FALSE;
   }

   if ((LockFd = fopen(LockFileName, "w")) == NULL)
      return FALSE;
   else {
      pw = getpwnam(cuserid(NULL));
      (void) time(&Seconds);
      fprintf(LockFd, "%s (%s)\n%s\n", cuserid(NULL), pw->pw_gecos, ctime(&Seconds));
      (void) fclose(LockFd);
      chown(LockFileName, getuid(), getgid());
   }

   return TRUE;
}

static int UnlockBoard()
{
   FILE           *LockFd;

   if ((LockFd = fopen(LockFileName, "r")) == NULL)
      return FALSE;
   else {
      (void) fclose(LockFd);
      if (unlink(LockFileName))
         return FALSE;
   }
   
   return TRUE;
}

static void BusErrorHandler()
{
   BoardPresent = FALSE;
   UnlockBoard();
}

static int MapBoard(Offset)
int Offset;
{
   int             VmeFd;
   char            HaveNoVolatileConstants;

   if ((VmeFd = open(VME_DEVICE, O_RDWR)) == -1) {
#ifdef TRACE
      printf("B011: Cannot open VME device %s\n", VME_DEVICE);
#endif
      return FALSE;
   }

   if ((B = (struct B011Layout *) valloc(sizeof(*B))) == NULL) {
#ifdef TRACE
      printf("B011: Cannot valloc memory\n");
#endif
      return FALSE;
   }

   if ((int) (B = (struct B011Layout *) mmap(B, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, VmeFd, Offset)) == -1) {
#ifdef TRACE
      printf("B011: Cannot mmap board addresses\n");
#endif
      (void) close(VmeFd);
      return FALSE;
   }

   BoardPresent = TRUE;
   signal(SIGBUS, BusErrorHandler);
   HaveNoVolatileConstants = B->ResetAndError;
   signal(SIGBUS, SIG_IGN);

   return BoardPresent;
}

int B011OpenLink(Name)
char *Name;
{
   FILE           *LockFd;
   char            String[100];
   char           *c;

   if (ActiveLink != NULL_LINK)
      return ER_LINK_CANT;

   if ((Name == NULL) || (*Name == '\0'))
      BaseAddress = DEFAULT_BASE_ADDRESS;
   else if (sscanf(Name, "#%x", &BaseAddress) != 1 &&
            sscanf(Name, "%x", &BaseAddress) != 1)
      return ER_LINK_SYNTAX;

   if (LockBoard(BaseAddress) == FALSE)
      return ER_LINK_BUSY;

   if (MapBoard(BaseAddress + 0x200000 - PAGESIZE) == FALSE) {
      UnlockBoard();
      return ER_LINK_CANT;
   }

   if ((setreuid(-1, getuid()) != 0) || (setregid(-1, getgid()) != 0)) {
      (void) UnlockBoard();
      BoardPresent = FALSE;

      return ER_LINK_CANT;
   }
      
   ActiveLink = 1;

   return ActiveLink;
}

int B011CloseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (UnlockBoard() == FALSE)
      return ER_LINK_CANT;

   ActiveLink = NULL_LINK;
   BoardPresent = FALSE;

   return SUCCEEDED;
}

int B011ReadLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   register int    n, l;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   if (Timeout) {
      for (n = 0; Count--; n++) {
         for (l = 0; l < LINK_TIMEOUT; l++)
            if (B->Isr & 1)
               break;

         if (l == LINK_TIMEOUT)
            break;

         *Buffer = B->Idr & 0xff;
#ifdef TRACE
         printf("<%X", *Buffer);
#endif
         Buffer++;
      }
   }
   else {
      for (n = 0; Count--; n++) {
         while ((B->Isr & 1) == 0);

         *Buffer++ = B->Idr & 0xff;
      }
   }

   return n;
}

int B011WriteLink(LinkId, Buffer, Count, Timeout)
int LinkId;
char *Buffer;
unsigned int Count;
int Timeout;
{
   register int    l, n, c;

   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   if (Count < 1)
      return ER_LINK_CANT;

   c = Count;

   if (Timeout) {
      for (n = 0; c--; n++) {
         for (l = 0; l < LINK_TIMEOUT; l++)
            if (B->Osr & 1)
               break;

         if (l == LINK_TIMEOUT)
            break;

         B->Odr = *Buffer & 0xff;
#ifdef TRACE
         printf(">%X", *Buffer & 0xff);
#endif
         Buffer++;
      }
   }
   else {
      for (n = 0; Count--; n++) {
         while ((B->Osr & 1) == 0);

         B->Odr = *Buffer++ & 0xff;
      }
   }

   return n;
}

int B011ResetLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   B->Analyse = 0;              /* Deassert analyse */
   usleep(HOLDTIME);            /* wait a while     */
   B->ResetAndError = 0;        /* deassert reset   */
   usleep(HOLDTIME);
   B->ResetAndError = 1;        /* assert reset     */
   usleep(HOLDTIME);
   B->ResetAndError = 0;        /* deassert reset   */
   usleep(HOLDTIME);

   return SUCCEEDED;
}

int B011AnalyseLink(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   B->Analyse = 1;              /* Assert analyse   */
   usleep(HOLDTIME);
   B->ResetAndError = 1;        /* Assert reset     */
   usleep(HOLDTIME);
   B->ResetAndError = 0;        /* Deassert reset   */
   usleep(HOLDTIME);
   B->Analyse = 0;              /* Deassert analyse */
   usleep(HOLDTIME);

   return SUCCEEDED;
}

int B011TestError(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (B->ResetAndError & 1) ? 1 : 0;
}

int B011TestRead(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (B->Isr & 1) ? 1 : 0;
}

int B011TestWrite(LinkId)
int LinkId;
{
   if (LinkId != ActiveLink)
      return ER_LINK_BAD;

   return (B->Osr & 1) ? 1 : 0;
}
