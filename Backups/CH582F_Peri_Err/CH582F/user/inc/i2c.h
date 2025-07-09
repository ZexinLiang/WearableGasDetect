/*
 * i2c.h
 *
 *  Created on: 2025年2月5日
 *      Author: 梁泽欣
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#define GPIOA_L(pin)    (R32_PA_DIR |= pin)     //由于无开漏输出，用输入模式模拟开漏输出
#define GPIOA_H(pin)    (R32_PA_DIR &= ~pin)
#define GPIOB_L(pin)    (R32_PB_DIR |= pin)
#define GPIOB_H(pin)    (R32_PB_DIR &= ~pin)

#define GPIOA   0x00    //由于GPIO不再被写成一个函数，这里重新定义GPIOPort以确保GPIO能够的正常切换
#define GPIOB   0x01

#include "CH58x_common.h"

typedef struct softI2C{
    uint8_t  SCLPort;
    uint8_t  SDAPort;
    uint32_t SCLPin;
    uint32_t SDAPin;
}softI2C_TypeDef;

extern softI2C_TypeDef i2c0;
extern softI2C_TypeDef i2c1;
extern uint16_t gasPPM[2];

void I2C_SCL_H(softI2C_TypeDef* I2C);//拉高时钟线

void I2C_SCL_L(softI2C_TypeDef* I2C);//拉低时钟线

uint8_t I2C_SCL_READ(softI2C_TypeDef* I2C);//读取时钟线

void I2C_SDA_H(softI2C_TypeDef* I2C);//拉高数据线

void I2C_SDA_L(softI2C_TypeDef* I2C);//拉低数据线

uint8_t I2C_SDA_READ(softI2C_TypeDef* I2C);//读取数据线

void I2CInit(softI2C_TypeDef* I2C);//初始化I2C

uint8_t I2C_Start(softI2C_TypeDef* I2C);//I2C通信起始信号

void I2C_SendByte(softI2C_TypeDef* I2C,uint8_t SendByte);//I2C发送单字节

uint8_t I2C_WaitAck(softI2C_TypeDef* I2C);//等待ACK

uint8_t I2C_RecvByte(softI2C_TypeDef* I2C);//接受八位数据

void I2C_Stop(softI2C_TypeDef* I2C);//结束信号

void I2C_delay(void);//I2C必要延时等待

void I2C_SendACK(softI2C_TypeDef* I2C,uint8_t i);//发送ACK信号

uint8_t i2c_write_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr,const uint8_t* data, uint8_t len);

uint8_t i2c_read_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* data, uint8_t len);

#endif /* INC_I2C_H_ */
