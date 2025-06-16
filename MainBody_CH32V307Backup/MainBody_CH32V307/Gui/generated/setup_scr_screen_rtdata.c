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


void setup_scr_screen_rtdata(lv_ui *ui){
	//Widget: screen_rtdata
	ui->screen_rtdata = lv_obj_create(NULL, NULL);
	kb = lv_keyboard_create(ui->screen_rtdata, NULL);
	lv_obj_set_event_cb(kb, kb_event_cb);
	lv_obj_set_hidden(kb, true);
	lv_obj_set_size(ui->screen_rtdata, 320, 240);

	//Set style for screen_rtdata. Part: LV_OBJ_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_main_default;
	lv_style_reset(&style_screen_rtdata_main_default);
	lv_style_set_bg_opa(&style_screen_rtdata_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata, LV_OBJ_PART_MAIN, &style_screen_rtdata_main_default);


	//Widget: screen_rtdata_temp_txt
	ui->screen_rtdata_temp_txt = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_temp_txt, "Temp:");
	lv_label_set_align(ui->screen_rtdata_temp_txt, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_temp_txt, 29, 42);
	lv_obj_set_width(ui->screen_rtdata_temp_txt, 70);

	//Set style for screen_rtdata_temp_txt. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_temp_txt_main_default;
	lv_style_reset(&style_screen_rtdata_temp_txt_main_default);
	lv_style_set_radius(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_temp_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_temp_txt, LV_LABEL_PART_MAIN, &style_screen_rtdata_temp_txt_main_default);


	//Widget: screen_rtdata_rh_txt
	ui->screen_rtdata_rh_txt = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_rh_txt, "RH:");
	lv_label_set_align(ui->screen_rtdata_rh_txt, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_rh_txt, 29, 73);
	lv_obj_set_width(ui->screen_rtdata_rh_txt, 70);

	//Set style for screen_rtdata_rh_txt. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_rh_txt_main_default;
	lv_style_reset(&style_screen_rtdata_rh_txt_main_default);
	lv_style_set_radius(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_rh_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_rh_txt, LV_LABEL_PART_MAIN, &style_screen_rtdata_rh_txt_main_default);


	//Widget: screen_rtdata_pres_txt
	ui->screen_rtdata_pres_txt = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_pres_txt, "Pres:");
	lv_label_set_align(ui->screen_rtdata_pres_txt, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_pres_txt, 29, 104);
	lv_obj_set_width(ui->screen_rtdata_pres_txt, 70);

	//Set style for screen_rtdata_pres_txt. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_pres_txt_main_default;
	lv_style_reset(&style_screen_rtdata_pres_txt_main_default);
	lv_style_set_radius(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_pres_txt_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_pres_txt, LV_LABEL_PART_MAIN, &style_screen_rtdata_pres_txt_main_default);


	//Widget: screen_rtdata_temp
	ui->screen_rtdata_temp = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_temp, "25.12");
	lv_label_set_align(ui->screen_rtdata_temp, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_temp, 110, 42);
	lv_obj_set_width(ui->screen_rtdata_temp, 100);

	//Set style for screen_rtdata_temp. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_temp_main_default;
	lv_style_reset(&style_screen_rtdata_temp_main_default);
	lv_style_set_radius(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_temp_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_temp, LV_LABEL_PART_MAIN, &style_screen_rtdata_temp_main_default);


	//Widget: screen_rtdata_rhu
	ui->screen_rtdata_rhu = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_rhu, "60%");
	lv_label_set_align(ui->screen_rtdata_rhu, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_rhu, 110, 73);
	lv_obj_set_width(ui->screen_rtdata_rhu, 100);

	//Set style for screen_rtdata_rhu. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_rhu_main_default;
	lv_style_reset(&style_screen_rtdata_rhu_main_default);
	lv_style_set_radius(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_rhu_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_rhu, LV_LABEL_PART_MAIN, &style_screen_rtdata_rhu_main_default);


	//Widget: screen_rtdata_menu
	ui->screen_rtdata_menu = lv_btn_create(ui->screen_rtdata, NULL);
	ui->screen_rtdata_menu_label = lv_label_create(ui->screen_rtdata_menu, NULL);
	lv_label_set_text(ui->screen_rtdata_menu_label, "MENU");
	lv_label_set_align(ui->screen_rtdata_menu_label, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_menu, 8, 8);
	lv_obj_set_size(ui->screen_rtdata_menu, 45, 30);

	//Set style for screen_rtdata_menu. Part: LV_BTN_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_menu_main_default;
	lv_style_reset(&style_screen_rtdata_menu_main_default);
	lv_style_set_text_color(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
	lv_style_set_border_width(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, 50);
	lv_style_set_shadow_width(&style_screen_rtdata_menu_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_menu, LV_BTN_PART_MAIN, &style_screen_rtdata_menu_main_default);


	//Widget: screen_rtdata_pres
	ui->screen_rtdata_pres = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_pres, "101.99kPa");
	lv_label_set_align(ui->screen_rtdata_pres, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_pres, 110, 104);
	lv_obj_set_width(ui->screen_rtdata_pres, 100);

	//Set style for screen_rtdata_pres. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_pres_main_default;
	lv_style_reset(&style_screen_rtdata_pres_main_default);
	lv_style_set_radius(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_17);
	lv_style_set_text_letter_space(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_pres_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_pres, LV_LABEL_PART_MAIN, &style_screen_rtdata_pres_main_default);


	//Widget: screen_rtdata_pwr
	ui->screen_rtdata_pwr = lv_label_create(ui->screen_rtdata, NULL);
	lv_label_set_text(ui->screen_rtdata_pwr, "100%");
	lv_label_set_align(ui->screen_rtdata_pwr, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(ui->screen_rtdata_pwr, 290, 8);
	lv_obj_set_width(ui->screen_rtdata_pwr, 30);

	//Set style for screen_rtdata_pwr. Part: LV_LABEL_PART_MAIN, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_pwr_main_default;
	lv_style_reset(&style_screen_rtdata_pwr_main_default);
	lv_style_set_radius(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	lv_style_set_text_font(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, &lv_font_montserratMedium_8);
	lv_style_set_text_letter_space(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 2);
	lv_style_set_text_line_space(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_opa(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_style_set_shadow_width(&style_screen_rtdata_pwr_main_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_pwr, LV_LABEL_PART_MAIN, &style_screen_rtdata_pwr_main_default);


	//Widget: screen_rtdata_pwr_pic
	ui->screen_rtdata_pwr_pic = lv_bar_create(ui->screen_rtdata, NULL);
	lv_bar_set_anim_time(ui->screen_rtdata_pwr_pic, 1000);
	lv_bar_set_range(ui->screen_rtdata_pwr_pic, 0, 100);
	lv_bar_set_value(ui->screen_rtdata_pwr_pic, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_rtdata_pwr_pic, 265, 9);
	lv_obj_set_size(ui->screen_rtdata_pwr_pic, 20, 6);

	//Set style for screen_rtdata_pwr_pic. Part: LV_BAR_PART_BG, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_pwr_pic_bg_default;
	lv_style_reset(&style_screen_rtdata_pwr_pic_bg_default);
	lv_style_set_bg_opa(&style_screen_rtdata_pwr_pic_bg_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_rtdata_pwr_pic_bg_default, LV_STATE_DEFAULT, lv_color_hex(0xd4d7d9));
	lv_style_set_radius(&style_screen_rtdata_pwr_pic_bg_default, LV_STATE_DEFAULT, 10);
	lv_style_set_shadow_width(&style_screen_rtdata_pwr_pic_bg_default, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_rtdata_pwr_pic, LV_BAR_PART_BG, &style_screen_rtdata_pwr_pic_bg_default);

	//Set style for screen_rtdata_pwr_pic. Part: LV_BAR_PART_INDIC, State: LV_STATE_DEFAULT
	static lv_style_t style_screen_rtdata_pwr_pic_indic_default;
	lv_style_reset(&style_screen_rtdata_pwr_pic_indic_default);
	lv_style_set_bg_opa(&style_screen_rtdata_pwr_pic_indic_default, LV_STATE_DEFAULT, 255);
	lv_style_set_bg_color(&style_screen_rtdata_pwr_pic_indic_default, LV_STATE_DEFAULT, lv_color_hex(0x01a2b1));
	lv_style_set_radius(&style_screen_rtdata_pwr_pic_indic_default, LV_STATE_DEFAULT, 10);
	lv_obj_add_style(ui->screen_rtdata_pwr_pic, LV_BAR_PART_INDIC, &style_screen_rtdata_pwr_pic_indic_default);


	//Init events for screen.
	events_init_screen_rtdata(ui);
}
