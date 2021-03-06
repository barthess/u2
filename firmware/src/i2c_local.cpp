#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static const I2CConfig i2cfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

//static const I2CConfig i2cfg = {
//    OPMODE_I2C,
//    100000,
//    STD_DUTY_CYCLE,
//};

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void I2CInitLocal(void){

#if defined(BOARD_BEZVODIATEL)
  i2cStart(&I2CD1, &i2cfg);
  i2cStart(&I2CD2, &i2cfg);
#elif defined(BOARD_MNU)
  i2cStart(&I2CD2, &i2cfg);
  i2cStart(&I2CD3, &i2cfg);
#else
#error "Unknown board"
#endif
}


/**
 *
 */
void I2CStopLocal(void){

#if defined(BOARD_BEZVODIATEL)
  i2cStop(&I2CD1);
  i2cStop(&I2CD2);
#elif defined(BOARD_MNU)
  i2cStop(&I2CD2);
  i2cStop(&I2CD3);
#else
#error "Unknown board"
#endif
}
