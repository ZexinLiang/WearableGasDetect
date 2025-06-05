/********************************** (C) COPYRIGHT *******************************
 * File Name          : gattprofile.C
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/10
 * Description        : Customize services with two attributes for CH9142 BLE compatibility:
 *                      - Write Characteristic (UUID: 0xFF01)
 *                      - Notify Characteristic (UUID: 0xFF02)
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

/*********************************************************************
 * CONSTANTS
 */
// Position of simpleProfilechar4 value in attribute array
#define SIMPLEPROFILE_CHAR4_VALUE_POS    7  // Updated position after removing unused characteristics

/*********************************************************************
 * GLOBAL VARIABLES
 */
// Simple GATT Profile Service UUID: 0xFFF0 (CH9142 default)
const uint8_t simpleProfileServUUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_SERV_UUID), HI_UINT16(SIMPLEPROFILE_SERV_UUID)};

// Characteristic 1 (Write) UUID: 0xFF01 (CH9142 TX -> CH582 RX)
const uint8_t simpleProfilechar1UUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_CHAR1_UUID), HI_UINT16(SIMPLEPROFILE_CHAR1_UUID)};

// Characteristic 4 (Notify) UUID: 0xFF02 (CH582 TX -> CH9142 RX)
const uint8_t simpleProfilechar4UUID[ATT_BT_UUID_SIZE] = {
    LO_UINT16(SIMPLEPROFILE_CHAR4_UUID), HI_UINT16(SIMPLEPROFILE_CHAR4_UUID)};

/*********************************************************************
 * LOCAL VARIABLES
 */
static simpleProfileCBs_t *simpleProfile_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */
static const gattAttrType_t simpleProfileService = {ATT_BT_UUID_SIZE, simpleProfileServUUID};

// Characteristic 1 (Write) Properties - Only WRITE for CH9142 TX
static uint8_t simpleProfileChar1Props = GATT_PROP_WRITE_NO_RSP;
static uint8_t simpleProfileChar1[SIMPLEPROFILE_CHAR1_LEN] = {0};
static uint8_t simpleProfileChar1UserDesp[] = "Write Characteristic (CH9142 TX)\0";

// Characteristic 4 (Notify) Properties - NOTIFY for CH582 TX
static uint8_t simpleProfileChar4Props = GATT_PROP_NOTIFY|GATT_PROP_READ;
static uint8_t simpleProfileChar4[SIMPLEPROFILE_CHAR4_LEN] = {0};
static gattCharCfg_t simpleProfileChar4Config[PERIPHERAL_MAX_CONNECTION];
static uint8_t simpleProfileChar4UserDesp[] = "Notify Characteristic (CH582 TX)\0";

/*********************************************************************
 * Profile Attributes - Table (Simplified for CH9142)
 */
static gattAttribute_t simpleProfileAttrTbl[] = {
    // Simple Profile Service
    {
        {ATT_BT_UUID_SIZE, primaryServiceUUID},
        GATT_PERMIT_READ,
        0,
        (uint8_t *)&simpleProfileService
    },

    // Characteristic 1 Declaration (Write: CH9142 -> CH582)
    {
        {ATT_BT_UUID_SIZE, characterUUID},
        GATT_PERMIT_READ,
        0,
        &simpleProfileChar1Props
    },
    // Characteristic Value 1 (UUID: 0xFF01)
    {
        {ATT_BT_UUID_SIZE, simpleProfilechar1UUID},
        GATT_PERMIT_WRITE,  // Only write permissions
        0,
        simpleProfileChar1
    },
    // Characteristic 1 User Description
    {
        {ATT_BT_UUID_SIZE, charUserDescUUID},
        GATT_PERMIT_READ,
        0,
        simpleProfileChar1UserDesp
    },

    // Characteristic 4 Declaration (Notify: CH582 -> CH9142)
    {
        {ATT_BT_UUID_SIZE, characterUUID},
        GATT_PERMIT_READ,
        0,
        &simpleProfileChar4Props
    },
    // Characteristic Value 4 (UUID: 0xFF02)
    {
        {ATT_BT_UUID_SIZE, simpleProfilechar4UUID},
        0,
        0,
        simpleProfileChar4
    },
    // Characteristic 4 Client Configuration (CCC)
    {
        {ATT_BT_UUID_SIZE, clientCharCfgUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8_t *)simpleProfileChar4Config
    },
    // Characteristic 4 User Description
    {
        {ATT_BT_UUID_SIZE, charUserDescUUID},
        GATT_PERMIT_READ,
        0,
        simpleProfileChar4UserDesp
    }
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen, uint16_t offset, uint16_t maxLen, uint8_t method);
static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len, uint16_t offset, uint8_t method);
static void simpleProfile_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType);

/*********************************************************************
 * PROFILE CALLBACKS
 */
gattServiceCBs_t simpleProfileCBs = {
    simpleProfile_ReadAttrCB,
    simpleProfile_WriteAttrCB,
    NULL
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
bStatus_t SimpleProfile_AddService(uint32_t services) {
    uint8_t status = SUCCESS;
    GATTServApp_InitCharCfg(INVALID_CONNHANDLE, simpleProfileChar4Config);
    linkDB_Register(simpleProfile_HandleConnStatusCB);

    if (services & SIMPLEPROFILE_SERVICE) {
        status = GATTServApp_RegisterService(simpleProfileAttrTbl,
                                             GATT_NUM_ATTRS(simpleProfileAttrTbl),
                                             GATT_MAX_ENCRYPT_KEY_SIZE,
                                             &simpleProfileCBs);
    }
    return status;
}

bStatus_t SimpleProfile_RegisterAppCBs(simpleProfileCBs_t *appCallbacks) {
    if (appCallbacks) {
        simpleProfile_AppCBs = appCallbacks;
        return SUCCESS;
    }
    return bleAlreadyInRequestedMode;
}

bStatus_t SimpleProfile_SetParameter(uint8_t param, uint16_t len, void *value) {
    bStatus_t ret = SUCCESS;
    switch (param) {
        case SIMPLEPROFILE_CHAR1:
            if (len == SIMPLEPROFILE_CHAR1_LEN) {
                tmos_memcpy(simpleProfileChar1, value, SIMPLEPROFILE_CHAR1_LEN);
            } else {
                ret = bleInvalidRange;
            }
            break;

        case SIMPLEPROFILE_CHAR4:
            if (len == SIMPLEPROFILE_CHAR4_LEN) {
                tmos_memcpy(simpleProfileChar4, value, SIMPLEPROFILE_CHAR4_LEN);
            } else {
                ret = bleInvalidRange;
            }
            break;

        default:
            ret = INVALIDPARAMETER;
            break;
    }
    return ret;
}

bStatus_t SimpleProfile_GetParameter(uint8_t param, void *value) {
    bStatus_t ret = SUCCESS;
    switch (param) {
        case SIMPLEPROFILE_CHAR1:
            tmos_memcpy(value, simpleProfileChar1, SIMPLEPROFILE_CHAR1_LEN);
            break;

        case SIMPLEPROFILE_CHAR4:
            tmos_memcpy(value, simpleProfileChar4, SIMPLEPROFILE_CHAR4_LEN);
            break;

        default:
            ret = INVALIDPARAMETER;
            break;
    }
    return ret;
}

bStatus_t simpleProfile_Notify(uint16_t connHandle, attHandleValueNoti_t *pNoti) {
    uint16_t value = GATTServApp_ReadCharCfg(connHandle, simpleProfileChar4Config);
    if (value & GATT_CLIENT_CFG_NOTIFY) {
        pNoti->handle = simpleProfileAttrTbl[SIMPLEPROFILE_CHAR4_VALUE_POS].handle;
        return GATT_Notification(connHandle, pNoti, FALSE);
    }
    return bleIncorrectMode;
}

/*********************************************************************
 * LOCAL FUNCTIONS (CALLBACKS)
 */
static bStatus_t simpleProfile_ReadAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                          uint8_t *pValue, uint16_t *pLen, uint16_t offset, uint16_t maxLen, uint8_t method) {
    bStatus_t status = SUCCESS;
    if (offset > 0) return ATT_ERR_ATTR_NOT_LONG;

    if (pAttr->type.len == ATT_BT_UUID_SIZE) {
        uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
        switch (uuid) {
            case SIMPLEPROFILE_CHAR4_UUID:  // Allow read for Notify characteristic (required by CH9142)
                *pLen = (maxLen > SIMPLEPROFILE_CHAR4_LEN) ? SIMPLEPROFILE_CHAR4_LEN : maxLen;
                tmos_memcpy(pValue, pAttr->pValue, *pLen);
                break;

            default:
                *pLen = 0;
                status = ATT_ERR_ATTR_NOT_FOUND;
                break;
        }
    } else {
        *pLen = 0;
        status = ATT_ERR_INVALID_HANDLE;
    }
    return status;
}

static bStatus_t simpleProfile_WriteAttrCB(uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t len, uint16_t offset, uint8_t method) {
    bStatus_t status = SUCCESS;
    uint8_t notifyApp = 0xFF;

    if (gattPermitAuthorWrite(pAttr->permissions)) {
        return ATT_ERR_INSUFFICIENT_AUTHOR;
    }

    if (pAttr->type.len == ATT_BT_UUID_SIZE) {
        uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
        switch (uuid) {
            case SIMPLEPROFILE_CHAR1_UUID:  // Write to Characteristic 1 (0xFF01)
                if (offset == 0 && len <= SIMPLEPROFILE_CHAR1_LEN) {
                    tmos_memcpy(pAttr->pValue, pValue, len);
                    notifyApp = SIMPLEPROFILE_CHAR1;
                } else {
                    status = (offset != 0) ? ATT_ERR_ATTR_NOT_LONG : ATT_ERR_INVALID_VALUE_SIZE;
                }
                break;

            case GATT_CLIENT_CHAR_CFG_UUID: // CCCD Write (Enable/Disable Notify)
                status = GATTServApp_ProcessCCCWriteReq(connHandle, pAttr, pValue, len,
                                                        offset, GATT_CLIENT_CFG_NOTIFY);
                break;

            default:
                status = ATT_ERR_ATTR_NOT_FOUND;
                break;
        }
    } else {
        status = ATT_ERR_INVALID_HANDLE;
    }
    if (pAttr->type.len == ATT_BT_UUID_SIZE) {
        uint16_t uuid = BUILD_UINT16(pAttr->type.uuid[0], pAttr->type.uuid[1]);
        switch (uuid) {
            // ... 其他特征处理 ...
            
            case GATT_CLIENT_CHAR_CFG_UUID: // CCCD 写入
                PRINT("CCCD Write: len=%d, data=%02X %02X\n", len, pValue[0], len > 1 ? pValue[1] : 0);
                status = GATTServApp_ProcessCCCWriteReq(connHandle, pAttr, pValue, len,
                                                        offset, GATT_CLIENT_CFG_NOTIFY);
                break;
        }
    }
    if (notifyApp != 0xFF && simpleProfile_AppCBs && simpleProfile_AppCBs->pfnSimpleProfileChange) {
        simpleProfile_AppCBs->pfnSimpleProfileChange(notifyApp, pValue, len);
    }

    return status;
}

static void simpleProfile_HandleConnStatusCB(uint16_t connHandle, uint8_t changeType) {
    if (connHandle != LOOPBACK_CONNHANDLE) {
        if ((changeType == LINKDB_STATUS_UPDATE_REMOVED) ||
            ((changeType == LINKDB_STATUS_UPDATE_STATEFLAGS) && (!linkDB_Up(connHandle)))) {
            GATTServApp_InitCharCfg(connHandle, simpleProfileChar4Config);
        }
    }
}