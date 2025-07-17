/*
 * i2c.h
 *
 *  Created on: 2025��2��5��
 *      Author: ������
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#define GPIOA_L(pin)    (R32_PA_DIR |= pin)     //�����޿�©�����������ģʽģ�⿪©���
#define GPIOA_H(pin)    (R32_PA_DIR &= ~pin)
#define GPIOB_L(pin)    (R32_PB_DIR |= pin)
#define GPIOB_H(pin)    (R32_PB_DIR &= ~pin)

#define GPIOA   0x00    //����GPIO���ٱ�д��һ���������������¶���GPIOPort��ȷ��GPIO�ܹ��������л�
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

void I2C_SCL_H(softI2C_TypeDef* I2C);//����ʱ����

void I2C_SCL_L(softI2C_TypeDef* I2C);//����ʱ����

uint8_t I2C_SCL_READ(softI2C_TypeDef* I2C);//��ȡʱ����

void I2C_SDA_H(softI2C_TypeDef* I2C);//����������

void I2C_SDA_L(softI2C_TypeDef* I2C);//����������

uint8_t I2C_SDA_READ(softI2C_TypeDef* I2C);//��ȡ������

void I2CInit(softI2C_TypeDef* I2C);//��ʼ��I2C

uint8_t I2C_Start(softI2C_TypeDef* I2C);//I2Cͨ����ʼ�ź�

void I2C_SendByte(softI2C_TypeDef* I2C,uint8_t SendByte);//I2C���͵��ֽ�

uint8_t I2C_WaitAck(softI2C_TypeDef* I2C);//�ȴ�ACK

uint8_t I2C_RecvByte(softI2C_TypeDef* I2C);//���ܰ�λ����

void I2C_Stop(softI2C_TypeDef* I2C);//�����ź�

void I2C_delay(void);//I2C��Ҫ��ʱ�ȴ�

void I2C_SendACK(softI2C_TypeDef* I2C,uint8_t i);//����ACK�ź�

uint8_t i2c_write_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr,const uint8_t* data, uint8_t len);

uint8_t i2c_read_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* data, uint8_t len);

#endif /* INC_I2C_H_ */
