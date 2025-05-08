/*
 * task.h
 *
 *  Created on: 2025ƒÍ2‘¬6»’
 *      Author: ¡∫‘Û–¿
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include "CH58x_common.h"
#include "HAL.h"
#include "config.h"
#include "RF_PHY.h"
#include "CH58xBLE_LIB.h"
#include "i2c.h"

void taskInit(void);

uint16_t ProcessEvent(uint8_t task_id, uint16_t events);

#endif /* INC_TASK_H_ */
