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
