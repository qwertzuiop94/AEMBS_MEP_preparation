/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "i2cbus.h"
#include "McuRTOS.h"

static SemaphoreHandle_t mutex = NULL; /* Mutex to protect access to bus */

void I2CBus_LockBus(void) {
  if (xSemaphoreTakeRecursive(mutex, pdMS_TO_TICKS(1000))!=pdTRUE) {
    for(;;) { /* error? */ }
  }
}

void I2CBus_ReleaseBus(void) {
  if (xSemaphoreGiveRecursive(mutex)!=pdTRUE) {
    for(;;) { /* error? */ }
  }
}

void I2CBus_Deinit(void) {
  vSemaphoreDelete(mutex);
  mutex = NULL;
}

void I2CBus_Init(void) {
 // mutex = xSemaphoreCreateMutex();
  mutex = xSemaphoreCreateRecursiveMutex();
  if (mutex==NULL) {
    for(;;) { /* error */ }
  }
  vQueueAddToRegistry(mutex, "I2C Mutex");
}

