/*
 * Copyright 2025 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *Black;
	bool Black_del;
	lv_obj_t *Black_canvas_1;
	lv_obj_t *PreScreen;
	bool PreScreen_del;
	lv_obj_t *PreScreen_canvas_1;
	lv_obj_t *PreScreen_img_1;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_Black(lv_ui *ui);
void setup_scr_PreScreen(lv_ui *ui);
LV_IMG_DECLARE(_WCHLogo_alpha_173x56);

#ifdef __cplusplus
}
#endif
#endif