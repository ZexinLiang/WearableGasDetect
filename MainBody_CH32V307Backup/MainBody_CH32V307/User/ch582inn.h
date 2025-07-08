/*
 * ch582inn.h
 *
 *  Created on: 2025Äê6ÔÂ8ÈÕ
 *      Author: 86135
 */

#ifndef USER_CH582INN_H_
#define USER_CH582INN_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"
#include "stdint.h"

typedef struct DataTab{
    float temp1;
    float pres1;
    float humi1;
    float gasRes;
    uint8_t humi2;
    uint8_t temp2;
    uint16_t CO2;
    uint16_t gas1;
}DataTab_TypeDef;

void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str);
void CH582_Com_Init(void);

void UART5_DataProcess(uint8_t* data, uint16_t len);

#endif /* USER_CH582INN_H_ */
