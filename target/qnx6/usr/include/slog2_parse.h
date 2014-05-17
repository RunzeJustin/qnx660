/*****************************************************************************
 *
 * Filename:    slog2parse.h
 *
 * Created:     April 4, 2012
 *
 * Description: API for slog2parse
 *
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
 *
 ****************************************************************************/

#ifndef _SLOG2_PARSE_H_INCLUDED
#define _SLOG2_PARSE_H_INCLUDED

#include <sys/platform.h>
#include <limits.h>

__BEGIN_DECLS

/* NOTE: THIS API IS STILL SUBJECT TO CHANGE */

#define SLOG2_PARSE_MAX_NAME_SIZE 64

/**
 * Flags that control the behavior of the parsing library
 */
#define SLOG2_PARSE_FLAGS_DYNAMIC 0x00000001 /*!< used to tell slog2_parse_all to live parse */
#define SLOG2_PARSE_FLAGS_CURRENT 0x00000002 /*!< used to tell slog2_parse_all to start live parse from current moment */

/**
 * Flags related to the packet
 */
#define SLOG2_PACKET_FLAGS_FIRSTPACKET 0x00000001 /*!< the first packet in the buffer */

/**
 * a handle to a log
 */
typedef void* slog2_log_t;

typedef enum {
    SLOG2_TYPE_ASCII_STRING,
    SLOG2_TYPE_BINARY,
    SLOG2_TYPE_UNSYNC,
    SLOG2_TYPE_ONLINE
} slog2_packet_data_type_t;

/**
 * Struct containing information about a log
 */
typedef struct {
    _Uint32t            size;                           /*!< sizeof( slog2_log_into_t ), used for versioning*/
    _Uint32t            num_buffers;                    /*!< number of buffers contained in this log*/
    _Uint32t            owner_pid;                      /*!< PID of the log creator process*/
    const char         *buffer_set_name;                /*!< descriptive name of this log*/
    _Uint8t             verbosity_level;                /*!< global verbosity level of log*/
} slog2_log_info_t;
#define SLOG2_LOG_INFO_INIT { .size = sizeof( slog2_log_info_t ) }

/**
 * Struct containing information about a buffer
 */
typedef struct {
    _Uint32t            size;                           /*!< sizeof( slog2_buffer_into_t ), used for versioning*/
    _Uint32t            buffer_size;                    /*!< size of the buffer*/
    const char         *buffer_name;                    /*!< name describing the contents of this buffer*/
} slog2_buffer_info_t;
#define SLOG2_BUFFER_INFO_INIT { .size = sizeof( slog2_buffer_info_t ) }


/**
 * Struct containing information about a packet.
 */
typedef struct {
    _Uint32t                    size;                   /*!< sizeof( slog2_packet_into_t ), used for versioning*/
    _Uint16t                    sequence_number;        /*!< system-global sequence number*/
    _Uint16t                    data_size;              /*!< size of object being returned*/
    _Uint64t                    timestamp;              /*!< packet timestamp*/
    slog2_packet_data_type_t    data_type;              /*!< data type of payload*/
    _Uint16t                    thread_id;              /*!< thread id of logging thread*/
    _Uint16t                    code;                   /*!< logging code*/
    _Uint8t                     severity;               /*!< the severity level of the packet*/
    char                        file_name[ 2 * SLOG2_PARSE_MAX_NAME_SIZE ];  /*!< file name this packet belongs to*/
    char                        buffer_name[ SLOG2_PARSE_MAX_NAME_SIZE ];    /*!< buffer name this packet belongs to*/
    _Uint32t                    owner_pid;              /*!< PID of the log creator process*/
    _Uint32t                    flags;                  /*!< flags related to this packet */
} slog2_packet_info_t;
#define SLOG2_PACKET_INFO_INIT { .size = sizeof( slog2_packet_info_t ) }

/**
 * user supplied callback function
 * @param info    pointer to a slog2_packet_info_t struct
 * @param payload pointer to the packet payload
 * @param param user specified parameter passed back to the callback.
 * @return        0 on success, non-zero failure
 */
typedef int (*slog2_packet_callback)( slog2_packet_info_t *__info, void *__payload, void *__param );

/**
 * Opens a log
 * @param filename file name of log file
 * @return handle to log, or 0 on error
 */
slog2_log_t slog2_open_log( const char *__filename );

/**
 * Closes a log
 * @param log handle previously returned by slog2_open_log
 */
void slog2_close_log( slog2_log_t __log );

/**
 * populate a user supplied slog2_log_info struct
 * @param log       handle previously returned by slog2_open_log
 * @param log_info  pointer to a user supplied slog2_log_info struct
 * @return          0 on success, -1 on failure
 */
int slog2_get_log_info( slog2_log_t __log, slog2_log_info_t *__log_info );

/**
  * Compare two packets and return -1 if packet1 is less than packet2, 0 if
  * they are equal, and 1 if packet1 is larger than packet2.
  *
  *@param element1 First packet
  *@param element2 Second packet
  *@return -1, 0, 1 if elem1 < elem2, elem1 == elem2, elem1 > elem2
  */
int slog2_packet_cmp ( slog2_packet_info_t *__packet1,
                       slog2_packet_info_t *__packet2 );


/**
 * populate a user supplied slog2_buffer_info struct
 * @param log           handle previously returned by slog2_open_log
 * @param buffer_index  buffer index; indexes range from 0 to (slog2_log_info.num_buffers - 1)
 * @param buffer_info   pointer to a user supplied slog2_buffer_info struct
 * @return              0 on success, -1 on failure
 */
int slog2_get_buffer_info( slog2_log_t __log, int __buffer_index, slog2_buffer_info_t *__buffer_info );

/**
 * parses through a static buffer within the log from beginning to end finding valid packets and
 * calling a user supplied callback function for each packet. If the user supplied callback
 * returns a non-zero value then this function will return immediately.
 * @param log           handle previously returned by slog2_open_log
 * @param buffer_index  buffer index; indexes range from 0 to (slog2_log_info.num_buffers - 1)
 * @param packet_info   pointer to a user supplied packet_info struct which
 *                      will get  populated and passed to the callback
 * @param callback      callback function, see definition of slog2_packet_callback
 * @param param parameter passed to the callback function
 * @return              0 on success, -1 on failure
 */
int slog2_parse_static_buffer( slog2_log_t __log,
                               int __buffer_index,
                               slog2_packet_info_t *__packet_info,
                               slog2_packet_callback __callback,
                               void *__param );

/**
 * performs live parsing of a buffer. If the user supplied callback
 * returns a non-zero value then this function will return immediately.
 * @param log           handle previously returned by slog2_open_log
 * @param buffer_index  buffer index; indexes range from 0 to (slog2_log_info.num_buffers - 1)
 * @param packet_info   pointer to a user supplied packet_info struct which
 *                      will get  populated and passed to the callback
 * @param callback      callback function, see definition of slog2_packet_callback
 * @param param parameter passed to the callback function
 * @return              0 on success, -1 on failure.
 */
int slog2_parse_dynamic_buffer( slog2_log_t __log,
                                int __buffer_index,
                                slog2_packet_info_t *__packet_info,
                                slog2_packet_callback __callback,
                                void *__param );

/**
 * parses all files in a given directory path or the live directory path if
 * the path supplied is NULL. The output is in a merged format according
 * to the time they occured.
 * 
 * The following flags are available:
 *      SLOG2_PARSE_FLAGS_DYNAMIC
 *          - Live streaming of all buffers merged. directory_path must be
 *             NULL.
 *
 * @param flags           flags to control the processing of the files
 * @param directory_path  the path where to parse all files
 * @param match_list comma seperated list of buffer_set names to match
 * @param packet_info   pointer to a user supplied packet_info struct which
 *                      will get  populated and passed to the callback
 * @param callback      callback function, see definition of slog2_packet_callback
 * @param param parameter passed to the callback function
 * @return              0 on success, -1 on failure.
 */
int slog2_parse_all( _Uint32t __flags,
                     char *__directory_path,
                     char *__match_list,
                     slog2_packet_info_t *__packet_info,
                     slog2_packet_callback __callback,
                     void *__param );


__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/slog2parse/public/slog2_parse.h $ $Rev: 724903 $")
#endif
