/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * The Matrix
 */

#include "common.hpp"
#include "matrix.hpp"
#include "display.hpp"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static uint16_t random_speed()
{
  return 32 + (uint64_t(64) * rand()) / RAND_MAX;
}

TheMatrix::TheMatrix()
  : limiter(50)
{
#define WHITESTART 224

  for (int i = 0; i < WHITESTART; ++i ) {
    palette[i].r = 0;
    palette[i].g = (i * 256) / WHITESTART;
    palette[i].b = 0;
  }
  for (int i = WHITESTART; i < 256; ++i) {
    palette[i].r = ((i - WHITESTART) * 256) / (256 - WHITESTART);
    palette[i].g = 255;
    palette[i].b = ((i - WHITESTART) * 256) / (256 - WHITESTART);
  }
  for (int i = 0; i < 24; ++i) {
    pos[i] = (24llu * 256 * rand()) / RAND_MAX;
    speed[i] = random_speed();
  }
}

TheMatrix::~TheMatrix()
{
}

void TheMatrix::run()
{
  if (limiter.skip()) {
    return;
  }

  for (int i = 0; i < 24 * 24; ++i) {
    if (frame[i] > 4) {
      frame[i] -= 4;
    } else {
      frame[i] = 0;
    }
  }

  // memset(frame, 0, 24 * 24);

  for (int i = 0; i < 24; ++i) {
    pos[i] += speed[i];
    if (pos[i] >= 24 * 256) {
      pos[i] = 0;
      speed[i] = random_speed();
    }
    frame[i + ((pos[i]) / 256) * 24] = 255;
  }

  for (int i = 0; i < 24 * 24; ++i) {
    pixels[i] = palette[frame[i]];
  }
}

REGISTER_PROGRAM(TheMatrix);
