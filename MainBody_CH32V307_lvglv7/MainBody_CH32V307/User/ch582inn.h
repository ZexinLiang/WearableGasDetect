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

void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str);
void CH582_Com_Init(void);

void UART5_DataProcess(uint8_t* data, uint16_t len);

#endif /* USER_CH582INN_H_ */
