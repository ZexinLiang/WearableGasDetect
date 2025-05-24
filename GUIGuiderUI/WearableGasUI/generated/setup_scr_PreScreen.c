/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_PreScreen(lv_ui *ui){

	//Write codes PreScreen
	ui->PreScreen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for PreScreen
	static lv_style_t style_PreScreen_main;
	lv_style_reset(&style_PreScreen_main);

	//Write style state: LV_STATE_DEFAULT for style_PreScreen_main
	lv_style_set_bg_color(&style_PreScreen_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_PreScreen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PreScreen, LV_OBJ_PART_MAIN, &style_PreScreen_main);

	//Write codes PreScreen_cont_1
	ui->PreScreen_cont_1 = lv_cont_create(ui->PreScreen, NULL);

	//Write style LV_CONT_PART_MAIN for PreScreen_cont_1
	static lv_style_t style_PreScreen_cont_1_main;
	lv_style_reset(&style_PreScreen_cont_1_main);

	//Write style state: LV_STATE_DEFAULT for style_PreScreen_cont_1_main
	lv_style_set_radius(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_color(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_width(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_opa(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_spread(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_x(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_y(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_PreScreen_cont_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PreScreen_cont_1, LV_CONT_PART_MAIN, &style_PreScreen_cont_1_main);
	lv_obj_set_pos(ui->PreScreen_cont_1, 0, 0);
	lv_obj_set_size(ui->PreScreen_cont_1, 320, 240);
	lv_obj_set_click(ui->PreScreen_cont_1, false);

	//Write codes PreScreen_img_1
	ui->PreScreen_img_1 = lv_img_create(ui->PreScreen_cont_1, NULL);

	//Write style LV_IMG_PART_MAIN for PreScreen_img_1
	static lv_style_t style_PreScreen_img_1_main;
	lv_style_reset(&style_PreScreen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_PreScreen_img_1_main
	lv_style_set_image_recolor(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PreScreen_img_1, LV_IMG_PART_MAIN, &style_PreScreen_img_1_main);
	lv_obj_set_pos(ui->PreScreen_img_1, 74, 91);
	lv_obj_set_size(ui->PreScreen_img_1, 173, 56);
	lv_obj_set_click(ui->PreScreen_img_1, true);
	lv_img_set_src(ui->PreScreen_img_1,&_WCHLogo_alpha_173x56);
	lv_img_set_pivot(ui->PreScreen_img_1, 50,50);
	lv_img_set_angle(ui->PreScreen_img_1, 0);
	lv_cont_set_layout(ui->PreScreen_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->PreScreen_cont_1, LV_FIT_NONE);

	//Init events for screen
	events_init_PreScreen(ui);
}