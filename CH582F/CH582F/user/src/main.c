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
#include "peripheral.h"
#include "i2c.h"
#include "task.h"
#include "jed.h"
#include "bmeInRegis.h"
#include "scd40reg.h"
#include "bme68x.h"
#include "bme68x_defs.h"
#include "bmelink.h"
#include "data.h"
//forDeBug
uint8_t TxBuff[100] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;

__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];  // 4�ֽڶ���
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)                           // ������
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

//������
DataTab_TypeDef DataTab={0};

//BME688
struct bme68x_data comp_data;

//JEDϵ��
uint16_t gasPPM[2]={0};

//SCD40
uint16_t CO2=50;
uint16_t Temperature=0;
uint16_t Relative_humidity=0;

//�������IIC�ӿ�
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

    //��������
    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();
    //�������IIC����ʵ�����ݲɼ�
    I2CInit(&i2c0);
    I2CInit(&i2c1);
    //JEDϵ�д�������������
    GPIOB_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_20mA);//���ô��������ȵ�ѹоƬʹ������
    GPIOB_ResetBits(GPIO_Pin_7);//Ĭ�ϲ����ȣ����͹���
    bme688devInit();
    taskInit();
    while(1)
    {
        TMOS_SystemProcess();//TMOS�������
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
        /*
        case UART_II_RECV_RDY: // ���ݴﵽ���ô�����
            for(i = 0; i != trigB; i++)
            {
                RxBuff[i] = UART1_RecvByte();
                UART1_SendByte(RxBuff[i]);
            }
            break;

        case UART_II_RECV_TOUT: // ���ճ�ʱ����ʱһ֡���ݽ������
            i = UART1_RecvString(RxBuff);
            UART1_SendString(RxBuff, i);
            break;

        case UART_II_THR_EMPTY: // ���ͻ������գ��ɼ�������
            break;

        case UART_II_MODEM_CHG: // ֻ֧�ִ���0
            break;
    */
        default:
            break;
    }
}
