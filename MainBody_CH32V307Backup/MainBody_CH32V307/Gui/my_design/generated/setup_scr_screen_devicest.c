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


void setup_scr_screen_devicest(lv_ui *ui){
	//Widget: screen_devicest
	ui->screen_devicest = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen_devicest, 320, 240);

	//Set style for screen_devicest. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_main_default;
	lv_style_reset(&style_screen_devicest_main_default);
	lv_style_set_bg_opa(&style_screen_devicest_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest, LV_OBJ_PART_MAIN, &style_screen_devicest_main_default);


	//Widget: screen_devicest_pwr_pic
	ui->screen_devicest_pwr_pic = lv_bar_create(ui->screen_devicest, NULL);
	lv_bar_set_anim_time(ui->screen_devicest_pwr_pic, 1000);
	lv_bar_set_range(ui->screen_devicest_pwr_pic, 0, 100);
	lv_bar_set_value(ui->screen_devicest_pwr_pic, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_devicest_pwr_pic, 265, 9);
	lv_obj_set_size(ui->screen_devicest_pwr_pic, 20, 6);

	//Set style for screen_devicest_pwr_pic. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_pwr_pic_bg_default;
	lv_style_reset(&style_screen_devicest_pwr_pic_bg_default);
	lv_style_set_bg_opa(&style_screen_devicest_pwr_pic_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_pwr_pic_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_devicest_pwr_pic_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_devicest_pwr_pic_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_pwr_pic, LV_BAR_PART_BG, &style_screen_devicest_pwr_pic_bg_default);

	//Set style for screen_devicest_pwr_pic. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_pwr_pic_indic_default;
	lv_style_reset(&style_screen_devicest_pwr_pic_indic_default);
	lv_style_set_bg_opa(&style_screen_devicest_pwr_pic_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_pwr_pic_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_devicest_pwr_pic_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_devicest_pwr_pic, LV_BAR_PART_INDIC, &style_screen_devicest_pwr_pic_indic_default);


	//Widget: screen_devicest_pwr
	ui->screen_devicest_pwr = lv_label_create(ui->screen_devicest, NULL);
	lv_label_set_text(ui->screen_devicest_pwr, "100%");
	lv_label_set_align(ui->screen_devicest_pwr, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_devicest_pwr, 290, 8);
	lv_obj_set_width(ui->screen_devicest_pwr, 30);

	//Set style for screen_devicest_pwr. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_pwr_main_default;
	lv_style_reset(&style_screen_devicest_pwr_main_default);
	lv_style_set_radius(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_8);
	lv_style_set_text_letter_space(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_devicest_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_pwr, LV_LABEL_PART_MAIN, &style_screen_devicest_pwr_main_default);


	//Widget: screen_devicest_menu
	ui->screen_devicest_menu = lv_btn_create(ui->screen_devicest, NULL);
	ui->screen_devicest_menu_label = lv_label_create(ui->screen_devicest_menu, NULL);
	lv_label_set_text(ui->screen_devicest_menu_label, "MENU");
	lv_label_set_align(ui->screen_devicest_menu_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_devicest_menu, 8, 8);
	lv_obj_set_size(ui->screen_devicest_menu, 45, 30);

	//Set style for screen_devicest_menu. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_menu_main_default;
	lv_style_reset(&style_screen_devicest_menu_main_default);
	lv_style_set_text_color(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_devicest_menu_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_menu, LV_BTN_PART_MAIN, &style_screen_devicest_menu_main_default);


	//Widget: screen_devicest_start_st
	ui->screen_devicest_start_st = lv_btn_create(ui->screen_devicest, NULL);
	ui->screen_devicest_start_st_label = lv_label_create(ui->screen_devicest_start_st, NULL);
	lv_label_set_text(ui->screen_devicest_start_st_label, "Start\nself-test");
	lv_label_set_align(ui->screen_devicest_start_st_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_devicest_start_st, 110, 67);
	lv_obj_set_size(ui->screen_devicest_start_st, 100, 50);

	//Set style for screen_devicest_start_st. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_start_st_main_default;
	lv_style_reset(&style_screen_devicest_start_st_main_default);
	lv_style_set_text_color(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_devicest_start_st_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_start_st, LV_BTN_PART_MAIN, &style_screen_devicest_start_st_main_default);


	//Widget: screen_devicest_st_process
	ui->screen_devicest_st_process = lv_bar_create(ui->screen_devicest, NULL);
	lv_bar_set_anim_time(ui->screen_devicest_st_process, 1000);
	lv_bar_set_range(ui->screen_devicest_st_process, 0, 100);
	lv_bar_set_value(ui->screen_devicest_st_process, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_devicest_st_process, 40, 149);
	lv_obj_set_size(ui->screen_devicest_st_process, 240, 10);

	//Set style for screen_devicest_st_process. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_st_process_bg_default;
	lv_style_reset(&style_screen_devicest_st_process_bg_default);
	lv_style_set_bg_opa(&style_screen_devicest_st_process_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_st_process_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_devicest_st_process_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_devicest_st_process_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_st_process, LV_BAR_PART_BG, &style_screen_devicest_st_process_bg_default);

	//Set style for screen_devicest_st_process. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_st_process_indic_default;
	lv_style_reset(&style_screen_devicest_st_process_indic_default);
	lv_style_set_bg_opa(&style_screen_devicest_st_process_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_devicest_st_process_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_devicest_st_process_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_devicest_st_process, LV_BAR_PART_INDIC, &style_screen_devicest_st_process_indic_default);


	//Widget: screen_devicest_st_msg
	ui->screen_devicest_st_msg = lv_label_create(ui->screen_devicest, NULL);
	lv_label_set_text(ui->screen_devicest_st_msg, "msg:");
	lv_label_set_align(ui->screen_devicest_st_msg, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_devicest_st_msg, 40, 180);
	lv_obj_set_width(ui->screen_devicest_st_msg, 240);

	//Set style for screen_devicest_st_msg. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_devicest_st_msg_main_default;
	lv_style_reset(&style_screen_devicest_st_msg_main_default);
	lv_style_set_radius(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_devicest_st_msg_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_devicest_st_msg, LV_LABEL_PART_MAIN, &style_screen_devicest_st_msg_main_default);


	//Init events for screen.
	events_init_screen_devicest(ui);
}
