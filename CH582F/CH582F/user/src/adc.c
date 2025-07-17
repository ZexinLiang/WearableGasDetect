
#include "CH58x_common.h"
#include "stdint.h"
#include "adc.h"

uint16_t adcBuff[40];
volatile uint8_t adclen = 0;
uint8_t adc_channel_list[] = {12, 13};  // PA8, PA9
uint8_t current_channel_index = 0;


void Start_ADC12_13_Interrupt_Sampling(void)
{
    GPIOA_ModeCfg(GPIO_Pin_8 | GPIO_Pin_9, GPIO_ModeIN_Floating);  // 配置 PA8 和 PA9 为输入
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);            // 单端采样初始化

    current_channel_index = 0;
    ADC_ChannelCfg(adc_channel_list[current_channel_index]);       // 先采样 ADC12（PA8）

    adclen = 0;
    ADC_ClearITFlag();
    PFIC_EnableIRQ(ADC_IRQn);     // 开启 ADC 中断
    ADC_StartUp();                // 启动第一次采样
}

int mian(void)
{
//    SetSysClock(CLK_SOURCE_PLL_60MHz);
//    DebugInit();
    PRINT("Start ADC Interrupt Voltage Sampling...\n");

    Start_ADC12_13_Interrupt_Sampling();

    while(current_channel_index < 2); // 等待中断完成两个通道

    // 输出转换为电压（单位 mV）
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
            // 切换通道
            current_channel_index++;
            if(current_channel_index < sizeof(adc_channel_list))
            {
                adclen = 0;
                ADC_ChannelCfg(adc_channel_list[current_channel_index]);
                ADC_StartUp();
            }
            else
            {
                PFIC_DisableIRQ(ADC_IRQn);  // 采完两个通道，关闭中断
            }
        }
    }
}
