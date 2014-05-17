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

#ifndef _DRVR_COMMON_H_INCLUDED
#define _DRVR_COMMON_H_INCLUDED

#include <sys/platform.h>

#define DRVR_BUSTYPE_PCI       0x70636900  /* "pci" */
#define DRVR_BUSTYPE_ISA       0x69736100  /* "isa" */
#define DRVR_BUSTYPE_USB       0x75736200  /* "usb" */
#define DRVR_BUSTYPE_VME       0x766d6500  /* "vme" */
#define DRVR_BUSTYPE_PCCARD    0x70636300  /* "pcc" */
#define DRVR_BUSTYPE_IEEE1394  0x66697200  /* "fir" */
#define DRVR_BUSTYPE_RAPIDIO   0x72696f00  /* "rio" */

#endif /* _DRVR_COMMON_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/drvr/public/drvr/common.h $ $Rev: 703817 $")
#endif
