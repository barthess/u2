#include "main.h"
#include "drivetrain.hpp"

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
Drivetrain::Drivetrain(void) :
engine(pwm),
servo(pwm)
{
  return;
}

/**
 *
 */
void Drivetrain::start(void) {

  pwm.start();
  engine.start();
  servo.start();

  ready = true;
}

/**
 *
 */
void Drivetrain::stop(void) {
  ready = false;

  servo.stop();
  engine.stop();
  pwm.stop();
}

/**
 *
 */
msg_t Drivetrain::update(const FutabaData &futaba_data, const Impact &impact) {

  osalDbgCheck(ready);

  if (OverrideLevel::impact == futaba_data.level) {
    osalSysHalt("Unrealized/Untested");
    servo.update(futaba_data, futaba_data.impact);
    engine.update(futaba_data, futaba_data.impact);
  }
  else {
    servo.update(futaba_data, impact);
    engine.update(futaba_data, impact);
  }

  return MSG_OK;
}

/**
 *
 */
void Drivetrain::futaba_override(const PwmVector &override) {
  pwm.futaba_override(override);
}