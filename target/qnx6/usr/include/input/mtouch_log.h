/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
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

/**
 * @file mtouch_log.h
 *
 * @brief Function and Macros that print mtouch log information.
 *
 */

#include <sys/slogcodes.h>
#include <sys/cdefs.h>


#ifndef MTOUCH_H_
#define MTOUCH_H_

__BEGIN_DECLS

/**
*   @brief Print mtouch log information
*
*   This is a variadic function. If @c NDEBUG is defined, the information
*   is sent as a message to the system logger (@c slogger). Otherwise, the log
*   is simply directed to @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[severity]: formatted argument list</tt>.
*
*   @param severity Severity of the condition that triggered the log.
*          For more information on severity levels, see @e slogf() in the
*          <em>QNX C Library Reference</em>. All log severities are defined in
*          <tt><sys/slog.h></tt>
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param ... Variable-length argument list that correponds to that which
*              is specified in @c format.
*
*   @return Nothing.
*/
void mtouch_log(int severity, const char* devname, const char* format, ...);

#ifdef NDEBUG
#define mtouch_debug(devname, format, args...)
#else
/**
*   @brief Print mtouch log information as @c SLOG_DEBUG1 severity
*
*   This macro implements an @e mtouch_log() function with severity of @c SLOG_DEBUG.
*   If @c NDEBUG is defined, the information is sent as a message to the
*   system logger (@c slogger). Otherwise, the log is simply directed to
*   @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[DEBUG]: formatted argument list</tt>.
*
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param args Variable-length argument list that correponds to that which
*               is specified in @c format.
*
*   @return Nothing.
*/
#define mtouch_debug(devname, format, args...) \
	mtouch_log(_SLOG_DEBUG1, devname, format, ##args)
#endif

/**
*   @brief Print mtouch log information as @c SLOG_INFO severity
*
*   This macro implements an @e mtouch_log() function with severity of @c SLOG_INFO.
*   If @c NDEBUG is defined, the information is sent as a message to the
*   system logger (@c slogger). Otherwise, the log is simply directed to
*   @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[INFO]: formatted argument list</tt>.
*
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param args Variable-length argument list that correponds to that which
*               is specified in @c format.
*
*   @return Nothing.
*/
#define mtouch_info(devname, format, args...) \
	mtouch_log(_SLOG_INFO, devname, format, ##args)

/**
*   @brief Print mtouch log information as @c SLOG_WARNING severity
*
*   This macro implements an @e mtouch_log() function with severity of @c SLOG_WARNING.
*   If @c NDEBUG is defined, the information is sent as a message to the
*   system logger (@c slogger). Otherwise, the log is simply directed to
*   @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[WARNING]: formatted argument list</tt>.
*
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param args Variable-length argument list that correponds to that which
*               is specified in @c format.
*
*   @return Nothing.
*/
#define mtouch_warn(devname, format, args...) \
	mtouch_log(_SLOG_WARNING, devname, format, ##args)

/**
*   @brief Print mtouch log information as @c SLOG_ERROR severity
*
*   This macro implements an @e mtouch_log() function with severity of @c SLOG_ERROR.
*   If @c NDEBUG is defined, the information is sent as a message to the
*   system logger (@c slogger). Otherwise, the log is simply directed to
*   @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[ERROR]: formatted argument list</tt>.
*
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param args Variable-length argument list that correponds to that which
*               is specified in @c format.
*
*   @return Nothing.
*/
#define mtouch_error(devname, format, args...) \
	mtouch_log(_SLOG_ERROR, devname, format, ##args)

/**
*   @brief Print mtouch log information as @c SLOG_CRITICAL severity
*
*   This macro implements an @e mtouch_log() function with severity of @c SLOG_ERROR.
*   If @c NDEBUG is defined, the information is sent as a message to the
*   system logger (@c slogger). Otherwise, the log is simply directed to
*   @c stderr. The @e mtouch_log() output format is:
*   <tt>devname[CRITICAL]: formatted argument list</tt>.
*
*   @param devname Name of device driver.
*   @param format String that specifies the format of the log. The formatting
*                 string determines what additional arguments you need to
*                 provide.
*   @param args Variable-length argument list that correponds to that which
*               is specified in @c format.
*
*   @return Nothing.
*/
#define mtouch_critical(devname, format, args...) \
	mtouch_log(_SLOG_CRITICAL, devname, format, ##args)

__END_DECLS

#endif /* MTOUCH_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/mtouch_log.h $ $Rev: 731258 $")
#endif
