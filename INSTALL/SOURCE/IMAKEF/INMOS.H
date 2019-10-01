/* CMSIDENTIFIER
   PLAY:INMOS_H@398.AAAA-FILE;3(14-DEC-92)[FROZEN] */
/*****************************************************************************
 *
 *  Object Name : inmos.h
 *  Revision    : 1
 *
 *  Copyright (c) Inmos Ltd, 1987
 *  All rights reserved.
 *
 *  DESCRIPTION : A standard header for C programs
 *
 *  HISTORY : Created by Ray Knagg 1st June 1988
 *
 *****************************************************************************/

/*
-- ----------------------------------------------------------------------------
--
--     MSC    - Compiling with Microsoft C to run under DOS.
--     VMS    - Compiling with VAX/VMS C to run under VMS.
--     LLL    - Compiling with 3L C to run on a transputer.
--     SUN3   - Compiling with SUN/UNIX C to run under UNIX.
--     SUN4   - Compiling with SUN/UNIX C to run under UNIX.
--     ICC    - Compiling with ICC to run on a transputer.
--     HELIOS - Compiling with HELIOS C to run under HELIOS.
--     WATCOM - Compiling with WATCOM C\386 v9.0 to run on 386/486 PC
--
-- ----------------------------------------------------------------------------
*/

#ifndef MSC
#ifndef VMS
#ifndef LLL
#ifndef SUN3
#ifndef SUN4
#ifndef ICC
#ifndef HELIOS
#ifndef WATCOM
error NO target host machine specified
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef MSC
#define _FOPEN_FLAGS

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 long int

#define ERROR_RETURN 1

#define DELETE(name) unlink(name)
#endif

#ifdef VMS
#define _FOPEN_FLAGS

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 42

#define DELETE(name) delete(name)
#endif

#ifdef LLL
#define _FOPEN_FLAGS

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) remove(name)
#endif

#ifdef SUN3
#define _FOPEN_NONE

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) unlink(name)
#endif

#ifdef SUN4
#define _FOPEN_NONE

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) unlink(name)
#endif


#ifdef ICC
#define _FOPEN_NONE

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) unlink(name)
#endif

#ifdef HELIOS
#define _FOPEN_NONE

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) unlink(name)
#endif

#ifdef WATCOM
#define _FOPEN_FLAGS

#define INT   int
#define CHAR  char
#define VOID  void
#define BYTE  unsigned char
#define BOOL  int
#define INT32 int

#define ERROR_RETURN 1

#define DELETE(name) remove(name)
#endif

/*
-- ----------------------------------------------------------------------------
--
--     _FOPEN_NONE  - no method of specifying access method.
--     _FOPEN_FMODE - access method specified using external _fmode variable.
--     _FOPEN_FLAGS - access method specified using no flag or the 'b' flag.
--
-- ----------------------------------------------------------------------------
*/

#ifndef _FOPEN_NONE
#ifndef _FOPEN_FMODE
#ifndef _FOPEN_FLAGS
error NO access method type specified
#endif
#endif
#endif

#ifdef _FOPEN_NONE
#define FOPEN_READ_TEXT(name, stream)   stream = fopen(name, "r")
#define FOPEN_READ_BINARY(name, stream) stream = fopen(name, "r")

#define FOPEN_WRITE_TEXT(name, stream)   stream = fopen(name, "w")
#define FOPEN_WRITE_BINARY(name, stream) stream = fopen(name, "w")

#define FOPEN_APPEND_TEXT(name, stream)   stream = fopen(name, "a")
#define FOPEN_APPEND_BINARY(name, stream) stream = fopen(name, "a")

#define FOPEN_READ_UPDATE_TEXT(name, stream)   stream = fopen(name, "r+")
#define FOPEN_READ_UPDATE_BINARY(name, stream) stream = fopen(name, "r+")

#define FOPEN_WRITE_UPDATE_TEXT(name, stream)   stream = fopen(name, "w+")
#define FOPEN_WRITE_UPDATE_BINARY(name, stream) stream = fopen(name, "w+")

#define FOPEN_APPEND_UPDATE_TEXT(name, stream)   stream = fopen(name, "a+")
#define FOPEN_APPEND_UPDATE_BINARY(name, stream) stream = fopen(name, "a+")
#endif

#ifdef _FOPEN_FMODE
#define FOPEN_READ_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "r");\
    _fmode = saved_fmode;\
}
#define FOPEN_READ_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "r");\
    _fmode = saved_fmode;\
}

#define FOPEN_WRITE_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "w");\
    _fmode = saved_fmode;\
}
#define FOPEN_WRITE_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "w");\
    _fmode = saved_fmode;\
}

#define FOPEN_APPEND_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "a");\
    _fmode = saved_fmode;\
}
#define FOPEN_APPEND_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "a");\
    _fmode = saved_fmode;\
}

#define FOPEN_READ_UPDATE_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "r+");\
    _fmode = saved_fmode;\
}
#define FOPEN_READ_UPDATE_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "r+");\
    _fmode = saved_fmode;\
}

#define FOPEN_WRITE_UPDATE_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "w+");\
    _fmode = saved_fmode;\
}
#define FOPEN_WRITE_UPDATE_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "w+");\
    _fmode = saved_fmode;\
}

#define FOPEN_APPEND_UPDATE_TEXT(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_TEXT;\
    stream = fopen(name, "a+");\
    _fmode = saved_fmode;\
}
#define FOPEN_APPEND_UPDATE_BINARY(name, stream) \
{\
    INT saved_fmode;\
    EXTERNAL INT _fmode;\
    saved_fmode = _fmode;\
    _fmode = O_BINARY;\
    stream = fopen(name, "a+");\
    _fmode = saved_fmode;\
}
#endif

#ifdef _FOPEN_FLAGS
#define FOPEN_READ_TEXT(name, stream)   stream = fopen(name, "r")
#define FOPEN_READ_BINARY(name, stream) stream = fopen(name, "rb")

#define FOPEN_WRITE_TEXT(name, stream)   stream = fopen(name, "w")
#define FOPEN_WRITE_BINARY(name, stream) stream = fopen(name, "wb")

#define FOPEN_APPEND_TEXT(name, stream)   stream = fopen(name, "a")
#define FOPEN_APPEND_BINARY(name, stream) stream = fopen(name, "ab")

#define FOPEN_READ_UPDATE_TEXT(name, stream)   stream = fopen(name, "r+")
#define FOPEN_READ_UPDATE_BINARY(name, stream) stream = fopen(name, "r+b")

#define FOPEN_WRITE_UPDATE_TEXT(name, stream)   stream = fopen(name, "w+")
#define FOPEN_WRITE_UPDATE_BINARY(name, stream) stream = fopen(name, "w+b")

#define FOPEN_APPEND_UPDATE_TEXT(name, stream)   stream = fopen(name, "a+")
#define FOPEN_APPEND_UPDATE_BINARY(name, stream) stream = fopen(name, "a+b")
#endif

#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif

#define MAX_BLOCK_SIZE  2048
#define MAX_STRING_SIZE  256

#define PUBLIC
#define PRIVATE  static
#define EXTERNAL extern
#define FORWARD  extern

/* #define LLL */   /* Compiling with the 3L compiler to run on a transputer */
/* #define VMS  */   /* Compiling to run on a VAX */
/* #define SUN3 */   /* Compiling to run on a SUN under UNIX */
/* #define MSC  */   /* Compiling with Microsoft C to run under PCDOS */

#ifdef ANSI
extern void *malloc(INT x);
extern void *calloc(INT x, INT n);
extern void *realloc(void *x,INT n);
extern int  free(void *x);
extern int  exit(INT n);
extern int  strlen(char *str);
extern char *strcat(char *new, char *old);
extern char *strcpy(char *new, char *old);
extern char *strncpy(char *str1, char *str2, INT n);
extern int  strcmp(char *str1, char *str2);
extern int  strncmp(char *str1, char *str2, INT n);
extern char *strrchr(char *str, char ch);
#else
extern char *malloc();
extern char *calloc();
extern char *realloc();
extern int  free();
extern int  exit();
extern int  strlen();
extern char *strcat();
extern char *strcpy();
extern char *strncpy();
extern int  strcmp();
extern int  strncmp();
extern char *strrchr();
#endif

