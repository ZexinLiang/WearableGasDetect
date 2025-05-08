#ifndef __BME_LINK_H__
#define __BME_LINK_H__

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

void bme688devInit(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_heatr_conf* heatr_conf);

void updateBME688(struct bme68x_dev* dev,struct bme68x_conf* conf,struct bme68x_data* data);

void user_delay_us(uint32_t period, void *intf_ptr);
#endif
