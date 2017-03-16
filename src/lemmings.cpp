/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Lemmings Animation
 */

#include "lemmings.hpp"
#include "display.hpp"
#include "pixel.hpp"
#include "counter.hpp"
#include <string.h>

#define INTERVAL 16
#define FRAMES 8

static Counter<10, FRAMES * INTERVAL> c;

static const pixel palette[] = {
  { 0, 0, 0 },
  { 255, 0, 0 },
  { 235, 255, 223 },
  { 0, 0, 255 }
};

static const uint8_t frames[][15] = {
  { 0, 1, 84, 22, 0, 168, 11, 0, 176, 11, 0, 240, 47, 0, 160 },
  { 4, 65, 80, 22, 0, 168, 11, 2, 240, 47, 32, 242, 60, 130, 128 },
  { 0, 1, 16, 21, 0, 96, 10, 130, 176, 47, 10, 252, 63, 202, 10 },
  { 0, 0, 80, 22, 65, 168, 11, 0, 176, 47, 0, 240, 191, 200, 40 },
  { 0, 1, 84, 22, 1, 168, 11, 0, 224, 11, 0, 240, 47, 0, 160 },
  { 4, 65, 80, 22, 0, 168, 11, 0, 224, 14, 32, 242, 60, 130, 128 },
  { 0, 1, 16, 21, 0, 96, 10, 128, 224, 14, 0, 248, 63, 202, 10 },
  { 0, 0, 80, 22, 65, 168, 11, 0, 176, 14, 0, 240, 191, 200, 40 }
};

Lemmings::Lemmings()
{
}

void Lemmings::run()
{
  memset(pixels, 0, 576 * 3);
  int step = c();
  const uint8_t* frame = frames[step % FRAMES];
  pixel* p = &pixels[7 * 24];
  for (int y = 0; y < 10; ++y) {
    for (int x = 0; x < 24; ++x) {
      int w = (x + INTERVAL * FRAMES - step) % INTERVAL;
      if (w < 6) {
        int bit = (y * 6 + w) * 2;
        int byte = bit / 8;
        int v = ((frame[byte]) >> (6 - bit % 8)) & 0x03;
        *p++ = palette[v];
      } else {
        *p++ = pixel{0, 0, 0};
      }
    }
  }
}

REGISTER_PROGRAM(Lemmings);
