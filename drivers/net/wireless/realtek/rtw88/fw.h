/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2018  Realtek Corporation.
 */

#ifndef __RTW_FW_H_
#define __RTW_FW_H_

#define H2C_PKT_SIZE		32
#define H2C_PKT_HDR_SIZE	8

/* FW bin information */
#define FW_HDR_SIZE			64
#define FW_HDR_CHKSUM_SIZE		8
#define FW_HDR_VERSION			4
#define FW_HDR_SUBVERSION		6
#define FW_HDR_SUBINDEX			7
#define FW_HDR_MONTH			16
#define FW_HDR_DATE			17
#define FW_HDR_HOUR			18
#define FW_HDR_MIN			19
#define FW_HDR_YEAR			20
#define FW_HDR_MEM_USAGE		24
#define FW_HDR_H2C_FMT_VER		28
#define FW_HDR_DMEM_ADDR		32
#define FW_HDR_DMEM_SIZE		36
#define FW_HDR_IMEM_SIZE		48
#define FW_HDR_EMEM_SIZE		52
#define FW_HDR_EMEM_ADDR		56
#define FW_HDR_IMEM_ADDR		60

#define FIFO_PAGE_SIZE_SHIFT		12
#define FIFO_PAGE_SIZE			4096
#define RSVD_PAGE_START_ADDR		0x780
#define FIFO_DUMP_ADDR			0x8000

enum rtw_c2h_cmd_id {
	C2H_BT_INFO = 0x09,
	C2H_HW_FEATURE_REPORT = 0x19,
	C2H_HW_FEATURE_DUMP = 0xfd,
	C2H_HALMAC = 0xff,
};

struct rtw_c2h_cmd {
	u8 id;
	u8 seq;
	u8 payload[0];
} __packed;

enum rtw_rsvd_packet_type {
	RSVD_BEACON,
	RSVD_PS_POLL,
	RSVD_PROBE_RESP,
	RSVD_NULL,
	RSVD_QOS_NULL,
};

enum rtw_fw_rf_type {
	FW_RF_1T2R = 0,
	FW_RF_2T4R = 1,
	FW_RF_2T2R = 2,
	FW_RF_2T3R = 3,
	FW_RF_1T1R = 4,
	FW_RF_2T2R_GREEN = 5,
	FW_RF_3T3R = 6,
	FW_RF_3T4R = 7,
	FW_RF_4T4R = 8,
	FW_RF_MAX_TYPE = 0xF,
};

struct rtw_general_info {
	u8 rfe_type;
	u8 rf_type;
	u8 tx_ant_status;
	u8 rx_ant_status;
};

struct rtw_iqk_para {
	u8 clear;
	u8 segment_iqk;
};

struct rtw_rsvd_page {
	struct list_head list;
	struct sk_buff *skb;
	enum rtw_rsvd_packet_type type;
	u8 page;
	bool add_txdesc;
};

/* PKT H2C */
#define H2C_PKT_CMD_ID 0xFF
#define H2C_PKT_CATEGORY 0x01

#define H2C_PKT_GENERAL_INFO 0x0D
#define H2C_PKT_PHYDM_INFO 0x11
#define H2C_PKT_IQK 0x0E

#define SET_PKT_H2C_CATEGORY(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(6, 0))
#define SET_PKT_H2C_CMD_ID(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#define SET_PKT_H2C_SUB_CMD_ID(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 16))
#define SET_PKT_H2C_TOTAL_LEN(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 0))

static inline void rtw_h2c_pkt_set_header(u8 *h2c_pkt, u8 sub_id)
{
	SET_PKT_H2C_CATEGORY(h2c_pkt, H2C_PKT_CATEGORY);
	SET_PKT_H2C_CMD_ID(h2c_pkt, H2C_PKT_CMD_ID);
	SET_PKT_H2C_SUB_CMD_ID(h2c_pkt, sub_id);
}

#define FW_OFFLOAD_H2C_SET_SEQ_NUM(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(31, 16))
#define GENERAL_INFO_SET_FW_TX_BOUNDARY(h2c_pkt, value)                        \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))

#define PHYDM_INFO_SET_REF_TYPE(h2c_pkt, value)                                \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(7, 0))
#define PHYDM_INFO_SET_RF_TYPE(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(15, 8))
#define PHYDM_INFO_SET_CUT_VER(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))
#define PHYDM_INFO_SET_RX_ANT_STATUS(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(27, 24))
#define PHYDM_INFO_SET_TX_ANT_STATUS(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(31, 28))
#define IQK_SET_CLEAR(h2c_pkt, value)                                          \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(0))
#define IQK_SET_SEGMENT_IQK(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(1))

/* Command H2C */
#define H2C_CMD_RSVD_PAGE		0x0
#define H2C_CMD_MEDIA_STATUS_RPT	0x01
#define H2C_CMD_SET_PWR_MODE		0x20
#define H2C_CMD_RA_INFO			0x40
#define H2C_CMD_RSSI_MONITOR		0x42

#define SET_H2C_CMD_ID_CLASS(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(7, 0))

#define MEDIA_STATUS_RPT_SET_OP_MODE(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#define MEDIA_STATUS_RPT_SET_MACID(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))

#define SET_PWR_MODE_SET_MODE(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(14, 8))
#define SET_PWR_MODE_SET_RLBM(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(19, 16))
#define SET_PWR_MODE_SET_SMART_PS(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 20))
#define SET_PWR_MODE_SET_AWAKE_INTERVAL(h2c_pkt, value)                        \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#define SET_PWR_MODE_SET_PORT_ID(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 5))
#define SET_PWR_MODE_SET_PWR_STATE(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#define SET_RSSI_INFO_MACID(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#define SET_RSSI_INFO_RSSI(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#define SET_RSSI_INFO_STBC(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, BIT(1))
#define SET_RA_INFO_MACID(h2c_pkt, value)                                      \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#define SET_RA_INFO_RATE_ID(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(20, 16))
#define SET_RA_INFO_INIT_RA_LVL(h2c_pkt, value)                                \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(22, 21))
#define SET_RA_INFO_SGI_EN(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(23))
#define SET_RA_INFO_BW_MODE(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(25, 24))
#define SET_RA_INFO_LDPC(h2c_pkt, value)                                       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(26))
#define SET_RA_INFO_NO_UPDATE(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(27))
#define SET_RA_INFO_VHT_EN(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(29, 28))
#define SET_RA_INFO_DIS_PT(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(30))
#define SET_RA_INFO_RA_MASK0(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#define SET_RA_INFO_RA_MASK1(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#define SET_RA_INFO_RA_MASK2(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(23, 16))
#define SET_RA_INFO_RA_MASK3(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(31, 24))

void rtw_fw_c2h_cmd_handle(struct rtw_dev *rtwdev, struct sk_buff *skb);
void rtw_fw_send_general_info(struct rtw_dev *rtwdev,
			      struct rtw_general_info *info);
void rtw_fw_send_phydm_info(struct rtw_dev *rtwdev,
			    struct rtw_general_info *info);
void rtw_fw_do_iqk(struct rtw_dev *rtwdev, struct rtw_iqk_para *para);
void rtw_fw_set_pwr_mode(struct rtw_dev *rtwdev);
void rtw_fw_send_rssi_info(struct rtw_dev *rtwdev, struct rtw_sta_info *si);
void rtw_fw_send_ra_info(struct rtw_dev *rtwdev, struct rtw_sta_info *si);
void rtw_fw_media_status_report(struct rtw_dev *rtwdev, u8 mac_id, bool conn);
void rtw_add_rsvd_page(struct rtw_dev *rtwdev, enum rtw_rsvd_packet_type type,
		       bool txdesc);
int rtw_fw_write_data_rsvd_page(struct rtw_dev *rtwdev, u16 pg_addr,
				u8 *buf, u32 size);
void rtw_reset_rsvd_page(struct rtw_dev *rtwdev);
int rtw_fw_download_rsvd_page(struct rtw_dev *rtwdev,
			      struct ieee80211_vif *vif);
int rtw_dump_drv_rsvd_page(struct rtw_dev *rtwdev,
			   u32 offset, u32 size, u32 *buf);
#endif
