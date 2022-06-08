/*
 * blinky.c
 *
 *  Created on: 17.02.2022
 *      Author: Manuel
 */

#include "blinky.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/* LED_BLUE: PTC2 */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_BLUE_GPIO_PIN_MASK (1U << 2U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_LED_BLUE_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_BLUE_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_BLUE_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */

static void delay(void) {
	uint32_t i;

	for(i=0;i<1000000;i++) {
		__asm volatile ("nop");
	}
}
static void InitLed(void) {
   CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC2 (pin 45)  */
    GPIO_PinInit(BOARD_INITPINS_LED_BLUE_GPIO, BOARD_INITPINS_LED_BLUE_PIN, &LED_BLUE_config);

    /* PORTC2 (pin 45) is configured as PTC2 */
    PORT_SetPinMux(BOARD_INITPINS_LED_BLUE_PORT, BOARD_INITPINS_LED_BLUE_PIN, kPORT_MuxAsGpio);
}

void BLINKY_Run(void) {
	InitLed();
	for(;;) {
		GPIO_PortToggle(BOARD_INITPINS_LED_BLUE_GPIO, BOARD_INITPINS_LED_BLUE_GPIO_PIN_MASK);
		delay();
	}
}



