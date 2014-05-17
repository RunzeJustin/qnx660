USB_CLASS_MASS_STORAGE = 0x08

-- basic options for devb-umass
DISK_OPTS  = "cam quiet blk cache=1m,vnode=384,auto=none,delwri=2:2,rmvto=none,noatime disk name=umass cdrom name=umasscd";
UMASS_OPTS = "umass priority=21";

device() {
	class(USB_CLASS_MASS_STORAGE) {
		driver"devb-umass $(DISK_OPTS) $(UMASS_OPTS),vid=$(vendor_id),did=$(product_id),busno=$(busno),devno=$(devno),iface=$(iface),ign_remove";
	};
};

if verbose >= 3 then
	table.dump(new_conf)
	table.dump(new_conf.flags)
	show_config()
end


local busno_user = {}  -- remember who is using each busno

local original_launch_driver         = launch_driver
local original_destroy_driver_object = destroy_driver_object
local original_destroy_device_object = destroy_device_object

function launch_driver(obj)
	local busno = obj.busno

	if busno_user[busno] then
	fyi(obj, 'cannot launch driver because %s is using busno %s', busno_user[busno], busno)
		return
	end

	local drv_obj_name, pid = original_launch_driver(obj)

	if drv_obj_name then
		busno_user[busno] = drv_obj_name  -- allocate busno
	end

	return drv_obj_name, pid
end

function destroy_driver_object(drv_obj, drv_obj_name, dev_obj, dev_obj_name)
	local busno = drv_obj.busno

	if drv_obj_name == busno_user[busno] then
	fyi(drv_obj, 'release busno %s', busno)
		busno_user[busno] = nil  -- release busno
	end

	return original_destroy_driver_object(drv_obj, drv_obj_name, dev_obj, dev_obj_name)
end

function destroy_device_object(dev_obj, dev_obj_name)

	-- you may add hooks here too

	return original_destroy_device_object(dev_obj, dev_obj_name)
end

