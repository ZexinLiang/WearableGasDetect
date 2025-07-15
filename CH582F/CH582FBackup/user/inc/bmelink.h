#ifndef __BME_LINK_H__
#define __BME_LINK_H__

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);

void bme688devInit(void);

void BME_In_Task(void);

#endif
