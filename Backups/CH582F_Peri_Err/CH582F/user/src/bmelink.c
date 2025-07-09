#include "bme68x.h"
#include "bme68x_defs.h"
#include "bmelink.h"
#include "i2c.h"

extern softI2C_TypeDef i2c1;
extern uint8_t dev_addr;

void updateBME688(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_data* data){
    uint8_t n_fields;

    // ����Ϊǿ��ģʽ�����β�����
    uint8_t rslt;
    rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, dev);

    // �����������ʱ�䲢�ȴ�
    uint32_t meas_dur;
    meas_dur = bme68x_get_meas_dur(BME68X_FORCED_MODE, conf, dev);
    dev->delay_us(meas_dur, dev->intf_ptr);

    // ��ȡ����
    rslt = bme68x_get_data(BME68X_FORCED_MODE, data, &n_fields, dev);

    if (rslt == BME68X_OK && n_fields > 0) {
        printf("�¶�: %.2f ��C\n", data->temperature);
        printf("ʪ��: %.2f %%\n", data->humidity);
        printf("��ѹ: %.2f Pa\n", data->pressure);
        printf("�������: %.2f ��\n", data->gas_resistance);
    } else {
        printf("�������ݻ��ȡʧ�ܣ�\n");
    }
}


void bme688devInit(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_heatr_conf* heatr_conf)
{
    // ���ýӿ����ͺͺ���ָ��
    dev->intf = BME68X_I2C_INTF;      // �ӿ�����Ϊ I2C
    dev->read = user_i2c_read;        // �󶨶�ȡ����
    dev->write = user_i2c_write;      // ��д�뺯��
    dev->delay_us = user_delay_us;    // ����ʱ����
    dev->intf_ptr = &dev_addr;        // �����豸��ַ����д����
    dev->amb_temp = 6;               // �����¶ȣ�����У׼��
    // ��ʼ��������
    int8_t rslt = bme68x_init(dev);
    if (rslt != BME68X_OK) {
        printf("��ʼ��ʧ�ܣ�������: %d\n", rslt);
        // �������
    }
    // ��ȡ��ǰ����
    rslt = bme68x_get_conf(conf, dev);
    if (rslt != BME68X_OK) {
        printf("��ȡ����ʧ�ܣ�������: %d\n", rslt);
    }
    else {
        printf("��ȡ���óɹ�\n");
    }

    // ���ò����ʺ��˲���
    conf->os_hum = BME68X_OS_1X;     // ʪ�� 1 ��������
    conf->os_temp = BME68X_OS_2X;    // �¶� 2 ��������
    conf->os_pres = BME68X_OS_16X;    // ��ѹ 16 ��������
    conf->filter = BME68X_FILTER_OFF; // �ر��˲���
    conf->odr = BME68X_ODR_NONE;

    // ���ü��������������������
    heatr_conf->enable = BME68X_ENABLE;      // ���ü�����
    heatr_conf->heatr_temp = 300;           // �����¶� 300��C
    heatr_conf->heatr_dur = 100;            // ���ȳ���ʱ�� 100ms

    // Ӧ������
    rslt = bme68x_set_conf(conf, dev);
    if (rslt != BME68X_OK) {
            printf("����0ʧ�ܣ�������: %d\n", rslt);
            // �������
        }
    else
        printf("����0�ɹ�");
    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, heatr_conf, dev);
    if (rslt != BME68X_OK) {
                printf("����1ʧ�ܣ�������: %d\n", rslt);
                // �������
            }
    else
        printf("����1�ɹ�");
}
// I2C ��ȡ����ʵ��ʾ�������ڱ�׼�ӿڣ�
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = 0x76; // ��ָ���ȡ�豸��ַ
    // ���� i2c_read_reg ��ƽ̨��I2C���Ĵ�������
    if (i2c_read_reg(&i2c1,dev_addr, reg_addr, reg_data, len) == 0) {
        return BME68X_E_COM_FAIL; // ͨ��ʧ��
    }
    return BME68X_OK; // �ɹ�
}

// I2C д�뺯��ʵ��ʾ��

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = 0x76;
    // ���� i2c_write_reg ��ƽ̨��I2Cд�Ĵ�������
    if (i2c_write_reg(&i2c1,dev_addr, reg_addr, reg_data, len) == 0) {
        return BME68X_E_COM_FAIL;
    }
    return BME68X_OK;
}

// ΢�뼶��ʱ�����������ϵͳʵ�֣�
void user_delay_us(uint32_t period, void *intf_ptr) {
    DelayUs(period);
}
