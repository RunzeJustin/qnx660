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



#ifndef __UUID_H_INCLUDED
#define __UUID_H_INCLUDED

#include <inttypes.h>

__BEGIN_DECLS

/*
 UUID defined by RFC4122

 936DA01F-9ABD-4d9d-80C7-02AF85C822A8
 |||||||| |||| |||| |||| ||||||||||||
 |||||||| |||| |||| |||| ++++++++++++--- node
 |||||||| |||| |||| ||++---------------- clock sequence low
 |||||||| |||| |||| |+------------------ clock sequence hi
 |||||||| |||| |||| +------------------- type 0???=old 10??=RFC4122 110?=Msft 111?=rsvd 
 |||||||| |||| |+++--------------------- timestamp high
 |||||||| |||| +------------------------ version (for type RFC4122)
 |||||||| ++++-------------------------- timestamp middle
 ++++++++------------------------------- timestamp low

timestamp is 60-bit value
clock sequence is 14-bit incrementing or random number to correct timestamps that may go back in time
*/

#define UUID_VER_TIME		1	/* Time-base version */
#define UUID_VER_DCE		2	/* DCE Security with POSUX UIDs */
#define UUID_VER_NAME_MD5	3	/* Name based using MD5 hashing */
#define UUID_VER_RANDOM		4	/* only type(2 bits) and version(4 bits) are reserved */
#define UUID_VER_NAME_SHA1	5	/* Name based using SHA-1 hashing */

#define UUID_SET_VER(u,v)	(u)->octet[8]=((u)->octet[8]&~0xc0)|0x80, (u)->octet[6]=((u)->octet[6]&~0xf0)|((v)<<4)
/* @@@ Add UUID_SET_TIME, UUID_SET_CLOCK and UUID_SET_NODE */


struct uuid {
	uint8_t		octet[16];
};

__END_DECLS

#endif

/* __SRCVERSION("uuid.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/services/io-fs/lib/public/sys/uuid.h $ $Rev: 680334 $")
#endif
