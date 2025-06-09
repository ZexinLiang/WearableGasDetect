/*
 * bmeInRegis.c
 *
 *  Created on: 2025年3月1日
 *      Author: 86135
 */

#include "bmeInRegis.h"

uint8_t BME688InitInReg(void){
    uint8_t rslt;//通信验证
    uint8_t chip_id;//芯片ID
    rslt = i2c_read_reg(&i2c1, 0x76, 0xD0, &chip_id, 1);//读取芯片ID
    if(!rslt){
        PRINT("Communication error:ID read\n");
        return 1;//失败
    }
    if(chip_id!=0x61){
        PRINT("ID recognition error\n");
        return 1;//失败
    }
    DelayMs(100);
    //初始化配置
    uint8_t h_rate = 0x01;//湿度采样率1x
    uint8_t tp_rate  = (0b010<<5)|(0b101<<2);//温度采样率2x，压力采样率16x
    DelayMs(1);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &tp_rate, 1);
    if(!rslt){
        PRINT("Communication error:temp pre rate set\n");
        return 1;//失败
    }else{
        PRINT("OK:temp pre rate set\r\n");
    }
//        DelayMs(100);
//        rslt = i2c_write_reg(&i2c1, 0x76, 0x72, &h_rate, 1);
//        if(!rslt){
//            PRINT("Communication error:humi rate set\n");
//            return 1;//失败
//        }
    uint8_t iir_flt = 0b100<<2;//IIR滤波器，滤波系数15
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x75, &iir_flt, 1);
    if(!rslt){
        PRINT("Communication error:iir_flt set\n");
        return 1;//失败
    }
    // 气体传感器配置
    // 步骤1: 设置加热时间gas_wait_0 (100ms)
    uint8_t gas_wait_0 = 0x59; // 0b01011001 (64*1 + 25=89 => 89ms ≈ 100ms)
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x64, &gas_wait_0, 1);
    if(!rslt){
        PRINT("Communication error:gas_wait_0 set\n");
        return 1;
    }

    // 步骤2: 计算并设置目标温度电阻值res_heat_0 (假设目标温度300°C)
    // 注：实际应使用API函数计算，这里使用示例值（需根据校准参数调整）
    uint8_t res_heat_0 = 0x50; // 示例值，需根据规格书第27页公式计算
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x5A, &res_heat_0, 1);
    if(!rslt){
        PRINT("Communication error:res_heat_0 set\n");
        return 1;
    }

    // 步骤3: 选择加热步骤0，启用气体测量
    uint8_t gas_ctrl1 = (0x0 << 0) | (1 << 5); // nb_conv=0, run_gas=1
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x71, &gas_ctrl1, 1);
    if(!rslt){
        PRINT("Communication error:gas_ctrl1 set\n");
        return 1;
    }

    // 触发强制模式测量
    uint8_t mode = 0x01; // Forced Mode
    DelayMs(100);
    rslt = i2c_write_reg(&i2c1, 0x76, 0x74, &mode, 1);
    if(!rslt){
        PRINT("Communication error:mode set\n");
        return 1;
    }

    // 等待测量完成（典型等待时间约100ms）
    DelayMs(100);

    // 读取状态寄存器
    uint8_t meas_status;
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1D, &meas_status, 1);
    if(!rslt){
        PRINT("Communication error:status read\n");
        return 1;
    }

    // 检查新数据有效位(bit7)
    if(!(meas_status & 0x80)){
        PRINT("No new data available\n");
        return 1;
    }

    // 读取原始数据（Field 0）
    uint8_t data[15];
    DelayMs(100);
    rslt = i2c_read_reg(&i2c1, 0x76, 0x1F, data, 15);
    if(!rslt){
        PRINT("Communication error:data read\n");
        return 1;
    }

    // 解析原始数据
    uint32_t press_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    uint32_t temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
    uint16_t hum_raw = (data[6] << 8) | data[7];
    uint16_t gas_res = (data[13] << 2) | (data[14] >> 6);
    uint8_t gas_range = data[14] & 0x0F;

    // 打印结果
    PRINT("Temperature: %d \n", temp_raw);
    // 添加压力、湿度、气体补偿计算...
    // 先读取校准参数（关键步骤！）
    uint16_t par_t1;
    uint16_t par_t2;
    int8_t par_t3;
    uint8_t calib_data[5];

    // 读取温度校准参数寄存器组
    DelayMs(100);
    rslt = i2c_read_reg(&i2c1, 0x76, 0xE9, calib_data, 5);  // 0xE9-0xED
    if(!rslt){
         PRINT("Communication error:reg read\n");
         return 1;
     }

    // 解析校准参数
    par_t1 = (calib_data[1] << 8) | calib_data[0];     // 0xE9-0xEA
    par_t2 = (calib_data[3] << 8) | calib_data[2];     // 0x8B-0x8C
    par_t3 = (int8_t)calib_data[4];                    // 0x8D

    // 读取原始温度数据（假设已获取data数组）

    // 整数补偿算法（规格书第23页）
    int32_t var1, var2,var3, t_fine;
    int32_t temp_comp;

    var1 = ((int32_t)temp_raw >> 3) - ((int32_t)par_t1 << 1);
    var2 = (var1 * (int32_t)par_t2) >> 11;
    var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)par_t3 << 4)) >> 14;
    t_fine = var2 + var3;

    // 最终温度计算（带0.01°C分辨率）
    temp_comp = (t_fine * 5 + 128) >> 8;  // 等价于 (t_fine / 5120.0) * 100

    // 转换为浮点温度值
    float temperature = temp_comp / 100.0f;
    PRINT("p1:%d p2:%d p3:%d\n",par_t1,par_t2,par_t3);
    PRINT("Compensated Temp: %.2f C\n", temperature);

    return 0;//配置成功
}

