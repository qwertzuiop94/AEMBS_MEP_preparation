/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "alien.h" /* include of own header file */

/* the bitmap data, copy from generated file */
static const uint8_t pixData[] = {
  /* put bitmap data here */
		0x00, 0x00,
  0x21, 0x00,
  0x12, 0x00,
  0x1e, 0x00,
  0x12, 0x00,
  0x12, 0x00,
  0x3f, 0x00,
  0x1e, 0x00,
  0x0c, 0x00,
  0x00, 0x00,
};

static const TIMAGE image = {
  .width = 10, /* number from converted file: .header.w */
  .height = 10, /* number from converted file: .header.h */
  .size = sizeof(pixData), /* size of bitmap data */
  .pixmap = pixData, /* pointer to bitmap data above */
  .name = "alien.bmp", /* optional name of file */
};

const PIMAGE alien_GetImage(void) {
  return (PIMAGE)&image;
}

