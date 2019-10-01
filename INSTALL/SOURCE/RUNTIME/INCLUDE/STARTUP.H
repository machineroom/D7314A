/* @(#)startup.h	1.3 6/30/92 */

/* startup.h */
/* Copyright (C) Inmos Ltd, 1992 */

#ifndef __startup_h
#define __startup_h

#include <channel.h>

/***************************************************************************
 *                                                                         *
 * This header file contains declarations of all the support functions     *
 * which are called by the runtime startup.                                *
 *                                                                         *
 ***************************************************************************/

#pragma IMS_translate(set_host_link, "set_host_link%c")
#pragma IMS_translate(io_and_hostinfo_init, "io_and_hostinfo_init%c")
#pragma IMS_translate(terminate_server, "terminate_server%c")
#pragma IMS_translate(GetArgsMyself, "GetArgsMyself%c")
#pragma IMS_translate(get_init_chain_start, "get_init_chain_start%c")

extern void set_host_link(Channel *in, Channel *out);
extern void io_and_hostinfo_init(void);
extern void terminate_server(long int n);
extern void GetArgsMyself(int *argcp, char ***argvp);
extern int *get_init_chain_start(void);

#endif /* __startup_h */

/* end of startup.h */

