/*
 * tempSensor.c
 *
 *  Created on: 19.06.2022
 *      Author: manuel
 */

#ifndef UTILS_I2C_TEMPSENSOR_C_
#define UTILS_I2C_TEMPSENSOR_C_

#include "float.h"
#include "McuSHT31.h"
#include "McuRTOS.h"

static float t;
static float h;

static TaskHandle_t taskHndl;



static void readSensor(void){
	McuSHT31_ReadTempHum(&t, &h);
}

static void SensorTask(void *pv) {
	(void)pv;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		readSensor();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
	}

}


float getTemperauture(void){
	return t;
}
float getHumidity(void){
	return h;
}

void TempSensorInit(void){
	BaseType_t res;

	McuSHT31_Init();

	res = xTaskCreate(
				SensorTask, /* pointer to the task */
				"SensorTask", /* task name for kernel awareness debugging */
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
void TempSensorDeInit(void){

}


#endif /* UTILS_I2C_TEMPSENSOR_C_ */
