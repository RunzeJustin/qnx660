-- Descriptor information for USB Serial Device

-- define descriptors .device, .fs_config, and .hs_config table values
-- by assigning each a string of bytes
-- the table value .strings must be a table of strings

USBDC_FULL_SPEED_MPS     = 64
USBDC_HIGH_SPEED_MPS     = 512

USBDC_VENDOR_ID          = 0x1234
USBDC_PRODUCT_ID         = 0x4
USBDC_MAX_CURRENT        = 0
USBDC_NUM_CONFIGURATIONS = 1            -- must be 1
USBDC_REVISION           = 0x0100

serial_raw_desc = {}

serial_raw_desc.device  = string.char(
	0x12,                     -- bLength
	0x01,                     -- bDescriptorType
	0x00,                     -- bcdUSB (LSB)
	0x02,                     -- bcdUSB (MSB)
	0x02,                     -- bDeviceClass
	0x02,                     -- bDeviceSubClass
	0x00,                     -- bDeviceProtocol
	0x40,                     -- bMaxPacketSize
	lsb(USBDC_VENDOR_ID),     -- idVendor (LSB)
	msb(USBDC_VENDOR_ID),     -- idVendor (MSB)
	lsb(USBDC_PRODUCT_ID),    -- idProduct (LSB)
	msb(USBDC_PRODUCT_ID),    -- idProduct (MSB)
	lsb(USBDC_REVISION),      -- bcdDevice (LSB)
	msb(USBDC_REVISION),      -- bcdDevice (MSB)
	0x01,                     -- iManufacturer
	0x02,                     -- iProduct
	0x03,                     -- iSerialNumber
	USBDC_NUM_CONFIGURATIONS  -- bNumConfigurations
)

serial_raw_desc.fs_config = string.char(
-- Configuration Descriptor
	0x9,                    -- bLength
	0x2,                    -- bDescriptorType
	0x4b,                   -- wTotalLength (LSB)       -- Total = Config_len + (Total_interfaces * Interface_len) + (Total_endpoints * Endpoint_len)
	0x00,                   -- wTotalLength (MSB)
	0x02,                   -- bNumInterfaces
	0x01,                   -- bConfigurationValue
	0x04,                   -- iConfiguration
	0xC0,                   -- bmAttributes
	0x00,                   -- max power

-- Application Port Interface Association Descriptor
	0x08,                   -- bLength
	0x0B,                   -- bDescriptorType
	0x00,                   -- bFirstInterface
	0x02,                   -- bInterfaceCount
	0x02,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass

	0x00,                   -- bInterfaceProtocol
	0x05,                   -- iFunction

-- Application Port Communication Class Interface Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x00,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x01,                   -- bNumEndpoints
	0x02,                   -- bInterfaceClass
	0x02,                   -- bInterfaceSubClass

	0x00,                   -- bInterfaceProtocol
	0x06,                   -- iInterface

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

-- Application Port Notification Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x81,                   -- bEndpointAddress
	0x03,                   -- bmAttributes
	0x08,                   -- wMaxPacketSize (LSB)
	0x00,                   -- wMaxPacketSize (MSB)
	0x08,                   -- bInterval

-- Application Port Data Class Interface Descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType
	0x01,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x02,                   -- bNumEndpoints
	0x0A,                   -- bInterfaceClass
	0x00,                   -- bInterfaceSubClass
	0x00,                   -- bInterfaceProtocol
	0x07,                   -- iInterface

-- Application Port Data Out Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x02,                   -- bEndpointAddress:
	0x02,                   -- bmAttributes
	USBDC_FULL_SPEED_MPS,   -- wMaxPacketSize (LSB)
	0x00,                   -- wMaxPacketSize (MSB)
	0x00,                   -- bInterval

-- Applicatin Port Data In Endpoint Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x83,                   -- bEndpointAddress:
	0x02,                   -- bmAttributes
	USBDC_FULL_SPEED_MPS,   -- wMaxPacketSize (LSB)
	0x00,                   -- wMaxPacketSize (MSB)
	0x00                    -- bInterval
)

serial_raw_desc.hs_config = string.char(
-- Configuration Descriptor
	0x9,                                -- bLength
	0x2,                                -- bDescriptorType
	0x4b,                               -- wTotalLength (LSB)       -- Total = Config_len + (Total_interfaces * Interface_len) + (Total_endpoints * Endpoint_len)
	0x00,                               -- wTotalLength (MSB)
	0x02,                               -- bNumInterfaces
	0x01,                               -- bConfigurationValue
	0x04,                               -- iConfiguration
	0xC0,                               -- bmAttributes
	0x00,                               -- max power

-- Application Port Interface Association Descriptor
	0x08,                               -- bLength
	0x0B,                               -- bDescriptorType
	0x00,                               -- bFirstInterface
	0x02,                               -- bInterfaceCount
	0x02,                               -- bInterfaceClass
	0x02,                               -- bInterfaceSubClass

	0x00,                               -- bInterfaceProtocol
	0x05,                               -- iFunction

-- Application Port Communication Class Interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x00,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x01,                               -- bNumEndpoints
	0x02,                               -- bInterfaceClass
	0x02,                               -- bInterfaceSubClass

	0x00,                               -- bInterfaceProtocol
	0x06,                               -- iInterface

-- Header Functional Descriptor
	0x05,                               -- bFunctionLength
	0x24,                               -- bDescriptorType
	0x00,                               -- bDescriptorSubType
	0x10,                               -- bcdCDC   (LSB)
	0x01,                               -- bcdCDC   (MSB)

-- Call Managment Functional Descriptor
	0x05,                               -- bFunctionLength
	0x24,                               -- bDescriptorType
	0x01,                               -- bDescriptorSubType
	0x00,                               -- bmCapabilities - ENOSUP
	0x01,                               -- bDataInterface

-- Abstract Control Model Function Descriptor
	0x04,                               -- bFunctionLength
	0x24,                               -- bDescriptorType
	0x02,                               -- bDescriptorSubType
	0x02,                               -- bmCapabilities

-- Abstract Control Model Union Descriptor
	0x05,                               -- bFunctionLength
	0x24,                               -- bDescriptorType
	0x06,                               -- bDescriptorSubType
	0x00,                               -- bControlInterface
	0x01,                               -- bSubordinate interface

-- Application Port Notification Endpoint Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x81,                               -- bEndpointAddress
	0x03,                               -- bmAttributes
	0x08,                               -- wMaxPacketSize (LSB)
	0x00,                               -- wMaxPacketSize (MSB)
	0x08,                               -- bInterval

-- Application Port Data Class Interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x01,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x02,                               -- bNumEndpoints
	0x0A,                               -- bInterfaceClass
	0x00,                               -- bInterfaceSubClass
	0x00,                               -- bInterfaceProtocol
	0x07,                               -- iInterface

-- Application Port Data Out Endpoint Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x02,                               -- bEndpointAddress:
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (2 bytes)
	msb(USBDC_HIGH_SPEED_MPS),
	0x00,                               -- bInterval

-- Applicatin Port Data In Endpoint Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x83,                               -- bEndpointAddress:
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (2 bytes)
	msb(USBDC_HIGH_SPEED_MPS),
	0x00                                -- bInterval
)

serial_raw_desc.strings = {
	string.char(4, 3, 9, 4),  -- bLength, bDescriptorType, lsb(wLANGID), msb(wLANGID)
	string.char(34, 3)..double_byte'Acme Corporation',
	string.char(44, 3)..double_byte'CDC Serial Peripheral',
	string.char(30, 3)..double_byte'xxxx-xxxx-xxxx',
    string.char(44, 3)..double_byte'Default Configuration',
    string.char(44, 3)..double_byte'Serial Port Interface',
    string.char(84, 3)..double_byte'Serial Port Communication Class Interface',
    string.char(66, 3)..double_byte'Serial Port Data Class Interface',
}
