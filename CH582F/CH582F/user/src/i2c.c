/*
 * I2C.c
 *
 *  Created on: 2025��2��5��
 *      Author: ������
 */
#include "I2C.h"

void I2CInit(softI2C_TypeDef* I2C){
    if(I2C->SCLPort==GPIOA){//����IO�������ֿ�д�ˣ���������жϸ���IOPort
        GPIOA_ModeCfg(I2C->SCLPin,GPIO_ModeIN_PU );//��ʼ��Ϊ��������
        GPIOA_ResetBits(I2C->SCLPin);//����Ĭ������͵�ƽ
    }
    else if(I2C->SCLPort==GPIOB){
        GPIOB_ModeCfg(I2C->SCLPin,GPIO_ModeIN_PU );//��ʼ��Ϊ��������
        GPIOB_ResetBits(I2C->SCLPin);//����Ĭ������͵�ƽ
    }
    I2C_SCL_H(I2C);//SCL����
    I2C_SDA_H(I2C);//SDA����
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
    I2C_SendByte(I2C, (dev_addr << 1) | 0); // �豸��ַ + д���־
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // ͨ��ʧ��
    }
    I2C_SendByte(I2C, reg_addr);
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // ͨ��ʧ��
    }
    //I2C_Stop(I2C);
    I2C_Start(I2C);
    I2C_SendByte(I2C, (dev_addr << 1) | 1); // �豸��ַ + ��ȡ��־
    if (!I2C_WaitAck(I2C)) {
        I2C_Stop(I2C);
        return 0; // ͨ��ʧ��
    }
    for (uint8_t i = 0; i < len; i++) {
        data[i] = I2C_RecvByte(I2C);
        if (i <= len - 1) {
            I2C_SendACK(I2C, 1); // ����ACK
        } else {
            I2C_SendACK(I2C, 0); // ����NACK
        }
    }
    //I2C_Stop(I2C);
    return 1; // ͨ�ųɹ�
}


uint8_t i2c_write_reg(softI2C_TypeDef* I2C, uint8_t dev_addr, uint8_t reg_addr,const uint8_t* data, uint8_t len) {
    I2C_Start(I2C);
    I2C_SendByte(I2C, (dev_addr << 1) | 0); // �豸��ַ + д���־
    if (!I2C_WaitAck(I2C)) {
        PRINT("W1");
        I2C_Stop(I2C);
        return 0; // ͨ��ʧ��
    }
//    I2C_SendByte(I2C, reg_addr);
//    if (!I2C_WaitAck(I2C)) {
//        PRINT("W2");
//        I2C_Stop(I2C);
//        return 0; // ͨ��ʧ��
//    }
    for (uint8_t i = 0; i < len; i++) {//��ַ������

        I2C_SendByte(I2C, reg_addr+i);
            if (!I2C_WaitAck(I2C)) {
                PRINT("W2");
                I2C_Stop(I2C);
                return 0; // ͨ��ʧ��
            }

        I2C_SendByte(I2C, data[i]);
        if (!I2C_WaitAck(I2C)) {
            PRINT("W3+%d",i);
            I2C_Stop(I2C);
            return 0; // ͨ��ʧ��
        }
    }
    I2C_Stop(I2C);
    return 1; // ͨ�ųɹ�
}


/*��ʼ�ź�*/
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

/*����һ���ֽ�*/
void I2C_SendByte(softI2C_TypeDef* I2C,uint8_t SendByte) //���ݴӸ�λ����λ
{
    uint8_t i=8;
    I2C_SCL_L(I2C);
    for (i=0; i<8; i++) //8λ������
    {
        if(SendByte&0x80)//SDA׼��
            I2C_SDA_H(I2C);
        else
            I2C_SDA_L(I2C);
        I2C_SCL_H(I2C); //����ʱ�ӣ����ӻ�����
        I2C_delay();//��ʱ����I2Cʱ��Ƶ�ʣ�Ҳ�Ǹ��ӻ������г���ʱ��
        I2C_SCL_L(I2C);//����ʱ�ӣ���SDA׼��
        I2C_delay();//��ʱ����I2Cʱ��Ƶ��
        SendByte<<=1;//�Ƴ����ݵ����λ
    }
}

/*�ȴ�ACK*/
uint8_t I2C_WaitAck(softI2C_TypeDef* I2C)  //����Ϊ:=1��ACK,=0��ACK
{
    uint16_t i=0;
    I2C_SDA_H(I2C);//�ͷ�SDA
    I2C_SCL_H(I2C);//SCL���߽��в���
    I2C_delay();
    while(I2C_SDA_READ(I2C))//�ȴ�SDA����
    {
        i++;//�ȴ�����
        if(i==1000)//��ʱ����ѭ��
        {
            PRINT("No ACK Response!");
            break;
        }
    }
    if(I2C_SDA_READ(I2C))//�ٴ��ж�SDA�Ƿ�����
    {
        I2C_SCL_L(I2C);
        printf("errorInAck");
        return 0;//�ӻ�Ӧ��ʧ�ܣ�����0
    }
    I2C_delay();//��ʱ��֤ʱ��Ƶ�ʵ���40K��
    I2C_SCL_L(I2C);
    I2C_delay(); //��ʱ��֤ʱ��Ƶ�ʵ���40K��
    return 1;//�ӻ�Ӧ��ɹ�������1
}

/*���ܰ�λ����*/
uint8_t I2C_RecvByte(softI2C_TypeDef* I2C) //���ݴӸ�λ����λ//
{
    uint8_t i=8;
    uint8_t ReceiveByte=0;
    I2C_SDA_H(I2C); //�ͷ�SDA�����ӻ�ʹ��
    I2C_delay(); //��ʱ���ӻ�׼��SDAʱ��
    for (i=0; i<8; i++)//8λ������
    {
        I2C_SCL_L(I2C);//����ʱ���ߣ�������յ�������
        I2C_delay();   //��ʱ���ӻ�׼��SDAʱ��
        I2C_SCL_H(I2C);//����ʱ���ߣ������ӻ�SDA
        ReceiveByte <<= 1;
        if(I2C_SDA_READ(I2C)) //������
            ReceiveByte |=0x01;
        I2C_delay();//��ʱ����I2Cʱ��Ƶ��
    }
    return ReceiveByte;
}

/*�����ź�*/
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

/*I2C�ȴ���ʱ*/
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
