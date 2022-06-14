/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "myTasks.h"
#include "McuRTOS.h"
#include <stdint.h>
#include <stdio.h>
#include "leds.h"

static uint32_t taskParam1 = 5;
static uint32_t taskParam2 = 10;
static TaskHandle_t myTaskHndl1 = NULL;
static TaskHandle_t killmeTaskHandle = NULL;

static void killmeTask(void *pv) {
  vTaskPrioritySet(NULL, 5);
  vTaskSuspend(NULL);
  vTaskDelete(NULL);
}

static void otherTask(void *pv) {
  vTaskResume(killmeTaskHandle);
  vTaskDelete(NULL);
}

static void mainTask(void *pv) {
  uint32_t param = *(uint32_t*)pv;

  printf("mainTask param is %d\n", (int)param);
  /* testing task priorities */
  vTaskPrioritySet(NULL, uxTaskPriorityGet(NULL)+1);
  vTaskPrioritySet(NULL, uxTaskPriorityGet(NULL)-1);
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(500));
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
    LEDS_Neg(LEDS_TINY_BLUE);
#else
    LEDS_Neg(LEDS_BLUE);
#endif
  }
}

void MyTasks_Init(void) {
  BaseType_t res;

  res = xTaskCreate(mainTask, "mainTask", 600/sizeof(StackType_t), &taskParam1, tskIDLE_PRIORITY+2, &myTaskHndl1);
  if (res!=pdPASS) {
    /* error! */
    for(;;) {}
  }
  /* second task with same task code */
  res = xTaskCreate(mainTask, "myTask2", 600/sizeof(StackType_t), &taskParam2, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }
  res = xTaskCreate(killmeTask, "killmeTask2", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+3, &killmeTaskHandle);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }
  res = xTaskCreate(otherTask, "otherTask", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+3, NULL);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }
}
