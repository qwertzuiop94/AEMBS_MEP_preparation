/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef SENSOR_H_
#define SENSOR_H_

float Sensor_GetTemperature(void);
float Sensor_GetHumidity(void);

void Sensor_Deinit(void);
void Sensor_Init(void);

#endif /* SENSOR_H_ */
