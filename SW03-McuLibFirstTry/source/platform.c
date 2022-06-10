/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "blinky.h"
#include "cycles.h"
#include "McuWait.h"

void PL_Init(void) {
  BLINKY_Init(); /* initialize blinky */
  Cycles_Init(); /* initialize cylce counter */
  McuWait_Init(); /*Init MCU Wait*/
}

void PL_Deinit(void) {
  /* NYI */
}
