/*
 * ch582inn.c
 *
 *  Created on: 2025年6月8日
 *      Author: 梁泽欣
 */
//
/*注意：板载HSE为12MHz*/
#include "ch582inn.h"
#include <stdio.h>

DataTab_TypeDef data;

void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define U5Rx_MAX_LEN 40
uint8_t U5Rx_Buff[U5Rx_MAX_LEN]={0};
uint16_t U5Rx_Len = 0;
uint8_t CH582Cnned = 0;
uint8_t CH582IdleCnt = 0;//超过五秒没有收到消息或者收到断联消息视为断链
/* 连接功能
 * 如果已经连接成功，直接返回数据
 * 如果没有连接成功，返回周围可查找到的设备
 * */

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


uint8_t u5GetFlag = 0;
uint8_t singleChar = 0;
void UART5_IRQHandler(void){
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){//接收中断触发
        singleChar = USART_ReceiveData(UART5);
        if(singleChar == '$') u5GetFlag = 1;
        if(u5GetFlag){
            CH582Cnned = 1;
            CH582IdleCnt = 0;
            U5Rx_Buff[U5Rx_Len++] = singleChar;
            if(singleChar == '*') {
                u5GetFlag = 0;//结束接收，可以处理数据
                U5Rx_Len = 0;
                if(U5Rx_Buff[1]=='t'&&U5Rx_Buff[5]=='1'){
                    data.temp1 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0')+
                                 (U5Rx_Buff[10]-'0')*0.1+(U5Rx_Buff[11]-'0')*0.01;
                }
                else if(U5Rx_Buff[2]=='r'&&U5Rx_Buff[5]=='1'){
                    data.pres1 = (U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0')+
                                 (U5Rx_Buff[13]-'0')*0.1+(U5Rx_Buff[14]-'0')*0.01;
                }
                else if(U5Rx_Buff[1]=='h'&&U5Rx_Buff[5]=='1'){
                    data.humi1 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0')+
                                 (U5Rx_Buff[10]-'0')*0.1+(U5Rx_Buff[11]-'0')*0.01;
                }
                else if(U5Rx_Buff[1]=='g'){
                    data.gasRes =(U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0')+
                                 (U5Rx_Buff[13]-'0')*0.1+(U5Rx_Buff[14]-'0')*0.01;
                }
                else if(U5Rx_Buff[1]=='h'&&U5Rx_Buff[5]=='2'){
                    data.humi2 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0');
                }
                else if(U5Rx_Buff[1]=='t'&&U5Rx_Buff[5]=='2'){
                    data.temp2 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0');
                }
                else if(U5Rx_Buff[1]=='C'){
                    data.CO2   =(U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0');
                }
                else if(U5Rx_Buff[2]=='g'&&U5Rx_Buff[5]=='1'){
                    data.gas1   =(U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0');
                }
            }
            //USART_SendData(UART5,U5Rx_Buff[U5Rx_Len-1]);
        } else{
            U5Rx_Len = 0;
        }
    }
//    if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET){//触发空闲中断
//        USART_ReceiveData(UART5);//清除中断标志位
//        if(U5Rx_Len != 0){
//            //认为一帧数据接收完成，处理数据部分
//            UART5_DataProcess(U5Rx_Buff,U5Rx_Len);
//            U5Rx_Len = 0;
//        }
//    }
}

