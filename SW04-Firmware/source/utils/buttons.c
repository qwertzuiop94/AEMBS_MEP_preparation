/*
 * buttons.c
 *
 *  Created on: 11.06.2022
 *      Author: manuel
 */

#ifndef UTILS_BUTTONS_C_
#define UTILS_BUTTONS_C_

#include "buttons.h"
#include "McuGPIO.h"
#include "fsl_clock.h"
#include "platform.h"
#include <stdbool.h>

static McuGPIO_Handle_t myPin;

bool ButtonState(void){
	return McuGPIO_IsLow(myPin);
}

void Button_Init(void){

	CLOCK_EnableClock(kCLOCK_PortB);
	McuGPIO_Config_t config;
	McuGPIO_GetDefaultConfig(&config);

#if PL_CONFIG_IS_TINY
	config.hw.gpio = GPIOB;
	config.hw.port = PORTB;
	config.hw.pin = 16;
	config.isHighOnInit = true;
	config.isInput = true;
#elif PL_CONFIG_IS_LPC
	config.hw.gpio = GPIO;
	config.hw.port = 0;
	config.hw.pin = 4;
	config.hw.iocon = IOCON_INDEX_PIO0_4;
	config.isHighOnInit = true;
	config.isInput = true;
#endif

	myPin = McuGPIO_InitGPIO(&config);
	if (myPin==NULL) {
	  for(;;) { /* error */ }
	}



}
void Button_DeInit(void){

}

#endif /* UTILS_BUTTONS_C_ */
