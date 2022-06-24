/*
 * systemView.c
 *
 *  Created on: 14.06.2022
 *      Author: manuel
 */

#ifndef SYSTEMVIEW_C_
#define SYSTEMVIEW_C_

#include "systemView.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuRTOS.h"

#define TEST_TASK_FOR_LOGGIN
#define ID 100

static void systemViewerTest(void *pv) {
	(void)pv;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	McuSystemView_Print((const char*)"Print\r\n");
	McuSystemView_Warn((const char*)"Warnung\r\n");
	McuSystemView_Error((const char*)"Error\r\n");
	for(;;){
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_OnUserStart(ID);
		McuSystemView_Print((const char*)"PrintTest 200mS\r\n");
#endif

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(200));
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
        McuSystemView_OnUserStop(ID);
#endif
	}

}



void systemViewInit(void) {
	/*SystemView Init */
	McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_Init();
#endif
#if defined TEST_TASK_FOR_LOGGIN
	BaseType_t res;
	TaskHandle_t taskHndl;
	res = xTaskCreate(systemViewerTest, /* pointer to the task */
	"TestSystemViewer", /* task name for kernel awareness debugging */
	600 / sizeof(StackType_t), /* task stack size */
	(void*) NULL, /* optional task startup argument */
	tskIDLE_PRIORITY + 2, /* initial priority */
	&taskHndl /* optional task handle to create */
	);

	if (res != pdPASS) {
		for (;;) {
		} /* error! probably out of memory */
	}
#endif

}
void systemViewDeInit(void) {

}

#endif /* SYSTEMVIEW_C_ */
