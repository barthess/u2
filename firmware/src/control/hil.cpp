#include "main.h"
#include "acs_input.hpp"
#include "hil.hpp"

using namespace chibios_rt;
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
HIL::HIL(void) {

}

/**
 *
 */
void HIL::update(ACSInput &acs_in) {

  for (size_t i=0; i<ACS_INPUT_ENUM_END; i++) {
    if (bitmapGet(&this->bmp.bitmap, i) > 0) {
      acs_in.ch[i] = this->shadow.ch[i];
    }
  }
}

/**
 *
 */
void HIL::disableAll(void) {
  bitmapObjectInit(&this->bmp.bitmap, 0);
}

/**
 *
 */
void HIL::override(float val, state_vector_enum addr) {
  osalDbgCheck(addr < ACS_INPUT_ENUM_END);

  shadow.ch[addr] = val;
  bitmapSet(&this->bmp.bitmap, addr);
}