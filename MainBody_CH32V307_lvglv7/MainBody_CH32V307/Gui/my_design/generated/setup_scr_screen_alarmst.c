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


void setup_scr_screen_alarmst(lv_ui *ui){
	//Widget: screen_alarmst
	ui->screen_alarmst = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen_alarmst, 320, 240);

	//Set style for screen_alarmst. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_alarmst_main_default;
	lv_style_reset(&style_screen_alarmst_main_default);
	lv_style_set_bg_opa(&style_screen_alarmst_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_alarmst, LV_OBJ_PART_MAIN, &style_screen_alarmst_main_default);


	//Widget: screen_alarmst_label_1
	ui->screen_alarmst_label_1 = lv_label_create(ui->screen_alarmst, NULL);
	lv_label_set_text(ui->screen_alarmst_label_1, "100%");
	lv_label_set_align(ui->screen_alarmst_label_1, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_alarmst_label_1, 290, 8);
	lv_obj_set_width(ui->screen_alarmst_label_1, 30);

	//Set style for screen_alarmst_label_1. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_alarmst_label_1_main_default;
	lv_style_reset(&style_screen_alarmst_label_1_main_default);
	lv_style_set_radius(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_8);
	lv_style_set_text_letter_space(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_alarmst_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_alarmst_label_1, LV_LABEL_PART_MAIN, &style_screen_alarmst_label_1_main_default);


	//Widget: screen_alarmst_bar_1
	ui->screen_alarmst_bar_1 = lv_bar_create(ui->screen_alarmst, NULL);
	lv_bar_set_anim_time(ui->screen_alarmst_bar_1, 1000);
	lv_bar_set_range(ui->screen_alarmst_bar_1, 0, 100);
	lv_bar_set_value(ui->screen_alarmst_bar_1, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_alarmst_bar_1, 265, 9);
	lv_obj_set_size(ui->screen_alarmst_bar_1, 20, 6);

	//Set style for screen_alarmst_bar_1. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_alarmst_bar_1_bg_default;
	lv_style_reset(&style_screen_alarmst_bar_1_bg_default);
	lv_style_set_bg_opa(&style_screen_alarmst_bar_1_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_alarmst_bar_1_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_alarmst_bar_1_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_alarmst_bar_1_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_alarmst_bar_1, LV_BAR_PART_BG, &style_screen_alarmst_bar_1_bg_default);

	//Set style for screen_alarmst_bar_1. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_alarmst_bar_1_indic_default;
	lv_style_reset(&style_screen_alarmst_bar_1_indic_default);
	lv_style_set_bg_opa(&style_screen_alarmst_bar_1_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_alarmst_bar_1_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_alarmst_bar_1_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_alarmst_bar_1, LV_BAR_PART_INDIC, &style_screen_alarmst_bar_1_indic_default);


	//Widget: screen_alarmst_menu
	ui->screen_alarmst_menu = lv_btn_create(ui->screen_alarmst, NULL);
	ui->screen_alarmst_menu_label = lv_label_create(ui->screen_alarmst_menu, NULL);
	lv_label_set_text(ui->screen_alarmst_menu_label, "MENU");
	lv_label_set_align(ui->screen_alarmst_menu_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_alarmst_menu, 8, 8);
	lv_obj_set_size(ui->screen_alarmst_menu, 45, 30);

	//Set style for screen_alarmst_menu. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_alarmst_menu_main_default;
	lv_style_reset(&style_screen_alarmst_menu_main_default);
	lv_style_set_text_color(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_alarmst_menu_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_alarmst_menu, LV_BTN_PART_MAIN, &style_screen_alarmst_menu_main_default);


	//Init events for screen.
	events_init_screen_alarmst(ui);
}
