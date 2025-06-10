#include "bme68x.h"
#include "bme68x_defs.h"
#include "bmelink.h"
#include "i2c.h"
#include "data.h"

extern DataTab_TypeDef DataTab;
extern softI2C_TypeDef i2c1;
static uint8_t dev_addr = BME68X_I2C_ADDR_LOW;
struct bme68x_dev dev;
#define BME68X_VALID_DATA  UINT8_C(0xB0)

void print_sensor_data(struct bme68x_data *comp_data)
{
#ifdef BME68X_USE_FPU
    printf("temperature:%0.2f*C   pressure:%0.2fhPa   humidity:%0.2f%%   Gas resistance:%0.2f ohm\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity, comp_data->gas_resistance         );
    printf("\r\b\r");
#else
    printf("temperature:%ld*C   pressure:%ldhPa   humidity:%ld%%   Gas resistance:%lu ohm\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity, comp_data->gas_resistance         );
    printf("\r\b\r");
#endif
}

int8_t stream_sensor_data_forced_mode(struct bme68x_dev *dev)
{
    int8_t rslt;
    uint8_t n_fields;
    uint32_t del_period;
    struct bme68x_conf conf;
    struct bme68x_heatr_conf heatr_conf;
    struct bme68x_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    conf.os_hum = BME68X_OS_1X;
    conf.os_pres = BME68X_OS_16X;
    conf.os_temp = BME68X_OS_2X;
    conf.filter = BME68X_FILTER_SIZE_15;

    rslt = bme68x_set_conf(&conf, dev);
    dev->delay_us(40*1000,dev->intf_ptr);

    heatr_conf.enable = BME68X_ENABLE;
    heatr_conf.heatr_temp = 300;
    heatr_conf.heatr_dur = 100;

    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, dev);
    dev->delay_us(40*1000,dev->intf_ptr);
//    printf("Temperature           Pressure             Humidity             Gas resistance\r\n");
//    /* Continuously stream sensor data */
//    while (1) {
//        rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, dev);
//        /* Wait for the measurement to complete and print data @25Hz */
//        del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, dev) + (heatr_conf.heatr_dur * 1000);
//        dev->delay_us(del_period*5, dev->intf_ptr);
//        rslt = bme68x_get_data(BME68X_FORCED_MODE, &comp_data, &n_fields, dev);
//        if(n_fields)
//        {
//            print_sensor_data(&comp_data);
//        }
//    }
    return rslt;
}

uint8_t readOrwrite = 1;
struct bme68x_heatr_conf heatr_conf;
extern struct bme68x_data comp_data;
uint8_t n_fields;
void BME_In_Task(void){
    if(readOrwrite) bme68x_set_op_mode(BME68X_FORCED_MODE, &dev);
    else {
        uint8_t rslt = bme68x_get_data(BME68X_FORCED_MODE, &comp_data, &n_fields, &dev);
        DataTab.gasRes = comp_data.gas_resistance;
        DataTab.humi1 = comp_data.humidity;
        DataTab.temp1 = comp_data.temperature;
        DataTab.pres1 = comp_data.pressure;
        print_sensor_data(&comp_data);
    }
    readOrwrite = !readOrwrite;
}

int8_t stream_sensor_data_parallel_mode(struct bme68x_dev *dev)
{
    int8_t rslt;
    uint8_t n_fields;
    struct bme68x_conf conf;
    struct bme68x_heatr_conf heatr_conf;
    struct bme68x_data comp_data[3];

    uint16_t temp_prof[10] = { 320, 100, 100, 100, 200, 200, 200, 320, 320, 320 };
    uint16_t mul_prof[10] = { 5, 2, 10, 30, 5, 5, 5, 5, 5, 5 };

    /* Recommended mode of operation: Indoor navigation */
    conf.os_hum = BME68X_OS_1X;
    conf.os_pres = BME68X_OS_16X;
    conf.os_temp = BME68X_OS_2X;
    conf.filter = BME68X_FILTER_SIZE_15;
    conf.odr = BME68X_ODR_62_5_MS;

    rslt = bme68x_set_conf(&conf, dev);
    dev->delay_us(40*1000,dev->intf_ptr);

    heatr_conf.enable = BME68X_ENABLE;
    heatr_conf.heatr_temp_prof = temp_prof;
    heatr_conf.heatr_dur_prof = mul_prof;

    heatr_conf.shared_heatr_dur = 140 - (bme68x_get_meas_dur(BME68X_PARALLEL_MODE, &conf, dev) / 1000);

    heatr_conf.profile_len = 10;

    rslt = bme68x_set_heatr_conf(BME68X_PARALLEL_MODE, &heatr_conf, dev);
    dev->delay_us(40*1000,dev->intf_ptr);

    rslt = bme68x_set_op_mode(BME68X_PARALLEL_MODE, dev);
    dev->delay_us(40*1000,dev->intf_ptr);

    printf("Temperature           Pressure             Humidity             Gas resistance\r\n");
    while (1) {
        /* Delay while the sensor completes a measurement */
        dev->delay_us(70*1000,dev->intf_ptr);
        rslt = bme68x_get_data(BME68X_PARALLEL_MODE, comp_data, &n_fields, dev);
        for (uint8_t i = 0; i < n_fields; i++)
        {
            if (comp_data[i].status == BME68X_VALID_DATA)
            {
                print_sensor_data(&comp_data[i]);
            }
        }
    }

    return rslt;
}

void bme688devInit(void)
{
    // 设置接口类型和函数指针
    dev.intf = BME68X_I2C_INTF;      // 接口类型为 I2C
    dev.read = user_i2c_read;        // 绑定读取函数
    dev.write = user_i2c_write;      // 绑定写入函数
    dev.delay_us = user_delay_us;    // 绑定延时函数
    dev.intf_ptr = &dev_addr;        // 传递设备地址给读写函数
    dev.amb_temp = 24;               // 环境温度（用于校准）
    // 初始化传感器
    int8_t rslt = bme68x_init(&dev);
    if (rslt != BME68X_OK) {
        printf("初始化失败！错误码: %d\n", rslt);
        // 处理错误
    }
    stream_sensor_data_forced_mode(&dev);
    //stream_sensor_data_parallel_mode(&dev);
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
