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
#include "ch9142cmd.h"
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
       while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
       USART_SendData(pUSARTx, *(str+i));
       i++;
    }while(*(str+i) != '\0');
}


#define CH9142_Config 0
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

#if CH9142_Config
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	USARTx_SendStr(USART1,"AT...\r\n");
	USARTx_SendStr(USART2,"AT...\r\n");
	delay_ms(500);
	USARTx_SendStr(USART1,"AT+BLEMODE=2\r\n");
	USARTx_SendStr(USART2,"AT+BLEMODE=1\r\n");
	delay_ms(500);
    //USARTx_SendStr(USART1,"AT+UXMOD=0\r\n");
    USARTx_SendStr(USART2,"AT+CONADD=E9:99:5F:72:AB:3C,000000\r\n");
    delay_ms(500);
    USARTx_SendStr(USART1,"AT+NAME=CH9142_UART0\r\n");
    USARTx_SendStr(USART2,"AT+NAME=CH9142_UART1\r\n");
    delay_ms(500);
    USARTx_SendStr(USART1,"AT+UART=115200,8,1,0,50\r\n");
    USARTx_SendStr(USART2,"AT+UART=115200,8,1,0,50\r\n");
    delay_ms(500);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
#endif

    while(1){
//        lv_tick_inc(30);
//        lv_task_handler();
//        tp_dev.scan(0);

        delay_ms(500);
        USART_SendData(USART1, 0x88);
        USART_SendData(USART2, 0x88);

    }
}
