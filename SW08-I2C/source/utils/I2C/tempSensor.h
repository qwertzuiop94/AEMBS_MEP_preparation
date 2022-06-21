/*
 * tempSensor.h
 *
 *  Created on: 19.06.2022
 *      Author: manuel
 */

#ifndef UTILS_I2C_TEMPSENSOR_H_
#define UTILS_I2C_TEMPSENSOR_H_

#include "float.h"

float getTemperauture(void);
float getHumidity(void);

void TempSensorInit(void);
void TempSensorDeInit(void);



#endif /* UTILS_I2C_TEMPSENSOR_H_ */
