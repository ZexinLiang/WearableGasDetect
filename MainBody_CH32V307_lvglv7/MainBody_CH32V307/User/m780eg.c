/*
 * m780eg.c
 *
 *  Created on: 2025年5月6日
 *      Author: 梁泽欣
 */

#include "m780eg.h"
#include <stdio.h>
#include "ch582inn.h"
#include "lvgl.h"
#include "gui_guider.h"


extern lv_ui guider_ui;
extern DataTab_TypeDef data;

void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define U3Rx_MAX_LEN 100
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
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);//下拉不复位
}

void m780eg_reset(void){
    GPIO_SetBits(GPIOB, GPIO_Pin_13);//上拉复位
}

void m780eg_work(void){
    GPIO_ResetBits(GPIOB, GPIO_Pin_13);//下拉开始工作
}

uint8_t m780eg_cnn_stat(void){
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
}

//测试临时变量
uint16_t temp1 = 543,temp2 = 326,temp3 = 2367;
void m780eg_dataUpload(void){//按照约定通信上报数据
    char uploadMsg[200] = {0};
    //上报气体数据信息
    m780EGUpload(uploadMsg);
    USARTx_SendStr(USART3, uploadMsg);
}

//放在定时器里的周期性任务,1000ms
uint8_t cnnRstCnt = 0;
uint8_t reworkFlag = 0;
uint8_t confirmFlag = 1;//第一次连接上服务器的确认信息
void m780eg_perioTask(void){
    cnnRstCnt++;
    if(m780eg_cnn_stat()){
        if(confirmFlag){
            confirmFlag = !confirmFlag;
            char loginMsg[200] = "{ \"type\":\"verify\",\
            \"data\": { \
            \"VerifyCode\": \"1037\",\
            \"DeviceID\":1}}$$";
            USARTx_SendStr(USART3, loginMsg);
        }
        lv_label_set_text(guider_ui.screen_network_cnn_state, "Connected");
        m780eg_dataUpload();
        cnnRstCnt = 0;
    }
    else
        lv_label_set_text(guider_ui.screen_network_cnn_state, "Disconnected");
    //配合cnnRstCnt起到reset下拉1s后自动复位
    if(reworkFlag){
        m780eg_work();
        reworkFlag = 1;
    }
    //30s还未连上网，软件进行复位
    if(cnnRstCnt == 30){
        m780eg_reset();
        reworkFlag = 1;
        cnnRstCnt  = 0;
    }
}


//uint8_t uploadCnt = 0;
#define maxMsgNum 8
void m780EGUpload(char* msg){//BLE数据回传，分多个数据包，每个数据包20字节，循环回传
    sprintf(msg,"{ \"type\":\"Sensor\",\
\"data\": { \
\"Humidity1\": %f,\
\"Humidity2\": %d,\
\"Pressure\": %f, \
\"Temperature1\": %f, \
\"Temperature2\": %d, \
\"GasRes\": %f, \
\"PGas\": %d,\
\"CO2\": %d\
}}$$",data.humi1,data.humi2,data.pres1,data.temp1,data.temp2,data.gasRes,data.gas1,data.CO2);
//    switch(uploadCnt%maxMsgNum){
//    case 0 : sprintf(msg,"$temp1%06.2f*",data.temp1);break;
//    case 1 : sprintf(msg,"$pres1%09.2f*",data.pres1);break;
//    case 2 : sprintf(msg,"$humi1%06.2f*",data.humi1);break;
//    case 3 : sprintf(msg,"$gResi%09.2f*",data.gasRes);break;
//    case 4 : sprintf(msg,"$humi2%03d*",data.humi2);break;
//    case 5 : sprintf(msg,"$temp2%03d*",data.temp2);break;
//    case 6 : sprintf(msg,"$CO2pp%06d*",data.CO2);break;
//    case 7 : sprintf(msg,"$pgas1%06d*",data.gas1);break;
//    }
//    uploadCnt++;
}

void m780eg_dataProcess(void){//处理接收到的服务器报文

}
extern uint8_t serverAlarm ;
void USART3_DataProcess(uint8_t* data, uint16_t len){
    //USART_SendData(USART3, len);
    if(data[1]=='b')
        serverAlarm = data[2];
    else
    lv_label_set_text(guider_ui.screen_network_server_msg,data+2);
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
