/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : ����1�շ���ʾ
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

__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];  // 4�ֽڶ���
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)                           // ������
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int main()
{
    PWR_DCDCCfg(ENABLE);//����DC-DC�͹���
    SetSysClock(CLK_SOURCE_PLL_60MHz);//����ϵͳʱ��

    GPIOA_SetBits(bTXD1);//PA9  ���ô���1
    GPIOA_ModeCfg(bRXD1, GPIO_ModeIN_PU);      // RXD-PA8������������
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA); // TXD-PA9�������������ע������IO������ߵ�ƽ
    UART1_DefInit();//BaundRate 115200
    UART1_ByteTrigCfg(UART_7BYTE_TRIG);
    UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART1_IRQn);

    GPIOB_SetBits(bTXD0);//PB7  ���ô���0
    GPIOB_ModeCfg(bRXD0, GPIO_ModeIN_PU);      // RXD-PB4������������
    GPIOB_ModeCfg(bTXD0, GPIO_ModeOut_PP_5mA); // TXD-PB7�������������ע������IO������ߵ�ƽ
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
 * @brief   UART1�жϺ���
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
        case UART_II_LINE_STAT: // ��·״̬����
        {
            //UART1_GetLinSTA();
            break;
        }

//        case UART_II_RECV_RDY: // ���ݴﵽ���ô�����
//            for(i = 0; i != trigB; i++)
//            {
//                RxBuff[i] = UART1_RecvByte();
//                UART1_SendByte(RxBuff[i]);
//            }
//            break;
//
//        case UART_II_RECV_TOUT: // ���ճ�ʱ����ʱһ֡���ݽ������
//            i = UART1_RecvString(RxBuff);
//            UART1_SendString(RxBuff, i);
//            break;
//
//        case UART_II_THR_EMPTY: // ���ͻ������գ��ɼ�������
//            break;
//
//        case UART_II_MODEM_CHG: // ֻ֧�ִ���0
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
        case UART_II_LINE_STAT: // ��·״̬����
        {
            //UART1_GetLinSTA();
            break;
        }

//        case UART_II_RECV_RDY: // ���ݴﵽ���ô�����
//            for(i = 0; i != trigB; i++)
//            {
//                RxBuff[i] = UART1_RecvByte();
//                UART1_SendByte(RxBuff[i]);
//            }
//            break;
//
//        case UART_II_RECV_TOUT: // ���ճ�ʱ����ʱһ֡���ݽ������
//            i = UART1_RecvString(RxBuff);
//            UART1_SendString(RxBuff, i);
//            break;
//
//        case UART_II_THR_EMPTY: // ���ͻ������գ��ɼ�������
//            break;
//
//        case UART_II_MODEM_CHG: // ֻ֧�ִ���0
//            break;

        default:
            break;
    }
}
