/********************************** (C) COPYRIGHT *******************************
 * File Name          : gattprofile.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef GATTPROFILE_H
#define GATTPROFILE_H

#ifdef __cplusplus
extern "C" {
#endif


// Profile Parameters
#define SIMPLEPROFILE_CHAR1         0           // RW uint8_t - Profile Characteristic 1 value
#define SIMPLEPROFILE_CHAR2         1           // RW uint8_t - Profile Characteristic 2 value
#define SIMPLEPROFILE_CHAR3         2           // RW uint8_t - Profile Characteristic 3 value

// Simple Profile Service UUID
#define SIMPLEPROFILE_SERV_UUID     0xFFF0

// Key Pressed UUID
#define SIMPLEPROFILE_CHAR1_UUID    0xFFF1
#define SIMPLEPROFILE_CHAR2_UUID    0xFFF2
#define SIMPLEPROFILE_CHAR3_UUID    0xFFF3

// Simple Keys Profile Services bit fields
#define SIMPLEPROFILE_SERVICE       0x00000001

// Length of characteristic in bytes ( Default MTU is 23 )
#define SIMPLEPROFILE_CHAR1_LEN     20
#define SIMPLEPROFILE_CHAR2_LEN     20
#define SIMPLEPROFILE_CHAR3_LEN     20


// Callback when a characteristic value has changed
typedef void (*simpleProfileChange_t)(uint8_t paramID, uint8_t *value);

typedef struct
{
    simpleProfileChange_t pfnSimpleProfileChange; // Called when characteristic value changes
} simpleProfileCBs_t;

/*********************************************************************
 * API FUNCTIONS
 */

/*
 * SimpleProfile_AddService- Initializes the Simple GATT Profile service by registering
 *          GATT attributes with the GATT server.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 */

extern bStatus_t SimpleProfile_AddService(void);

/*
 * SimpleProfile_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t SimpleProfile_RegisterAppCBs(simpleProfileCBs_t *appCallbacks);

/*
 * SimpleProfile_SetParameter - Set a Simple GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 */
extern bStatus_t SimpleProfile_SetParameter(uint8_t param, uint8_t len, void *value);

/*
 * SimpleProfile_GetParameter - Get a Simple GATT Profile parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16_t will be cast to
 *          uint16_t pointer).
 */
extern bStatus_t SimpleProfile_GetParameter(uint8_t param, void *value);

/*
 * simpleProfile_Notify - Send notification.
 *
 *    connHandle - connect handle
 *    pNoti - pointer to structure to notify.
 */
bStatus_t SimpleProfile_Notify(uint8_t charIndex, uint16_t connHandle, uint8_t *data, uint8_t len)

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
