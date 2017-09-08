/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <debug.h>
#include <err.h>
#include <smem.h>
#include <msm_panel.h>
#include <board.h>
#include <mipi_dsi.h>

#include "include/panel.h"
#include "panel_display.h"

/*---------------------------------------------------------------------------*/
/* GCDB Panel Database                                                       */
/*---------------------------------------------------------------------------*/
#include "include/panel_toshiba_720p_video.h"
#include "include/panel_sharp_qhd_video.h"
#include "include/panel_jdi_1080p_video.h"
#include "include/panel_generic_720p_cmd.h"
#include "include/panel_jdi_qhd_dualdsi_video.h"
#include "include/panel_jdi_qhd_dualdsi_cmd.h"
#include "target/display.h"
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_JDI_R63419_SUPPORT)
#include "include/panel_jdi_r63419_wqhd_dualdsi_cmd.h"
#endif
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd end*/

/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_SUPPORT)
#include "include/panel_truly_r63419_wqhd_dualdsi_cmd.h"
#include "include/panel_truly_r63419_wqhd_dualdsi_video.h"
#endif
/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd end*/

/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_SUPPORT)
#include "include/panel_sharp_r63419_wqhd_dualdsi_cmd.h"
#include "include/panel_sharp_r63419_wqhd_dualdsi_video.h"
#endif
/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd begin*/

/*Gionee xiangzhong 2013-12-21 add for lcd compatibility begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT)
/*define two gpio for lcd type check,just need modify these macro if the gpio changed*/
#include <platform/gpio.h>
#include <platform/iomap.h>
#include <reg.h>
#define LCD_TYPE_CHECK_GPIO_1	81
#define LCD_TYPE_CHECK_GPIO_2	82
int lcd_vendor;
#endif
/*Gionee xiangzhong 2013-12-21 add for lcd compatibility end*/

#define DISPLAY_MAX_PANEL_DETECTION 3

/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
enum {
JDI_1080P_VIDEO_PANEL,
TOSHIBA_720P_VIDEO_PANEL,
/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_SUPPORT)
TRULY_R63419_WQHD_CMD_PANEL,
TRULY_R63419_WQHD_VIDEO_PANEL,
#endif
/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd end*/
/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_SUPPORT)
SHARP_R63419_WQHD_CMD_PANEL,
SHARP_R63419_WQHD_VIDEO_PANEL,
#endif
/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd end*/
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_JDI_R63419_SUPPORT)
JDI_R63419_WQHD_CMD_PANEL,
#endif
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd end*/
SHARP_QHD_VIDEO_PANEL,
GENERIC_720P_CMD_PANEL,
JDI_QHD_DUALDSI_VIDEO_PANEL,
JDI_QHD_DUALDSI_CMD_PANEL,
UNKNOWN_PANEL
};

static uint32_t panel_id;
/*Gionee xiangzhong 2014-05-30 add for iovcc begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_IOVCC_CONTROL_SUPPORT)
void enable_iovcc(void )
{
	gpio_tlmm_config(iovcc_enable_gpio.pin_id, 0,iovcc_enable_gpio.pin_direction, 
	iovcc_enable_gpio.pin_pull,iovcc_enable_gpio.pin_strength, iovcc_enable_gpio.pin_state);
	gpio_set(iovcc_enable_gpio.pin_id, 2);
/*Gionee guoshite 20140910 modify 20ms to 200ms after iovcc power-on begin*/
	mdelay(200); //add 200ms for iovcc 
/*Gionee guoshite 20140910 modify 20ms to 200ms after iovcc power-on end*/
}
#endif
/*Gionee xiangzhong 2014-05-30 add for iovcc end*/

/*Gionee xiangzhong 2013-12-21 add for lcd compatibility begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT)
void lcd_vendor_check(void )
{
	int adc_value_1;
	int adc_value_2;

	gpio_tlmm_config(LCD_TYPE_CHECK_GPIO_1, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA, GPIO_ENABLE);
	gpio_tlmm_config(LCD_TYPE_CHECK_GPIO_2, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA, GPIO_ENABLE);
	adc_value_1 = readl((unsigned int *)GPIO_IN_OUT_ADDR(LCD_TYPE_CHECK_GPIO_1));
	adc_value_2 = readl((unsigned int *)GPIO_IN_OUT_ADDR(LCD_TYPE_CHECK_GPIO_2));
	dprintf(INFO,"adc_value_1 = %d adc_value_2 = %d\n",adc_value_1, adc_value_2);

	if((adc_value_1 == 0) && (adc_value_2 == 0))
		lcd_vendor = 1; //for jdi lcd
	else if((adc_value_1 == 0) && (adc_value_2 == 1))
		lcd_vendor = 1; //for truly lcd
	else if ((adc_value_1 == 1) && (adc_value_2 == 1))
		lcd_vendor = 2; //for sharp lcd
	else
		dprintf(INFO,"not found right lcd\n");
}
#endif
/*Gionee xiangzhong 2013-12-21 add for lcd compatibility end*/

int oem_panel_rotation()
{
	/* OEM can keep there panel spefic on instructions in this
	function */
	return NO_ERROR;
}


int oem_panel_on()
{
	/* OEM can keep there panel spefic on instructions in this
	function */
	return NO_ERROR;
}

int oem_panel_off()
{
	/* OEM can keep there panel spefic off instructions in this
	function */
	return NO_ERROR;
}

static void init_panel_data(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	switch (panel_id) {
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_JDI_R63419_SUPPORT)
	case JDI_R63419_WQHD_CMD_PANEL:
		dprintf(INFO, "JDI R63419 WQHD CMD PANEL\n");
		panelstruct->paneldata    = &jdi_r63419_wqhd_cmd_panel_data;
		panelstruct->panelres     = &jdi_r63419_wqhd_cmd_panel_res;
		panelstruct->color        = &jdi_r63419_wqhd_cmd_color;
		panelstruct->videopanel   = &jdi_r63419_wqhd_cmd_video_panel;
		panelstruct->commandpanel = &jdi_r63419_wqhd_cmd_command_panel;
		panelstruct->state        = &jdi_r63419_wqhd_cmd_state;
		panelstruct->laneconfig   = &jdi_r63419_wqhd_cmd_lane_config;
		panelstruct->paneltiminginfo
					 = &jdi_r63419_wqhd_cmd_timing_info;
		panelstruct->panelresetseq
					 = &jdi_r63419_wqhd_dualdsi_cmd_reset_seq;
		panelstruct->backlightinfo = &jdi_r63419_wqhd_cmd_backlight;
		pinfo->mipi.panel_cmds
					= jdi_r63419_wqhd_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
					= JDI_R63419_WQHD_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			jdi_r63419_wqhd_cmd_timings, TIMING_SIZE);
		pinfo->mipi.signature 	= JDI_R63419_CMD_SIGNATURE;
		break;
#endif
/*Gionee xiangzhong 2013-12-20 add for jdi r63419 cmd end*/

/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_SUPPORT)
	case TRULY_R63419_WQHD_VIDEO_PANEL:
		dprintf(INFO, "TRULY R63419 WQHD VIDEO PANEL\n");
		panelstruct->paneldata    = &truly_r63419_wqhd_video_panel_data;
		panelstruct->panelres     = &truly_r63419_wqhd_video_panel_res;
		panelstruct->color        = &truly_r63419_wqhd_video_color;
		panelstruct->videopanel   = &truly_r63419_wqhd_video_video_panel;
		panelstruct->commandpanel = &truly_r63419_wqhd_video_command_panel;
		panelstruct->state        = &truly_r63419_wqhd_video_state;
		panelstruct->laneconfig   = &truly_r63419_wqhd_video_lane_config;
		panelstruct->paneltiminginfo
			= &truly_r63419_wqhd_video_timing_info;
		panelstruct->panelresetseq
					 = &truly_r63419_wqhd_video_reset_seq;
		panelstruct->backlightinfo = &truly_r63419_wqhd_video_backlight;
		pinfo->mipi.panel_cmds
			= truly_r63419_wqhd_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= TRULY_R63419_WQHD_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			truly_r63419_wqhd_video_timings, TIMING_SIZE);
		break;
	case TRULY_R63419_WQHD_CMD_PANEL:
		dprintf(INFO, "TRULY R63419 WQHD CMD PANEL\n");
		panelstruct->paneldata    = &truly_r63419_wqhd_cmd_panel_data;
		panelstruct->panelres     = &truly_r63419_wqhd_cmd_panel_res;
		panelstruct->color        = &truly_r63419_wqhd_cmd_color;
		panelstruct->videopanel   = &truly_r63419_wqhd_cmd_video_panel;
		panelstruct->commandpanel = &truly_r63419_wqhd_cmd_command_panel;
		panelstruct->state        = &truly_r63419_wqhd_cmd_state;
		panelstruct->laneconfig   = &truly_r63419_wqhd_cmd_lane_config;
		panelstruct->paneltiminginfo
					 = &truly_r63419_wqhd_cmd_timing_info;
		panelstruct->panelresetseq
					 = &truly_r63419_wqhd_dualdsi_cmd_reset_seq;
		panelstruct->backlightinfo = &truly_r63419_wqhd_cmd_backlight;
		pinfo->mipi.panel_cmds
					= truly_r63419_wqhd_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
					= TRULY_R63419_WQHD_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			truly_r63419_wqhd_cmd_timings, TIMING_SIZE);
		pinfo->mipi.signature 	= TRULY_R63419_CMD_SIGNATURE;
		break;
#endif
/*Gionee xiangzhong 2013-12-20 add for truly r63419 cmd begin*/

/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_SUPPORT)
	case SHARP_R63419_WQHD_VIDEO_PANEL:
		dprintf(INFO, "SHARP R63419 WQHD VIDEO PANEL\n");
		panelstruct->paneldata    = &sharp_r63419_wqhd_video_panel_data;
		panelstruct->panelres     = &sharp_r63419_wqhd_video_panel_res;
		panelstruct->color        = &sharp_r63419_wqhd_video_color;
		panelstruct->videopanel   = &sharp_r63419_wqhd_video_video_panel;
		panelstruct->commandpanel = &sharp_r63419_wqhd_video_command_panel;
		panelstruct->state        = &sharp_r63419_wqhd_video_state;
		panelstruct->laneconfig   = &sharp_r63419_wqhd_video_lane_config;
		panelstruct->paneltiminginfo
			= &sharp_r63419_wqhd_video_timing_info;
		panelstruct->panelresetseq
					 = &sharp_r63419_wqhd_video_reset_seq;
		panelstruct->backlightinfo = &sharp_r63419_wqhd_video_backlight;
		pinfo->mipi.panel_cmds
			= sharp_r63419_wqhd_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= SHARP_R63419_WQHD_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			sharp_r63419_wqhd_video_timings, TIMING_SIZE);
		break;
	case SHARP_R63419_WQHD_CMD_PANEL:
		dprintf(INFO, "SHARP R63419 WQHD CMD PANEL\n");
		panelstruct->paneldata    = &sharp_r63419_wqhd_cmd_panel_data;
		panelstruct->panelres     = &sharp_r63419_wqhd_cmd_panel_res;
		panelstruct->color        = &sharp_r63419_wqhd_cmd_color;
		panelstruct->videopanel   = &sharp_r63419_wqhd_cmd_video_panel;
		panelstruct->commandpanel = &sharp_r63419_wqhd_cmd_command_panel;
		panelstruct->state        = &sharp_r63419_wqhd_cmd_state;
		panelstruct->laneconfig   = &sharp_r63419_wqhd_cmd_lane_config;
		panelstruct->paneltiminginfo
			= &sharp_r63419_wqhd_cmd_timing_info;
		panelstruct->panelresetseq
					 = &sharp_r63419_wqhd_dualdsi_cmd_reset_seq;
		panelstruct->backlightinfo = &sharp_r63419_wqhd_cmd_backlight;
		pinfo->mipi.panel_cmds
			= sharp_r63419_wqhd_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
			= SHARP_R63419_WQHD_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			sharp_r63419_wqhd_cmd_timings, TIMING_SIZE);
		break;
#endif
/*Gionee xiangzhong 2013-12-20 add for sharp r63419 cmd end*/
	case TOSHIBA_720P_VIDEO_PANEL:
		panelstruct->paneldata    = &toshiba_720p_video_panel_data;
		panelstruct->panelres     = &toshiba_720p_video_panel_res;
		panelstruct->color        = &toshiba_720p_video_color;
		panelstruct->videopanel   = &toshiba_720p_video_video_panel;
		panelstruct->commandpanel = &toshiba_720p_video_command_panel;
		panelstruct->state        = &toshiba_720p_video_state;
		panelstruct->laneconfig   = &toshiba_720p_video_lane_config;
		panelstruct->paneltiminginfo
					 = &toshiba_720p_video_timing_info;
		panelstruct->panelresetseq
					 = &toshiba_720p_video_panel_reset_seq;
		panelstruct->backlightinfo = &toshiba_720p_video_backlight;
		pinfo->mipi.panel_cmds
					= toshiba_720p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= TOSHIBA_720P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			toshiba_720p_video_timings, TIMING_SIZE);
		pinfo->mipi.signature 	= TOSHIBA_720P_VIDEO_SIGNATURE;
		break;
	case SHARP_QHD_VIDEO_PANEL:
		panelstruct->paneldata    = &sharp_qhd_video_panel_data;
		panelstruct->panelres     = &sharp_qhd_video_panel_res;
		panelstruct->color        = &sharp_qhd_video_color;
		panelstruct->videopanel   = &sharp_qhd_video_video_panel;
		panelstruct->commandpanel = &sharp_qhd_video_command_panel;
		panelstruct->state        = &sharp_qhd_video_state;
		panelstruct->laneconfig   = &sharp_qhd_video_lane_config;
		panelstruct->paneltiminginfo
					 = &sharp_qhd_video_timing_info;
		panelstruct->panelresetseq
					 = &sharp_qhd_video_panel_reset_seq;
		panelstruct->backlightinfo = &sharp_qhd_video_backlight;
		pinfo->mipi.panel_cmds
					= sharp_qhd_video_on_command;
		pinfo->mipi.num_of_panel_cmds
					= SHARP_QHD_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
				sharp_qhd_video_timings, TIMING_SIZE);
		break;
	case JDI_1080P_VIDEO_PANEL:
		panelstruct->paneldata    = &jdi_1080p_video_panel_data;
		panelstruct->panelres     = &jdi_1080p_video_panel_res;
		panelstruct->color        = &jdi_1080p_video_color;
		panelstruct->videopanel   = &jdi_1080p_video_video_panel;
		panelstruct->commandpanel = &jdi_1080p_video_command_panel;
		panelstruct->state        = &jdi_1080p_video_state;
		panelstruct->laneconfig   = &jdi_1080p_video_lane_config;
		panelstruct->paneltiminginfo
			= &jdi_1080p_video_timing_info;
		panelstruct->panelresetseq
					 = &jdi_1080p_video_panel_reset_seq;
		panelstruct->backlightinfo = &jdi_1080p_video_backlight;
		pinfo->mipi.panel_cmds
			= jdi_1080p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= JDI_1080P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			jdi_1080p_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = JDI_1080P_VIDEO_SIGNATURE;
		break;
	case GENERIC_720P_CMD_PANEL:
		panelstruct->paneldata    = &generic_720p_cmd_panel_data;
		panelstruct->panelres     = &generic_720p_cmd_panel_res;
		panelstruct->color        = &generic_720p_cmd_color;
		panelstruct->videopanel   = &generic_720p_cmd_video_panel;
		panelstruct->commandpanel = &generic_720p_cmd_command_panel;
		panelstruct->state        = &generic_720p_cmd_state;
		panelstruct->laneconfig   = &generic_720p_cmd_lane_config;
		panelstruct->paneltiminginfo
			= &generic_720p_cmd_timing_info;
		panelstruct->panelresetseq
					 = &generic_720p_cmd_reset_seq;
		panelstruct->backlightinfo = &generic_720p_cmd_backlight;
		pinfo->mipi.panel_cmds
			= generic_720p_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
			= GENERIC_720P_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			generic_720p_cmd_timings, TIMING_SIZE);
		pinfo->mipi.signature = GENERIC_720P_CMD_SIGNATURE;
		break;
	case JDI_QHD_DUALDSI_VIDEO_PANEL:
		panelstruct->paneldata    = &jdi_qhd_dualdsi_video_panel_data;
		panelstruct->panelres     = &jdi_qhd_dualdsi_video_panel_res;
		panelstruct->color        = &jdi_qhd_dualdsi_video_color;
		panelstruct->videopanel   = &jdi_qhd_dualdsi_video_video_panel;
		panelstruct->commandpanel = &jdi_qhd_dualdsi_video_command_panel;
		panelstruct->state        = &jdi_qhd_dualdsi_video_state;
		panelstruct->laneconfig   = &jdi_qhd_dualdsi_video_lane_config;
		panelstruct->paneltiminginfo
			= &jdi_qhd_dualdsi_video_timing_info;
		panelstruct->panelresetseq
					 = &jdi_qhd_dualdsi_video_reset_seq;
		panelstruct->backlightinfo = &jdi_qhd_dualdsi_video_backlight;
		pinfo->mipi.panel_cmds
			= jdi_qhd_dualdsi_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= JDI_QHD_DUALDSI_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			jdi_qhd_dualdsi_video_timings, TIMING_SIZE);
		break;
	case JDI_QHD_DUALDSI_CMD_PANEL:
		panelstruct->paneldata    = &jdi_qhd_dualdsi_cmd_panel_data;
		panelstruct->panelres     = &jdi_qhd_dualdsi_cmd_panel_res;
		panelstruct->color        = &jdi_qhd_dualdsi_cmd_color;
		panelstruct->videopanel   = &jdi_qhd_dualdsi_cmd_video_panel;
		panelstruct->commandpanel = &jdi_qhd_dualdsi_cmd_command_panel;
		panelstruct->state        = &jdi_qhd_dualdsi_cmd_state;
		panelstruct->laneconfig   = &jdi_qhd_dualdsi_cmd_lane_config;
		panelstruct->paneltiminginfo
			= &jdi_qhd_dualdsi_cmd_timing_info;
		panelstruct->panelresetseq
					 = &jdi_qhd_dualdsi_cmd_reset_seq;
		panelstruct->backlightinfo = &jdi_qhd_dualdsi_cmd_backlight;
		pinfo->mipi.panel_cmds
			= jdi_qhd_dualdsi_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
			= JDI_QHD_DUALDSI_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			jdi_qhd_dualdsi_cmd_timings, TIMING_SIZE);
		break;
	case UNKNOWN_PANEL:
		memset(panelstruct, 0, sizeof(struct panel_struct));
		memset(pinfo->mipi.panel_cmds, 0, sizeof(struct mipi_dsi_cmd));
		pinfo->mipi.num_of_panel_cmds = 0;
		memset(phy_db->timing, 0, TIMING_SIZE);
		pinfo->mipi.signature = 0;
		break;
	}
}

uint32_t oem_panel_max_auto_detect_panels()
{
	return target_panel_auto_detect_enabled() ?
			DISPLAY_MAX_PANEL_DETECTION : 0;
}

/*Gionee xiangzhong 2013-12-20 add for gionee lcd  begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_JDI_R63419_SUPPORT) || defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_SUPPORT) \
	|| defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_SUPPORT)
static uint32_t auto_pan_loop = 1;
#else
static uint32_t auto_pan_loop = 0;
#endif
/*Gionee xiangzhong 2013-12-20 add for gionee lcd end*/

bool oem_panel_select(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	uint32_t hw_id = board_hardware_id();
	uint32_t target_id = board_target_id();
	bool ret = true;

/*Gionee xiangzhong 2014-05-30 add for iovcc begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_IOVCC_CONTROL_SUPPORT)
	enable_iovcc();
#endif
/*Gionee xiangzhong 2014-05-30 add for iovcc end*/

/*Gionee xiangzhong 2013-12-21 add for lcd compatibility begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT)
	lcd_vendor_check();
#endif
/*Gionee xiangzhong 2013-12-21 add for lcd compatibility end*/

	switch (hw_id) {
	case HW_PLATFORM_MTP:
	case HW_PLATFORM_FLUID:
	case HW_PLATFORM_SURF:
		switch (auto_pan_loop) {
		case 0:
			dprintf(INFO, "auto_pan_loop\n");
			panel_id = JDI_1080P_VIDEO_PANEL;
			break;
		case 1:
/*Gionee xiangzhong 2013-12-20 add for lcd compatibility begin*/
#if defined(CONFIG_GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT) && \
			(defined(CONFIG_GN_Q_BSP_LCD_JDI_R63419_SUPPORT) || \
			 defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_SUPPORT) || \
			 defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_SUPPORT))
	if (lcd_vendor == 0)  //for jdi lcd
	{
		dprintf(INFO, "LCD PANEL IS JDI WQHD CMD\n");
		panel_id = JDI_R63419_WQHD_CMD_PANEL;
	}
	else if(lcd_vendor == 1)
	{
#if defined(CONFIG_GN_Q_BSP_LCD_TRULY_R63419_VIDEO_SUPPORT)
		panel_id = TRULY_R63419_WQHD_VIDEO_PANEL;
		dprintf(INFO, "LCD PANEL IS TRULY WQHD VIDEO\n");
#else
		panel_id = TRULY_R63419_WQHD_CMD_PANEL;
		dprintf(INFO, "LCD PANEL IS TRULY WQHD CMD\n");
#endif
	}
	else if(lcd_vendor == 2)
	{
#if defined(CONFIG_GN_Q_BSP_LCD_SHARP_R63419_VIDEO_SUPPORT)
		panel_id = SHARP_R63419_WQHD_VIDEO_PANEL;
		dprintf(INFO, "LCD PANEL IS SYHARP WQHD VIDEO\n");
#else
		dprintf(INFO, "LCD PANEL IS SHARP WQHD CMD\n");
		panel_id = SHARP_R63419_WQHD_CMD_PANEL;
#endif
	}
#else
			panel_id = TOSHIBA_720P_VIDEO_PANEL;
#endif
/*Gionee xiangzhong 2013-12-20 add for lcd compatibility begin*/
			break;
		case 2:
			panel_id = GENERIC_720P_CMD_PANEL;
			break;
		default:
			panel_id = UNKNOWN_PANEL;
			ret = false;
			break;
		}
		auto_pan_loop++;
		break;
	case HW_PLATFORM_DRAGON:
		panel_id = SHARP_QHD_VIDEO_PANEL;
		break;
	default:
		dprintf(CRITICAL, "Display not enabled for %d HW type\n"
					, hw_id);
		return false;
	}

	init_panel_data(panelstruct, pinfo, phy_db);

	return ret;
}
