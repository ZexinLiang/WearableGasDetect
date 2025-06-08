/*
 * ch582inn.c
 *
 *  Created on: 2025��6��8��
 *      Author: ������
 */
//
/*ע�⣺����HSEΪ12MHz*/
#include "ch582inn.h"
#include <stdio.h>

void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define U5Rx_MAX_LEN 40
uint8_t U5Rx_Buff[U5Rx_MAX_LEN]={0};
uint16_t U5Rx_Len = 0;

void CH582_Com_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};
    //Init uart5
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);

    /* USART5 TX-->C.12   RX-->D.2 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(UART5, &USART_InitStructure);
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(UART5, ENABLE);
}

void UART5_DataProcess(uint8_t* data, uint16_t len){
    USART_SendData(UART5, len);
}

void UART5_IRQHandler(void){
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){//�����жϴ���
        if(U5Rx_Len<U5Rx_MAX_LEN){
            U5Rx_Buff[U5Rx_Len++] = USART_ReceiveData(UART5);
            USART_SendData(UART5,U5Rx_Buff[U5Rx_Len-1]);
        } else{
            USART_ReceiveData(UART5);
            U5Rx_Len = 0;
        }
    }
//    if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET){//���������ж�
//        USART_ReceiveData(UART5);//����жϱ�־λ
//        if(U5Rx_Len != 0){
//            //��Ϊһ֡���ݽ�����ɣ��������ݲ���
//            UART5_DataProcess(U5Rx_Buff,U5Rx_Len);
//            U5Rx_Len = 0;
//        }
//    }
}

