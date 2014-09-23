#ifndef LSM303_MAG_HPP_
#define LSM303_MAG_HPP_

#include "i2c_sensor.hpp"

#define lsm303magaddr       0b0011110

#define LSM_MAG_RX_DEPTH    8
#define LSM_MAG_TX_DEPTH    4

class LSM303_mag: private I2CSensor {
public:
  LSM303_mag(I2CDriver *i2cdp, i2caddr_t addr);
  msg_t get(float *result);
  msg_t start(void);
  void stop(void);

private:
  msg_t set_gain(uint8_t val);
  msg_t refresh_gain(void);
  msg_t start_single_measurement(void);
  void thermo_comp(float *result);
  void iron_comp(float *result);
  float mag_sens(void);
  void pickle(float *result);
  msg_t hw_init_full(void);
  msg_t hw_init_fast(void);
  uint8_t rxbuf[LSM_MAG_RX_DEPTH];
  uint8_t txbuf[LSM_MAG_TX_DEPTH];
  size_t sample_cnt;
  const uint32_t *gain = NULL;
  float cache[3];
  uint8_t gain_prev;
};

#endif /* LSM303_MAG_HPP_ */
