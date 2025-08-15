/*
 * periodicalTask.h
 *
 *  Created on: 2025Äê5ÔÂ6ÈÕ
 *      Author: 86135
 */

#ifndef USER_PERIODICALTASK_H_
#define USER_PERIODICALTASK_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"
#include "stdint.h"
#include "powerManage.h"

typedef struct errmsg{
    uint8_t rherr;
    uint8_t co2err;
    uint8_t o2err;
    uint8_t temperr;
    uint8_t gasrerr;
    uint8_t preserr;
    uint8_t manualerr;
}ERR_TypeDef;

void TIM2_Trigger_Init(u16 arr, u16 psc);

#endif /* USER_PERIODICALTASK_H_ */
