/*
 * bmeInRegis.c
 *
 *  Created on: 2025年3月1日
 *      Author: 梁泽欣
 */

#include "bmeInRegis.h"

PBData_TypeDef PBData={0};

void BME688_Test(void){
    if(!BME688_ForceModeCFG()) PRINT("BME688 Config Error\r\n");
    // 等待测量完成
    DelayMs(500);

    // 读取状态寄存器
    if(!BME688_MeaStusGet())    return;

    double temperature,pressure,humidity;
    BME688_TempGet(&temperature);
    BME688_PresGet(&pressure);
    BME688_HumiGet(&humidity);
    PRINT("Compensated Temp: %f C\r\n", temperature);
    PRINT("Compensated Pres: %f Pa\r\n", pressure);
    PRINT("Compensated Humi: %f %\r\n", humidity);
    return;//配置成功
}

uint8_t BME688_ForceModeCFG(void){
    uint8_t rslt;//通信验证
    uint8_t chip_id;//芯片ID
    rslt = i2c_read_reg(&i2c1, 0x76, 0xD0, &chip_id, 1);//读取芯片ID
    if(!rslt){
        PRINT("Communication error:ID read\r\n");
        return 1;//失败
    }
    if(chip_id!=0x61){
        PRINT("ID recognition error\r\n");
        return 1;//失败
    }
    //初始化配置
    uint8_t h_rate = 0x01;//湿度采样率1x
    uint8_t tp_rate  = (0b010<<5)|(0b101<<2);//温度采样率2x，压力采样率16x
    rslt = i2c_write_reg(&i2c1, 0x76, 0x72, &h_rate, 1);
    if(!rslt){
        PRINT("Communication error:humi rate set\r\n");
        return 1;//失败
        }
    DelayMs(1);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &tp_rate, 1);
    if(!rslt){
        PRINT("Communication error:temp pre rate set\r\n");
        return 1;//失败
    }
    uint8_t iir_flt = 0b101;//IIR滤波器，滤波系数5
    rslt = i2c_write_reg(&i2c1, 0x76, 0x75, &iir_flt, 1);
    if(!rslt){
        PRINT("Communication error:iir_flt set\r\n");
        return 1;//失败
    }
    // 气体传感器配置
    // 步骤1: 设置加热时间gas_wait_0 (100ms)
    uint8_t gas_wait_0 = 0x59; // 0b01011001 (64*1 + 25=89 => 89ms ≈ 100ms)
    rslt = i2c_write_reg(&i2c1, 0x76, 0x64, &gas_wait_0, 1);
    if(!rslt){
        PRINT("Communication error:gas_wait_0 set\r\n");
        return 1;
    }

    // 步骤2: 计算并设置目标温度电阻值res_heat_0 (假设目标温度300°C)
    uint8_t res_heat_0;
    BME688_HeatResGet(300, &res_heat_0);
#warnig "Haven't been test"
    rslt = i2c_write_reg(&i2c1, 0x76, 0x5A, &res_heat_0, 1);
    if(!rslt){
        PRINT("Communication error:res_heat_0 set\r\n");
        return 1;
    }

    // 步骤3: 选择加热步骤0，启用气体测量
    uint8_t gas_ctrl1 = (0x0 << 0) | (1 << 5); // nb_conv=0, run_gas=1
    rslt = i2c_write_reg(&i2c1, 0x76, 0x71, &gas_ctrl1, 1);
    if(!rslt){
        PRINT("Communication error:gas_ctrl1 set\r\n");
        return 1;
    }

    // 触发强制模式测量
    uint8_t mode = 0x01; // Forced Mode
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &mode, 1);
    if(!rslt){
        PRINT("Communication error:mode set\r\n");
        return 1;
    }
    return 0;
}

void BME688_TempGet(double* temp){
    //获取AD值以及校准参数
    uint32_t par_t1,par_t2,par_t3;//校准参数
    uint32_t temp_adc;//温度ADC原始值
    uint8_t rslt;//读取成功判断
    uint8_t i = 0;//通信错误码
    uint8_t regData[3] = {0};
    rslt = i2c_read_reg(&i2c1, 0x76, 0xE9, regData, 2);
    if(!rslt){
        PRINT("Communication error:TempGet %d\r\n",i++);
        return;
    }
    par_t1 = regData[1]<<8|regData[0];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x8A, regData, 3);
    if(!rslt){
        PRINT("Communication error:TempGet %d\r\n",i++);
        return;
    }
    par_t2 = regData[1]<<8|regData[0];
    par_t3 = regData[2];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x22, regData, 3);
    if(!rslt){
        PRINT("Communication error:TempGet %d\r\n",i++);
        return;
    }
    temp_adc = regData[0]<<12|regData[1]<<4|regData[0]>>4;
    double var1,var2,t_fine,temp_comp;
    var1 = (((double)temp_adc / 16384.0) - ((double)par_t1 / 1024.0)) * (double)par_t2;
    var2 = ((((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0)) *
           (((double)temp_adc / 131072.0) - ((double)par_t1 / 8192.0))) *
           ((double)par_t3 * 16.0);
    t_fine = var1 + var2;
    PBData.t_fine = t_fine;
    temp_comp = t_fine / 5120.0;
    *temp = temp_comp;
    PBData.temp_comp = temp_comp;
}

void BME688_PresGet(double* pressure){
    uint32_t par_p1,par_p2,par_p3,par_p4,par_p5\
            ,par_p6,par_p7,par_p8,par_p9,par_p10;//校准参数
    uint32_t pres_adc;//温度ADC原始值
    uint8_t rslt;//读取成功判断
    uint8_t i = 0;//通信错误码
    uint8_t regData[6];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x8E, regData, 5);
    if(!rslt){
        PRINT("Communication error:PresGet %d\r\n",i++);
        return;
    }
    par_p1 = regData[1]<<8|regData[0];
    par_p2 = regData[3]<<8|regData[2];
    par_p3 = regData[4];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x94, regData, 6);
    if(!rslt){
        PRINT("Communication error:PresGet %d\r\n",i++);
        return;
    }
    par_p4 = regData[1]<<8|regData[0];
    par_p5 = regData[3]<<8|regData[2];
    par_p6 = regData[5];
    par_p7 = regData[4];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x9C, regData, 5);
    if(!rslt){
        PRINT("Communication error:PresGet %d\r\n",i++);
        return;
    }
    par_p8 = regData[1]<<8|regData[0];
    par_p9 = regData[3]<<8|regData[2];
    par_p10 = regData[4];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1F, regData, 3);
    if(!rslt){
        PRINT("Communication error:PresGet %d\r\n",i++);
        return;
    }
    pres_adc = regData[0]<<12|regData[1]<<4|regData[0]>>4;
    double var1,var2,var3,press_comp;
    var1 = ((double)PBData.t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)par_p6 / 131072.0);
    var2 = var2 + (var1 * (double)par_p5 * 2.0);
    var2 = (var2 / 4.0) + ((double)par_p4 * 65536.0);
    var1 = ((((double)par_p3 * var1 * var1) / 16384.0) +
     ((double)par_p2 * var1)) / 524288.0;
    var1 = (1.0 + (var1 / 32768.0)) * (double)par_p1;
    press_comp = 1048576.0 - (double)pres_adc;
    press_comp = ((press_comp - (var2 / 4096.0)) * 6250.0) / var1;
    var1 = ((double)par_p9 * press_comp * press_comp) / 2147483648.0;
    var2 = press_comp * ((double)par_p8 / 32768.0);
    var3 = (press_comp / 256.0) * (press_comp / 256.0) *
     (press_comp / 256.0) * (par_p10 / 131072.0);
    press_comp = press_comp + (var1 + var2 + var3 +
     ((double)par_p7 * 128.0)) / 16.0;
    *pressure  = press_comp;
}
void BME688_HumiGet(double* humidity){
    //获取AD值以及校准参数
    uint32_t par_h1,par_h2,par_h3,par_h4,par_h5,par_h6,par_h7;//校准参数
    uint32_t humi_adc;//温度ADC原始值
    uint8_t rslt;//读取成功判断
    uint8_t i = 0;//通信错误码
    uint8_t regData[8] = {0};
    rslt = i2c_read_reg(&i2c1, 0x76, 0xE1, regData, 8);
    if(!rslt){
        PRINT("Communication error:HumiGet %d\r\n",i++);
        return;
    }
    par_h1 = regData[2]<<4|(regData[1]&0b00001111);//选中数据后四位
    par_h2 = regData[0]<<4|regData[1]>>4;//取MSB-4
    par_h3 = regData[3];
    par_h4 = regData[4];
    par_h5 = regData[5];
    par_h6 = regData[6];
    par_h7 = regData[7];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x25, regData, 2);
    if(!rslt){
        PRINT("Communication error:HumiGet %d\r\n",i++);
        return;
    }
    humi_adc = regData[0]<<8|regData[1];
    double var1,var2,var3,var4,hum_comp;
    var1 = humi_adc - (((double)par_h1 * 16.0) + (((double)par_h3 / 2.0) * PBData.temp_comp));
    var2 = var1 * (((double)par_h2 / 262144.0) * (1.0 + (((double)par_h4 / 16384.0) *
            PBData.temp_comp) + (((double)par_h5 / 1048576.0) * PBData.temp_comp * PBData.temp_comp)));
    var3 = (double)par_h6 / 16384.0;
    var4 = (double)par_h7 / 2097152.0;
    hum_comp = var2 + ((var3 + (var4 * PBData.temp_comp)) * var2 * var2);
    *humidity = hum_comp;
}

void BME688_HeatResGet(double target_temp,uint8_t* res_heat_x){
    uint32_t par_g1,par_g2,par_g3;
    int8_t res_heat_range,res_heat_val;
    uint8_t rslt;//读取成功判断
    uint8_t i = 0;//通信错误码
    uint8_t regData[4] = {0};
    rslt = i2c_read_reg(&i2c1, 0x76, 0xEB, regData, 4);
    if(!rslt){
        PRINT("Communication error:HeatResGet %d\r\n",i++);
        return;
    }
    par_g1 = regData[2];
    par_g2 = regData[1]<<8|regData[0];
    par_g3 = regData[3];
    rslt = i2c_read_reg(&i2c1, 0x76, 0x02, regData, 1);
    if(!rslt){
        PRINT("Communication error:HeatResGet %d\r\n",i++);
        return;
    }
    res_heat_range = (regData[0]>>4)&0b00110000;
    rslt = i2c_read_reg(&i2c1, 0x76, 0x00, regData, 1);
    if(!rslt){
        PRINT("Communication error:HeatResGet %d\r\n",i++);
        return;
    }
    res_heat_val = regData[0];
    double var1,var2,var3,var4,var5;
    var1 = ((double)par_g1 / 16.0) + 49.0;
    var2 = (((double)par_g2 / 32768.0) * 0.0005) + 0.00235;
    var3 = (double)par_g3 / 1024.0;
    var4 = var1 * (1.0 + (var2 * (double) target_temp));
    var5 = var4 + (var3 * (double)PBData.temp_comp);//目标设定阻值，单位Ohm
    res_heat_x = (uint8_t)(3.4 * ((var5 * (4.0 / (4.0 + (double)res_heat_range)) * (1.0/(1.0 +
    ((double)res_heat_val * 0.002)))) - 25));
}
uint8_t BME688_MeaStusGet(void){
    uint8_t meas_status,rslt;
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1D, &meas_status, 1);
    if(!rslt){
        PRINT("Communication error:status read\r\n");
        return 0;
    }
    // 检查新数据有效位(bit7)
    if(!(meas_status & 0x80)){
        PRINT("No new data available\r\n");
        return 0;
    }
    return 1;
}
