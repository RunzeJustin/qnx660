/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems.
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

#ifndef DVFS_API_H
#define DVFS_API_H

/**
 * This structure may be used by applications to register a notification
 * handler
 */
typedef struct {
    int   reql;       /* Requested power level by application */
    int   capp_chid;  /* Channel identifier of the requesting application */
    pid_t capp_pid;   /* Application's process identifier */
} dvfs_data_t;

/**
 * This structure may be used by applications to read back various information
 * from DVFS
 */
typedef struct {
    int cpuload[32];  /* CPU loads (if applicable) */
    int temperature;  /* Core temperature (if applicable) */
    int pwrlevl;      /* Current power level */
    int mode;         /* Current DVFS operating point */
    int total_pwrlvl; /* Total number of DVFS power levels */
} dvfs_status_t;

/**
 * Definitions used to notify clients of changes to their desired minimum power level
 */
#define DVFS_NOTIFY_REJECTED          0x20           /* Current level has been rejected due to temperature limits */
#define DVFS_NOTIFY_RESTORED          0x21           /* Previous level has been restored */
#define DVFS_NOTIFY_TERMINATED        0x22           /* Request has been terminated by driver (switching to manual/semi mode) */

/**
 * DEVCTL definitions supported by DVFS resource manager
 */
#define DVFS_DEVCTL_SET_MIN           __DIOT(_DCMD_MISC, 0x100, dvfs_data_t)    /* Set minimum operating point */
#define DVFS_DEVCTL_UNSET_MIN         __DIOT(_DCMD_MISC, 0x101, dvfs_data_t)    /* Unset minimum operating point */
#define DVFS_DEVCTL_SET_MODE          __DIOT(_DCMD_MISC, 0x102, dvfs_data_t)    /* Set operating mode (auto,semi,manual) */
#define DVFS_DEVCTL_SET_PWR_LVL       __DIOT(_DCMD_MISC, 0x103, dvfs_data_t)    /* Set power level (for semi/manual) */
#define DVFS_DEVCTL_GETSTATUS         __DIOF(_DCMD_MISC, 0x104, dvfs_status_t)  /* Read DVFS status */
#define DVFS_DEVCTL_RUN_MAX           __DIOT(_DCMD_MISC, 0x105, dvfs_data_t)    /* Run at highest possible operating point */
#define DVFS_DEVCTL_RUN_MIN           __DIOT(_DCMD_MISC, 0x106, dvfs_data_t)    /* Run at lowest possible operating point */

/**
 *  DVFS operating modes:
 *   AUTO: DVFS will scale voltage/frequency based on cpu load and temperature
 *   SEMI: User will call voltage/frequency scaling API based on CPU load. DVFS will monitor/react to temperature
 *    MAN: User will call voltage/frequency scaling API based on CPU load and temperature
 */
#define DVFS_MODE_AUTO 0
#define DVFS_MODE_SEMI 1
#define DVFS_MODE_MAN  2
#define DVFS_MODE_MAX  2

/**
 * dvfs_pre_init: Initial CPU initialization
 * - Description: This function performs early CPU initializations
 * that might be needed before parsing the configuration file or other
 * cpu-related configurations
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 * - Returns:
 *  - Status of pre-init. EOK on success, EFAULT on failure
 */
int dvfs_pre_init(void * handle);

/**
 * dvfs_init: CPU-related initialization
 * - Description: This function performs numerous CPU initialization
 * required for CPU load calculation and voltage/frequency scaling. This
 * function is also expected to initiate and kick off CPU load calculation
 * gear (threads/hardware/interrupts) in order to deliver CPU load related
 * events to the main CTRL thread
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 * - Returns: CPU initialization status: EOK on success, EFAULT on Failure.
 *
 */
int dvfs_init(void *handle);

/**
 * dvfs_therm_init: SoC/hardware temperature sensing initialization
 * - Description: This function is in charge of performing SoC/hardware
 * level initialization
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 * - Returns:
 *  - thermal initialization status: EOK on success, EFAULT on failure
 */
int dvfs_therm_init(void *handle);

/* Function to release the resource and close
* handle: the handle returned by dvfs_init
*/

/**
 * dvfs_fini: CPU-related de-initialization
 * - Description: This function is in charge of cleaning
 * up after dvfs_init function upon shutdown.
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 */
void dvfs_fini(void *handle);

/**
 * get_pwr_levels_count: Obtain the supported power levels
 * - Description: This function returns the number of power
 * levels allowed for a given SoC. This is to ensure the user-defined
 * configuration file does not have more levels that allowed by SoC.
 * - Returns:
 *  - The number of power levels for specific SoC.
 */
int get_pwr_levels_count(void *handle);

/**
 * get_pwr_lvl_freq: Get the frequency of given power level (from table)
 * - Description: This function returns the allowed frequency for a given power level
 * - Arguments:
 *  - pwr_level: The requested power level
 * - Returns:
 *  - The corresponding frequency of the given power level OR -1 for invalid power level
 */
uint32_t get_pwr_lvl_freq(void *handle, uint8_t pwr_level);

/**
 * get_pwr_lvl_volt: Get the voltage of given power level (from table)
 * - Description: This function returns the voltage level for a given power level
 * - Arguments:
 *  - pwr_level: The requested power level
 * - Returns:
 *  - The corresponding voltage of the given power level OR -1 for invalid power level
 */
uint32_t get_pwr_lvl_volt(void *handle, uint8_t pwr_level);

/**
 * get_cpu_freq: Get CPU frequency (in Hz) *
 * - Description: This function calculates CPU frequency based on System PLL
 * frequency and CPU divider
 * - Returns:
 *  - CPU frequency (in Hz) OR 0 in case of error
 */
uint32_t get_cpu_freq(void *handle);

/**
 * get_cpu_voltage: Get CPU voltage (in uV)
 * - Description: This function is used to get CPU voltage (in uV)
 * - Returns:
 *  - CPU voltage
 */
uint32_t get_cpu_voltage(void *handle);

/**
 * get_cpu_temperature: Get CPU temperature
 * - Description: This function is used to get core temperature. The implementation
 * may involved built-in temperature sensors or external sensors.
 * - Returns:
 *  - Core temperature
 */
int get_cpu_temperature(void *handle);

/*
 * set_cpu_freq: Set CPU frequency
 * - Description: This function is used to set CPU frequency (in Hz). This function
 * must ensure the requested frequency does not exceed maximum allowed frequency
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 *  - freq: The desired frequency (in Hz)
 * - Returns:
 *  - Status of frequency change. EOK on success, EFAULT on error
 */
int set_cpu_freq(void *handle, uint32_t freq);

/**
 * set_cpu_voltage: Set CPU voltage (in uV)
 * - Description: This function is in charge of changing the CPU voltage to the
 * desired level. This function must ensure the voltage is within an allowed range
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 *  - voltage: The desired voltage level (in uV)
 * - Returns:
 *  - Status of voltage change. EOK on success, EFAULT on error
 */
int set_cpu_voltage(void *handle, uint32_t voltage);

/**
 * post_pwr_lvl_config: Perform post-processing after power level change
 * - Description: This function is an optional call for platforms that require
 * any post-action after power levels are changed.
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 *
 */
void post_pwr_lvl_config(void *handle, int lvl);

/**
 * update_boundaries: Update max/min boundaries
 * - Description: This function is an optional call for platforms to
 * update the minimum/maximum boundaries needed by SoC after an
 * application or thermal thread disable/enable
 * levels
 * - Arguments:
 *  - handle: A pointer to the global dvfs structure
 *  - lvl:    The new power level
 */
void update_boundaries(void *handle);

#endif /* __DVFS_H__ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/dvfsmgr/public/hw/dvfs_api.h $ $Rev: 732568 $")
#endif
