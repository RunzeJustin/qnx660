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

#ifndef __SYS_TRACELOG_H_INCLUDED
#define __SYS_TRACELOG_H_INCLUDED

#include <sys/types.h>
#include <sys/trace.h>

typedef struct tracelog_instance tracelog_instance_t;
typedef ssize_t (*tracelog_write_t)(void *cookie, const char *data, size_t sz);
typedef int (*tracelog_writev_t)(void *cookie, const iov_t *iov, int iovcnt);

enum tracelog_verbosity_level {
	TRACELOG_VERBOSITY_NONE = 0,
	TRACELOG_VERBOSITY_INFO,
	TRACELOG_VERBOSITY_DEBUG,
	TRACELOG_VERBOSITY_HACK,
};

/** 
 * Initialize a tracelog instance
 * 
 * @param inst receives a pointer to an initialized instance structure
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_instance_init(tracelog_instance_t **inst);

/** 
 * Destroy a tracelog instance
 * 
 * @param inst the instance to destroy
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_instance_destroy(tracelog_instance_t *inst);

/** 
 * Configure a writing callback to accept trace data
 *
 * As an example, the standard POSIX write function can be used, with the fd to write
 * to passed as the cookie. Similarly, a writev function can be passed to improve
 * performance for multi-buffer writes, although the library will use write if writev
 * is not provided.
 * 
 * @param inst pointer to an initialized instance structure
 * @param write function to accept a trace data buffer
 * @param writev function to accept an IOV of trace data buffers, or 0
 * @param cookie arbitrary data to be passed to write function
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setwriter(tracelog_instance_t *inst, tracelog_write_t write, tracelog_writev_t writev, void *cookie);

/** 
 * Configure a collection of memory buffers to receive trace data
 *
 * The default is for the library to allocate 64 buffers
 * 
 * @param inst pointer to an initialized instance structure
 * @param pbufs address of memory buffer, or NULL to have the library allocate buffers
 * @param nbufs number of buffers that can be stored at given location, or number of buffers to allocate
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setbuffers(tracelog_instance_t *inst, void *pbufs, int nbufs);

/** 
 * Configure memory that the kernel will use to store trace data
 *
 * The default is for the kernel to allocate 32 buffers
 * 
 * @param inst pointer to an initialized instance structure
 * @param pbufs physical address of buffers, or 0 to have the kernel allocate buffers
 * @param nbufs number of buffers that can be stored at given location, or number of buffers to allocate
 * @param preserve 1 to save the allocated buffer for the next invocation, 0 to free
 * @param reuse 1 to attempt to reuse a buffer saved from a previous run, 0 to allocate fresh buffers
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setkbuffers(tracelog_instance_t *inst, paddr_t pbufs, int nbufs, int preserve, int reuse);

/** 
 * Set the number of iterations over which to collect trace data
 *
 * If a value of 0 is specified, there is no iteration limit applied. This is
 * the default.
 * 
 * @param inst pointer to an initialized instance structure
 * @param niters number of iterations
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setiterations(tracelog_instance_t *inst, int niters);

/** 
 * Configures a maximum time to trace
 *
 * The trace time period will start at the call to tracelog_start if that
 * call begins tracing, otherwise the timer will be started after the first
 * buffer of trace data is logged.
 * 
 * @param inst pointer to an initialized instance structure
 * @param seconds number of seconds
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setduration(tracelog_instance_t *inst, int seconds);

/** 
 * Configures a periodic trace flush timer
 *
 * The timer will only be active while tracing is active
 * 
 * @param inst pointer to an initialized instance structure
 * @param seconds period in seconds
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setflushtimer(tracelog_instance_t *inst, int seconds);

/** 
 * Set ring or linear mode
 *
 * The default is linear mode.
 * 
 * @param inst pointer to an initialized instance structure
 * @param ring_mode 1 to set ring mode, 0 to set linear mode
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setringmode(tracelog_instance_t *inst, int ring_mode);

/** 
 * Set a maximum size for the generated output
 * 
 * @param inst pointer to an initialized instance structure
 * @param nbytes size in bytes
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setoutputcap(tracelog_instance_t *inst, int nbytes);

/** 
 * Set a header attribute value.
 *
 * The key and value will be copied uninterpreted into the trace header.
 * If the value is NULL, any existing key/value pair will be removed.
 * 
 * @param inst pointer to an initialized instance structure
 * @param key attribute key
 * @param value attribute value
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setattribute(tracelog_instance_t *inst, const char *key, const char *value);

/** 
 * Set the verbosity of libtracelog output
 *
 * By default no output is generated. Output levels are defined by tracelog_verbosity_level
 * above.
 * 
 * @param level amount of output to generate
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_setverbosity(unsigned level);

/** 
 * Start the logging mechanism.
 *
 * Starts the thread to process kernel trace data. Can optionally turn kernel tracing
 * on, if the "start" parameter is "1". If the "start" parameter is "0", tracing must
 * be enabled using "TraceEvent(_NTO_TRACE_START)".
 *
 * This call will not return until tracing is complete, either because the configured
 * maximum time or number of iterations elapses, or because another thread calls
 * "tracelog_stop".
 * 
 * @param inst pointer to an initialized instance structure
 * @param start 1 to start kernel tracing now, 0 otherwise
 * @param async 1 to create a separate thread for tracing, 0 to use the calling thread
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_start(tracelog_instance_t *inst, int start);

/** 
 * Flush trace buffers.
 *
 * Causes accumulated trace events to be flushed from the kernel to user space, and
 * from there through the specified write callback if applicable.
 * 
 * @param inst pointer to an initialized instance structure
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_flush(tracelog_instance_t *inst);

/** 
 * Get the number of bytes written during a tracelog session
 * Note that this is only valid once logging has completed.
 * 
 * @param inst the instance to query
 * @return the number of bytes written, or -1 in case of an invalid instance, or if logging is active
 */
off_t tracelog_get_bytes(const tracelog_instance_t *inst);

/** 
 * Stop the logging mechanism.
 *
 * Causes kernel tracing to stop and flushes all data. Note that termination happens
 * asynchronously, and if it is necessary to know that all tracing operations have
 * ceased then tracelog_wait should be used.
 * 
 * @param inst pointer to an initialized instance structure
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_stop(tracelog_instance_t *inst);

/** 
 * Wait for tracing to finish.
 *
 * Blocks the calling thread until tracing is finished.
 * 
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_wait(void);

/** 
 * Start a monitor to control access to trace resources.
 *
 * This allows a potential user of the kernel trace to make use of it in times
 * when it would otherwise be idle, by providing notification when other users
 * intend to use it. The supplied callback function will be called with an
 * argument of 1 when the tracelog transitions from unavailable to available,
 * and 0 when the tracelog transitions from available to unavailable.
 *
 * When the callback is called with an argument of 0 the function is expected to
 * finalize any current tracing before returning, and monitor process is expected
 * to not make any further use of kernel trace resources, until such time as the
 * callback is called again with an argument of 1. The callback is expected to
 * return with no undue delay.
 *
 * This mechanism relies on cooperation with other users of the tracelog, which
 * are expected to use the tracelog_acquire and tracelog_release functions to
 * assert ownership of trace resources. The standard utilities "tracelogger" and
 * "qconn" will cooperate in this way.
 * 
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_monitor(void (*callback)(int acquired));

/** 
 * Request the monitor to stop.
 *
 * This is only effective from within the same process that called tracelog_monitor.
 * 
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_monitor_stop(void);

/** 
 * Inform the monitor that the caller is taking ownership of kernel trace resources.
 *
 * A cooperating user of the kernel trace should call this function before making
 * any use of trace resources (e.g., calling TraceEvent or tracelog_start). If
 * there is no monitor process the function will return immediately; otherwise, it
 * will return after the monitor process has finalized its use of the trace.
 *
 * If there is a monitor process, but another process has already called
 * tracelog_acquire to assert ownership of the trace, this routine will return EBUSY.
 * If there is no monitor process, EBUSY will be returned if the kernel trace
 * is active.
 * 
 * @return EOK on success, EBUSY if tracing is already in use, or an error code
 * indicating the nature of the failure
 */
int tracelog_acquire(void);

/** 
 * Inform the monitor that the caller is releasing ownership of kernel trace resources.
 *
 * A cooperating user of the kernel trace should call this function once it has
 * finished using the kernel trace.
 *
 * @return EOK on success, or an error code indicating the nature of the failure
 */
int tracelog_release(void);


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/tracelog/public/sys/tracelog.h $ $Rev: 724903 $")
#endif
