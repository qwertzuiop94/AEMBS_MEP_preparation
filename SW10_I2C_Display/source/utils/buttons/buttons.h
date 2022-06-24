/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "buttons_config.h"

/*!
 * \brief Decides if a button is pressed
 * \param btn Button to check
 * \return true if button is pressed
 */
bool BTN_IsPressed(BTN_Buttons_e btn);

/*!
 * \brief Read directly the button status from the pins (polling)
 * \return Bitset of buttons pressed, e.g. BTN_BIT_NAV_UP, see buttons_config.h
 */
uint32_t BTN_GetButtons(void);

/*!
 * \brief Module de-initialization
 */
void BTN_Deinit(void);

/*!
 * \brief Module initialization
 */
void BTN_Init(void);

#endif /* BUTTONS_H_ */
