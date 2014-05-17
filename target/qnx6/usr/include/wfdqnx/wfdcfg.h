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

#ifndef HDRINCL_WFDCFG
#define HDRINCL_WFDCFG

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/* Macro used to validate the type of a function pointer
 * at compile time. */
#if defined __GNUC__
#define WFDCFG_FNPTR(FN,TYP) __builtin_choose_expr(   \
  __builtin_types_compatible_p(__typeof__(FN), TYP),  \
  (FN), (void)0 /*cause an error*/ )
#else
#define WFDCFG_FNPTR(FN,TYP) (FN)
#endif

struct wfdcfg_device;     /* opaque type */
struct wfdcfg_port;       /* opaque type */
struct wfdcfg_mode_list;  /* opaque type */

struct wfdcfg_timing {
	_Uint32t pixel_clock_kHz;
	_Uint32t hpixels, vlines;       /* resolution */
	_Uint16t hsw, vsw;              /* sync. pulse width */
	_Uint16t hfp, vfp;              /* front porch */
	_Uint16t hbp, vbp;              /* back porch */
	_Uint32t flags;                 /* bitmask of wfdcfg_flags values */
};

enum wfdcfg_flags {
	/* these are used for the .flags field of struct wfdcfg_timing */
#	define _b(x) ((_Uint32t)1 << (x))

	WFDCFG_INVERT_HSYNC =_b(0),     /* use negative hsync */
	WFDCFG_INVERT_VSYNC =_b(1),     /* use negative vsync */
	WFDCFG_INVERT_DATA_EN =_b(2),   /* invert "data enable" signal */
	WFDCFG_INVERT_CLOCK =_b(3),
	WFDCFG_INVERT_DATA =_b(4),

	WFDCFG_INTERLACE =_b(8),
	WFDCFG_DOUBLESCAN =_b(9),

	WFDCFG_PREFERRED =_b(31),

#	undef _b
};

enum wfdcfg_power_mode {
	WFDCFG_POWER_MODE_OFF            = 0x7680,
	WFDCFG_POWER_MODE_SUSPEND        = 0x7681,
	WFDCFG_POWER_MODE_LIMITED_USE    = 0x7682,
	WFDCFG_POWER_MODE_ON             = 0x7683,
};

/**
 * wfdcfg_keyval arrays appear in several places to allow for extensions:
 *  - on each device; access these via wfdcfg_device_get_extension.
 *  - on each port; access these via wfdcfg_port_get_extension.
 *  - on each mode; access these via wfdcfg_mode_get_extension.
 *  - on each modelist; access these via wfdcfg_mode_list_get_extension.
 * Several wfdcfg function takes wfdcfg_keyval as optional argument:
 *  - certain drivers will pass data to the wfdcfg via this interface.
 * The .i and .p members depend on the key; an element with .key==NULL
 * marks the end of the array.  Unused .i/.p fields should be 0 or NULL.
 */
struct wfdcfg_keyval {
	const char *key;
	long i;
	void *p;
};

/* Common extensions */
/** Gives the physical size in millimetres.  This is a port extension.
 *   .p points to an array: (float[]){ width, height }
 *  .i must be zero
 */
#define WFDCFG_EXT_PHYS_SIZE_MM "phys_size_mm"

/* Common function extensions */
/** Extension function called to set power mode on a port. This is a port extension.
 *  .p function pointer
 *  .i must be zero
 *
 * On failure, returns a code from errno.h.
 * possible error codes include (but are not limited to):
 *   EINVAL when a invalid power mode is passed.
 *
 *   EOK on success.
 */
#define WFDCFG_EXT_FN_SET_POWER_MODE "set_power_mode"
typedef int (wfdcfg_ext_fn_set_power_mode_t)(struct wfdcfg_port *port, enum wfdcfg_power_mode power_mode);

/**
 * Create a wfdcfg device.
 *
 * On success, returns 0 and sets *device to an opaque pointer.
 * The device id will be the WFD device id. The wfd need at least
 * one device otherwise the wfd driver will report an error.
 *
 * On failure, returns a code from errno.h and leaves *device unchanged.
 * Possible error codes include (but are not limited to):
 *   ENOMEM - can't allocate a device
 *   ENOENT - unknown device ID.
 */
int
wfdcfg_device_create(struct wfdcfg_device **device, int deviceid,
	const struct wfdcfg_keyval *opts);

/**
 * Get an extension identified by a key(string) from a device.
 * The extension is valid between the time you create and destroy
 * the device.
 *
 * Return:
 *   wfdcfg_keyval ptr - if the extension is found.
 *   NULL              - if the extension is not found. It's
 *                       acceptable to have no extension.
 *
 */
const struct wfdcfg_keyval*
wfdcfg_device_get_extension(const struct wfdcfg_device *device,
                            const char *key);

/**
 * Destroy a wfdcfg device. Will release the memory
 * allocated by the create wfdcfg_create_device.
 *
 * Device's extension pointer are not valid after this call.
 */
void
wfdcfg_device_destroy(struct wfdcfg_device *device);

/**
 * Create a wfdcfg port.
 *
 * On success, returns 0 and sets *port to an opaque pointer.
 * The port id will be the WFD port id. The wfdcfg need
 * to support at least one port otherwise the wfd driver will
 * report an error.
 *
 * On failure, returns a code from errno.h and leaves *device unchanged.
 * Possible error codes include (but are not limited to):
 *   ENOMEM - can't allocate a port
 *   ENOENT - unknown port ID.
 */
int
wfdcfg_port_create(struct wfdcfg_port **port,
	const struct wfdcfg_device *device, int portid,
	const struct wfdcfg_keyval *opts);

/**
 * Get an extension identify by a key(string) from a port.
 * The extension is valid between the time you create and destroy
 * the port.
 *
 * Return:
 *   wfdcfg_keyval ptr - if the extension is found.
 *   NULL              - if the extension is not found. It's
 *                       acceptable to have no extension.
 */
const struct wfdcfg_keyval*
wfdcfg_port_get_extension(const struct wfdcfg_port *port, const char *key);

/**
 * Destroy a wfdcfg port. Will release the memory
 * allocated by the create wfdcfg_create_port.
 *
 * Port's extension pointer are not valid after this call.
 */
void
wfdcfg_port_destroy(struct wfdcfg_port *port);

/**
 * Create a list of video modes.
 *
 * On success, returns 0 and sets *list to an opaque pointer.
 * Use wfdcfg_get_next_mode to get the list entries.
 *
 * On failure, returns a code from errno.h and leaves *list unchanged.
 * Possible error codes include (but are not limited to):
 *   ENOMEM - can't allocate a list
 *   ENOENT - unknown port ID
 */
int
wfdcfg_mode_list_create(struct wfdcfg_mode_list **list,
	const struct wfdcfg_port *port, const struct wfdcfg_keyval *opts);

/**
 * Get an extension identify by a key(string) from a mode list.
 * The extension is valid between the time you create and destroy
 * the list.
 *
 * Return:
 *   wfdcfg_keyval ptr - if the extension is found.
 *   NULL              - if the extension is not found. It's
 *                       acceptable to have no extension.
 */
const struct wfdcfg_keyval*
wfdcfg_mode_list_get_extension(const struct wfdcfg_mode_list *list,
	const char *key);

/**
 * Free a mode list. If called with a null pointer, do nothing.
 */
void
wfdcfg_mode_list_destroy(struct wfdcfg_mode_list *list);

/**
 * Get a mode from the given list.
 *
 * If prev_mode is NULL, this will return the first mode; otherwise it will
 * return the mode that follows prev_mode (which must be a valid entry in the
 * given list).  In either case, a return value of NULL indicates that the
 * end of the list has been reached.
 *
 * Returned pointers are valid until the list is freed.
 */
const struct wfdcfg_timing*
wfdcfg_mode_list_get_next(const struct wfdcfg_mode_list *list,
	const struct wfdcfg_timing *prev_mode);

/**
 * Get a mode extension from the given mode.
 * Returned pointers are valid until the mode list is freed.
 *
 * Return:
 *   wfdcfg_keyval ptr - if the extension is found.
 *   NULL              - if the extension is not found. It's
 *                       acceptable to have no extension.
 */
const struct wfdcfg_keyval*
wfdcfg_mode_get_extension(const struct wfdcfg_timing *mode,
	const char* key);

#endif /* HDRINCL_WFDCFG */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/wfdcfg/public/wfdqnx/wfdcfg.h $ $Rev: 732568 $")
#endif
