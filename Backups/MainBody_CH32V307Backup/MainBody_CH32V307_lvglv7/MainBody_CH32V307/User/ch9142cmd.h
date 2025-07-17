/*
 * ch9142cmd.h
 *
 *  Created on: 2025年6月1日
 *      Author: lzx
 */

#ifndef USER_CH9142CMD_H_
#define USER_CH9142CMD_H_

#include "ch32v30x.h"
#include <stdint.h>

// 主发送接口
void CH9142_SendCommand(USART_TypeDef* USARTx, const char* cmd);

//IO进入/退出AT
void CH9142_ATIO_IN(USART_TypeDef* USARTx);
void CH9142_ATIO_EXIT(USART_TypeDef* USARTx);

// 基本控制类
void CH9142_AT(USART_TypeDef* USARTx);
void CH9142_Reset(USART_TypeDef* USARTx);
void CH9142_ExitAT(USART_TypeDef* USARTx);

// 信息获取类
void CH9142_GetVersion(USART_TypeDef* USARTx);
void CH9142_GetUART(USART_TypeDef* USARTx);
void CH9142_GetMAC(USART_TypeDef* USARTx);
void CH9142_GetBLEStatus(USART_TypeDef* USARTx);
void CH9142_GetBLEMode(USART_TypeDef* USARTx);
void CH9142_GetName(USART_TypeDef* USARTx);
void CH9142_GetPName(USART_TypeDef* USARTx);
void CH9142_GetSysID(USART_TypeDef* USARTx);
void CH9142_GetModName(USART_TypeDef* USARTx);
void CH9142_GetSeriNum(USART_TypeDef* USARTx);
void CH9142_GetFirmRev(USART_TypeDef* USARTx);
void CH9142_GetHardRev(USART_TypeDef* USARTx);
void CH9142_GetSoftRev(USART_TypeDef* USARTx);
void CH9142_GetManuName(USART_TypeDef* USARTx);
void CH9142_GetPNPID(USART_TypeDef* USARTx);

// 配置类
void CH9142_SetUART(USART_TypeDef* USARTx, uint32_t baud, uint8_t databit, uint8_t stopbit, uint8_t parity, uint8_t timeout);
void CH9142_SetBLEMode(USART_TypeDef* USARTx, uint8_t mode);
void CH9142_SetName(USART_TypeDef* USARTx, const char* name);
void CH9142_SetPName(USART_TypeDef* USARTx, const char* pname);
void CH9142_SetSysID(USART_TypeDef* USARTx, const char* id);
void CH9142_SetModName(USART_TypeDef* USARTx, const char* name);
void CH9142_SetSeriNum(USART_TypeDef* USARTx, const char* sn);
void CH9142_SetFirmRev(USART_TypeDef* USARTx, const char* rev);
void CH9142_SetHardRev(USART_TypeDef* USARTx, const char* rev);
void CH9142_SetSoftRev(USART_TypeDef* USARTx, const char* rev);
void CH9142_SetManuName(USART_TypeDef* USARTx, const char* name);
void CH9142_SetPNPID(USART_TypeDef* USARTx, const char* id);

// 连接控制类
void CH9142_Disconnect(USART_TypeDef* USARTx);

#endif /* USER_CH9142CMD_H_ */
