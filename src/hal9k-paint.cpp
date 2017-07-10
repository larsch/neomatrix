/**
 * Copyright (C) 2017 Lars Christensen
 */

#include "counter.hpp"
#include "hal9k-paint.hpp"
#include "coord.hpp"
#include "display.hpp"
#include "hsv2rgb.hpp"

static Counter<4096, 4096> c;

Hal9kPaint::Hal9kPaint()
{
  last = { 0, 0, 0 };
  current = hsv2rgb(cp, 128, 128);
  lv = c();
  cp = 0;
}

Hal9kPaint::~Hal9kPaint()
{
}

void Hal9kPaint::run()
{
  uint32_t now = c();
  int ph = now / 1024;
  int w = 2000;
  int h = 600;
  int t = now % 1024;
  int x = t * w / 1024;
  int y = t * h / 1024;
  if (t < lv) {
    last = current;
    cp = (cp + 123) % 360;
    current = hsv2rgb(cp, 255, 255);
  }
  lv = t;
  switch (ph) {
  case 0:
    for (int pix = 0; pix < COUNT; ++pix)
      pixels[pix] = coord[pix][0] < x ? current : last;
    break;
  case 1:
    for (int pix = 0; pix < COUNT; ++pix)
      pixels[pix] = coord[pix][1] < y ? current : last;
    break;
  case 2:
    for (int pix = 0; pix < COUNT; ++pix)
      pixels[pix] = coord[pix][0] < (w - x) ? last : current;
    break;
  case 3:
    for (int pix = 0; pix < COUNT; ++pix)
      pixels[pix] = coord[pix][1] < (h - y) ? last : current;
    break;
  }
}

REGISTER_PROGRAM(Hal9kPaint);
