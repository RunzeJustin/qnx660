/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_CRYPTO_H_INCLUDED
#define __FS_CRYPTO_H_INCLUDED


/*  Domains can be assigned a type at creation time.  The type describes
	the mechanisms used to complete the actual encryption and decryption
	of file data.  This field is only a byte in size.  Note only a
	limited number of encryption methods may be available.
*/
enum _tagFsEncryptTypes {
	FS_CRYPTO_TYPE_NONE             = 0,
	FS_CRYPTO_TYPE_XTS,
	FS_CRYPTO_TYPE_CBC,

	FS_CRYPTO_TYPE_USER1            = 100,
	FS_CRYPTO_TYPE_USER2,
	FS_CRYPTO_TYPE_USER3,

	/* Private range for internal use 200..255 */
	FS_CRYPTO_TYPE_INTERNAL         = 200,

	FS_CRYPTO_TYPE_TESTV1           = 254,
	FS_CRYPTO_TYPE_RESERVED         = 255
};

#define FS_CRYPTO_MIN_TYPE_VAL      (1)
#define FS_CRYPTO_MAX_TYPE_VAL      (FS_CRYPTO_TYPE_RESERVED)
#define FS_CRYPTO_IS_VALID_TYPE(n)				\
			( ((n)>FS_CRYPTO_TYPE_NONE) && ((n)<FS_CRYPTO_TYPE_RESERVED) )


/*  Actions that can be completed against an open file descriptor.
*/
enum _tagFsEncryptActions {
	FS_CRYPTO_INVALID,
	FS_CRYPTO_SUPPORT_CHECK,
	FS_CRYPTO_CREATE_DOMAIN,
	FS_CRYPTO_DESTROY_DOMAIN,
	FS_CRYPTO_QUERY_DOMAIN,
	FS_CRYPTO_LOCK_DOMAIN,
	FS_CRYPTO_UNLOCK_DOMAIN,
	FS_CRYPTO_SET_FILE_DOMAIN,
	FS_CRYPTO_GET_FILE_DOMAIN,
	FS_CRYPTO_READ_FILE_KEY,
	FS_CRYPTO_WRITE_FILE_KEY,
	FS_CRYPTO_ENABLE,
	FS_CRYPTO_CHANGE_DOMAIN_KEY,
	FS_CRYPTO_CHECK_DOMAIN_KEY,
	FS_CRYPTO_MIGRATE_TAG,
	FS_CRYPTO_MIGRATE_STATE,
	FS_CRYPTO_MIGRATE_CONTROL,
    FS_CRYPTO_MIGRATE_STATUS,
	FS_CRYPTO_NUM_ACTIONS
};

#define FS_CRYPTO_CMD_STR_LIST        	\
    {                               	\
        "<invalid-command>",        	\
        "Support Check",            	\
        "Create Domain",    			\
        "Destroy Domain",     			\
        "Query Domain",     			\
        "Lock Domain",     				\
        "Unlock Domain",     			\
        "Set File Domain",     			\
        "Get File Domain",     			\
        "Read File Key",     			\
        "Write File Key",     			\
        "Enable Encryption",			\
        "Change Domain Key",            \
        "Check Domain Key",             \
        "Tag File For Migration",       \
        "Get Migration State",          \
        "Control Migration",            \
        "Get Migration Status",         \
    }

#define FS_CRYPTO_DECL_CMD_STRINGS      							\
	const char *aszFsEncCmdStr[] = FS_CRYPTO_CMD_STR_LIST;

#define FS_CRYPTO_CMD_STR(r)              							\
			((r)<(sizeof(aszFsEncCmdStr)/sizeof(aszFsEncCmdStr[0]))	\
			? aszFsEncCmdStr[(r)]									\
			: "<out-of-bounds command>")


/* Allowed domains are numbered 1..100 */
#define FS_CRYPTO_MIN_DOM_VAL           (1)
#define FS_CRYPTO_MAX_DOM_VAL           (100)
#define FS_CRYPTO_ANON_DOM_VAL          (255)
#define FS_CRYPTO_UNASSIGNED_DOMAIN     (0)

/*	Flags used to enable certain features on the fsf-crypt filter.
	These flags are absolute, ie, not interpreted as a bitmask. They will be ignored
	on all commands other than ENABLE.
*/

/*	Defines if the whole disk is being encrypted under one domain.
	This will assume all plaintext files are 'tagged' to be migrated.
	This also hides all plaintext files from being viewed or accessed.
*/
#define FS_CRYPTO_ENABLE_WHOLE_DISK			0x1


/*  Describes the state of the migration thread.
*/
typedef enum migrate_state_e {
    /*  The migrate thread is idle, waiting for work to do.
    */
    MIGRATE_STATE_IDLE      = 0,

    /*  The migrate thread is scanning the filesystem for inodes that have
        outstanding migration to be performed.
    */
    MIGRATE_STATE_SCANNING  = 1,

    /*  The migrate thread is actively completing a unit of work.
    */
    MIGRATE_STATE_MIGRATING = 2,

    /*  The migrate thread has completed a work unit and is waiting for its
        delay period to expire before checking for additional work.
    */
    MIGRATE_STATE_DELAYING  = 3,

    /*  The migrate thread is disabled and shutting down.
    */
    MIGRATE_STATE_DISABLED  = 4,
} migrate_state_t;

#define FS_CRYPTO_MIGRATE_STATE_STR_LIST    \
    {                                       \
        "IDLE",                             \
        "SCANNING",                         \
        "MIGRATING",                        \
        "DELAYING",                         \
        "DISABLED",                         \
    }

#define FS_CRYPTO_MIGRATE_STATE_STR_DECL    \
	static const char *aszFsEncMigrateStateStr[] = FS_CRYPTO_MIGRATE_STATE_STR_LIST

#define FS_CRYPTO_MIGRATE_STATE_STR(r)                                          \
    ((r)<(sizeof aszFsEncMigrateStateStr / sizeof aszFsEncMigrateStateStr[0])   \
        ? aszFsEncMigrateStateStr[(r)]                                          \
        : "<out-of-bounds migration state>")

/*  Migration of files into an encrypted domain is completed in units of work
	that is slightly abstracted from the caller.  A low number of units will
	complete the migration slower with less impact to the file system responsiveness.
	Larger units will be more efficient and faster at a cost to file system
	performance.  Zero indicates the file system should make a decsision
	with regard to the size of an operation to complete.
*/
#define FS_CRYPTO_WORK_UNIT_DEFAULT      (0)
#define FS_CRYPTO_WORK_UNIT_MIN          (0)
#define FS_CRYPTO_WORK_UNIT_MAX          (1024)
#define FS_CRYPTO_MIGRATE_ANY            (-1)

/*	Disable the migration service. This implies the migration service will be
	paused and then stopped. The context argument is ignored for this flag.
*/
#define FS_CRYPTO_MIGRATE_DISABLE	0x00000001U


/*	Start the migration service or resume the migration service if paused. The
	context agrument is ignored for this flag.
*/
#define FS_CRYPTO_MIGRATE_START		0x00000002U


/*	Pause the migration service. The service will be paused after completion
	of either:
		1) The current migration unit is completed.
		2) The scan for files to be migrated is completed.
	The context argument is ignored for this flag.
*/
#define FS_CRYPTO_MIGRATE_PAUSE		0x00000004U


/*	Set the period in between units of migration work. The context argument will
	be interpreted as a 32-bit unsigned integer describing the number of
	milliseconds to be used as the period.
*/
#define FS_CRYPTO_MIGRATE_PERIOD	0x00000008U


/*	Sets the number of filesystem blocks to migrate in one unit of work. The
	context argument will be interpreted as a 32-bit unsigned integer describing
	the number of filesystem blocks to migrate in one unit.
*/
#define FS_CRYPTO_MIGRATE_UNITS		0x00000010U


/*  Flag indicating an error has been injected into the migration process.
*/
#define FS_CRYPTO_MIGRATE_ERROR_INJECTED    0x00000020U

/*  The latest version of the migrate_status_t structure defined below.
*/
#define MIGRATE_STATUS_VERSION      1

/*  Structure describing the status of migration.
*/
typedef struct migrate_status_s {
    uint32_t            s_version;          /*  The version of this structure.  */
    migrate_state_t     s_state;            /*  The current state of migration. */
    uint64_t            s_remaining;        /*  Number of bytes to be migrated. */
    uint64_t            s_migrate_inode;    /*  Inode # of last migration unit. */
    int                 s_migrate_error;    /*  Error of last migration unit.   */
    /*  Version 1 END */
} migrate_status_t;

/*  Provides the unpadded size in bytes of the migrate_status_t structure for a
    particular version. The returned size does not include any padding that may
    be added by the compiler, so this size should be used as a minimum structure
    size, and *not* for allocating a migrate_status_t structure.

    Parameters
        version - The version of the migrate_status_t structure to determine.

    Returns
        The unpadded size in bytes of the migrate_status_t structure with the
        specified version. If no such version exists, 0 is returned.
*/
static __inline__ unsigned migrate_status_version_size(
    uint32_t version)
{
    unsigned size;

    switch (version) {
    case 1:
        size  = (unsigned)(&((migrate_status_t *)0)->s_migrate_error);
        size += sizeof (((migrate_status_t *)0)->s_migrate_error);
        break;
    default:
        size = 0;
        break;
    }

    return size;
}

/* Actions sent through the fs_crypto ioctl are limited to one byte. */
#define FS_CRYPTO_ACTION_MASK           (0x000000ff)
#define FS_CRYPTO_ACTION_RESERVED       (0xffffff00)

/* The current implementation restricts the size of keys. Note, these
   may change in the future.  The largest file key size is currently
   composed of two records (domain and file) and up to block size - 1
   bytes for the last portion of the file that is composed of both
   encrypted file data and the filesystem allocation block.
*/
#define FS_CRYPTO_RECORD_SIZE           (512)
#define FS_CRYPTO_MAX_KEY_SIZE          (512/8)
#define FS_CRYPTO_MIN_FILE_KEY_SIZE     (512+512+511)
#define FS_CRYPTO_MAX_FILE_KEY_SIZE     (512+512+4095)

#define FS_CRYPTO_IS_VALID_ACTION(n)						\
			( ((n)>FS_CRYPTO_INVALID) && ((n)<FS_CRYPTO_NUM_ACTIONS) )

#define FS_CRYPTO_IS_VALID_DOMAIN(n)						\
			(  ((n)>=FS_CRYPTO_MIN_DOM_VAL) && ((n)<=FS_CRYPTO_MAX_DOM_VAL) )


/*  Any changes to the id codes need to be matched to the string
    declaration lists below.
*/
enum _tagFsEncryptReply {
	FS_CRYPTO_REPLY_INVALID		=	0,
	FS_CRYPTO_REPLY_UNKNOWN_CMD,
	FS_CRYPTO_REPLY_UNKNOWN_DOMAIN,
	FS_CRYPTO_REPLY_UNKNOWN_TYPE,
	FS_CRYPTO_REPLY_BAD_LEN,
	FS_CRYPTO_REPLY_BAD_FILE,
	FS_CRYPTO_REPLY_BAD_KEY,
	FS_CRYPTO_REPLY_NOT_ZERO,
	FS_CRYPTO_REPLY_DOMAIN_EXISTS,
	FS_CRYPTO_REPLY_NOT_ASSIGNED,
	FS_CRYPTO_REPLY_READONLY,

	FS_CRYPTO_REPLY_ALREADY,
	FS_CRYPTO_REPLY_SUPPORTED,
	FS_CRYPTO_REPLY_NOENTRY,
	FS_CRYPTO_REPLY_LOCKED,
	FS_CRYPTO_REPLY_UNLOCKED,

	FS_CRYPTO_REPLY_COMPLETE,
	FS_CRYPTO_REPLY_ERRNO,
	FS_CRYPTO_REPLY_NOSUPPORT,
	FS_CRYPTO_REPLY_NOT_MOUNT,
	FS_CRYPTO_NUM_REPLIES
};

#define FS_CRYPTO_REPLY_STR_LIST     \
    {                                \
        "<invalid-reply>",           \
        "Unknown command",           \
        "Unknown domain number",     \
        "Unknown encryption type",   \
        "Bad length",                \
        "Bad file",                  \
        "Bad key data",              \
        "File is not zero length",   \
        "Domain exists",             \
        "Not assigned",              \
        "Read-only file system",     \
        "Already done",              \
        "Supported",                 \
        "No entry found",            \
        "Domain locked",             \
        "Domain unlocked",           \
        "complete",                  \
        "See errno",                 \
        "No support",                \
        "Not a mount point",         \
    }

#define FS_CRYPTO_DECL_REPLY_STRINGS    								\
	const char *aszFsEncReplyStr[] = FS_CRYPTO_REPLY_STR_LIST;

#define FS_CRYPTO_REPLY_STR(r)              							\
			((r)<(sizeof(aszFsEncReplyStr)/sizeof(aszFsEncReplyStr[0]))	\
				? aszFsEncReplyStr[(r)] : "<out-of-bounds reply>")

#endif /* __FS_CRYPTO_H_INCLUDED */




#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/services/blk/io-blk/public/sys/fs_crypto.h $ $Rev: 733328 $")
#endif
