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

void PL_Init(void) {
  BLINKY_Init(); /* initialize blinky */
  Cycles_Init(); /* initialize cylce counter */
  McuWait_Init(); /*Init MCU Wait*/
  McuRTOS_Init();
  Button_Init();
  LEDS_Init();
  systemViewInit();
}

void PL_Deinit(void) {
  /* NYI */
}
