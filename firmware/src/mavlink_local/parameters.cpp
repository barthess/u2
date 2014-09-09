#include <string.h>

#include "main.h"
#include "global_flags.h"

#include "message.hpp"
#include "param_registry.hpp"
#include "mavdbg.hpp"
#include "this_comp_id.h"
#include "subscribe_link.hpp"

using namespace chibios_rt;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define PARAM_CONFIRM_TMO     MS2ST(1000)
#define PARAM_POST_TMO        MS2ST(50)
#define SEND_VALUE_PAUSE      MS2ST(50)
#define CHECK_FRESH_PERIOD    MS2ST(50)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

extern mavlink_system_t               mavlink_system_struct;

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
static mavlink_param_value_t          mavlink_out_param_value_struct;
static mavlink_param_set_t            mavlink_in_param_set_struct;
static mavlink_param_request_read_t   mavlink_in_param_request_read_struct;
static mavlink_param_request_list_t   mavlink_in_param_request_list_struct;

static bool param_set_fresh = false;
static bool param_request_read_fresh = false;
static bool param_request_list_fresh = false;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

static void param_set_callback(const mavlink_message_t &msg);
static void param_request_read_callback(const mavlink_message_t &msg);
static void param_request_list_callback(const mavlink_message_t &msg);

static SubscribeLink param_set_link(param_set_callback);
static SubscribeLink param_request_read_link(param_request_read_callback);
static SubscribeLink param_request_list_link(param_request_list_callback);

static void param_set_callback(const mavlink_message_t &msg){
  if (false == param_set_fresh){
    mavlink_msg_param_set_decode(&msg, &mavlink_in_param_set_struct);
    param_set_fresh = true;
  }
}

static void param_request_read_callback(const mavlink_message_t &msg){
  if (false == param_request_read_fresh){
    mavlink_msg_param_request_read_decode(&msg, &mavlink_in_param_request_read_struct);
    param_request_read_fresh = true;
  }
}

static void param_request_list_callback(const mavlink_message_t &msg){
  if (false == param_request_list_fresh){
    mavlink_msg_param_request_list_decode(&msg, &mavlink_in_param_request_list_struct);
    param_request_list_fresh = true;
  }
}

/**
 *
 */
static void ParamValueSend(const mavlink_param_value_t *m, MAV_COMPONENT comp){
  (void)m;
  (void)comp;
  osalSysHalt("Unported yet");
}

/**
 * @brief   Sends answer to QGC
 *
 * @param[in] key   if NULL than perform search by index
 * @param[in] n     search index
 */
static bool send_value(const char *key, int32_t n){
  int32_t index = -1;
  const GlobalParam_t *p;

  p = param_registry.getParam(key, n, &index);

  if (-1 != index){
    /* fill all fields */
    mavlink_out_param_value_struct.param_value = p->valuep->f32;
    mavlink_out_param_value_struct.param_type  = p->param_type;
    mavlink_out_param_value_struct.param_count = param_registry.paramCount();
    mavlink_out_param_value_struct.param_index = index;
    memcpy(mavlink_out_param_value_struct.param_id, p->name, ONBOARD_PARAM_NAME_LENGTH);

    /* inform sending thread */
    ParamValueSend(&mavlink_out_param_value_struct, MAV_COMP_ID_SYSTEM_CONTROL);
    osalThreadSleep(SEND_VALUE_PAUSE);
    return OSAL_SUCCESS;
  }
  else
    return OSAL_FAILED;
}

/**
 * @brief   Sends fake answer to ground.
 *
 * @param[in] p   pointer to mavlink_param_set_t structure received from QGC
 */
static void ignore_value(const mavlink_param_set_t &p){

  /* fill all fields */
  mavlink_out_param_value_struct.param_value = p.param_value;
  mavlink_out_param_value_struct.param_type  = p.param_type;
  mavlink_out_param_value_struct.param_count = param_registry.paramCount();
  mavlink_out_param_value_struct.param_index = param_registry.paramCount();
  memcpy(mavlink_out_param_value_struct.param_id, p.param_id, ONBOARD_PARAM_NAME_LENGTH);

  /* inform sending thread */
  ParamValueSend(&mavlink_out_param_value_struct, MAV_COMP_ID_SYSTEM_CONTROL);
  chThdSleep(SEND_VALUE_PAUSE);
}

/**
 * Send all values one by one.
 */
static void send_all_values(void){
  int32_t i = 0;
  int32_t retry = 20;

  msg_t status = MSG_RESET;
  while ((i < param_registry.paramCount()) && (retry > 0)){
    status = send_value(NULL, i);
    if (status == OSAL_SUCCESS)
      i++;
    else
      retry--;
  }
}

/**
 * The MAV has to acknowledge the write operation by emitting a
 * PARAM_VALUE value message with the newly written parameter value.
 */
static void param_set_handler(void){
  floatint *valuep = NULL;
  const GlobalParam_t *paramp = NULL;
  param_status_t status;

  valuep = (floatint *)&(mavlink_in_param_set_struct.param_value);
  paramp = param_registry.getParam(mavlink_in_param_set_struct.param_id, -1, NULL);
  if (NULL == paramp){
    ignore_value(mavlink_in_param_set_struct);
    return;
  }
  else{
    status = param_registry.setParam(valuep, paramp);
  }

  /* send confirmation */
  osalSysHalt("debug print unrealized");
  (void)status;
//  switch(status){
//  case PARAM_CLAMPED:
//    mavlink_dbg_print(MAV_SEVERITY_WARNING, "PARAM: clamped", MAV_COMP_ID_SYSTEM_CONTROL);
//    break;
//  case PARAM_NOT_CHANGED:
//    mavlink_dbg_print(MAV_SEVERITY_WARNING, "PARAM: not changed", MAV_COMP_ID_SYSTEM_CONTROL);
//    break;
//  case PARAM_INCONSISTENT:
//    mavlink_dbg_print(MAV_SEVERITY_ERROR, "PARAM: inconsistent", MAV_COMP_ID_SYSTEM_CONTROL);
//    break;
//  case PARAM_WRONG_TYPE:
//    mavlink_dbg_print(MAV_SEVERITY_ERROR, "PARAM: wrong type", MAV_COMP_ID_SYSTEM_CONTROL);
//    break;
//  case PARAM_UNKNOWN_ERROR:
//    mavlink_dbg_print(MAV_SEVERITY_ERROR, "PARAM: unknown error", MAV_COMP_ID_SYSTEM_CONTROL);
//    break;
//  case PARAM_OK:
//    break;
//  }

  send_value(mavlink_in_param_set_struct.param_id, 0);
}

/**
 *
 */
static void param_request_read_handler(void){
  if (mavlink_in_param_request_read_struct.param_index >= 0)
    send_value(NULL, mavlink_in_param_request_read_struct.param_index);
  else
    send_value(mavlink_in_param_request_read_struct.param_id, 0);
}

/**
 * Decide is this packed addressed to us.
 */
template <typename T>
static bool for_me(T *message){
  if (message->target_system != mavlink_system_struct.sysid)
    return FALSE;
  if (THIS_COMP_ID == message->target_component)
    return TRUE;
  else if (MAV_COMP_ID_ALL == message->target_component)
    return TRUE;
  else
    return FALSE;
}

/**
 * Receive messages with parameters and transmit parameters by requests.
 */
static THD_WORKING_AREA(ParametersThreadWA, 512);
static THD_FUNCTION(ParametersThread, arg){
  chRegSetThreadName("ParamWorker");
  (void)arg;

  while (!chThdShouldTerminateX()) {
    /* set single parameter */
    if (true == param_set_fresh){
      if (for_me(&mavlink_in_param_set_struct))
        param_set_handler();
      param_set_fresh = false;
    }

    /* request all */
    if (true == param_request_list_fresh){
      if (for_me(&mavlink_in_param_request_list_struct))
        send_all_values();
      param_request_list_fresh = false;
    }

    /* request single */
    if (true == param_request_read_fresh){
      if (for_me(&mavlink_in_param_request_read_struct))
        param_request_read_handler();
      param_request_read_fresh = false;
    }

    osalThreadSleepMilliseconds(CHECK_FRESH_PERIOD);
  }

  chThdExit(MSG_OK);
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void ParametersInit(void){
  /* read data from eeprom to memory mapped structure */
  param_registry.load();

  chThdCreateStatic(ParametersThreadWA,
          sizeof(ParametersThreadWA),
          NORMALPRIO,
          ParametersThread,
          NULL);

  setGlobalFlag(GlobalFlags.parameters_loaded);
}