
#include "CH58x_common.h"
#include "stdint.h"
#include "adc.h"

uint16_t adcBuff[40];
volatile uint8_t adclen = 0;
uint8_t adc_channel_list[] = {12, 13};  // PA8, PA9
uint8_t current_channel_index = 0;


void Start_ADC12_13_Interrupt_Sampling(void)
{
    GPIOA_ModeCfg(GPIO_Pin_8 | GPIO_Pin_9, GPIO_ModeIN_Floating);  // ���� PA8 �� PA9 Ϊ����
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);            // ���˲�����ʼ��

    current_channel_index = 0;
    ADC_ChannelCfg(adc_channel_list[current_channel_index]);       // �Ȳ��� ADC12��PA8��

    adclen = 0;
    ADC_ClearITFlag();
    PFIC_EnableIRQ(ADC_IRQn);     // ���� ADC �ж�
    ADC_StartUp();                // ������һ�β���
}

int mian(void)
{
//    SetSysClock(CLK_SOURCE_PLL_60MHz);
//    DebugInit();
    PRINT("Start ADC Interrupt Voltage Sampling...\n");

    Start_ADC12_13_Interrupt_Sampling();

    while(current_channel_index < 2); // �ȴ��ж��������ͨ��

    // ���ת��Ϊ��ѹ����λ mV��
    PRINT("PA8 (ADC12) Voltage:\n");
    for(uint8_t i = 0; i < 20; i++)
    {
        uint16_t voltage_mv = (adcBuff[i] * 3300) / 4095;
        PRINT("%d mV\n", voltage_mv);
    }

    PRINT("PA9 (ADC13) Voltage:\n");
    for(uint8_t i = 20; i < 40; i++)
    {
        uint16_t voltage_mv = (adcBuff[i] * 3300) / 4095;
        PRINT("%d mV\n", voltage_mv);
    }

    while(1);
}



__INTERRUPT
__HIGH_CODE
void ADC_IRQHandler(void)
{
    if (ADC_GetITStatus())
    {
        ADC_ClearITFlag();

        if(adclen < 20)
        {
            adcBuff[adclen++] = ADC_ReadConverValue();
            ADC_StartUp();
        }
        else
        {
            // �л�ͨ��
            current_channel_index++;
            if(current_channel_index < sizeof(adc_channel_list))
            {
                adclen = 0;
                ADC_ChannelCfg(adc_channel_list[current_channel_index]);
                ADC_StartUp();
            }
            else
            {
                PFIC_DisableIRQ(ADC_IRQn);  // ��������ͨ�����ر��ж�
            }
        }
    }
}
