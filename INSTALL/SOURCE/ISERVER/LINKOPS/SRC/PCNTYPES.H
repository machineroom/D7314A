/*-----------------------------------------------------------------------------
--
-- CMSIDENTIFIER
-- PRODUCT:ITEM.VARIANT-TYPE;0(DATE) 
--
-- File    : pcntypes.h
--  file descriptor macros for PC-NFS (real pc's only)
--    assume fds_set is a long int.
--
-- Copyright 1990 INMOS Limited
--
-- Date    : 3/26/91
-- Version : 1.2
--
-- 09/12/90 dave edwards
--   originated
--
-----------------------------------------------------------------------------*/

#define FD_ZERO(fds) (long int)*(fds)=0L

#define FD_SET(n, fds) (long int)*(fds)=( ((long int)*(fds)) | (1L << n) )
                                                         
