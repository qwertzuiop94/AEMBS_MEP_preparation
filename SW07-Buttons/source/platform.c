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

void PL_Init(void) {
  //BLINKY_Init(); /* initialize blinky */
  Cycles_Init(); /* initialize cylce counter */
  McuWait_Init(); /*Init MCU Wait*/
  McuRTOS_Init();
  McuGPIO_Init();
  McuBtn_Init();
  McuDbnc_Init();
  BTN_Init();
  Debounce_Init();
  LEDS_Init();
  systemViewInit();
  Invader_Init();
}

void PL_Deinit(void) {
  /* NYI */
}
