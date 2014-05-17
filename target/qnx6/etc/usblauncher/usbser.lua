--  Sample USB descriptors for a USB Serial device

-- complete templates for the .device, .fs_config, and .hs_config table values

USB_CONFIG_SELFPOWERED         = 0xC0
USB_CONFIG_REMOTEWAKEUP        = 0x20
USB_MAX_CURRENT                = 0

comm_descriptors = {
-- Header Functional Descriptor
	0x05,                   -- bFunctionLength
	0x24,                   -- bDescriptorType
	0x00,                   -- bDescriptorSubType
	0x10,                   -- bcdCDC   (LSB)
	0x01,                   -- bcdCDC   (MSB)

-- Call Managment Functional Descriptor
	0x05,                   -- bFunctionLength
	0x24,                   -- bDescriptorType
	0x01,                   -- bDescriptorSubType
	0x00,                   -- bmCapabilities - ENOSUP
	0x01,                   -- bDataInterface

-- Abstract Control Model Function Descriptor
	0x04,                   -- bFunctionLength
	0x24,                   -- bDescriptorType
	0x02,                   -- bDescriptorSubType
	0x02,                   -- bmCapabilities

-- Abstract Control Model  Union Descriptor
	0x05,                   -- bFunctionLength
	0x24,                   -- bDescriptorType
	0x06,                   -- bDescriptorSubType
	0x00,                   -- bControlInterface
	0x01,                   -- bSubordinate interface
}

usbser = {}

usbser.device = Device{
	bDeviceClass = USB_CLASS_COMMS,
	bDeviceSubClass = USB_COMMS_SUBCLASS_MODEM,
	bDeviceProtocol = 0x0,
	bMaxPacketSize = 64,
	idVendor = 0x1234,
	idProduct = 0x4,
	bcdDevice = 0x0100,
	manufacturer = 'Acme Corporation',
	product = 'CDC Serial Peripheral',
	serial = 'xxxx-xxxx-xxxx',
	bNumConfigurations = 1,
}

usbser.fs_config = Config{  -- full speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	description = 'Default Configuration',
	interfaces = {
		Association{
			bInterfaceClass = USB_CLASS_COMMS,
			bInterfaceSubClass = USB_COMMS_SUBCLASS_MODEM,
			bInterfaceProtocol = 0x0,
			description = 'Serial Port Interface',
			interfaces = {
				Iface{
					bInterfaceClass = USB_CLASS_COMMS,
					bInterfaceSubClass = USB_COMMS_SUBCLASS_MODEM,
					bInterfaceProtocol = 0x0,
					bAlternateSetting = 0,
					description = 'Serial Port Communication Class Interface',
					class_specific = comm_descriptors;
					endpoints = {
						InterruptIn{wMaxPacketSize = 8, bInterval = 8}
					}
				},
				Iface{
					bInterfaceClass = USB_CLASS_CDC_DATA,
					bInterfaceSubClass = 0x0,
					bInterfaceProtocol = 0x0,
					bAlternateSetting = 0,
					description = 'Serial Port Data Class Interface',
					endpoints = {
						BulkOut{wMaxPacketSize = 64},
						BulkIn{wMaxPacketSize = 64},
					}
				},
			},
		},
    },
}

usbser.hs_config = Config{  -- high speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	description = 'Default Configuration',
	interfaces = {
		Association{
			bInterfaceClass = USB_CLASS_COMMS,
			bInterfaceSubClass = USB_COMMS_SUBCLASS_MODEM,
			bInterfaceProtocol = 0x0,
			description = 'Serial Port Interface',
			interfaces = {
				Iface{
					bInterfaceClass = USB_CLASS_COMMS,
					bInterfaceSubClass = USB_COMMS_SUBCLASS_MODEM,
					bInterfaceProtocol = 0x0,
					bAlternateSetting = 0,
					description = 'Serial Port Communication Class Interface',
					class_specific = comm_descriptors;
					endpoints = {
						InterruptIn{wMaxPacketSize = 8, bInterval = 8}
					}
				},
				Iface{
					bInterfaceClass = USB_CLASS_CDC_DATA,
					bInterfaceSubClass = 0x0,
					bInterfaceProtocol = 0x0,
					bAlternateSetting = 0,
					description = 'Serial Port Data Class Interface',
					endpoints = {
						BulkOut{wMaxPacketSize = 512},
						BulkIn{wMaxPacketSize = 512},
					}
				},
			},
		},
	},
}
