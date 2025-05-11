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


void setup_scr_screen_1(lv_ui *ui){
	//Widget: screen_1
	ui->screen_1 = lv_obj_create(NULL, NULL);
	kb = lv_keyboard_create(ui->screen_1, NULL);
	lv_obj_set_event_cb(kb, kb_event_cb);
	lv_obj_set_hidden(kb, true);
	lv_obj_set_size(ui->screen_1, 320, 240);

	//Set style for screen_1. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_main_default;
	lv_style_reset(&style_screen_1_main_default);
	lv_style_set_bg_opa(&style_screen_1_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_main_default, LV_STATE_DEFAULT, lv_color_hex(0x484848));
	lv_obj_add_style(ui->screen_1, LV_OBJ_PART_MAIN, &style_screen_1_main_default);


	//Widget: screen_1_ta_1
	ui->screen_1_ta_1 = lv_textarea_create(ui->screen_1, NULL);
	lv_textarea_set_text(ui->screen_1_ta_1, "gas1:");
	lv_obj_set_event_cb(ui->screen_1_ta_1, text_area_event_cb);
	lv_obj_set_pos(ui->screen_1_ta_1, 12, 49);
	lv_obj_set_size(ui->screen_1_ta_1, 136, 25);

	//Set style for screen_1_ta_1. Part: LV_PAGE_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_1_bg_default;
	lv_style_reset(&style_screen_1_ta_1_bg_default);
	lv_style_set_text_color(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_width(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_pad_top(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_radius(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_ta_1_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_1, LV_PAGE_PART_BG, &style_screen_1_ta_1_bg_default);

	//Set style for screen_1_ta_1. Part: LV_PAGE_PART_SCROLLABLE, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_1_scrollable_default;
	lv_style_reset(&style_screen_1_ta_1_scrollable_default);
	lv_style_set_bg_opa(&style_screen_1_ta_1_scrollable_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_ta_1_scrollable_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_radius(&style_screen_1_ta_1_scrollable_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_1, LV_PAGE_PART_SCROLLABLE, &style_screen_1_ta_1_scrollable_default);


	//Widget: screen_1_ta_2
	ui->screen_1_ta_2 = lv_textarea_create(ui->screen_1, NULL);
	lv_textarea_set_text(ui->screen_1_ta_2, "gas2:");
	lv_obj_set_event_cb(ui->screen_1_ta_2, text_area_event_cb);
	lv_obj_set_pos(ui->screen_1_ta_2, 12, 92);
	lv_obj_set_size(ui->screen_1_ta_2, 136, 25);

	//Set style for screen_1_ta_2. Part: LV_PAGE_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_2_bg_default;
	lv_style_reset(&style_screen_1_ta_2_bg_default);
	lv_style_set_text_color(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_width(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_pad_top(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_radius(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_ta_2_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_2, LV_PAGE_PART_BG, &style_screen_1_ta_2_bg_default);

	//Set style for screen_1_ta_2. Part: LV_PAGE_PART_SCROLLABLE, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_2_scrollable_default;
	lv_style_reset(&style_screen_1_ta_2_scrollable_default);
	lv_style_set_bg_opa(&style_screen_1_ta_2_scrollable_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_ta_2_scrollable_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_radius(&style_screen_1_ta_2_scrollable_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_2, LV_PAGE_PART_SCROLLABLE, &style_screen_1_ta_2_scrollable_default);


	//Widget: screen_1_ta_3
	ui->screen_1_ta_3 = lv_textarea_create(ui->screen_1, NULL);
	lv_textarea_set_text(ui->screen_1_ta_3, "gas3:");
	lv_obj_set_event_cb(ui->screen_1_ta_3, text_area_event_cb);
	lv_obj_set_pos(ui->screen_1_ta_3, 12, 134);
	lv_obj_set_size(ui->screen_1_ta_3, 136, 25);

	//Set style for screen_1_ta_3. Part: LV_PAGE_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_3_bg_default;
	lv_style_reset(&style_screen_1_ta_3_bg_default);
	lv_style_set_text_color(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_width(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_pad_top(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_radius(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_ta_3_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_3, LV_PAGE_PART_BG, &style_screen_1_ta_3_bg_default);

	//Set style for screen_1_ta_3. Part: LV_PAGE_PART_SCROLLABLE, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_3_scrollable_default;
	lv_style_reset(&style_screen_1_ta_3_scrollable_default);
	lv_style_set_bg_opa(&style_screen_1_ta_3_scrollable_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_ta_3_scrollable_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_radius(&style_screen_1_ta_3_scrollable_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_3, LV_PAGE_PART_SCROLLABLE, &style_screen_1_ta_3_scrollable_default);


	//Widget: screen_1_ta_4
	ui->screen_1_ta_4 = lv_textarea_create(ui->screen_1, NULL);
	lv_textarea_set_text(ui->screen_1_ta_4, "gas4:");
	lv_obj_set_event_cb(ui->screen_1_ta_4, text_area_event_cb);
	lv_obj_set_pos(ui->screen_1_ta_4, 12, 178);
	lv_obj_set_size(ui->screen_1_ta_4, 136, 25);

	//Set style for screen_1_ta_4. Part: LV_PAGE_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_4_bg_default;
	lv_style_reset(&style_screen_1_ta_4_bg_default);
	lv_style_set_text_color(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_text_letter_space(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_width(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_pad_top(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_right(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 4);
	lv_style_set_radius(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_1_ta_4_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_4, LV_PAGE_PART_BG, &style_screen_1_ta_4_bg_default);

	//Set style for screen_1_ta_4. Part: LV_PAGE_PART_SCROLLABLE, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_ta_4_scrollable_default;
	lv_style_reset(&style_screen_1_ta_4_scrollable_default);
	lv_style_set_bg_opa(&style_screen_1_ta_4_scrollable_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_ta_4_scrollable_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_radius(&style_screen_1_ta_4_scrollable_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_ta_4, LV_PAGE_PART_SCROLLABLE, &style_screen_1_ta_4_scrollable_default);


	//Widget: screen_1_bar_1
	ui->screen_1_bar_1 = lv_bar_create(ui->screen_1, NULL);
	lv_bar_set_anim_time(ui->screen_1_bar_1, 1000);
	lv_bar_set_range(ui->screen_1_bar_1, 0, 100);
	lv_bar_set_value(ui->screen_1_bar_1, 70, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_1_bar_1, 280, 14);
	lv_obj_set_size(ui->screen_1_bar_1, 29, 6);

	//Set style for screen_1_bar_1. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_bar_1_bg_default;
	lv_style_reset(&style_screen_1_bar_1_bg_default);
	lv_style_set_bg_opa(&style_screen_1_bar_1_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_bar_1_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_1_bar_1_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_1_bar_1_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_bar_1, LV_BAR_PART_BG, &style_screen_1_bar_1_bg_default);

	//Set style for screen_1_bar_1. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_1_bar_1_indic_default;
	lv_style_reset(&style_screen_1_bar_1_indic_default);
	lv_style_set_bg_opa(&style_screen_1_bar_1_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_1_bar_1_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_1_bar_1_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_1_bar_1, LV_BAR_PART_INDIC, &style_screen_1_bar_1_indic_default);


}
