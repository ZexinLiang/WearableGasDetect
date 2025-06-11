/*
 * control.h
 *
 *  Created on: 2025Äê6ÔÂ11ÈÕ
 *      Author: 86135
 */

#ifndef USER_INC_CONTROL_H_
#define USER_INC_CONTROL_H_
#include "CH58x_common.h"
#include "HAL.h"
#include "config.h"
#include "CH58xBLE_LIB.h"
#include "gattprofile.h"
#include "central.h"

void BLEDataTransfer(gattMsgEvent_t *pMsg);

#endif /* USER_INC_CONTROL_H_ */
