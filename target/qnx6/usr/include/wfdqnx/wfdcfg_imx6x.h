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

#ifndef HDRINCL_WFDCFG_IMX6X
#define HDRINCL_WFDCFG_IMX6X

#include <wfdqnx/wfdcfg.h>

/**
 * Extensions for i.MX6
 *
 */

enum imx6x_ldb_options {
	TIMING_LDB_DATA_MAPPING_SPWG,   /* 24 bit SPWG */
	TIMING_LDB_DATA_MAPPING_JEIDA,  /* 24 bit JEIDA or 18 bit SPWG */
	TIMING_LDB_DATA_MAPPING_SPWG_24 = TIMING_LDB_DATA_MAPPING_SPWG,   /* alias */
	TIMING_LDB_DATA_MAPPING_SPWG_18 = TIMING_LDB_DATA_MAPPING_JEIDA,  /* alias */
};
#define TIMING_LDB_OPTIONS "ldb_options"

/**
 * Some users want to program the PLL explicitly to avoid EMI or
 * other issues related to PLL selection.  If this option is set to a
 * non-zero value, the PLL must be configured (e.g. in the BSP code or
 * system startup) to a rate of (7.0 * pixel_clk).  In this case, the
 * pixel_clk_kHz modelib parameter will have no effect, but it should
 * be the same as the LVDS pixel rate so that the display refresh rate
 * reported by WFD will be correct.
 */
#define TIMING_LDB_DISABLE_CLOCK_SETUP "ldb_disable_clock_setup"

enum imx6x_output_formats {
	TIMING_OUTPUT_FORMAT_RGB888 = 24,  /* 24 bit (use for 18-bit SPWG too) */
	TIMING_OUTPUT_FORMAT_RGB666 = 18,  /* 18 bit (parallel LCD panels, not LVDS) */
	TIMING_OUTPUT_FORMAT_RGB565 = 16,  /* 16 bit parallel LCD panels */
};
#define TIMING_OUTPUT_FORMAT "output_format"

#define TIMING_CLK_DOWN "clk_down"  /* ends up in DI_BS_CLKGEN1 */
#define TIMING_CLK_UP   "clk_up"    /* unit is ns */

/**
 * The following options are DEPRECATED.  They used to change the
 * selection of the LVDS LDB input clock, but the WFD driver now reads
 * the mux register directly.
 */
enum imx6x_ldb_di0_clock_sel {
	TIMING_LDB_DI0_CLOCK_SEL_PLL5 = 0 << 9,
	TIMING_LDB_DI0_CLOCK_SEL_PLL2_352M_PFD = 1 << 9,
	TIMING_LDB_DI0_CLOCK_SEL_PLL2_396M_PFD = 2 << 9,
	TIMING_LDB_DI0_CLOCK_SEL_MMDC_CH1 = 3 << 9,
	TIMING_LDB_DI0_CLOCK_SEL_PLL3 = 4 << 9,
};
#define TIMING_LDB_DI0_CLOCK_SEL "ldb_di0_clock_sel"

enum imx6x_ldb_di1_clock_sel {
	TIMING_LDB_DI1_CLOCK_SEL_PLL5 = 0 << 12,
	TIMING_LDB_DI1_CLOCK_SEL_PLL2_352M_PFD = 1 << 12,
	TIMING_LDB_DI1_CLOCK_SEL_PLL2_396M_PFD = 2 << 12,
	TIMING_LDB_DI1_CLOCK_SEL_MMDC_CH1 = 3 << 12,
	TIMING_LDB_DI1_CLOCK_SEL_PLL3 = 4 << 12,
};
#define TIMING_LDB_DI1_CLOCK_SEL "ldb_di1_clock_sel"

/* Backward compatibility */
#define LDB_DI0_CLK_SEL_OPTIONS TIMING_LDB_DI0_CLOCK_SEL

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/wfd/imx6x/public/wfdqnx/wfdcfg_imx6x.h $ $Rev: 731807 $")
#endif
