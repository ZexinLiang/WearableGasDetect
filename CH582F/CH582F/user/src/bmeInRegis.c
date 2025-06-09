/*
 * bmeInRegis.c
 *
 *  Created on: 2025��3��1��
 *      Author: 86135
 */

#include "bmeInRegis.h"

uint8_t BME688InitInReg(void){
    uint8_t rslt;//ͨ����֤
    uint8_t chip_id;//оƬID
    rslt = i2c_read_reg(&i2c1, 0x76, 0xD0, &chip_id, 1);//��ȡоƬID
    if(!rslt){
        PRINT("Communication error:ID read\n");
        return 1;//ʧ��
    }
    if(chip_id!=0x61){
        PRINT("ID recognition error\n");
        return 1;//ʧ��
    }
    DelayMs(100);
    //��ʼ������
    uint8_t h_rate = 0x01;//ʪ�Ȳ�����1x
    uint8_t tp_rate  = (0b010<<5)|(0b101<<2);//�¶Ȳ�����2x��ѹ��������16x
    DelayMs(1);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &tp_rate, 1);
    if(!rslt){
        PRINT("Communication error:temp pre rate set\n");
        return 1;//ʧ��
    }else{
        PRINT("OK:temp pre rate set\r\n");
    }
//        DelayMs(100);
//        rslt = i2c_write_reg(&i2c1, 0x76, 0x72, &h_rate, 1);
//        if(!rslt){
//            PRINT("Communication error:humi rate set\n");
//            return 1;//ʧ��
//        }
    uint8_t iir_flt = 0b100<<2;//IIR�˲������˲�ϵ��15
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x75, &iir_flt, 1);
    if(!rslt){
        PRINT("Communication error:iir_flt set\n");
        return 1;//ʧ��
    }
    // ���崫��������
    // ����1: ���ü���ʱ��gas_wait_0 (100ms)
    uint8_t gas_wait_0 = 0x59; // 0b01011001 (64*1 + 25=89 => 89ms �� 100ms)
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x64, &gas_wait_0, 1);
    if(!rslt){
        PRINT("Communication error:gas_wait_0 set\n");
        return 1;
    }

    // ����2: ���㲢����Ŀ���¶ȵ���ֵres_heat_0 (����Ŀ���¶�300��C)
    // ע��ʵ��Ӧʹ��API�������㣬����ʹ��ʾ��ֵ�������У׼����������
    uint8_t res_heat_0 = 0x50; // ʾ��ֵ������ݹ�����27ҳ��ʽ����
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x5A, &res_heat_0, 1);
    if(!rslt){
        PRINT("Communication error:res_heat_0 set\n");
        return 1;
    }

    // ����3: ѡ����Ȳ���0�������������
    uint8_t gas_ctrl1 = (0x0 << 0) | (1 << 5); // nb_conv=0, run_gas=1
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x71, &gas_ctrl1, 1);
    if(!rslt){
        PRINT("Communication error:gas_ctrl1 set\n");
        return 1;
    }

    // ����ǿ��ģʽ����
    uint8_t mode = 0x01; // Forced Mode
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &mode, 1);
    if(!rslt){
        PRINT("Communication error:mode set\n");
        return 1;
    }

    // �ȴ�������ɣ����͵ȴ�ʱ��Լ100ms��
    DelayMs(100);

    // ��ȡ״̬�Ĵ���
    uint8_t meas_status;
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1D, &meas_status, 1);
    if(!rslt){
        PRINT("Communication error:status read\n");
        return 1;
    }

    // �����������Чλ(bit7)
    if(!(meas_status & 0x80)){
        PRINT("No new data available\n");
        return 1;
    }

    // ��ȡԭʼ���ݣ�Field 0��
    uint8_t data[15];
    DelayMs(100);
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1F, data, 15);
    if(!rslt){
        PRINT("Communication error:data read\n");
        return 1;
    }

    // ����ԭʼ����
    uint32_t press_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    uint32_t temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
    uint16_t hum_raw = (data[6] << 8) | data[7];
    uint16_t gas_res = (data[13] << 2) | (data[14] >> 6);
    uint8_t gas_range = data[14] & 0x0F;

    // ��ӡ���
    PRINT("Temperature: %d \n", temp_raw);
    // ���ѹ����ʪ�ȡ����岹������...
    // �ȶ�ȡУ׼�������ؼ����裡��
    uint16_t par_t1;
    uint16_t par_t2;
    int8_t par_t3;
    uint8_t calib_data[5];

    // ��ȡ�¶�У׼�����Ĵ�����
    DelayMs(100);
    rslt = i2c_read_reg(&i2c1, 0x76, 0xE9, calib_data, 5);  // 0xE9-0xED
    if(!rslt){
         PRINT("Communication error:reg read\n");
         return 1;
     }

    // ����У׼����
    par_t1 = (calib_data[1] << 8) | calib_data[0];     // 0xE9-0xEA
    par_t2 = (calib_data[3] << 8) | calib_data[2];     // 0x8B-0x8C
    par_t3 = (int8_t)calib_data[4];                    // 0x8D

    // ��ȡԭʼ�¶����ݣ������ѻ�ȡdata���飩

    // ���������㷨��������23ҳ��
    int32_t var1, var2,var3, t_fine;
    int32_t temp_comp;

    var1 = ((int32_t)temp_raw >> 3) - ((int32_t)par_t1 << 1);
    var2 = (var1 * (int32_t)par_t2) >> 11;
    var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)par_t3 << 4)) >> 14;
    t_fine = var2 + var3;

    // �����¶ȼ��㣨��0.01��C�ֱ��ʣ�
    temp_comp = (t_fine * 5 + 128) >> 8;  // �ȼ��� (t_fine / 5120.0) * 100

    // ת��Ϊ�����¶�ֵ
    float temperature = temp_comp / 100.0f;
    PRINT("p1:%d p2:%d p3:%d\n",par_t1,par_t2,par_t3);
    PRINT("Compensated Temp: %.2f C\n", temperature);

    return 0;//���óɹ�
}

