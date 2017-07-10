/**
 * Copyright (C) 2017 Lars Christensen
 */

#include "counter.hpp"
#include "hal9k-letter.hpp"
#include "coord.hpp"
#include "display.hpp"

static Counter<1000, 10000> c;

LetterWipe::LetterWipe()
{
  start = c();
}

LetterWipe::~LetterWipe()
{
}


void LetterWipe::run()
{
  uint32_t now = c() - start;
  int letter = now / 500;
  int yphase = now % 500;
  int ymax = 360;
  int ymin = 120;
  int yp = ymin + ((ymax - ymin) * yphase) / 500;
  for (int l = 0; l < 5; ++l) {
    for (int pix = offset[l]; pix < offset[l] + count[l]; ++pix) {
      int y = coord[pix][1];
      if (l < 3 && (l < letter || (l == letter && y < yp)))
        pixels[pix] = { 255, 255, 255 };
      else if (l < 5 && (l < letter || (l == letter && y < yp)))
        pixels[pix] = { 0, 255, 0 };
      else
        pixels[pix] = { 0, 0, 0 };
    }
    for (int l = 5; l < LETTERS; ++l) {
      int xmin = 76;
      int xmax = 1870;
      int xp = xmin + ((xmax - xmin) * yphase) / 500;
      for (int pix = offset[l]; pix < offset[l] + count[l]; ++pix) {
        int x = coord[pix][0];
        if ((letter >= 8) || (letter == 7 && x < xp))
          pixels[pix] = { 255, 255, 0 };
        else
          pixels[pix] = { 0, 0, 0 };
      }
    }
  }
}

REGISTER_PROGRAM(LetterWipe);
