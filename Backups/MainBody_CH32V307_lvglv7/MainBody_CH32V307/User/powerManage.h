/*
 * powerManage.h
 *
 *  Created on: 2025ƒÍ5‘¬6»’
 *      Author: ¡∫‘Û–¿
 */

#ifndef USER_POWERMANAGE_H_
#define USER_POWERMANAGE_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"
#include "stdint.h"

void powerOn_Init_Execute(void);
void powerMagage_Init(void);
u16 Get_ConversionVal(s16 val);
void getVolInPercent(uint16_t ADC_vol);
void powerOffDetect(void);


#endif /* USER_POWERMANAGE_H_ */
