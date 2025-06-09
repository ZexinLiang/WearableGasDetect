/*
 * bmeInRegis.h
 *
 *  Created on: 2025年3月1日
 *      Author: 86135
 */

#ifndef USER_INC_BMEINREGIS_H_
#define USER_INC_BMEINREGIS_H_

#include "i2c.h"

//计算时公用数据
typedef struct BME688PbData{
    double t_fine;
}PBData_TypeDef;

uint8_t BME688InitInReg(void);

void BME688_TempGet(double* temp);

void BME688_PresGet(double* pressure);

#endif /* USER_INC_BMEINREGIS_H_ */
