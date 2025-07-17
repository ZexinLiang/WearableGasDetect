/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void screen_none_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_pwon_del == true) {
	          setup_scr_screen_pwon(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_pwon, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_none_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_none(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_none, screen_none_event_handler);
}

static void screen_pwon_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_pwon_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_pwon_cont_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	default:
		break;
	}
}
static void screen_pwon_label_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_rtdata_del == true) {
	          setup_scr_screen_rtdata(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_rtdata, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
	        guider_ui.screen_pwon_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_pwon_img_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_pwon_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_pwon(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_pwon, screen_pwon_event_handler);
	lv_obj_set_event_cb(ui->screen_pwon_cont_1, screen_pwon_cont_1_event_handler);
	lv_obj_set_event_cb(ui->screen_pwon_label_1, screen_pwon_label_1_event_handler);
	lv_obj_set_event_cb(ui->screen_pwon_img_1, screen_pwon_img_1_event_handler);
}

static void screen_settings_page_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	default:
		break;
	}
}
static void screen_settings_btn_sub_device_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_sub_device_del == true) {
	          setup_scr_screen_sub_device(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_sub_device, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_settings_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_settings_btn_network_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_network_del == true) {
	          setup_scr_screen_network(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_network, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_settings_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_settings_btn_rtdata_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_rtdata_del == true) {
	          setup_scr_screen_rtdata(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_rtdata, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_settings_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_settings_btn_devicest_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_devicest_del == true) {
	          setup_scr_screen_devicest(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_devicest, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_settings_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_settings_btn_alarmset_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_alarmst_del == true) {
	          setup_scr_screen_alarmst(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_alarmst, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_settings_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_settings(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_settings_page, screen_settings_page_event_handler);
	lv_obj_set_event_cb(ui->screen_settings_btn_sub_device, screen_settings_btn_sub_device_event_handler);
	lv_obj_set_event_cb(ui->screen_settings_btn_network, screen_settings_btn_network_event_handler);
	lv_obj_set_event_cb(ui->screen_settings_btn_rtdata, screen_settings_btn_rtdata_event_handler);
	lv_obj_set_event_cb(ui->screen_settings_btn_devicest, screen_settings_btn_devicest_event_handler);
	lv_obj_set_event_cb(ui->screen_settings_btn_alarmset, screen_settings_btn_alarmset_event_handler);
}

static void screen_rtdata_menu_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_rtdata_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_rtdata(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_rtdata_menu, screen_rtdata_menu_event_handler);
}

static void screen_devicest_menu_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_devicest_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_devicest_start_st_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_devicest(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_devicest_menu, screen_devicest_menu_event_handler);
	lv_obj_set_event_cb(ui->screen_devicest_start_st, screen_devicest_start_st_event_handler);
}

static void screen_alarmst_menu_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_NONE, 100, 100, false);
	        guider_ui.screen_alarmst_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_alarmst_mm_btn_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	default:
		break;
	}
}
void events_init_screen_alarmst(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_alarmst_menu, screen_alarmst_menu_event_handler);
	lv_obj_set_event_cb(ui->screen_alarmst_mm_btn, screen_alarmst_mm_btn_event_handler);
}

static void screen_network_menu_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_network_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_network_btn_cnn_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_network(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_network_menu, screen_network_menu_event_handler);
	lv_obj_set_event_cb(ui->screen_network_btn_cnn, screen_network_btn_cnn_event_handler);
}

static void screen_sub_device_menu_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_settings_del == true) {
	          setup_scr_screen_settings(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false);
	        guider_ui.screen_sub_device_del = false;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_sub_device_btn_dcnn_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void screen_sub_device_btn_cnn_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_sub_device(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_sub_device_menu, screen_sub_device_menu_event_handler);
	lv_obj_set_event_cb(ui->screen_sub_device_btn_dcnn, screen_sub_device_btn_dcnn_event_handler);
	lv_obj_set_event_cb(ui->screen_sub_device_btn_cnn, screen_sub_device_btn_cnn_event_handler);
}


void events_init(lv_ui *ui)
{

}
