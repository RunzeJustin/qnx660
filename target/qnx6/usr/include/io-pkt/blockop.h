/*
 * $QNXtpLicenseC:
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


#ifndef _BLOCKOP_H_INCLUDED
#define _BLOCKOP_H_INCLUDED

#include <receive.h>

struct proc;

struct bop_dispatch {
	struct stk_callback	bop_cb;
	void			(*bop_func)(void *arg);
	void			*bop_arg;
	int			bop_prio;
};

void blockop_init(void);
int blockop_dispatch(struct bop_dispatch *, struct proc *);
void blockop_wakeup(void *arg);

#endif /* !_BLOCKOP_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/io-pkt/sys/blockop.h $ $Rev: 680336 $")
#endif
