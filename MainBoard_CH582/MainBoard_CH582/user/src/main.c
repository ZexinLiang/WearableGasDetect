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
#include "central.h"

uint8_t TxBuff[] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;

__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];  // 4字节对齐
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)                           // 不启用
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

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

    GPIOB_SetBits(bTXD0);//PB7  配置串口0
    GPIOB_ModeCfg(bRXD0, GPIO_ModeIN_PU);      // RXD-PB4配置上拉输入
    GPIOB_ModeCfg(bTXD0, GPIO_ModeOut_PP_5mA); // TXD-PB7配置推挽输出，注意先让IO口输出高电平
    UART0_DefInit();//BaundRate 115200
    UART0_ByteTrigCfg(UART_7BYTE_TRIG);
    UART0_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART0_IRQn);

    CH58X_BLEInit();
    HAL_Init();
    GAPRole_CentralInit();
    Central_Init();

    while(1)
    {
        TMOS_SystemProcess();
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

//        case UART_II_RECV_RDY: // 数据达到设置触发点
//            for(i = 0; i != trigB; i++)
//            {
//                RxBuff[i] = UART1_RecvByte();
//                UART1_SendByte(RxBuff[i]);
//            }
//            break;
//
//        case UART_II_RECV_TOUT: // 接收超时，暂时一帧数据接收完成
//            i = UART1_RecvString(RxBuff);
//            UART1_SendString(RxBuff, i);
//            break;
//
//        case UART_II_THR_EMPTY: // 发送缓存区空，可继续发送
//            break;
//
//        case UART_II_MODEM_CHG: // 只支持串口0
//            break;

        default:
            break;
    }
}
void UART0_IRQHandler(void)
{
    volatile uint8_t i;

    switch(UART0_GetITFlag())
    {
        case UART_II_LINE_STAT: // 线路状态错误
        {
            //UART1_GetLinSTA();
            break;
        }

//        case UART_II_RECV_RDY: // 数据达到设置触发点
//            for(i = 0; i != trigB; i++)
//            {
//                RxBuff[i] = UART1_RecvByte();
//                UART1_SendByte(RxBuff[i]);
//            }
//            break;
//
//        case UART_II_RECV_TOUT: // 接收超时，暂时一帧数据接收完成
//            i = UART1_RecvString(RxBuff);
//            UART1_SendString(RxBuff, i);
//            break;
//
//        case UART_II_THR_EMPTY: // 发送缓存区空，可继续发送
//            break;
//
//        case UART_II_MODEM_CHG: // 只支持串口0
//            break;

        default:
            break;
    }
}
