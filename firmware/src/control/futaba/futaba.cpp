#include "main.h"
#include "putinrange.hpp"
#include "array_len.hpp"
#include "geometry.hpp"
#include "param_registry.hpp"
#include "mavlink_local.hpp"
#include "override_level_enum.hpp"
#include "futaba.hpp"

using namespace control;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/**
 *
 */
typedef enum {
  RC_OVERRIDE_HIGH,
  RC_OVERRIDE_MEDIUM,
  RC_OVERRIDE_LOW,
  RC_OVERRIDE_PULSE_GENERATOR,
  RC_OVERRIDE_ENUM_END
}rc_override_level_t;

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
/**
 *
 */
static msg_t futaba2high(RecevierOutput const &recv, FutabaOutput &result) {

  memcpy(result.ch, recv.ch, sizeof(recv.ch));

  result.man = ManualSwitch::semiauto;
  for (size_t i=0; i<PID_CHAIN_ENUM_END; i++)
    result.ol[i] = OverrideLevel::high;

  return MSG_OK;
}

/**
 *
 */
static msg_t futaba2medium(RecevierOutput const &recv, FutabaOutput &result) {

  memcpy(result.ch, recv.ch, sizeof(recv.ch));

  result.man = ManualSwitch::semiauto;
  for (size_t i=0; i<PID_CHAIN_ENUM_END; i++)
    result.ol[i] = OverrideLevel::medium;

  return MSG_OK;
}

/**
 *
 */
static msg_t futaba2low(RecevierOutput const &recv, FutabaOutput &result) {

  memcpy(result.ch, recv.ch, sizeof(recv.ch));

  result.man = ManualSwitch::semiauto;
  for (size_t i=0; i<PID_CHAIN_ENUM_END; i++)
    result.ol[i] = OverrideLevel::low;

  return MSG_OK;
}

/**
 *
 */
msg_t Futaba::semiauto_interpret(RecevierOutput const &recv,
                                 FutabaOutput &result, float dT) {
  msg_t ret = MSG_OK;

  switch(*override){
  case RC_OVERRIDE_HIGH:
    ret = futaba2high(recv, result);
    break;
  case RC_OVERRIDE_MEDIUM:
    ret = futaba2medium(recv, result);
    break;
  case RC_OVERRIDE_LOW:
    ret = futaba2low(recv, result);
    break;
  case RC_OVERRIDE_PULSE_GENERATOR:
    ret = alcoi.update(result, dT);
    break;
  }

  return ret;
}

/**
 *
 */
msg_t Futaba::man_switch_interpret(RecevierOutput const &recv,
                                   FutabaOutput &result, float dT) {
  msg_t ret = MSG_OK;

  switch(recv.man) {
  case ManualSwitch::manual:
    memcpy(result.ch, recv.ch, sizeof(recv.ch));
    result.man = ManualSwitch::manual;
    for (size_t i=0; i<PID_CHAIN_ENUM_END; i++)
      result.ol[i] = OverrideLevel::bypass;
    ret = MSG_OK;
    break;

  case ManualSwitch::fullauto:
    result.man = ManualSwitch::fullauto;
    for (size_t i=0; i<PID_CHAIN_ENUM_END; i++)
      result.ol[i] = OverrideLevel::high;
    ret = MSG_OK;
    break;

  case ManualSwitch::semiauto:
    ret = semiauto_interpret(recv, result, dT);
    break;
  }

  return ret;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
Futaba::Futaba(void) {

  static_assert(OverrideLevel::high ==
      static_cast<OverrideLevel>(RC_OVERRIDE_HIGH),   "");
  static_assert(OverrideLevel::medium ==
      static_cast<OverrideLevel>(RC_OVERRIDE_MEDIUM), "");
  static_assert(OverrideLevel::low ==
      static_cast<OverrideLevel>(RC_OVERRIDE_LOW),    "");
//  static_assert(OverrideLevel::bypass ==
//      static_cast<OverrideLevel>(RC_OVERRIDE_BYPASS), "");
}

/**
 *
 */
void Futaba::start(void) {

  param_registry.valueSearch("RC_timeout",  &timeout);
  param_registry.valueSearch("RC_override", &override);

  receiver_rc.start(timeout);
  receiver_mavlink.start(timeout);
  alcoi.start();

  ready = true;
}

/**
 *
 */
void Futaba::stop(void){

  ready = false;

  alcoi.stop();
  receiver_mavlink.stop();
  receiver_rc.stop();
}

/**
 * @brief   Process all receivers in priorities order (higher to lower)
 */
msg_t Futaba::update(FutabaOutput &result, float dT) {
  RecevierOutput recv;

  osalDbgCheck(ready);

  receiver_rc.update(recv);
  if (RECEIVER_STATUS_NO_ERRORS == recv.status)
    return man_switch_interpret(recv, result, dT);

  receiver_mavlink.update(recv);
  if (RECEIVER_STATUS_NO_ERRORS == recv.status)
    return man_switch_interpret(recv, result, dT);

  return MSG_TIMEOUT;
}

