/*
 * ch9142cmd.c
 *
 *  Created on: 2025年6月1日
 *      Author: lzx
 */

#include "ch9142cmd.h"
#include <stdio.h>
#include <string.h>

extern void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str);

static char at_buf[128];

void CH9142_SendCommand(USART_TypeDef* USARTx, const char* cmd) {
    USARTx_SendStr(USARTx, (char*)cmd);
}

//IO进入/退出AT
void CH9142_ATIO_IN(USART_TypeDef* USARTx){
    if(USARTx == USART1)
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
    else if(USARTx == USART2)
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}
void CH9142_ATIO_EXIT(USART_TypeDef* USARTx){
    if(USARTx == USART1)
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
    else if(USARTx == USART2)
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

// 基本控制类
void CH9142_AT(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT...\r\n"); }
void CH9142_Reset(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+RESET\r\n"); }
void CH9142_ExitAT(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+EXIT\r\n"); }

// 信息获取类
void CH9142_GetVersion(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+VER\r\n"); }
void CH9142_GetUART(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+UART?\r\n"); }
void CH9142_GetMAC(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+MAC?\r\n"); }
void CH9142_GetBLEStatus(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+BLESTA?\r\n"); }
void CH9142_GetBLEMode(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+BLEMODE?\r\n"); }
void CH9142_GetName(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+NAME?\r\n"); }
void CH9142_GetPName(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+PNAME?\r\n"); }
void CH9142_GetSysID(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+SYSID?\r\n"); }
void CH9142_GetModName(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+MODNAME?\r\n"); }
void CH9142_GetSeriNum(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+SERINUM?\r\n"); }
void CH9142_GetFirmRev(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+FIRMREV?\r\n"); }
void CH9142_GetHardRev(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+HARDREV?\r\n"); }
void CH9142_GetSoftRev(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+SOFTREV?\r\n"); }
void CH9142_GetManuName(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+MANUNAME?\r\n"); }
void CH9142_GetPNPID(USART_TypeDef* USARTx) { CH9142_SendCommand(USARTx, "AT+PNPID?\r\n"); }

// 配置类
void CH9142_SetUART(USART_TypeDef* USARTx, uint32_t baud, uint8_t databit, uint8_t stopbit, uint8_t parity, uint8_t timeout) {
    snprintf(at_buf, sizeof(at_buf), "AT+UART=%lu,%d,%d,%d,%d\r\n", baud, databit, stopbit, parity, timeout);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetBLEMode(USART_TypeDef* USARTx, uint8_t mode) {
    snprintf(at_buf, sizeof(at_buf), "AT+BLEMODE=%d\r\n", mode);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetName(USART_TypeDef* USARTx, const char* name) {
    snprintf(at_buf, sizeof(at_buf), "AT+NAME=%s\r\n", name);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetPName(USART_TypeDef* USARTx, const char* pname) {
    snprintf(at_buf, sizeof(at_buf), "AT+PNAME=%s\r\n", pname);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetSysID(USART_TypeDef* USARTx, const char* id) {
    snprintf(at_buf, sizeof(at_buf), "AT+SYSID=%s\r\n", id);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetModName(USART_TypeDef* USARTx, const char* name) {
    snprintf(at_buf, sizeof(at_buf), "AT+MODNAME=%s\r\n", name);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetSeriNum(USART_TypeDef* USARTx, const char* sn) {
    snprintf(at_buf, sizeof(at_buf), "AT+SERINUM=%s\r\n", sn);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetFirmRev(USART_TypeDef* USARTx, const char* rev) {
    snprintf(at_buf, sizeof(at_buf), "AT+FIRMREV=%s\r\n", rev);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetHardRev(USART_TypeDef* USARTx, const char* rev) {
    snprintf(at_buf, sizeof(at_buf), "AT+HARDREV=%s\r\n", rev);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetSoftRev(USART_TypeDef* USARTx, const char* rev) {
    snprintf(at_buf, sizeof(at_buf), "AT+SOFTREV=%s\r\n", rev);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetManuName(USART_TypeDef* USARTx, const char* name) {
    snprintf(at_buf, sizeof(at_buf), "AT+MANUNAME=%s\r\n", name);
    CH9142_SendCommand(USARTx, at_buf);
}

void CH9142_SetPNPID(USART_TypeDef* USARTx, const char* id) {
    snprintf(at_buf, sizeof(at_buf), "AT+PNPID=%s\r\n", id);
    CH9142_SendCommand(USARTx, at_buf);
}

// 连接控制
void CH9142_Disconnect(USART_TypeDef* USARTx) {
    CH9142_SendCommand(USARTx, "AT+DISCONN\r\n");
}

