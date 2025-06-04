/********************************** (C) COPYRIGHT *******************************
 * File Name          : gattprofile.C
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/10
 * Description        : Customize services with five different attributes, 
 *                      including readable, writable, notification, 
 *                      readable and writable, and safe readable
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "CONFIG.h"
#include "gattprofile.h"


#define SIMPLEPROFILE_CHAR4_VALUE_POS    11
#define SIMPLEPROFILE_CHAR1_VALUE_POS    11

// Simple GATT Profile Service UUID: 0xFFF0
const uint8_t simpleProfileServUUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_SERV_UUID), HI_UINT16(SIMPLEPROFILE_SERV_UUID)};

// Characteristic 1 UUID: 0xFFF1
const uint8_t simpleProfileChar1UUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_CHAR1_UUID), HI_UINT16(SIMPLEPROFILE_CHAR1_UUID)};

// Characteristic 2 UUID: 0xFFF2
const uint8_t simpleProfileChar2UUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_CHAR2_UUID), HI_UINT16(SIMPLEPROFILE_CHAR2_UUID)};

// Characteristic 3 UUID: 0xFFF3
const uint8_t simpleProfileChar3UUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_CHAR3_UUID), HI_UINT16(SIMPLEPROFILE_CHAR3_UUID)};

static simpleProfileCBs_t *simpleProfile_AppCBs = NULL;

static const gattAttrType_t simpleProfileService = {ATT_BT_UUID_SIZE, simpleProfileServUUID};

static uint8_t simpleProfileChar1Props = GATT_PROP_READ | GATT_PROP_NOTIFY;
static uint8_t simpleProfileChar2Props = GATT_PROP_WRITE_NO_RSP;
static uint8_t simpleProfileChar3Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTIFY;

static uint8_t char1Value[20] = {0};
static uint8_t char2Value[20] = {0};
static uint8_t char3Value[20] = {0};

static gattCharCfg_t char1NotifyCfg[PERIPHERAL_MAX_CONNECTION];
static gattCharCfg_t char3NotifyCfg[PERIPHERAL_MAX_CONNECTION];

/*********************************************************************
 * Profile Attributes - Table
 */
static gattAttribute_t simpleProfileAttrTbl[] = {
    // Service declaration
    {{ATT_BT_UUID_SIZE, primaryServiceUUID}, GATT_PERMIT_READ, 0, (uint8_t *)simpleProfileServUUID},

    // Characteristic 1 Declaration
    {{ATT_BT_UUID_SIZE, characterUUID}, GATT_PERMIT_READ, 0, &simpleProfileChar1Props},
    // Characteristic 1 Value
    {{ATT_BT_UUID_SIZE, simpleProfileChar1UUID}, GATT_PERMIT_READ, 0, char1Value},
    // Characteristic 1 CCCD
    {{ATT_BT_UUID_SIZE, clientCharCfgUUID}, GATT_PERMIT_READ | GATT_PERMIT_WRITE, 0, (uint8_t *)char1NotifyCfg},

    // Characteristic 2 Declaration
    {{ATT_BT_UUID_SIZE, characterUUID}, GATT_PERMIT_READ, 0, &simpleProfileChar2Props},
    // Characteristic 2 Value
    {{ATT_BT_UUID_SIZE, simpleProfileChar2UUID}, GATT_PERMIT_WRITE, 0, char2Value},

    // Characteristic 3 Declaration
    {{ATT_BT_UUID_SIZE, characterUUID}, GATT_PERMIT_READ, 0, &simpleProfileChar3Props},
    // Characteristic 3 Value
    {{ATT_BT_UUID_SIZE, simpleProfileChar3UUID}, GATT_PERMIT_READ | GATT_PERMIT_WRITE, 0, char3Value},
    // Characteristic 3 CCCD
    {{ATT_BT_UUID_SIZE, clientCharCfgUUID}, GATT_PERMIT_READ | GATT_PERMIT_WRITE, 0, (uint8_t *)char3NotifyCfg},
};

static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint8_t *pLen, uint16_t offset,
                                          uint8_t maxLen)
{
    if (pAttr->type.len == ATT_BT_UUID_SIZE)
    {
        uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
        if (uuid == SIMPLEPROFILE_CHAR1_UUID)
        {
            *pLen = strlen((char *)char1Value);
            memcpy(pValue, char1Value, *pLen);
            return SUCCESS;
        }
        else if (uuid == SIMPLEPROFILE_CHAR3_UUID)
        {
            *pLen = strlen((char *)char3Value);
            memcpy(pValue, char3Value, *pLen);
            return SUCCESS;
        }
    }
    return ATT_ERR_ATTR_NOT_FOUND;
}

static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint8_t len, uint16_t offset)
{
    if (pAttr->type.len == ATT_BT_UUID_SIZE)
    {
        uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
        if (uuid == SIMPLEPROFILE_CHAR2_UUID)
        {
            memset(char2Value, 0, sizeof(char2Value));
            memcpy(char2Value, pValue, len);
            if (simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange)
                simpleProfile_AppCBs->pfnSimpleProfileChange(2,pValue);
            return SUCCESS;
        }
        else if (uuid == SIMPLEPROFILE_CHAR3_UUID)
        {
            memset(char3Value, 0, sizeof(char3Value));
            memcpy(char3Value, pValue, len);
            if (simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange)
                simpleProfile_AppCBs->pfnSimpleProfileChange(3,pValue);
            return SUCCESS;
        }
    }
    return ATT_ERR_ATTR_NOT_FOUND;
}

static gattServiceCBs_t simpleProfileCBs = {
    simpleProfile_ReadAttrCB,  // Read callback
    simpleProfile_WriteAttrCB, // Write callback
    NULL                       // Authorization not used
};

static void simpleProfile_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType);


bStatus_t SimpleProfile_AddService(void)
{
    GATTServApp_InitCharCfg(INVALID_CONNHANDLE, char1NotifyCfg);
    GATTServApp_InitCharCfg(INVALID_CONNHANDLE, char3NotifyCfg);
    return GATTServApp_RegisterService(simpleProfileAttrTbl, GATT_NUM_ATTRS(simpleProfileAttrTbl), GATT_MAX_ENCRYPT_KEY_SIZE, &simpleProfileCBs);
}

bStatus_t SimpleProfile_RegisterAppCBs(simpleProfileCBs_t *appCallbacks)
{
    if (appCallbacks)
    {
        simpleProfile_AppCBs = appCallbacks;
        return SUCCESS;
    }
    return bleAlreadyInRequestedMode;
}

bStatus_t SimpleProfile_SetParameter(uint8_t param, uint8_t len, void *value)
{
    switch(param)
    {
        case 1:
            memcpy(char1Value, value, len);
            break;
        case 2:
            memcpy(char2Value, value, len);
            break;
        case 3:
            memcpy(char3Value, value, len);
            break;
        default:
            return INVALIDPARAMETER;
    }
    return SUCCESS;
}

bStatus_t SimpleProfile_Notify(uint8_t charIndex, uint16_t connHandle, uint8_t *data, uint8_t len)
{
    attHandleValueNoti_t noti;
    noti.pValue = GATT_bm_alloc(connHandle, ATT_HANDLE_VALUE_NOTI, len, NULL, 0);
    if (!noti.pValue) return bleNoResources;

    memcpy(noti.pValue, data, len);
    noti.len = len;
    noti.handle = (charIndex == 1) ? simpleProfileAttrTbl[2].handle : simpleProfileAttrTbl[8].handle;

    return GATT_Notification(connHandle, &noti, (charIndex == 1) ? char1NotifyCfg : char3NotifyCfg);
}

bStatus_t SimpleProfile_GetParameter(uint8_t param, void *value)
{
    switch(param)
    {
        case 1:
            memcpy(value, char1Value, sizeof(char1Value));
            break;
        case 2:
            memcpy(value, char2Value, sizeof(char2Value));
            break;
        case 3:
            memcpy(value, char3Value, sizeof(char3Value));
            break;
        default:
            return INVALIDPARAMETER;
    }
    return SUCCESS;
}

void simpleProfile_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType)
{
    if (changeType == LINKDB_STATUS_UPDATE_REMOVED || (changeType == LINKDB_STATUS_UPDATE_STATEFLAGS && connHandle == INVALID_CONNHANDLE))
    {
        GATTServApp_InitCharCfg(connHandle, char1NotifyCfg);
        GATTServApp_InitCharCfg(connHandle, char3NotifyCfg);
    }
}
