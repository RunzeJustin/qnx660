
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



#ifndef _SPI_LIB_H_INCLUDED
#define _SPI_LIB_H_INCLUDED

#ifndef	__TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef	_INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#define SPILIB_VERSION_MAJOR    1
#define SPILIB_VERSION_MINOR    0
#define SPILIB_REVISION         0

typedef struct {
    unsigned char   major;
    unsigned char   minor;
    unsigned char   revision;
} spi_libversion_t;

typedef enum {
    SPI_CPOL_ACTIVE_HIGH,
    SPI_CPOL_ACTIVE_LOW
} spi_clock_polarity_t;

typedef enum {
    SPI_CPHASE_NONE,
    SPI_CPHASE_HALF
} spi_clock_phase_t;

typedef enum {
    SPI_BIT_MSB,
    SPI_BIT_LSB
} spi_bit_order_t;

typedef uint32_t    spi_devnum_t;

/*
 * Hardware interface
 */
typedef struct {
    /* size of this structure */
    size_t size;

    /*
     * Return version information
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*version_info)(spi_libversion_t *version);

    /*
     * Initialize master interface.
     * Returns a handle that is passed to all other functions.
     * Returns:
     * !NULL    success
     * NULL     failure
     */
    void *(*init)(int argc, char *argv[]);

    /*
     * Clean up driver.
     * Frees memory associated with "hdl".
     */
    void (*fini)(void *hdl);

    /* TODO pass only the message context, supply lib function
     * to read message data (or try to get all data in message
     * buffer?)
     */
    /*
     * Returns:
     * number of bytes queued for transmission
     */
    int (*send)(
            void *hdl, uint8_t *buf, int len, 
            void (*done)(void *userdata, int rcvid, int nbytes), 
            void *userdata, int rcvid);
    int (*recv)(
            void *hdl, uint8_t *buf, int len,
            void (*done)(void *userdata, int rcvid, iov_t *iov, int nparts), 
            void *userdata, int rcvid);

    /*
     * notify that data is available
     * - this could be used for slave mode, or if the SPI master
     *
     */
    int (*set_recv_notify)(
            void *hdl,
            void (*notify)(void *userdata),
            void *userdata);

    /*
     * notify that write buffer has space
     */
    int (*set_send_notify)(
            void *hdl,
            void (*notify)(void *userdata),
            void *userdata);

    /*
     * query if data is available - for intial ionotify
     */
    int (*query_recv_notify)(void *hdl);

    /*
     * query for space in write buffer - for initial ionotify
     */
    int (*query_send_notify)(void *hdl);
} spi_funcs_t;

#define SPI_GETFUNCS "spi_getfuncs"

/*
 * Fills in the given table with the hardware-specific functions. 
 * If a function table entry is unimplemented, it should 
 * be left unchanged (and not set to NULL, etc.).
 * "funcs->size" should be set by whomever has allocated the
 * table. Don't change this.
 * Parameters:
 * (i/o)    funcs       Function table
 * (in)     tabsize     size of "funcs" in bytes
 * Returns:
 * 0    success
 * -1   failure
 */
typedef int (spi_getfuncs_f)(spi_funcs_t *funcs, int tabsize);
spi_getfuncs_f   spi_getfuncs;

#define SPI_ADD_FUNC(tabletype, table, entry, func, limit) \
    if (((size_t)&(((tabletype *)0)->entry)) + \
        sizeof (void (*)()) <= (limit)) \
        (table)->entry = (func);

#define SPI_OPTIONS "u:"

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/spi/public/hw/spi.h $ $Rev: 736767 $")
#endif
