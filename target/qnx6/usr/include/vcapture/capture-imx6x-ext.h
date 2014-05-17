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

#ifndef INCL__VCAPTURE_IMX6X_EXT__H
#define INCL__VCAPTURE_IMX6X_EXT__H

#include <vcapture/capture.h>

#define CAPTURE_PROPERTY_IMX6X_VSYNC_TYPE CAPTURE_PROPERTY('M','X','V','T')
	/* R/W		int		VSYNC signal type (0: internal VSYNC, 1: external */
	/*					VSYNC, or -1 for default). */

#define CAPTURE_PROPERTY_IMX6X_SENSOR_CLK_MODE CAPTURE_PROPERTY('M','X','S','C')
	/* R/W		int		Sensor timing/data mode protocol, see the enum below */

enum imx6x_sensor_clk_mode {
	SENSOR_CLK_MODE_GATED_CLK,
	SENSOR_CLK_MODE_NONGATED_CLK,
	SENSOR_CLK_MODE_CCIR656_PROGRESSIVE,
	SENSOR_CLK_MODE_CCIR656_INTERLACED,
	SENSOR_CLK_MODE_CCIR1120_PROGRESSIVE_DDR,
	SENSOR_CLK_MODE_CCIR1120_PROGRESSIVE_SDR,
	SENSOR_CLK_MODE_CCIR1120_INTERLACED_DDR,
	SENSOR_CLK_MODE_CCIR1120_INTERLACED_SDR,
};

#define CAPTURE_PROPERTY_IMX6X_ADAPTIVE_DEI_MOTION_MODE CAPTURE_PROPERTY( 'M', 'X', 'V', 'M' )
	/* R/W		int		Motion mode of adaptive deinterlacer (VDI), see the enum below */

enum imx6x_vdi_motion_mode {
	VDI_MOTION_MODE_LOW,
	VDI_MOTION_MODE_MED,
	VDI_MOTION_MODE_HIGH,
};

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/wfd/imx6x/caplib/public/vcapture/capture-imx6x-ext.h $ $Rev: 732568 $")
#endif
