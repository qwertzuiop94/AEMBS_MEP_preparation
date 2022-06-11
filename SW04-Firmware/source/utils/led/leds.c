/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "leds_config.h"
#include "leds.h"
#include "McuLED.h"

#if LEDS_CONFIG_HAS_RED_LED
  static McuLED_Handle_t ledRed;
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  static McuLED_Handle_t ledGreen;
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  static McuLED_Handle_t ledBlue;
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  static McuLED_Handle_t ledOrange;
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  static McuLED_Handle_t ledTiny;
#endif

void LEDS_On(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_On(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_On(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_On(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_On(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_On(ledTiny); break;
  #endif
    default:
      break; /* error */
  }
}

void LEDS_Off(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Off(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Off(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Off(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_Off(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_Off(ledTiny); break;
  #endif
    default:
      break; /* error */
  }
}

void LEDS_Neg(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Toggle(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Toggle(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Toggle(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_Toggle(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_Toggle(ledTiny); break;
  #endif
    default:
      break; /* error */
  }
}

void LEDS_Init(void) {
  LEDS_CONFIG_ENABLE_CLOCK();
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;

#if LEDS_CONFIG_HAS_RED_LED
  config.hw.gpio = LEDS_CONFIG_RED_GPIO;
  config.hw.port = LEDS_CONFIG_RED_PORT;
  config.hw.pin = LEDS_CONFIG_RED_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_RED_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_RED_LOW_ACTIVE;
  ledRed = McuLED_InitLed(&config);
  if (ledRed==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  config.isLowActive = true;
  config.hw.gpio = LEDS_CONFIG_GREEN_GPIO;
  config.hw.port = LEDS_CONFIG_GREEN_PORT;
  config.hw.pin = LEDS_CONFIG_GREEN_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_GREEN_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_GREEN_LOW_ACTIVE;
  ledGreen = McuLED_InitLed(&config);
  if (ledGreen==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  config.isLowActive = true;
  config.hw.gpio = LEDS_CONFIG_BLUE_GPIO;
  config.hw.port = LEDS_CONFIG_BLUE_PORT;
  config.hw.pin = LEDS_CONFIG_BLUE_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_BLUE_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_BLUE_LOW_ACTIVE;
  ledBlue = McuLED_InitLed(&config);
  if (ledBlue==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_ORANGE_LED
  config.isLowActive = false;
  config.hw.gpio = LEDS_CONFIG_ORANGE_GPIO;
  config.hw.port = LEDS_CONFIG_ORANGE_PORT;
  config.hw.pin = LEDS_CONFIG_ORANGE_PIN;
  ledOrange = McuLED_InitLed(&config);
  config.isLowActive = LEDS_CONFIG_ORANGE_LOW_ACTIVE;
  if (ledOrange==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  config.isLowActive = true;
  config.hw.gpio = LEDS_CONFIG_BLUE_TINY_GPIO;
  config.hw.port = LEDS_CONFIG_BLUE_TINY_PORT;
  config.hw.pin = LEDS_CONFIG_BLUE_TINY_PIN;
  config.isLowActive = LEDS_CONFIG_BLUE_TINY_LOW_ACTIVE;
  ledTiny = McuLED_InitLed(&config);
  if (ledTiny==NULL) {
    for(;;) {}
  }
#endif
}

void LED_Deinit(void) {
#if LEDS_CONFIG_HAS_RED_LED
  ledRed = McuLED_DeinitLed(ledRed);
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  ledGreen = McuLED_DeinitLed(ledGreen);
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  ledBlue = McuLED_DeinitLed(ledBlue);
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  ledOrange = McuLED_DeinitLed(ledOrange);
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  ledTiny = McuLED_DeinitLed(ledTiny);
#endif
}
