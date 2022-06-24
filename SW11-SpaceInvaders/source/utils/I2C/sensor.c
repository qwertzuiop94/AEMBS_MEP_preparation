/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "sensor.h"
#include "McuRTOS.h"
#include "i2cbus.h"
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7
  #include "McuSHT40.h"
#else
  #include "McuSHT31.h"
#endif

static float Sensor_temperature, Sensor_humidity;

float Sensor_GetTemperature(void) {
  return Sensor_temperature; /* technically no mutex required, as 32bit access in one instruction */
}

float Sensor_GetHumidity(void) {
  return Sensor_humidity; /* technically no mutex required, as 32bit access in one instruction */
}

static void sensorTask(void *pv) {
  float t, h;
  uint8_t res;

  for(;;) {
    I2CBus_LockBus();
  #if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7
    res = McuSHT40_ReadTempHum(&t, &h);
  #else
    res = McuSHT31_ReadTempHum(&t, &h);
  #endif
    I2CBus_ReleaseBus();
    if (res==ERR_OK) {
      Sensor_temperature = t; /* technically no mutex required, as 32bit access in one instruction */
      Sensor_humidity = h; /* technically no mutex required, as 32bit access in one instruction */
    } else {
      for(;;) {} /* error */
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void Sensor_Deinit(void) {

}

void Sensor_Init(void) {
  BaseType_t res;

  res = xTaskCreate(sensorTask, "sensor", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    /* error! */
    for(;;) {}
  }
}
