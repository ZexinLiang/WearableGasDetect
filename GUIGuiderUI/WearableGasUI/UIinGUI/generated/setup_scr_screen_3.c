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


void setup_scr_screen_3(lv_ui *ui){
	//Widget: screen_3
	ui->screen_3 = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen_3, 320, 240);

	//Set style for screen_3. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_3_main_default;
	lv_style_reset(&style_screen_3_main_default);
	lv_style_set_bg_opa(&style_screen_3_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_3, LV_OBJ_PART_MAIN, &style_screen_3_main_default);


	//Widget: screen_3_cont_1
	ui->screen_3_cont_1 = lv_cont_create(ui->screen_3, NULL);
	lv_obj_set_click(ui->screen_3_cont_1, false);
	lv_cont_set_layout(ui->screen_3_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_3_cont_1, LV_FIT_NONE);
	lv_obj_set_pos(ui->screen_3_cont_1, 0, -1);
	lv_obj_set_size(ui->screen_3_cont_1, 320, 400);

	//Set style for screen_3_cont_1. Part: LV_CONT_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_3_cont_1_main_default;
	lv_style_reset(&style_screen_3_cont_1_main_default);
	lv_style_set_bg_opa(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x999999));
	lv_style_set_radius(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_3_cont_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_3_cont_1, LV_CONT_PART_MAIN, &style_screen_3_cont_1_main_default);

	//Widget: screen_3_btn_1
	ui->screen_3_btn_1 = lv_btn_create(ui->screen_3_cont_1, NULL);
	ui->screen_3_btn_1_label = lv_label_create(ui->screen_3_btn_1, NULL);
	lv_label_set_text(ui->screen_3_btn_1_label, "default");
	lv_label_set_align(ui->screen_3_btn_1_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_3_btn_1, 120, 94);
	lv_obj_set_size(ui->screen_3_btn_1, 100, 50);

	//Set style for screen_3_btn_1. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_3_btn_1_main_default;
	lv_style_reset(&style_screen_3_btn_1_main_default);
	lv_style_set_text_color(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_3_btn_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_3_btn_1, LV_BTN_PART_MAIN, &style_screen_3_btn_1_main_default);


	//Init events for screen.
	events_init_screen_3(ui);
}
