#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"
#include "mavlink_local.hpp"
#include "param_registry.hpp"
#include "pack_unpack.h"
#include "array_len.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define ADDITIONAL_WRITE_TMO    MS2ST(5)

#define PARAM_VALUE_SIZE        (sizeof(param_union_t))
#define PARAM_RECORD_SIZE       (PARAM_ID_SIZE + PARAM_VALUE_SIZE)

#define PARAM_FILE_NAME         ("param")

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
ParamRegistry param_registry;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

#include "param_autogenerated.hpp"
static uint8_t eeprombuf[PARAM_RECORD_SIZE];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 *
 */
void ParamRegistry::acquire(void) {
  this->mutual_sem.wait();
}

/**
 *
 */
void ParamRegistry::release(void) {
  this->mutual_sem.signal();
}

/**
 * @brief   Performs key-value search. Low level function
 *
 * @return      Index in dictionary.
 * @retval -1   key not found.
 */
int ParamRegistry::key_index_search(const char* key) {
  int i = 0;

  for (i = 0; i < ONBOARD_PARAM_CNT; i++){
    if (strcmp(key, param_db[i].name) == 0)
      return i;
  }
  return -1;
}

void ParamRegistry::store_value(int i, float **vp){
  osalDbgCheck(MAVLINK_TYPE_FLOAT == param_db[i].param_type);
  *vp = &param_db[i].valuep->f32;
}

void ParamRegistry::store_value(int i, int32_t **vp){
  osalDbgCheck(MAVLINK_TYPE_INT32_T == param_db[i].param_type);
  *vp = &param_db[i].valuep->i32;
}

void ParamRegistry::store_value(int i, uint32_t **vp){
  osalDbgCheck(MAVLINK_TYPE_UINT32_T == param_db[i].param_type);
  *vp = &param_db[i].valuep->u32;
}

void ParamRegistry::store_value(int i, const float **vp){
  osalDbgCheck(MAVLINK_TYPE_FLOAT == param_db[i].param_type);
  *vp = &param_db[i].valuep->f32;
}

void ParamRegistry::store_value(int i, const int32_t **vp){
  osalDbgCheck(MAVLINK_TYPE_INT32_T == param_db[i].param_type);
  *vp = &param_db[i].valuep->i32;
}

void ParamRegistry::store_value(int i, const uint32_t **vp){
  osalDbgCheck(MAVLINK_TYPE_UINT32_T == param_db[i].param_type);
  *vp = &param_db[i].valuep->u32;
}

/**
 * This functions created for smooth update of parameter registry in case
 * adding of some new parameters somewhere in middle.
 * 1) get name from MCU's flash
 * 2) perform brute force search in EEPROM file
 */
bool ParamRegistry::load_extensive(void) {
  int i = 0, n = 0;
  size_t status = 0;
  param_union_t v;
  v.u32 = 0;
  bool found = false;

  for (i = 0; i < this->paramCount(); i++){
    ParamFile->setPosition(0);
    found = false;

    for (n=0; n<this->paramCount(); n++){
      status = ParamFile->read(eeprombuf, PARAM_RECORD_SIZE);
      if (status < PARAM_RECORD_SIZE){
        osalSysHalt("");
        return OSAL_FAILED;
      }
      if (strcmp((const char *)eeprombuf, param_db[i].name) == 0){
        found = true;
        break;
      }
    }

    /* was parameter previously stored in eeprom */
    if (found){
      v.u32 = pack8to32ne(&(eeprombuf[PARAM_ID_SIZE]));
    }
    else{
      /* use hardcoded default */
      v.u32 = param_db[i].def.u32;
    }

    /* check value acceptability and set it */
    validator.set(&v, &(param_db[i]));
  }

  return save_all();
}

/**
 *
 */
bool ParamRegistry::save_all(void) {
  int i;
  size_t status = 0;
  uint32_t v = 0;
  uint8_t tmpbuf[PARAM_RECORD_SIZE];

  ParamFile->setPosition(0);

  for (i = 0; i < this->paramCount(); i++){

    /* first copy parameter name into buffer */
    memcpy(eeprombuf, param_db[i].name, PARAM_ID_SIZE);

    /* now write data */
    v = param_db[i].valuep->u32;
    unpack32to8ne(v, &(eeprombuf[PARAM_ID_SIZE]));
    status = ParamFile->write(eeprombuf, PARAM_RECORD_SIZE);
    osalDbgAssert(status == PARAM_RECORD_SIZE, "write failed");

    /* check written data */
    ParamFile->setPosition(ParamFile->getPosition() - PARAM_RECORD_SIZE);
    status = ParamFile->read(tmpbuf, sizeof(tmpbuf));
    if (0 != memcmp(tmpbuf, eeprombuf, (PARAM_ID_SIZE + sizeof(v))))
      osalSysHalt("Verification failed");

    osalThreadSleep(ADDITIONAL_WRITE_TMO);
  }

  return OSAL_SUCCESS;
}

/**
 *
 */
void ParamRegistry::open_file(void) {

  ParamFile = NvramTryOpen(PARAM_FILE_NAME, BOOTSTRAP_PARAM_FILE_SIZE);
  osalDbgCheck(nullptr != ParamFile);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
ParamRegistry::ParamRegistry(void) :
    mutual_sem(false), ready(false) {

  int i = 0, n = 0;
  const int len = paramCount();

  osalDbgAssert((sizeof(gp_val) / sizeof(gp_val[0])) == len,
      "sizes of volatile array and param array must be equal");

  /* Initialize variable array with zeroes to be safer */
  param_union_t tmp;
  tmp.u32 = 0;
  for (i = 0; i < len; i++){
    gp_val[i] = tmp;
  }

  /* check hardcoded name lengths */
  for (i = 0; i<len; i++){
    if (strlen(param_db[i].name) > ONBOARD_PARAM_NAME_LENGTH)
      osalSysHalt("name too long");
  }

  /* check for keys' names collisions */
  for (n=0; n<len; n++){
    for (i=n+1; i<len; i++){
      if (0 == strcmp(param_db[i].name, param_db[n].name))
        osalSysHalt("name collision detected");
    }
  }
}

/**
 *
 */
bool ParamRegistry::syncParam(const char* key) {
  int i = 0;
  size_t status = 0;
  uint32_t v = 0;
  uint8_t  tmpbuf[PARAM_RECORD_SIZE];

  i = key_index_search(key);
  osalDbgAssert(i != -1, "Not found");

  acquire();
  ParamFile->setPosition(i * PARAM_RECORD_SIZE);

  /* ensure we found exacly what needed */
  status = ParamFile->read(tmpbuf, sizeof(tmpbuf));
  osalDbgAssert(status == sizeof(tmpbuf), "read failed");
  osalDbgAssert(strcmp((char *)tmpbuf, key) == 0, "param not found in EEPROM");

  /* write only if value differ */
  ParamFile->setPosition(ParamFile->getPosition() - PARAM_VALUE_SIZE);
  v = ParamFile->getU32();
  if (v != param_db[i].valuep->u32){
    ParamFile->setPosition(ParamFile->getPosition() - PARAM_VALUE_SIZE);
    status = ParamFile->putU32(param_db[i].valuep->u32);
    osalDbgAssert(status == sizeof(uint32_t), "read failed");
    osalThreadSleep(ADDITIONAL_WRITE_TMO);
  }

  release();
  return OSAL_SUCCESS;
}

/**
 *
 */
bool ParamRegistry::loadToRam(void) {
  int i = 0;
  int cmpresult = -1;
  size_t status = 0;
  param_union_t v;
  v.u32 = 0;

  /* check reserved space in EEPROM */
  osalDbgAssert(((PARAM_RECORD_SIZE * this->paramCount()) < ParamFile->getSize()),
          "not enough space in file");

  acquire();
  ParamFile->setPosition(0);

  for (i = 0; i < this->paramCount(); i++){

    /* read field from EEPROM and check number of red bytes */
    status = ParamFile->read(eeprombuf, PARAM_RECORD_SIZE);
    if (status < PARAM_RECORD_SIZE){
      osalSysHalt("");
      goto FAIL;
    }

    /* if no updates was previously in parameter structure than order of
     * parameters in registry must be the same as in eeprom */
    cmpresult = strcmp(param_db[i].name, (char *)eeprombuf);
    if (0 == cmpresult){   /* OK, this parameter already presents in EEPROM */
      v.u32 = pack8to32ne(&(eeprombuf[PARAM_ID_SIZE]));
    }
    else{
      /* there is not such parameter in EEPROM. Possible reasons:
       * 1) parameter "registry" has been changed.
       * 2) this is very first run with totally empty EEPROM
       * To correctly fix this situation we just need to
       * save structure to EEPROM after loading of all parameters to RAM.
       */
      if (OSAL_SUCCESS != load_extensive())
        goto FAIL;
      else
        goto SUCCESS;
    }

    /* check value acceptability and set it */
    validator.set(&v, &(param_db[i]));
  }

SUCCESS:
  ready = true;
  release();
  return OSAL_SUCCESS;

FAIL:
  ready = false;
  release();
  return OSAL_FAILED;
}

/**
 *
 */
void ParamRegistry::start(void) {
  this->open_file();
  this->loadToRam();
}

/**
 *
 */
void ParamRegistry::stop(void) {
  this->ready = false;
  nvram_fs.close(this->ParamFile);
}

/**
 *
 */
bool ParamRegistry::saveAll(void){
  bool ret;

  osalDbgCheck(true == ready);

  acquire();
  ret = this->save_all();
  release();

  return ret;
}

/**
 *
 */
ParamStatus ParamRegistry::setParam(const param_union_t *value,
                                    const GlobalParam_t *param) {
  osalDbgCheck(true == ready);
  return validator.set(value, param);
}

/**
 *
 */
int ParamRegistry::paramCount(void){
  return ONBOARD_PARAM_CNT;
}

/**
 * @brief   Retrieve parameter from registry.
 *
 * @param[in] key     if NULL than perform search by index
 * @param[in] n       search index
 * @param[out] *i     store founded index here. Set to NULL if not used
 *
 * @return    pointer to parameter structure
 * @retval    NULL - parameter not found
 */
const GlobalParam_t * ParamRegistry::getParam(const char *key, int n, int *i) {
  int index = -1;
  osalDbgCheck(true == ready);

  if (key != NULL){
    index = param_registry.key_index_search(key);
    if (-1 == index)
      return NULL;
  }
  else{
    if ((n > paramCount()) || (-1 == n))
      return NULL;
    else
      index = n;
  }

  /**/
  if (NULL != i)
    *i = index;
  return &(param_db[index]);
}
