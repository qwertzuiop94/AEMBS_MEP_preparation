/*
 * firstTask.c
 *
 *  Created on: 14.06.2022
 *      Author: manuel
 */

#ifndef FIRSTTASK_C_
#define FIRSTTASK_C_

#include "firstTask.h"
#include "McuRTOS.h"
#include "leds.h"

TaskHandle_t taskHndl;

static void myFirstTask(void *pv) {

}

void FirstTaskInit(void) {
	BaseType_t res;

	xTaskCreate(
			myFirstTask, /* pointer to the task */
			"FirstBlinkyTask", /* task name for kernel awareness debugging */
			600 / sizeof(StackType_t), /* task stack size */
			(void*) NULL, /* optional task startup argument */
			tskIDLE_PRIORITY + 2, /* initial priority */
			&taskHndl
	); /* optional task handle to create */

	if (res != pdPASS) {
		for (;;) {
		} /* error! probably out of memory */
	}

}
void FirstTaskDeInit(void) {

}

#endif /* FIRSTTASK_C_ */
