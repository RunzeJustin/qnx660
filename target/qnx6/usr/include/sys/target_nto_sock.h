/*
 * $QNXtpLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
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

#ifndef _TARGET_NTO_SOCK_H_INCLUDED
#define _TARGET_NTO_SOCK_H_INCLUDED

#ifdef QNX_MFIB
/*
 * Common MFIB defines needed in both kernel and non-kernel space
 */
#define FIBS_MAX 16 /* currently 16 routing tables */
#define DEFAULT_FIB 0 /* for now, default fib is fib 0. Fib ID is stored as a mask on the ifp */
#endif


#endif /* _TARGET_NTO_SOCK_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/socket/public/sys/target_nto_sock.h $ $Rev: 680336 $")
#endif
