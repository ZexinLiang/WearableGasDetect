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
#include "buzzer.h"

uint8_t lvgl_task_flag = 0;
extern lv_ui guider_ui;
extern DataTab_TypeDef data;
extern uint8_t volInPercent;
extern uint8_t CH582IdleCnt;
extern uint8_t CH582Cnned;
ERR_TypeDef errmsg;

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

float tempT = 40,co2T = 5000,rhT = 20,gasrT = 20000,o2T = 18.6;
uint8_t serverAlarm = 0;
uint8_t BzOnFlag = 0;
void updateErrMsg(){
    errmsg.temperr = (data.temp2>tempT)||(serverAlarm&0x01)?1:0;
    //errmsg.co2err = (data.CO2>co2T)||(serverAlarm&0x02)?1:0;
    errmsg.co2err = (data.CO2>co2T)?1:0;
    errmsg.rherr = (data.humi2<rhT)||(serverAlarm&0x04)?1:0;
    errmsg.gasrerr = (data.gasRes<gasrT)||(serverAlarm&0x08)?1:0;
    errmsg.o2err = (data.o2<o2T)?1:0;
    if(errmsg.co2err||errmsg.rherr||errmsg.gasrerr||errmsg.o2err)
        BzOnFlag = 1;
    else BzOnFlag = 0;
}


uint8_t divInS = 0;
uint8_t divIn5S = 0;

uint8_t bzOnOff = 0;
void TIM2_IRQHandler()//50ms
{

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {//��������
        bool is_on = lv_switch_get_state(guider_ui.screen_alarmst_silence_sw);
        bool is_datam_on = lv_switch_get_state(guider_ui.screen_alarmst_datam_sw);
        bool is_data_update_on = lv_switch_get_state(guider_ui.screen_alarmst_esc_sw);
        if(!is_on)
        {
        if(BzOnFlag)
        {
            if(bzOnOff)
                BuzzerChange( 100-1, 480-1, 40 );
            else
                BuzzerChange( 100-1, 480-1, 0 );
            bzOnOff = !bzOnOff;
        }
        else {
            BuzzerChange( 100-1, 480-1, 0 );
        }}
        else BuzzerChange( 100-1, 480-1, 0 );

        //�ػ����
        //powerOffDetect();

        //��Ļ�����޸�
        if(lvgl_task_flag&&is_datam_on){
            if(errmsg.rherr)lv_label_set_text_fmt(guider_ui.screen_rtdata_rhu, "!%d%%",data.humi2);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_rhu, "%d%%",data.humi2);
            if(errmsg.temperr) lv_label_set_text_fmt(guider_ui.screen_rtdata_temp, "!%d*C",(int32_t)data.temp2);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_temp, "%d*C",(int32_t)data.temp2);
            if(errmsg.preserr) lv_label_set_text_fmt(guider_ui.screen_rtdata_pres, "!%dPa",(int32_t)data.pres1);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_pres, "%dPa",(int32_t)data.pres1);
            if(errmsg.gasrerr) lv_label_set_text_fmt(guider_ui.screen_rtdata_gasr, "!%d",(int32_t)data.gasRes);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_gasr, "%d",(int32_t)data.gasRes);
            if(errmsg.co2err) lv_label_set_text_fmt(guider_ui.screen_rtdata_co2,"!%dppm",data.CO2);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_co2,"%dppm",data.CO2);
            if(errmsg.o2err) lv_label_set_text_fmt(guider_ui.screen_rtdata_oo2,"!%d%%",(int32_t)data.o2);
            else lv_label_set_text_fmt(guider_ui.screen_rtdata_oo2,"%d%%",(int32_t)data.o2);
        }
        divInS = (divInS+1)%20;
        if(!divInS){//1sִ�е�����
            //�����ϱ�
            if(is_data_update_on)
                m780eg_perioTask();
            //O2Ũ�ȹ���
            data.o2 = 20.9 - 3.5f*((float)data.CO2/10000)+0.02f*(data.temp2)+0.005f*(1013-data.pres1/100);
            //�ж��Ƿ�Σ��ֵ
            updateErrMsg();

            //�ж��Ƿ����Ӵӻ�
            CH582IdleCnt = (CH582IdleCnt+1)%5;
            if(CH582IdleCnt == 4){
                CH582Cnned = 0;
            }
            if(CH582Cnned) lv_label_set_text(guider_ui.screen_sub_device_cnn_state, "Connected");
            else lv_label_set_text(guider_ui.screen_sub_device_cnn_state, "Disconnected");

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
