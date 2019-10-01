/* Copyright INMOS Limited 1988,1990,1991 */

/* CMSIDENTIFIER */
/* PRODUCT:ITEM.VARIANT-TYPE;0(DATE) */

#ifndef _VMS_H_

#define _VMS_H_

#define SWITCH_CHAR '/'

#define TERMINATE_OK_EXIT     (1)
#define TERMINATE_FAIL_EXIT   (4)
#define USER_EXIT             (10)
#define ERROR_FLAG_EXIT       (2)
#define MISC_EXIT             (12)

#define ERROUT stderr

#define NEWLINE_SEQUENCE "\n"
#define REDIRECT_STDERR       1

/* fopen modes */
#define BINARY_1 "rb"
#define BINARY_2 "wb"
#define BINARY_3 "ab"
#define BINARY_4 "r+b"
#define BINARY_5 "w+b"
#define BINARY_6 "a+b"
#define TEXT_1 "r"
#define TEXT_2 "w"
#define TEXT_3 "a"
#define TEXT_4 "r+"
#define TEXT_5 "w+"
#define TEXT_6 "a+"

#define HOST_TTY_NAME         "TT:"

#ifndef SEEK_SET
#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2
#endif /* SEEK_SET */

/* Stuff for record structured files (groan!) */

#define POSITIONS_PER_BLOCK   256

struct RMSPOS {
   unsigned short int   a,b,c;
};

typedef struct RMSPOS FilePos;

struct POSINFO {
   int            baserec;
   FilePos        pos[POSITIONS_PER_BLOCK];
   struct POSINFO *prev;
   struct POSINFO *next;
};

typedef struct POSINFO RecInfo;

#endif /* _VMS_H_ */
