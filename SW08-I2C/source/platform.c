/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "blinky.h"
#include "cycles.h"
#include "McuWait.h"
#include "buttons.h"
#include "leds.h"
#include "firstTask.h"
#include "McuRTOS.h"
#include "systemView.h"
#include "buttons.h"
#include "debounce.h"
#include "McuGPIO.h"
#include "McuButton.h"
#include "McuDebounce.h"
#include "invader.h"
#include "tempSensor.h"
#include "McuGenericI2C.h"
#include "McuI2cLib.h"

void PL_Init(void) {
  //BLINKY_Init(); /* initialize blinky */
  Cycles_Init(); /* initialize cylce counter */
  McuWait_Init(); /*Init MCU Wait*/
  McuRTOS_Init();
  McuGPIO_Init();
  McuGenericI2C_Init();
  CLOCK_EnableClock(kCLOCK_PortB);
  McuI2cLib_Init();
  McuBtn_Init();
  McuDbnc_Init();
  BTN_Init();
  Debounce_Init();
  LEDS_Init();
  systemViewInit();
  TempSensorInit();
  Invader_Init();

}

void PL_Deinit(void) {
  /* NYI */
}
