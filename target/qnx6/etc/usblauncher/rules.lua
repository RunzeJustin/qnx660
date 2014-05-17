USB_CLASS_DEVICE = 0x00
USB_CLASS_AUDIO = 0x01
    USB_AUDIO_SUBCLASS_CONTROL = 0x01
    USB_AUDIO_SUBCLASS_STREAMING = 0x02
        USB_AUDIO_PROTOCOL_1_0 = 0x00
        USB_AUDIO_PROTOCOL_2_0 = 0x20
USB_CLASS_COMMS = 0x02
    USB_COMMS_SUBCLASS_DIRECT_LINE = 0x01
    USB_COMMS_SUBCLASS_MODEM = 0x02
    USB_COMMS_SUBCLASS_TELEPHONE = 0x03
    USB_COMMS_SUBCLASS_MULTICHANNEL = 0x04
    USB_COMMS_SUBCLASS_CAPI_CONTROL = 0x05
    USB_COMMS_SUBCLASS_ETHERNET = 0x06
    USB_COMMS_SUBCLASS_ATM = 0x07
    USB_COMMS_SUBCLASS_WIRELESS_HANDSET = 0x08
    USB_COMMS_SUBCLASS_DEVICE_MGMT = 0x09
    USB_COMMS_SUBCLASS_MOBILE_DIRECT_LINE = 0x0a
    USB_COMMS_SUBCLASS_OBEX = 0x0b
    USB_COMMS_SUBCLASS_NCM  = 0x0d
    USB_COMMS_SUBCLASS_ETHERNET_EMULATION = 0x0c
        USB_COMMS_PROTOCOL_ETHERNET_EMULATION = 0x07
USB_CLASS_HID = 0x03
    USB_HID_SUBCLASS_NONE = 0x00
        USB_HID_PROTOCOL_NONE = 0x00
        USB_HID_PROTOCOL_KEYBOARD = 0x01
        USB_HID_PROTOCOL_MOUSE = 0x02
    USB_HID_SUBCLASS_BOOTINTERFACE = 0x01
USB_CLASS_PHYSICAL = 0x05
USB_CLASS_IMAGING = 0x06
    USB_IMAGING_SUBCLASS_STILL = 0x01
        USB_IMAGING_STILL_PROTOCOL_PTP = 0x01
USB_CLASS_PRINTER = 0x07
USB_CLASS_MASS_STORAGE = 0x08
USB_CLASS_HUB = 0x09
    USB_HUB_PROTOCOL_FULL = 0x00
    USB_HUB_PROTOCOL_HI_SINGLE_TT = 0x01
    USB_HUB_PROTOCOL_HI_MULTIPLE_TT = 0x02
USB_CLASS_CDC_DATA = 0x0a
USB_CLASS_SMART_CARD = 0x0b
USB_CLASS_CONTENT_SECURITY = 0x0d
USB_CLASS_VIDEO = 0x0e
USB_CLASS_DIAGNOSTIC = 0xdc
USB_CLASS_WIRELESS = 0xe0
    USB_WIRELESS_SUBCLASS_RADIO = 0x01
        USB_WIRELESS_PROTOCOL_BLUETOOTH_PI = 0x01
        USB_WIRELESS_PROTOCOL_UWB_RCI = 0x02
        USB_WIRELESS_PROTOCOL_RNDIS = 0x03
    USB_WIRELESS_SUBCLASS_ADAPTER = 0x02
        USB_WIRELESS_PROTOCOL_HOST_WIRE = 0x01
        USB_WIRELESS_PROTOCOL_DEVICE_WIRE = 0x02
        USB_WIRELESS_PROTOCOL_DEVICE_WIRE_ISOCHRONOUS = 0x03
USB_CLASS_MISC = 0xef
USB_CLASS_APPSPEC = 0xef
    USB_APPSPEC_SUBCLASS_FIRMWARE_UPDATE = 0x01
        USB_APPSPEC_PROTOCOL_FIRMWARE_UPDATE = 0x01
    USB_APPSPEC_SUBCLASS_IRDA_BRIDGE = 0x02
        USB_APPSPEC_PROTOCOL_IRDA_BRIDGE = 0x00
    USB_APPSPEC_SUBCLASS_TEST_MEASURE = 0x03
        USB_APPSPEC_PROTOCOL_TMC = 0x00
        USB_APPSPEC_PROTOCOL_USB488 = 0x01
USB_CLASS_VENDOR_SPECIFIC = 0xff

------------------------------------------------------------------------------

--[[
Host_Stack = {
	cmd  = 'io-usb -c -d ehci-mx28 ioport=0x02184100,irq=75,phy=0x020c9000';
	path = '/dev/otg/io-usb';
}

dofile '/etc/usblauncher/iap2.lua'
dofile '/etc/usblauncher/iap2ncm.lua'
dofile '/etc/usblauncher/umass.lua'

Device_Stack = {
	cmd  = 'io-usb-dcd -d iap2-mx6sabrelite-ci ioport=0x02184000,irq=75,vbus_enable';
	path = '/dev/otg/io-usb-dcd';
	descriptors = { iap2, iap2ncm, umass };
}

-- peripheral rules
device(0x1234, 0xfff1) { -- these should match your peripheral's descriptors
	class(USB_CLASS_VENDOR_SPECIFIC, 0xF0, 0x0) {
-- you may need to change the i2c addr= and path= to match your particular board configuration
		driver"mm-ipod -d iap2,config=/etc/mm/iap2.cfg,probe,ppsdir=/pps/services/multimedia/iap2 -a i2c,addr=0x11,path=/dev/i2c99 -t usbdevice,path=/dev/otg/io-usb-dcd -l /dev/shmem/iap2.log -vvvvvv";
	}
}

device(0x1234, 4) {
	class(USB_CLASS_COMMS, USB_COMMS_SUBCLASS_MODEM, 0) {
		driver"devc-serusb_dcd -e -v -F -s -d iface_list=0,path=/dev/otg/io-usb-dcd"
	},
	class(USB_CLASS_MASS_STORAGE)
	{
		driver"devu-umass_client-block -s /dev/otg/io-usb-dcd  -l lun=0,iface=0,fname=/dev/ram0"
	}
}
--]]

--[[
MirrorLink = {
	version = 0x0101;
	vendor_id = 0xABAB;
	blacklist = {
		{ vid = 0x0781; did = 0x74e0 }; -- SanDisk Sansa Fuze+
		{ vid = 0x0951; did = 0x1624 }; -- Kingston DataTraveler G2
		{ vid = 0x05ac;              }; -- any Apple device
	};
	timeout = 2000;
	ignore  = false;
	stall_reset = false;
}
--]]

------------------------------------------------------------------------------

skip_devices = {
	device(0x0424, 0xec00);
	device(0x0eef, 0x0001);  -- eGalax Inc. USB TouchController
}

foreach (skip_devices) {
	Ignore;  -- don't even attach to these devices
}

-- this entry could be included in the skip_devices table instead
device(0x0e0f, 0x0003) {
	Ignore;
}

char_devices = {
	device(0x0557, 0x2008);  -- ATEN_232A/GUC_232A
	device(0x2478, 0x2008);  -- TRIPP LITE U2009-000-R
	device(0x9710, 0x7720);  -- MOSCHIP 7720
	device(0x0403, 0x6001);  -- FTDI 8U232AM
	device(0x1199, 0x0120);  -- Sierra AirCard U595
	device(0x0681, 0x0040);  -- Siemens HC25
	device(0x1bc7, 0x1003);  -- Telit UC864E
	device(0x067b, 0x2303);  -- Prolific
}

foreach (char_devices) {
	driver"devc-serusb -d vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno)";
}

device(0x2001, 0x3c05) {  -- D-Link DUB-E100 ethernet dongle
	-- if you provide scripts to run on device insertion and removal,
	-- comment out this block and enable the start and removal rules instead
	interface() { -- still publish a PPS object but ignore all interfaces
		Ignore;
	};
--	start"netstart.sh";
--	removal"netfinish.sh";
}

-- basic options for devb-umass
DISK_OPTS  = "cam quiet blk cache=1m,vnode=384,auto=none,delwri=2:2,rmvto=none,noatime disk name=umass cdrom name=umasscd";
UMASS_OPTS = "umass priority=21";
--UMASS_OPTS = "umass path=/dev/otg/io-usb,priority=21";

-- table of specific MSC devices that can't handle Microsoft descriptor queries
-- By specifying the vid/did, the rule is tried before any generic rules
known_msc = {
	device(0x0781, 0x5567); -- SanDisk Cruzer Blade
}

foreach (known_msc) {
	driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
}

--[[
-- example commented out
device(0x5dc, 0xa410) { -- Lexar
	Never;  -- Never match this device.  Handy way to disable a rule.
	class(USB_CLASS_MASS_STORAGE) {
		driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
	};
};
--]]

-- iPod
--[[
-- example commented out
product(0x05AC, 0x1200, 0x12FF) {
--    RoleSwap_DigitaliPodOut;
--    RoleSwap_AppleDevice;
--    Probe_iAP2;
-- launch the following drivers if we stay in host mode (and don't role swap)
-- otherwise, role swap is automatic and the mm-ipod rule above is
-- matched after switching stacks.
	class(USB_CLASS_AUDIO, USB_AUDIO_SUBCLASS_CONTROL) {
--        inc_usr_spec_id = unique"/fs/ipod";  -- does rsrcdbmgr_devno_attach
		driver"io-audio -dipod busno=$(busno),devno=$(devno),cap_name=ipod-$(busno)-$(devno)";
	};
	class(USB_CLASS_HID) {
-- you may need to change the i2c addr= and path= to match your particular board configuration
		driver"io-fs-media -dipod,transport=usb:busno=$(busno):devno=$(devno):audio=/dev/snd/ipod-$(busno)-$(devno),darates=+8000:11025:12000:16000:22050:24000,playback,acp=i2c:addr=0x11:path=/dev/i2c99,fnames=short,config=/etc/mm/ipod.cfg,stalk";
	};
	class(USB_CLASS_AUDIO, USB_AUDIO_SUBCLASS_STREAMING) {
		Ignore;
	};
};
--]]

-- specific MTP rule
--[[
-- example commented out
device(0x054c, 0x03fd) { -- Sony Walkman
	-- 4d 54 50 == 'M' 'T' 'P'
	ms_desc(string.char(0x4d, 0x54, 0x50), "", 1) {
		driver"io-fs-media -dpfs-sony,device=$(busno):$(devno):$(iface)";
	};
};
--]]

-- this example shows how to specify a MS descriptor vendorId
-- it is somewhat redundant because the device vid & did are also given
--[[
-- example commented out
device(0x781, 0x7420) { -- SanDisk sansa
	ms_desc("MTP", "", 0xfe) {
		driver"io-fs-media -dpfs-sansa,device=$(busno):$(devno):$(iface)";
	};
};
--]]

-- generic MTP rule should proceed generic MSC (mass storage) rule so that it is tried first.
--[[
-- example commented out
device() {
	ms_desc("MTP") {
		driver"io-fs-media -dpfs,device=$(busno):$(devno):$(iface)";
	};
};
--]]

-- generic mass storage rule

device() {
	class(USB_CLASS_MASS_STORAGE) {
		driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
	};
};

device() {
	class(USB_CLASS_COMMS, USB_COMMS_SUBCLASS_NCM) {
		start"echo NCM interface $(iface)";
	};
};

------------------------------------------------------------------------------

if verbose >= 3 then
	table.dump(new_conf)
	table.dump(new_conf.flags)
	show_config()
end

