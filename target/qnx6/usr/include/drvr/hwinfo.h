/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems.
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


#ifndef _DRVR_HWINFO_H_INCLUDED
#define _DRVR_HWINFO_H_INCLUDED

#include <sys/platform.h>
#include <hw/sysinfo.h>		/* needed for hwi_tag type */
#include <sys/hwinfo.h>		/* needed for the hwiattr_* types */

/* HWI support routines */
unsigned	hwi_find(const char *device_name, int unit, unsigned hwi_off);
int			hwi_find_unit(unsigned hwi_off);
int			hwi_find_num_units(const char *name);
unsigned	hwi_find_bus(const char *bus_name, unsigned unit);
unsigned	hwi_find_device(const char *device_name, unsigned unit);
unsigned	hwi_find_devicebus(unsigned device_hwi_off);

hwi_tag *	hwi_tag_find(unsigned hwi_off, const char *tag_name, unsigned *tag_idx);
unsigned	hwitag_find_ivec(unsigned hwi_off, unsigned *irq);
int			hwitag_find_nicaddr(unsigned hwi_off, unsigned *nicaddr_idx, _Uint8t *nicaddr);
int			hwitag_find_phyaddr(unsigned hwi_off, unsigned *phy_idx);
long		hwitag_find_clkfreq(unsigned hwi_off, unsigned *clk_idx);
int			hwitag_find_errata(unsigned hwi_off, unsigned *errata_idx);
int			hwitag_find_busattr(unsigned hwi_off, unsigned *busattr_idx, struct hwi_busattr *busattr);

int			hwiattr_get(unsigned hwi_off, hwiattr_t *hwiattr);
/* bus attribute get functions */
int			hwiattr_get_spi(unsigned hwi_off, hwiattr_spi_t *hwiattr);
int			hwiattr_get_i2c(unsigned hwi_off, hwiattr_i2c_t *hwiattr);
int			hwiattr_get_pci(unsigned hwi_off, hwiattr_pci_t *hwiattr);
int			hwiattr_get_usb(unsigned hwi_off, hwiattr_usb_t *hwiattr);
int			hwiattr_get_can(unsigned hwi_off, hwiattr_can_t *hwiattr);
/* device attribute get functions */
int			hwiattr_get_uart(unsigned hwi_off, hwiattr_uart_t *hwiattr);
int			hwiattr_get_enet(unsigned hwi_off, hwiattr_enet_t *hwiattr);
int			hwiattr_get_rtc(unsigned hwi_off, hwiattr_rtc_t *hwiattr);
int			hwiattr_get_dma(unsigned hwi_off, hwiattr_dma_t *hwiattr);
int			hwiattr_get_timer(unsigned hwi_off, hwiattr_timer_t *hwiattr);

#endif	/* _DRVR_HWINFO_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/drvr/public/drvr/hwinfo.h $ $Rev: 736740 $")
#endif
