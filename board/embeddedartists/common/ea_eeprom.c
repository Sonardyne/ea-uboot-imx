/*
 * Copyright (C) 2015 Embedded Artists AB
 *
 * Configuration parameters stored in EEPROM for the Embedded Artists
 * i.MX COM Board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <i2c.h>
#include <dm.h>

#include "ea_eeprom.h"

#if !(defined(CONFIG_TARGET_MX7DEA_COM) || defined(CONFIG_TARGET_MX7DEA_UCOM))
struct _ea_ddr_cfg
{
	u32 addr;
	u32 val;
};


#define EA_DDR_LIST_BUF_SZ (8)
//static struct ea_ddr_cfg ddr_list_buf[EA_DDR_LIST_BUF_SZ];

/*
 * Default values for DDR initialization in case eeprom data
 * couldn't be read
 */
static struct _ea_ddr_cfg ddr_init_default[] = {
#if defined(CONFIG_MX6SX)
	{0x020e0618, 0x000c0000},
	{0x020e05fc, 0x00000000},

	{0x020e032c, 0x00000030},

	{0x020e0300, 0x00000020},
	{0x020e02fc, 0x00000020},
	{0x020e05f4, 0x00000020},

	{0x020e0340, 0x00000020},

	{0x020e0320, 0x00000000},
	{0x020e0310, 0x00000020},
	{0x020e0314, 0x00000020},
	{0x020e0614, 0x00000020},

	{0x020e05f8, 0x00020000},
	{0x020e0330, 0x00000028},
	{0x020e0334, 0x00000028},
	{0x020e0338, 0x00000028},
	{0x020e033c, 0x00000028},

	{0x020e0608, 0x00020000},
	{0x020e060c, 0x00000028},
	{0x020e0610, 0x00000028},
	{0x020e061c, 0x00000028},
	{0x020e0620, 0x00000028},
	{0x020e02ec, 0x00000028},
	{0x020e02f0, 0x00000028},
	{0x020e02f4, 0x00000028},
	{0x020e02f8, 0x00000028},

	{0x021b0800, 0xa1390003},

	{0x021b080c, 0x002b0025},
	{0x021b0810, 0x00290024},

	{0x021b083c, 0x4153014B},
	{0x021b0840, 0x013E0132},

	{0x021b0848, 0x43434549},
	{0x021b0850, 0x36363A35},

	{0x021b081c, 0x33333333},
	{0x021b0820, 0x33333333},
	{0x021b0824, 0x33333333},
	{0x021b0828, 0x33333333},

	{0x021b08b8, 0x00000800},

	{0x021b0004, 0x0002002d},
	{0x021b0008, 0x00333030},
	{0x021b000c, 0x676b52f3},
	{0x021b0010, 0xb66d8b63},
	{0x021b0014, 0x01ff00db},
	{0x021b0018, 0x00011740},
	{0x021b001c, 0x00008000},
	{0x021b002c, 0x000026d2},
	{0x021b0030, 0x006b1023},
	{0x021b0040, 0x0000005f},
	{0x021b0000, 0x84190000},

	{0x021b001c, 0x04008032},
	{0x021b001c, 0x00008033},
	{0x021b001c, 0x00048031},
	{0x021b001c, 0x05208030},
	{0x021b001c, 0x04008040},

	{0x021b0020, 0x00000800},
	{0x021b0818, 0x00011117},
	{0x021b001c, 0x00000000},

#elif defined(CONFIG_MX6Q)
	{0x020e0798, 0x000C0000},
	{0x020e0758, 0x00000000},
	{0x020e0588, 0x00000030},
	{0x020e0594, 0x00000030},
	{0x020e056c, 0x00000030},
	{0x020e0578, 0x00000030},
	{0x020e074c, 0x00000030},
	{0x020e057c, 0x00000030},
	{0x020e058c, 0x00000000},
	{0x020e059c, 0x00000030},
	{0x020e05a0, 0x00000030},
	{0x020e078c, 0x00000030},
	{0x020e0750, 0x00020000},
	{0x020e05a8, 0x00000028},
	{0x020e05b0, 0x00000028},
	{0x020e0524, 0x00000028},
	{0x020e051c, 0x00000028},
	{0x020e0518, 0x00000028},
	{0x020e050c, 0x00000028},
	{0x020e05b8, 0x00000028},
	{0x020e05c0, 0x00000028},
	{0x020e0774, 0x00020000},
	{0x020e0784, 0x00000028},
	{0x020e0788, 0x00000028},
	{0x020e0794, 0x00000028},
	{0x020e079c, 0x00000028},
	{0x020e07a0, 0x00000028},
	{0x020e07a4, 0x00000028},
	{0x020e07a8, 0x00000028},
	{0x020e0748, 0x00000028},
	{0x020e05ac, 0x00000028},
	{0x020e05b4, 0x00000028},
	{0x020e0528, 0x00000028},
	{0x020e0520, 0x00000028},
	{0x020e0514, 0x00000028},
	{0x020e0510, 0x00000028},
	{0x020e05bc, 0x00000028},
	{0x020e05c4, 0x00000028},
	{0x021b0800, 0xa1390003},
	{0x021b080c, 0x001F0018},
	{0x021b0810, 0x0023001F},
	{0x021b480c, 0x000F001F},
	{0x021b4810, 0x0006001D},
	{0x021b083c, 0x43340344},
	{0x021b0840, 0x03300328},
	{0x021b483c, 0x432C0340},
	{0x021b4840, 0x03300274},
	{0x021b0848, 0x3A303232},
	{0x021b4848, 0x36362E3E},
	{0x021b0850, 0x32343E3C},
	{0x021b4850, 0x4032463E},
	{0x021b081c, 0x33333333},
	{0x021b0820, 0x33333333},
	{0x021b0824, 0x33333333},
	{0x021b0828, 0x33333333},
	{0x021b481c, 0x33333333},
	{0x021b4820, 0x33333333},
	{0x021b4824, 0x33333333},
	{0x021b4828, 0x33333333},
	{0x021b08b8, 0x00000800},
	{0x021b48b8, 0x00000800},
	{0x021b0004, 0x00020036},
	{0x021b0008, 0x09444040},
	{0x021b000c, 0x8A8F7955},
	{0x021b0010, 0xFF328F64},
	{0x021b0014, 0x01FF00DB},
	{0x021b0018, 0x00001740},
	{0x021b001c, 0x00008000},
	{0x021b002c, 0x000026d2},
	{0x021b0030, 0x008F1023},
	{0x021b0040, 0x00000047},
	{0x021b0000, 0x841A0000},
// ---------------------------------->
	/*{0x021b001c, 0x04088032},
	{0x021b001c, 0x00008033},
	{0x021b001c, 0x00048031},
	{0x021b001c, 0x09408030},
	{0x021b001c, 0x04008040},*/
// <----------------------------------
	{0x021b0020, 0x00005800},
	{0x021b0818, 0x00011117},
	{0x021b4818, 0x00011117},
	{0x021b0004, 0x00025576},
	{0x021b0404, 0x00011006},
	{0x021b001c, 0x00000000},
	{0x020c4068, 0x00C03F3F},
	{0x020c406c, 0x0030FC03},
	{0x020c4070, 0x0FFFC000},
	{0x020c4074, 0x3FF00000},
	{0x020c4078, 0x00FFF300},
	{0x020c407c, 0x0F0000F3},
	{0x020c4080, 0x000003FF},
	{0x020e0010, 0xF00000CF},
	{0x020e0018, 0x007F007F},
	{0x020e001c, 0x007F007F},
	{0x020c4060, 0x000000fb},

#elif defined(CONFIG_MX6DL)
        {0x020e0774, 0x000C0000},
        {0x020e0754, 0x00000000},
        {0x020e04ac, 0x00000030},
        {0x020e04b0, 0x00000030},
        {0x020e0464, 0x00000030},
        {0x020e0490, 0x00000030},
        {0x020e074c, 0x00000030},
        {0x020e0494, 0x00000030},
        {0x020e04a0, 0x00000000},
        {0x020e04b4, 0x00000030},
        {0x020e04b8, 0x00000030},
        {0x020e076c, 0x00000030},
        {0x020e0750, 0x00020000},
        {0x020e04bc, 0x00000030},
        {0x020e04c0, 0x00000030},
        {0x020e04c4, 0x00000030},
        {0x020e04c8, 0x00000030},
        {0x020e04cc, 0x00000030},
        {0x020e04d0, 0x00000030},
        {0x020e04d4, 0x00000030},
        {0x020e04d8, 0x00000030},
        {0x020e0760, 0x00020000},
        {0x020e0764, 0x00000030},
        {0x020e0770, 0x00000030},
        {0x020e0778, 0x00000030},
        {0x020e077c, 0x00000030},
        {0x020e0780, 0x00000030},
        {0x020e0784, 0x00000030},
        {0x020e078c, 0x00000030},
        {0x020e0748, 0x00000030},
        {0x020e0470, 0x00000030},
        {0x020e0474, 0x00000030},
        {0x020e0478, 0x00000030},
        {0x020e047c, 0x00000030},
        {0x020e0480, 0x00000030},
        {0x020e0484, 0x00000030},
        {0x020e0488, 0x00000030},
        {0x020e048c, 0x00000030},
        {0x021b0800, 0xa1390003},
        {0x021b080c, 0x004E004E},
        {0x021b0810, 0x0042004A},
        {0x021b480c, 0x002D0030},
        {0x021b4810, 0x002C0045},
        {0x021b083c, 0x42460244},
        {0x021b0840, 0x02300230},
        {0x021b483c, 0x422C0238},
        {0x021b4840, 0x021E0222},
        {0x021b0848, 0x44464848},
        {0x021b4848, 0x42484842},
        {0x021b0850, 0x342E2A32},
        {0x021b4850, 0x362E322A},
        {0x021b081c, 0x33333333},
        {0x021b0820, 0x33333333},
        {0x021b0824, 0x33333333},
        {0x021b0828, 0x33333333},
        {0x021b481c, 0x33333333},
        {0x021b4820, 0x33333333},
        {0x021b4824, 0x33333333},
        {0x021b4828, 0x33333333},
        {0x021b08b8, 0x00000800},
        {0x021b48b8, 0x00000800},
        {0x021b0004, 0x0002002D},
        {0x021b0008, 0x00333030},
        {0x021b000c, 0x3F435313},
        {0x021b0010, 0xB66E8B63},
        {0x021b0014, 0x01FF00DB},
        {0x021b0018, 0x00011740},
        {0x021b001c, 0x00008000},
        {0x021b002c, 0x000026d2},
        {0x021b0030, 0x00431023},
        {0x021b0040, 0x00000027},
        {0x021b0000, 0x831A0000},
/*
        {0x021b001c, 0x04008032},
        {0x021b001c, 0x00008033},
        {0x021b001c, 0x00048031},
        {0x021b001c, 0x05208030},
*/
        {0x021b0020, 0x00005800},
        {0x021b0818, 0x00011117},
        {0x021b4818, 0x00011117},
        {0x021b0004, 0x0002556D},
        {0x021b0404, 0x00011006},
        {0x021b001c, 0x00000000},
        {0x020c4068, 0x00C03F3F},
        {0x020c406c, 0x0030FC03},
        {0x020c4070, 0x0FFFC000},
        {0x020c4074, 0x3FF00000},
        {0x020c4078, 0x00FFF300},
        {0x020c407c, 0x0F0000C3},
        {0x020c4080, 0x000003FF},
        {0x020e0010, 0xF00000CF},
        {0x020e0018, 0x007F007F},
        {0x020e001c, 0x007F007F},

#elif defined(CONFIG_MX6UL)

	{0x020c4068, 0xffffffff},
	{0x020c406c, 0xffffffff},
	{0x020c4070, 0xffffffff},
	{0x020c4074, 0xffffffff},
	{0x020c4078, 0xffffffff},
	{0x020c407c, 0xffffffff},
	{0x020c4080, 0xffffffff},
	{0x020c4084, 0xffffffff},
	{0x020E04B4, 0x000C0000},
	{0x020E04AC, 0x00000000},
	{0x020E027C, 0x00000008},
	{0x020E0250, 0x00000030},
	{0x020E024C, 0x00000030},
	{0x020E0490, 0x00000030},
	{0x020E0288, 0x00000030},
	{0x020E0270, 0x00000000},
	{0x020E0260, 0x00000030},
	{0x020E0264, 0x00000030},
	{0x020E04A0, 0x00000030},
	{0x020E0494, 0x00020000},
	{0x020E0280, 0x00000038},
	{0x020E0284, 0x00000030},
	{0x020E04B0, 0x00020000},
	{0x020E0498, 0x00000030},
	{0x020E04A4, 0x00000030},
	{0x020E0244, 0x00000030},
	{0x020E0248, 0x00000030},
	{0x021B001C, 0x00008000},
	{0x021B0800, 0xA1390003},
	{0x021B080C, 0x00090000},
	{0x021B083C, 0x41540154},
	{0x021B0848, 0x40404442},
	{0x021B0850, 0x40405450},
	{0x021B081C, 0x33333333},
	{0x021B0820, 0x33333333},
	{0x021B082C, 0xf3333333},
	{0x021B0830, 0xf3333333},
	{0x021B08C0, 0x00922012},
	{0x021B0858, 0x00000F00},
	{0x021B08b8, 0x00000800},
	{0x021B0004, 0x0002002D},
	{0x021B0008, 0x1B333000},

	{0x021B000C, 0x676B54F3},
	{0x021B0010, 0xB68E0A83},
	{0x021B0014, 0x01FF00DB},
	{0x021B0018, 0x00211740},
	{0x021B001C, 0x00008000},
	{0x021B002C, 0x000026D2},
	{0x021B0030, 0x006B1023},
	{0x021B0040, 0x0000004F},
	{0x021B0000, 0x84180000},
// ------> NOK
/*	{0x021B001C, 0x02008032},
	{0x021B001C, 0x00008033},
	{0x021B001C, 0x00048031},
	{0x021B001C, 0x15208030},
	{0x021B001C, 0x04008040},*/
// <----- NOK
	{0x021B0020, 0x00000800},
	{0x021B0818, 0x00000227},
	{0x021B0004, 0x0002552D},
	{0x021B0404, 0x00011006},
	{0x021B001C, 0x00000000},

#elif defined(CONFIG_MX7D) && defined(CONFIG_TARGET_MX7DEA_UCOM)
        {0x30340004, 0x4F400005},
        {0x30391000, 0x00000002},
        {0x307a0000, 0x01040008},
        {0x307A0064, 0x00200038},
        {0x307a0490, 0x00000001},
        {0x307A00D0, 0x00350001},
        {0x307A00DC, 0x00C3000A},
        {0x307A00E0, 0x00010000},
        {0x307A00E4, 0x00110006},
        {0x307A00F4, 0x0000033F},
        {0x307A0100, 0x0A0E110B},
        {0x307A0104, 0x00020211},
        {0x307A0108, 0x03060708},
        {0x307A010C, 0x00A0500C},
        {0x307A0110, 0x05020307},
        {0x307A0114, 0x02020404},
        {0x307A0118, 0x02020003},
        {0x307A011C, 0x00000202},
        {0x307A0120, 0x00000202},
        {0x307A0180, 0x00600018},
        {0x307A0184, 0x00E00100},
        {0x307A0190, 0x02098205},
        {0x307A0194, 0x00060303},
        {0x307A01A0, 0x80400003},
        {0x307A01A4, 0x00100020},
        {0x307A01A8, 0x80100004},
        {0x307A0200, 0x00000016},
        {0x307A0204, 0x00171717},
        {0x307A0210, 0x00000F0F},
        {0x307A0214, 0x04040404},
        {0x307A0218, 0x0F040404},
        {0x307A0240, 0x06000600},
        {0x307A0244, 0x00000000},
        {0x30391000, 0x00000000},
        {0x30790000, 0x17421e40},
        {0x30790004, 0x10210100},
        {0x30790008, 0x00010000},
        {0x30790010, 0x0007080C},
        {0x307900b0, 0x1010007e},
        {0x3079001C, 0x01010000},
        {0x3079009c, 0x00000b24},
        {0x30790020, 0x0A0A0A0A},
        {0x30790030, 0x06060606},
        {0x30790050, 0x01000008},
        {0x30790050, 0x00000008},
        {0x30790018, 0x0000000F},
        {0x307900c0, 0x0C487304},
        {0x307900c0, 0x0C4C7304},
        {0x307900c0, 0x0C4C7306},
        {0x307900C0, 0x0C4C7304},
        {0x30384130, 0x00000000},
        {0x30340020, 0x00000178},
        {0x30384130, 0x00000002},

#elif defined(CONFIG_MX7D) && defined(CONFIG_TARGET_MX7DEA_COM)

	{0x30340004, 0x4F400005},
	{0x30391000, 0x00000002},
	{0x307a0000, 0x01040001},
	{0x307a01a0, 0x80400003},
	{0x307a01a4, 0x00100020},
	{0x307a01a8, 0x80100004},
	{0x307a0064, 0x0040005e},
	{0x307a0490, 0x00000001},
	{0x307a00d0, 0x00020001},
	{0x307a00d4, 0x00010000},
	{0x307a00dc, 0x09300004},
	{0x307a00e0, 0x04080000},
	{0x307a00e4, 0x00090004},
	{0x307a00f4, 0x0000033f},
	{0x307a0100, 0x0908120a},
	{0x307a0104, 0x0002020e},
	{0x307a0108, 0x03040407},
	{0x307a010c, 0x00002006},
	{0x307a0110, 0x04020204},
	{0x307a0114, 0x03030202},
	{0x307a0120, 0x03030803},
	{0x307a0180, 0x00800020},
	{0x307a0190, 0x02098204},
	{0x307a0194, 0x00030303},
	{0x307a0200, 0x00000016},
	{0x307a0204, 0x00171717},
	{0x307a0214, 0x04040404},
	{0x307a0218, 0x00040404},
	{0x307a0240, 0x06000601},
	{0x307a0244, 0x00001323},
	{0x30391000, 0x00000000},
	{0x30790000, 0x17420f40},
	{0x30790004, 0x10210100},
	{0x30790010, 0x00060807},
	{0x307900b0, 0x1010007e},
	{0x3079009c, 0x00000d6e},
	{0x30790020, 0x08080808},
	{0x30790030, 0x08080808},
	{0x30790050, 0x01000010},
	{0x30790050, 0x00000010},
	{0x307900c0, 0x0e407304},
	{0x307900c0, 0x0e447304},
	{0x307900c0, 0x0e447306},
	{0x307900c0, 0x0e447304},
	{0x307900c0, 0x0e407304},
	{0x30384130, 0x00000000},
	{0x30340020, 0x00000178},
	{0x30384130, 0x00000002},
	{0x30790018, 0x0000000f},

#elif defined(CONFIG_TARGET_MX8MQEA_COM)
	// TODO
#else

#error "Unknown SOC"

#endif
};

#endif


#ifdef CONFIG_DM_I2C
static int ea_dm_i2c_init(struct udevice **i2c_dev)
{
	struct udevice *bus;
        int ret;

        ret = uclass_get_device_by_seq(UCLASS_I2C, EA_EEPROM_I2C_BUS, &bus);
        if (ret) {
                printf("%s: Can't find bus\n", __func__);
                return -EINVAL;
        }

        ret = dm_i2c_probe(bus, EA_EEPROM_I2C_SLAVE, 0, i2c_dev);
        if (ret) {
                printf("%s: Can't find device id=0x%x\n",
                        __func__, EA_EEPROM_I2C_SLAVE);
                return -ENODEV;
        }

	return i2c_set_chip_offset_len(*i2c_dev, 2);

}
#endif


int ea_eeprom_init(void)
{
#if !defined(CONFIG_DM_I2C)
	i2c_set_bus_num(EA_EEPROM_I2C_BUS);
	i2c_init(CONFIG_SYS_I2C_SPEED, EA_EEPROM_I2C_SLAVE);
#endif

	return 0;
}

int ea_eeprom_get_config(ea_eeprom_config_t* config)
{
#if !defined(CONFIG_DM_I2C)

	i2c_set_bus_num(EA_EEPROM_I2C_BUS);

	if (i2c_probe(EA_EEPROM_I2C_SLAVE)) {
		return -ENODEV;
	}

	if (i2c_read(EA_EEPROM_I2C_SLAVE,
		0,
		2,
		(uint8_t *)config,
		sizeof(ea_eeprom_config_t)))
	{
		return -EIO;
	}
#else
	struct udevice *i2c_dev = NULL;
	int ret;

	ret = ea_dm_i2c_init(&i2c_dev);
	if (ret) {
		return ret;
	}

        ret = dm_i2c_read(i2c_dev, 0, (uint8_t *)config, sizeof(ea_eeprom_config_t));
        if (ret) {
                printf("%s dm_i2c_read failed, err %d\n", __func__, ret);
                return -EIO;
        }

#endif

	if (config->magic != EA_EEPROM_MAGIC) {
		return -EINVAL;
	}

	return 0;
}

#if !(defined(CONFIG_TARGET_MX7DEA_COM) || defined(CONFIG_TARGET_MX7DEA_UCOM))
static int intern_dram_init(void)
{
	ea_eeprom_config_t config = {0};
	int toRead = 0;
	int haveRead = 0;
	int i, ret;
	struct _ea_ddr_cfg ddr_list_buf[EA_DDR_LIST_BUF_SZ];

#ifdef CONFIG_DM_I2C
	struct udevice *i2c_dev = NULL;

        ret = ea_dm_i2c_init(&i2c_dev);
        if (ret) {
                return ret;
        }

#endif

	ret = ea_eeprom_get_config(&config);
	if (ret) {
		return ret;
	}

	do {
#if !defined(CONFIG_DM_I2C)
		/*
		 * Have seen issues with i2c access after some  register
		 * updates/accesses (eg.g for iMX6 Quad). Re-initializing
		 * i2c just in case.
		 */
		i2c_set_bus_num(EA_EEPROM_I2C_BUS);
	        i2c_init(CONFIG_SYS_I2C_SPEED, EA_EEPROM_I2C_SLAVE);
#endif

		toRead = config.num_reg_value_pairs;
		if (toRead > EA_DDR_LIST_BUF_SZ)
			toRead = EA_DDR_LIST_BUF_SZ;

#if !defined(CONFIG_DM_I2C)
		if (i2c_read(EA_EEPROM_I2C_SLAVE,
			sizeof(ea_eeprom_config_t)+haveRead*sizeof(struct _ea_ddr_cfg),
			2,
			(uint8_t *)ddr_list_buf,
			toRead*sizeof(struct _ea_ddr_cfg)))
		{
			return -EIO;
		}
#else
		ret = dm_i2c_read(i2c_dev,
			sizeof(ea_eeprom_config_t)+haveRead*sizeof(struct _ea_ddr_cfg),
			(uint8_t *)ddr_list_buf,
			toRead*sizeof(struct _ea_ddr_cfg));
		if (ret) {
			printf("%s dm_i2c_read failed, err %d\n", __func__, ret);
			return -EIO;
		}
#endif
		config.num_reg_value_pairs -= toRead;
		haveRead += toRead;
		for (i = 0; i < toRead; i++) {
			writel(ddr_list_buf[i].val, (unsigned long)ddr_list_buf[i].addr);
		}



	} while(config.num_reg_value_pairs > 0);

	return 0;
}

int ea_eeprom_dram_init(void)
{
	int i = 0;

	if (intern_dram_init() != 0) {
		// try with default values if we failed with eeprom data
		for(i = 0; i < sizeof(ddr_init_default)/sizeof(struct _ea_ddr_cfg); i++)
		{
			writel(ddr_init_default[i].val, (unsigned long)ddr_init_default[i].addr);
		}
	}

	return 0;
}
#endif


int ea_eeprom_ddr_cfg_init(ea_ddr_cfg_t *cfg)
{
	ea_eeprom_config_t config;
	int ret = 0;

	ea_eeprom_init();
	ret = ea_eeprom_get_config(&config);
	if (!ret) {
		cfg->num_pairs = config.num_reg_value_pairs;
		cfg->next = 0;
		cfg->ddr_size_mb = config.ddr_size;
	}

	return ret;
}

int ea_eeprom_ddr_cfg_read(ea_ddr_cfg_t *cfg, ea_ddr_cfg_pair_t* pairs,
	int num, int *num_read)
{
	int to_read;

#ifdef CONFIG_DM_I2C
	int ret;
	struct udevice *i2c_dev = NULL;

        ret = ea_dm_i2c_init(&i2c_dev);
        if (ret) {
                return ret;
        }

#endif

	*num_read = 0;

	/* max to read */
	to_read = cfg->num_pairs - cfg->next;

	/* no more to read */
	if (to_read <= 0) return 0;

	/* fewer requested */
	if (num < to_read) to_read = num;


#if !defined(CONFIG_DM_I2C)
	if (i2c_read(EA_EEPROM_I2C_SLAVE,
		sizeof(ea_eeprom_config_t)+cfg->next*sizeof(ea_ddr_cfg_pair_t),
		2,
		(uint8_t *)pairs,
		to_read*sizeof(ea_ddr_cfg_pair_t)))
	{
		return -EIO;
	}
#else
	ret = dm_i2c_read(i2c_dev,
		sizeof(ea_eeprom_config_t)+cfg->next*sizeof(ea_ddr_cfg_pair_t),
		(uint8_t *)pairs,
		to_read*sizeof(ea_ddr_cfg_pair_t));
	if (ret) {
		printf("%s dm_i2c_read failed, err %d\n", __func__, ret);
		return -EIO;
	}
#endif

	*num_read = to_read;
	cfg->next += to_read;

	return 0;
}
