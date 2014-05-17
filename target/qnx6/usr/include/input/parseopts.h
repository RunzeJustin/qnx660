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
 * @file parseopts.h
 *
 * @brief Helper functions to parse the options from the @c mtouch section of
 *        <tt>graphics.conf</tt>.
 *
 * The parseopts.h header file defines the helper functions that are used
 * to parse the options from the @c mtouch section of the configuration
 * file, <tt>graphics.conf</tt>.
 *
 */

#include <sys/cdefs.h>

#ifndef __INPUT_PARSEOPTS_H_INCLUDED
#define __INPUT_PARSEOPTS_H_INCLUDED

__BEGIN_DECLS

/**
 * @brief Parse values from options of @c mtouch section of
 *        <tt>graphics.conf</tt>.
 *
 * This function is passed as an argument to @e input_parseopts(). It is called
 * by @e input_parseopts() to parse out individual options. This function must
 * be implemented by your driver to parse, with the use of the helper functions,
 * the options and set the user information (@c arg) of your driver.
 *
 * @param option Option passed from @c mtouch section of <tt>graphics.conf</tt>.
 * @param value Value associated with @c option from <tt>graphics.conf</tt>.
 * @param arg User information.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
typedef int (*set_option_t)(const char* option, const char* value, void* arg);

/**
 * @brief Parse the argument @c options
 *
 * This function calls the @c set_option callback function on the device for
 * each option in @c options. The format of @c options is:
 * <tt>option=value1,option2=value2</tt>
 *
 * @param options Option passed from @c mtouch section of <tt>graphics.conf</tt>.
 * @param set_option Callback function that is called on each option in @c options
 *                   to parse the information and set the user information.
 * @param arg User information.
 *
 * @return Nothing.
 */
void input_parseopts(const char* options, set_option_t set_option, void* arg);

/**
 * @brief Parse an @c option of the type unsigned integer.
 *
 * @param option Option of type unsgined integer to be parsed.
 * @param value Value of the option.
 * @param out The unsigned integer value of @c option.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
int input_parse_unsigned(const char* option, const char* value, unsigned* out);

/**
 * @brief Parse an @c option of the type integer.
 *
 * @param option Option of type integer to be parsed.
 * @param value Value of the option.
 * @param out The integer value of @c option.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
int input_parse_signed(const char* option, const char* value, int* out);

/**
 * @brief Parse an @c option of the type boolean.
 *
 * @param option Option of type boolean to be parsed.
 * @param value Value of the option.
 * @param out The boolean value of @c option.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
int input_parse_bool(const char* option, const char* value, unsigned* out);

/**
 * @brief Parse an @c option of the type string.
 *
 * @param option Option of type string to be parsed.
 * @param value Value of the option.
 * @param out The string value of @c option.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
int input_parse_string(const char* option, const char* value, char** out);

/**
 * @brief Parse an @c option of the type double.
 *
 * @param option Option of type string to be parsed.
 * @param value Value of the option.
 * @param out The double value of @c option.
 *
 * @return @c 0 if successful, otherwise non-zero if an error occurred.
 */
int input_parse_double(const char* option, const char* value, double* out);

__END_DECLS

#endif /* __INPUT_PARSEOPTS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/parseopts.h $ $Rev: 729618 $")
#endif
