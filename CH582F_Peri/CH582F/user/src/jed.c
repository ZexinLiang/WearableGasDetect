#include "i2c.h"

uint16_t JED_I2C_Read_Byte(softI2C_TypeDef* I2C)
{
    uint16_t rec_data16;
    uint8_t rec_data;
    I2C_Start(I2C);
    I2C_SendByte(I2C,0x54);
    I2C_WaitAck(I2C);
    I2C_SendByte(I2C,0xe1);
    I2C_WaitAck(I2C);
    I2C_Start(I2C);
    I2C_SendByte(I2C,0x55);
    I2C_WaitAck(I2C);
    rec_data = I2C_RecvByte(I2C);
    rec_data16=rec_data;
    I2C_SendACK(I2C,0);
    rec_data = I2C_RecvByte(I2C);
    rec_data16=rec_data16<<8|rec_data;
    I2C_Stop(I2C);
    return rec_data16;
}
