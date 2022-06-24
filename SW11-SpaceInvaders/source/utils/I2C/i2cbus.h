/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2CBUS_H_
#define I2CBUS_H_

void I2CBus_LockBus(void);
void I2CBus_ReleaseBus(void);

void I2CBus_Deinit(void);
void I2CBus_Init(void);

#endif /* I2CBUS_H_ */
