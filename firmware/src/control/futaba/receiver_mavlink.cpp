#include "main.h"

#include <futaba/receiver_mavlink.hpp>

using namespace control;

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
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
ReceiverMavlink::ReceiverMavlink(systime_t timeout) : Receiver(timeout) {
  return;
}

/**
 *
 */
void ReceiverMavlink::start(void) {
  ready = true;
}

/**
 *
 */
void ReceiverMavlink::stop(void) {
  ready = false;
}

/**
 *
 */
msg_t ReceiverMavlink::update(uint16_t *pwm) const {

  msg_t ret = MSG_TIMEOUT;

  chDbgCheck(ready);

  for (size_t i=0; i<FUTABA_RECEIVER_PWM_CHANNELS; i++)
    pwm[i] = 1500;

  ret = MSG_TIMEOUT;
  return ret;
}




