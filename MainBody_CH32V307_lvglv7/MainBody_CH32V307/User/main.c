/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#include "debug.h"
#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_widgets.h"
#include "touch.h"
#include "ch9142.h"
#include "m780eg.h"
#include "periodicalTask.h"
#include "powerManage.h"
#include "events_init.h"
#include "gui_guider.h"
#include "buzzer.h"

extern _m_tp_dev tp_dev;
lv_ui guider_ui;

void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str)
{
    uint8_t i = 0;
    do
    {
       USART_SendData(pUSARTx, *(str+i));
       i++;
    }while(*(str+i) != '\0');
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	powerOn_Init_Execute();

	//device Init
    LCD_Init();
    ch9142_Init();
    m780eg_Init();
    powerMagage_Init();


    //Software Init
    TIM2_Trigger_Init(50000-1, 96-1);//50ms

    //Lvgl Init
	POINT_COLOR=RED;
	TP_Init();
	lv_init();
	lv_port_disp_init();
	//lv_demo_widgets();
	lv_port_indev_init();
	setup_ui(&guider_ui);
	events_init(&guider_ui);
    while(1)
    {
        //USART_SendData(USART3, 0x78);
        //USART_SendData(USART1, 0x78);
        lv_tick_inc(30);
        lv_task_handler();
        tp_dev.scan(0);
        Delay_Ms(30);
    }
}

