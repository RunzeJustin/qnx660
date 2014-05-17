/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 *  dcmd_sim_sercd.h   Non-portable low-level devctl definitions
 *
*/

#ifndef __DCMD_SIM_SERCD_H_INCLUDED
#define __DCMD_SIM_SERCD_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#include <_pack64.h>

#define SERCD_BCD_DEC( _bcd )		( ( ( ( (_bcd) >> 8 ) & 0xf ) * 100 ) + ( ( ( (_bcd) >> 4 ) & 0xf ) * 10 ) + ( (_bcd) & 0xf ) )
#define SERCD_DEC_HTU_BCD( _dec )	( ( ( (_dec) / 100 ) << 8 ) | ( ( ( (_dec) % 100 ) / 10 ) << 4 ) + ( (_dec) % 10 ) )
#define SERCD_DEC_H_BCD( _dec )		( (_dec) / 100 )
#define SERCD_DEC_T_BCD( _dec )		( ( ( (_dec) % 100 ) / 10 ) << 4 )
#define SERCD_DEC_U_BCD( _dec )		( (_dec) % 10 )
#define SERCD_DEC_TU_BCD( _dec )	( ( ( ( (_dec) % 100 ) / 10 ) << 4 ) | ( (_dec) % 10 ) )

#define SERCD_MAX_MSG             255

     /* timeout - raw_cmd and raw_rcvmsg */
#define SERCD_TIME_DEFAULT        0x00000000  /* request timeout in seconds */
#define SERCD_TIME_INFINITY       0xffffffff  /* infinite timeout */

     /* flags - raw_cmd and raw_rcvmsg */
#define SERCD_FLG_MSG_CANCEL            0x01  /* cancel pending messages */
#define SERCD_FLG_MSG_IMMEDIATE         0x02  /* immediate message (no completion) */

#define SERCD_STATUS_REQ_INPROG         0x00  /* request in progress */
#define SERCD_STATUS_REQ_CMP            0x01  /* request complete */
#define SERCD_STATUS_REQ_ABORTED        0x02  /* request aborted */
#define SERCD_STATUS_REQ_CMP_ERR        0x04  /* request complete with error */
#define SERCD_STATUS_REQ_INVALID        0x06
#define SERCD_STATUS_REQ_TIMEOUT        0x0b  /* request timeout */

     /* flags - raw_cmd only */
#define SERCD_FLG_CMD_RETRY             0x10  /* retry command on timeout */
#define SERCD_FLG_CMD_NOSTAT            0x20  /* no status */
#define SERCD_FLG_CMD_IMMEDIATE         0x40  /* no completion */
#define SERCD_FLG_CMD_CMP               0x80  /* wait for command complete */
#define SERCD_FLG_CMD_FORCE             0x100 /* issue command regardless of state */

/* command format */
/* byte     0         1        ... */
/*      cmd byte    parm n     ... */

/* message format */
/* byte     0         1           2           3          ... */
/*      num bytes   ident     data byte   data byte n    ... */

typedef struct _sercd_raw_cmd {
    _Uint32t            flags;             /* see SERCD_FLG_xxxx */
    _Uint32t            status;            /* see SERCD_STATUS_xxxx */
    _Uint32t            timeout;           /* timeout in seconds */
    _Uint8t             mech_state;        /* mechanism state (drive specific) */
    _Uint8t             mech_status;       /* mechanism status (drive specific) */
    _Uint8t             clength;           /* command length */
    _Uint8t             mlength;           /* message length */
    _Uint8t             mid;               /* message identification */
    _Uint8t             nmids;
    _Uint8t             rsvd[6];
/*   unsigned char      data[ clength/mlength ];  variable length cmd/msg data */
} SERCD_RAW_CMD;

typedef struct _sercd_raw_rcvmsg {
    _Uint32t            flags;             /* see SERCD_FLG_xxxx */
    _Uint32t            status;            /* see SERCD_STATUS_xxxx */
    _Uint32t            timeout;           /* timeout in seconds */
    _Uint8t             mech_state;        /* mechanism state (drive specific) */
    _Uint8t             mech_status;       /* mechanism status (drive specific) */
    _Uint8t             mlength;           /* message length */
    _Uint8t             mid;               /* message identification */
    _Uint8t             nmids;
    _Uint8t             rsvd[7];
/*   unsigned char      data[ mlength ];  variable length data */
} SERCD_RAW_RCVMSG;

#define SERCD_APM_LEVEL					0x00     /* Set apm level */
#define SERCD_APM_CPM					0x01     /* Check Power Mode */
	#define SERCD_CPM_STANDBY			0x00     /* drive in standby (returned) */
	#define SERCD_CPM_STANDBY_MEDIA		0x01     /* drive in standby media (qnx specific) */
	#define SERCD_CPM_IDLE				0x80     /* drive idle (returned) */
	#define SERCD_CPM_ACTIVE			0xff     /* drive active (returned) */
	#define SERCD_CPM_IDLE_ACTIVE		0xff     /* drive idle or active (returned) */
#define SERCD_APM_MODE					0x02     /* Set apm mode */
	#define SERCD_MODE_ACTIVE			0x01
	#define SERCD_MODE_IDLE				0x02
	#define SERCD_MODE_STANDBY			0x03
	#define SERCD_MODE_SLEEP			0x05
	#define SERCD_MODE_STANDBY_MEDIA	0x80     /* Standby Media (fail media access) */
#define SERCD_APM_STANDBY_INTERVAL		0x03     /* Set apm standby interval */
   /* level         timeout period */
   /* 0           timeout disabled */
   /* 1-240       ( value * 5 ) seconds */
   /* 241-251     ( ( value - 240 ) * 30 )  minutes */
   /* 252         21 minutes */
   /* 253         8 to 12 hours */
   /* 254         reserved */
   /* 255         21 minutes 15 seconds */
   /* Note:  times are approximate ) */

typedef struct _sercd_apm {
	_Uint32t		action;
	_Uint32t		level;
	_Uint32t		rsvd[7];
} SERCD_APM;

#define SERCD_CAP_UMID			0x00001			 /* supports unique media id */
#define SERCD_CAP_CA			0x00002			 /* supports compressed audio (mp3/wma) */
#define SERCD_CAP_CDDA			0x00004          /* supports CDDA */
#define SERCD_CAP_BDEC			0x00008			 /* supports Block Decoding */
#define SERCD_CAP_CLV			0x00010          /* supports CAV */
#define SERCD_CAP_CAV			0x00020          /* supports CLV */
#define SERCD_CAP_ROM			0x00040          /* supports CD-ROM */
#define SERCD_CAP_MS			0x00080          /* supports multisession */
#define SERCD_CAP_TXT			0x00100          /* supports CD-Text */
#define SERCD_CAP_PLST			0x00200			 /* supports playlists */
#define SERCD_CAP_TEMP			0x00400          /* supports temperature */
#define SERCD_CAP_AUTO_INS		0x00800			 /* supports auto insert */
#define SERCD_CAP_PLY_RNG		0x01000			 /* supports play range (abs to abs) */
#define SERCD_CAP_PLY_EOM		0x02000			 /* supports play to end of media */
#define SERCD_CAP_PLY_EOS		0x04000			 /* supports play to end of track/file */
#define SERCD_CAP_ALP           0x08000			 /* supports accurate landing precision */
#define SERCD_CAP_META_FULL		0x10000			 /* supports full metadata query */
#define SERCD_CAP_META_BKGND	0x20000			 /* supports background metadata */
typedef struct _sercd_capabilities {
	_Uint32t		cap;
	_Uint32t		rsvd[19];
} SERCD_CAPABILITIES;

/* play mode actions: */
#define SERCD_PM_QUERY				0x00
#define SERCD_PM_SET				0x01

/* play mode modes: */
#define SERCD_PM_PLAY_CA			0x01     /* play compressed audio (ie mp3, wma) */
#define SERCD_PM_PLAY_CDDA			0x02     /* play CDDA */
#define SERCD_PM_PLAY_MS			0x04     /* play multisession */
#define SERCD_PM_PLAY_EOM			0x08     /* play to end/begining of media */
#define SERCD_PM_PLAY_EOS			0x10     /* play to end/begining of song */
#define SERCD_PM_REPEAT_SONG		0x20     /* repeat song */
#define SERCD_PM_REPEAT_DISC		0x40     /* repeat disc */
#define SERCD_PM_PLAY_MSK			( SERCD_PM_PLAY_EOM | SERCD_PM_PLAY_EOS )
#define SERCD_PM_REPEAT_MSK			( SERCD_PM_REPEAT_SONG | SERCD_PM_REPEAT_DISC )
#define SERCD_PM_MSK				0x3f
typedef struct _sercd_play_mode {
	_Uint32t		action;
	_Uint32t		mode;
	_Uint32t		mask;
	_Uint32t		rsvd[7];
} SERCD_PLAY_MODE;

#define DCMD_SERCD_RAW_CMD          __DIOTF(_DCMD_CAM, _SIM_SERCD + 0, struct _sercd_raw_cmd)
#define DCMD_SERCD_RAW_RCVMSG       __DIOTF(_DCMD_CAM, _SIM_SERCD + 1, struct _sercd_raw_rcvmsg)
#define DCMD_SERCD_APM              __DIOTF(_DCMD_CAM, _SIM_SERCD + 2, struct _sercd_apm)
#define DCMD_SERCD_PLAY_MODE        __DIOTF(_DCMD_CAM, _SIM_SERCD + 4, struct _sercd_play_mode)
#define DCMD_SERCD_CAPABILITIES     __DIOF(_DCMD_CAM, _SIM_SERCD + 5, struct _sercd_capabilities)

#include <_packpop.h>

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/devb/sercd/public/hw/dcmd_sim_sercd.h $ $Rev: 680332 $")
#endif
