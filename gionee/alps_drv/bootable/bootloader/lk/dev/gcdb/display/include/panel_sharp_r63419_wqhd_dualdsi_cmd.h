/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
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

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_SHARP_R63419_WQHD_DUALDSI_CMD_H_

#define _PANEL_SHARP_R63419_WQHD_DUALDSI_CMD_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/
static struct panel_config sharp_r63419_wqhd_cmd_panel_data = {
	"qcom,mdss_dsi_sharp_r63419_wqhd_dualmipi0_cmd", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 1, "DISPLAY_1", 0, 0, 60, 0, 0, 1, 0, 0, 0, 0, 0, 11, 0, 0,
	"qcom,mdss_dsi_sharp_r63419_wqhd_dualmipi1_cmd"
};
	

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution sharp_r63419_wqhd_cmd_panel_res = {
  1440, 2560, 120, 44, 16, 0, 8, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel Color Information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info sharp_r63419_wqhd_cmd_color = {
  24, 0, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel Command information                                                 */
/*---------------------------------------------------------------------------*/

static char sharp_r63419_wqhd_cmd_on_cmd0[] = {
	0xb0, 0x00, 0x23, 0x80 
};

static char sharp_r63419_wqhd_cmd_on_cmd1[] = {
	0xd6, 0x01, 0x23, 0x80
};

static char sharp_r63419_wqhd_cmd_on_cmd2[] = {
	0x02, 0x00, 0x29, 0xc0,
	0xb3, 0x08, 0xff, 0xff
};

static char sharp_r63419_wqhd_cmd_on_cmd3[] = {
  0x08, 0x00, 0x29, 0xc0,
  0xba, 0xb5, 0x32, 0x41,
  0x64, 0x23, 0xa0, 0xa0
};

static char sharp_r63419_wqhd_cmd_on_cmd4[] = {
  0x24, 0x00, 0x29, 0xc0,
  0xc1, 0x04, 0x61, 0x00,
  0x5f, 0x90, 0xff, 0x51,
  0x02, 0xff, 0xff, 0xff,
  0x5d, 0x63, 0xac, 0xb9,
  0xff, 0x3f, 0x7c, 0x41,
	0xfd, 0xff, 0xcb, 0xf8,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x00, 0x22,
	0x00, 0x04, 0xc7, 0x51
};

static char sharp_r63419_wqhd_cmd_on_cmd5[] = {
  0x14, 0x00, 0x29, 0xc0,
	0xc8, 0x01, 0x02, 0xff,
	0x00, 0xfe, 0xc8, 0x00,
	0x02, 0xff, 0x00, 0xfe,
	0xb0, 0x00, 0x02, 0xff,
  0x00, 0xfe, 0xfc, 0x00
};

static char sharp_r63419_wqhd_cmd_on_cmd6[] = {
    0x25, 0x00, 0x29, 0xc0,
	  0xCA, 0xA1, 0xA0, 0xA0,
	  0xB0, 0xB0, 0xA0, 0xA0,
	  0x0C, 0x20, 0x00, 0x94,
	  0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0xF0, 0x10,
	  0x4A, 0x00, 0xFF, 0x00,
	  0xFF, 0x0C, 0x0C, 0x20,
	  0x10, 0x3F, 0x3F, 0x10,
	  0x10, 0x3F, 0x3F, 0x3F,
	  0x3F, 0xff, 0xff, 0xff
};

static char sharp_r63419_wqhd_cmd_on_cmd7[] = {
    0x10, 0x00, 0x29, 0xc0,
	  0xcb, 0xe6, 0xe0, 0xc7,
	  0x63, 0x00, 0x00, 0x00,
	  0x00, 0x40, 0x00, 0x80,
	  0x00, 0xe8, 0x00, 0x00

 };

static char sharp_r63419_wqhd_cmd_on_cmd8[] = {
	0x05, 0x00, 0x39, 0xc0,
	0x2a, 0x00, 0x00, 0x05,
	0x9f, 0xff, 0xff, 0xff
};

static char sharp_r63419_wqhd_cmd_on_cmd9[] = {
	0x05, 0x00, 0x39, 0xc0,
	0x2b, 0x00, 0x00, 0x09,
	0xff, 0xff, 0xff, 0xff
};

static char sharp_r63419_wqhd_cmd_on_cmd10[] = {
          0x35, 0x00, 0x15, 0x80
};
static char sharp_r63419_wqhd_cmd_on_cmd11[] = {
          0x51, 0xff, 0x15, 0x80
};

static char sharp_r63419_wqhd_cmd_on_cmd12[] = {
          0x53, 0x24, 0x15, 0x80
};
static char sharp_r63419_wqhd_cmd_on_cmd13[] = {
          0x55, 0x83, 0x15, 0x80
};

static char sharp_r63419_wqhd_cmd_on_cmd14[] = {
          0xb0, 0xb3, 0x23, 0x80
};


static char sharp_r63419_wqhd_cmd_on_cmd15[] = {
	0x29, 0x00, 0x05, 0x80
};

static char sharp_r63419_wqhd_cmd_on_cmd16[] = {
	0x11, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd sharp_r63419_wqhd_cmd_on_command[] = {
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd0},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd1},
	{ 0x8 , sharp_r63419_wqhd_cmd_on_cmd2},
	{ 0xc , sharp_r63419_wqhd_cmd_on_cmd3},
	{ 0x28 , sharp_r63419_wqhd_cmd_on_cmd4},
	{ 0x18, sharp_r63419_wqhd_cmd_on_cmd5},
	{ 0x2c , sharp_r63419_wqhd_cmd_on_cmd6},
	{ 0x14 , sharp_r63419_wqhd_cmd_on_cmd7},
	{ 0xc , sharp_r63419_wqhd_cmd_on_cmd8},
	{ 0xc , sharp_r63419_wqhd_cmd_on_cmd9},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd10},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd11},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd12},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd13},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd14},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd15,20},
	{ 0x4 , sharp_r63419_wqhd_cmd_on_cmd16,120},
};
#define SHARP_R63419_WQHD_CMD_ON_COMMAND (sizeof(sharp_r63419_wqhd_cmd_on_command)/ sizeof(sharp_r63419_wqhd_cmd_on_command[0]))


static char sharp_r63419_wqhd_cmdoff_cmd0[] = {
0x28, 0x00, 0x05, 0x80 };


static char sharp_r63419_wqhd_cmdoff_cmd1[] = {
0x10, 0x00, 0x05, 0x80 };




static struct mipi_dsi_cmd sharp_r63419_wqhd_cmd_off_command[] = {
{ 0x4 , sharp_r63419_wqhd_cmdoff_cmd0},
{ 0x4 , sharp_r63419_wqhd_cmdoff_cmd1}
};
#define R63419_WQHD_CMD_OFF_COMMAND 2


static struct command_state sharp_r63419_wqhd_cmd_state = {
  0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/

static struct commandpanel_info sharp_r63419_wqhd_cmd_command_panel = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/

static struct videopanel_info sharp_r63419_wqhd_cmd_video_panel = {
  1, 0, 0, 0, 1, 1, 2, 0, 0x9
};

/*---------------------------------------------------------------------------*/
/* Lane Configuration                                                        */
/*---------------------------------------------------------------------------*/

static struct lane_configuration sharp_r63419_wqhd_cmd_lane_config = {
  4, 0, 1, 1, 1, 1
};


/*---------------------------------------------------------------------------*/
/* Panel Timing                                                              */
/*---------------------------------------------------------------------------*/
static const uint32_t sharp_r63419_wqhd_cmd_timings[] = {
	0xcd, 0x34, 0x24, 0x00, 0x64, 0x68, 0x28, 0x38, 0x2a, 0x03, 0x04, 0x00
};

static struct panel_timing sharp_r63419_wqhd_cmd_timing_info = {
	0x0, 0x04, 0x28, 0x27
};

/*---------------------------------------------------------------------------*/
/* Panel reset sequence                                                      */
/*---------------------------------------------------------------------------*/
static struct panel_reset_sequence sharp_r63419_wqhd_dualdsi_cmd_reset_seq = {
	{1, 0, 1, }, {20, 200, 20, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight Settings                                                        */
/*---------------------------------------------------------------------------*/

static struct backlight sharp_r63419_wqhd_cmd_backlight = {
  1, 1, 255, 100, 1, "PMIC_8941"
};

#define SHARP_R63419_CMD_SIGNATURE 0xF96D28C
#endif /*_PANEL_SHARP_R63419_WQHD_DUALDSI_CMD_H_*/