/*
 * control.c
 *
 *  Created on: 2025��6��11��
 *      Author: 86135
 */

/*���ƻش�������������
 * �����������ת���豸��Ϣ
 * ���򷵻�ɨ�赽���豸����
 */

#include "control.h"

void BLEDataTransfer(gattMsgEvent_t *pMsg){
    uint8_t fbMsg[20]={0};
    uint8_t i = 0,j = 0;
    for(int i = 0; i < pMsg->msg.handleValueNoti.len ; i++){
        fbMsg[i] = *(pMsg->msg.handleValueNoti.pValue+i);
        j = j+1;
        if(*(pMsg->msg.handleValueNoti.pValue+i)=='*'||i==19)//���������������ݰ������Ϲ淶����
            break;
    }
    UART1_SendString(fbMsg, j);
}

