/*
 * control.c
 *
 *  Created on: 2025年6月11日
 *      Author: 86135
 */

/*控制回传给主机的数据
 * 如果连接上则转发设备消息
 * 否则返回扫描到的设备数据
 */

#include "control.h"

void BLEDataTransfer(gattMsgEvent_t *pMsg){
    uint8_t fbMsg[20]={0};
    uint8_t i = 0,j = 0;
    for(int i = 0; i < pMsg->msg.handleValueNoti.len ; i++){
        fbMsg[i] = *(pMsg->msg.handleValueNoti.pValue+i);
        j = j+1;
        if(*(pMsg->msg.handleValueNoti.pValue+i)=='*'||i==19)//数据阻塞或者数据包不符合规范处理
            break;
    }
    UART1_SendString(fbMsg, j);
}

