#include "bme68x.h"
#include "bme68x_defs.h"
#include "bmelink.h"
#include "i2c.h"

extern softI2C_TypeDef i2c1;
extern uint8_t dev_addr;

void updateBME688(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_data* data){
    uint8_t n_fields;

    // 设置为强制模式（单次测量）
    uint8_t rslt;
    rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, dev);

    // 计算测量所需时间并等待
    uint32_t meas_dur;
    meas_dur = bme68x_get_meas_dur(BME68X_FORCED_MODE, conf, dev);
    dev->delay_us(meas_dur, dev->intf_ptr);

    // 读取数据
    rslt = bme68x_get_data(BME68X_FORCED_MODE, data, &n_fields, dev);

    if (rslt == BME68X_OK && n_fields > 0) {
        printf("温度: %.2f °C\n", data->temperature);
        printf("湿度: %.2f %%\n", data->humidity);
        printf("气压: %.2f Pa\n", data->pressure);
        printf("气体电阻: %.2f Ω\n", data->gas_resistance);
    } else {
        printf("无新数据或读取失败！\n");
    }
}


void bme688devInit(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_heatr_conf* heatr_conf)
{
    // 设置接口类型和函数指针
    dev->intf = BME68X_I2C_INTF;      // 接口类型为 I2C
    dev->read = user_i2c_read;        // 绑定读取函数
    dev->write = user_i2c_write;      // 绑定写入函数
    dev->delay_us = user_delay_us;    // 绑定延时函数
    dev->intf_ptr = &dev_addr;        // 传递设备地址给读写函数
    dev->amb_temp = 6;               // 环境温度（用于校准）
    // 初始化传感器
    int8_t rslt = bme68x_init(dev);
    if (rslt != BME68X_OK) {
        printf("初始化失败！错误码: %d\n", rslt);
        // 处理错误
    }
    // 获取当前配置
    rslt = bme68x_get_conf(conf, dev);
    if (rslt != BME68X_OK) {
        printf("获取配置失败！错误码: %d\n", rslt);
    }
    else {
        printf("获取配置成功\n");
    }

    // 设置采样率和滤波器
    conf->os_hum = BME68X_OS_1X;     // 湿度 1 倍过采样
    conf->os_temp = BME68X_OS_2X;    // 温度 2 倍过采样
    conf->os_pres = BME68X_OS_16X;    // 气压 16 倍过采样
    conf->filter = BME68X_FILTER_OFF; // 关闭滤波器
    conf->odr = BME68X_ODR_NONE;

    // 配置加热器（用于气体测量）
    heatr_conf->enable = BME68X_ENABLE;      // 启用加热器
    heatr_conf->heatr_temp = 300;           // 加热温度 300°C
    heatr_conf->heatr_dur = 100;            // 加热持续时间 100ms

    // 应用配置
    rslt = bme68x_set_conf(conf, dev);
    if (rslt != BME68X_OK) {
            printf("配置0失败！错误码: %d\n", rslt);
            // 处理错误
        }
    else
        printf("配置0成功");
    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, heatr_conf, dev);
    if (rslt != BME68X_OK) {
                printf("配置1失败！错误码: %d\n", rslt);
                // 处理错误
            }
    else
        printf("配置1成功");
}
// I2C 读取函数实现示例（基于标准接口）
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = 0x76; // 从指针获取设备地址
    // 假设 i2c_read_reg 是平台的I2C读寄存器函数
    if (i2c_read_reg(&i2c1,dev_addr, reg_addr, reg_data, len) == 0) {
        return BME68X_E_COM_FAIL; // 通信失败
    }
    return BME68X_OK; // 成功
}

// I2C 写入函数实现示例

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = 0x76;
    // 假设 i2c_write_reg 是平台的I2C写寄存器函数
    if (i2c_write_reg(&i2c1,dev_addr, reg_addr, reg_data, len) == 0) {
        return BME68X_E_COM_FAIL;
    }
    return BME68X_OK;
}

// 微秒级延时函数（需根据系统实现）
void user_delay_us(uint32_t period, void *intf_ptr) {
    DelayUs(period);
}
