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

//gionee caomingliang 20140815 add begin
#include "include/panel_nt35596_1080p_video.h"
#include "include/panel_nt35695_1080p_cmd.h"
#include "include/panel_r63311_1080p_video.h"
#include <platform/gpio.h>
#include <platform/iomap.h>
#include <reg.h>
#define LCD_TYPE_CHECK_GPIO_1	76
#define LCD_TYPE_CHECK_GPIO_2	77
int lcd_vendor;

#define DISPLAY_MAX_PANEL_DETECTION 3
//gionee caomingliang 20140815 add end

/*---------------------------------------------------------------------------*/
/* static panel selection variable                                           */
/*---------------------------------------------------------------------------*/
enum {
JDI_1080P_VIDEO_PANEL,
TOSHIBA_720P_VIDEO_PANEL,
//gionee caomingliang 20140815 add begin
TRULY_NT35596_1080P_VIDEO_PANEL,
TRULY_NT35695_1080P_CMD_PANEL,
R63311_1080P_VIDEO_PANEL,
//gionee caomingliang 20140815 add end
SHARP_QHD_VIDEO_PANEL,
GENERIC_720P_CMD_PANEL,
JDI_QHD_DUALDSI_VIDEO_PANEL,
JDI_QHD_DUALDSI_CMD_PANEL,
UNKNOWN_PANEL
};

static uint32_t panel_id;

//gionee caomingliang 20140815 add begin
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
		lcd_vendor = 0; //for sharp lcd
	else if((adc_value_1 == 0) && (adc_value_2 == 1))
		lcd_vendor = 1; //for truly lcd
	else if ((adc_value_1 == 1) && (adc_value_2 == 1))
		lcd_vendor = 2; //for  lcd
	else
		dprintf(INFO,"not found right lcd\n");
}
//gionee caomingliang 20140815 add end
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
//gionee caomingliang 20140815 add begin
	case TRULY_NT35695_1080P_CMD_PANEL:
		panelstruct->paneldata    = &nt35695_1080p_cmd_panel_data;
		panelstruct->panelres     = &nt35695_1080p_cmd_panel_res;
		panelstruct->color        = &nt35695_1080p_cmd_color;
		panelstruct->videopanel   = &nt35695_1080p_cmd_video_panel;
		panelstruct->commandpanel = &nt35695_1080p_cmd_command_panel;
		panelstruct->state        = &nt35695_1080p_cmd_state;
		panelstruct->laneconfig   = &nt35695_1080p_cmd_lane_config;
		panelstruct->paneltiminginfo
			= &nt35695_1080p_cmd_timing_info;
		panelstruct->panelresetseq
					 = &nt35695_1080p_cmd_reset_seq;
		panelstruct->backlightinfo = &nt35695_1080p_cmd_backlight;
		pinfo->mipi.panel_cmds
			= nt35695_1080p_cmd_on_command;
		pinfo->mipi.num_of_panel_cmds
			= NT35695_1080P_CMD_ON_COMMAND;
		memcpy(phy_db->timing,
			nt35695_1080p_cmd_timings, TIMING_SIZE);
		pinfo->mipi.signature = NT35695_1080P_CMD_SIGNATURE;
		break;
	case TRULY_NT35596_1080P_VIDEO_PANEL:
		panelstruct->paneldata    = &nt35596_1080p_video_panel_data;
		panelstruct->panelres     = &nt35596_1080p_video_panel_res;
		panelstruct->color        = &nt35596_1080p_video_color;
		panelstruct->videopanel   = &nt35596_1080p_video_video_panel;
		panelstruct->commandpanel = &nt35596_1080p_video_command_panel;
		panelstruct->state        = &nt35596_1080p_video_state;
		panelstruct->laneconfig   = &nt35596_1080p_video_lane_config;
		panelstruct->paneltiminginfo
			= &nt35596_1080p_video_timing_info;
		panelstruct->panelresetseq
					 = &nt35596_1080p_video_panel_reset_seq;
		panelstruct->backlightinfo = &nt35596_1080p_video_backlight;
		pinfo->mipi.panel_cmds
			= nt35596_1080p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= NT35596_1080P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			nt35596_1080p_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = NT35596_1080P_VIDEO_SIGNATURE;
		break;
	case R63311_1080P_VIDEO_PANEL:
		panelstruct->paneldata    = &r63311_1080p_video_panel_data;
		panelstruct->panelres     = &r63311_1080p_video_panel_res;
		panelstruct->color        = &r63311_1080p_video_color;
		panelstruct->videopanel   = &r63311_1080p_video_video_panel;
		panelstruct->commandpanel = &r63311_1080p_video_command_panel;
		panelstruct->state        = &r63311_1080p_video_state;
		panelstruct->laneconfig   = &r63311_1080p_video_lane_config;
		panelstruct->paneltiminginfo
			= &r63311_1080p_video_timing_info;
		panelstruct->panelresetseq
					 = &r63311_1080p_video_panel_reset_seq;
		panelstruct->backlightinfo = &r63311_1080p_video_backlight;
		pinfo->mipi.panel_cmds
			= r63311_1080p_video_on_command;
		pinfo->mipi.num_of_panel_cmds
			= R63311_1080P_VIDEO_ON_COMMAND;
		memcpy(phy_db->timing,
			r63311_1080p_video_timings, TIMING_SIZE);
		pinfo->mipi.signature = R63311_1080P_VIDEO_SIGNATURE;
		break;
//gionee caomingliang 20140815 add end
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

static uint32_t auto_pan_loop = 1;

bool oem_panel_select(struct panel_struct *panelstruct,
			struct msm_panel_info *pinfo,
			struct mdss_dsi_phy_ctrl *phy_db)
{
	uint32_t hw_id = board_hardware_id();
	//uint32_t target_id = board_target_id();
	bool ret = true;

//gionee caomingliang 20140815 add begin
	lcd_vendor_check();
//gionee caomingliang 20140815 add end
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
//gionee caomingliang 20140815 add begin
			if (lcd_vendor == 0)  //for jdi lcd
			{
				dprintf(INFO, "LCD PANEL IS sharp video\n");
				panel_id = R63311_1080P_VIDEO_PANEL;
			}
			else if(lcd_vendor == 1)
			{
				dprintf(INFO, "LCD PANEL IS TRULY CMD\n");
				//panel_id = TRULY_NT35596_1080P_VIDEO_PANEL;
				panel_id = TRULY_NT35695_1080P_CMD_PANEL;
			}
			else if(lcd_vendor == 2)
			{
				dprintf(INFO, "LCD PANEL IS SHARP none\n");
				panel_id = R63311_1080P_VIDEO_PANEL;
			}
//gionee caomingliang 20140815 add end
			break;
		case 2:
//gionee caomingliang 20140815 add begin
			if (lcd_vendor == 0)  //for jdi lcd
			{
				dprintf(INFO, "LCD PANEL IS sharp video\n");
				panel_id = R63311_1080P_VIDEO_PANEL;
			}
			else if(lcd_vendor == 1)
			{
				dprintf(INFO, "LCD PANEL IS TRULY VIDEO\n");
				panel_id = TRULY_NT35596_1080P_VIDEO_PANEL;
				//panel_id = TRULY_NT35695_1080P_CMD_PANEL;
			}
			else if(lcd_vendor == 2)
			{
				dprintf(INFO, "LCD PANEL IS SHARP none\n");
				panel_id = R63311_1080P_VIDEO_PANEL;
			}
//gionee caomingliang 20140815 add end
//			panel_id = GENERIC_720P_CMD_PANEL;
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
