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


void setup_scr_screen(lv_ui *ui){
	//Widget: screen
	ui->screen = lv_obj_create(NULL, NULL);
	lv_obj_set_size(ui->screen, 320, 240);

	//Set style for screen. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_main_default;
	lv_style_reset(&style_screen_main_default);
	lv_style_set_bg_opa(&style_screen_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen, LV_OBJ_PART_MAIN, &style_screen_main_default);



	//Init events for screen.
	events_init_screen(ui);
}
