/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Embedded Artists i.MX6 Quad COM Board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#ifndef __MX6QEA_COM_H
#define __MX6QEA_COM_H

#include "mx6_common.h"

#ifdef CONFIG_SPL
#include "imx6_spl.h"
#endif

/* uncomment for PLUGIN mode support */
/* #define CONFIG_USE_PLUGIN */

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

#ifdef CONFIG_SECURE_BOOT
#ifndef CONFIG_CSF_SIZE
#define CONFIG_CSF_SIZE 0x4000
#endif
#endif

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_MXC_UART_BASE		UART1_BASE

#define CONFIG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=${console},${baudrate} " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.file=/fat g_mass_storage.ro=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
                "enable_wait_mode=off "\
		"\0" \
	"initrd_addr=0x12C00000\0" \
	"initrd_high=0xffffffff\0" \
	"bootcmd_mfg=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0"

#ifdef CONFIG_MX6DL
#define FDT_FILE "imx6dlea-com-kit.dtb"
#else
#define FDT_FILE "imx6qea-com-kit.dtb"
#endif

#ifdef EA_IMX_PTP
#define EA_IMX_PTP_ENV_SETTINGS "eadisp_hdmi_enabled=yes\0eadisp_prefer=hdmi\0"
#else
#define EA_IMX_PTP_ENV_SETTINGS ""
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS \
	EA_IMX_PTP_ENV_SETTINGS \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"console=ttymxc0\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_file=" FDT_FILE "\0" \
	"fdt_addr=0x18000000\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"panel=Hannstar-XGA\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=1\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	"mmcautodetect=yes\0" \
	"smp=\0"\
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot} ${args_from_script}\0" \
	"loadbootscript=" \
		"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp ${args_from_script}\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0"

#define CONFIG_BOOTCOMMAND \
	   "mmc dev ${mmcdev};" \
	   "mmc dev ${mmcdev}; if mmc rescan; then " \
		   "if run loadbootscript; then " \
			   "run bootscript; " \
		   "else " \
			   "if run loadimage; then " \
				   "run mmcboot; " \
			   "else run netboot; " \
			   "fi; " \
		   "fi; " \
	   "else run netboot; fi"

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x10000)


/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#ifdef CONFIG_MX6DL
#define PHYS_SDRAM_SIZE			SZ_1G
#else
#define PHYS_SDRAM_SIZE			SZ_2G
#endif

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* MMC Configuration */
#define CONFIG_SYS_FSL_USDHC_NUM	3
#define CONFIG_SYS_MMC_ENV_DEV		2  /*USDHC4*/
#define CONFIG_SYS_MMC_ENV_PART		0  /* user area */
#define CONFIG_MMCROOT			"/dev/mmcblk2p2"  /* SDHC3 */

#define CONFIG_SYS_FSL_ESDHC_ADDR	0

/* I2C Configs */
#ifndef CONFIG_DM_I2C
#define CONFIG_SYS_I2C
#endif
#ifdef CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_I2C_SPEED		  100000
#endif

/* PMIC */
#ifndef CONFIG_DM_PMIC
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08
#endif

/* Network */
#define CONFIG_FEC_MXC
#define CONFIG_MII

#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x1

#define CONFIG_FEC_XCV_TYPE             RGMII
#ifdef CONFIG_DM_ETH
#define CONFIG_ETHPRIME			"eth0"
#else
#define CONFIG_ETHPRIME			"FEC"
#endif

#define CONFIG_PHYLIB
#define CONFIG_PHY_ATHEROS


/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#endif

/* Framebuffer */
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IMX_HDMI


#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)


/* EA: EEPROM */
#define CONFIG_CMD_EEPROM
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#define CONFIG_ENV_EEPROM_IS_ON_I2C
/* the page boundary is 32 bytes (2^5 = 32) */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 5
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10

#if defined(CONFIG_ANDROID_SUPPORT)
#include "mx6sabreandroid_common.h"
#else

#ifndef CONFIG_SPL
#define CONFIG_USBD_HS
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#endif

#endif /* CONFIG_ANDROID_SUPPORT */



#endif				/* __CONFIG_H */
