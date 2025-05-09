#include "i2c.h"

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

void start_periodic_measurement(void)//��ʼ���ڲ���
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xb1);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 

void read_measurement(uint16_t *CO2,uint16_t *Temperature,uint16_t *Relative_humidity)//3.5.2��ȡ���������
{
    uint16_t temp1,temp2,crc,value1,value2,value3;
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0xec);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x05);
    I2C_WaitAck(&i2c0);
    DelayMs(1);//��ʱ����
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    //����CO2����
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value1 = (temp1<<8)|temp2;
    //�����¶�����
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value2 = (temp1<<8)|temp2;
    //����ʪ������
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value3 = (temp1<<8)|temp2;
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    *CO2 = value1;
    *Temperature = (uint16_t)(-45 + 175.f*(float)value2/65536.f);
    *Relative_humidity = (uint16_t)(100.f*(float)value3/65536.f);
}



void stop_periodic_measurement(void) //ֹͣ����
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x3f);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x86);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}

void set_sensor_offset(float *offset_set)//�����¶�ƫ����
{
    uint16_t word  = (uint16_t)(*offset_set*65535/175);
    uint8_t byte[2];
    byte[0] = (uint8_t)(word>>8);
    byte[1] = (uint8_t)word;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x1d);
    I2C_WaitAck(&i2c0);
    
    I2C_SendByte(&i2c0,byte[0]);   //д�����õĺ���
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}

void get_temperature_offset(float *offset)//��ȡ�¶�ƫ����
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x18);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    uint16_t word = (temp1<<8)|temp2;
    *offset = (float)word*175.f/65535.f;
}


void set_sensor_altitude(uint16_t *altitude_set)//���ú��� 
{
    uint8_t byte[2];
    byte[0] = (uint8_t)*altitude_set>>8;
    byte[1] = (uint8_t)*altitude_set;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x27);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,byte[0]);     //д�����õĺ���ָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}



void get_sensor_altitude(uint16_t *altitude)//��ȡ����
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x22);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    *altitude = (temp1<<8)|temp2;
}


void set_ambient_pressure(uint16_t *pressure_set)//���û���ѹ�� 
{
    uint16_t word = pressure_set/100;
    uint8_t byte[2];
    byte[0] = (uint8_t)(word>>8);
    byte[1] = (uint8_t)word;
    uint8_t crc = CRC_Cal(byte, 2);
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0xe0);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x00);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,byte[0]);
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0,byte[1]);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0,crc);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}


#warning "data input required"
void  perform_forced_recalibration(uint16_t *correction)//ִ��ǿ��У���׼
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x2f);
    I2C_WaitAck(&i2c0);
    
    DelayMs(400);//��ʱ����
    
    I2C_SendByte(&i2c0),     //д�����õ�ָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);
    uint8_t crc = I2C_SendByte(&i2c0);
    I2C_WaitAck(&i2c0);
    
    DelayMs(400);//��ʱ����
    
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    *correction = (temp1<<8)|temp2;
    
    I2C_Stop(&i2c0);
} 



#warning "data input required"

void set_automatic_self_calibration_enabled(void)//�����Զ���У׼����
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x16);
    I2C_WaitAck(&i2c0);
    
    DelayMs(1);//��ʱ����
    
    //д��,1=ASC enabled; 0=ASC disabled
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);
    
    uint8_t crc = I2C_SendByte(&i2c0);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}



void get_automatic_self_calibration_enabled (uint16_t *state)//��ȡ�Զ���У׼����״̬
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0x23);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x13);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *state = (temp1<<8)|temp2;
}


void start_low_power_periodic_measurement(void) //�����͹��Ķ��ڲ���
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xac);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



void get_data_ready_status (uint16_t *ready_state)//��ȡ���ݾ���״̬
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0xe4);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0xb8);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *ready_state = (temp1<<8)|temp2;
}



void persist_settings(void) //��������
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x15);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



#warning "need persist data"
void get_serial_number (uint16_t *number)//��ȡ���к�
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x82);
    I2C_WaitAck(&i2c0);

    DelayMs(1);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint16_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint16_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint16_t temp3 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *number = (temp1<<32)|(temp2<<16)|(temp3);
}



void perform_self_test(uint16_t *self_test)//ִ���Լ�
{
    I2C_Start(&i2c0);//��ʼ�ź�
    I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    //����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x39);
    I2C_WaitAck(&i2c0);

    DelayMs(10000);//��ʱ����

    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0, 0x62<<1|0x01);//�ӻ���ַ��1����ָ��
    I2C_WaitAck(&i2c0);
    uint8_t temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    uint8_t temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);//���������յ���ӦACK
    uint8_t crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
    
    *self_test = (temp1<<8)|temp2;//0=δ��⵽���ϣ���0��⵽���� 
}




void  perform_factory_reset(void) //ִ�лָ���������
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x32);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 

void reinit(void)//���³�ʼ��
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x36);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x46);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



void measure_single_shot(void)//ִ�е��β���
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x9d);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
} 



void measure_single_shot_rht_only(void)//��ִ����ʪ�ȵ��β���
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x21);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x96);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}
