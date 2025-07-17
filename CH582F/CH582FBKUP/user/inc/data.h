/*
 * data.h
 *
 *  Created on: 2025Äê6ÔÂ10ÈÕ
 *      Author: 86135
 */

#ifndef USER_INC_DATA_H_
#define USER_INC_DATA_H_

#include "CH58x_common.h"
#include "HAL.h"
#include "config.h"
#include "CH58xBLE_LIB.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "i2c.h"
#include "task.h"
#include "jed.h"
#include "bmeInRegis.h"
#include "scd40reg.h"
#include "bme68x.h"
#include "bme68x_defs.h"
#include "bmelink.h"

typedef struct DataTab{
    float temp1;
    float pres1;
    float humi1;
    float gasRes;
    uint8_t humi2;
    uint8_t temp2;
    uint16_t CO2;
    uint16_t gas1;
}DataTab_TypeDef;

void BleMsgOutput(char* msg);

#endif /* USER_INC_DATA_H_ */
