/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */



#ifndef _RECEIVE_H_INCLUDED
#define _RECEIVE_H_INCLUDED

struct nw_oob_ctl;

struct rcv_loop_args {
	int		main_argc;
	char		**main_argv;
	const char	*main_options;

	char		*proto_opts;

	int		sigev_type;
	int		preseed_threads;
};

int receive_loop_init(void *);
int oob_init(void *);
void oob_fini(struct nw_oob_ctl *);
void poke_stack_pkt_q(void);

void *receive_loop_uni(void *arg);
#ifndef VARIANT_uni
void *receive_loop_multi(void *arg);
#endif
extern void * receive_loop_oob(void *); /* if defined(OOB_THREAD_HIGH) || defined(OOB_THREAD_LOW) */


#endif /* !_RECEIVE_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/io-pkt/sys/receive.h $ $Rev: 680336 $")
#endif
