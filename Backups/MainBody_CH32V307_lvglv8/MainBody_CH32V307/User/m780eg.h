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

void m780eg_Init(void);
void USART3_DataProcess(uint8_t* data, uint16_t len);

#endif /* USER_M780EG_H_ */
