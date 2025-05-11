/*
 * ch9142.c
 *
 *  Created on: 2025年5月6日
 *      Author: 梁泽欣
 */
#include "ch9142.h"
#include "debug.h"
#include "string.h"
#include "stdint.h"

#define U1Rx_MAX_LEN 40
#define U2Rx_MAX_LEN 40
uint8_t U1Rx_Buff[U1Rx_MAX_LEN]={0};
uint8_t U2Rx_Buff[U2Rx_MAX_LEN]={0};
uint16_t U1Rx_Len = 0,U2Rx_Len = 0;

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void ch9142_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};

    //Init usart1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->A.9   RX-->A.10 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);

    //Init usart2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* USART2 TX-->A.2   RX-->A.3 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE);

    //other IO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PC4-BLESAT0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PC5-BLESAT1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PA4-AT0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_4);//透传模式

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PA5-AT1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_5);//透传模式

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PA6-SLEEP
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_6);//不休眠

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PA7-RST
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_7);//不复位
}

void USART1_DataProcess(uint8_t* data, uint16_t len){
    USART_SendData(USART1, len);
}
void USART2_DataProcess(uint8_t* data, uint16_t len){
    USART_SendData(USART2, len);
}

void USART1_IRQHandler(void){
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){//接收中断触发
        if(U1Rx_Len<U1Rx_MAX_LEN){
            U1Rx_Buff[U1Rx_Len++] = USART_ReceiveData(USART1);
        } else{
            USART_ReceiveData(USART1);
            U1Rx_Len = 0;
        }
    }
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET){//触发空闲中断
        USART_ReceiveData(USART1);//清除中断标志位
        if(U1Rx_Len != 0){
            //认为一帧数据接收完成，处理数据部分
            USART1_DataProcess(U1Rx_Buff,U1Rx_Len);
            U1Rx_Len = 0;
        }
    }
}

void USART2_IRQHandler(void){
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){//接收中断触发
        if(U2Rx_Len<U2Rx_MAX_LEN){
            U2Rx_Buff[U2Rx_Len++] = USART_ReceiveData(USART2);
        } else{
            USART_ReceiveData(USART2);
            U2Rx_Len = 0;
        }
    }
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET){//触发空闲中断
        USART_ReceiveData(USART2);//清除中断标志位
        if(U2Rx_Len != 0){
            //认为一帧数据接收完成，处理数据部分
            USART2_DataProcess(U2Rx_Buff,U2Rx_Len);
            U2Rx_Len = 0;
        }
    }
}
