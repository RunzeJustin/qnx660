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

#ifndef _DRVR_SUPPORT_H_INCLUDED
#define _DRVR_SUPPORT_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <hw/pci.h>
#include <sys/types.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <gulliver.h>
#include <pthread.h>

/* Typed memory functions. */
void	*mmap_typed_device_memory (void *addr, size_t len, int prot, int flags, uint64_t physical,
									char *name, int oflag, int tflag);
uintptr_t	mmap_typed_device_io (size_t len, uint64_t io, char *name, int oflag, int tflag);

#endif /* _DRVR_SUPPORT_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/drvr/public/drvr/support.h $ $Rev: 703817 $")
#endif
