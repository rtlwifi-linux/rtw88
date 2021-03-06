/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2018  Realtek Corporation.
 */

#ifndef __RTW8822C_H__
#define __RTW8822C_H__

#include <asm/byteorder.h>

struct rtw8822cu_efuse {
	u8 res4[4];			/* 0xd0 */
	u8 usb_optional_function;
	u8 res5[0x1e];
	u8 res6[2];
	u8 serial[0x0b];		/* 0xf5 */
	u8 vid;				/* 0x100 */
	u8 res7;
	u8 pid;
	u8 res8[4];
	u8 mac_addr[ETH_ALEN];		/* 0x107 */
	u8 res9[2];
	u8 vendor_name[0x07];
	u8 res10[2];
	u8 device_name[0x14];
	u8 res11[0xcf];
	u8 package_type;		/* 0x1fb */
	u8 res12[0x4];
};

struct rtw8822ce_efuse {
	u8 mac_addr[ETH_ALEN];		/* 0xd0 */
	u8 vender_id[2];
	u8 device_id[2];
	u8 sub_vender_id[2];
	u8 sub_device_id[2];
	u8 pmc[2];
	u8 exp_device_cap[2];
	u8 msi_cap;
	u8 ltr_cap;			/* 0xe3 */
	u8 exp_link_control[2];
	u8 link_cap[4];
	u8 link_control[2];
	u8 serial_number[8];
	u8 res0:2;			/* 0xf4 */
	u8 ltr_en:1;
	u8 res1:2;
	u8 obff:2;
	u8 res2:3;
	u8 obff_cap:2;
	u8 res3:4;
	u8 res4[3];
	u8 class_code[3];
	u8 pci_pm_L1_2_supp:1;
	u8 pci_pm_L1_1_supp:1;
	u8 aspm_pm_L1_2_supp:1;
	u8 aspm_pm_L1_1_supp:1;
	u8 L1_pm_substates_supp:1;
	u8 res5:3;
	u8 port_common_mode_restore_time;
	u8 port_t_power_on_scale:2;
	u8 res6:1;
	u8 port_t_power_on_value:5;
	u8 res7;
};

struct rtw8822c_efuse {
	__le16 rtl_id;
	u8 res0[0x0e];

	/* power index for four RF paths */
	struct rtw_txpwr_idx txpwr_idx_table[4];

	u8 channel_plan;		/* 0xb8 */
	u8 xtal_k;
	u8 thermal_meter;
	u8 iqk_lck;
	u8 pa_type;			/* 0xbc */
	u8 lna_type_2g[2];		/* 0xbd */
	u8 lna_type_5g[2];
	u8 rf_board_option;
	u8 rf_feature_option;
	u8 rf_bt_setting;
	u8 eeprom_version;
	u8 eeprom_customer_id;
	u8 tx_bb_swing_setting_2g;
	u8 tx_bb_swing_setting_5g;
	u8 tx_pwr_calibrate_rate;
	u8 rf_antenna_option;		/* 0xc9 */
	u8 rfe_option;
	u8 country_code[2];
	u8 res[3];
	union {
		struct rtw8822cu_efuse u;
		struct rtw8822ce_efuse e;
	};
};

/* phy status page0 */
#define GET_PHY_STAT_P0_PWDB_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P0_PWDB_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(7, 0))
#define GET_PHY_STAT_P0_GAIN_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(21, 16))
#define GET_PHY_STAT_P0_GAIN_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(29, 24))

/* phy status page1 */
#define GET_PHY_STAT_P1_PWDB_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P1_PWDB_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(23, 16))
#define GET_PHY_STAT_P1_L_RXSC(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x01), GENMASK(11, 8))
#define GET_PHY_STAT_P1_HT_RXSC(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x01), GENMASK(15, 12))

#define REG_ANAPARLDO_POW_MAC	0x0029
#define BIT_LDOE25_PON		BIT(0)

#define REG_DFIRBW	0x810
#define REG_ANTMAP0	0x820
#define REG_ANTMAP	0x824
#define REG_DYMPRITH	0x86c
#define REG_DYMENTH0	0x870
#define REG_DYMENTH	0x874
#define REG_DYMTHMIN	0x8a4
#define REG_TXBWCTL	0x9b0
#define REG_TXCLK	0x9b4
#define REG_SCOTRK	0xc30
#define REG_MRCM	0xc38
#define REG_AGCSWSH	0xc44
#define REG_ANTWTPD	0xc54
#define REG_ORITXCODE	0x1800
#define REG_3WIRE	0x180c
#define BIT_3WIRE_TX_EN		BIT(0)
#define BIT_3WIRE_RX_EN		BIT(1)
#define BIT_3WIRE_PI_ON		BIT(28)
#define REG_RXAGCCTL0	0x18ac
#define REG_CCKSB	0x1a00
#define REG_RXCCKSEL	0x1a04
#define REG_PSFGC2	0x1a24
#define REG_PSFGC6	0x1a28
#define REG_CCANRX	0x1a2c
#define BIT_CCK_FA_RST		(BIT(14) | BIT(15))
#define BIT_OFDM_FA_RST		(BIT(12) | BIT(13))
#define REG_CCK_FACNT	0x1a5c
#define REG_CCKTXONLY	0x1a80
#define BIT_BB_CCK_CHECK_EN	BIT(18)
#define REG_PSFGC	0x1aac
#define REG_PCCAWT	0x1ac0
#define REG_TXANT	0x1c28
#define REG_ENCCK	0x1c3c
#define BIT_CCK_BLK_EN		BIT(1)
#define BIT_CCK_OFDM_BLK_EN	(BIT(0) | BIT(1))
#define REG_CCAMSK	0x1c80
#define REG_RXFNCTL	0x1d30
#define REG_RXIGI	0x1d70
#define REG_ENFN	0x1e24
#define REG_TXANTSEG	0x1e28
#define REG_TXLGMAP	0x1e2c
#define REG_CCKPATH	0x1e5c
#define REG_CNT_CTRL	0x1eb4
#define BIT_ALL_CNT_RST		BIT(25)
#define REG_OFDM_FACNT	0x2d00
#define REG_OFDM_TXCNT	0x2de0
#define REG_ORITXCODE2	0x4100
#define REG_3WIRE2	0x410c
#define REG_RXAGCCTL	0x41ac

#endif
