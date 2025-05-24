/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"

void events_init(lv_ui *ui)
{
}

static void PreScreenevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.Black_del == true)
				setup_scr_Black(&guider_ui);
			lv_scr_load_anim(guider_ui.Black, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.PreScreen_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_PreScreen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->PreScreen, PreScreenevent_handler);
}

static void Blackevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	default:
		break;
	}
}

void events_init_Black(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->Black, Blackevent_handler);
}
