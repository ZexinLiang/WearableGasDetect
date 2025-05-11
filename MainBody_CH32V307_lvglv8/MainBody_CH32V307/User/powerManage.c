/*
 * powerManage.c
 *
 *  Created on: 2025��5��6��
 *      Author: ������
 */

#include "powerManage.h"

void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

const uint16_t minVol = 2890;//��Ϳ�����ѹ
const uint16_t maxVol = 3468;//��ߵ�ѹֵ
const uint16_t volRange = maxVol - minVol;//��Ч��ѹ��Χ

uint8_t volInPercent = 100;//�ٷֱȵ�ѹ
uint16_t voltageFilter[3] = {maxVol,maxVol,maxVol};//��ѹ�˲�������
uint8_t cntForPF = 0;//������ʱ�س���
uint16_t VoltageADCVal = 0;//ʵʱ�ɼ��ĵ�ѹֵ
//uint8_t lowPowerFlag = 0;//�͵�ѹ��־λ
uint8_t powerOffFlag = 0;//�͵�ѹ�ػ�
uint8_t userOffFlag = 0;//�û����ùػ�

int16_t Calibrattion_Val = 0;//ADCУ׼ֵ

//��ʼ������������Ҫ�ĳ���
void powerOn_Init_Execute(void){
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
    //1S�󿪻�
    for(uint8_t i = 0;i<100;i++)
        Delay_Ms(10);
    GPIO_SetBits(GPIOB,GPIO_Pin_0);//IO���ߣ�ά�ֿ���״̬
}

void powerMagage_Init(void){
    //Init ADC1_CH9 for voltage collect.
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigInjecConv_T2_TRGO;//��ʱ������жϴ���ADC�ɼ�
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 9;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_InjectedSequencerLengthConfig(ADC1, 1);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_BufferCmd(ADC1, DISABLE); //disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    Calibrattion_Val = Get_CalibrationValue(ADC1);
}

u16 Get_ConversionVal(s16 val)
{
    if((val + Calibrattion_Val) < 0||val==0)
        return 0;
    if((Calibrattion_Val + val) > 4095 || val==4095)
        return 4095;
    return (val + Calibrattion_Val);
}

//��ص�����ȡ
void getVolInPercent(uint16_t ADC_vol){
    voltageFilter[0]=voltageFilter[1];
    voltageFilter[1]=voltageFilter[2];
    voltageFilter[2]=ADC_vol;
    uint16_t ADC_volAvg = (voltageFilter[0]+voltageFilter[1]+voltageFilter[2])/3;
    uint16_t usefulVolIn = ((ADC_volAvg - minVol)>0?(ADC_volAvg - minVol):0);//��ȡ��Ч��ѹ��ֵ
    usefulVolIn = (usefulVolIn>volRange)?volRange:usefulVolIn;//���Ʒ���
    float percent = (float)usefulVolIn/(float)volRange*100.f;
    volInPercent = (uint8_t)percent;
}

void powerOffDetect(void){
    if((!powerOffFlag)&&volInPercent==0) powerOffFlag = 1;
    else if(powerOffFlag&&(volInPercent!=0)) powerOffFlag = 0;
    if(powerOffFlag == 1){
        cntForPF++;
        if(cntForPF==100){
            //ִ�йػ�����
            GPIO_ResetBits(GPIOB, GPIO_Pin_0);
            while(1);
        }
    }
    else cntForPF = 0;
    if(userOffFlag){
        //ִ�йػ�����
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    }
}

void ADC1_2_IRQHandler()
{
    u16 ADC_val;

    if(ADC_GetITStatus(ADC1, ADC_IT_JEOC))
    {
        ADC_val = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
        VoltageADCVal = Get_ConversionVal(ADC_val);
        getVolInPercent(VoltageADCVal);
        //USART_SendData(USART1, ADC_ActVal);
    }
    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
}
