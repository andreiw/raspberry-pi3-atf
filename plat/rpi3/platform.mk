#
# Copyright (c) 2013-2015, ARM Limited and Contributors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of ARM nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

PLAT_INCLUDES		:=	-Iinclude/plat/arm/common/		\
				-Iinclude/plat/arm/common/aarch64/	\
				-Iplat/rpi3/include			\
				-Iinclude/common/tbbr


PLAT_BL_COMMON_SOURCES	:=	plat/rpi3/rpi3_common.c			\
				drivers/console/aarch64/console.S	\
				drivers/ti/uart/aarch64/16550_console.S	\
				lib/xlat_tables/xlat_tables_common.c	\
				lib/xlat_tables/aarch64/xlat_tables.c

BL1_SOURCES		+=	drivers/io/io_fip.c			\
				drivers/io/io_memmap.c			\
				drivers/io/io_storage.c			\
				plat/rpi3/rpi3_io_storage.c		\
				lib/cpus/aarch64/cortex_a53.S		\
				plat/common/aarch64/platform_mp_stack.S	\
				plat/rpi3/aarch64/plat_helpers.S	\
				plat/rpi3/rpi3_bl1_setup.c

BL2_SOURCES		+=	drivers/io/io_fip.c			\
				drivers/io/io_memmap.c			\
				drivers/io/io_storage.c			\
				plat/common/aarch64/platform_mp_stack.S	\
				plat/rpi3/rpi3_io_storage.c		\
				plat/rpi3/aarch64/plat_helpers.S	\
				plat/rpi3/rpi3_bl2_setup.c

BL31_SOURCES		+=	lib/cpus/aarch64/cortex_a53.S		\
				plat/common/aarch64/platform_mp_stack.S	\
				plat/common/aarch64/plat_psci_common.c	\
				plat/common/aarch64/plat_common.c	\
				plat/rpi3/rpi3_pm.c			\
				plat/rpi3/topology.c			\
				plat/rpi3/aarch64/plat_helpers.S	\
				plat/rpi3/rpi3_bl31_setup.c

# Disable the PSCI platform compatibility layer
ENABLE_PLAT_COMPAT	:= 0

BL32_RAM_LOCATION	:= tdram
ifeq (${BL32_RAM_LOCATION}, tsram)
  BL32_RAM_LOCATION_ID = SEC_SRAM_ID
else ifeq (${BL32_RAM_LOCATION}, tdram)
  BL32_RAM_LOCATION_ID = SEC_DRAM_ID
else
  $(error "Unsupported BL32_RAM_LOCATION value")
endif

# Process flags
$(eval $(call add_define,BL32_RAM_LOCATION_ID))
