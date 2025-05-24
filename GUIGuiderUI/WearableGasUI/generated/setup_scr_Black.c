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
	lv_style_set_bg_color(&style_Black_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_Black_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Black, LV_OBJ_PART_MAIN, &style_Black_main);

	//Init events for screen
	events_init_Black(ui);
}