/* @(#)bootlink.h	1.3 9/10/92 */

/* Copyright (C) INMOS ltd, 1992 */

#ifndef __bootlink_h
#define __bootlink_h

/* Declare the function which returns the boot link channels */

#include <channel.h>

#pragma IMS_translate( get_bootlink_channels, "get_bootlink_channels%c" )

extern int get_bootlink_channels( Channel ** /*in_ptr*/, 
                                  Channel ** /*out_ptr*/ );

#endif
