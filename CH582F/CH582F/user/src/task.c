/*
 * task.c
 *
 *  Created on: 2024年2月6日
 *      Author: 梁泽欣
 */
#include "task.h"
#include "i2c.h"
#include "jed.h"
#include "scd40reg.h"

#define READ_BAT_EVENT   1
#define READ_UART_EVENT  2
#define E5000MS_EVENT    4
#define E1000MS_EVENT    8
#define E100MS_EVENT     16
#define E10MS_EVENT      32
#define SLEEP_EVENT      64

uint8_t TASK_ID = INVALID_TASK_ID;

uint8_t gasMsg[40]="0";

extern uint16_t CO2;
extern uint16_t Temperature;
extern uint16_t Relative_humidity;

void taskInit(void){
    TASK_ID = TMOS_ProcessEventRegister(ProcessEvent);
    tmos_start_task( TASK_ID, E1000MS_EVENT, 1600 );
    tmos_start_task( TASK_ID, E5000MS_EVENT, 8000 );
}

extern uint16_t centralCharHdl;
extern uint16_t centralConnHandle;
uint16_t ProcessEvent(uint8_t task_id, uint16_t events)
{
    if (events & SYS_EVENT_MSG)
    {
        uint8_t *pMsg;
        if ((pMsg = tmos_msg_receive(TASK_ID)) != NULL)
        {
            tmos_msg_deallocate(pMsg);
        }
        return (events ^ SYS_EVENT_MSG);
    }
    if (events & READ_UART_EVENT)
    {
        tmos_start_task(TASK_ID, READ_UART_EVENT, 8); // 8 * 0.625ms执行一次  2.5MS
        return (events ^ READ_UART_EVENT);
    }
    if (events & E5000MS_EVENT)
    {
        uint8_t status = 0;
        get_data_ready_status(&status);
        if(status)
        {
            read_measurement(&CO2,&Temperature,&Relative_humidity);
            printf("CO2:%d,T:%d,H:%d\r\n",CO2,Temperature,Relative_humidity);
        }

        tmos_start_task(TASK_ID, E5000MS_EVENT, 8000); // 3200 * 0.625ms执行一次  1000MS
        return (events ^ E5000MS_EVENT);
    }
    if (events & E1000MS_EVENT)
    {
        //gasPPM[0] = JED_I2C_Read_Byte(&i2c0);//IIC读取函数
        //gasPPM[1] = JED_I2C_Read_Byte(&i2c1);
        //sprintf(gasMsg,"gas0:%6dppm    gas1:%6dppm",gasPPM[0],gasPPM[1]);
        //UART1_SendString(gasMsg,sizeof(gasMsg));
        attWriteReq_t req;
        uint8_t data[] = {0x55, 0xAA};  // 要发送的两个字节

        req.handle = centralCharHdl;         // 你在特征发现阶段记录的句柄
        req.len = sizeof(data);
        memcpy(req.pValue, data, req.len);

        bStatus_t status = GATT_WriteNoRsp(centralConnHandle, &req);

        if (status == SUCCESS) {
            printf("Sent data to CH9142.\r\n");
        } else {
            printf("Write failed: %d\r\n", status);
        }

        tmos_start_task(TASK_ID, E1000MS_EVENT, 1600); // 3200 * 0.625ms执行一次  1000MS
        return (events ^ E1000MS_EVENT);
    }
    if (events & E100MS_EVENT)
    {
        tmos_start_task(TASK_ID, E100MS_EVENT, 160); // 160 * 0.625ms执行一次  100MS
        return (events ^ E100MS_EVENT);
    }
    if (events & E10MS_EVENT)
    {
        tmos_start_task(TASK_ID, E10MS_EVENT, 16); // 16 * 0.625ms执行一次  10MS
        return (events ^ E10MS_EVENT);
    }
    return 0;
}
