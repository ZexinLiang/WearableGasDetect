/*
 * periodicalTask.h
 *
 *  Created on: 2025��5��6��
 *      Author: 86135
 */

#ifndef USER_PERIODICALTASK_H_
#define USER_PERIODICALTASK_H_

#include "ch32v30x.h"
#include "ch32v30x_conf.h"
#include "stdint.h"
#include "powerManage.h"

void TIM2_Trigger_Init(u16 arr, u16 psc);

#endif /* USER_PERIODICALTASK_H_ */
