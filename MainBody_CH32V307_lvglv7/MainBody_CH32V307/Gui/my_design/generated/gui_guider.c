/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"

void init_scr_del_flag(lv_ui *ui)
{
  
	ui->screen_none_del = false;
	ui->screen_pwon_del = false;
	ui->screen_settings_del = false;
	ui->screen_rtdata_del = false;
	ui->screen_devicest_del = false;
	ui->screen_alarmst_del = false;
	ui->screen_network_del = false;
	ui->screen_sub_device_del = false;
}

void setup_ui(lv_ui *ui)
{
  LV_THEME_DEFAULT_INIT(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY,
		LV_THEME_MATERIAL_FLAG_LIGHT, LV_THEME_DEFAULT_FONT_SMALL,  LV_THEME_DEFAULT_FONT_NORMAL,
		LV_THEME_DEFAULT_FONT_SUBTITLE, LV_THEME_DEFAULT_FONT_TITLE);
  init_scr_del_flag(ui);
  setup_scr_screen_pwon(ui);
  setup_scr_screen_alarmst(ui);
  setup_scr_screen_devicest(ui);
  setup_scr_screen_network(ui);
  setup_scr_screen_none(ui);
  setup_scr_screen_rtdata(ui);
  setup_scr_screen_settings(ui);
  setup_scr_screen_sub_device(ui);
  lv_switch_on(ui->screen_alarmst_datam_sw, LV_ANIM_OFF);
  lv_switch_on(ui->screen_alarmst_esc_sw, LV_ANIM_OFF);
  lv_scr_load(ui->screen_pwon);
}
