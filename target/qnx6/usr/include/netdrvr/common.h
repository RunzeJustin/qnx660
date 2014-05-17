/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef _NETDRVR_COMMON_H_INCLUDED
#define _NETDRVR_COMMON_H_INCLUDED

#include <drvr/common.h>

/* Miscellaneous utilities */
void nsec_delay(int nsec);
_Uint64t drvr_mphys(void *);

int nic_pic_irq(void *handle, int irr_mmask, int irr_smask,
    void (*irq_assert)(void *), void (*irq_clear)(void *));
void dma_cascade(int dchnl);

#endif /* _NETDRVR_COMMON_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/io-pkt/sys/lib/libnetdrvr/public/netdrvr/common.h $ $Rev: 703817 $")
#endif
