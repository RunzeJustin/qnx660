/*
 * $QNXLicenseC:
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

#ifndef INCL__VCAPTURE_OMAP4_5_EXT__H
#define INCL__VCAPTURE_OMAP4_5_EXT__H

#include <vcapture/capture.h>

#define CAPTURE_PROPERTY_OMAP_DDR_CLOCK_MHZ CAPTURE_PROPERTY('O','D','C','K')
	/* R/W  int32_t      the dual-data rate clock (MHz) of the external CSI2 transmitter */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/wfd/omap4-5-j6/caplib/public/vcapture/capture-omap4-5-ext.h $ $Rev: 732568 $")
#endif
