/*------------------------------------------------------------------------------
--
-- File    : metlnkio.c
--     switching link module - conforms exactly to linkio specification
--                             but provides full connection manager functionality
--
-- Copyright 1990, 1991 INMOS Limited
--
-- Date    : 3/26/91
-- Version : 1.2
--
-- 06/06/90 - dave edwards
--   originated
-- 04/09/90 - dave edwards
--   updated to conform to connection mgr spec as agreed
-- 03/12/90 - dave edwards
--   updated to include tcplinkio module
-- 04/12/90 - dave edwards
--   updated debug/info bits
-- 06/12/90 - dave edwards
--   made resource names case insensitive
-- 15/02/91 - dave edwards 
--   fixed remote access bug
-- 18/02/91 - dave edwards
--   fixed METAmethod bug re. tcp access
-- 05/03/91 - dave edwards
--   made METAmethod non-static
-- 06/03/91 - dave edwards
--   made link method value be an int based on old iserver board values
-- 19/03/91 - dave edwards 
--   added sccs id stuff
-- 13/10/92 - stuart menefy
--   added checks to LOPS_Open to ensure TCP installed on PC
--
------------------------------------------------------------------------------*/

/* CMSIDENTIFIER */
static char *CMS_Id = "PRODUCT:ITEM.VARIANT-TYPE;0(DATE)";

#include <stdio.h>
#include <ctype.h>

#include "types.h"
#include "opserror.h"
#include "conlib.h"
#include "debug.h"
#include "lmethod.h"

#ifdef VMS
#include "linkio.h"
#else
#include "linkio.h"
#endif

#ifdef VMS
#include <string.h>
#else
#ifdef MSDOS
#include <string.h>
#else
#include <strings.h>
#endif
#endif

#ifdef PCTCP
#include <pctcp/syscalls.h>
#endif


/***
**** exported variables
***/
BOOL METAsearch_database = TRUE;
int METAmethod = HW_X;

/**
 ** imports
 **/

/* from lmethod.c */
extern char *LMethodNames[];
extern int LMethodValues[];

/**
 ** internal variables
 **/

/***
**** internal functions
***/
static int Undefined ()
{
  (void) fprintf(stderr, "***FATAL ERROR : metlnkio -\n####undefined routine####\n");
  return (-1);
}

/***
**** setup pointers to functions
***/

struct VECTOR {
  int (*function)();
};                                        

BOOL   method_isavailable[MAX_LMETHODS];
struct VECTOR openlink_vector[MAX_LMETHODS];
struct VECTOR closelink_vector[MAX_LMETHODS];
struct VECTOR readlink_vector[MAX_LMETHODS];
struct VECTOR writelink_vector[MAX_LMETHODS];
struct VECTOR resetlink_vector[MAX_LMETHODS];
struct VECTOR analyselink_vector[MAX_LMETHODS];
struct VECTOR testerror_vector[MAX_LMETHODS];
struct VECTOR testread_vector[MAX_LMETHODS];
struct VECTOR testwrite_vector[MAX_LMETHODS];

#ifdef SUN3
#define SUN3OR4 cowabunga
#endif

#ifdef SUN4
#define SUN3OR4 cowabunga
#endif

#ifdef LNKtcp
extern int TCPOpenLink ();
extern int TCPCloseLink ();
extern int TCPReadLink ();
extern int TCPWriteLink ();
extern int TCPResetLink ();
extern int TCPAnalyseLink ();
extern int TCPTestError ();
extern int TCPTestRead ();
extern int TCPTestWrite ();
#endif

static BOOL StringCaseCmp (s1, s2)
char *s1, *s2;
{
  int i = 0;
  char c1, c2;

  /* if one arg is NUL strings are not equal */
  if ((s1[0] == NUL) ^ (s2[0] == NUL)) {
    return (FALSE);
  }
  
  while ( (s1[i] != NUL) && (s2[i] != NUL) ) {
    c1 = s1[i];
    if ( isalpha(c1) && isupper(c1) ) {
      c1 = tolower(c1);
    }
    
    c2 = s2[i];
    if ( isalpha(c2) && isupper(c2) ) {
      c2 = tolower(c2);           
    }
    
    if (c1 != c2) {
      return (FALSE);
    } else {
      i++;
    }
  }
  
  if ((s1[i] == NUL) && (s2[i] == NUL)){
    return (TRUE);            
  } else {
    return (FALSE);
  }
}

/***
**** exported functions (see linkio spec)
***/
int OpenLink (name)
char *name;
{

  char internal_resource[65];
  char internal_machine[129];
  char linkname[66];
  char machine[129];
  int result, i, j;
  BOOL search, found_but_unopened, contains_at, quoted_thismachine, local_resource;
  
#define HOSTNAMELEN 65
  char hostname[HOSTNAMELEN];

  /* setup pointers to functions */
  for (i = 0; i < MAX_LMETHODS; i++) {
    method_isavailable[i] = FALSE;
    openlink_vector[i].function = Undefined;
    closelink_vector[i].function = Undefined;
    readlink_vector[i].function = Undefined;
    writelink_vector[i].function = Undefined;
    resetlink_vector[i].function = Undefined;
    analyselink_vector[i].function = Undefined;
    testerror_vector[i].function = Undefined;
    testread_vector[i].function = Undefined;
    testwrite_vector[i].function = Undefined;
  }
    
      
#ifdef SUN3OR4

#ifdef LNKb011
  method_isavailable[B011] = TRUE;
  openlink_vector[B011].function    = B011OpenLink;
  closelink_vector[B011].function   = B011CloseLink;
  readlink_vector[B011].function    = B011ReadLink;
  writelink_vector[B011].function   = B011WriteLink;
  resetlink_vector[B011].function   = B011ResetLink;
  analyselink_vector[B011].function = B011AnalyseLink;
  testerror_vector[B011].function   = B011TestError;
  testread_vector[B011].function    = B011TestRead;
  testwrite_vector[B011].function   = B011TestWrite;
#endif

#ifdef LNKb014
  method_isavailable[B014] = TRUE;
  openlink_vector[B014].function    = B014OpenLink;
  closelink_vector[B014].function   = B014CloseLink;
  readlink_vector[B014].function    = B014ReadLink;
  writelink_vector[B014].function   = B014WriteLink;
  resetlink_vector[B014].function   = B014ResetLink;
  analyselink_vector[B014].function = B014AnalyseLink;
  testerror_vector[B014].function   = B014TestError;
  testread_vector[B014].function    = B014TestRead;
  testwrite_vector[B014].function   = B014TestWrite;
#endif
    
#ifdef LNKb016
  method_isavailable[B016] = TRUE;
  openlink_vector[B016].function    = B016OpenLink;
  closelink_vector[B016].function   = B016CloseLink;
  readlink_vector[B016].function    = B016ReadLink;
  writelink_vector[B016].function   = B016WriteLink;
  resetlink_vector[B016].function   = B016ResetLink;
  analyselink_vector[B016].function = B016AnalyseLink;
  testerror_vector[B016].function   = B016TestError;
  testread_vector[B016].function    = B016TestRead;
  testwrite_vector[B016].function   = B016TestWrite;
#endif
    
#ifdef LNKtcp
  method_isavailable[TCP_LINKOPS] = TRUE;
  openlink_vector[TCP_LINKOPS].function     = TCPOpenLink;
  closelink_vector[TCP_LINKOPS].function    = TCPCloseLink;
  readlink_vector[TCP_LINKOPS].function     = TCPReadLink;
  writelink_vector[TCP_LINKOPS].function    = TCPWriteLink;
  resetlink_vector[TCP_LINKOPS].function    = TCPResetLink;
  analyselink_vector[TCP_LINKOPS].function  = TCPAnalyseLink;
  testerror_vector[TCP_LINKOPS].function    = TCPTestError;
  testread_vector[TCP_LINKOPS].function     = TCPTestRead;
  testwrite_vector[TCP_LINKOPS].function    = TCPTestWrite;
#endif
#endif /* SUN3OR4 */
    
#ifdef SUN386
#ifdef S386
  method_isavailable[B008] = TRUE;
  openlink_vector[B008].function    = S386OpenLink;
  closelink_vector[B008].function   = S386CloseLink;
  readlink_vector[B008].function    = S386ReadLink;
  writelink_vector[B008].function   = S386WriteLink;
  resetlink_vector[B008].function   = S386ResetLink;
  analyselink_vector[B008].function = S386AnalyseLink;
  testerror_vector[B008].function   = S386TestError;
  testread_vector[B008].function    = S386TestRead;
  testwrite_vector[B008].function   = S386TestWrite;
#endif

#ifdef LNKtcp
  method_isavailable[TCP_LINKOPS] = TRUE;
  openlink_vector[TCP_LINKOPS].function     = TCPOpenLink;
  closelink_vector[TCP_LINKOPS].function    = TCPCloseLink;
  readlink_vector[TCP_LINKOPS].function     = TCPReadLink;
  writelink_vector[TCP_LINKOPS].function    = TCPWriteLink;
  resetlink_vector[TCP_LINKOPS].function    = TCPResetLink;
  analyselink_vector[TCP_LINKOPS].function  = TCPAnalyseLink;
  testerror_vector[TCP_LINKOPS].function    = TCPTestError;
  testread_vector[TCP_LINKOPS].function     = TCPTestRead;
  testwrite_vector[TCP_LINKOPS].function    = TCPTestWrite;
#endif
#endif /* SUN386 */

#ifdef PC
#ifdef LNKb004
  method_isavailable[B004] = TRUE;
  openlink_vector[B004].function    = B004OpenLink;
  closelink_vector[B004].function   = B004CloseLink;
  readlink_vector[B004].function    = B004ReadLink;
  writelink_vector[B004].function   = B004WriteLink;
  resetlink_vector[B004].function   = B004ResetLink;
  analyselink_vector[B004].function = B004AnalyseLink;
  testerror_vector[B004].function   = B004TestError;
  testread_vector[B004].function    = B004TestRead;
  testwrite_vector[B004].function   = B004TestWrite;
#endif

#ifdef LNKb008
  method_isavailable[B008] = TRUE;
  openlink_vector[B008].function    = B008OpenLink;
  closelink_vector[B008].function   = B008CloseLink;
  readlink_vector[B008].function    = B008ReadLink;
  writelink_vector[B008].function   = B008WriteLink;
  resetlink_vector[B008].function   = B008ResetLink;
  analyselink_vector[B008].function = B008AnalyseLink;
  testerror_vector[B008].function   = B008TestError;
  testread_vector[B008].function    = B008TestRead;
  testwrite_vector[B008].function   = B008TestWrite;
#endif

#ifdef LNKtcp
  method_isavailable[TCP_LINKOPS] = TRUE;
  openlink_vector[TCP_LINKOPS].function     = TCPOpenLink;
  closelink_vector[TCP_LINKOPS].function    = TCPCloseLink;
  readlink_vector[TCP_LINKOPS].function     = TCPReadLink;
  writelink_vector[TCP_LINKOPS].function    = TCPWriteLink;
  resetlink_vector[TCP_LINKOPS].function    = TCPResetLink;
  analyselink_vector[TCP_LINKOPS].function  = TCPAnalyseLink;
  testerror_vector[TCP_LINKOPS].function    = TCPTestError;
  testread_vector[TCP_LINKOPS].function     = TCPTestRead;
  testwrite_vector[TCP_LINKOPS].function    = TCPTestWrite;
#endif
#endif /* SUN386 */

#ifdef VAX
#ifdef LNKqt0
  method_isavailable[QT0] = TRUE;
  openlink_vector[QT0].function    = QT0OpenLink;
  closelink_vector[QT0].function   = QT0CloseLink;
  readlink_vector[QT0].function    = QT0ReadLink;
  writelink_vector[QT0].function   = QT0WriteLink;
  resetlink_vector[QT0].function   = QT0ResetLink;
  analyselink_vector[QT0].function = QT0AnalyseLink;
  testerror_vector[QT0].function   = QT0TestError;
  testread_vector[QT0].function    = QT0TestRead;
  testwrite_vector[QT0].function   = QT0TestWrite;
#endif

#ifdef LNKtcp
  method_isavailable[TCP_LINKOPS] = TRUE;
  openlink_vector[TCP_LINKOPS].function     = TCPOpenLink;
  closelink_vector[TCP_LINKOPS].function    = TCPCloseLink;
  readlink_vector[TCP_LINKOPS].function     = TCPReadLink;
  writelink_vector[TCP_LINKOPS].function    = TCPWriteLink;
  resetlink_vector[TCP_LINKOPS].function    = TCPResetLink;
  analyselink_vector[TCP_LINKOPS].function  = TCPAnalyseLink;
  testerror_vector[TCP_LINKOPS].function    = TCPTestError;
  testread_vector[TCP_LINKOPS].function     = TCPTestRead;
  testwrite_vector[TCP_LINKOPS].function    = TCPTestWrite;
#endif
#endif /* VAX */

  METAmethod = HW_X;
   
  if (METAsearch_database == TRUE) {
    /* initialise database search, setup resource name */
    if ((name == NULL) || (*name == NUL)) {
      DebugMessage (fprintf (stderr, "Debug       : null resource name given\n") );
      ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
      return (ER_LINK_SYNTAX);
    }
    
    /**
     ** parse resource name into separate internal_resource
     ** and internal_machine parts
    **/
    {
      BOOL strip_resource, strip_machine;
      
      internal_resource[0] = NUL;
      internal_machine[0] = NUL;
      
      strip_resource = TRUE;
      strip_machine = FALSE;
      contains_at = FALSE;
      i = 0;
      while (strip_resource == TRUE) {
        if (i > 64) {                                 
          DebugMessage (fprintf (stderr, "Debug       : resource name too long\n") );
          ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
          return (ER_LINK_SYNTAX);
        }
        if (name[i] == NUL) {
          internal_resource[i] = NUL;
          if (i < 1) {
            DebugMessage (fprintf (stderr, "Debug       : null resource name given\n") );
            ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
            return (ER_LINK_SYNTAX);
          } else {
            strip_resource = FALSE; 
          }
          
        } else {
          if (name[i] == '@') {
            if (i < 1) {
              DebugMessage (fprintf (stderr, "Debug       : resource name before @\n") );
              ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
              return (ER_LINK_SYNTAX);
            } else {
              internal_resource[i] = NUL;
              strip_resource = FALSE;
              strip_machine = TRUE;
              contains_at = TRUE;
              i++;
            }
          
          } else {
            internal_resource[i] = name[i];
            i++;
          } 
        }
      }
     
      if (strip_machine == FALSE) {
      } else {
        j = 0;
        while (strip_machine == TRUE) {
          if (j > 64) {
            DebugMessage (fprintf (stderr, "Debug       : machine name too long\n") );
            ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
            return (ER_LINK_SYNTAX);
          }
          if (name[i] == NUL) {
            internal_machine[j] = NUL;
            if (j < 1) {                                  
               DebugMessage (fprintf (stderr, "Debug       : null resource name given\n") );
               ErrorMessage (fprintf (stderr, "Error       : invalid resource name\n") );
              return (ER_LINK_SYNTAX);
            } else {
              internal_machine[j] = NUL;
              strip_machine = FALSE;
            }
            
          } else {
            internal_machine[j] = name[i];
            i++;
            j++;
          }
        }
      }
    }
    
    /**
     ** see if given resource name refers just to this
     ** local machine
     **
    **/
#ifdef LNKtcp
    /**
     ** deduce name of this machine
     ** Only call gethostname() if we have network software installed.
     **/
#ifdef PCNFS
    if (is_pc_nfs_installed()) {
#endif
#ifdef PCTCP
    if (vec_search()) {
#endif
      if (gethostname(hostname, HOSTNAMELEN) < 0) {
         ErrorMessage (fprintf (stderr, "Error       : module[metlnkio.c], function [OpenLink]\n -> gethostname failed\n") );
         return (ER_LINK_SOFT);
       }
#if defined(PCNFS) || defined(PCTCP)
    }
    else {
      if ((contains_at == TRUE) && (StringCaseCmp (internal_machine, "localhost") == FALSE)) {
        ErrorMessage (fprintf (stderr, "Error       : module[metlnkio.c], function [OpenLink]\n -> can't access remote [%s] TCP not installed\n", name ) );
        return (ER_LINK_SOFT);
      }
      (void) strcpy (hostname, "localhost");
    }
#endif
#else
    /* no tcp resource so setup default name */
    strcpy (hostname, "localhost");
#endif /* LNKtcp */

    if (( StringCaseCmp (internal_machine, "localhost") == TRUE) || ( StringCaseCmp (internal_machine, hostname) == TRUE)) {
      quoted_thismachine = TRUE;
      DebugMessage (fprintf (stderr, "Debug       : search for resource on this machine only\n") );
    } else {
      quoted_thismachine = FALSE;
      DebugMessage (fprintf (stderr, "Debug       : search for resource on any machine\n") );
    }   
    
    if (contains_at == TRUE) {
      if (quoted_thismachine == FALSE) {
#ifdef LNKtcp
        /**
         ** machine name given quotes another machine so try
         ** opening a connection to it via TCP
        **/
        InfoMessage ( fprintf (stderr, "Info        : attempting TCP linkio open to resource [%s] ...\n", name) );
        if (method_isavailable[TCP_LINKOPS] == FALSE) {
          InfoMessage ( fprintf (stderr, "Warning          : module[metlnkio.c], function [OpenLink]\n -> not compiled to drive a [%s] resource\n", LMethodNames[TCP_LINKOPS]) );
          return (ER_NO_LINK);
        } else {
          result = (*openlink_vector[TCP_LINKOPS].function) (name);
          if (result >= 0) {
            METAmethod = TCP_LINKOPS;
            return (result);
          } else {
            return (result);
          }
        }
#else
        InfoMessage ( fprintf (stderr, "Info        : can't access [%s] as not compiled to use TCP\n", name) );
        ErrorMessage (fprintf (stderr, "Error       : can't access resource [%s]\n", name) );
        return (ER_LINK_SOFT);
#endif /* LNKtcp */
      } else {
        (void) strcpy (internal_machine, hostname);
      }
    } else {
      /* no machine name quoted so look for local or remote resource */
    }
      
    result = CM_InitSearch (internal_resource, internal_machine, hostname);
    switch (result) {
      case STATUS_NOERROR:
        break;
        
      case STATUS_BAD_OPERATION:
        ErrorMessage (fprintf (stderr, "%s", conlib_errorstring) );
        return (ER_LINK_SOFT);
        break;
        
      default:
        ErrorMessage ( fprintf (stderr, "%s", conlib_errorstring) );
        return (result);
        break;
    }
    DebugMessage (fprintf (stderr, "Debug       : initialised database search\n") );
    
  }
  
  search = TRUE;
  found_but_unopened = FALSE;
  
  while (search == TRUE) {
    /**
     ** decide whether to search database for an entry
    **/
    if (METAsearch_database == FALSE) {
      /* dont search database, just read off current values */
      search = FALSE; /* only do 1 check */
    } else {
      /* perform resource search */
      result = CM_DoSearch ();
      if (result != STATUS_NOERROR) {
        ErrorMessage (fprintf(stderr, "%s", conlib_errorstring) );
        switch (result) {
          case STATUS_BAD_TARGET_NAME:
            (void) CM_EndSearch ();
            ErrorMessage (fprintf (stderr, "%s", conlib_errorstring) );
            if (found_but_unopened == TRUE) {
              ErrorMessage (fprintf(stderr, "Error       : can't access resource [%s]\n", name) );
            } else {
              ErrorMessage (fprintf (stderr, "Error       : can't find resource [%s]\n", name) );
            } 
            return (ER_LINK_BAD);
            break;
          
          case STATUS_BAD_OPERATION:
            (void) CM_EndSearch ();
            return (ER_LINK_SOFT);
            break;
            
          default:
            (void) CM_EndSearch ();
            ErrorMessage (fprintf (stderr, "%s", conlib_errorstring) );
            ErrorMessage (fprintf (stderr, "Error       : called by module [metlnkio.c], function [OpenLink]\n") );
            return (ER_LINK_SOFT);
            break;                
         }
      }
    }
    
    /**
     ** a match has now been made, check
     ** its fields & attempt an open 
    **/
    if (CM_GetIsWorking () == TRUE) {
      METAmethod = CM_GetLinkMethod ();
      (void) CM_GetMachine (machine);
      (void) CM_GetLinkName (linkname);
      
      if (method_isavailable [METAmethod] == FALSE) {
        InfoMessage ( fprintf (stderr, "Warning     : connection database weirdness, at line [%d]\n -> not compiled to drive a [%s] resource\n", CM_GetLineNumber (), LMethodNames[METAmethod]) );
        return (ER_LINK_SYNTAX);
      } else {
        /**
         ** deduce whether to access by TCP or by local driver.
         ** Again, we only call gethostname() if we can't be sure its a local resource
         **/
        if ( StringCaseCmp (machine, "localhost") == TRUE) {
          local_resource = TRUE;
        } else {
          /**
           ** I suppose we can call gethostname() now !
           **/
          if (gethostname(hostname, HOSTNAMELEN) < 0) {
            ErrorMessage (fprintf (stderr, "Error       : module[metlnkio.c], function [OpenLink]\n -> gethostname failed\n") );
            return (ER_LINK_SOFT);
          }
          
          if (StringCaseCmp (machine, hostname) == TRUE) {
            local_resource = TRUE;
          } else {
            local_resource = FALSE;
          }
        } 
      
        if ((local_resource == TRUE) && (METAmethod == TCP_LINKOPS)) {
          InfoMessage ( fprintf (stderr, "Warning     : connection database weirdness, at line [%d]\n -> can't access local resource via TCP\n", CM_GetLineNumber) );
        } else {
          /**
           ** ok so far, attempt to open connection
          **/
          found_but_unopened = TRUE;
           
          if ((METAmethod == TCP_LINKOPS) || (local_resource == FALSE) ){
#ifdef LNKtcp
            char full_name[129];
             
            strcpy (full_name, name);
            strcat (full_name, "@");
            strcat (full_name, machine);
            METAmethod = TCP_LINKOPS;
            InfoMessage ( fprintf (stderr, "Info        : attempting open to resource [%s] via method [%s]\n", full_name, LMethodNames[METAmethod]) );
            /* call underlying routine & return linkid */
            result = (*openlink_vector[METAmethod].function) (full_name);
#endif /* LNKtcp */
          } else {
            InfoMessage ( fprintf (stderr, "Info        : attempting open to resource [%s] via method [%s]\n", name, LMethodNames[METAmethod]) );
            /* call underlying routine & return linkid */
            result = (*openlink_vector[METAmethod].function) (linkname);
          }
          if (result >= 0) {
            search = FALSE;              /* opened connection ok */
          } else {
            if (METAsearch_database == TRUE) {
              found_but_unopened = TRUE; /* failed to open, try another */
            } else {
              METAmethod = HW_X;
              return (ER_LINK_CANT);    /* failed to open, return */
            }
          }
        } 
      } 
    }
  }
  
  if (METAsearch_database == TRUE) {
    (void) CM_EndSearch ();
  }
  return (result);
  
}

int CloseLink (linkid)
int linkid;
{
  int result;
  result = (*closelink_vector[METAmethod].function) (linkid);
  METAsearch_database = TRUE;
  METAmethod = HW_X;
  return (result);
}

int ReadLink (linkid, buffer, count, timeout)
int linkid;
char *buffer;
unsigned int count;
int timeout;
{
  return (*readlink_vector[METAmethod].function) (linkid, buffer, count, timeout);
}

int WriteLink (linkid, buffer, count, timeout)
int linkid;
char *buffer;
unsigned int count;
int timeout;
{
  return (*writelink_vector[METAmethod].function) (linkid, buffer, count, timeout); 
}

int ResetLink (linkid)
int linkid;
{
  return (*resetlink_vector[METAmethod].function) (linkid);
}

int AnalyseLink (linkid)
int linkid;
{
  return (*analyselink_vector[METAmethod].function) (linkid);
}

int TestError (linkid)
int linkid;
{
  return (*testerror_vector[METAmethod].function) (linkid);
}

int TestRead (linkid)
int linkid;
{
  return (*testread_vector[METAmethod].function) (linkid);
}

int TestWrite (linkid)
int linkid;
{
  return (*testwrite_vector[METAmethod].function) (linkid);
}











