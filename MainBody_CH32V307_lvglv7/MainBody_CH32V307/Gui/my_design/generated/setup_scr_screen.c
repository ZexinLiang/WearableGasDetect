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

#if LV_USE_KEYBOARD
static lv_obj_t * kb;
static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
	lv_keyboard_def_event_cb(event_kb, event);
	if(event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL){
		lv_obj_set_hidden(event_kb, true);
	}
}

static void text_area_event_cb(lv_obj_t* ta, lv_event_t event)
{
	if (event == LV_EVENT_FOCUSED || event == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_set_hidden(kb, false);
	}
	if (event == LV_EVENT_CANCEL || event == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_set_hidden(kb, true);
	}
}
#endif


void setup_scr_screen(lv_ui *ui){
	//Widget: screen
	ui->screen = lv_obj_create(NULL, NULL);
	kb = lv_keyboard_create(ui->screen, NULL);
	lv_obj_set_event_cb(kb, kb_event_cb);
	lv_obj_set_hidden(kb, true);
	lv_obj_set_size(ui->screen, 320, 240);

	//Set style for screen. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_main_default;
	lv_style_reset(&style_screen_main_default);
	lv_style_set_bg_opa(&style_screen_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_obj_add_style(ui->screen, LV_OBJ_PART_MAIN, &style_screen_main_default);


	//Widget: screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen, NULL);
	lv_obj_set_click(ui->screen_img_1, true);
	lv_img_set_src(ui->screen_img_1, &_wchlogo_alpha_149x44);
	lv_img_set_pivot(ui->screen_img_1, 50,50);
	lv_img_set_angle(ui->screen_img_1, 0);
	lv_obj_set_pos(ui->screen_img_1, 85.5, 98);
	lv_obj_set_size(ui->screen_img_1, 149, 44);

	//Set style for screen_img_1. Part: LV_IMG_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_img_1_main_default;
	lv_style_reset(&style_screen_img_1_main_default);
	lv_style_set_image_opa(&style_screen_img_1_main_default, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_1, LV_IMG_PART_MAIN, &style_screen_img_1_main_default);


	//Init events for screen.
	events_init_screen(ui);
}
