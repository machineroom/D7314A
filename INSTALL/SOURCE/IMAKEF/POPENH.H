/* CMSIDENTIFIER
   PLAY:POPENH_H@403.AAAA-FILE;1(20-FEB-92)[FROZEN] */
/*
-- ----------------------------------------------------------------------------
--
--     Object Name : popenh.h
--     Revision    : 1
--
--     Copyright INMOS Limited, 1988.
--     All Rights Reserved.
--
--     DESCRIPTION
--         Include file for the INMOS path searching library routine.
--
--     NOTES
--         None.
--
--     HISTORY
--         28-Nov-1988    Antony King    Last change.
--
-- ----------------------------------------------------------------------------
*/

#ifndef _POPENH
#define _POPENH

#include "inmos.h"   /* Standard INMOS system include file */

EXTERNAL FILE *popen_read();

#define POPEN_TEXT_MODE   0
#define POPEN_BINARY_MODE 1

#define POPEN_READ_TEXT(name, pathname, newname, stream) \
stream = popen_read(name, pathname, newname, POPEN_TEXT_MODE);

#define POPEN_READ_BINARY(name, pathname, newname, stream) \
stream = popen_read(name, pathname, newname, POPEN_BINARY_MODE);
#endif
