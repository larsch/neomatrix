/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * HSV-to-RGB conversion
 */

#include "hsv2rgb.hpp"

pixel hsv2rgb(int h, uint8_t s, uint8_t v)
{
  if (s == 0)
    return pixel{v, v, v};

  int hh = (h % 60);

  uint8_t p = (v * (255 - s)) / 256;
  uint8_t q = (v * (15300 - (s * hh))) / (256 * 60);
  uint8_t t = (v * (15300 - (s * (59 - hh)))) / (256 * 60);

  switch (h / 60) {
  case 0:
    return pixel{t, v, p};
  case 1:
    return pixel{v, q, p};
  case 2:
    return pixel{v, p, t};
  case 3:
    return pixel{q, p, v};
  case 4:
    return pixel{p, t, v};
  default:
    return pixel{p, v, q};
  }
}
