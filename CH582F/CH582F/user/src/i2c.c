/*
 * I2C.c
 *
 *  Created on: 2025年2月5日
 *      Author: 梁泽欣
 */
#include "I2C.h"

void I2CInit(softI2C_TypeDef* I2C){
    if(I2C->SCLPort==GPIOA){//由于IO函数被分开写了，这里采用判断更改IOPort
        GPIOA_ModeCfg(I2C->SCLPin,GPIO_ModeIN_PU );//初始化为上拉输入
        GPIOA_ResetBits(I2C->SCLPin);//配置默认输出低电平
    }
    else if(I2C->SCLPort==GPIOB){
        GPIOB_ModeCfg(I2C->SCLPin,GPIO_ModeIN_PU );//初始化为上拉输入
        GPIOB_ResetBits(I2C->SCLPin);//配置默认输出低电平
    }
    I2C_SCL_H(I2C);//SCL拉高
    I2C_SDA_H(I2C);//SDA拉高
}

void I2C_SCL_H(softI2C_TypeDef* I2C){
    if(I2C->SCLPort==GPIOA)         GPIOA_H(I2C->SCLPin);
    else if(I2C->SCLPort==GPIOB)    GPIOB_H(I2C->SCLPin);
}

void I2C_SCL_L(softI2C_TypeDef* I2C){
    if(I2C->SCLPort==GPIOA)         GPIOA_L(I2C->SCLPin);
    else if(I2C->SCLPort==GPIOB)    GPIOB_L(I2C->SCLPin);
}

uint8_t I2C_SCL_READ(softI2C_TypeDef* I2C){
    if(I2C->SCLPort==GPIOA){
        if(GPIOA_ReadPortPin(I2C->SCLPin))  return 1;
        else return 0 ;
    }
    else if(I2C->SCLPort==GPIOB){
        if(GPIOB_ReadPortPin(I2C->SCLPin))  return 1;
        else return 0 ;
    }
    else return 0;
}

void I2C_SDA_H(softI2C_TypeDef* I2C){
    if(I2C->SDAPort==GPIOA)         GPIOA_H(I2C->SDAPin);
    else if(I2C->SDAPort==GPIOB)    GPIOB_H(I2C->SDAPin);
}

void I2C_SDA_L(softI2C_TypeDef* I2C){
    if(I2C->SDAPort==GPIOA)         GPIOA_L(I2C->SDAPin);
    else if(I2C->SDAPort==GPIOB)    GPIOB_L(I2C->SDAPin);
}

uint8_t I2C_SDA_READ(softI2C_TypeDef* I2C){
    if(I2C->SDAPort==GPIOA){
        if(GPIOA_ReadPortPin(I2C->SDAPin))  return 1;
        else return 0 ;
    }
    else if(I2C->SDAPort==GPIOB){
        if(GPIOB_ReadPortPin(I2C->SDAPin))  return 1;
        else return 0 ;
    }
    else return 0;
}

uint8_t i2c_read_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr, uint8_t* data, uint8_t len) {
    I2C_Start(I2C);
    I2C_SendByte(I2C, (dev_addr << 1) | 0); // 设备地址 + 写入标志
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // 通信失败
    }
    I2C_SendByte(I2C, reg_addr);
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // 通信失败
    }
    //I2C_Stop(I2C);
    I2C_Start(I2C);
    I2C_SendByte(I2C, (dev_addr << 1) | 1); // 设备地址 + 读取标志
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // 通信失败
    }
    for (uint8_t i = 0; i < len; i++) {
        data[i] = I2C_RecvByte(I2C);
        if (i <= len - 1) {
            I2C_SendACK(I2C, 1); // 发送ACK
        } else {
            I2C_SendACK(I2C, 0); // 发送NACK
        }
    }
    //I2C_Stop(I2C);
    return 1; // 通信成功
}


uint8_t i2c_write_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr,const uint8_t* data, uint8_t len) {
    I2C_Start(I2C);
    I2C_SendByte(I2C, (dev_addr << 1) | 0); // 设备地址 + 写入标志
    if (!I2C_WaitAck(I2C)) {
        PRINT("W1");
        I2C_Stop(I2C);
        return 0; // 通信失败
    }
//    I2C_SendByte(I2C, reg_addr);
//    if (!I2C_WaitAck(I2C)) {
//        PRINT("W2");
//        I2C_Stop(I2C);
//        return 0; // 通信失败
//    }
    for (uint8_t i = 0; i < len; i++) {//地址不自增

        I2C_SendByte(I2C, reg_addr+i);
            if (!I2C_WaitAck(I2C)) {
                PRINT("W2");
                I2C_Stop(I2C);
                return 0; // 通信失败
            }

        I2C_SendByte(I2C, data[i]);
        if (!I2C_WaitAck(I2C)) {
            PRINT("W3+%d",i);
            I2C_Stop(I2C);
            return 0; // 通信失败
        }
    }
    I2C_Stop(I2C);
    return 1; // 通信成功
}


/*起始信号*/
uint8_t I2C_Start(softI2C_TypeDef* I2C)
{
    I2C_SDA_H(I2C);
    I2C_delay();
    I2C_SCL_H(I2C);
    I2C_delay();
    if(!I2C_SDA_READ(I2C)) return 0;
    I2C_SDA_L(I2C);
    I2C_delay();
    if(I2C_SDA_READ(I2C)) return 0;
    I2C_SCL_L(I2C);
    I2C_delay();
    return 1;
}

/*发送一个字节*/
void I2C_SendByte(softI2C_TypeDef* I2C,uint8_t SendByte) //数据从高位到低位
{
    uint8_t i=8;
    I2C_SCL_L(I2C);
    for (i=0; i<8; i++) //8位计数器
    {
        if(SendByte&0x80)//SDA准备
            I2C_SDA_H(I2C);
        else
            I2C_SDA_L(I2C);
        I2C_SCL_H(I2C); //拉高时钟，给从机采样
        I2C_delay();//延时保持I2C时钟频率，也是给从机采样有充足时间
        I2C_SCL_L(I2C);//拉低时钟，给SDA准备
        I2C_delay();//延时保持I2C时钟频率
        SendByte<<=1;//移出数据的最高位
    }
}

/*等待ACK*/
uint8_t I2C_WaitAck(softI2C_TypeDef* I2C)  //返回为:=1有ACK,=0无ACK
{
    uint16_t i=0;
    I2C_SDA_H(I2C);//释放SDA
    I2C_SCL_H(I2C);//SCL拉高进行采样
    I2C_delay();
    while(I2C_SDA_READ(I2C))//等待SDA拉低
    {
        i++;//等待计数
        if(i==1000)//超时跳出循环
        {
            PRINT("No ACK Response!");
            break;
        }
    }
    if(I2C_SDA_READ(I2C))//再次判断SDA是否拉低
    {
        I2C_SCL_L(I2C);
        printf("errorInAck");
        return 0;//从机应答失败，返回0
    }
    I2C_delay();//延时保证时钟频率低于40K，
    I2C_SCL_L(I2C);
    I2C_delay(); //延时保证时钟频率低于40K，
    return 1;//从机应答成功，返回1
}

/*接受八位数据*/
uint8_t I2C_RecvByte(softI2C_TypeDef* I2C) //数据从高位到低位//
{
    uint8_t i=8;
    uint8_t ReceiveByte=0;
    I2C_SDA_H(I2C); //释放SDA，给从机使用
    I2C_delay(); //延时给从机准备SDA时间
    for (i=0; i<8; i++)//8位计数器
    {
        I2C_SCL_L(I2C);//拉低时钟线，处理接收到的数据
        I2C_delay();   //延时给从机准备SDA时间
        I2C_SCL_H(I2C);//拉高时钟线，采样从机SDA
        ReceiveByte <<= 1;
        if(I2C_SDA_READ(I2C)) //读数据
            ReceiveByte |=0x01;
        I2C_delay();//延时保持I2C时钟频率
    }
    return ReceiveByte;
}

/*结束信号*/
void I2C_Stop(softI2C_TypeDef* I2C)
{
    I2C_SCL_L(I2C);
    I2C_delay();
    I2C_SDA_L(I2C);
    I2C_delay();
    I2C_SCL_H(I2C);
    I2C_delay();
    I2C_SDA_H(I2C);
    I2C_delay();
}

/*I2C等待延时*/
void I2C_delay(void)
{
    DelayUs(30);
}
void I2C_SendACK(softI2C_TypeDef* I2C,uint8_t i)
{
    I2C_SCL_L(I2C);
    if(i==0)
        I2C_SDA_H(I2C);
    else
        I2C_SDA_L(I2C);
    I2C_delay();
    I2C_SCL_H(I2C);
    I2C_delay();
    I2C_SCL_L(I2C);
    I2C_delay();
}
