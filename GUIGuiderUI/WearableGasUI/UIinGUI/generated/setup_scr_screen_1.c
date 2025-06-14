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


void setup_scr_screen_1(lv_ui *ui){
	//Widget: screen_1
	ui->screen_1 = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen_1, 320, 240);

	//Set style for screen_1. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_main_default;
	lv_style_reset(&style_screen_1_main_default);
	lv_style_set_bg_opa(&style_screen_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1, LV_OBJ_PART_MAIN, &style_screen_1_main_default);


	//Widget: screen_1_cont_1
	ui->screen_1_cont_1 = lv_cont_create(ui->screen_1, NULL);
	lv_obj_set_click(ui->screen_1_cont_1, false);
	lv_cont_set_layout(ui->screen_1_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_1, LV_FIT_NONE);
	lv_obj_set_pos(ui->screen_1_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_1_cont_1, 320, 240);

	//Set style for screen_1_cont_1. Part: LV_CONT_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_cont_1_main_default;
	lv_style_reset(&style_screen_1_cont_1_main_default);
	lv_style_set_bg_opa(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_border_width(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x999999));
	lv_style_set_radius(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_cont_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_1, LV_CONT_PART_MAIN, &style_screen_1_cont_1_main_default);

	//Widget: screen_1_label_1
	ui->screen_1_label_1 = lv_label_create(ui->screen_1_cont_1, NULL);
	lv_label_set_text(ui->screen_1_label_1, "WearableGasDetect\nDevice");
	lv_label_set_align(ui->screen_1_label_1, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_1_label_1, 79, 137);
	lv_obj_set_width(ui->screen_1_label_1, 162);

	//Set style for screen_1_label_1. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_label_1_main_default;
	lv_style_reset(&style_screen_1_label_1_main_default);
	lv_style_set_radius(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_pad_top(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_label_1_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_1, LV_LABEL_PART_MAIN, &style_screen_1_label_1_main_default);


	//Widget: screen_1_img_1
	ui->screen_1_img_1 = lv_img_create(ui->screen_1_cont_1, NULL);
	lv_obj_set_click(ui->screen_1_img_1, true);
	lv_img_set_src(ui->screen_1_img_1, &_wchlogo_alpha_162x41);
	lv_img_set_pivot(ui->screen_1_img_1, 50,50);
	lv_img_set_angle(ui->screen_1_img_1, 0);
	lv_obj_set_pos(ui->screen_1_img_1, 79, 78);
	lv_obj_set_size(ui->screen_1_img_1, 162, 41);

	//Set style for screen_1_img_1. Part: LV_IMG_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_img_1_main_default;
	lv_style_reset(&style_screen_1_img_1_main_default);
	lv_style_set_image_opa(&style_screen_1_img_1_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_1, LV_IMG_PART_MAIN, &style_screen_1_img_1_main_default);


	//Init events for screen.
	events_init_screen_1(ui);
}
