/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "ship.h" /* include of own header file */

/* the bitmap data, copy from generated file */
static const uint8_t pixData[] = {
  /* put bitmap data here */
  0x00, 0x00,
  0x00, 0x00,
  0x08, 0x00,
  0x1c, 0x00,
  0x14, 0x00,
  0x1c, 0x00,
  0x5d, 0x00,
  0xff, 0x80,
  0xfd, 0x80,
  0xdd, 0x80,
  0x00, 0x00,
};

static const TIMAGE image = {
  .width = 10, /* number from converted file: .header.w */
  .height = 10, /* number from converted file: .header.h */
  .size = sizeof(pixData), /* size of bitmap data */
  .pixmap = pixData, /* pointer to bitmap data above */
  .name = "ship.bmp", /* optional name of file */
};

const PIMAGE ship_GetImage(void) {
  return (PIMAGE)&image;
}

