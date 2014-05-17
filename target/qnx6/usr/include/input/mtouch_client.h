/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#include "input/mtouch_params.h"

#ifndef MTOUCH_CLIENT_H_
#define MTOUCH_CLIENT_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

struct input_descriptor* mtouch_client_open(_Uint8t class_idx, mtouch_client_params_t* params);
int mtouch_client_close(struct input_descriptor* id);
int mtouch_client_read(struct input_descriptor* id, void* buf, _Int32t buf_size, _Int32t event_stride, int blocking);

int mtouch_get_client_params(struct input_descriptor* id, mtouch_client_params_t* params);
int mtouch_set_client_params(struct input_descriptor* id, mtouch_client_params_t* params);
int mtouch_add_filter(struct input_descriptor* id, mtouch_filter_config_t* filter_config);
int mtouch_get_driver_params(struct input_descriptor* id, mtouch_driver_params_t* params);
int mtouch_get_filter_id(const char *name);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* MTOUCH_CLIENT_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/mtouch_client.h $ $Rev: 724998 $")
#endif
