/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "missile.h"

static const uint8_t pixData[] = {
  0x80,
  0x80,
  0x80,
};

static const TIMAGE image = {
  .width = 1, /* .header.w */
  .height = 3, /* .header.h */
  .size = sizeof(pixData),
  .pixmap = pixData,
  .name = "missile.bmp",
};

const PIMAGE Missile_GetImage(void) {
  return (PIMAGE)&image;
}
