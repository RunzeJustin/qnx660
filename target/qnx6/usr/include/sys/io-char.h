/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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



/*
 *  io-char.h     Character device library interface.
 *

 */

#ifndef __IO_CHAR_H_INCLUDED
#define __IO_CHAR_H_INCLUDED

#ifndef _QNX_SOURCE
#define _QNX_SOURCE
#endif

struct ttydev_entry;

#ifdef __IOFUNC_H_INCLUDED
#error sys/iofunc.h already included
#endif
#define IOFUNC_ATTR_T		struct ttydev_entry
#include <sys/iofunc.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/queue.h>

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _TERMIOS_H_INCLUDED
#include <termios.h>
#endif

__BEGIN_DECLS

/* Flag definitions */
#define EVENT_QUEUED		0x0000001
#define EVENT_SIGINT		0x0000002
#define EVENT_SIGHUP		0x0000004
#define EVENT_TTO			0x0000008
#define EVENT_READ			0x0000010
#define EVENT_WRITE			0x0000020
#define EVENT_DRAIN			0x0000040
#define EVENT_TIMEOUT		0x0000080
#define EVENT_NOTIFY_INPUT	0x0000100
#define EVENT_NOTIFY_OUTPUT	0x0000200
#define EVENT_NOTIFY_OBAND	0x0000400
#define EVENT_CARRIER		0x0000800
#define EVENT_SIGQUIT		0x0004000
#define EVENT_SIGSUSP		0x0008000

#define OHW_PAGED			0x0001000	/* OHW_PAGED and OSW_PAGED flags share the same bits */
#define IHW_PAGED			0x0002000	/* IHW_PAGED and ISW_PAGED flags share the same bits */
#define OSW_PAGED			0x0001000
#define ISW_PAGED			0x0002000
#define EDIT_INSERT			0x0010000
#define EDIT_PREFIX			0x0020000
#define OBAND_DATA			0x0040000
#define LOSES_TX_INTR		0x0080000
#define TIMER_ACTIVE		0x0100000
#define TIMER_KEEP			0x0200000
#define NOTTY				0x0400000	/* Used by Pty's */
#define NL_INSERT			0x0800000	
#define ISAPTY				0x1000000	/* Is a pty */
#define DEV_ACTIVE			0x2000000	/* Used by pty's to indicate device history */
#define LITERAL				0x4000000
#define FIRST_TIME_ALONE	0x8000000	/* Many->One reader transition (see wait.c) */

/* Extra/Extended flags definitions */
#define  OSW_PAGED_OVERRIDE  0x0000001   /* Software flow control override (when set allow transmit of one byte when output is suspended) */
#define  MODEM_DISCONNECT    0x0000002   /* Used to prevent read/write while in a disconnected state */ 
#define  IBUF_TRANSITION     0x0000004	 /* Used to flag when the input buffer has changed from empty to non-empty */
#define  SERCTL_INPROG		 0x0000008	 /* Used to hold of write requests until current SERCTL operation is complete */

/* Logging Flags */
#define  LOG_LAST_IPAGED     0x0000001    /* Last logged state for input flow control (set/cleared) */
#define  LOG_LAST_OPAGED     0x0000002    /* Last logged state for output flow control (set/cleared) */
#define  LOG_BREAK           0x0000010
#define  LOG_INTR            0x0000020
#define  LOG_TX_DATA         0x0000040    /* Log TX data to file */
#define  LOG_RX_DATA         0x0000080	  /* Log RX data to file */

/* Event Masks */
#define  IS_ERROR_EVENT      0x000000f

/* Event flags */
#define  EVENT_PARITY      0x0000001    /* Parity Error  */
#define  EVENT_FRAME       0x0000002    /* Framing Error */
#define  EVENT_OVERRUN     0x0000004    /* HW fifo Overrun Error */
#define  EVENT_OVERRUN_SW  0x0000008    /* SW buffer Overrun Error */
#define  EVENT_IPAGED      0x0000010    /* Change in input flow control state */
#define  EVENT_OPAGED      0x0000020    /* Change in output flow control state */
#define  EVENT_OPEN        0x0000040    /* Open event to service clients on the waiting_open list */
#define  EVENT_TIMER_QUEUE 0x0000080	/* Queue a timer */
#define  EVENT_CUSTOM      0x0000100	/* Custom driver event callout */
#define  EVENT_FLUSH_TX_LOG 0x0000200    /* Write logged TX data to file */
#define  EVENT_FLUSH_RX_LOG 0x0000400    /* Write logged RX data to file */

/* Verbosity Levels  */
#define  EVENT 3
#define  POWER 5


/* These codes must start above an 8 bit character code. */
enum {
	TTI_BREAK    = 0x100,
	TTI_OVERRUN  = 0x200,
	TTI_FRAME    = 0x300,
	TTI_PARITY   = 0x400,
	TTI_CARRIER  = 0x500,
	TTI_HANGUP   = 0x600,
	TTI_OHW_STOP = 0x700,
	TTI_OHW_CONT = 0x800,
	TTI_OSW_STOP = 0x900,
	TTI_OSW_CONT = 0xa00,
	TTI_QUIT     = 0xb00,
	TTI_SUSP     = 0xc00,
	TTI_INTR     = 0xd00
	};

enum {
	TTO_DATA,
	TTO_STTY,
	TTO_CTRL,
	TTO_EVENT,
	TTO_LINESTATUS
	};

enum {
	TTC_INIT_PROC,
	TTC_INIT_CC,
	TTC_INIT_START,
	TTC_INIT_RAW,
	TTC_INIT_EDIT,
	TTC_INIT_ATTACH,
	TTC_SET_OPTION,
	TTC_TIMER_QUEUE,
	TTC_INIT_PTY,
	TTC_INIT_TTYNAME,
	TTC_TTY_DETACH,
	TTC_INIT_POWER,
	TTC_INIT_STOP
	};

/*TTC_INIT_ATTACH flags */
#define NUMBER_DEV_FROM_INODE	0x80000000	/*Device has number appended to it from inode (0based)*/
#define NUMBER_DEV_1_BASED		0x40000000	/*Device has number from inode incremented by 1*/
#define NUMBER_DEV_FROM_USER	0x20000000	/*Device has a number specified by the user*/
#define USE_GENERIC_CLASS		0x00800000	/*Use the generic "device" class*/

#if 0 /* This is off until we are more sure the dev specific locks work */
#define dev_lock(dev)		(InterruptLock(&(dev)->lock))
#define dev_unlock(dev)		(InterruptUnlock(&(dev)->lock))
#else
#define dev_lock(dev)		(InterruptLock(&ttyctrl.lock))
#define dev_unlock(dev)		(InterruptUnlock(&ttyctrl.lock))
#endif

#define IO_CHAR_COMMON_OPTIONS	"veEfFsSC:I:O:o:"
#define IO_CHAR_SERIAL_OPTIONS	IO_CHAR_COMMON_OPTIONS "b:"
#define IO_CHAR_DEFAULT_BITSIZE 12
#define IO_CHAR_PMM_NAME_MAX	256 	
#define IO_CHAR_USEC_PER_SEC 	1000000  /* Number of useconds in a second */

#define SET_NAME_NUMBER(x)		(((x) & 0x3ff) << 10)	/* 10 bit name number */
#define GET_NAME_NUMBER(x)		(((x) >> 10) & 0x3ff)


#define OBUF_SAFETY   5  /* extra obuf space to allow injection of software flow control characters */

typedef struct ttyinit_entry {
	_Paddr64t		port;
	unsigned		port_shift;
	unsigned		intr;
	int				baud;
	int				isize;
	int				osize;
	int				csize;
	int				c_cflag;
	int				c_iflag;
	int				c_lflag;
	int				c_oflag;
	int				fifo;
	int				clk;
	int				div;
	char			name[TTY_NAME_MAX];
	char			*reserved1;
	unsigned		reserved2;
	int      		verbose; /* Driver verbosity */
	int      		highwater;	/* ibuf highwater mark for flow control */
	char    		logging_path[_POSIX_PATH_MAX];
	unsigned		lflags;  		/* Logging flags */
} TTYINIT;


typedef struct ttybuf_entry {
	int			 	cnt;
	int			 	size;
	unsigned char	*buff;
	unsigned char	*head;
	unsigned char	*tail;
} TTYBUF; 

/* TTYCTRL flags */
#define  DEBUG_BREAK           0x0000001
#define  NODAEMONIZE           0x0000002
#define  CREATE_CLEANUP_THREAD 0x0000004

typedef struct chario_entry {
	dispatch_t		*dpp;
	void			*msg_ctp;
	int				tid;
	int				coid;
	int				timerid;
	int 			reserved1;
	int				start;
	unsigned		max_devs;
	unsigned		num_devs;
	struct sigevent	event;
	struct sigevent	timer;
	struct ttydev_entry	*timer_list;
	unsigned		num_events;
	struct ttydev_entry	**event_queue;
	intrspin_t		lock;
	void  			*reserved2;
	unsigned		flags;
	unsigned		perm;
	pthread_mutex_t timer_mutex;
	TAILQ_HEAD(ttylist_head,ttydev_entry) dlist;
} TTYCTRL;

typedef struct ttywait_entry {
	struct ttywait_entry 	*next;
	int			rcvid;
	int			scoid;
	int			coid;
	int			offset;
	int			nbytes;
	pid_t		pid;
	int			tid;
} TTYWAIT;

typedef struct ttyinitpty_entry {
	TTYWAIT *(*wait_add)(TTYWAIT **, resmgr_context_t *, int);
} TTYINITPTY;

/* io-char's data to save in persistent storage */
typedef struct psdata_entry {
	int						c_cflag;
	int						c_iflag;
	int						c_lflag;
	int						c_oflag;
    cc_t			 		c_cc[NCCS];
	int			 			baud;
} PSDATA;


typedef struct ttydev_entry {
	iofunc_attr_t			attr;
	iofunc_mount_t			mount;
	TTYWAIT					*waiting_read;
	TTYWAIT					*waiting_write;
	TTYWAIT					*waiting_drain;
	TTYWAIT					*waiting_devctl;
	int						c_cflag;
	int						c_iflag;
	int						c_lflag;
	int						c_oflag;
	volatile unsigned		flags;
	volatile unsigned		xflags;  /* Extended flags, for miscellaneous flags */
	volatile unsigned		eflags;  /* Event flags, extention to the events in the flags variable */
	volatile unsigned		lflags;  /* Logging flags */
	int						verbose; /* Driver verbosity */
	unsigned int			bcnt;
	unsigned int			fwdcnt;
	struct ttydev_entry		*timer;
	int			 			timeout;
	int			 			timeout_reset;
	union {
		/* Note: io-char requires members of the union are the same size */
		uint64_t			tmrs;
		struct {
			char 			drn_tmr;	/* drain timer */
			char 			tx_tmr;		/* loses tx interrupt timer */
			char 			brk_tmr;	/* break timer */
			char 			dtr_tmr;	/* dtr line timer */
			char 			spare_tmr;	/* spare timer for driver use ONLY */
			char 			dsr_tmr;	/* for device side driver where DSR is an output */
			char 			dcd_tmr;	/* for device side driver where DCD is an output */
			char 			rsvd3; 		/* Reserved for more timers to be added */
		}	s;
	} 		un;
	pid_t					brkpgrp;
	pid_t			 		huppid;
    cc_t			 		c_cc[NCCS];
	unsigned char		 	fifo;
	unsigned char		 	fwd;
	unsigned char		 	prefix_cnt;
	unsigned char		 	oband_data;
	int			 			highwater;
	int			 			baud;
	struct winsize			winsize;
	TTYBUF	 				obuf;
	TTYBUF	 				obuf_log;
	TTYBUF	 				ibuf;
	TTYBUF	 				ibuf_log;
	TTYBUF	 				cbuf;
	iofunc_notify_t		 	notify[3];
	struct ttydev_entry		*extra;
	TTYWAIT					*waiting_open;
	int						linkid;			/* id returned from resmgr_attach */
	void					*reserved2;		/* reserved for use by io-char */
	int						(*io_devctlext)(resmgr_context_t *ctp, io_devctl_t *msg, iofunc_ocb_t *ocb);
	int						(*custom_event_handler) (struct ttydev_entry *tty);
	char			 		name[TTY_NAME_MAX];
	char                    *logging_path;
	int                     tx_log_fd;
	int                     rx_log_fd;
	/* supress flooding slog with errors */
	volatile unsigned 		shush; 
	TAILQ_ENTRY(ttydev_entry) dlist_next;	/* Link for main device list */
	} TTYDEV;

extern int  drain_check(TTYDEV *dev, uintptr_t *cnt);
extern int  dev_cleanup(TTYDEV *dev);

extern int	ttc(int type, void *ptr, int arg);
extern int 	tti(TTYDEV *dev, unsigned c);
extern int 	tti2(TTYDEV *dev, unsigned char *char_buf, int len, uint16_t err_code);
extern int 	tto(TTYDEV *dev, int action, int arg);
extern void kick(TTYDEV *dev);
extern void tx_inject(TTYDEV *dev, unsigned char c);
extern void iochar_send_event(TTYDEV *dev);
extern TTYWAIT *wait_add(TTYWAIT **queue, resmgr_context_t *ctp, int offset);
extern int wait_remove_rcvid(TTYWAIT **head, int rcvid, int *offset);
extern unsigned char tto_getchar( TTYDEV *dev);
extern int tto_write_block(TTYDEV *dev, char *buf, int buf_size, int *byte_cnt);
extern int tto_checkclients(TTYDEV *dev);
extern void timer_queue(TTYDEV *dev);
extern void timer_remove(TTYDEV *dev);

extern resmgr_io_funcs_t		iochar_io_funcs;
extern resmgr_connect_funcs_t	iochar_connect_funcs;

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/io-char/public/sys/io-char.h $ $Rev: 730973 $")
#endif
