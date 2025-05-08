#include "i2c.h"

extern softI2C_TypeDef i2c0;

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

void read_measurement(uint16_t *CO2,uint16_t *Temperature,uint16_t *Relative_umidity)//3.5.2��ȡ���������
{
    uint16_t temp1,temp2,crc,value;
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
    value = (temp1<<8)|temp2;
    *CO2 = value;
    //�����¶�����
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value = (temp1<<8)|temp2;
    *Temperature = (uint16_t)(-45 + 175.f*(float)value/65536.f);
    //����ʪ������
    temp1 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    temp2 = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    crc = I2C_RecvByte(&i2c0);
    I2C_SendACK(&i2c0, 1);
    value = (temp1<<8)|temp2;
    *Relative_umidity =

    I2C_SendACK(&i2c0, 0);//NACK
    I2C_Stop(&i2c0);
}



void stop_periodic_measurement(void) //ֹͣ����
{
	2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x3f);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x86);
    I2C_WaitAck(&i2c0);
    I2C_Stop(&i2c0);
}



#warning "data input required"
void set_sensor_offset(uint16_t *offset_set)//�����¶�ƫ���� 
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x1d);
    I2C_WaitAck(&i2c0);
    
    DelayMs(1);//��ʱ����
     
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0),     //д�����õĺ���
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);
    uint8_t crc = I2C_SendByte(&i2c0);
    I2C_WaitAck(&i2c0);
    
    I2C_Stop(&i2c0);
}




void get_temperature_offset(uint16_t *offset)//��ȡ�¶�ƫ����
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
    *offset = (temp1<<8)|temp2;
}



#warning "data input required"
void set_sensor_altitude(uint16_t *altitude_set)//���ú��� 
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0x24);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x27);
    I2C_WaitAck(&i2c0);
    
    DelayMs(1);//��ʱ����
     
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0),     //д�����õĺ���ָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);
    uint8_t crc = I2C_SendByte(&i2c0);
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


#warning "data input required"
void set_ambient_pressure(uint16_t *pressure_set)//���û���ѹ�� 
{
	I2C_Start(&i2c0);//��ʼ�ź�
	I2C_SendByte(&i2c0, 0x62<<1);//�ӻ���ַ��0��дָ��
	I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
	//����16λָ��
    I2C_SendByte(&i2c0, 0xe0);
    I2C_WaitAck(&i2c0);
    I2C_SendByte(&i2c0, 0x00);
    I2C_WaitAck(&i2c0);
    
    DelayMs(1);//��ʱ����
     
    I2C_Start(&i2c0);
    I2C_SendByte(&i2c0),     //д�����õ�ѹ��ָ��
    I2C_WaitAck(&i2c0);//�ȴ��ӻ���Ӧ
    I2C_SendByte(&i2c0),
    I2C_WaitAck(&i2c0);
    uint8_t crc = I2C_SendByte(&i2c0);
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
