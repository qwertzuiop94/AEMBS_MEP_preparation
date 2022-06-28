/*
 * lpc.c
 *
 *  Created on: 27.06.2022
 *      Author: manuel
 */

#ifndef LPC_C_
#define LPC_C_

#include "lpc.h"
#include "McuRTOS.h"
#include "leds.h"



static TaskHandle_t taskHndl;
static LEDS_Leds_e testLed1 = LEDS_BLUE;
static LEDS_Leds_e testLed2 = LEDS_GREEN;
static SemaphoreHandle_t xsemaphore;

static void taaskA(void *pv) {
	(void)pv;
	static uint16_t i = 0;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
        LEDS_On(testLed1);
        vTaskDelay(pdMS_TO_TICKS(100));
        LEDS_Off(testLed1);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
        i++;
        if(i>=5){
        	//semaphore aktiviere!
        	xSemaphoreGive(xsemaphore);
        	i = 0;
        }
	}

}

static void taskB(void *pv) {
	(void)pv;
	for(;;){
		xSemaphoreTake(xsemaphore,portMAX_DELAY);
		LEDS_On(testLed2);
		vTaskDelay(pdMS_TO_TICKS(50));
		LEDS_Off(testLed2);
	}

}


/*! \brief Module initialization */
void LPC_Deinit(void){

}

/*! \brief Module deinitialization */
void LPC_Init(void){
	BaseType_t res;

	res = xTaskCreate(
			taaskA, /* pointer to the task */
			"taaskA", /* task name for kernel awareness debugging */
			600 / sizeof(StackType_t), /* task stack size */
			(void*) NULL, /* optional task startup argument */
			tskIDLE_PRIORITY + 2, /* initial priority */
			&taskHndl /* optional task handle to create */
	);

	if (res != pdPASS) {
		for (;;) {
		} /* error! probably out of memory */
	}

	// semaphore shit
	xsemaphore = xSemaphoreCreateBinary();
	vQueueAddToRegistry(xsemaphore, "LED_Semaphore");
	if(xsemaphore == NULL){
		for(;;){
			//error!
		}

	}
	res = xTaskCreate(
			taskB, /* pointer to the task */
			"taskB", /* task name for kernel awareness debugging */
			600 / sizeof(StackType_t), /* task stack size */
			(void*) NULL, /* optional task startup argument */
			tskIDLE_PRIORITY + 2, /* initial priority */
			&taskHndl /* optional task handle to create */
	);

	if (res != pdPASS) {
		for (;;) {
		} /* error! probably out of memory */
	}




}

#endif /* LPC_C_ */

