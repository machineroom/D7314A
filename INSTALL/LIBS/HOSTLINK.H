/* @(#)hostlink.h	1.4 9/10/92 */

/* Copyright (C) INMOS ltd, 1992 */

#ifndef __hostlink_h
#define __hostlink_h

/* Declare those functions which return the host link channels */

#include <channel.h>

#pragma IMS_translate(from_host_link, "from_host_link%c")
#pragma IMS_translate(to_host_link, "to_host_link%c")

extern Channel *from_host_link(void);
extern Channel *to_host_link(void);

#endif
