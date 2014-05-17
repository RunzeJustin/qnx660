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
 * @mainpage Input Events Library Overview
 *
 * @section input_events_library_overview Input Events Library Overview
 *
 * The Input Events library allows applications to receive and process events
 * from input devices. The classes of events that are recognized by the
 * Input Events library are:
 * - TOUCH (@c INPUT_CLASS_MTOUCH)
 * - KEYBOARD (@c INPUT_CLASS_KEYBOARD)
 * - MOUSE (@c INPUT_CLASS_MOUSE)
 */

/**
 * @file event_types.h
 *
 * @brief Enumerations and structures for input events
 *
 * The event_types.h header file provides type definitions for classifying
 * input event types.  These type definitions can be used to determine the kind
 * of input event that has occurred and the properties of the event.
 *
 */
#include <inttypes.h>
#include <sys/types.h>
#include <time.h>

#ifndef INPUTEVENTS_H_
#define INPUTEVENTS_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Classes of input events
 */
typedef enum {
	INPUT_CLASS_MTOUCH = 1, /**< A touch-related event on the screen */
	INPUT_CLASS_KEYBOARD,   /**< A key event on the virtual keyboard */
	INPUT_CLASS_MOUSE       /**< A mouse event using a connected mouse */
} input_class_e;

/**
 * @brief Types of @c INPUT_CLASS_MTOUCH events
 *
 * One event type is received per touchpoint. For example, if you have two
 * fingers in contact with the screen, you will receive two
 * @c INPUT_EVENT_MTOUCH_TOUCH events. Similarly, if you remove two fingers from
 * contact with the screen, you will receive two @c INPUT_EVENT_MTOUCH_RELEASE
 * events, one for each finger. The touch-related events are identified
 * individually through a contact ID.
 */
typedef enum {
	/** Unknown event type (default). */
	INPUT_EVENT_UNKNOWN = 0,

	/** Event type for when there is new contact with the screen detected. */
	INPUT_EVENT_MTOUCH_TOUCH = 100,

	/** Event type for when contact with the screen is already detected, but
	    the contact is changing position.
	 */
	INPUT_EVENT_MTOUCH_MOVE,

	/** Event type for when contact with the screen is removed. */
	INPUT_EVENT_MTOUCH_RELEASE,

	/** Event type for when a gesture is cancelled; a touch controller
	 *  that is powered off could cause a cancel.
	 */
	INPUT_EVENT_MTOUCH_CANCEL,

	/* Internal use only.
	 * Event type for a flush event that is normally requested by a filter
	 */
	INPUT_EVENT_FLUSH,

	/* Internal use only.
	 * Event type for a large object
	 */
	INPUT_EVENT_LARGE_OBJECT,

	/* Internal use only.
	 * Event type for a large object cancel; used to distinguish a large object
	 * cancel from a cancel event.
	 */
	INPUT_EVENT_LARGE_OBJECT_CANCEL
} input_event_e;

/**
 * @brief Types of contact for an @c INPUT_CLASS_MTOUCH event
 */
typedef enum {
	CONTACT_TYPE_FINGER = 0,        /**< Finger touch (default). */
	CONTACT_TYPE_STYLUS = 1,        /**< Stylus touch. */
} contact_type_e;

/**
 * @brief Structure that contains details common to @c INPUT_CLASS_MTOUCH input
 *        events
 *
 * The @c mtouch_event structure represents information that is common to all
 * input events of class @c INPUT_CLASS_MTOUCH.  This information is provided by
 * the input device driver whenever an @c INPUT_CLASS_MTOUCH event occurs.
 */
typedef struct mtouch_event {
	/** The event type of the @c INPUT_CLASS_MTOUCH event. */
	input_event_e event_type;

	/** Timestamp, based on realtime clock, when the @c INPUT_CLASS_MTOUCH
	 *  event occurred.
	 */
	_Uint64t timestamp;

	/** The sequence number for the event; @c seq_id is incremented each time a
	 *  new touch-related event occurs.
	 */
	_Uint32t seq_id;

	/** The order of occurrence for multiple touch contacts. */
	_Uint32t contact_id;

	/** The x screen position, in pixels, for the event. */
	_Int32t x;

	/** The y screen position, in pixels, for the event. */
	_Int32t y;

	/** The width, in pixels, of the touch area. */
	_Uint32t width;

	/** The height, in pixels, of the touch area. */
	_Uint32t height;

	/** The orientation of the contact.*/
	_Uint32t orientation;

	/** The pressure of the touch contact, ranging from 0 to 2^32 - 1. */
	_Uint32t pressure;

	/** The contact type. Valid contact types are of type @c #contact_type_e. */
	_Uint32t contact_type;

	/** The selected buttons */
	_Uint32t select;
} mtouch_event_t;

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* INPUTEVENTS_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/event_types.h $ $Rev: 731258 $")
#endif
