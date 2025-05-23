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
	lv_style_set_bg_opa(&style_PreScreen_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->PreScreen, LV_OBJ_PART_MAIN, &style_PreScreen_main);

	//Write codes PreScreen_canvas_1
	ui->PreScreen_canvas_1 = lv_canvas_create(ui->PreScreen, NULL);

	//Write style LV_CANVAS_PART_MAIN for PreScreen_canvas_1
	static lv_style_t style_PreScreen_canvas_1_main;
	lv_style_reset(&style_PreScreen_canvas_1_main);

	//Write style state: LV_STATE_DEFAULT for style_PreScreen_canvas_1_main
	lv_style_set_shadow_color(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_width(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_opa(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_spread(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_x(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_y(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_recolor(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor_opa(&style_PreScreen_canvas_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PreScreen_canvas_1, LV_CANVAS_PART_MAIN, &style_PreScreen_canvas_1_main);
	lv_obj_set_pos(ui->PreScreen_canvas_1, 0, 0);
	lv_obj_set_size(ui->PreScreen_canvas_1, 320, 240);
	static lv_color_t buf_PreScreen_canvas_1[320*240*4];
	lv_canvas_set_buffer(ui->PreScreen_canvas_1, buf_PreScreen_canvas_1, 320, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
	lv_canvas_fill_bg(ui->PreScreen_canvas_1, lv_color_make(0x00, 0x00, 0x00), 255);

	//Write codes PreScreen_img_1
	ui->PreScreen_img_1 = lv_img_create(ui->PreScreen, NULL);

	//Write style LV_IMG_PART_MAIN for PreScreen_img_1
	static lv_style_t style_PreScreen_img_1_main;
	lv_style_reset(&style_PreScreen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_PreScreen_img_1_main
	lv_style_set_image_recolor(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_PreScreen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PreScreen_img_1, LV_IMG_PART_MAIN, &style_PreScreen_img_1_main);
	lv_obj_set_pos(ui->PreScreen_img_1, 73.5, 92);
	lv_obj_set_size(ui->PreScreen_img_1, 173, 56);
	lv_obj_set_click(ui->PreScreen_img_1, true);
	lv_img_set_src(ui->PreScreen_img_1,&_WCHLogo_alpha_173x56);
	lv_img_set_pivot(ui->PreScreen_img_1, 50,50);
	lv_img_set_angle(ui->PreScreen_img_1, 0);
}