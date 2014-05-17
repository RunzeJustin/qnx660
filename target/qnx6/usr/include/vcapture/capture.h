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

#ifndef	QNXVIDEOCAPTURE_PUBLIC_H
#define	QNXVIDEOCAPTURE_PUBLIC_H

#include <inttypes.h>
#include <sys/platform.h>

__BEGIN_DECLS

struct _capture_context;
typedef struct _capture_context	*capture_context_t;

/** The capture API is thread safe -- unless stated otherwise for a particular API.
 *
 */
/* 0x0001 is reserved */
#define CAPTURE_FLAG_EXTERNAL_SOURCE	0x0002

/**
 * Establish a connection to the capture device and create a context.
 *
 * CAPTURE_FLAG_EXTERNAL_SOURCE can be used to indicate that
 * the to-be-created context is for external source, instead of captured source.
 *
 * Before the application exits all contexts must be 'destroyed'.
 * 
 * IMPORTANT: Failure to destroy the context can cause severe memory
 * corruption with some capture implementations, and the OS may not be to
 * clean up adequately after the exiting process. See capture_destroy_context
 * for more details.
 *
 * @flags -- bitmask parameter, 0, or
 *           CAPTURE_FLAG_EXTERNAL_SOURCE -- the to-be-created context is for
 *           external source, instead of captured source.
 *
 * Returns:
 *  a pointer to a new context or a NULL if an error occurred -- errno is set.
 *  EINVAL -- invalid flags,
 *  EBUSY  -- unable to create a context because one is already in use.
 *  <list of dlopen()/SendMsg() errors>
 */
extern capture_context_t capture_create_context( uint32_t flags );

/**
 * Disconnect from the capture device and destroy the passed context.
 * All existing and pending capturing operations are canceled at this time.
 * When this functions returns it is safe to release the capture buffers that
 * may have been in use.
 *
 * NOT SIGNAL HANLDER SAFE!
 *
 * IMPONTANT: We recommend that applications create a separate thread to do
 * proper signal handling, and there are two ways for the signal thread to
 * destroy the capture context:
 * 1. Inform other threads to call capture_destroy_context().
 * 2. call capture_destroy_context() directly in the signal thread.
 */
extern void capture_destroy_context( capture_context_t context );

/**
 * 
Capture memory model:

For each buffer type (frame buffers and frame metadata buffers), the buffer can
either be allocated by the application and used by the driver: 'application-allocated',
or allocated by the driver and used by the application: 'driver-allocated'.
We include in the "application" any code that isn't part of the capture driver.
An application might get memory from elsewhere, such as screen, that it wants
to use for capture, but we still consider this to be application-allocated
memory since the capture driver didn't allocate it.

Each type of buffer can be in one of three states:
 -- allocated by the driver,
 -- allocated by the application, or
 -- not allocated at all.
 
The "not allocated at all" case is special because the driver may disable
expensive hardware features that aren't necessary to capture data for which
no buffer has been allocated.

Creating frame and metadata buffers with capture_create_buffers() implements
driver-allocated memory--it changes the state of the buffer to driver-allocated,
and causes the driver to cease using any previous buffer.  If the buffer was
previously driver-allocated and is still suitable, the driver may simply re-use
the existing buffer (hardware that does not support dynamic buffers at all must
always do this).  If the buffer was previously application-allocated or not
allocated at all then the driver must always provide its own
driver-allocated buffer.

Setting the various buffer pointer properties with capture_set_property_p()
implements application-allocated memory--it changes the state of the associated
buffer to application-allocated, and may cause any previous driver-allocated
memory to be freed by the driver.  The driver may make this a no-op if the
previous application-allocated buffer was compatible, sufficiently large,
and located at the same address.

Setting a given buffer pointer to NULL implements the "not allocated at all"
case for that buffer, causes the driver to cease using application-allocated
buffer memory, and may cause the driver to free previously driver-allocated
memory.  Hardware that supports only driver-allocated memory with little
flexibility can use a simpler implementation that simply rejects any attempt
to take a buffer out of driver-allocated state.  In such cases, setting a
buffer property to NULL returns success, but may have no effect.

Driver-allocated memory is managed by the driver.  The driver allocates and
frees this memory, and the application can only use it when the API defines
it to be valid.  In worst-case hardware the buffer is at a hardcoded physical
RAM address, so the driver's allocate function merely returns a pointer to
this memory mmap()ped into the application's address space through
capture_get_property_p(), and the free function does nothing.

Application-allocated memory is managed by the application.  The application
allocates and frees this memory, and the driver can only use it when the API
defines it to be valid.  The driver does no buffer memory allocation in this
case (unless the hardware requires such buffers to exist even when not used
by the application).  Some hardware will not be able to use
application-allocated memory, in which case setting a buffer pointer property
will fail if the pointer value is non-NULL.

It's possible to get a pointer to a buffer with capture_get_property_p() and
then set the same pointer with capture_set_property_p().  If the buffer was
driver-allocated, this would cause the driver to free its buffer (which is
what the pointer points to) and then assume the application owned the now
non-existent buffer, with disastrous results.  We should either make that
a special no-op case, or disallow it completely, or explicitly document this
failure mode.  If the buffer was initially application-allocated then no ill
effects occur.

We could require that application-allocated memory can only be set with
capture_set_property if and only if any previously allocated buffer had been
released by setting the property to NULL.
*/

/**
 * Create capture safe memory.
 *
 * @property  -- The buffer property to allocate memory for.
 *               The memory is allocated based on the properties that are set
 *               in the context beforehand.
 *
 * This call is synchronous, and the buffer(s) are created immediately (if any).
 * The existing buffers that were allocated before this call are freed immediatelly.
 * If you need to free a buffer without creating a new one set the buffer property
 * to NULL via capture_set_property_v().
 *
 * IMPORTANT: Calling this function must be done when capturing is not in progress.
 *
 * Return:
 *    0 -- on success
 *   -1 -- on error, errno is set.
 *
 * errno:
 *  EINVAL -- invalid argument or not a buffer property.
 *  ENOMEM -- unable to allocate memory
 *  ENOSYS -- this driver doesn't support buffer allocation.
 *
 * Example:
 *  ...
 *	capture_set_property_i( context, CAPTURE_PROPERTY_DST_NBYTES, 320 * 240 * 4 );
 *  capture_set_property_i( context, CAPTURE_PROPERTY_FRAME_NBUFFERS, 5 );
 *
 *  // create 5 frame buffers with 320x240x4 bytes each.
 *  capture_create_buffers( context, CAPTURE_PROPERTY_FRAME_BUFFERS );
 *
 *  // get the buffers..
 *  void 		**frame_buffers;
 *
 *  capture_get_property_p( context, CAPTURE_PROPERTY_FRAME_BUFFERS, (void**)&frame_buffers );
 *  ....
 *
 */
extern int capture_create_buffers( capture_context_t context, uint32_t property );

/**
 * Test if the property 'prop' is supported by this capturing device.
 * Return:
 *		0 -- property is not supported;
 *		1 -- property is supported;
 */
extern int capture_is_property( capture_context_t context, uint32_t prop );

/**
 * Property Setters
 *
 * Return: 0 -- success,
 *         -1 on error, errno is set:
 * errno:
 *   EINVAL -- bad value or values
 *   EROFS  -- unable to change read-only property
 *   ENOENT -- no such property for this type of a setter method.
 *   ENOTSUP -- this property is not supported by this driver or HW configuration.
 * NOTE:
 *  Array resources such as CAPTURE_PROPERTY_FRAME_FLAGS, CAPTURE_PROPERTY_FRAME_SEQNO are not allocated
 *  by default. The user must allocate these arrays of sufficient size and pass a pointer to the array
 *  by using capture_set_property_p(). The capture library stores this pointer to the array
 *  and will update the array when appropriate. The user code reads the data from the array
 *  directly when appropriate. The number of elements in the arrays is at least as the
 *  number of buffers (CAPTURE_PROPERTY_FRAME_NBUFFERS).
 *  Setting a NULL on an array property instructs the capture library to stop collecting/providing
 *  the arrays date.
 *
 *  For example:
 *
 *  nbuffers = 3;
 *  // allocate a seqno buffer.
 *  uint32_t seqno[nbuffers];
 *
 *  // tell the capture library to use this array and update it when frames are captured.
 *  capture_set_property_p( ctx, CAPTURE_PROPERTY_FRAME_SEQNO, &seqno );
 *
 *  ...
 *  // get a captured frame
 *  int idx = capture_get_frame( ctx, ... );
 *
 *	// the frame data and the buffer of the 'idx' frame is locked.
 *  if( -1 != idx ) {
 *  	// it is safe to access the contents of the seqno[idx]
 *      printf( "captured a frame, seqno = %u\n", seqno[idx] );
 *  }
 *
 *  ...
 *  capture_release_frame( ctx, idx );
 *
 *  ...
 *  // no longer safe to access seqno[idx] -- since the data may no longer be valid.
 *
 *
 */
extern int capture_set_property_i( capture_context_t context, uint32_t prop, int32_t value );
extern int capture_set_property_p( capture_context_t context, uint32_t prop, void *value );

/**
 * Property Getters
 *
 * Return:
 *        -1 -- on error, errno is set.
 *       >=0 -- is the number of filled elements.
 * errno:
 *	ENOENT -- no such property/type for this type of a getter method.
 *  ENOTSUP -- this property is not supported by this driver or HW configuration.
 */
extern int capture_get_property_i( capture_context_t context, uint32_t prop, int32_t *value );
extern int capture_get_property_p( capture_context_t context, uint32_t prop, void **value );

/**
 * Update capture device. All properties that changed since the last update are applied (committed)
 * to the device. This allows proper combining of discrete properties such as *DST_X, *DST_Y, *DST_WIDTH and etc.
 * If the CAPTURE_ENABLE is set to 1, capturing will commence immediately.
 *
 * @flags -- provisional parameters
 *
 * Return:
 *  0 -- Success,
 * -1 -- on error, errno is set
 *
 * errno:
 *  EINVAL -- some of the parameters are in conflict. Capturing is not possible.
 *  EIO    -- H/W input/output error.
 *  ENODEV -- no such capturing device (id).
 *
 *  NOTE: the driver may slog*() additional details on the conflict. Use the sloginfo.
 *
 */
extern int capture_update( capture_context_t context, uint32_t flags );

#define	CAPTURE_TIMEOUT_INFINITE	(-1ULL)
#define	CAPTURE_TIMEOUT_NO_WAIT		(0)
#define	CAPTURE_FLAG_LATEST_FRAME	(0x0001)
#define CAPTURE_FLAG_FREE_BUFFER	(0x0002)
/**
 * Get the next captured frame. This may block if no captured frames available.
 *
 * @timeout		-- timeout value in nanoseconds. Special values are:
 *                 CAPTURE_TIMEOUT_NO_WAIT  -- immediate return even if there is no frame;
 *                 CAPTURE_TIMEOUT_INFINITE -- infinite timeout -- wait for a frame indefinitely.
 * @flags		-- 0, or CAPTURE_FLAG_LATEST_FRAME to get the latest frame,
 *                 and discard all the other queued frames.
 *
 * This call is thread safe.
 * It is okay to call this function even if capturing is not started yet. The assumption is that
 * some other thread is going to enable/disable capturing when required.
 *
 * Returns:
 *  >=0 -- index of the captured buffer (see CAPTURE_PROPERTY_DST_BUFFERS).
 *         The associated buffer is locked until the next capture_release_frame()
 *         is called for the returned index. The capture will continue into the
 *         other available buffers.
 *         The dropped counter is maintained while capturing.
 *   -1 -- an error occurred or timeout, errno is set.
 *
 * errno:
 *  ETIMEDOUT -- timeout occurred, no frame captured.
 *  ECANCELED -- the capture was disabled. This error occurs when get_frame() was called while
 *               capturing was enabled, and disabled by some other thread during execution of this function.
 *  EINVAL    -- invalid argument.
 *  EIO       -- h/w input/output error
 *  ENOMEM	  -- capturing is not possible -- ALL capture buffers are locked by the user (not released
 *               back to the capture library).
 */
extern int capture_get_frame( capture_context_t context, uint64_t timeout, uint32_t flags );

/**
 *  Get a free buffer to decode into. Calls capture_get_frame with CAPTURE_FLAG_FREE_BUFFER.
 */
#define capture_get_free_buffer( context, timeout, flags )    \
		capture_get_frame( context, timeout, (flags) | CAPTURE_FLAG_FREE_BUFFER )

/**
 * Release the frame back to the h/w for capturing. If the frame
 * is already released no error is reported.
 * Returns:
 *      0 -- success
 *     -1 -- an error occurred, errno is set
 * Errno:
 *  EINVAL -- idx is not valid.
 */
extern int capture_release_frame( capture_context_t context, uint32_t idx );

/**
 * Injects the buffer to the driver for deinterlacing.
 * Returns:
 *      0 -- success
 *     -1 -- an error occurred, errno is set
 * Errno:
 *  EINVAL -- idx is not valid, and/or the sequence number is not valid.
 */
extern int capture_put_buffer( capture_context_t ctx, uint32_t idx, uint32_t flags );

/*************************************************************** PROPERTIES ***/
#define CAPTURE_PROPERTY(a, b, c, d)	( (a) << 24 | (b) << 16 | (c) << 8 | (d) )

#define	CAPTURE_PROPERTY_DEVICE_INFO	CAPTURE_PROPERTY( 'Q', 'I', 'N', 'F' )
		/* R	(const char *)	Returns a string information about this capture h/w and driver. */
		/* All drivers support this property. */

#define	CAPTURE_ENABLE					CAPTURE_PROPERTY( 'Q', 'E', 'N', 'A' )
		/* R/W		uint32_t	Capture start (1)/stop(0). */

#define CAPTURE_PROPERTY_NDEVICES		CAPTURE_PROPERTY( 'Q', 'N', 'D', 'V' )
		/* R		uint32_t	Number of supported capture units */

#define CAPTURE_PROPERTY_DEVICE			CAPTURE_PROPERTY( 'Q', 'D', 'E', 'V' )
		/* R/W		uint32_t	Active capture device in this context */

#define	CAPTURE_PROPERTY_NSOURCES		CAPTURE_PROPERTY( 'Q', 'N', 'S', 'R' )
		/* R		uint32_t	Number of available source input (after the device is set). */

#define CAPTURE_PROPERTY_CONTRAST		CAPTURE_PROPERTY( 'Q', 'C', 'O', 'N' )
		/*R/W		int32_t		Contrast, -128 to 127. */

#define CAPTURE_PROPERTY_BRIGHTNESS		CAPTURE_PROPERTY( 'Q', 'B', 'R', 'I' )
		/* R/W		int32_t		Brightness, -128 to 127. */

#define CAPTURE_PROPERTY_SATURATION		CAPTURE_PROPERTY( 'Q', 'S', 'A', 'T' )
		/* R/W		int32_t		Color saturation, -128 to 127. */

#define CAPTURE_PROPERTY_HUE			CAPTURE_PROPERTY( 'Q', 'H', 'U', 'E' )
		/* R/W		int32_t		Color hue, -128 to 127. */

#define CAPTURE_PROPERTY_DEINTERLACE_FLAGS	CAPTURE_PROPERTY( 'Q', 'D', 'E', 'I' )
		/* R/W		uint32_t	De-interlacing flag (bit-field). */

#define CAPTURE_PROPERTY_DEINTERLACE_MODE	CAPTURE_PROPERTY( 'Q', 'D', 'E', 'M' )
		/* R/W		uint32_t	De-interlacing mode; see the enum below. */

enum capture_deinterlace_mode {
		CAPTURE_DEINTERLACE_NONE_MODE	= 0,
		CAPTURE_DEINTERLACE_WEAVE_MODE,
		CAPTURE_DEINTERLACE_BOB_MODE,
		CAPTURE_DEINTERLACE_BOB2_MODE,
		CAPTURE_DEINTERLACE_WEAVE2_MODE,
		CAPTURE_DEINTERLACE_MOTION_ADAPTIVE_MODE,
		/* TODO: add more modes -- even if provisional */
};

#define CAPTURE_PROPERTY_MIN_NBUFFERS		CAPTURE_PROPERTY( 'Q', 'M', 'N', 'B' )
		/* R		uint32_t	Minimum number of buffers required for a specific deinterlacing mode. */

#define CAPTURE_BUFFER_USAGE_RDONLY	0x001

#define CAPTURE_PROPERTY_BUFFER_USAGE		CAPTURE_PROPERTY( 'Q', 'B', 'U', 'S' )
		/* R/W		[] uint32_t	Array of buffer usage flags. Element i indicates */
		/*				if the capture driver has CAPTURE_BUFFER_USAGE_RDONLY or */
		/*			        CAPTURE_BUFFER_USAGE_RDWR permissions for buffer 'i'. */
		/*			        The latter is the default value. */

#define CAPTURE_PROPERTY_BUFFER_INDEX		CAPTURE_PROPERTY( 'Q', 'B', 'I', 'X' )
		/* W		uint32_t	The index of the buffer to be injected through capture_put_buffer() API. */

#define CAPTURE_PROPERTY_BUFFER_NFIELDS		CAPTURE_PROPERTY( 'Q', 'B', 'N', 'F' )
		/* W		uint32_t	The number of fields contained in the buffer injected through */
		/*				capture_put_buffer() API. */

#define CAPTURE_PROPERTY_BUFFER_PLANAR_OFFSETS	CAPTURE_PROPERTY( 'Q', 'B', 'P', 'O' )
		/* W            [][3] int32_t  Array per buffer (one row per field). Each row indicates the offset from */
		/*				the base address for each of the Y, U, and V components of planar YUV formats. */

#define CAPTURE_PROPERTY_BUFFER_FLAGS		CAPTURE_PROPERTY( 'Q', 'B', 'F', 'L' )
		/* W		[] uint32_t	Array of buffer flags, per buffer (bit-field). */

#define CAPTURE_PROPERTY_BUFFER_SEQNO		CAPTURE_PROPERTY( 'Q', 'B', 'S', 'N' )
		/* W		[] uint32_t     Array of sequence numbers, per buffer. Each element indicates the sequence number */
		/*				of the field contained within. */

#define CAPTURE_PROPERTY_NORM			CAPTURE_PROPERTY( 'Q', 'N', 'O', 'R' )
		/* R/W		const char *	Set video standard, see the macros below. */
#define CAPTURE_NORM_AUTO	"AUTO"		/* auto detection */

#define	CAPTURE_PROPERTY_CURRENT_NORM		CAPTURE_PROPERTY( 'Q', 'Q', 'N', 'M' )
		/* R		const char *	Returns current detected video standard, see the macros below. */

#define CAPTURE_NORM_NONE	"NONE"		/* no input */
#define CAPTURE_NORM_UNKNOWN	"UNKNOWN"	/* the detected norm is unknown */

/* these macros are common for CAPTURE_PROPERTY_NORM and CAPTURE_PROPERTY_CURRENT_NORM */
#define CAPTURE_NORM_NTSC_M_J			"NTSC_M_J"
#define CAPTURE_NORM_NTSC_4_43			"NTSC_4_43"
#define CAPTURE_NORM_PAL_M			"PAL_M"
#define CAPTURE_NORM_PAL_B_G_H_I_D		"PAL_B_G_H_I_D"
#define CAPTURE_NORM_PAL_COMBINATION_N		"PAL_COMBINATION_N"
#define CAPTURE_NORM_PAL_60			"PAL_60"
#define CAPTURE_NORM_SECAM			"SECAM"

#define CAPTURE_PROPERTY_INVERT_FID_POL   CAPTURE_PROPERTY( 'Q', 'L', 'F', 'I' )
		/* R/W      int             Controls whether the field ID signal is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_INVERT_VSYNC_POL CAPTURE_PROPERTY( 'Q', 'L', 'H', 'S' )
		/* R/W      int             Controls whether the vsync polarity is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_INVERT_HSYNC_POL CAPTURE_PROPERTY( 'Q', 'L', 'V', 'S' )
		/* R/W      int             Controls whether the hsync polarity is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_INVERT_CLOCK_POL CAPTURE_PROPERTY( 'Q', 'L', 'P', 'C' )
		/* R/W      int             Controls whether the clock polarity is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_INVERT_DATAEN_POL CAPTURE_PROPERTY( 'Q', 'L', 'D', 'E' )
		/* R/W      int             Controls whether the data_en polarity is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_INVERT_DATA_POL CAPTURE_PROPERTY( 'Q', 'L', 'D', 'A' )
		/* R/W      int             Controls whether the data input polarity is */
		/*                          inverted (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_SRC_FORMAT		CAPTURE_PROPERTY( 'Q', 'S', 'F', 'O' )
		/* R/W		uint32_t	Source buffer format */

#define CAPTURE_PROPERTY_SRC_STRIDE		CAPTURE_PROPERTY( 'Q', 'S', 'F', 'S' )
		/* R/W		uint32_t	Source buffer stride in bytes. */

#define	CAPTURE_PROPERTY_SRC_WIDTH		CAPTURE_PROPERTY( 'Q', 'S', 'W', 'I' )
		/* R/W		uint32_t	the actual width of the source */

#define	CAPTURE_PROPERTY_SRC_HEIGHT		CAPTURE_PROPERTY( 'Q', 'S', 'H', 'E' )
		/* R/W		uint32_t	the actual height of the source */

#define CAPTURE_PROPERTY_CROP_WIDTH		CAPTURE_PROPERTY( 'Q', 'C', 'W', 'I' )
		/* R/W		uint32_t	source viewport width */

#define CAPTURE_PROPERTY_CROP_HEIGHT	CAPTURE_PROPERTY( 'Q', 'C', 'H', 'E' )
		/* R/W		uint32_t	source viewport height */

#define CAPTURE_PROPERTY_SRC_INDEX		CAPTURE_PROPERTY( 'Q', 'S', 'I', 'D' )
		/* R/W		uint32_t	Device's video capture unit */
		/* TODO: We need to describe what the dependencies are between the device and source. */
		/* DRAFT: a capture drivers provides a list of supported devices (NDEVICES), */
		/*        each device contains/has at least one input (NSOURCES). */
		/*        Selection of the input is done by choosing a device, and then a source. */

#define CAPTURE_PROPERTY_CROP_X			CAPTURE_PROPERTY( 'Q', 'C', 'X', 'P' )
		/* R/W		uint32_t	source viewport X */

#define CAPTURE_PROPERTY_CROP_Y			CAPTURE_PROPERTY( 'Q', 'C', 'Y', 'P' )
		/* R/W		uint32_t	source viewport Y */

#define CAPTURE_PROPERTY_DST_WIDTH		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'W' )
		/* R/W		uint32_t	Destination frame width in pixels */

#define CAPTURE_PROPERTY_DST_HEIGHT		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'H' )
		/* R/W		uint32_t	Destination frame height in pixels */

#define CAPTURE_PROPERTY_DST_STRIDE		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'S' )
		/* R/W		uint32_t	Destination frame stride in bytes. */
		/* NOTE: The application should make sure that the size of the allocated buffers */
		/* is not less than "destination stride * destination frame height" */

#define	CAPTURE_PROPERTY_DST_NBYTES		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'B' )
		/* R/W		uint32_t	Destination frame buffer size in bytes */

#define	CAPTURE_PROPERTY_FRAME_NBUFFERS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'N' )
		/* R/W		uint32_t	Number of dst buffers specified in the CAPTURE_PROPERTY_DST_BUFFERS */

/** NOTE: Array properties have special handling. The user's code must provide pointers to the arrays.
 * The pointers are stored in the capture library's context. The access modifiers in the properties
 * below are for the user's intended access of the arrays contents. If an array for a property is not set,
 * the capture library is not going to do the work associated with getting the data from
 * the hardware.
 * see the note and example of capture_set_property_p().
 */

#define CAPTURE_PROPERTY_FRAME_BUFFERS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'A' )
		/* R/W		[] void*	Pointers to the capture buffers */

#define	CAPTURE_PROPERTY_FRAME_TIMESTAMP	CAPTURE_PROPERTY( 'Q', 'F', 'B', 'T' )
		/* R        [] uint64_t		An array of CLOCK_MONOTONIC timestamps indexed by the buffer index */

#define	CAPTURE_PROPERTY_FRAME_TIMECODE		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'C' )
		/* R        [] struct smpte_timestamp	An array of SMTPE timestamps indexed by the buffer index */

#define	CAPTURE_PROPERTY_FRAME_SEQNO		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'S' )
		/* R		[] uint32_t		An array of sequence numbers indexed by the buffer index */

#define	CAPTURE_PROPERTY_FRAME_FLAGS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'F' )
		/* R		[] uint32_t		An array of frame flags indexed by the buffer index */

#define	CAPTURE_PROPERTY_FRAME_NBYTES		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'B' )
		/* R		[] uint32_t		An array of frame sizes in bytes indexed by the buffer index */

/* flags for CAPTURE_PROPERTY_FRAME_FLAGS */
#define	CAPTURE_FRAME_FLAG_ERROR	0x0001
#define	CAPTURE_FRAME_FLAG_INTERLACED	0x0002
#define	CAPTURE_FRAME_FLAG_FIELD_BOTTOM	0x0004

#define CAPTURE_PROPERTY_DST_FORMAT			CAPTURE_PROPERTY( 'Q', 'D', 'F', 'F' )
		/* R/W		uint32_t	Destination buffer format */

#define CAPTURE_PROPERTY_PLANAR_OFFSETS		CAPTURE_PROPERTY( 'Q', 'P', 'L', 'O' )
		/* R/W		[3] int32_t Offset from the base address for each of the Y, */
		/*						U, and V components of planar YUV formats. */

#define CAPTURE_PROPERTY_THREAD_PRIORITY	CAPTURE_PROPERTY( 'Q', 'T', 'P', 'R' )
		/* R/W		int		The scheduling priority of the capture thread */
		/*                      default value is "application priority + 20" */

#define CAPTURE_PROPERTY_INTERFACE_TYPE		CAPTURE_PROPERTY('Q','P','I','F')
		/* R/W		uint32_t	Interface type, see the enum below */
enum capture_iface_type {
	CAPTURE_IF_PARALLEL = 0,
	CAPTURE_IF_MIPI_CSI2,
};

#define CAPTURE_PROPERTY_DATA_BUS_WIDTH		CAPTURE_PROPERTY( 'Q', 'D', 'B', 'W' )
		/* R/W		int		The data bus width, for parallel interface */
		/*				possible values: 8, 10, 16... */

#define CAPTURE_PROPERTY_CSI2_NUM_DATA_LANES	CAPTURE_PROPERTY('Q','C','N','D')
		/* R/W		int		Number of CSI2 data lanes (1 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_CSI2_CLK_LANE_POS	CAPTURE_PROPERTY('Q','C','C','P')
		/* R/W		int		Position of CSI2 clock lane (0 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_CSI2_DATA0_LANE_POS	CAPTURE_PROPERTY('Q','C','D','0')
		/* R/W		int		Position of CSI2 data lane 0 (0 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_CSI2_DATA1_LANE_POS	CAPTURE_PROPERTY('Q','C','D','1')
		/* R/W		int		Position of CSI2 data lane 1 (0 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_CSI2_DATA2_LANE_POS	CAPTURE_PROPERTY('Q','C','D','2')
		/* R/W		int		Position of CSI2 data lane 2 (0 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_CSI2_DATA3_LANE_POS	CAPTURE_PROPERTY('Q','C','D','3')
		/* R/W		int		Position of CSI2 data lane 3 (0 ~ 4, or -1 for default) */

#define CAPTURE_PROPERTY_VERBOSITY		CAPTURE_PROPERTY( 'Q', 'V', 'B', 'R' )
		/* R/W		uint32_t	The verbose level when capturing */
		/*				possible values: 0 (default), 1, 2..... */

#define CAPTURE_PROPERTY_DECODER_I2C_PATH	CAPTURE_PROPERTY('Q','D','I','P')
		/* R/W		const char *	Device path of the decoder. e.g. "/dev/i2c0", etc. */
		/*				(only for the decoders which are connected via I2C) */
#define CAPTURE_PROPERTY_DECODER_I2C_ADDR	CAPTURE_PROPERTY('Q','D','I','A')
		/* R/W		uint32_t	Slave address of the decoder. */
		/*				(only for the decoders which are connected via I2C) */
/* helpers */
#define CAPTURE_INTERVAL_FROM_MS(x) ((x) * 1000000ULL)
#define CAPTURE_INTERVAL_FROM_US(x) ((x) * 1000ULL)
#define CAPTURE_INTERVAL_FROM_NS(x) (x)

#define CAPTURE_INTERVAL_TO_MS(x) ((x) / 1000000ULL)
#define CAPTURE_INTERVAL_TO_US(x) ((x) / 1000ULL)
#define CAPTURE_INTERVAL_TO_NS(x) (x)

#define CAPTURE_INTERVAL_NTSC_FIELD 16668333
#define CAPTURE_INTERVAL_NTSC_FRAME (CAPTURE_INTERVAL_NTSC_FIELD * 2)


#if 0
/******************************************************************* SAMPLE ***/
/* Capture app pseudo code: */
/* NOTE: There is almost no error checking. The production code */
/* must have proper error handling in place. */
main() {
	void	*pointers[n_pointers] = { 0 };
	/* connect to screen */
	/* create a window */
	/* create buffers */
	/* obtain pointers to the buffers */

	/* Connect to a capture device */
	capture_context_t context = capture_create_context( flags );
	if( !context ) {
		/* TODO: Handle errors... */
	}

	const char *info = NULL;
	capture_get_property_p( context, CAPTURE_PROPERTY_DEVICE_INFO, &info );
	fprintf( stderr, "device-info = '%s'\n", info );

	/* Validate device's properties */
	if( !capture_is_property( context, CAPTURE_PROPERTY_BRIGHTNESS )
	 || !capture_is_property( context, CAPTURE_PROPERTY_CONTRAST )
	 || !capture_is_property( context, ... )
	) {
		capture_destroy_context( context );
		fprintf( stderr, "can't do it. some properties are not supported by this driver\n" );
		return EXIT_FAILURE;
	}

	/* setup capture parameters */
	capture_set_property_i( context, CAPTURE_PROPERTY_DEVICE, 1 );
	capture_set_property_i( context, CAPTURE_PROPERTY_BRIGHTNESS, 10 );
	capture_set_property_i( context, CAPTURE_PROPERTY_DST_NBUFFERS, n_pointers );
	capture_set_property_pv( context, CAPTURE_PROPERTY_DST_BUFFERS, n_pointers, pointers );

	/* tell the driver to start capturing (when capture_update() is called). */
	capture_set_property_i( context, CAPTURE_ENABLE, 1 );

	/* commit changes to the H/W -- and start capturing... */
	capture_update( context, 0 );

	while( capturing ) {
		int n_dropped;

		/* get next captured frame... */
		int idx = capture_get_frame( context, CAPTURE_TIMEOUT_INFINITE, flags );

		/* the returned idx-ed pointer is 'locked' upon return from the capture_get_frame() */
		/* this buffer will remain locked until the capture_get_frame() is called again. */

		/* update screen */
		screen_post_window( win, buf[idx], n_dirty_rects, dirty_rects, flags );

		/* Mark the buffer identifed by the idx as available for capturing. */
		capture_release_frame( context, idx );
	}

	/* stop capturing... */
	capture_set_property_i( context, CAPTURE_ENABLE, 0 );
	capture_update( context, 0 );

	...
}

#endif
__END_DECLS
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/capture/public/vcapture/capture.h $ $Rev: 732568 $")
#endif
