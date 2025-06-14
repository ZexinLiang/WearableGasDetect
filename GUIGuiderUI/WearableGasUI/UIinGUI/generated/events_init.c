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


static void screen_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_1_del == true) {
	          setup_scr_screen_1(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
	        guider_ui.screen_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen, screen_event_handler);
}

static void screen_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_2_del == true) {
	          setup_scr_screen_2(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
	        guider_ui.screen_1_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_1_cont_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	default:
		break;
	}
}
static void screen_1_label_1_event_handler (lv_obj_t *obj, lv_event_t event) 
{
	switch (event) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_2_del == true) {
	          setup_scr_screen_2(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, true);
	        guider_ui.screen_1_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_1(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_1, screen_1_event_handler);
	lv_obj_set_event_cb(ui->screen_1_cont_1, screen_1_cont_1_event_handler);
	lv_obj_set_event_cb(ui->screen_1_label_1, screen_1_label_1_event_handler);
}


void events_init(lv_ui *ui)
{

}
