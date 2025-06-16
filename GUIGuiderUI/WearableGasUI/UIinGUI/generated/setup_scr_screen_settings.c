/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen_settings(lv_ui *ui){
	//Widget: screen_settings
	ui->screen_settings = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen_settings, 320, 240);

	//Set style for screen_settings. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_main_default;
	lv_style_reset(&style_screen_settings_main_default);
	lv_style_set_bg_opa(&style_screen_settings_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings, LV_OBJ_PART_MAIN, &style_screen_settings_main_default);


	//Widget: screen_settings_page
	ui->screen_settings_page = lv_cont_create(ui->screen_settings, NULL);
	lv_obj_set_click(ui->screen_settings_page, false);
	lv_cont_set_layout(ui->screen_settings_page, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_settings_page, LV_FIT_NONE);
	lv_obj_set_pos(ui->screen_settings_page, -440, 0);
	lv_obj_set_size(ui->screen_settings_page, 1200, 240);

	//Set style for screen_settings_page. Part: LV_CONT_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_page_main_default;
	lv_style_reset(&style_screen_settings_page_main_default);
	lv_style_set_bg_opa(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, lv_color_hex(0x999999));
	lv_style_set_radius(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_settings_page_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_page, LV_CONT_PART_MAIN, &style_screen_settings_page_main_default);

	//Widget: screen_settings_btn_sub_device
	ui->screen_settings_btn_sub_device = lv_btn_create(ui->screen_settings_page, NULL);
	ui->screen_settings_btn_sub_device_label = lv_label_create(ui->screen_settings_btn_sub_device, NULL);
	lv_label_set_text(ui->screen_settings_btn_sub_device_label, "Sub-device\nConnection");
	lv_label_set_align(ui->screen_settings_btn_sub_device_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_btn_sub_device, 30, 34);
	lv_obj_set_size(ui->screen_settings_btn_sub_device, 200, 160);

	//Set style for screen_settings_btn_sub_device. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_btn_sub_device_main_default;
	lv_style_reset(&style_screen_settings_btn_sub_device_main_default);
	lv_style_set_text_color(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_32);
	lv_style_set_bg_opa(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_settings_btn_sub_device_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_btn_sub_device, LV_BTN_PART_MAIN, &style_screen_settings_btn_sub_device_main_default);


	//Widget: screen_settings_btn_network
	ui->screen_settings_btn_network = lv_btn_create(ui->screen_settings_page, NULL);
	ui->screen_settings_btn_network_label = lv_label_create(ui->screen_settings_btn_network, NULL);
	lv_label_set_text(ui->screen_settings_btn_network_label, "Network\nConnection");
	lv_label_set_align(ui->screen_settings_btn_network_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_btn_network, 264, 34);
	lv_obj_set_size(ui->screen_settings_btn_network, 200, 160);

	//Set style for screen_settings_btn_network. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_btn_network_main_default;
	lv_style_reset(&style_screen_settings_btn_network_main_default);
	lv_style_set_text_color(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_32);
	lv_style_set_bg_opa(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_settings_btn_network_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_btn_network, LV_BTN_PART_MAIN, &style_screen_settings_btn_network_main_default);


	//Widget: screen_settings_btn_rtdata
	ui->screen_settings_btn_rtdata = lv_btn_create(ui->screen_settings_page, NULL);
	ui->screen_settings_btn_rtdata_label = lv_label_create(ui->screen_settings_btn_rtdata, NULL);
	lv_label_set_text(ui->screen_settings_btn_rtdata_label, "Realtime\nData\nMonitoring");
	lv_label_set_align(ui->screen_settings_btn_rtdata_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_btn_rtdata, 500, 34);
	lv_obj_set_size(ui->screen_settings_btn_rtdata, 200, 160);

	//Set style for screen_settings_btn_rtdata. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_btn_rtdata_main_default;
	lv_style_reset(&style_screen_settings_btn_rtdata_main_default);
	lv_style_set_text_color(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_32);
	lv_style_set_bg_opa(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_settings_btn_rtdata_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_btn_rtdata, LV_BTN_PART_MAIN, &style_screen_settings_btn_rtdata_main_default);


	//Widget: screen_settings_btn_devicest
	ui->screen_settings_btn_devicest = lv_btn_create(ui->screen_settings_page, NULL);
	ui->screen_settings_btn_devicest_label = lv_label_create(ui->screen_settings_btn_devicest, NULL);
	lv_label_set_text(ui->screen_settings_btn_devicest_label, "Device\nSelf-test");
	lv_label_set_align(ui->screen_settings_btn_devicest_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_btn_devicest, 970, 34);
	lv_obj_set_size(ui->screen_settings_btn_devicest, 200, 160);

	//Set style for screen_settings_btn_devicest. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_btn_devicest_main_default;
	lv_style_reset(&style_screen_settings_btn_devicest_main_default);
	lv_style_set_text_color(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_32);
	lv_style_set_bg_opa(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_settings_btn_devicest_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_btn_devicest, LV_BTN_PART_MAIN, &style_screen_settings_btn_devicest_main_default);


	//Widget: screen_settings_btn_alarmset
	ui->screen_settings_btn_alarmset = lv_btn_create(ui->screen_settings_page, NULL);
	ui->screen_settings_btn_alarmset_label = lv_label_create(ui->screen_settings_btn_alarmset, NULL);
	lv_label_set_text(ui->screen_settings_btn_alarmset_label, "Alarm\nSettings");
	lv_label_set_align(ui->screen_settings_btn_alarmset_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_btn_alarmset, 735, 34);
	lv_obj_set_size(ui->screen_settings_btn_alarmset, 200, 160);

	//Set style for screen_settings_btn_alarmset. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_btn_alarmset_main_default;
	lv_style_reset(&style_screen_settings_btn_alarmset_main_default);
	lv_style_set_text_color(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_32);
	lv_style_set_bg_opa(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_settings_btn_alarmset_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_btn_alarmset, LV_BTN_PART_MAIN, &style_screen_settings_btn_alarmset_main_default);


	//Widget: screen_settings_pwr_pic
	ui->screen_settings_pwr_pic = lv_bar_create(ui->screen_settings, NULL);
	lv_bar_set_anim_time(ui->screen_settings_pwr_pic, 1000);
	lv_bar_set_range(ui->screen_settings_pwr_pic, 0, 100);
	lv_bar_set_value(ui->screen_settings_pwr_pic, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_settings_pwr_pic, 265, 9);
	lv_obj_set_size(ui->screen_settings_pwr_pic, 20, 6);

	//Set style for screen_settings_pwr_pic. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_pwr_pic_bg_default;
	lv_style_reset(&style_screen_settings_pwr_pic_bg_default);
	lv_style_set_bg_opa(&style_screen_settings_pwr_pic_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_pwr_pic_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_settings_pwr_pic_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_settings_pwr_pic_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_pwr_pic, LV_BAR_PART_BG, &style_screen_settings_pwr_pic_bg_default);

	//Set style for screen_settings_pwr_pic. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_pwr_pic_indic_default;
	lv_style_reset(&style_screen_settings_pwr_pic_indic_default);
	lv_style_set_bg_opa(&style_screen_settings_pwr_pic_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_settings_pwr_pic_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_settings_pwr_pic_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_settings_pwr_pic, LV_BAR_PART_INDIC, &style_screen_settings_pwr_pic_indic_default);


	//Widget: screen_settings_pwr
	ui->screen_settings_pwr = lv_label_create(ui->screen_settings, NULL);
	lv_label_set_text(ui->screen_settings_pwr, "100%");
	lv_label_set_align(ui->screen_settings_pwr, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_settings_pwr, 290, 8);
	lv_obj_set_width(ui->screen_settings_pwr, 30);

	//Set style for screen_settings_pwr. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_settings_pwr_main_default;
	lv_style_reset(&style_screen_settings_pwr_main_default);
	lv_style_set_radius(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_8);
	lv_style_set_text_letter_space(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_settings_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_settings_pwr, LV_LABEL_PART_MAIN, &style_screen_settings_pwr_main_default);


	//Init events for screen.
	events_init_screen_settings(ui);
}
