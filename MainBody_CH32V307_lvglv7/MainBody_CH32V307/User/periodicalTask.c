/*
 * periodicalTask.c
 *
 *  Created on: 2025年5月6日
 *      Author: 86135
 */
#include "periodicalTask.h"
#include "m780eg.h"

void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*
 * TIM2
 * 触发ADC电池电压采集
 * */
void TIM2_Trigger_Init(u16 arr, u16 psc){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 定时器基础配置
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // 配置TIM2触发输出为更新事件
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    // 使能定时器更新中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 配置NVIC中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 优先级高于ADC中断
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能定时器
    TIM_Cmd(TIM2, ENABLE);
}

uint8_t divInS = 0;
void TIM2_IRQHandler()//50ms
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        //powerOffDetect();//关机检测
        divInS = (divInS+1)%20;
        if(!divInS){//1s执行的任务
            m780eg_perioTask();
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
