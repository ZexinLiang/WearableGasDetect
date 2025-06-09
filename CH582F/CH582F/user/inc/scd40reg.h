/*
 * scd40reg.h
 *
 *  Created on: 2025Äê5ÔÂ9ÈÕ
 *      Author: 86135
 */

#ifndef USER_INC_SCD40REG_H_
#define USER_INC_SCD40REG_H_
#include "i2c.h"

uint8_t SCD40Init(uint8_t* cnt);
uint8_t CRC_Cal(const uint8_t* data, uint16_t count);
void start_periodic_measurement(void);
void read_measurement(uint16_t *CO2,uint16_t *Temperature,uint16_t *Relative_humidity);
void stop_periodic_measurement(void);
void set_sensor_offset(float *offset_set);
void get_temperature_offset(float *offset);
void set_sensor_altitude(uint16_t *altitude_set);
void get_sensor_altitude(uint16_t *altitude);
void set_ambient_pressure(uint16_t *pressure_set);
void  perform_forced_recalibration(uint16_t *correction,int16_t *frc_c);
void set_automatic_self_calibration_enabled(uint8_t ASC_en);
void get_automatic_self_calibration_enabled (uint16_t *state);
void start_low_power_periodic_measurement(void);
void get_data_ready_status (uint8_t *ready_state);
void persist_settings(void);
void perform_self_test(uint16_t *self_test);
void perform_factory_reset(void);
void reinit(void);
void measure_single_shot(void);
void measure_single_shot_rht_only(void);

#endif /* USER_INC_SCD40REG_H_ */
