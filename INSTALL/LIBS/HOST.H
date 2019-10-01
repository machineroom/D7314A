/* @(#)host.h	1.1 3/25/91 */

/* host.h */
/* Copyright (C) Inmos Ltd. 19/3/90 */

#ifndef __host_h
#define __host_h 1

/* allows interrogation of the host */

#pragma IMS_translate(host_info, "host_info%c")

extern void host_info(int * /*host*/, int * /*os*/, int * /*board*/);

/* hosts */

#define _IMS_HOST_PC        1
#define _IMS_HOST_NEC       2 
#define _IMS_HOST_VAX       3
#define _IMS_HOST_SUN3      4
#define _IMS_HOST_IBM370    5
#define _IMS_HOST_SUN4      6
#define _IMS_HOST_SUN386i   7
#define _IMS_HOST_APOLLO    8


/* operating systems */

#define _IMS_OS_DOS	    1
#define _IMS_OS_HELIOS      2
#define _IMS_OS_VMS         3
#define _IMS_OS_SUNOS       4
#define _IMS_OS_CMS         5

/* boards */

#define _IMS_BOARD_B004	    1
#define _IMS_BOARD_B008     2
#define _IMS_BOARD_B010	    3
#define _IMS_BOARD_B011     4
#define _IMS_BOARD_B014	    5
#define _IMS_BOARD_DRX11    6
#define _IMS_BOARD_QT0	    7
#define _IMS_BOARD_B015     8
#define _IMS_BOARD_CAT	    9
#define _IMS_BOARD_B016	    10
#define _IMS_BOARD_UDP_LINK 11


#endif

/* end of host.h */
