/*
 * m780eg.h
 *
 *  Created on: 2025ƒÍ5‘¬6»’
 *      Author: ¡∫‘Û–¿
 */

#ifndef USER_M780EG_H_
#define USER_M780EG_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"
#include "stdint.h"

void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str);

void m780eg_Init(void);
void m780eg_work(void);
void m780eg_reset(void);
uint8_t m780eg_cnn_stat(void);
void m780eg_perioTask(void);

void USART3_DataProcess(uint8_t* data, uint16_t len);

#endif /* USER_M780EG_H_ */
