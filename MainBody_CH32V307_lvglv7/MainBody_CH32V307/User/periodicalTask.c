/*
 * periodicalTask.c
 *
 *  Created on: 2025��5��6��
 *      Author: 86135
 */
#include "periodicalTask.h"
#include "m780eg.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "ch582inn.h"

uint8_t lvgl_task_flag = 0;
extern lv_ui guider_ui;
extern DataTab_TypeDef data;
extern uint8_t volInPercent;

void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*
 * TIM2
 * ����ADC��ص�ѹ�ɼ�
 * */
void TIM2_Trigger_Init(u16 arr, u16 psc){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // ��ʱ����������
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // ����TIM2�������Ϊ�����¼�
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    // ʹ�ܶ�ʱ�������ж�
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // ����NVIC�ж����ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ���ȼ�����ADC�ж�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ʹ�ܶ�ʱ��
    TIM_Cmd(TIM2, ENABLE);
}

uint8_t divInS = 0;
uint8_t divIn5S = 0;
void TIM2_IRQHandler()//50ms
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        //�ػ����
        //powerOffDetect();

        //��Ļ�����޸�
        if(lvgl_task_flag){
            lv_label_set_text_fmt(guider_ui.screen_rtdata_rhu, "%d%%",data.humi2);
            lv_label_set_text_fmt(guider_ui.screen_rtdata_temp, "%d",data.temp1);
            lv_label_set_text_fmt(guider_ui.screen_rtdata_pres, "%dkPa",data.pres1);
        }
        divInS = (divInS+1)%20;
        if(!divInS){//1sִ�е�����
            //�����ϱ�
            m780eg_perioTask();
        }
        divIn5S = (divIn5S+1)%40;
        if(!divIn5S){//2S����
            lv_label_set_text_fmt(guider_ui.screen_settings_pwr, "%3d%%",volInPercent);
            lv_label_set_text_fmt(guider_ui.screen_devicest_pwr, "%3d%%",volInPercent);
            lv_label_set_text_fmt(guider_ui.screen_alarmst_label_1, "%3d%%",volInPercent);
            lv_label_set_text_fmt(guider_ui.screen_network_label_1, "%3d%%",volInPercent);
            lv_label_set_text_fmt(guider_ui.screen_rtdata_pwr, "%3d%%",volInPercent);
            lv_label_set_text_fmt(guider_ui.screen_sub_device_label_1, "%3d%%",volInPercent);
            lv_bar_set_value(guider_ui.screen_settings_pwr_pic, volInPercent, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_devicest_pwr_pic, volInPercent, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_alarmst_bar_1, volInPercent, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_network_bar_1, volInPercent, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_rtdata_pwr_pic, volInPercent, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_sub_device_bar_1, volInPercent, LV_ANIM_OFF);
        }

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
