/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Black(lv_ui *ui){

	//Write codes Black
	ui->Black = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for Black
	static lv_style_t style_Black_main;
	lv_style_reset(&style_Black_main);

	//Write style state: LV_STATE_DEFAULT for style_Black_main
	lv_style_set_bg_color(&style_Black_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_Black_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Black, LV_OBJ_PART_MAIN, &style_Black_main);

	//Write codes Black_canvas_1
	ui->Black_canvas_1 = lv_canvas_create(ui->Black, NULL);

	//Write style LV_CANVAS_PART_MAIN for Black_canvas_1
	static lv_style_t style_Black_canvas_1_main;
	lv_style_reset(&style_Black_canvas_1_main);

	//Write style state: LV_STATE_DEFAULT for style_Black_canvas_1_main
	lv_style_set_shadow_color(&style_Black_canvas_1_main, LV_STATE_DEFAULT, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_width(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_opa(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_spread(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_x(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_ofs_y(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_recolor(&style_Black_canvas_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor_opa(&style_Black_canvas_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Black_canvas_1, LV_CANVAS_PART_MAIN, &style_Black_canvas_1_main);
	lv_obj_set_pos(ui->Black_canvas_1, 0, 0);
	lv_obj_set_size(ui->Black_canvas_1, 320, 240);
	static lv_color_t buf_Black_canvas_1[320*240*4];
	lv_canvas_set_buffer(ui->Black_canvas_1, buf_Black_canvas_1, 320, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
	lv_canvas_fill_bg(ui->Black_canvas_1, lv_color_make(0x00, 0x00, 0x00), 255);

	//Init events for screen
	events_init_Black(ui);
}