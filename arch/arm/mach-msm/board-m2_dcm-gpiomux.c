/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <asm/mach-types.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>
#include "devices.h"
#include "board-8960.h"
#include <mach/msm8960-gpio.h>
#include <asm/system_info.h>

/* The SPI configurations apply to GSBI 1*/
static struct gpiomux_setting spi_active = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting spi_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting spi_active_config2 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting spi_suspended_config2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting gsbi3_suspended_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gsbi1 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi3_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi5 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi7 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi10 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi12 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting cdc_mclk = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting nc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting audio_auxpcm[] = {
	/* Suspended state */
	{
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	},
	/* Active state */
	{
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	},
};

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct gpiomux_setting gpio_eth_config = {
	.pull = GPIOMUX_PULL_NONE,
	.drv = GPIOMUX_DRV_8MA,
	.func = GPIOMUX_FUNC_GPIO,
};
#endif

static struct gpiomux_setting slimbus = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

static struct gpiomux_setting volkey = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
static struct gpiomux_setting sdc4_suspend_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc4_suspend2_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc4_active_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv  = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_UP,
};
#endif

#ifdef CONFIG_USB_EHCI_MSM_HSIC
static struct gpiomux_setting hsic_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting hsic_hub_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

static struct gpiomux_setting hap_lvl_shft_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hap_lvl_shft_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ap2mdm_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_status_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_errfatal_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting ap2mdm_kpdpwr_n_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdp_vsync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
static struct gpiomux_setting hdmi_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hdmi_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hdmi_active_2_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hdmi_active_3_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting hdmi_active_4_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_HIGH,
};
#endif

#ifdef CONFIG_USB_SWITCH_FSA9485
static struct gpiomux_setting fsa9485_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting fsa9485_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm8960_fsa9485_configs[] __initdata = {
	{
		.gpio = 14,
		.settings = {
			[GPIOMUX_ACTIVE]	= &fsa9485_active_cfg,
			[GPIOMUX_SUSPENDED] = &fsa9485_suspend_cfg,
		},
	},

	{
		.gpio = 73,
		.settings = {
			[GPIOMUX_ACTIVE]	 = &fsa9485_active_cfg,
			[GPIOMUX_SUSPENDED] = &fsa9485_suspend_cfg,
		},
	},

	{
		.gpio = 74,
		.settings = {
			[GPIOMUX_ACTIVE]	= &fsa9485_active_cfg,
			[GPIOMUX_SUSPENDED] = &fsa9485_suspend_cfg,
		},
	},
};
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct msm_gpiomux_config msm8960_ethernet_configs[] = {
	{
		.gpio = 90,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
	{
		.gpio = 89,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
};
#endif

static struct msm_gpiomux_config msm8960_gsbi_configs[] __initdata = {
	{
	.gpio = 6,			/* FPGA_SPI_DI == NC */
	.settings = {
		[GPIOMUX_SUSPENDED] = &nc_cfg,
		[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
	.gpio = 7,			/* GSBI1 QUP SPI_DATA_MISO */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config,
		[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
	.gpio = 8,			/* FPGA_SPI_EN == NC */
	.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
	.gpio = 9,			/* FPGA_SPI_CLK == NC */
	.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
			[GPIOMUX_ACTIVE] = &nc_cfg,
		},
	},
	{
	.gpio = 14,			/* GSBI1 SPI_CS_1 */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config2,
		[GPIOMUX_ACTIVE] = &spi_active_config2,
		},
	},
	{
	.gpio = 16,			/* GSBI3 I2C QUP SDA */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
		[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
	.gpio = 17,			/* GSBI3 I2C QUP SCL */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
		[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
	.gpio = 22,			/* GSBI5 UART2 */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi5,
		},
	},
	{
	.gpio = 23,			/* GSBI5 UART2 */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi5,
		},
	},
	{
	.gpio = 24,			/* GSBI5 UART2 */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi5,
		},
	},
	{
	.gpio = 25,			/* GSBI5 UART2 */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi5,
		},
	},
#ifdef CONFIG_NFC_PN544
	{
	.gpio = 32,			/* GSBI7 I2C QUP SDA */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi7,
		},
	},
	{
	.gpio = 33,			/* GSBI7 I2C QUP SCL */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi7,
		},
	},
#endif
#ifdef CONFIG_S5C73M3
	{
	.gpio = GPIO_CAM_SPI_MOSI,	/* GSBI11 QUP SPI_DATA_MOSI */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config,
		[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
	.gpio = GPIO_CAM_SPI_MISO,	/* GSBI11 QUP SPI_DATA_MISO */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config,
		[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
	.gpio = GPIO_CAM_SPI_SSN,	/* GSBI11 QUP SPI_CS_N */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config,
		[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
	.gpio = GPIO_CAM_SPI_SCLK,	/* GSBI11 QUP SPI_CLK */
	.settings = {
		[GPIOMUX_SUSPENDED] = &spi_suspended_config,
		[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
#endif
	{
	.gpio = 44,			/* GSBI12 I2C QUP SDA */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi12,
		},
	},
	{
	.gpio = 45,			/* GSBI12 I2C QUP SCL */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi12,
		},
	},
	{
	.gpio = 73,			/* GSBI10 I2C QUP SDA */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
	{
	.gpio = 74,			/* GSBI10 I2C QUP SCL */
	.settings = {
		[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
};

static struct msm_gpiomux_config msm8960_slimbus_config[] __initdata = {
	{
	.gpio = 60,			/* slimbus data */
	.settings = {
		[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
	{
	.gpio = 61,			/* slimbus clk */
	.settings = {
		[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
};

static struct msm_gpiomux_config msm8960_audio_codec_configs[] __initdata = {
	{
	.gpio = 59,
	.settings = {
		[GPIOMUX_SUSPENDED] = &cdc_mclk,
		},
	},
};

static struct msm_gpiomux_config msm8960_audio_auxpcm_configs[] __initdata = {
	{
	.gpio = 63,
	.settings = {
		[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
		[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
	.gpio = 64,
	.settings = {
		[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
		[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
	.gpio = 65,
	.settings = {
		[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
		[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
	.gpio = 66,
	.settings = {
		[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
		[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
};

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
	.gpio = 84,
	.settings = {
		[GPIOMUX_ACTIVE] = &wcnss_5wire_active_cfg,
		[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
	.gpio = 85,
	.settings = {
		[GPIOMUX_ACTIVE] = &wcnss_5wire_active_cfg,
		[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
	.gpio = 86,
	.settings = {
		[GPIOMUX_ACTIVE] = &wcnss_5wire_active_cfg,
		[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
	.gpio = 87,
	.settings = {
		[GPIOMUX_ACTIVE] = &wcnss_5wire_active_cfg,
		[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
	.gpio = 88,
	.settings = {
		[GPIOMUX_ACTIVE] = &wcnss_5wire_active_cfg,
		[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
static struct msm_gpiomux_config sdc4_interface[] = {
	{
		.gpio = 83,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
	{
		.gpio = 84,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
	{
		.gpio = 85,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
	{
		.gpio = 86,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
	{
		.gpio = 87,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
	{
		.gpio = 88,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_active_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend2_cfg,
		},
	},
};
#endif

#ifdef CONFIG_USB_EHCI_MSM_HSIC
static struct msm_gpiomux_config msm8960_hsic_configs[] = {
	{
		.gpio = 150,               /*HSIC_STROBE */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 151,               /* HSIC_DATA */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 91,               /* HSIC_HUB_RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};
#endif

static struct msm_gpiomux_config hap_lvl_shft_config[] __initdata = {
	{
		.gpio = 47,
		.settings = {
			[GPIOMUX_SUSPENDED] = &hap_lvl_shft_suspended_config,
			[GPIOMUX_ACTIVE] = &hap_lvl_shft_active_config,
		},
	},
};

static struct msm_gpiomux_config mdm_configs[] __initdata = {
	/* AP2MDM_STATUS */
	{
		.gpio = 94,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_STATUS */
	{
		.gpio = 69,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_status_cfg,
		}
	},
	/* MDM2AP_ERRFATAL */
	{
		.gpio = 70,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_errfatal_cfg,
		}
	},
	/* AP2MDM_ERRFATAL */
	{
		.gpio = 95,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* AP2MDM_KPDPWR_N */
	{
		.gpio = 81,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	},
	/* AP2MDM_PMIC_RESET_N */
	{
		.gpio = 80,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	}
};

static struct msm_gpiomux_config msm8960_mdp_vsync_configs[] __initdata = {
	{
		.gpio = 0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdp_vsync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdp_vsync_suspend_cfg,
		},
	}
};

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
static struct msm_gpiomux_config msm8960_hdmi_configs[] __initdata = {
	{
		.gpio = 99,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 101,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 102,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
	{
		.gpio = 15,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
};
#endif

#ifdef CONFIG_I2C

#define MSM_8960_GSBI3_QUP_I2C_BUS_ID 3
#define MSM_8960_GSBI10_QUP_I2C_BUS_ID 10

#endif

static struct gpiomux_setting sec_ts_ldo_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sec_ts_ldo_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm8960_sec_ts_configs[] = {
	{	/* TS LDO EN */
		.gpio = 10,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sec_ts_ldo_act_cfg,
			[GPIOMUX_SUSPENDED] = &sec_ts_ldo_sus_cfg,
		},
	},
};


static struct gpiomux_setting sec_prox_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sec_prox_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config msm8960_sec_sensor_configs[] = {
	{	/* PS INTERRUPT */
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sec_prox_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &sec_prox_int_sus_cfg,
		},
	},
};

#ifdef CONFIG_FELICA
static struct gpiomux_setting felica_i2c_sda_setting = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting felica_i2c_scl_setting = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting felica_uart_tx_setting = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting felica_uart_rx_setting = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting felica_pon_setting = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting felica_rfs_setting = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting felica_int_setting = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm8960_felica_configs[] __initdata = {
	{
		.gpio = GPIO_FELICA_I2C_SDA,/*I2C_SDA*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_i2c_sda_setting,
			[GPIOMUX_SUSPENDED] = &felica_i2c_sda_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_I2C_SCL,/*I2C_SCL*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_i2c_scl_setting,
			[GPIOMUX_SUSPENDED] = &felica_i2c_scl_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_UART_TX,/*2-pin UART_TX*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_uart_tx_setting,
			[GPIOMUX_SUSPENDED] = &felica_uart_tx_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_UART_RX,/*2-pin UART_RX*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_uart_rx_setting,
			[GPIOMUX_SUSPENDED] = &felica_uart_rx_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_RFS,/*RFS*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_rfs_setting,
			[GPIOMUX_SUSPENDED] = &felica_rfs_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_PON,/*PON*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_pon_setting,
			[GPIOMUX_SUSPENDED] = &felica_pon_setting,
		},
	},
	{
		.gpio = GPIO_FELICA_INT,/*INT*/
		.settings = {
			[GPIOMUX_ACTIVE]    = &felica_int_setting,
			[GPIOMUX_SUSPENDED] = &felica_int_setting,
		},
	},

};
#endif /* CONFIG_FELICA */
int __init msm8960_init_gpiomux(void)
{
	int rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err(KERN_ERR "msm_gpiomux_init failed %d\n", rc);
		return rc;
	}

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
	msm_gpiomux_install(msm8960_ethernet_configs,
			ARRAY_SIZE(msm8960_ethernet_configs));
#endif

	msm_gpiomux_install(msm8960_gsbi_configs,
			ARRAY_SIZE(msm8960_gsbi_configs));

	msm_gpiomux_install(msm8960_sec_ts_configs,
			ARRAY_SIZE(msm8960_sec_ts_configs));

	msm_gpiomux_install(msm8960_slimbus_config,
			ARRAY_SIZE(msm8960_slimbus_config));

	msm_gpiomux_install(msm8960_sec_sensor_configs,
			ARRAY_SIZE(msm8960_sec_sensor_configs));

	msm_gpiomux_install(msm8960_audio_codec_configs,
			ARRAY_SIZE(msm8960_audio_codec_configs));

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
	if (system_rev >= 0x1)
		msm_gpiomux_install(sdc4_interface, ARRAY_SIZE(sdc4_interface));
	else
#endif
		msm_gpiomux_install(wcnss_5wire_interface,
				ARRAY_SIZE(wcnss_5wire_interface));
#ifdef CONFIG_USB_SWITCH_FSA9485
		msm_gpiomux_install(msm8960_fsa9485_configs,
				ARRAY_SIZE(msm8960_fsa9485_configs));
#endif

	if (machine_is_msm8960_mtp() || machine_is_msm8960_fluid() ||
		machine_is_msm8960_liquid() || machine_is_msm8960_cdp())
		msm_gpiomux_install(hap_lvl_shft_config,
			ARRAY_SIZE(hap_lvl_shft_config));

	if (PLATFORM_IS_CHARM25())
		msm_gpiomux_install(mdm_configs,
			ARRAY_SIZE(mdm_configs));

#ifdef CONFIG_USB_EHCI_MSM_HSIC
	if ((SOCINFO_VERSION_MAJOR(socinfo_get_version()) != 1) &&
		(PLATFORM_IS_CHARM25() || machine_is_msm8960_liquid()))
		msm_gpiomux_install(msm8960_hsic_configs,
			ARRAY_SIZE(msm8960_hsic_configs));
#endif

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
	msm_gpiomux_install(msm8960_hdmi_configs,
			ARRAY_SIZE(msm8960_hdmi_configs));
#endif

	msm_gpiomux_install(msm8960_mdp_vsync_configs,
			ARRAY_SIZE(msm8960_mdp_vsync_configs));

#ifdef CONFIG_FELICA
	msm_gpiomux_install(msm8960_felica_configs,
			ARRAY_SIZE(msm8960_felica_configs));
#endif /* CONFIG_FELICA */
	return 0;
}
