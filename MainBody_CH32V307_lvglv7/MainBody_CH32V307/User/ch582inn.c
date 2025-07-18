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
#include <stdlib.h>

DataTab_TypeDef data = {
        .CO2 = 800,
        .gasRes = 300000,
        .humi2 = 70,
        .o2 = 20,
        .temp2 = 25
};

void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define U5Rx_MAX_LEN 40
uint8_t U5Rx_Buff[U5Rx_MAX_LEN]={0};
uint16_t U5Rx_Len = 0;
uint8_t CH582Cnned = 0;
uint8_t CH582IdleCnt = 0;//��������û���յ���Ϣ�����յ�������Ϣ��Ϊ����
/* ���ӹ���
 * ����Ѿ����ӳɹ���ֱ�ӷ�������
 * ���û�����ӳɹ���������Χ�ɲ��ҵ����豸
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

uint16_t co2filter[3] = {0};
float garsrFliter[3] = {300000,300000,300000};
uint8_t rhFilter[3]={80,80,80};
int compare_uint8(const void *a, const void *b) {
    return (*(uint8_t*)a - *(uint8_t*)b); // ֱ�Ӽ��������� uint8_t
}

// ������λ�������������������ݣ�
uint8_t find_median_uint8(uint8_t data[], int n) {
    qsort(data, n, sizeof(uint8_t), compare_uint8);
    return data[n / 2]; // ֱ�ӷ����м�ֵ
}

int compare_uint16(const void *a, const void *b) {
    return (*(uint16_t*)a - *(uint16_t*)b); // �޷��������Ƚ�
}

uint16_t find_median_uint16(uint16_t *dataTab, int n) {
    qsort(dataTab, n, sizeof(uint16_t), compare_uint16);
    return dataTab[n / 2]; // ֱ�ӷ����м�ֵ
}

int compare_float(const void *a, const void *b) {
    float fa = *(const float*)a; // ת��Ϊ float ָ��������
    float fb = *(const float*)b;

    // ����ֱ�ӷ��� (fa - fb)����ֹ������ʧ�����
    if (fa > fb) return  1; // a > b ʱ��������
    if (fa < fb) return -1; // a < b ʱ���ظ���
    return 0;               // ���ʱ���� 0
}

// ������λ������������������������
float find_median_float(float data[], int n) {
    qsort(data, n, sizeof(float), compare_float);
    return data[n / 2]; // ֱ�ӷ����м�ֵ
}

void CO2Fliter(uint16_t co2ppm){
    for(int i = 0;i < 2 ;i++)
    {
        co2filter[i] = co2filter[1+i];
    }
    co2filter[2] = co2ppm;
   data.CO2 = find_median_uint16(co2filter, 3);
}

void GasRFilter(float gasr){
    for(int i = 0;i < 2 ;i++)
        {
        garsrFliter[i] = garsrFliter[1+i];
        }
        garsrFliter[2] = gasr;
       data.gasRes = find_median_float(garsrFliter, 3);
}

void RHGFilter(uint8_t rh){
    for(int i = 0;i < 2 ;i++)
        {
        rhFilter[i] = rhFilter[1+i];
        }
    rhFilter[2] = rh;
       data.humi2 = find_median_uint8(rhFilter, 3);
}

void UART5_IRQHandler(void){
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){//�����жϴ���
        singleChar = USART_ReceiveData(UART5);
        if(singleChar == '$') u5GetFlag = 1;
        if(u5GetFlag){
            CH582Cnned = 1;
            CH582IdleCnt = 0;
            U5Rx_Buff[U5Rx_Len++] = singleChar;
            if(singleChar == '*') {
                u5GetFlag = 0;//�������գ����Դ�������
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
//                    float gasrTemp =(U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
//                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0')+
//                                 (U5Rx_Buff[13]-'0')*0.1+(U5Rx_Buff[14]-'0')*0.01;
//                    GasRFilter(gasrTemp);
                    data.gasRes  =  (U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                                             (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0')+
                                                             (U5Rx_Buff[13]-'0')*0.1+(U5Rx_Buff[14]-'0')*0.01;
                }
                else if(U5Rx_Buff[1]=='h'&&U5Rx_Buff[5]=='2'){
//                    uint8_t humi2Temp = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0');
//                    RHGFilter(humi2Temp);
                    data.humi2 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0');
                }
                else if(U5Rx_Buff[1]=='t'&&U5Rx_Buff[5]=='2'){
                    data.temp2 = (U5Rx_Buff[6]-'0')*100+(U5Rx_Buff[7]-'0')*10+(U5Rx_Buff[8]-'0');
                }
                else if(U5Rx_Buff[1]=='C'){
                    uint16_t tempco2   =(U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
                                 (U5Rx_Buff[9]-'0')*100+(U5Rx_Buff[10]-'0')*10+(U5Rx_Buff[11]-'0');
                    //CO2Fliter(tempco2);
                    if(tempco2-data.CO2<3000&&tempco2-data.CO2>-3000)
                        data.CO2 =  (U5Rx_Buff[6]-'0')*100000+(U5Rx_Buff[7]-'0')*10000+(U5Rx_Buff[8]-'0')*1000+
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
//    if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET){//���������ж�
//        USART_ReceiveData(UART5);//����жϱ�־λ
//        if(U5Rx_Len != 0){
//            //��Ϊһ֡���ݽ�����ɣ��������ݲ���
//            UART5_DataProcess(U5Rx_Buff,U5Rx_Len);
//            U5Rx_Len = 0;
//        }
//    }
}

