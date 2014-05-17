/*
 * $QNXLicenseC:  
 * Copyright 2006, QNX Software Systems. All Rights Reserved.
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
#include <sys/usbdci.h>

__BEGIN_DECLS

struct _usbdc_endpoint;

typedef struct _io_usb_dll_entry 	io_usb_dll_entry_t;
typedef struct _st_USB_Hc 			st_USB_Hc;
typedef struct _usbdc_device 		usbdc_device_t;


typedef struct _iousb_endpoint_t  {
	usbd_endpoint_descriptor_t 	edesc;		/* USB defined endpoint descriptor information */
	uint32_t					flags;		/* Endpoint flags set by HW driver */
	void 						*user;		/* used by HW driver */
} iousb_endpoint_t;

#define IOUSB_ENDPOINT_FLAGS_BMAP		0x10
#define IOUSB_ENDPOINT_FLAGS_NO_STATUS	0x20  /* Try to short circuit status stage */


typedef struct _iousb_device {
	uint32_t		device_address;
	uint32_t		device_port;
	uint32_t		device_speed;
} iousb_device_t;


typedef struct _iousb_transfer {
	uint32_t	status;
	uint32_t	semaphore;
	uint32_t	flags;
	uint32_t	timeout;
	uint32_t	isoch_frame;
	uint8_t		*buffer;
	paddr64_t	buffer_paddr;
	uint32_t	buffer_len;
	uint32_t	actual_len;
	void		(*urb_complete_cbf)  ( iousb_endpoint_t *endp, struct _iousb_transfer *urb, uint32_t status, uint32_t tlen );
	void		*xdata_ptr;		
} iousb_transfer_t;


/*
 * Calls HC drivers can make into io-usb
 */
typedef struct _io_usb_self {
	_uint32			nfuncs;
	int 			(*hc_port_resume_signalling) ( struct _st_USB_Hc *Hc, _uint32 portno );
	iousb_device_t	*(*iousb_get_parent_device) ( iousb_device_t *device );
	int 			(*hc_reserved) ( struct _st_USB_Hc *Hc, void *data );
} io_usb_self_t;

#define _IO_USB_NFUNCS		((sizeof(io_usb_self_t)-sizeof(u_int))/sizeof(void *))

typedef struct _iousb_pipe_methods {
	_uint32         (*iousb_endpoint_enable)	( void *chdl, iousb_device_t *device, iousb_endpoint_t *endp );
	_uint32         (*iousb_endpoint_disable)	( void *chdl, iousb_endpoint_t *endp );
	_uint32         (*iousb_transfer_data)		( void *chdl, iousb_transfer_t *urb, iousb_endpoint_t *endp,_uint8 *buffer, _uint32 length, _uint32 flags );
	_uint32         (*iousb_transfer_abort)		( void *chdl, iousb_transfer_t *urb, iousb_endpoint_t *endp );
	void            (*reserved)					( void *chdl, void *data );	
} iousb_pipe_methods_t;

#define _USB_HC_PIPE_METHODS ((sizeof(hc_pipe_methods_t) - sizeof(_uint32)) / sizeof(void *))


/* USB transfer flags */
#define  PIPE_FLAGS_TOKEN_SETUP		0x01
#define  PIPE_FLAGS_TOKEN_STATUS	0x02
#define  PIPE_FLAGS_TOKEN_IN		0x04
#define  PIPE_FLAGS_TOKEN_OUT		0x08
#define	 PIPE_FLAGS_BUFFER_PHYS 	0x10
#define  PIPE_FLAGS_MULTI_XFER		0x20
#define  PIPE_FLAGS_LAST_PACKET 	0x80000000


/*
 * Entry point into HC Drivers.
 */
typedef struct _hc_methods {
	_uint32         		nentries;
	_uint32         		(*hc_init)					( st_USB_Hc *hc, _uint32 flags, char *args );
	_uint32         		(*hc_start)					( st_USB_Hc *hc );
	_uint32         		(*hc_stop)					( st_USB_Hc *hc );
	_uint32         		(*hc_shutdown)				( st_USB_Hc *hc );
	_uint32         		(*hc_set_bus_state)         ( st_USB_Hc *hc, _uint32 bus_state );
	void 					*(*hc_dma_memory_malloc)	( st_USB_Hc *hc, size_t len );
	_uint32					(*hc_dma_memory_free) 		( st_USB_Hc *hc, _uint32 *addr, size_t len );
	_uint32         		(*hc_interrupt)				( st_USB_Hc *hc );
	_uint32         		(*hc_set_port_feature)      ( st_USB_Hc *hc, _uint32 port, _uint32 feature );
	_uint32         		(*hc_clear_port_feature)    ( st_USB_Hc *hc, _uint32 port, _uint32 feature );
	_uint32	        		(*hc_check_port_status) 	( st_USB_Hc *hc, _uint32 port, _uint32 *port_status );
	_uint32	        		(*hc_check_device_connected)( st_USB_Hc *hc, _uint32 port );
	_uint32	        		(*hc_get_root_device_speed)	( st_USB_Hc *hc, _uint32 port );
	_uint32         		(*hc_get_current_frame)		( st_USB_Hc *hc );

	/* pipe handling methods 			*/
	iousb_pipe_methods_t 	*ctrl_pipe_methods;
	iousb_pipe_methods_t	*int_pipe_methods;
	iousb_pipe_methods_t 	*bulk_pipe_methods;
	iousb_pipe_methods_t 	*isoch_pipe_methods;
} hc_methods_t;


#define _USB_HC_METHODS ((sizeof(hc_methods_t) - sizeof(_uint32)) / sizeof(void *))



/*
 * Calls DC drivers can make into io-usb
 */
typedef struct _io_usbdc_self {
	uint32_t		nfuncs;
	int 			(*usbdc_device_state_change) 	( struct _usbdc_device *udc, uint32_t device_state );
	int 			(*usbdc_endpoint_state_change)	( iousb_endpoint_t *endp, uint32_t state );
	int 			(*usbdc_setup_packet_process) 	( struct _usbdc_device *udc, uint8_t *buff );
	void 			(*usbdc_set_device_speed) 		( struct _usbdc_device *udc, uint32_t speed );
	int 			(*usbdc__reserved) 				( struct _usbdc_device *udc, void *data );
} io_usbdc_self_t;

#define _IO_USBDC_NFUNCS		((sizeof(io_usbdc_self_t)-sizeof(u_int))/sizeof(void *))



/*
 * Entry points into DC Drivers.
 */
typedef struct _dc_methods {
	uint32_t 				nentries;
	uint32_t 				(*dc_init)					( usbdc_device_t *udc, io_usbdc_self_t *udc_self, char *args );
	_uint32         		(*dc_start)					( usbdc_device_t *udc );
	_uint32         		(*dc_stop)					( usbdc_device_t *udc );
	uint32_t				(*dc_shutdown)				( usbdc_device_t *udc );

	void 					*(*dc_dma_memory_malloc)	( usbdc_device_t *udc, size_t len );
	_uint32					(*dc_dma_memory_free) 		( usbdc_device_t *udc, _uint32 *addr, size_t len );

	uint32_t				(*dc_set_bus_state) 		( usbdc_device_t *udc, uint32_t bus_state );
	uint32_t				(*dc_set_device_feature) 	( usbdc_device_t *udc, uint32_t feature, _uint16 index );
	uint32_t				(*dc_clear_device_feature) 	( usbdc_device_t *udc, uint32_t feature );

	uint32_t 				(*dc_set_device_address) 	( usbdc_device_t *udc, uint32_t address );

	uint32_t 				(*dc_get_descriptor)		( usbdc_device_t *udc, uint8_t type, uint8_t index, uint16_t lang_id, uint8_t **desc, uint32_t speed );

	uint32_t 				(*dc_select_configuration)	( usbdc_device_t *udc, uint8_t config );
	uint32_t				(*dc_interrupt)				( usbdc_device_t *udc );

	uint32_t				(*dc_set_endpoint_state) 	( usbdc_device_t *udc, iousb_endpoint_t *ep, uint32_t ep_state );
	uint32_t				(*dc_clear_endpoint_state)	( usbdc_device_t *udc, iousb_endpoint_t *ep, uint32_t ep_state );
	uint32_t				(*dc_set_sel)				( usbdc_device_t *udc, uint8_t u1sel, uint8_t u1pel, uint16_t u2sel, uint16_t u2pel );


	/* pipe handling methods 			*/
	iousb_pipe_methods_t 	*ctrl_pipe_methods;
	iousb_pipe_methods_t 	*int_pipe_methods;
	iousb_pipe_methods_t 	*bulk_pipe_methods;
	iousb_pipe_methods_t 	*isoch_pipe_methods;
} dc_methods_t;

#define _USB_DC_METHODS ((sizeof(dc_methods_t) - sizeof(uint32_t)) / sizeof(void *))


/*
 * Entry points into OTG Drivers.
 */
typedef struct _otgc_methods {


} otgc_methods_t;

#define USBDC_DEVICE_STATE_CONNECTED		0x01
#define USBDC_DEVICE_STATE_DISCONNECTED		0x02


typedef struct _usb_controller_methods {
		hc_methods_t		*hc_methods;
		dc_methods_t		*dc_methods;
		otgc_methods_t		*otgc_methods;
		void				*reserved;
} usb_controller_methods;


/*
 * Entry points for DLLs
 */

struct _io_usb_dll_entry {
	char			*name;										/* Name of DLL						*/
	uint32_t		device_interest;				 			/* Chip type this DLL can handle	*/
	uint32_t		vid;										/* change to allow full spec by DLL( PCI structure )*/
	uint32_t		did;
	uint32_t		ctrl_type;
	int 			(*init) (void *dll_hdl, dispatch_t *dpp, struct _io_usb_self *iousb, char *options);
	int 			(*shutdown)	( void *dll_hdl );
	usb_controller_methods	*usbctrl_methods;					/*  Controller methods 				*/
};

#define USB_CONTROLLER_HOST			0x01
#define USB_CONTROLLER_DEVICE		0x02
#define USB_CONTROLLER_OTG			0x04


/*
 * Common HW control
 */

typedef struct _iousb_hw_ctrl {
    char 	         			*cname;                 /* Descriptive name   		    */
	struct pci_dev_info 		*pci_inf;
	_uint32						cindex;
	_uint32						capabilities;			/* capabilites of controller	*/ 
	_uint32						max_transfer_size;      /* Size of the max transfer     */
	_uint32						max_unaligned_xfer;		/* Size of the max transfer with unaligned buffer */
	_uint32						buff_alignment_mask;	/* mask fo buffer alignment    */
} iousb_hw_ctrl_t;


/*
 * Structure passed to HC Drivers
 */
struct _st_USB_Hc {
	iousb_hw_ctrl_t				hw_ctrl;	
	struct _io_usb_self			*iousb_self;
	void						*pdev;			
	_uint32						num_root_hubs;
	_uint32						root_hub_status;		/* port change bitmap			*/
	_uint32         			AvailableBandwidth;     /* Guaranteed bandwidth         */
	_uint32						ctrl_retry;				/* ctrl retry count 			*/ 
	_uint32         			HFrameumber;            /* High 16bit word for frame nb */
	void						*dll_hdl;
	void 						*hc_data;				/* data associated with a HC	*/
};

/* USB HC PCI class codes */
#define USB_CLASS_OHCI          		0x0c0310
#define USB_CLASS_UHCI          		0x0c0300
#define USB_CLASS_EHCI          		0x0c0320
#define USB_CLASS_ISP1161       		0x0c6100

/* HC capability flags */
#define HC_CAP_INTERRUPT	    		0x00000001
#define HC_CAP_BULK		    			0x00000002
#define HC_CAP_ISOCH		    		0x00000004
#define HC_CAP_REMOTE_WAKEUP			0x00000008

#define HC_CAP_AYSNC_PARK_MODE			0x00000010
#define HC_CAP_64_BIT_ADDRESSING    	0x00000020

#define HC_CAP_MAP_CLIENT_BUFF			0x40000000
#define HC_CAP_DMA_MEMORY_SPECIAL		0x80000000

/* DC capability flags 	*/
#define DC_CAP_ENDP_STALL_AUTO_CLEARED	0x00000001
#define DC_CAP_LOW_SPEED				0x00000002
#define DC_CAP_FULL_SPEED				0x00000004
#define DC_CAP_HIGH_SPEED				0x00000008
#define DC_CAP_TEST_MODES_SUPPORTED			0x00000010
#define DC_CAP_SUPER_SPEED				0x00000020


/* bus states */
#define USB_BUS_STATE_RESET				1
#define USB_BUS_STATE_SUSPENDED			2
#define USB_BUS_STATE_RESUME			3	
#define USB_BUS_STATE_OPERATIONAL		4

/* chip state */
#define USB_BUS_STATE_START				5
#define USB_BUS_STATE_STOP				6

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

/* define for BUS events */
#define IOUSB_EVENT_BUS_OVERCURRENT				10
/*#define IOUSB_EVENT_BUS_DEVICE_SUSPEND		11 */
/*#define IOUSB_EVENT_BUS_DEVICE_RESEUME		12 */

#define IOUSB_EVENT_DEVICE_STATUS_CHANGE		20
#define IOUSB_EVENT_DEVICE_NOT_RESPONDING		21
#define IOUSB_EVENT_DRIVER_DEVICE_SUSPEND		22
#define IOUSB_EVENT_DRIVER_DEVICE_RESUME		23
#define IOUSB_EVENT_DEVICE_SUSPEND				24
#define IOUSB_EVENT_DEVICE_RESUME				25
#define IOUSB_EVENT_DEVICE_DEVICE_WAKEUP		26

/* Events for Function Driver */

#define IOUSB_EVENT_DEVICE_FUNCTION				80
#define IOUSB_EVENT_VENDOR_COMMAND              1
#define IOUSB_EVENT_DEVICE_STATE_CHANGE 		2
#define IOUSB_EVENT_ENDPOINT_STATE_CHANGE 		3

/*
 * Structure passed to DC Drivers
 */
struct _usbdc_device {
	iousb_hw_ctrl_t				hw_ctrl;	
	struct _io_usbdc_self		*usbdc_self;
	uint32_t					priority;
	uint32_t					verbosity;
	char 						*serial_string;

	uint8_t						selected_config;
	uint8_t						rsrvd[3];

	uint8_t						*setup_buf;
	void						*drvr_hdl;
    void                        *dc_data;               /* data associated with a DC    */
	void						*dll_hdl;
};


/* device speed */
#define	IOUSB_DEVICE_FULL_SPEED		0
#define	IOUSB_DEVICE_LOW_SPEED		1
#define	IOUSB_DEVICE_HIGH_SPEED		2
#define	IOUSB_DEVICE_SUPER_SPEED	3
#define	IOUSB_DEVICE_MASK_SPEED		3

/* defines for DC BUS state */
#define IOUSB_BUS_STATE_DISCONNECTED 	1
#define IOUSB_BUS_STATE_CONNECTED 		2
#define IOUSB_BUS_STATE_RESUME 			3


/* define device states */
#define IOUSB_DEVICE_STATE_UNKNOWN                  0
#define IOUSB_DEVICE_STATE_INSERTED                 1
#define IOUSB_DEVICE_STATE_REMOVED                  2
#define IOUSB_DEVICE_STATE_SUSPENDED                3
#define IOUSB_DEVICE_STATE_RESET                    4
#define IOUSB_DEVICE_STATE_RESUMING                 5
#define IOUSB_DEVICE_STATE_UNCONFIGURED             6
#define IOUSB_DEVICE_STATE_CONFIGURED               7
#define IOUSB_DEVICE_STATE_STALLED                  8
#define IOUSB_DEVICE_SUSPEND_REQUEST                9
#define IOUSB_DEVICE_STATE_RESUMED                 10
#define IOUSB_DEVICE_STATE_SHUTDOWN                11
#define IOUSB_DEVICE_STATE_TEST_MODE               12
#define IOUSB_DEVICE_STATE_WALLCHARGER_INSERTED    13
#define IOUSB_DEVICE_STATE_WALLCHARGER_REMOVED     14



#define IOUSB_DEVICE_STATE_READY        0x80000000  /* device endpoints are configured and not in error state */

#define IOUSB_DEVICE_SPEED_LOW          1
#define IOUSB_DEVICE_SPEED_FULL         2
#define IOUSB_DEVICE_SPEED_HIGH         3

/* define interface states */
#define IOUSB_INTERFACE_STATE_ENABLED    		1
#define IOUSB_INTERFACE_STATE_DISABLED   		2
#define IOUSB_INTERFACE_STATE_ENABLED_COMPLETE 	3
#define IOUSB_INTERFACE_STATE_DISABLED_COMPLETE	4

/* define endpoint states */
#define IOUSB_ENDPOINT_STATE_ENABLE     1
#define IOUSB_ENDPOINT_STATE_DISABLED   2
#define IOUSB_ENDPOINT_STATE_RESET      3
#define IOUSB_ENDPOINT_STATE_READY      4
#define IOUSB_ENDPOINT_STATE_NAK        5
#define IOUSB_ENDPOINT_STATE_STALLED    6

#define WAIT_ROOT_DEVICE_INSERT			50
#define WAIT_ROOT_HUB_RESET 			150

__END_DECLS


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/services/usb_dcd/public/sys/io-usb_dcd.h $ $Rev: 732568 $")
#endif
