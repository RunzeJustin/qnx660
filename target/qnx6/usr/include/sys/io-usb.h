/*
 * $QNXLicenseC:  
 * Copyright 2005, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

/*
 *  sys/io-usb.h
 *
 */

#ifndef __NTO_IO_USB_H_INCLUDED
#define __NTO_IO_USB_H_INCLUDED

#include <inttypes.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <hw/pci.h>
#include <hw/pci_devices.h>
#include <sys/usbdi.h>

__BEGIN_DECLS

struct _st_DEVICE_DESCRIPTOR;
struct _st_ENDPOINT_DESCRIPTOR;
struct _st_URB_TRANSFER;

typedef struct _st_USB_Hc st_USB_Hc;
typedef struct _io_usb_dll_entry io_usb_dll_entry_t;

/*
 * Calls HC drivers can make into io-usb
 */

typedef struct _io_usb_self {
	_uint32		nfuncs;
	int 		(*hc_port_resume_signalling) 	( struct _st_USB_Hc *Hc, _uint32 portno );
	int 		(*hc_port_status_change) 		( struct _st_USB_Hc *Hc, _uint32 change_mask );
	int 		(*hc_reserved) ( struct _st_USB_Hc *Hc, void *data );
} io_usb_self_t;

#define _IO_USB_NFUNCS		((sizeof(io_usb_self_t)-sizeof(u_int))/sizeof(void *))

typedef struct _hc_methods {
	_uint32         nentries;
	_uint32         (*hc_init)					( st_USB_Hc *hc, _uint32 flags, char *args );
	_uint32         (*hc_shutdown)				( st_USB_Hc *hc );
	_uint32         (*hc_set_bus_state)         ( st_USB_Hc *hc, _uint32 bus_state );
	void 			*(*hc_dma_memory_malloc)	( st_USB_Hc *hc, size_t len );
	_uint32			(*hc_dma_memory_free) 		( st_USB_Hc *hc, _uint32 *addr, size_t len );
	_uint32         (*hc_interrupt)				( st_USB_Hc *hc );
	_uint32         (*hc_set_port_feature)      ( st_USB_Hc *hc, _uint32 port, _uint32 feature );
	_uint32         (*hc_clear_port_feature)    ( st_USB_Hc *hc, _uint32 port, _uint32 feature );
	_uint32	        (*hc_check_port_status) 	( st_USB_Hc *hc, _uint32 *portno_status );
	_uint32	        (*hc_check_device_connected)( st_USB_Hc *hc, _uint32 port );
	_uint32	        (*hc_get_root_device_speed)	( st_USB_Hc *hc, _uint32 port );
	_uint32         (*hc_get_current_frame)		( st_USB_Hc *hc );
} hc_methods_t;

#define _USB_HC_METHODS ((sizeof(hc_methods_t) - sizeof(_uint32)) / sizeof(void *))


typedef struct _hc_pipe_methods {
	_uint32         (*hc_endpoint_enable)		( st_USB_Hc *hc, struct _st_DEVICE_DESCRIPTOR *ddesc, struct _st_ENDPOINT_DESCRIPTOR *ED );
	_uint32         (*hc_endpoint_disable)		( st_USB_Hc *hc, struct _st_ENDPOINT_DESCRIPTOR *ED );
	_uint32         (*hc_transfer_data)			( st_USB_Hc *hc, struct _st_URB_TRANSFER *urb, struct _st_ENDPOINT_DESCRIPTOR *ED,_uint8 *buffer, _uint32 length, _uint32 flags );
	_uint32         (*hc_transfer_abort)		( st_USB_Hc *hc, struct _st_URB_TRANSFER *urb, struct _st_ENDPOINT_DESCRIPTOR *ED );
	void            (*reserved)					( st_USB_Hc *hc, void *data );	
} hc_pipe_methods_t;

#define _USB_HC_PIPE_METHODS ((sizeof(hc_pipe_methods_t) - sizeof(_uint32)) / sizeof(void *))

/* Transfer flags */
#define  PIPE_FLAGS_TOKEN_SETUP		0x01
#define  PIPE_FLAGS_TOKEN_STATUS	0x02
#define  PIPE_FLAGS_TOKEN_IN		0x04
#define  PIPE_FLAGS_TOKEN_OUT		0x08
#define	 PIPE_FLAGS_BUFFER_PHYS 	0x10
#define  PIPE_FLAGS_MULTI_XFER		0x20
#define  PIPE_FLAGS_LAST_PACKET 	0x80000000


/*
 * Entry point for DLLs
 */

struct _io_usb_dll_entry {
	char	*name;										/* name of DLL						*/
	_uint32	device_interest;				 			/* chip type this DLL can handle	*/
	int 	(*init) (void *dll_hdl, dispatch_t *dpp,
				 io_usb_self_t *iousb, char *options);
	int 	(*shutdown) 		(void *dll_hdl);
	hc_methods_t				*hc_methods;			/* HC methods 						*/
	hc_pipe_methods_t 			*ctrl_pipe_methods;		/* pipe handling methods 			*/
	hc_pipe_methods_t			*int_pipe_methods;
	hc_pipe_methods_t 			*bulk_pipe_methods;
	hc_pipe_methods_t 			*isoch_pipe_methods;
};


/* privatize some of this info */
struct _st_USB_Hc {
    char 	         			*cname;                 /* Descriptive name   		    */
	struct pci_dev_info 		*pci_inf;
	_uint32						cindex;
	int							chid;	
	int							coid;	
	int							tid;	
	void						*pdev;			
    _uint32         			Irq;                    /* Irq Number                   */
	_uint32						usb_iid;				/* interrrupt handle			*/
	pthread_rwlock_t    		usb_rwlock;				/* lock used during enumeration/io */
	_uint32						num_root_hubs;
	_uint32						root_hub_status;		/* port change bitmap			*/
	_uint32         			AvailableBandwidth;     /* Guaranteed bandwidth         */
	_uint32						MaxTransferSize;        /* Size of the max transfer     */
	_uint32						MaxUnalignedTransferSize;/* Size of the max transfer with unaligned buffer */
	_uint32						buff_alignment_mask;	/* mask fo buffer alignement    */
	_uint32						capabilities;			/* capabilites of controller	*/ 
	_uint32						ctrl_retry;				/* ctrl retry count 			*/ 
	_uint32         			HFrameumber;            /* High 16bit word for frame nb */
	void 						*ArrayUsbDevices;
	void						*UsbDevices;
	void						*dll_hdl;
	void 						*hc_data;				/* data associated with a HC	*/

	/* HC methods */
	hc_methods_t				*hc_methods;	

	/* HC controller pipe methods */
	hc_pipe_methods_t            *ctrl_pipe_methods;
	hc_pipe_methods_t            *int_pipe_methods;
	hc_pipe_methods_t            *bulk_pipe_methods;
	hc_pipe_methods_t            *isoch_pipe_methods;
};

typedef struct _iousb_hc_dll_debug_entry {
	int		(*debug_init) 		( st_USB_Hc *Hc );
	int		(*debug_command) 	( st_USB_Hc *Hc, uint32_t dcmd, uint32_t level );
	int		(*debug_destroy) 	( st_USB_Hc *Hc );
} iousb_hc_dll_debug_entry_t;

/* internal DEBUG commands */

#define USB_COMPONENT_DEBUG_STACK					1
	#define USB_DEBUG_SET_VERBOSITY						(1<<16)

#define USB_COMPONENT_DEBUG_HW_DLL					2

	#define USB_BUS_DEBUG_STATE_TRIGGER					(1<<16)
	#define USB_BUS_DEBUG_REGISTER_DUMP					(2<<16)
		#define USB_BUS_DEBUG_REGISTER_DUMP_CONTROLLER		1
		#define USB_BUS_DEBUG_REGISTER_DUMP_PHY				2
		#define USB_BUS_DEBUG_REGISTER_DUMP_INTERNAL		4
	#define USB_BUS_DEBUG_SCHEDULE_DUMP					(3<<16)
		#define USB_SCHEDULE_DUMP_INTERNAL					1
		#define USB_SCHEDULE_DUMP_CONTROLLER				2
	#define USB_BUS_DEBUG_PORT							(7<<16)
	#define USB_BUS_DEBUG_XFER_ERROR					(8<<16)
	#define USB_BUS_DEBUG_SET_VERBOSITY					(9<<16)
	#define USB_BUS_DEBUG_PHY_RESET						(10<<16)
	#define USB_BUS_DEBUG_SET_CLOCKS					(11<<16)
		#define USB_BUS_DEBUG_CLOCK_CONTROLLER				1		/* bitmask of clock state 1==on, 0==off */
		#define USB_BUS_DEBUG_CLOCK_PHY						2
		#define USB_BUS_DEBUG_CLOCK_OTHER					4
	#define USB_BUS_DEBUG_ULPI_REG_READ					(12<<16)
	#define USB_BUS_DEBUG_ULPI_REG_WRITE				(13<<16)
	#define USB_BUS_DEBUG_PORT_SUSPEND					(14<<16)
	#define USB_BUS_DEBUG_PORT_RESUME					(15<<16)
	#define USB_BUS_DEBUG_SET_DEBUG_VERBOSITY			(16<<16)
	#define USB_BUS_DEBUG_ULPI_SET_STP					(17<<16)



/* USB HC PCI class codes */
#define USB_CLASS_OHCI          0x0c0310
#define USB_CLASS_UHCI          0x0c0300
#define USB_CLASS_EHCI          0x0c0320
#define USB_CLASS_XHCI          0x0c0330
#define USB_CLASS_ISP1161       0x0c6100

/* DLL init flags */
#define IOUSB_USBMGR_ENABLED			0x80000000

/* HC capability flags */
#define HC_CAP_IND_PORT_STATUS          0x04000000
#define HC_CAP_PORT_CHANGE_REPORT       0x08000000
#define HC_CAP_AYSNC_PARK_MODE			0x10000000
#define HC_CAP_64_BIT_ADDRESSING    	0x20000000
#define HC_CAP_MAP_CLIENT_BUFF			0x40000000
#define HC_CAP_DMA_MEMORY_SPECIAL		0x80000000

/* bus states */
#define USB_BUS_STATE_RESET				1
#define USB_BUS_STATE_SUSPENDED			2
#define USB_BUS_STATE_RESUME			3	
#define USB_BUS_STATE_OPERATIONAL		4

/* chip state */
#define USB_BUS_STATE_START				5
#define USB_BUS_STATE_STOP				6

/* port set/clear feature states */
#define USB_PORT_ENABLE 				1
#define USB_PORT_RESET					2
#define USB_PORT_SUSPEND				3 
#define USB_PORT_POWER 					4
#define	USB_PORT_CONNECT_STATUS_CHANGE	5
#define	USB_PORT_OVRC_STATUS_CHANGE		6
#define USB_PORT_ENABLE_STATUS_CHANGE	7

#define USB_PORT_IOUSB_PHY_RESET		100

#define USB_IOUSB_PORT_WAKEUP_CONNECT		0x00010000
#define USB_IOUSB_PORT_WAKEUP_DISCONNECT	0x00020000
#define USB_IOUSB_PORT_WAKEUP_OVER_CURRENT	0x00040000

/* define for hub port status */
#define HUB_STATUS_PORT_CONNECTION          0x0001
#define HUB_STATUS_PORT_ENABLE              0x0002
#define HUB_STATUS_PORT_SUSPEND             0x0004
#define HUB_STATUS_PORT_OVER_CURRENT        0x0008
#define HUB_STATUS_PORT_RESET               0x0010
#define HUB_STATUS_PORT_POWER               0x0100
#define HUB_STATUS_PORT_LOW_SPEED           0x0200
#define HUB_STATUS_PORT_HIGH_SPEED          0x0400
#define HUB_STATUS_PORT_TEST_MODE           0x0800
#define HUB_STATUS_PORT_INDICATOR_CONTROL   0x1000

#define HUB_CHANGE_PORT_CONNECTION          0x010000
#define HUB_CHANGE_PORT_ENABLE              0x020000
#define HUB_CHANGE_PORT_SUSPEND             0x040000
#define HUB_CHANGE_PORT_OVER_CURRENT        0x080000
#define HUB_CHANGE_PORT_RESET               0x100000

#define USB_PORT_CLEAR_TT_BUFFER		(1<<16)

/* defines for wValue USB_HUB_CLEAR_TT_BUFFER request */
#define USB_HUB_CLEAR_TT_S_ENDPOINT_NUMBER 		0
#define USB_HUB_CLEAR_TT_S_DEVICE_ADDRESS		4
#define USB_HUB_CLEAR_TT_S_ENDPOINT_TYPE 		11
#define USB_HUB_CLEAR_TT_M_ENDPOINT_DIRECTION 	0x8000


/* events to usbmgr for interface suspend/resume requests */
#define IOUSB_EVENT_DRIVER_INTERFACE_SUSPEND	100
#define IOUSB_EVENT_DRIVER_INTERFACE_RESUME		101


__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/services/usb/public/sys/io-usb.h $ $Rev: 733447 $")
#endif
