/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

typedef struct
{
  
    lv_obj_t *screen_none;
    bool screen_none_del;
    lv_obj_t *g_kb_screen_none;
    lv_obj_t *screen_pwon;
    bool screen_pwon_del;
    lv_obj_t *g_kb_screen_pwon;
    lv_obj_t *screen_pwon_cont_1;
    lv_obj_t *screen_pwon_label_1;
    lv_obj_t *screen_pwon_img_1;
    lv_obj_t *screen_settings;
    bool screen_settings_del;
    lv_obj_t *g_kb_screen_settings;
    lv_obj_t *screen_settings_page;
    lv_obj_t *screen_settings_btn_sub_device;
    lv_obj_t *screen_settings_btn_sub_device_label;
    lv_obj_t *screen_settings_btn_network;
    lv_obj_t *screen_settings_btn_network_label;
    lv_obj_t *screen_settings_btn_rtdata;
    lv_obj_t *screen_settings_btn_rtdata_label;
    lv_obj_t *screen_settings_btn_devicest;
    lv_obj_t *screen_settings_btn_devicest_label;
    lv_obj_t *screen_settings_btn_alarmset;
    lv_obj_t *screen_settings_btn_alarmset_label;
    lv_obj_t *screen_settings_pwr_pic;
    lv_obj_t *screen_settings_pwr;
    lv_obj_t *screen_rtdata;
    bool screen_rtdata_del;
    lv_obj_t *g_kb_screen_rtdata;
    lv_obj_t *screen_rtdata_menu;
    lv_obj_t *screen_rtdata_menu_label;
    lv_obj_t *screen_rtdata_pwr;
    lv_obj_t *screen_rtdata_pwr_pic;
    lv_obj_t *screen_rtdata_temp_txt;
    lv_obj_t *screen_rtdata_rh_txt;
    lv_obj_t *screen_rtdata_pres_txt;
    lv_obj_t *screen_rtdata_temp;
    lv_obj_t *screen_rtdata_rhu;
    lv_obj_t *screen_rtdata_pres;
    lv_obj_t *screen_rtdata_gasr_txt;
    lv_obj_t *screen_rtdata_o2_txt;
    lv_obj_t *screen_rtdata_oo2;
    lv_obj_t *screen_rtdata_co2_txt;
    lv_obj_t *screen_rtdata_co2;
    lv_obj_t *screen_rtdata_gasr;
    lv_obj_t *screen_rtdata_no2_txt;
    lv_obj_t *screen_rtdata_co_txt;
    lv_obj_t *screen_rtdata_coo;
    lv_obj_t *screen_rtdata_no2;
    lv_obj_t *screen_rtdata_loc_txt;
    lv_obj_t *screen_rtdata_loc;
    lv_obj_t *screen_devicest;
    bool screen_devicest_del;
    lv_obj_t *g_kb_screen_devicest;
    lv_obj_t *screen_devicest_pwr_pic;
    lv_obj_t *screen_devicest_pwr;
    lv_obj_t *screen_devicest_menu;
    lv_obj_t *screen_devicest_menu_label;
    lv_obj_t *screen_devicest_start_st;
    lv_obj_t *screen_devicest_start_st_label;
    lv_obj_t *screen_devicest_st_process;
    lv_obj_t *screen_devicest_st_msg;
    lv_obj_t *screen_alarmst;
    bool screen_alarmst_del;
    lv_obj_t *g_kb_screen_alarmst;
    lv_obj_t *screen_alarmst_label_1;
    lv_obj_t *screen_alarmst_bar_1;
    lv_obj_t *screen_alarmst_menu;
    lv_obj_t *screen_alarmst_menu_label;
    lv_obj_t *screen_alarmst_silence_sw;
    lv_obj_t *screen_alarmst_label_2;
    lv_obj_t *screen_alarmst_label_3;
    lv_obj_t *screen_alarmst_esc_sw;
    lv_obj_t *screen_alarmst_mm_btn;
    lv_obj_t *screen_alarmst_mm_btn_label;
    lv_obj_t *screen_alarmst_datam_sw;
    lv_obj_t *screen_alarmst_label_4;
    lv_obj_t *screen_network;
    bool screen_network_del;
    lv_obj_t *g_kb_screen_network;
    lv_obj_t *screen_network_label_1;
    lv_obj_t *screen_network_bar_1;
    lv_obj_t *screen_network_menu;
    lv_obj_t *screen_network_menu_label;
    lv_obj_t *screen_network_cnn_txt;
    lv_obj_t *screen_network_cnn_state;
    lv_obj_t *screen_network_btn_cnn;
    lv_obj_t *screen_network_btn_cnn_label;
    lv_obj_t *screen_network_server_msg;
    lv_obj_t *screen_sub_device;
    bool screen_sub_device_del;
    lv_obj_t *g_kb_screen_sub_device;
    lv_obj_t *screen_sub_device_label_1;
    lv_obj_t *screen_sub_device_bar_1;
    lv_obj_t *screen_sub_device_menu;
    lv_obj_t *screen_sub_device_menu_label;
    lv_obj_t *screen_sub_device_cnn_txt;
    lv_obj_t *screen_sub_device_cnn_state;
    lv_obj_t *screen_sub_device_btn_dcnn;
    lv_obj_t *screen_sub_device_btn_dcnn_label;
    lv_obj_t *screen_sub_device_btn_cnn;
    lv_obj_t *screen_sub_device_btn_cnn_label;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen_none(lv_ui *ui);
void setup_scr_screen_pwon(lv_ui *ui);
void setup_scr_screen_settings(lv_ui *ui);
void setup_scr_screen_rtdata(lv_ui *ui);
void setup_scr_screen_devicest(lv_ui *ui);
void setup_scr_screen_alarmst(lv_ui *ui);
void setup_scr_screen_network(lv_ui *ui);
void setup_scr_screen_sub_device(lv_ui *ui);
LV_IMG_DECLARE(_wchlogo_alpha_142x35);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_32)
LV_FONT_DECLARE(lv_font_montserratMedium_8)
LV_FONT_DECLARE(lv_font_montserratMedium_17)


#ifdef __cplusplus
}
#endif
#endif
