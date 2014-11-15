#include "main.h"
#include "onewire2.h"
#include "pads.h"
#include "string.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define ZERO_WIDTH        60
#define ONE_WIDTH         6
#define SAMPLE_WIDTH      15
#define RECOVERY_WIDTH    10

#define MASTER_CHANNEL    2 /* this PWM channel drives bus */
#define SAMPLE_CHANNEL    3 /* this just generates interrupts when read needed */

#define READ_ROM_CMD      0x33

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

OWDriver OWD1;

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

static void ow_presece_cb(OWDriver *owp) {
  owp->slave_present = (PAL_LOW == palReadPad(GPIOB, GPIOB_TACHOMETER));
  osalSysLockFromISR();
  osalThreadResumeI(&(owp)->thread, MSG_OK);
  osalSysUnlockFromISR();
}

static void pwm_presence_cb(PWMDriver *pwmp) {
  (void)pwmp;

  ow_presece_cb(&OWD1);
}

/*
 * config for presence detection
 */
static const PWMConfig pwmcfg_presence = {
  1000000,
  960,
  NULL,
  {
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW, pwm_presence_cb}
  },
  0,
  0
};

/*
 * bit transmission callback
 */
static void ow_tx_cb(PWMDriver *pwmp, OWDriver *owp) {

  osalSysLockFromISR();

  if (8 == owp->txbit) {
    owp->txbuf++;
    owp->txbit = 0;
    owp->txbytes--;

    if (0 == owp->txbytes) {
      pwmDisableChannelI(pwmp, MASTER_CHANNEL);
      /* special value to signalize premature stop protector
         FIXME: use special driver state for it */
      owp->txbit = 9;
      osalSysUnlockFromISR();
      return;
    }
  }

  /* prevent premature timer stop */
  if (9 == owp->txbit) {
    pwm_lld_disable_periodic_notification(pwmp);
    osalThreadResumeI(&(owp)->thread, MSG_OK);
    osalSysUnlockFromISR();
    return;
  }

  if ((*owp->txbuf & (1 << owp->txbit)) > 0)
    pwmEnableChannelI(pwmp, MASTER_CHANNEL, ONE_WIDTH);
  else
    pwmEnableChannelI(pwmp, MASTER_CHANNEL, ZERO_WIDTH);

  owp->txbit++;

  osalSysUnlockFromISR();
}

static void pwmpcb_tx(PWMDriver *pwmp) {

  ow_tx_cb(pwmp, &OWD1);
}

/*
 * config for bytes transmitting
 */
static const PWMConfig pwmcfg_tx = {
  1000000,                                   /* PWM clock frequency.   */
  (ZERO_WIDTH + RECOVERY_WIDTH),             /* Initial PWM period        */
  pwmpcb_tx,
  {
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
  0
};

/**
 *
 */
static void pwm_start_rx_cb(PWMDriver *pwmp) {

  osalSysLockFromISR();

  pwmEnableChannelI(pwmp, MASTER_CHANNEL, ONE_WIDTH);
  pwmEnableChannelI(pwmp, SAMPLE_CHANNEL, SAMPLE_WIDTH);
  pwm_lld_disable_periodic_notification(pwmp);
  pwm_lld_enable_channel_notification(pwmp, SAMPLE_CHANNEL);

  osalSysUnlockFromISR();
}

/**
 *
 */
static void ow_read_bit_cb(PWMDriver *pwmp, OWDriver *owp) {

  osalSysLockFromISR();

  *owp->rxbuf |= palReadPad(GPIOB, GPIOB_TACHOMETER) << owp->rxbit;
  owp->rxbit++;
  if (8 == owp->rxbit) {
    owp->rxbit = 0;
    owp->rxbuf++;
    owp->rxbytes--;
    if (0 == owp->rxbytes) {
      pwmDisableChannelI(pwmp, MASTER_CHANNEL);
      pwmDisableChannelI(pwmp, SAMPLE_CHANNEL);
      pwm_lld_disable_channel_notification(pwmp, SAMPLE_CHANNEL);
      osalThreadResumeI(&(owp)->thread, MSG_OK);
    }
  }

  osalSysUnlockFromISR();
}

/**
 *
 */
static void pwm_read_bit_cb(PWMDriver *pwmp) {

  ow_read_bit_cb(pwmp, &OWD1);
}

/*
 * config for data receiving
 */
static const PWMConfig pwmcfg_rx = {
  1000000,                                    /* PWM clock frequency.   */
  (ZERO_WIDTH + RECOVERY_WIDTH),              /* Initial PWM period        */
  pwm_start_rx_cb,
  {
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW, pwm_read_bit_cb}
  },
  0,
  0
};

/*
 *
 */
static const OWConfig ow_cfg = {
  &PWMD4
};

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


void onewireObjectInit(OWDriver *owp) {
  owp->config = NULL;
  owp->slave_present = false;
  owp->state = OW_STOP;
  owp->thread = NULL;

  owp->txbytes = 0;
  owp->txbit = 0;
  owp->txbuf = NULL;

  owp->rxbytes = 0;
  owp->rxbit = 0;
  owp->rxbuf = NULL;
}

void onewireStart(OWDriver *owp, const OWConfig *config) {
  owp->config = config;
  owp->state = OW_READY;
}

/**
 *
 */
bool onewireReset(OWDriver *owp) {

  pwmStart(&PWMD4, &pwmcfg_presence);
  pwmEnableChannel(&PWMD4, MASTER_CHANNEL, 480);
  pwmEnableChannel(&PWMD4, SAMPLE_CHANNEL, 550);
  pwmEnableChannelNotification(&PWMD4, SAMPLE_CHANNEL);

  osalSysLock();
  osalThreadSuspendS(&owp->thread);
  osalSysUnlock();

  pwmStop(&PWMD4);

  return owp->slave_present;
}

/**
 *
 */
void onewireWriteData(OWDriver *owp, uint8_t *txbuf, size_t txbytes) {

  owp->txbuf = txbuf;
  owp->txbit = 0;
  owp->txbytes = txbytes;

  pwmStart(&PWMD4, &pwmcfg_tx);
  pwmEnablePeriodicNotification(&PWMD4);

  osalSysLock();
  osalThreadSuspendS(&owp->thread);
  osalSysUnlock();

  pwmStop(&PWMD4);
}

/**
 *
 */
void onewireReadData(OWDriver *owp, uint8_t *rxbuf, size_t rxbytes) {

  /* Buffer zeroing this is important because of driver collects
     bits using |= operation.*/
  memset(rxbuf, 0, rxbytes);

  owp->rxbit = 0;
  owp->rxbuf = rxbuf;
  owp->rxbytes = rxbytes;

  pwmStart(&PWMD4, &pwmcfg_rx);
  pwmEnablePeriodicNotification(&PWMD4);

  osalSysLock();
  osalThreadSuspendS(&owp->thread);
  osalSysUnlock();

  pwmStop(&PWMD4);
}

/**
 *
 */
static uint8_t id_buf[8];
static uint8_t txbuf[8];
void onewireTest(void) {

  onewireObjectInit(&OWD1);
  onewireStart(&OWD1, &ow_cfg);

  while (true) {
    if (true == onewireReset(&OWD1)){
      red_led_on();
      txbuf[0] = READ_ROM_CMD;
      onewireWriteData(&OWD1, txbuf, 1);
      onewireReadData(&OWD1, id_buf, 8);
    }
    else {
      red_led_off();
    }

    osalThreadSleepMilliseconds(1);
  }
}
