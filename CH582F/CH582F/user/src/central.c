/********************************** (C) COPYRIGHT *******************************
* File Name          : central.c
* Author             : WCH
* Version            : V1.1
* Date               : 2020/08/06
* Description        : 主机例程，主动扫描周围设备，连接至给定的从机设备地址，
*                      寻找自定义服务及特征，执行读写命令，需与从机例程配合使用,
                       并将从机设备地址修改为该例程目标地址，默认为(84:C2:E4:03:02:02)
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
#include "central.h"
#include <string.h>

/*********************************************************************
 * MACROS
 */
#define CH9142_SERVICE_UUID  0xFFF0
#define CH9142_NOTIFY_UUID   0xFFF1
#define CH9142_WRITE_UUID    0xFFF2
#define DEFAULT_MAX_SCAN_RES                10
#define DEFAULT_SCAN_DURATION               2400
#define DEFAULT_MIN_CONNECTION_INTERVAL     20
#define DEFAULT_MAX_CONNECTION_INTERVAL     100
#define DEFAULT_CONNECTION_TIMEOUT          100
#define DEFAULT_DISCOVERY_MODE              DEVDISC_MODE_ALL
#define DEFAULT_DISCOVERY_ACTIVE_SCAN       TRUE
#define DEFAULT_DISCOVERY_WHITE_LIST        FALSE
#define DEFAULT_LINK_HIGH_DUTY_CYCLE        FALSE
#define DEFAULT_LINK_WHITE_LIST             FALSE
#define DEFAULT_RSSI_PERIOD                 2400
#define DEFAULT_UPDATE_MIN_CONN_INTERVAL    20
#define DEFAULT_UPDATE_MAX_CONN_INTERVAL    100
#define DEFAULT_UPDATE_SLAVE_LATENCY        0
#define DEFAULT_UPDATE_CONN_TIMEOUT         600
#define DEFAULT_PASSCODE                    0
#define DEFAULT_PAIRING_MODE                GAPBOND_PAIRING_MODE_WAIT_FOR_REQ
#define DEFAULT_MITM_MODE                   TRUE
#define DEFAULT_BONDING_MODE                TRUE
#define DEFAULT_IO_CAPABILITIES             GAPBOND_IO_CAP_NO_INPUT_NO_OUTPUT
#define DEFAULT_SVC_DISCOVERY_DELAY         1600
#define DEFAULT_PARAM_UPDATE_DELAY          3200
#define DEFAULT_PHY_UPDATE_DELAY            2400
#define DEFAULT_READ_OR_WRITE_DELAY         1600
#define DEFAULT_WRITE_CCCD_DELAY            1600
#define ESTABLISH_LINK_TIMEOUT              3200

#define SEND_DATA_TO_CH9142_EVT             0x0400
#define ENABLE_NOTIFY_EVT                   0x0800

// Application states
enum
{
    BLE_STATE_IDLE,
    BLE_STATE_CONNECTING,
    BLE_STATE_CONNECTED,
    BLE_STATE_DISCONNECTING
};

// Discovery states
enum
{
    BLE_DISC_STATE_IDLE, // Idle
    BLE_DISC_STATE_SVC,  // Service discovery
    BLE_DISC_STATE_CHAR, // Characteristic discovery
    BLE_DISC_STATE_CCCD  // client characteristic configuration discovery
};

static uint8_t centralTaskId;
static uint8_t centralScanRes;
static gapDevRec_t centralDevList[DEFAULT_MAX_SCAN_RES];
static uint8_t PeerAddrDef[B_ADDR_LEN] = {0x48, 0x0E, 0xBD, 0xA7, 0x14, 0x54};
static uint8_t centralRssi = TRUE;
static uint8_t centralParamUpdate = TRUE;
static uint8_t centralPhyUpdate = FALSE;
static uint16_t centralConnHandle = GAP_CONNHANDLE_INIT;
static uint8_t centralState = BLE_STATE_IDLE;
static uint8_t centralDiscState = BLE_DISC_STATE_IDLE;
static uint16_t centralSvcStartHdl = 0;
static uint16_t centralSvcEndHdl = 0;
static uint16_t centralCharHdl = 0;
static uint16_t centralCCCDHdl = 0;
static uint16_t centralReadCharHdl = 0;
static uint16_t centralWriteCharHdl = 0;
static uint8_t centralCharVal = 0x5A;
static uint8_t centralDoWrite = TRUE;
static uint8_t centralProcedureInProgress = FALSE;

static void centralProcessGATTMsg(gattMsgEvent_t *pMsg);
static void centralRssiCB(uint16_t connHandle, int8_t rssi);
static void centralEventCB(gapRoleEvent_t *pEvent);
static void centralHciMTUChangeCB(uint16_t connHandle, uint16_t maxTxOctets, uint16_t maxRxOctets);
static void centralPasscodeCB(uint8_t *deviceAddr, uint16_t connectionHandle,
                              uint8_t uiInputs, uint8_t uiOutputs);
static void centralPairStateCB(uint16_t connHandle, uint8_t state, uint8_t status);
static void central_ProcessTMOSMsg(tmos_event_hdr_t *pMsg);
static void centralGATTDiscoveryEvent(gattMsgEvent_t *pMsg);
static void centralStartDiscovery(void);
static void centralAddDeviceInfo(uint8_t *pAddr, uint8_t addrType);
/*********************************************************************
 * PROFILE CALLBACKS
 */

// GAP Role Callbacks
static gapCentralRoleCB_t centralRoleCB = {
    centralRssiCB,        // RSSI callback
    centralEventCB,       // Event callback
    centralHciMTUChangeCB // MTU change callback
};

// Bond Manager Callbacks
static gapBondCBs_t centralBondCB = {
    centralPasscodeCB,
    centralPairStateCB
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      Central_Init
 *
 * @brief   Initialization function for the Central App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notification).
 *
 * @param   task_id - the ID assigned by TMOS.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void Central_Init()
{
    centralTaskId = TMOS_ProcessEventRegister(Central_ProcessEvent);

    // Setup GAP
    GAP_SetParamValue(TGAP_DISC_SCAN, DEFAULT_SCAN_DURATION);
    GAP_SetParamValue(TGAP_CONN_EST_INT_MIN, DEFAULT_MIN_CONNECTION_INTERVAL);
    GAP_SetParamValue(TGAP_CONN_EST_INT_MAX, DEFAULT_MAX_CONNECTION_INTERVAL);
    GAP_SetParamValue(TGAP_CONN_EST_SUPERV_TIMEOUT, DEFAULT_CONNECTION_TIMEOUT);

    // Setup the GAP Bond Manager
    {
        uint32_t passkey = DEFAULT_PASSCODE;
        uint8_t  pairMode = DEFAULT_PAIRING_MODE;
        uint8_t  mitm = DEFAULT_MITM_MODE;
        uint8_t  ioCap = DEFAULT_IO_CAPABILITIES;
        uint8_t  bonding = DEFAULT_BONDING_MODE;

        GAPBondMgr_SetParameter(GAPBOND_CENT_DEFAULT_PASSCODE, sizeof(uint32_t), &passkey);
        GAPBondMgr_SetParameter(GAPBOND_CENT_PAIRING_MODE, sizeof(uint8_t), &pairMode);
        GAPBondMgr_SetParameter(GAPBOND_CENT_MITM_PROTECTION, sizeof(uint8_t), &mitm);
        GAPBondMgr_SetParameter(GAPBOND_CENT_IO_CAPABILITIES, sizeof(uint8_t), &ioCap);
        GAPBondMgr_SetParameter(GAPBOND_CENT_BONDING_ENABLED, sizeof(uint8_t), &bonding);
    }
    // Initialize GATT Client
    GATT_InitClient();
    // Register to receive incoming ATT Indications/Notifications
    GATT_RegisterForInd(centralTaskId);
    // Setup a delayed profile startup
    tmos_set_event(centralTaskId, START_DEVICE_EVT);
}

/*********************************************************************
 * @fn      Central_ProcessEvent
 *
 * @brief   Central Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id  - The TMOS assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16_t Central_ProcessEvent(uint8_t task_id, uint16_t events)
{
    if (events & SYS_EVENT_MSG)
    {
        uint8_t *pMsg;
        if ((pMsg = tmos_msg_receive(centralTaskId)) != NULL)
        {
            central_ProcessTMOSMsg((tmos_event_hdr_t *)pMsg);
            tmos_msg_deallocate(pMsg);
        }
        return (events ^ SYS_EVENT_MSG);
    }

    if (events & START_DEVICE_EVT)
    {
        GAPRole_CentralStartDevice(centralTaskId, &centralBondCB, &centralRoleCB);
        return (events ^ START_DEVICE_EVT);
    }

    if (events & ESTABLISH_LINK_TIMEOUT_EVT)
    {
        GAPRole_TerminateLink(INVALID_CONNHANDLE);
        return (events ^ ESTABLISH_LINK_TIMEOUT_EVT);
    }

    if (events & START_SVC_DISCOVERY_EVT)
    {
        centralStartDiscovery();
        return (events ^ START_SVC_DISCOVERY_EVT);
    }

    if (events & START_PARAM_UPDATE_EVT)
    {
        GAPRole_UpdateLink(centralConnHandle,
                           DEFAULT_UPDATE_MIN_CONN_INTERVAL,
                           DEFAULT_UPDATE_MAX_CONN_INTERVAL,
                           DEFAULT_UPDATE_SLAVE_LATENCY,
                           DEFAULT_UPDATE_CONN_TIMEOUT);
        return (events ^ START_PARAM_UPDATE_EVT);
    }

    if (events & START_PHY_UPDATE_EVT)
    {
        PRINT("PHY Update %x...\n", GAPRole_UpdatePHY(centralConnHandle, 0,
              GAP_PHY_BIT_LE_2M, GAP_PHY_BIT_LE_2M, GAP_PHY_OPTIONS_NOPRE));
        return (events ^ START_PHY_UPDATE_EVT);
    }

//    if (events & START_READ_OR_WRITE_EVT)
//    {
//        if (centralProcedureInProgress == FALSE)
//        {
//            if (centralDoWrite)
//            {
//                uint8_t msg[] = "HiCH9142";
//                Central_SendDataToCH9142();
//                centralDoWrite = !centralDoWrite;
//            }
//            else
//            {
//                attReadReq_t req;
//                req.handle = centralReadCharHdl;
//                if (GATT_ReadCharValue(centralConnHandle, &req, centralTaskId) == SUCCESS)
//                {
//                    centralProcedureInProgress = TRUE;
//                    centralDoWrite = !centralDoWrite;
//                }
//            }
//            tmos_start_task(centralTaskId, START_READ_OR_WRITE_EVT, DEFAULT_READ_OR_WRITE_DELAY);
//        }
//        return (events ^ START_READ_OR_WRITE_EVT);
//    }

    if (events & START_WRITE_CCCD_EVT)
    {
        if (centralProcedureInProgress == FALSE)
        {
            attWriteReq_t req;
            req.cmd = FALSE;
            req.sig = FALSE;
            req.handle = centralCCCDHdl;
            req.len = 2;
            req.pValue = GATT_bm_alloc(centralConnHandle, ATT_WRITE_REQ, req.len, NULL, 0);
            if (req.pValue != NULL)
            {
                req.pValue[0] = 1;
                req.pValue[1] = 0;
                if (GATT_WriteCharValue(centralConnHandle, &req, centralTaskId) == SUCCESS)
                {
                    centralProcedureInProgress = TRUE;
                }
                else
                {
                    GATT_bm_free((gattMsg_t *)&req, ATT_WRITE_REQ);
                }
            }
        }
        return (events ^ START_WRITE_CCCD_EVT);
    }

    if (events & START_READ_RSSI_EVT)
    {
        GAPRole_ReadRssiCmd(centralConnHandle);
        tmos_start_task(centralTaskId, START_READ_RSSI_EVT, DEFAULT_RSSI_PERIOD);
        return (events ^ START_READ_RSSI_EVT);
    }

    if (events & ENABLE_NOTIFY_EVT)
    {
        Central_EnableNotify();
        return (events ^ ENABLE_NOTIFY_EVT);
    }

    if (events & SEND_DATA_TO_CH9142_EVT)
    {
        Central_SendDataToCH9142();
        return (events ^ SEND_DATA_TO_CH9142_EVT);
    }

    return 0;
}

/*********************************************************************
 * @fn      central_ProcessTMOSMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void central_ProcessTMOSMsg(tmos_event_hdr_t *pMsg)
{
    switch(pMsg->event)
    {
        case GATT_MSG_EVENT:
            centralProcessGATTMsg((gattMsgEvent_t *)pMsg);
            break;
    }
}

/*********************************************************************
 * @fn      centralProcessGATTMsg
 *
 * @brief   Process GATT messages
 *
 * @return  none
 */
static void centralProcessGATTMsg(gattMsgEvent_t *pMsg)
{
    if (centralState != BLE_STATE_CONNECTED)
    {
        GATT_bm_free(&pMsg->msg, pMsg->method);
        return;
    }

    if ((pMsg->method == ATT_EXCHANGE_MTU_RSP) ||
        ((pMsg->method == ATT_ERROR_RSP) &&
         (pMsg->msg.errorRsp.reqOpcode == ATT_EXCHANGE_MTU_REQ)))
    {
        if (pMsg->method == ATT_ERROR_RSP)
        {
            uint8_t status = pMsg->msg.errorRsp.errCode;
            PRINT("Exchange MTU Error: %x\n", status);
        }
        centralProcedureInProgress = FALSE;
    }
    else if (pMsg->method == ATT_MTU_UPDATED_EVENT)
    {
        PRINT("MTU: %d\n", pMsg->msg.mtuEvt.MTU);
    }
    else if ((pMsg->method == ATT_READ_RSP) ||
             ((pMsg->method == ATT_ERROR_RSP) &&
              (pMsg->msg.errorRsp.reqOpcode == ATT_READ_REQ)))
    {
        if (pMsg->method == ATT_ERROR_RSP)
        {
            uint8_t status = pMsg->msg.errorRsp.errCode;
            PRINT("Read Error: %x\n", status);
        }
        else
        {
            PRINT("Read rsp: %x\n", *pMsg->msg.readRsp.pValue);
        }
        centralProcedureInProgress = FALSE;
    }
    else if ((pMsg->method == ATT_WRITE_RSP) ||
             ((pMsg->method == ATT_ERROR_RSP) &&
              (pMsg->msg.errorRsp.reqOpcode == ATT_WRITE_REQ)))
    {
        if (pMsg->method == ATT_ERROR_RSP)
        {
            uint8_t status = pMsg->msg.errorRsp.errCode;
            PRINT("Write Error: %x\n", status);
        }
        else
        {
            PRINT("Write success\n");
        }
        centralProcedureInProgress = FALSE;
    }
    else if (pMsg->method == ATT_HANDLE_VALUE_NOTI)
    {
        HandleNotifyEvent(pMsg);
    }
    else if (centralDiscState != BLE_DISC_STATE_IDLE)
    {
        centralGATTDiscoveryEvent(pMsg);
    }

    GATT_bm_free(&pMsg->msg, pMsg->method);
}

/*********************************************************************
 * @fn      centralRssiCB
 *
 * @brief   RSSI callback.
 *
 * @param   connHandle - connection handle
 * @param   rssi - RSSI
 *
 * @return  none
 */
static void centralRssiCB(uint16_t connHandle, int8_t rssi)
{
    PRINT("RSSI : -%d dB \n", -rssi);
}

/*********************************************************************
 * @fn      centralHciMTUChangeCB
 *
 * @brief   MTU changed callback.
 *
 * @param   maxTxOctets - Max tx octets
 * @param   maxRxOctets - Max rx octets
 *
 * @return  none
 */
static void centralHciMTUChangeCB(uint16_t connHandle, uint16_t maxTxOctets, uint16_t maxRxOctets)
{
    PRINT(" HCI data length changed, Tx: %d, Rx: %d\n", maxTxOctets, maxRxOctets);
    centralProcedureInProgress = TRUE;
}

/*********************************************************************
 * @fn      centralEventCB
 *
 * @brief   Central event callback function.
 *
 * @param   pEvent - pointer to event structure
 *
 * @return  none
 */
static void centralEventCB(gapRoleEvent_t *pEvent)
{
    switch(pEvent->gap.opcode)
    {
        case GAP_DEVICE_INIT_DONE_EVENT:
        {
            PRINT("Discovering...\n");
            GAPRole_CentralStartDiscovery(DEFAULT_DISCOVERY_MODE,
                                          DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                          DEFAULT_DISCOVERY_WHITE_LIST);
        }
        break;

        case GAP_DEVICE_INFO_EVENT:
        {
            // Add device to list
            centralAddDeviceInfo(pEvent->deviceInfo.addr, pEvent->deviceInfo.addrType);
        }
        break;

        case GAP_DEVICE_DISCOVERY_EVENT:
        {
            uint8_t i;

            // See if peer device has been discovered
            for(i = 0; i < centralScanRes; i++)
            {
                if(tmos_memcmp(PeerAddrDef, centralDevList[i].addr, B_ADDR_LEN))
                    break;
            }

            // Peer device not found
            if(i == centralScanRes)
            {
                PRINT("Device not found...\n");
                centralScanRes = 0;
                GAPRole_CentralStartDiscovery(DEFAULT_DISCOVERY_MODE,
                                              DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                              DEFAULT_DISCOVERY_WHITE_LIST);
                PRINT("Discovering...\n");
            }

            // Peer device found
            else
            {
                PRINT("Device found...\n");
                GAPRole_CentralEstablishLink(DEFAULT_LINK_HIGH_DUTY_CYCLE,
                                             DEFAULT_LINK_WHITE_LIST,
                                             centralDevList[i].addrType,
                                             centralDevList[i].addr);

                // Start establish link timeout event
                tmos_start_task(centralTaskId, ESTABLISH_LINK_TIMEOUT_EVT, ESTABLISH_LINK_TIMEOUT);
                PRINT("Connecting...\n");
            }
        }
        break;

        case GAP_LINK_ESTABLISHED_EVENT:
        {
            tmos_stop_task(centralTaskId, ESTABLISH_LINK_TIMEOUT_EVT);
            if(pEvent->gap.hdr.status == SUCCESS)
            {
                centralState = BLE_STATE_CONNECTED;
                centralConnHandle = pEvent->linkCmpl.connectionHandle;
                centralProcedureInProgress = TRUE;
               
                // Update MTU
                attExchangeMTUReq_t req = {
                    .clientRxMTU = BLE_BUFF_MAX_LEN - 4,
                };

                GATT_ExchangeMTU(centralConnHandle, &req, centralTaskId);

                // Initiate service discovery
                tmos_start_task(centralTaskId, START_SVC_DISCOVERY_EVT, DEFAULT_SVC_DISCOVERY_DELAY);

                // See if initiate connect parameter update
                if(centralParamUpdate)
                {
                    tmos_start_task(centralTaskId, START_PARAM_UPDATE_EVT, DEFAULT_PARAM_UPDATE_DELAY);
                }
                // See if initiate phy update
                if(centralPhyUpdate)
                {
                    tmos_start_task(centralTaskId, START_PHY_UPDATE_EVT, DEFAULT_PHY_UPDATE_DELAY);
                }
                // See if start RSSI polling
                if(centralRssi)
                {
                    tmos_start_task(centralTaskId, START_READ_RSSI_EVT, DEFAULT_RSSI_PERIOD);
                }

                PRINT("Connected...\n");
            }
            else
            {
                PRINT("Connect Failed...Reason:%X\n", pEvent->gap.hdr.status);
                PRINT("Discovering...\n");
                centralScanRes = 0;
                GAPRole_CentralStartDiscovery(DEFAULT_DISCOVERY_MODE,
                                              DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                              DEFAULT_DISCOVERY_WHITE_LIST);
            }
        }
        break;

        case GAP_LINK_TERMINATED_EVENT:
        {
            centralState = BLE_STATE_IDLE;
            centralConnHandle = GAP_CONNHANDLE_INIT;
            centralDiscState = BLE_DISC_STATE_IDLE;
            centralCharHdl = 0;
            centralScanRes = 0;
            centralProcedureInProgress = FALSE;
            tmos_stop_task(centralTaskId, START_READ_RSSI_EVT);
            PRINT("Disconnected...Reason:%x\n", pEvent->linkTerminate.reason);
            PRINT("Discovering...\n");
            GAPRole_CentralStartDiscovery(DEFAULT_DISCOVERY_MODE,
                                          DEFAULT_DISCOVERY_ACTIVE_SCAN,
                                          DEFAULT_DISCOVERY_WHITE_LIST);
        }
        break;

        case GAP_LINK_PARAM_UPDATE_EVENT:
        {
            PRINT("Param Update...\n");
        }
        break;

        case GAP_PHY_UPDATE_EVENT:
        {
            PRINT("PHY Update...\n");
        }
        break;

        case GAP_EXT_ADV_DEVICE_INFO_EVENT:
        {
            // Display device addr
            PRINT("Recv ext adv \n");
            // Add device to list
            centralAddDeviceInfo(pEvent->deviceExtAdvInfo.addr, pEvent->deviceExtAdvInfo.addrType);
        }
        break;

        case GAP_DIRECT_DEVICE_INFO_EVENT:
        {
            // Display device addr
            PRINT("Recv direct adv \n");
            // Add device to list
            centralAddDeviceInfo(pEvent->deviceDirectInfo.addr, pEvent->deviceDirectInfo.addrType);
        }
        break;

        default:
            break;
    }
}

/*********************************************************************
 * @fn      pairStateCB
 *
 * @brief   Pairing state callback.
 *
 * @return  none
 */
static void centralPairStateCB(uint16_t connHandle, uint8_t state, uint8_t status)
{
    if(state == GAPBOND_PAIRING_STATE_STARTED)
    {
        PRINT("Pairing started:%d\n", status);
    }
    else if(state == GAPBOND_PAIRING_STATE_COMPLETE)
    {
        if(status == SUCCESS)
        {
            PRINT("Pairing success\n");
        }
        else
        {
            PRINT("Pairing fail\n");
        }
    }
    else if(state == GAPBOND_PAIRING_STATE_BONDED)
    {
        if(status == SUCCESS)
        {
            PRINT("Bonding success\n");
        }
    }
    else if(state == GAPBOND_PAIRING_STATE_BOND_SAVED)
    {
        if(status == SUCCESS)
        {
            PRINT("Bond save success\n");
        }
        else
        {
            PRINT("Bond save failed: %d\n", status);
        }
    }
}

/*********************************************************************
 * @fn      centralPasscodeCB
 *
 * @brief   Passcode callback.
 *
 * @return  none
 */
static void centralPasscodeCB(uint8_t *deviceAddr, uint16_t connectionHandle,
                              uint8_t uiInputs, uint8_t uiOutputs)
{
    uint32_t passcode;

    // Create random passcode
    passcode = tmos_rand();
    passcode %= 1000000;
    // Display passcode to user
    if(uiOutputs != 0)
    {
        PRINT("Passcode:%06d\n", (int)passcode);
    }
    // Send passcode response
    GAPBondMgr_PasscodeRsp(connectionHandle, SUCCESS, passcode);
}

/*********************************************************************
 * @fn      centralStartDiscovery
 *
 * @brief   Start service discovery.
 *
 * @return  none
 */
static void centralStartDiscovery(void)
{
//    uint8_t uuid[ATT_BT_UUID_SIZE] = {LO_UINT16(SIMPLEPROFILE_SERV_UUID),
//                                      HI_UINT16(SIMPLEPROFILE_SERV_UUID)};
    uint8_t uuid[ATT_BT_UUID_SIZE] = {LO_UINT16(0xfff0),
                                      HI_UINT16(0xfff0)};
    // Initialize cached handles
    centralSvcStartHdl = centralSvcEndHdl = centralCharHdl = 0;

    centralDiscState = BLE_DISC_STATE_SVC;

    // Discovery simple BLE service
    GATT_DiscPrimaryServiceByUUID(centralConnHandle,
                                  uuid,
                                  ATT_BT_UUID_SIZE,
                                  centralTaskId);
}

/*********************************************************************
 * @fn      centralGATTDiscoveryEvent
 *
 * @brief   Process GATT discovery event
 *
 * @return  none
 */
static void centralGATTDiscoveryEvent(gattMsgEvent_t *pMsg)
{
    attReadByTypeReq_t req;

    if (centralDiscState == BLE_DISC_STATE_SVC)
    {
        // 服务发现成功
        if (pMsg->method == ATT_FIND_BY_TYPE_VALUE_RSP &&
            pMsg->msg.findByTypeValueRsp.numInfo > 0)
        {
            centralSvcStartHdl = ATT_ATTR_HANDLE(pMsg->msg.findByTypeValueRsp.pHandlesInfo, 0);
            centralSvcEndHdl = ATT_GRP_END_HANDLE(pMsg->msg.findByTypeValueRsp.pHandlesInfo, 0);
            PRINT("发现CH9142服务: 起始句柄=0x%04X, 结束句柄=0x%04X\n",
                  centralSvcStartHdl, centralSvcEndHdl);
        }

        // 服务发现完成
        if ((pMsg->method == ATT_FIND_BY_TYPE_VALUE_RSP &&
             pMsg->hdr.status == bleProcedureComplete) ||
            (pMsg->method == ATT_ERROR_RSP))
        {
            if (centralSvcStartHdl != 0)
            {
                // 开始发现特征
                centralDiscState = BLE_DISC_STATE_CHAR;

                // 设置发现所有特征
                req.startHandle = centralSvcStartHdl;
                req.endHandle = centralSvcEndHdl;
                req.type.len = ATT_BT_UUID_SIZE;
                req.type.uuid[0] = LO_UINT16(GATT_CHARACTER_UUID);
                req.type.uuid[1] = HI_UINT16(GATT_CHARACTER_UUID);

                PRINT("开始发现特征...\n");
                GATT_ReadUsingCharUUID(centralConnHandle, &req, centralTaskId);
            }
            else
            {
                PRINT("错误: 未找到CH9142服务\n");
                centralDiscState = BLE_DISC_STATE_IDLE;
            }
        }
    }
    else if (centralDiscState == BLE_DISC_STATE_CHAR)
    {
        // 处理特征发现响应
        if (pMsg->method == ATT_READ_BY_TYPE_RSP &&
            pMsg->msg.readByTypeRsp.numPairs > 0)
        {
            uint8_t *pData = pMsg->msg.readByTypeRsp.pDataList;
            uint8_t pairLen = pMsg->msg.readByTypeRsp.len;

            for (uint8_t i = 0; i < pMsg->msg.readByTypeRsp.numPairs; i++, pData += pairLen)
            {
                uint16_t charHandle = BUILD_UINT16(pData[0], pData[1]);
                uint8_t  properties = pData[2];
                uint16_t charUuid = BUILD_UINT16(pData[5], pData[6]);

                // 检查是否是目标特征
                if (charUuid == CH9142_NOTIFY_UUID)  // 通知特征
                {
                    centralReadCharHdl = charHandle;
                    PRINT("发现通知特征(FFF1): 句柄=0x%04X, 属性=0x%02X\n",
                          charHandle, properties);
                }
                else if (charUuid == CH9142_WRITE_UUID)  // 写入特征
                {
                    centralWriteCharHdl = charHandle;
                    PRINT("发现写入特征(FFF2): 句柄=0x%04X, 属性=0x%02X\n",
                          charHandle, properties);
                }
            }
        }

        // 特征发现完成
        if ((pMsg->method == ATT_READ_BY_TYPE_RSP &&
             pMsg->hdr.status == bleProcedureComplete) ||
            (pMsg->method == ATT_ERROR_RSP))
        {
            // 检查是否找到写入特征（必须）
            if (centralWriteCharHdl != 0)
            {
                PRINT("特征发现完成，准备数据传输\n");

                // 如果找到通知特征，假设其CCCD句柄为特征值句柄+1
                if (centralReadCharHdl != 0) {
                    centralCCCDHdl = centralReadCharHdl + 1;
                    PRINT("假设CCCD句柄为0x%04X\n", centralCCCDHdl);
                }

                // 立即发送数据
                tmos_set_event(centralTaskId, SEND_DATA_TO_CH9142_EVT);

                // 如果找到通知特征，启用通知
                if (centralReadCharHdl != 0)
                {
                    PRINT("启用通知特征\n");
                    tmos_set_event(centralTaskId, ENABLE_NOTIFY_EVT);
                }
            }
            else
            {
                PRINT("错误: 未找到写入特征(FFF2)\n");
            }

            centralDiscState = BLE_DISC_STATE_IDLE;
            centralProcedureInProgress = FALSE;
        }
    }
}
/*********************************************************************
 * @fn      centralAddDeviceInfo
 *
 * @brief   Add a device to the device discovery result list
 *
 * @return  none
 */
static void centralAddDeviceInfo(uint8_t *pAddr, uint8_t addrType)
{
    uint8_t i;

    // If result count not at max
    if(centralScanRes < DEFAULT_MAX_SCAN_RES)
    {
        // Check if device is already in scan results
        for(i = 0; i < centralScanRes; i++)
        {
            if(tmos_memcmp(pAddr, centralDevList[i].addr, B_ADDR_LEN))
            {
                return;
            }
        }
        // Add addr to scan result list
        tmos_memcpy(centralDevList[centralScanRes].addr, pAddr, B_ADDR_LEN);
        centralDevList[centralScanRes].addrType = addrType;
        // Increment scan result count
        centralScanRes++;
        // Display device addr
        PRINT("Device %d - Addr %x %x %x %x %x %x \n", centralScanRes,
              centralDevList[centralScanRes - 1].addr[0],
              centralDevList[centralScanRes - 1].addr[1],
              centralDevList[centralScanRes - 1].addr[2],
              centralDevList[centralScanRes - 1].addr[3],
              centralDevList[centralScanRes - 1].addr[4],
              centralDevList[centralScanRes - 1].addr[5]);
    }
}

void Central_SendDataToCH9142(void)
{
    if (centralWriteCharHdl == 0 || centralState != BLE_STATE_CONNECTED)
    {
        PRINT("写入失败: 未连接或无效句柄\n");
        return;
    }

    // 实际数据发送逻辑
    uint8_t payload[] = "Hello CH9142"; // 测试数据
    uint16_t len = sizeof(payload) - 1; // 不包含结尾的0

    attWriteReq_t req;
    req.cmd = TRUE; // 无响应写入
    req.sig = FALSE;
    req.handle = centralWriteCharHdl;
    req.len = len;

    req.pValue = GATT_bm_alloc(centralConnHandle, ATT_WRITE_CMD, len, NULL, 0);
    if (req.pValue)
    {
        memcpy(req.pValue, payload, len);
        if (GATT_WriteNoRsp(centralConnHandle, &req) != SUCCESS)
        {
            GATT_bm_free((gattMsg_t *)&req, ATT_WRITE_CMD);
            PRINT("写入失败\n");
        }
        else
        {
            PRINT("数据发送成功: %s\n", payload);
        }
    }
    else
    {
        PRINT("内存分配失败\n");
    }
}

void Central_EnableNotify(void)
{
    if (centralCCCDHdl == 0 || centralState != BLE_STATE_CONNECTED)
    {
        PRINT("CCCD not ready or not connected\n");
        return;
    }

    uint8_t val[2] = {0x01, 0x00}; // Enable notify
    attWriteReq_t req;
    req.cmd = FALSE;
    req.sig = FALSE;
    req.handle = centralCCCDHdl;
    req.len = 2;
    req.pValue = GATT_bm_alloc(centralConnHandle, ATT_WRITE_REQ, 2, NULL, 0);
    if (req.pValue)
    {
        memcpy(req.pValue, val, 2);
        if (GATT_WriteCharValue(centralConnHandle, &req, centralTaskId) != SUCCESS)
        {
            GATT_bm_free((gattMsg_t *)&req, ATT_WRITE_REQ);
            PRINT("Enable notify failed\n");
        }
        else
        {
            PRINT("Notify enabled\n");
        }
    }
    else
    {
        PRINT("GATT_bm_alloc failed for CCCD\n");
    }
}

void HandleCharDiscovery(attReadByTypeRsp_t *pRsp)
{
    for (uint8_t i = 0; i < pRsp->numPairs; i++)
    {
        uint8_t *pData = pRsp->pDataList + i * pRsp->len;
        uint16_t handle = BUILD_UINT16(pData[0], pData[1]);
        uint16_t charUuid = BUILD_UINT16(pData[5], pData[6]);

        if (charUuid == 0xFFF1)
        {
            centralReadCharHdl = handle;
            PRINT("Found FFF1 (notify) handle: 0x%04X\n", handle);
        }
        else if (charUuid == 0xFFF2)
        {
            centralWriteCharHdl = handle;
            PRINT("Found FFF2 (write) handle: 0x%04X\n", handle);
            tmos_start_task(centralTaskId, SEND_DATA_TO_CH9142_EVT, 100);
        }
    }
}

void HandleNotifyEvent(gattMsgEvent_t *pMsg)
{
    if (pMsg->method == ATT_HANDLE_VALUE_NOTI) {
        uint8_t len = pMsg->msg.handleValueNoti.len;
        uint8_t *data = pMsg->msg.handleValueNoti.pValue;

        // 实际数据处理逻辑
        PRINT("收到通知数据(%d字节): ", len);
        for (uint8_t i = 0; i < len; i++) {
            PRINT("%02X ", data[i]);
        }
        PRINT("\n");

        // 可以在这里添加数据处理代码
        // 例如: processCH9142Data(data, len);
    }
}
/************************ endfile @ central **************************/
