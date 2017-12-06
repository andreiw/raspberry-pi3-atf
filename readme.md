ARM Trusted Firmware for RPi3
=============================

Last updated May 9th, 2018.

This is an implementation of ATF for the RPi3 platform, based off of
https://github.com/ardbiesheuvel/arm-trusted-firmware/tree/rpi3.

No attempt has been made to keep it in sync with https://github.com/ARM-software/arm-trusted-firmware. Sorry.

Purpose
=======

This tree is meant to be used with a preloaded BL33 payload, as part
of a UEFI or U-Boot implementation for the Raspberry Pi 3.

This is a 64-bit implementation.

Building
========

```
export CROSS_COMPILE=aarch64-linux-gnu-
make -C raspberry-pi3-atf PLAT=rpi3 PRELOADED_BL33_BASE=0x30000 SUPPORT_VFP=1 DEBUG=1 V=1 fip all
```

This is not directly useful by itself, since you would need to combine the BL1 and FIP with a BL33 payload.

Features
========

* PSCI_CPU_ON_AARCH64
* PSCI_SYSTEM_RESET
* PSCI_SYSTEM_OFF (as PSCI_SYSTEM_RESET)
* Compatible with Windows on Arm ;-).

Implementation Details
======================

ATF of course runs in secure mode, but there is no secure memory, and there are no secure peripherals. Caveat Emptor!

This ATF implementation expects the following memory layout:

| Address Start | Address End | What |
| --- | --- | --- |
| `0x00000000` | `0x00007FFF` | BL1 |
| `0x00008000` | `0x0000FFFF` | DTB |
| `0x00010000` | `0x0002FFFF` | FIP containing BL2 + BL31 |
| `0x00030000` | `0x001FFFFF` | BL33 Non-Secure firmware |
| `0x00200000` | `0x0024FFFF` | "Secure SRAM" |
| `0x00250000` | `0x003FFFFF` | "Secure DRAM" |
| `0x00400000` | ... | Non-Secure DRAM |

This means that a minimally-viable image will concatenate BL1, FIP and the BL33
payload, to be loaded via a custom `config.txt`:
```
arm_control=0x200
enable_uart=1
armstub=atf_and_bl33.bin
disable_commandline_tags=2
device_tree_address=0x8000
device_tree_end=0x10000
```

`[0x8000:0x10000)` is where you can load the DTB if you want it, this ATF implementation does not use
the DTB in any way.

Contact
=======

Andrey Warkentin <andrey.warkentin@gmail.com>

Btw, feel free to upstream, if so inclined.
