/*
 * Copyright (c) 2016, Linaro Limited. All rights reserved.
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

/* watchdog constants */
#define RPI3_WDOG_BASE_ADDRESS			0x3f100000
#define RPI3_WDOG_PASSWORD			0x5a000000
#define RPI3_WDOG_HALT_AFTER_RESET		0x555
#define RPI3_WDOG_RSTC_OFFSET			0x0000001c
#define RPI3_WDOG_RSTS_OFFSET			0x00000020
#define RPI3_WDOG_WDOG_OFFSET			0x00000024
#define RPI3_WDOG_RSTC_WRCFG_MASK		0x00000030
#define RPI3_WDOG_RSTC_WRCFG_FULL_RESET		0x00000020

/* local interrupt controller */
#define RPI3_INTC_BASE_ADDRESS			0x40000000
#define RPI3_INTC_CONTROL_OFFSET		0x00000000
#define RPI3_INTC_PRESCALER_OFFSET		0x00000008
#define RPI3_INTC_MBOX_CONTROL_OFFSET		0x00000050
#define RPI3_INTC_MBOX_CONTROL_SLOT3_FIQ	0x00000080
#define RPI3_INTC_PENDING_FIQ_OFFSET		0x00000070
#define RPI3_INTC_PENDING_FIQ_MBOX3		0x00000080
