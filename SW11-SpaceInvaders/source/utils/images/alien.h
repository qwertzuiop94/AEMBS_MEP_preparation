/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef IMAGES_ALIEN_H_
#define IMAGES_ALIEN_H_

#include "McuGDisplaySSD1306.h"

/*!
 * \brief Return the image
 * \return Pointer to the (const) image data
 */
const PIMAGE alien_GetImage(void);


#endif /* IMAGES_ALIEN_H */
