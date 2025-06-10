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
    double temp_comp;
}PBData_TypeDef;

void BME688_Test(void);

uint8_t BME688_ForceModeCFG(void);

void BME688_TempGet(double* temp);

void BME688_PresGet(double* pressure);

void BME688_HumiGet(double* humidity);

void BME688_HeatResGet(double target_temp,uint8_t* res_heat_x);

uint8_t BME688_MeaStusGet(void);

#endif /* USER_INC_BMEINREGIS_H_ */
