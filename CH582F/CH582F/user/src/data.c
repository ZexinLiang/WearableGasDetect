/*
 * data.c
 *
 *  Created on: 2025年6月10日
 *      Author: lzx
 */
#include "data.h"

extern DataTab_TypeDef DataTab;

void UsartMsgOutput(void){//输出调试信息，包含每个气体实时值

}
//
//float temp1;
//float pres1;
//float humi1;
//float gasRes;
//uint8_t humi2;
//uint8_t temp2;
//uint16_t CO2;
//uint16_t gas1;

uint8_t cnt = 0;
#define maxMsgNum 8
void BleMsgOutput(char* msg){//BLE数据回传，分多个数据包，每个数据包20字节，循环回传
    switch(cnt%maxMsgNum){
    case 0 : sprintf(msg,"$temp1%03.2f*",DataTab.temp1);break;
    case 1 : sprintf(msg,"$pres1%04.2f*",DataTab.pres1);break;
    case 2 : sprintf(msg,"$humi1%03.2f*",DataTab.humi1);break;
    case 3 : sprintf(msg,"$gResi%06.2f*",DataTab.gasRes);break;
    case 4 : sprintf(msg,"$humi2%03d*",DataTab.humi2);break;
    case 5 : sprintf(msg,"$temp2%03d*",DataTab.temp2);break;
    case 6 : sprintf(msg,"$CO2pp%06d*",DataTab.CO2);break;
    case 7 : sprintf(msg,"$pgas1%06d*",DataTab.gas1);break;
    }
    cnt++;
}
