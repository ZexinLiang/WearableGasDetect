/*
 * m780eg.c
 *
 *  Created on: 2025年5月6日
 *      Author: 梁泽欣
 */

#include "m780eg.h"

void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define U3Rx_MAX_LEN 40
uint8_t U3Rx_Buff[U3Rx_MAX_LEN]={0};
uint16_t U3Rx_Len = 0;

void m780eg_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};
    //Init usart3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* USART3 TX-->B.10   RX-->B.11 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART3, ENABLE);

    //other IO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PB12-RDY
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PB13-RST
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void USART3_DataProcess(uint8_t* data, uint16_t len){
    USART_SendData(USART3, len);
}

void USART3_IRQHandler(void){
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){//接收中断触发
        if(U3Rx_Len<U3Rx_MAX_LEN){
            U3Rx_Buff[U3Rx_Len++] = USART_ReceiveData(USART3);
        } else{
            USART_ReceiveData(USART3);
            U3Rx_Len = 0;
        }
    }
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET){//触发空闲中断
        USART_ReceiveData(USART3);//清除中断标志位
        if(U3Rx_Len != 0){
            //认为一帧数据接收完成，处理数据部分
            USART3_DataProcess(U3Rx_Buff,U3Rx_Len);
            U3Rx_Len = 0;
        }
    }
}
