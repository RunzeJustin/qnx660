/*
 * $QNXLicenseC:  
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

#ifndef __USB_CDC_ECM_H_INCLUDED
#define __USB_CDC_ECM_H_INCLUDED

#include <sys/usb100.h>
#include <hw/usb/usb_cdc.h>

typedef struct _usb_ecm_functional_descriptor {
	USB100_FIELD(	bLength,				_Uint8t);
	USB100_FIELD(	bDescriptorType,		_Uint8t);
	USB100_FIELD(	bDescriptorSubType,		_Uint8t);
	USB100_FIELD(	iMACAddress,			_Uint8t);
	USB100_FIELD(	bmEthernetStatistics,	_Uint32t);
	USB100_FIELD(	wMaxSegmentSize,		_Uint16t);
	USB100_FIELD(	wNumberMCFilters,		_Uint16t);
	USB100_FIELD(	bNumberPowerFilters,	_Uint8t);
} usb100_ecm_functional_descriptor_t;

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/usbdi/public/hw/usb/usb_cdc_ecm.h $ $Rev: 680336 $")
#endif
