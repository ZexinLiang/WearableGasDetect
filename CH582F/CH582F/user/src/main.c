/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : 串口1收发演示
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH58x_common.h"
#include "HAL.h"
#include "config.h"
#include "CH58xBLE_LIB.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "i2c.h"
#include "task.h"
#include "jed.h"
#include "bmeInRegis.h"
#include "scd4x_i2c.h"
#include "sensirion_common.h"

//forDeBug
uint8_t TxBuff[100] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;

__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];  // 4字节对齐
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)                           // 不启用
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

//BME688
uint8_t dev_addr = 0x77;

//JED系列
uint16_t gasPPM[2]={0};

//SCD40


//两个软件IIC接口
softI2C_TypeDef i2c0={
        .SCLPort=GPIOB,
        .SCLPin =GPIO_Pin_14,
        .SDAPort=GPIOB,
        .SDAPin =GPIO_Pin_15
};
softI2C_TypeDef i2c1={
        .SCLPort=GPIOB,
        .SCLPin =GPIO_Pin_12,
        .SDAPort=GPIOB,
        .SDAPin =GPIO_Pin_13
};

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main()
{
    PWR_DCDCCfg(ENABLE);//启动DC-DC低功耗
    SetSysClock(CLK_SOURCE_PLL_60MHz);//配置系统时钟

    GPIOA_SetBits(bTXD1);//PA9  配置串口1
    GPIOA_ModeCfg(bRXD1, GPIO_ModeIN_PU);      // RXD-PA8配置上拉输入
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA); // TXD-PA9配置推挽输出，注意先让IO口输出高电平
    UART1_DefInit();//BaundRate 115200
    UART1_ByteTrigCfg(UART_7BYTE_TRIG);
    UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART1_IRQn);

    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();

    I2CInit(&i2c0);//配置软件IIC
    I2CInit(&i2c1);

    GPIOB_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_20mA);//配置传感器加热电压芯片使能引脚
    GPIOB_ResetBits(GPIO_Pin_7);//默认不加热，降低功耗

    //BME688InitInReg();

    //SCD40
    // 1. 初始化传感器
    scd4x_init(0x62);

    // 2. 可选 - 停止之前的测量（确保干净状态）
    scd4x_stop_periodic_measurement();

    // 3. 配置传感器（可选）
    scd4x_set_temperature_offset_raw(0);       // 设置温度偏移
    scd4x_set_ambient_pressure(101300);       // 设置环境压力（帕斯卡）

    // 4. 启动周期测量模式
    int16_t error = scd4x_start_periodic_measurement();
    if (error != NO_ERROR) {
        PRINT("SETEEEEEERROR1\n");
        // 处理错误
    }
    else {
        PRINT("OK1");
    }

    while(1) {
        // 5. 检查数据是否就绪
        bool data_ready = false;
        error = scd4x_get_data_ready_status(&data_ready);
        if (error != NO_ERROR) {
            PRINT("SETEEEEEERROR2\n");
            // 处理错误
        }

        if (data_ready) {
            // 6. 读取测量数据
            uint16_t co2;
            int32_t temperature_mc;
            int32_t humidity_mp;
            error = scd4x_read_measurement(&co2, &temperature_mc, &humidity_mp);

            if (error == NO_ERROR) {
                // 7. 转换数据格式
                float temperature = temperature_mc / 1000.0f;  // 转换为摄氏度
                float humidity = humidity_mp / 1000.0f;        // 转换为%RH

                printf("CO2: %u ppm\n", co2);
                printf("Temperature: %.2f C\n", temperature);
                printf("Humidity: %.2f %%RH\n", humidity);
            }
        }

        // 8. 等待5秒（SCD4x的测量周期）
        DelayMs(5000);
    }

    return 0;
    while(1){}
    taskInit();//测量任务初始化

    while(1)
    {
        TMOS_SystemProcess();//TMOS任务调度
    }

}

/*********************************************************************
 * @fn      UART1_IRQHandler
 *
 * @brief   UART1中断函数
 *
 * @return  none
 */
__INTERRUPT
__HIGH_CODE
void UART1_IRQHandler(void)
{
    volatile uint8_t i;

    switch(UART1_GetITFlag())
    {
        case UART_II_LINE_STAT: // 线路状态错误
        {
            //UART1_GetLinSTA();
            break;
        }
        /*
        case UART_II_RECV_RDY: // 数据达到设置触发点
            for(i = 0; i != trigB; i++)
            {
                RxBuff[i] = UART1_RecvByte();
                UART1_SendByte(RxBuff[i]);
            }
            break;

        case UART_II_RECV_TOUT: // 接收超时，暂时一帧数据接收完成
            i = UART1_RecvString(RxBuff);
            UART1_SendString(RxBuff, i);
            break;

        case UART_II_THR_EMPTY: // 发送缓存区空，可继续发送
            break;

        case UART_II_MODEM_CHG: // 只支持串口0
            break;
    */
        default:
            break;
    }
}
