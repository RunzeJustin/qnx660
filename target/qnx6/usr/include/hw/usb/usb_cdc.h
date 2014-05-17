/*
 * $QNXLicenseC:  
 * Copyright 2011, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/


#ifndef __USB_CDC_H_INCLUDED
#define __USB_CDC_H_INCLUDED

#include <sys/usb100.h>

/* CDC SUBCLASSES */

#define CDC_CLASS                        0x2
#define CDC_SUBCLASS_DIRECTLINE_CM       0x1
#define CDC_SUBCLASS_ACM                 0x2
#define CDC_SUBCLASS_TELEPHONE_CM        0x3
#define CDC_SUBCLASS_MULTICHAN_CM        0x4
#define CDC_SUBCLASS_CAPI_CM             0x5
#define CDC_SUBCLASS_ECM                 0x6
#define CDC_SUBCLASS_ATM_CM              0x7
#define CDC_SUBCLASS_WIRELESS_CM         0x8
#define CDC_SUBCLASS_DEVICE_MANAGEMENT   0x9
#define CDC_SUBCLASS_MOBILE_DIRECTLINE   0xa
#define CDC_SUBCLASS_OBEX                0xb
#define CDC_SUBCLASS_EEM                 0xc


/* CDC Communications Class Protocol Codes */
#define CDC_CPROT_NONE                   0x0
#define CDC_CPROT_AT_V250                0x1
#define CDC_CPROT_AT_PCCA_101            0x2
#define CDC_CPROT_AT_PCCA_ANNEX_O        0x3
#define CDC_CPROT_AT_GSM707              0x4
#define CDC_CPROT_AT_3GPP2707            0x5
#define CDC_CPROT_AT_CDMA                0x6
#define CDC_CPROT_EEM                    0x7
#define CDC_CPROT_EXTERN                 0xfe
#define CDC_CPROT_VENDOR_SPECIFIC        0xff


/* Data Interface Class Protocols */
#define CDC_DATA_IFACE_CLASS             0xa

#define CDC_DPROT_NONE                   0x0
#define CDC_DPROT_ISDN                   0x30
#define CDC_DPROT_HDLC                   0x31
#define CDC_DPROT_TRANSPARENT            0x32
#define CDC_DPROT_MANAGEMENT_Q921        0x50
#define CDC_DPROT_DATALINK_Q921          0x51
#define CDC_DPROT_TEI_MUX_Q921           0x52
#define CDC_DPROT_DATA_COMPRESSION       0x90
#define CDC_DPROT_EURO_ISDN              0x91
#define CDC_DPROT_V24_ISDN               0x92
#define CDC_DPROT_CAPI                   0x93
#define CDC_DPROT_HOST                   0xfd
#define CDC_DPROT_PROT_FD                0xfe
#define CDC_DPROT_VENDOR_SPECIFIC        0xff


/* Functional Descriptors */


typedef struct _usb_cdc_functional_descriptor {
	USB100_FIELD(	bLength,				_Uint8t);
	USB100_FIELD(	bDescriptorType,		_Uint8t);
	USB100_FIELD(	bDescriptorSubType,		_Uint8t);
} usb100_cdc_functional_descriptor_t;


/* Values for the bDescriptorType filed */
#define CDC_CS_INTERFACE                 0x24
#define CDC_CS_ENDPOINT                  0x25

/* bDescriptor SubType */

#define CDC_FDESC_SUBTYPE_HEADER			0x0
#define CDC_FDESC_SUBTYPE_CALL_MANAGMENT    0x1
#define CDC_FDESC_SUBTYPE_ACM               0x2
#define CDC_FDESC_SUBTYPE_DIRECTLINE        0x3
#define CDC_FDESC_SUBTYPE_TELEPHONE_RINGER  0x4
#define CDC_FDESC_SUBTYPE_CALL_LINESTATE    0x5
#define CDC_FDESC_SUBTYPE_UNION             0x6
#define CDC_FDESC_SUBTYPE_COUNTRY_SELECT    0x7
#define CDC_FDESC_SUBTYPE_TELEPHONE_OP      0x8
#define CDC_FDESC_SUBTYPE_USB_TERM          0x9
#define CDC_FDESC_SUBTYPE_NETWORK_CHAN      0xa
#define CDC_FDESC_SUBTYPE_PROTOCOL_UNIT     0xb
#define CDC_FDESC_SUBTYPE_EXTENSION_UNIT    0xc
#define CDC_FDESC_SUBTYPE_MULTI_CHAN        0xd
#define CDC_FDESC_SUBTYPE_CAPI              0xe
#define CDC_FDESC_SUBTYPE_ECM               0xf
#define CDC_FDESC_SUBTYPE_ATM               0x10
#define CDC_FDESC_SUBTYPE_WIRELESS          0x11
#define CDC_FDESC_SUBTYPE_MOBILE_DIRECTLINE 0x12
#define CDC_FDESC_SUBTYPE_MDLM              0x13
#define CDC_FDESC_SUBTYPE_DEVICE_MANAGEMENT 0x14
#define CDC_FDESC_SUBTYPE_OBEX              0x15
#define CDC_FDESC_SUBTYPE_CMD_SET           0x16
#define CDC_FDESC_SUBTYPE_CMD_SET_DETAIL    0x17
#define CDC_FDESC_SUBTYPE_TCM               0x18
#define CDC_FDESC_SUBTYPE_OBEX_SERVICE_ID   0x19


typedef struct _usb_cdc_hdr_functional_descriptor {
	USB100_FIELD(	bLength,				_Uint8t);
	USB100_FIELD(	bDescriptorType,		_Uint8t);
	USB100_FIELD(	bDescriptorSubType,		_Uint8t);
	USB100_FIELD(	bcdCDC,					_Uint16t);	
} usb100_cdc_hdr_functional_descriptor_t;


typedef struct _usb_cdc_union_functional_descriptor {
	USB100_FIELD(	bLength,				_Uint8t);
	USB100_FIELD(	bDescriptorType,		_Uint8t);
	USB100_FIELD(	bDescriptorSubType,		_Uint8t);
	USB100_FIELD(	bControlInterface,		_Uint8t);
	USB100_FIELD(	bSubordinateInterface,	_Uint8t);	/* variable size entry	 */
} usb100_cdc_union_functional_descriptor_t;


typedef struct _usb_cdc_country_functional_descriptor {
	USB100_FIELD(	bLength,				_Uint8t);
	USB100_FIELD(	bDescriptorType,		_Uint8t);
	USB100_FIELD(	bDescriptorSubType,		_Uint8t);
	USB100_FIELD(	iCountryCodeRelDate,	_Uint8t);
	USB100_FIELD(	wCountryCode,			_Uint16t);	/* variable size entry */
} usb100_cdc_country_functional_descriptor_t;



/* Management Interface Requests */


#define CDC_REQ_SEND_ENCAPSULATED_COMMAND             0x0
#define CDC_REQ_GET_ENCAPSULATED_RESPONSE             0x1
#define CDC_REQ_SET_COMM_FEATURE                      0x2
#define CDC_REQ_GET_COMM_FEATURE                      0x3
#define CDC_REQ_CLEAR_COMM_FEATURE                    0x4
#define CDC_REQ_SET_AUX_LINE_STATE                    0x10
#define CDC_REQ_SET_HOOK_STATE                        0x11
#define CDC_REQ_PULSE_SETUP                           0x12
#define CDC_REQ_SEND_PULSE                            0x13
#define CDC_REQ_SET_PULSE_TIME                        0x14
#define CDC_REQ_RING_AUX_JACK                         0x15
#define CDC_REQ_SET_LINE_CODING                       0x20
#define CDC_REQ_GET_LINE_CODING                       0x21
#define CDC_REQ_SET_CONTROL_LINE_STATE                0x22
#define CDC_REQ_SEND_BREAK                            0x23
#define CDC_REQ_SET_RINGER_PARAMS                     0x30
#define CDC_REQ_GET_RINGER_PARAMS                     0x31
#define CDC_REQ_SET_OPERATION_PARAMS                  0x32
#define CDC_REQ_GET_OPERATION_PARAMS                  0x33
#define CDC_REQ_SET_LINE_PARAMS                       0x34
#define CDC_REQ_GET_LINE_PARAMS                       0x35
#define CDC_REQ_DIAL_DIGITS                           0x36
#define CDC_REQ_SET_UNIT_PARAMETER                    0x37
#define CDC_REQ_GET_UNIT_PARAMETER                    0x38
#define CDC_REQ_CLEAR_UNIT_PARAMETER                  0x39
#define CDC_REQ_GET_PROFILE                           0x3a
#define CDC_REQ_SET_ETHERNET_MULTICAST_FILTERS        0x40
#define CDC_REQ_SET_ETHERNET_PWRMAN_PATTERN_FILTER    0x41
#define CDC_REQ_GET_ETHERNET_PWRMAN_PATTERN_FILTER    0x42
#define CDC_REQ_SET_ETHERNET_PACKET_FILTER            0x43
#define CDC_REQ_GET_ETHERNET_STATISTICS               0x44
#define CDC_REQ_SET_ATM_DATA_FORMAT                   0x50
#define CDC_REQ_GET_ATM_DEVICE_STATISTICS             0x51
#define CDC_REQ_ATM_DEFAULT_VC                        0x52
#define CDC_REQ_GET_ATM_VC_STATISTICS                 0x53
#define CDC_REQ_GET_NTB_PARAMETERS                    0x80
#define CDC_REQ_GET_NET_ADDRESS                       0x81
#define CDC_REQ_SET_NET_ADDRESS                       0x82
#define CDC_REQ_GET_NTB_FORMAT                        0x83
#define CDC_REQ_SET_NTB_FORMAT                        0x84
#define CDC_REQ_GET_NTB_INPUT_SIZE                    0x85
#define CDC_REQ_SET_NTB_INPUT_SIZE                    0x86
#define CDC_REQ_GET_MAX_DATAGRAM_SIZE                 0x87
#define CDC_REQ_SET_MAX_DATAGRAM_SIZE                 0x88
#define CDC_REQ_GET_CRC_MODE                          0x89
#define CDC_REQ_SET_CRC_MODE                          0x8a


/* Management Interface Notifications */

#define CDC_NOTIFY_NETWORK_CONNECTION                 0x0
	#define CDC_NETWORK_CONNECTION_DISCONNECTED           0
	#define CDC_NETWORK_CONNECTION_CONNECTED              1

#define CDC_NOTIFY_RESPONSE_AVAILABLE                 0x1
#define CDC_NOTIFY_AUX_JACK_HOOK_STATE                0x8
#define CDC_NOTIFY_RING_DETECT                        0x9
#define CDC_NOTIFY_SERIAL_STATE                       0x20
#define CDC_NOTIFY_CALL_STATE_CHANGE                  0x28
#define CDC_NOTIFY_LINE_STATE_CHANGE                  0x29
#define CDC_NOTIFY_CONNECTION_SPEED_CHANGE            0x2a

typedef struct _usb100_cdc_notification {
	USB100_FIELD(	bmRequestType,				_Uint8t);
	USB100_FIELD(	bNotifyCode,				_Uint8t);
	USB100_FIELD(	wValue,						_Uint16t);
	USB100_FIELD(	wIndex,						_Uint16t);
	USB100_FIELD(	wLength,					_Uint16t);
	USB100_FIELD(	Data,						_Uint8t);
} usb100_cdc_notification_t;
	
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/usbdi/public/hw/usb/usb_cdc.h $ $Rev: 732568 $")
#endif
