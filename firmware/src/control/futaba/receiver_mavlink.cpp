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
void ReceiverMavlink::start(const uint32_t *timeout) {
  this->timeout = timeout;
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
void ReceiverMavlink::update(receiver_data_t &result) {

  osalDbgCheck(ready);
  (void)result;
}





