/*
 * ch9142.h
 *
 *  Created on: 2025ƒÍ5‘¬6»’
 *      Author: ¡∫‘Û–¿
 */

#ifndef USER_CH9142_H_
#define USER_CH9142_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"

void ch9142_Init(void);
void USART1_DataProcess(uint8_t* data, uint16_t len);
void USART2_DataProcess(uint8_t* data, uint16_t len);

#endif /* USER_CH9142_H_ */
