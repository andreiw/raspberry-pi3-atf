/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <arch.h>
#include <common_def.h>
#include <tbbr_img_def.h>

/* Special value used to verify platform parameters from BL2 to BL3-1 */
#define RPI3_BL31_PLAT_PARAM_VAL	0x0f1e2d3c4b5a6978ULL

#define PLATFORM_STACK_SIZE		0x1000

#define PLATFORM_MAX_CPUS_PER_CLUSTER	4
#define PLATFORM_CLUSTER_COUNT		1
#define PLATFORM_CLUSTER0_CORE_COUNT	PLATFORM_MAX_CPUS_PER_CLUSTER
#define PLATFORM_CLUSTER1_CORE_COUNT	0
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT + \
					 PLATFORM_CLUSTER1_CORE_COUNT)

#define RPI3_PRIMARY_CPU		0

#define PLAT_NUM_PWR_DOMAINS		(PLATFORM_CLUSTER_COUNT + \
					PLATFORM_CORE_COUNT)
#define PLAT_MAX_PWR_LVL		MPIDR_AFFLVL1

#define PLAT_MAX_RET_STATE		1
#define PLAT_MAX_OFF_STATE		2

/* Local power state for power domains in Run state. */
#define PLAT_LOCAL_STATE_RUN		0
/* Local power state for retention. Valid only for CPU power domains */
#define PLAT_LOCAL_STATE_RET		1
/*
 * Local power state for OFF/power-down. Valid for CPU and cluster power
 * domains.
 */
#define PLAT_LOCAL_STATE_OFF		2

/*
 * Macros used to parse state information from State-ID if it is using the
 * recommended encoding for State-ID.
 */
#define PLAT_LOCAL_PSTATE_WIDTH		4
#define PLAT_LOCAL_PSTATE_MASK		((1 << PLAT_LOCAL_PSTATE_WIDTH) - 1)

/*
 * Some data must be aligned on the biggest cache line size in the platform.
 * This is known only to the platform as it might have a combination of
 * integrated and external caches.
 */
#define CACHE_WRITEBACK_SHIFT		6
#define CACHE_WRITEBACK_GRANULE		(1 << CACHE_WRITEBACK_SHIFT)

/*
 * Partition memory into secure ROM, non-secure DRAM, secure "SRAM",
 * and secure DRAM.
 */
#define SEC_ROM_BASE			0x00000000
#define SEC_ROM_SIZE			0x00008000

#define NS_DRAM0_BASE			0x00400000
#define NS_DRAM0_SIZE			0x00c00000

#define SEC_SRAM_BASE			0x00190000
#define SEC_SRAM_SIZE			0x00070000

#define SEC_DRAM_BASE			0x00200000
#define SEC_DRAM_SIZE			0x00200000

/*
 * ARM-TF lives in SRAM, partition it here
 */

#define SHARED_RAM_BASE			SEC_SRAM_BASE
#define SHARED_RAM_SIZE			0x00001000

#define PLAT_RPI3_TRUSTED_MAILBOX_BASE	SHARED_RAM_BASE
#define PLAT_RPI3_TRUSTED_MAILBOX_SIZE	(8 + PLAT_RPI3_HOLD_SIZE)
#define PLAT_RPI3_HOLD_BASE		(PLAT_RPI3_TRUSTED_MAILBOX_BASE + 8)
#define PLAT_RPI3_HOLD_SIZE		(PLATFORM_CORE_COUNT * \
					 PLAT_RPI3_HOLD_ENTRY_SIZE)
#define PLAT_RPI3_HOLD_ENTRY_SIZE	8
#define PLAT_RPI3_HOLD_STATE_WAIT	0x1337
#define PLAT_RPI3_HOLD_STATE_GO		0

#define BL_RAM_BASE			(SHARED_RAM_BASE + SHARED_RAM_SIZE)
#define BL_RAM_SIZE			(SEC_SRAM_SIZE - SHARED_RAM_SIZE)

/*
 * BL1 specific defines.
 *
 * BL1 RW data is relocated from ROM to RAM at runtime so we need 2 sets of
 * addresses.
 * Put BL1 RW at the top of the Secure SRAM. BL1_RW_BASE is calculated using
 * the current BL1 RW debug size plus a little space for growth.
 */
#define BL1_RO_BASE			SEC_ROM_BASE
#define BL1_RO_LIMIT			(SEC_ROM_BASE + SEC_ROM_SIZE)
#define BL1_RW_BASE			(BL1_RW_LIMIT - 0x12000)
#define BL1_RW_LIMIT			(BL_RAM_BASE + BL_RAM_SIZE)

/*
 * BL2 specific defines.
 *
 * Put BL2 just below BL3-1. BL2_BASE is calculated using the current BL2 debug
 * size plus a little space for growth.
 */
#define BL2_BASE			(BL31_BASE - 0x2C000)
#define BL2_LIMIT			BL31_BASE

/*
 * BL3-1 specific defines.
 *
 * Put BL3-1 at the top of the Trusted SRAM. BL31_BASE is calculated using the
 * current BL3-1 debug size plus a little space for growth.
 */
#define BL31_BASE			(BL31_LIMIT - 0x20000)
#define BL31_LIMIT			(BL_RAM_BASE + BL_RAM_SIZE)
#define BL31_PROGBITS_LIMIT		BL1_RW_BASE


/*
 * BL3-2 specific defines.
 *
 * BL3-2 can execute from Secure SRAM, or Secure DRAM.
 */
#define BL32_SRAM_BASE			BL_RAM_BASE
#define BL32_SRAM_LIMIT			BL31_BASE
#define BL32_DRAM_BASE			SEC_DRAM_BASE
#define BL32_DRAM_LIMIT			(SEC_DRAM_BASE + SEC_DRAM_SIZE)

#define SEC_SRAM_ID			0
#define SEC_DRAM_ID			1

#if BL32_RAM_LOCATION_ID == SEC_SRAM_ID
# define BL32_MEM_BASE			BL_RAM_BASE
# define BL32_MEM_SIZE			BL_RAM_SIZE
# define BL32_BASE			BL32_SRAM_BASE
# define BL32_LIMIT			BL32_SRAM_LIMIT
#elif BL32_RAM_LOCATION_ID == SEC_DRAM_ID
# define BL32_MEM_BASE			SEC_DRAM_BASE
# define BL32_MEM_SIZE			SEC_DRAM_SIZE
# define BL32_BASE			BL32_DRAM_BASE
# define BL32_LIMIT			BL32_DRAM_LIMIT
#else
# error "Unsupported BL32_RAM_LOCATION_ID value"
#endif
#define BL32_SIZE			(BL32_LIMIT - BL32_BASE)

#define ADDR_SPACE_SIZE			(1ull << 32)
#define MAX_MMAP_REGIONS		8
#define MAX_XLAT_TABLES			6
#define MAX_IO_DEVICES			3
#define MAX_IO_HANDLES			4

/*
 * PL011 related constants
 */
#define UART0_BASE			0x3f215040
#define UART0_CLK_IN_HZ			500000000

#define PLAT_RPI3_BOOT_UART_BASE	UART0_BASE
#define PLAT_RPI3_BOOT_UART_CLK_IN_HZ	UART0_CLK_IN_HZ

#define PLAT_RPI3_CONSOLE_BAUDRATE	115200

#define PLAT_RPI3_FIP_BASE		0x00010000
#define PLAT_RPI3_FIP_MAX_SIZE		0x00020000

#define DEVICE0_BASE			0x3f000000
#define DEVICE0_SIZE			0x01000000

/*
 * System counter
 */
#define SYS_COUNTER_FREQ_IN_TICKS	19200000

#endif /* __PLATFORM_DEF_H__ */
