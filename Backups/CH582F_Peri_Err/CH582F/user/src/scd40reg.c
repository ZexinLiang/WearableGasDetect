#include "scd40reg.h"
/******************************
 * 注意：
 * 1.SCD40接受时记得多接受一位，否则会造成时序错误
 * 2.SCD40不能已经开启的功能不能再开启，否则传感器不应答，依旧产生IIC时序错误
 * 3.SCD40采集完的数据只能读取一次，读取前判断，5s一周期，否则全是0
 *****************************/


extern softI2C_TypeDef i2c0;

#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT 0xFF

uint8_t CRC_Cal(const uint8_t* data, uint16_t count) {
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for (current_byte = 0; current_byte < count; ++current_byte) {
        crc ^= (data[current_byte]);
        for (crc_bit = 8; crc_bit > 0; --crc_bit) {
            if (crc & 0x80)
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }
    return crc;
}

void start_periodic_measurement(void)//开始定期测量
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xb1);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 

void read_measurement(uint16_t *CO2,uint16_t *Temperature,uint16_t *Relative_humidity)//3.5.2读取传感器输出
{
    uint16_t temp1,temp2,crc,value1,value2,value3;
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0xec);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x05);
    I2C_WaitAck(&i2c0);
    DelayMs(1);//延时函数
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    //接受CO2数据
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value1 = (temp1<<8)|temp2;
    //接受温度数据
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value2 = (temp1<<8)|temp2;
    //接受湿度数据
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value3 = (temp1<<8)|temp2;
    I2C_SendACK(&i2c0, 1);
    I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);

    *CO2 = value1;
    *Temperature = (uint16_t)(-45 + 175.f*(float)value2/65536.f);
    *Relative_humidity = (uint16_t)(100.f*(float)value3/65536.f);
}

void stop_periodic_measurement(void) //停止测量
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x3f);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x86);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}

void set_sensor_offset(float *offset_set)//设置温度偏移量
{
    uint16_t word  = (uint16_t)(*offset_set*65535/175);
    uint8_t byte[2];
    byte[0] = (uint8_t)(word>>8);
    byte[1] = (uint8_t)word;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x1d);
    I2C_WaitAck(&i2c0);
    
    I2C_SendByte(&i2c0,byte[0]);   //写入设置的海拔
    I2C_WaitAck(&i2c0);//等待从机响应
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}

void get_temperature_offset(float *offset)//读取温度偏移量
{
    I2C_Start(&i2c0);//起始信号
    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
    I2C_WaitAck(&i2c0);//等待从机响应
    //发送16位指令
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x18);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//延时函数

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    uint16_t word = (temp1<<8)|temp2;
    *offset = (float)word*175.f/65535.f;
}


void set_sensor_altitude(uint16_t *altitude_set)//设置海拔 
{
    uint8_t byte[2];
    byte[0] = (uint8_t)*altitude_set>>8;
    byte[1] = (uint8_t)*altitude_set;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x27);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,byte[0]);     //写入设置的海拔指令
    I2C_WaitAck(&i2c0);//等待从机响应
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}



void get_sensor_altitude(uint16_t *altitude)//读取海拔
{
    I2C_Start(&i2c0);//起始信号
    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
    I2C_WaitAck(&i2c0);//等待从机响应
    //发送16位指令
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x22);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//延时函数

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    *altitude = (temp1<<8)|temp2;
}


void set_ambient_pressure(uint16_t *pressure_set)//设置环境压力 
{
    uint16_t word = (*pressure_set)/100;
    uint8_t byte[2];
    byte[0] = (uint8_t)(word>>8);
    byte[1] = (uint8_t)word;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0xe0);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x00);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,byte[0]);
    I2C_WaitAck(&i2c0);//等待从机响应
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}


void  perform_forced_recalibration(uint16_t *correction,int16_t *frc_c)//执行强制校验标准
{
    uint8_t byte[2] ={0};
    byte[0] = (uint8_t)(*correction>>8);
    byte[1] = (uint8_t)(*correction);
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x2f);
    I2C_WaitAck(&i2c0);
    
    I2C_SendByte(&i2c0,byte[0]);     //写入设置的指令
    I2C_WaitAck(&i2c0);//等待从机响应
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    
    DelayMs(400);//延时函数
    
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    uint16_t returnfrcori = (temp1<<8)|temp2;
    *frc_c = returnfrcori - 0x8000;
} 

void set_automatic_self_calibration_enabled(uint8_t ASC_en)//设置自动自校准启用
{
    uint8_t crc = CRC_Cal(&ASC_en, 1);
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x16);
    I2C_WaitAck(&i2c0);
    //写入,1=ASC enabled; 0=ASC disabled
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0,0),
    I2C_WaitAck(&i2c0);//等待从机响应
    I2C_SendByte(&i2c0,ASC_en),
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}



void get_automatic_self_calibration_enabled (uint16_t *state)//获取自动自校准启用状态
{
    I2C_Start(&i2c0);//起始信号
    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
    I2C_WaitAck(&i2c0);//等待从机响应
    //发送16位指令
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x13);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//延时函数

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *state = (temp1<<8)|temp2;
}


void start_low_power_periodic_measurement(void) //启动低功耗定期测量
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xac);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



void get_data_ready_status (uint8_t *ready_state)//获取数据就绪状态
{
    I2C_Start(&i2c0);//起始信号
    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
    I2C_WaitAck(&i2c0);//等待从机响应
    //发送16位指令
    I2C_SendByte(&i2c0, 0xe4);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xb8);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//延时函数

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    uint16_t word = (temp1<<8)|temp2;
    if(word & 0b0000011111111111) *ready_state = 1;
    else *ready_state =0;
}



void persist_settings(void) //保存设置
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x15);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



//#warning "need persist data"
//void get_serial_number (uint16_t *number)//获取序列号
//{
//    I2C_Start(&i2c0);//起始信号
//    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
//    I2C_WaitAck(&i2c0);//等待从机响应
//    //发送16位指令
//    I2C_SendByte(&i2c0, 0x36);
//    I2C_WaitAck(&i2c0);
//    I2C_SendByte(&i2c0, 0x82);
//    I2C_WaitAck(&i2c0);
//
//    DelayMs(1);//延时函数
//
//    I2C_Start(&i2c0);
//    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
//    I2C_WaitAck(&i2c0);
//    uint16_t temp1 = I2C_RecvByte(&i2c0);
//    I2C_SendACK(&i2c0, 1);
//    uint16_t temp2 = I2C_RecvByte(&i2c0);
//    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
//    uint16_t temp3 = I2C_RecvByte(&i2c0);
//    I2C_SendACK(&i2c0, 1);
//    uint8_t crc = I2C_RecvByte(&i2c0);
//    I2C_SendACK(&i2c0, 0);//NACK
//    I2C_Stop(&i2c0);
//
//    *number = (temp1<<32)|(temp2<<16)|(temp3);
//}



void perform_self_test(uint16_t *self_test)//执行自检
{
    I2C_Start(&i2c0);//起始信号
    I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
    I2C_WaitAck(&i2c0);//等待从机响应
    //发送16位指令
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x39);
    I2C_WaitAck(&i2c0);

    DelayMs(10000);//延时函数

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//从机地址，1：读指令
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//主机发送收到响应ACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *self_test = (temp1<<8)|temp2;//0=未检测到故障，≠0检测到故障 
}




void  perform_factory_reset(void) //执行恢复出厂设置
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x32);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 

void reinit(void)//重新初始化
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x46);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



void measure_single_shot(void)//执行单次测量
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x9d);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 

//Only for scd41
void measure_single_shot_rht_only(void)//仅执行温湿度单次测量
{
	I2C_Start(&i2c0);//起始信号
	I2C_SendByte(&i2c0, 0x62<<1);//从机地址，0：写指令
	I2C_WaitAck(&i2c0);//等待从机响应
	//发送16位指令
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x96);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}
