-- Sample USB descriptors for a mass storage device

-- complete templates for the .device, .fs_config, and .hs_config table values

USB_CONFIG_SELFPOWERED         = 0xC0
USB_CONFIG_REMOTEWAKEUP        = 0x20
USB_MAX_CURRENT                = 0

umass = {}

umass.device = Device{
	bDeviceClass = USB_CLASS_DEVICE,
	bDeviceSubClass = 0x0,
	bDeviceProtocol = 0x0,
	bMaxPacketSize = 64,
	idVendor = 0x1234,
	idProduct = 0x4,
	bcdDevice = 0x0100,
	manufacturer = 'QNX Software',
	product = 'USB Mass Storage Device',
	serial = '123456789ABC',
	bNumConfigurations = 1,
}

umass.fs_config = Config{  -- full speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	interfaces = {
		Iface{
			bInterfaceClass = USB_CLASS_MASS_STORAGE,
			bInterfaceSubClass = 0x06,
			bInterfaceProtocol = 0x50,
			bAlternateSetting = 0,
			endpoints = {
				BulkIn{wMaxPacketSize = 64},
				BulkOut{wMaxPacketSize = 64},
			}
		},
	},
}

umass.hs_config = Config{  -- high speed
	bConfigurationValue = 1,
	bmAttributes = USB_CONFIG_SELFPOWERED,
	bMaxPower = USB_MAX_CURRENT,
	interfaces = {
		Iface{
			bInterfaceClass = USB_CLASS_MASS_STORAGE,
			bInterfaceSubClass = 0x06,
			bInterfaceProtocol = 0x50,
			bAlternateSetting = 0,
			endpoints = {
				BulkIn{wMaxPacketSize = 512},
				BulkOut{wMaxPacketSize = 512},
			}
		},
	}
}
