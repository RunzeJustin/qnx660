/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef HDRINCL_WFDCFG_AM335X
#define HDRINCL_WFDCFG_AM335X

#include <wfdqnx/wfdcfg.h>

/*
 * RASTER_TIMING_2 Register (Section 13.5.13)
 *     Bit 25 phsvs_on_off: Hsync/Vsync Pixel Clock Control On/Off
 */
#define WFDCFG_EXT_PHSVS_ON_OFF          "phsvs_on_off"
enum am335x_phsvs_on_off {
	WFDCFG_PHSVS_ON  = 0,	// lcd_lp and lcd_fp are drivern on opposite edages of pixel clock
							// than the lcd_pixel_o
	WFDCFG_PHSVS_OFF = 1,	// lcd_lp and lcd_fp are drivern according to bit 24 Note that this bit
							// MUST be set to '0' for Passive Matrix displays.
							// The edge timing is fixed.
};

/*
 * RASTER_TIMING_2 Register (Section 13.5.13)
 *     Bit 24 phsvs_rf: Program HSYNC/VSYNC Rise or Fall
 */
#define WFDCFG_EXT_PHSVS_RF              "phsvs_rf"
enum am335x_phsvs_rf {
	WFDCFG_PHSVS_RISE = 0,	// lcd_lp and lcd_fp are drivern on the rising edge of pixel clock (bit
							// 25 must be set to 1).
	WFDCFG_PHSVS_FALL = 1,	// lcd_lp and lcd_fp are drivern on the falling edge of pixel clock (bit
							// 25 must be set to 1).
};

/*
 * RASTER_TIMING_2 Register (Section 13.5.13)
 *     Bits 15-8  acb: AC Bias Pin Frequency (From 0-255)
 */
#define WFDCFG_EXT_ACB_VALUE             "acb_value"

/*
 * RASTER_TIMING_2 Register (Section 13.5.13)
 *     Bits 19-16  acbi: AC Bias Pins Transitions per Interrupt Value (From  to 15)
 */
#define WFDCFG_EXT_ACBI_VALUE            "acbi_value"

#define WFDCFG_EXT_OUTPUT_FORMAT         "output_format"
enum am335x_output_format {
	WFDCFG_OUTPUT_FORMAT_RGBX8888 = 32,
	WFDCFG_OUTPUT_FORMAT_RGB888   = 24,
	WFDCFG_OUTPUT_FORMAT_RGB666   = 18,
	WFDCFG_OUTPUT_FORMAT_RGB565   = 16,   /* 16 bit parallel LCD panels */
};

#define WFDCFG_EXT_PIXEL_CLOCK_DIVIDER   "pixel_clock_divider"


/**
 * Port initialisation hook.  If this port extension exists, the WFD driver
 * will call the given function when the port is created.
 *  .p is a pointer to a function of type wfdcfg_ext_fn_port_init1_t
 *      (which returns EOK on success or another errno code on failure)
 *  .i must be zero
 */
#define WFDCFG_EXT_FN_PORT_INIT1     "port_init1"
typedef int (wfdcfg_ext_fn_port_init1_t)(struct wfdcfg_port*);

/**
 * Port deinitialisation hook.  If this port extension exists, the WFD driver
 * will call the given function when the port is destroyed.
 *  .p is a pointer to a function of type wfdcfg_ext_fn_port_uninit1_t
 *  .i must be zero
 */
#define WFDCFG_EXT_FN_PORT_UNINIT1   "port_uninit1"
typedef void (wfdcfg_ext_fn_port_uninit1_t)(struct wfdcfg_port*);

/**
 * Port modesetting hook.  If this port extension exists, the WFD driver
 * will call the given function when programming a mode.
 *  .p is a pointer to a function of type wfdcfg_ext_fn_port_set_mode_t
 *      (which takes a pointer to the mode being programmed, and
 *      returns EOK on success or another errno code on failure)
 *  .i must be zero
 */
#define WFDCFG_EXT_FN_PORT_SET_MODE2 "port_set_mode2"
typedef int (wfdcfg_ext_fn_port_set_mode2_t)(struct wfdcfg_port*,
		const struct wfdcfg_timing*);


#endif // HDRINCL_WFDCFG_AM335X


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/wfd/am335x/wfdcfg/public/wfdqnx/wfdcfg_am335x.h $ $Rev: 736009 $")
#endif
