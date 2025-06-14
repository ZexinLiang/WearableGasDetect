/*
 * periodicalTask.c
 *
 *  Created on: 2025��5��6��
 *      Author: 86135
 */
#include "periodicalTask.h"
#include "m780eg.h"

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
void TIM2_IRQHandler()//50ms
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        //powerOffDetect();//�ػ����
        divInS = (divInS+1)%20;
        if(!divInS){//1sִ�е�����
            m780eg_perioTask();
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
