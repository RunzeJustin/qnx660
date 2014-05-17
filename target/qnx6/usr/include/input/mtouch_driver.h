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
 * @file mtouch_driver.h
 *
 * @brief Functions that are to be implemented by the mtouch driver and are
 * called by @c libinputevents to fetch the data required to transform the
 * device data into mtouch events.
 *
 */
#include <sys/neutrino.h>

#include "input/mtouch_params.h"

#ifndef MTOUCH_DRIVER_H_
#define MTOUCH_DRIVER_H_

/** The multitouch device capability to support contact IDs. */
#define MTOUCH_CAPABILITIES_CONTACT_ID (1 << 0)

/** The multitouch device capability to support coordinates. */
#define MTOUCH_CAPABILITIES_COORDS (1 << 1)

/** The multitouch device capability to support contact counts. */
#define MTOUCH_CAPABILITIES_CONTACT_COUNT (1 << 2)

/** The multitouch device capability to support touch widths. */
#define MTOUCH_CAPABILITIES_WIDTH (1 << 3)

/** The multitouch device capability to support touch heights. */
#define MTOUCH_CAPABILITIES_HEIGHT (1 << 4)

/** The multitouch device capability to support touch orientations. */
#define MTOUCH_CAPABILITIES_ORIENTATION (1 << 5)

/** The multitouch device capability to support touch pressures
*   (or signal strength for capacitive touchscreens).
*/
#define MTOUCH_CAPABILITIES_PRESSURE (1 << 6)

/** The multitouch device capability to support setting of an event rate. */
#define MTOUCH_CAPABILITIES_RATE_SET (1 << 7)

/** The multitouch device capability to support sequence IDs. */
#define MTOUCH_CAPABILITIES_SEQ_ID (1 << 8)

/** The multitouch device capability to support contact type. */
#define MTOUCH_CAPABILITIES_CONTACT_TYPE (1 << 9)

/* The multitouch device capability to support select (buttons).
 * Do not use; not yet implemented.
 */
#define MTOUCH_CAPABILITIES_SELECT (1 << 10)

/* Default values for unsupported features */
/** The width when @c MTOUCH_CAPABILITIES_WIDTH isn't set or if this capability
 *  isn't available.
 */
#define MTOUCH_DEFAULT_WIDTH 1

/** The height when @c MTOUCH_CAPABILITIES_HEIGHT isn't set or if this
 *  capability isn't available.
 */
#define MTOUCH_DEFAULT_HEIGHT 1

/* The orientation when @c MTOUCH_CAPABILITIES_ORIENTATION isn't set, or if
 *  this capability isn't available.
 *  Do not use; not yet implemented.
 */
#define MTOUCH_DEFAULT_ORIENTATION 0

/** The pressure when @c MTOUCH_CAPABILITIES_PRESSURE isn't set or if this
 *  this capability isn't available.
 */
#define MTOUCH_DEFAULT_PRESSURE 1

/* Multitouch device flags */
/** A multi-touch device flag. Devices that report touch data for individual
 *  fingers in an inconsistent order should set this flag. Use this flag, along
 *  with the @c MTOUCH_FLAGS_INCONSISTENT_CONTACT_IDS flag, to describe the
 *  relationship between the digit index and the contact ID.
 */
#define MTOUCH_FLAGS_INCONSISTENT_DIGIT_ORDER (1 << 0)

/** A multitouch device flag. Devices that don't have contact IDs assigned as
 *  a zero-based index should set this flag. Use this flag along with
 *  the @c MTOUCH_FLAGS_INCONSISTENT_DIGIT_ORDER flag to describe the
 *  relationship between the digit index and the contact ID.
 */
#define MTOUCH_FLAGS_INCONSISTENT_CONTACT_IDS (1 << 1)

/* Internal use only.
 * Multitouch parser special params */
#define MTOUCH_PARSER_FLAG_NONE                       (0)
#define MTOUCH_PARSER_FLAG_CANCEL                     (1<<0)
#define MTOUCH_PARSER_FLAG_FLUSH                      (1<<1)
#define MTOUCH_PARSER_FLAG_LARGE_OBJECT               (1<<2)

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
* @brief Opaque data type that represents the multi-touch device.
*/
struct mtouch_device;

/**
 * @brief Functions to be implemented by the mtouch driver. These callback
 *        functions are called into by @c libinputevents to fetch the data
 *        required to transform the device (touch controller) data into
 *        mtouch events.
 *
 *        These functions must be implemented. Otherwise, the driver will not be
 *        able to connect to the Input Events framework.
 */
typedef struct {
	/**
	* @brief Retrieve the contact ID for the specified digit from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c contact_id Pointer to contact ID of the touch-related event for the
	*                 specified @c digit_idx. This function updates
	*                 @c contact_id upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_contact_id)(void* packet, _Uint8t digit_idx, _Uint32t* contact_id, void* arg);

	/**
	* @brief Retrieve the touch status for the specified digit from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c valid Pointer to touch status (e.g., @c 1 = Down and @c 0 = Up)
	*            of the touch-related event for the specified @c digit_idx.
	*            This function updates @c valid upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*is_contact_down)(void* packet, _Uint8t digit_idx, int* valid, void* arg);

	/**
	* @brief Retrieve the coordinates for the specified digit from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c x Pointer to the x coordinate of the touch-related event for the
	*        specified @c digit_idx. This function updates @c x upon its
	*        successful execution.
	* - @c y Pointer to the y coordinate of the touch-related event for the
	*        specified @c digit_idx. This function updates @c y upon its
	*        successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_coords)(void* packet, _Uint8t digit_idx, _Int32t* x, _Int32t* y, void* arg);

	/**
	* @brief Retrieve the number of touchpoints currently in contact with the
	*        screen.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c down_count Pointer to the number of rouchpoints currently in contact
	*                 with the screen. This function updates @c down_count
	*                 upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_down_count)(void* packet, _Uint32t* down_count, void* arg);

	/**
	* @brief Retrieve the width information for the specified digit from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c touch_width Pointer to the width of the touch-related event for the
	*                  specified @c digit_idx. This function updates
	*                  @c touch_width upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_touch_width)(void* packet, _Uint8t digit_idx, _Uint32t* touch_width, void* arg);

	/**
	* @brief Retrieve the height information for the specified digit from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c touch_height Pointer to the height of the touch-related event for the
	*                   specified @c digit_idx. This function updates
	*                   @c touch_height upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_touch_height)(void* packet, _Uint8t digit_idx, _Uint32t* touch_height, void* arg);

	/**
	* @brief Retrieve the orientation information for the specified digit from
	*        @c packet.
	*
	* This callback function is not yet implemented by the Input Events library.
	* For the time being, simply set this callback function to @c NULL in your
	* @c mtouch_driver_funcs_t assignment before you call
	* @e mtouch_driver_attach().
	*
	* @b Arguments
	* - @c packet
	* - @c digit_idx
	* - @c touch_orientation
	* - @c arg
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_touch_orientation)(void* packet, _Uint8t digit_idx, _Uint32t* touch_orientation, void* arg);

	/**
	* @brief Retrieve the touch pressure information for the specified digit
	*        from @c packet.
	*
	* For capacitive touchscreens, this callback function retrieves the signal
	* strength, not the pressure. The signal strength information is directly
	* proportional to the width and height retrieved from the
	* <em>(*get_touch_width)()</em> and <em>(*get_touch_height)()</em> callback
	* functions.
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that the Input Events library is
	*                requesting. It is a zero based index whose maximum is
	*                (@c max_touchpoints - 1). There is no requirement for any
	*                correlation between @c digit_idx and @c contact_id.
	* - @c touch_pressure Pointer to the pressure, or signal strength for
	*                     capacitive touchscreens, of the touch-related event
	*                     for the specified @c digit_idx. This function updates is
	*                     @c touch_pressure upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_touch_pressure)(void* packet, _Uint8t digit_idx, _Uint32t* touch_pressure, void* arg);

	/**
	* @brief Retrieve the unique sequence ID of a touch-related event from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h). The sequence ID is used to
	* track the touch-related event in the Input Events library. The sequence ID is
	* commonly a value that is incremented continuously.
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c seq_id Pointer to the unique sequence ID that Input Events library is
	*             requesting. This function updates @c seq_id upon its
	*             successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	void (*get_seq_id)(void* packet, _Uint32t* seq_id, void* arg);

	/**
	* @brief Retrieve the contact type of a touch-related event from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h).
	*
	* @b Arguments
	* - @c packet Data packet that contains information on the touch-related event.
	*             This data packet is the same packet that was passed into
	*             @e mtouch_driver_process_packet(). This data can be used to
	*             retrieve information about all digits, regardless of whether
	*             or not they are touching.
	* - @c digit_idx Digit (finger) index that is related to the contact type
	*                that is being retrived. It is a zero based index whose
	*                maximum is(@c max_touchpoints - 1).
	* - @c contact_type Pointer to the contact type that Input Events library is
	*                   requesting. Valid contact types are of type
	*                   @c #contact_type_e. This function updates @c contact_type
	*                   upon its successful execution.
	* - @c arg User information.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_contact_type)(void* packet, _Uint8t digit_idx, _Uint32t* contact_type, void* arg);

	/**
	* @brief Retrieve the select buttons of a touch-related event from @c packet.
	*
	* This callback function is not yet implemented by the Input Events library.
	* For the time being, simply set this callback function to @c NULL in your
	* @c mtouch_driver_funcs_t assignment when attaching your driver.
	*
	* @b Arguments
	* - @c packet
	* - @c digit_idx
	* - @c select
	* - @c arg
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*get_select)(void* packet, _Uint8t digit_idx, _Uint32t* select, void* arg);

	/**
	* @brief Retrieve the sampling period of a touch-related event from @c packet.
	*
	* This callback function is called for each of the touchpoints. The maximum
	* number of touchpoints is @c max_touchpoints, as specified in
	* @c mtouch_driver_params_t (@c mtouch_params.h). This function is called
	* with the device mutex held.
	*
	* @b Arguments
	* - @c dev Handle to the device driver.
	* - @c min_event_interval Minimum sampling period, in microseconds, of the
	*                         touch controller. Two touch-related events will not be
	*                         received in a time less than this interval.
	*
	* @b Returns
	* - @c 0 if successful; otherwise non-zero if an error occurred.
	*/
	int (*set_event_rate)(void* dev, _Uint32t min_event_interval);
} mtouch_driver_funcs_t;

/**
*   @brief Attach driver to the Input Events framework
*
*   This function connects the driver with the specified parameters and
*   callback functions to the Input Events frameowrk. You need to configure
*   @c params and @c funcs before passing them as arguments to this
*   function. This function must be called when you initialize your driver.
*
*   @param params Configured parameters for your driver.
*   @param funcs Callback functions that are implemented by the mtouch driver.
*                 The Input Events framework will use these callback functions
*                 to retrieve required information from the driver.
*
*   @return A handle to the opaque data type that represents the touch
*           device.
*/
struct mtouch_device* mtouch_driver_attach(mtouch_driver_params_t* params, mtouch_driver_funcs_t* funcs);

/**
*   @brief Detach driver from the Input Events framework
*
*   This function disconnects the specified driver from the Input Events
*   framework. Any memory allocated by the framework to support this driver
*   will be freed. This function must be called in addition to any device
*   cleanup.
*
*   @param device Handle to the touch device.
*
*   @return Nothing.
*/
void mtouch_driver_detach(struct mtouch_device* device);

/**
*   @brief Process the data packet from the specified driver
*
*   This function takes the data packet from the specfied driver and extracts
*   information from it. The relevant information from the driver's data packet
*   will be used to create an @c mtouch_event_t so that the Input Events
*   framework can continue to process it and pass it to Screen.
*   Drivers must call this function with a @c packet from which data for all
*   digits currently in contact with the touchscreen can be retrieved. For
*   example, if there are two digits in contact with the touchscreen, then
*   information for the contact of both digits must be included in the single
*   data packet. Drivers must not call this function multiple times when
*   multiple digits are simultaneously touching. This situation would result in
*   multiple touch and release events instead of an intended single move
*   event.
*
*   @param device Handle to the touch device.
*   @param packet Data packet that contains information on the touch-related event.
*   @param arg User information that resulted from initializing your driver.
*   @param flags Internal use only.
*
*   @return Nothing.
*/
void mtouch_driver_process_packet(struct mtouch_device* device, void* packet, void* arg, unsigned int flags);

/**
* @brief Types of pulse codes.
*
* Internal use only.
*/
enum {
	MTOUCH_FILTER_FLUSH_PULSE_CODE = _PULSE_CODE_MINAVAIL,
	MTOUCH_PULSE_CODE_MINAVAIL
};

/**
*   @brief Set the channel ID
*
*   Internal use only.
*
*   @param device Handle to the touch device.
*   @param chid Channel ID
*
*   @return Nothing.
*/
void mtouch_driver_set_chid(struct mtouch_device* device, int chid);

/** @brief The types of test results
*
*   This enumeration lists possible test results from using the test interface
*   for an mtouch driver.
*   @anonenum Mtouch_Driver_Test_Result_Types Driver test result types
*/
enum {
	/**
	*  Test has completed.
	*/
    MTOUCH_TEST_RESULT_COMPLETED,

	/**
	*  Test is not supported.
	*/
    MTOUCH_TEST_RESULT_NOT_SUPPORTED,

	/**
	*  Test cannot be run at this time. Possible reasons include:
	*  - firmware is being updated
	*  - single scan
	*  - BIST is occurring
	*/
    MTOUCH_TEST_RESULT_NOT_NOW,

	/**
	*  I2C communication with controller failed.
	*/
    MTOUCH_TEST_RESULT_I2C_FAILURE,

	/**
	*  The controller did not respond in time.
	*/
    MTOUCH_TEST_RESULT_TIMEOUT
};

/**
*   @brief Initialize test driver interface
*
*   This function initializes the test driver with defaults and prepares the
*   test driver interface for running individual test functions.
*
*   @return A handle to the device driver. This handle is passed as an
*           argument into each of the other test functions.
*/
void* mtouch_test_init(void);

/**
*   @brief Clean up test driver interface
*
*   This function frees any memory allocated by the test driver interface
*   used in running test functions.
*
*   @param dev Handle to the device driver.
*
*   @return Nothing.
*/
void mtouch_test_fini(void* dev);

/**
*   @brief Test the built-in-self-test (BIST)
*
*   This function runs the BIST of the driver.
*
*   @return A test result type. The test result will be one of type
*           <a href="mtouch__driver_8h_1Mtouch_Driver_Test_Result_Types.xml">Driver test result types</a>.
*/
int mtouch_test_bist(void* dev, uint8_t* passfail, uint16_t* max, uint16_t* min);

/**
*   @brief Test the ability to read the supplier ID.
*
*   This function reads the supplier ID from the driver. The first byte in
*   @c supplier represents the number of additional bytes in the buffer.
*
*   @param dev Handle to the device driver.
*   @param supplier Supplier ID read from the driver. The supplier ID is updated
*                   by this function and is valid until the next call of any
*                   one of the test functions.
*
*   @return A test result type. The test result will be one of type
*           <a href="mtouch__driver_8h_1Mtouch_Driver_Test_Result_Types.xml">Driver test result types</a>.
*/
int mtouch_test_read_supplier_id(void* dev, uint8_t** supplier);

/**
*   @brief Test the ability to read the serial ID of the driver.
*
*   This function reads the serial ID from the driver. The first byte in
*   @c serial represents the number of additional bytes in the buffer.
*
*   @param dev Handle to the device driver.
*   @param serial Serial ID read from the driver. The serial ID is updated by
*                 this function and is valid until the next call of any one of
*                 the test functions.
*
*   @return A test result type. The test result will be one of type
*           <a href="mtouch__driver_8h_1Mtouch_Driver_Test_Result_Types.xml">Driver test result types</a>.
*/
int mtouch_test_read_serial_id(void* dev, uint8_t** serial);

/**
*   @brief Test the ability to read the product ID of the driver.
*
*   This function reads the product ID from the driver. The first byte in
*   @c product represents the number of additional bytes in the buffer.
*
*   @param dev Handle to the device driver.
*   @param product product ID read from the driver. The product ID is updated by
*                  this function and is valid until the next call of any one of
*                  the test functions.
*
*   @return A test result type. The test result will be one of type
*           <a href="mtouch__driver_8h_1Mtouch_Driver_Test_Result_Types.xml">Driver test result types</a>.
*/
int mtouch_test_read_product_id(void *dev, uint8_t** product);

/**
*   @brief Test the ability to read the firmware version of the driver.
*
*   This function reads the firmware version from the driver. The first byte in
*   @c fwv represents the number of additional bytes in the buffer.
*
*   @param dev Handle to the device driver.
*   @param fwv Firmware version read from the driver and is valid until the next
*              call of any one of the test functions.
*
*   @return A test result type. The test result will be one of type
*           <a href="mtouch__driver_8h_1Mtouch_Driver_Test_Result_Types.xml">Driver test result types</a>.
*/
int mtouch_test_read_firmware_version(void* dev, uint8_t** fwv);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* MTOUCH_DRIVER_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/mtouch_driver.h $ $Rev: 731258 $")
#endif
