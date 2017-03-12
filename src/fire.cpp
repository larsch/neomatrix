#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pixel.hpp"
#include "program.hpp"
#include "framelimiter.hpp"

static FrameLimiter limiter(50);
static uint8_t* palette;
static uint8_t* fire;

#define PAL(i, c) palette[((i)*3)+(c)]

extern pixel* pixels;

void fire_init()
{
  if (palette == nullptr) {
    palette = (uint8_t*)malloc(256 * 3);
  }
  memset(palette, 0, 256 * 3);
  for (int i = 0; i < 32; ++i) {
    PAL(i, 2) = i << 1;
    PAL(i + 32, 1) = i << 3;
    PAL(i + 32, 2) = 64 - (i << 1);
    PAL(i + 64, 1) = 255;
    PAL(i + 64, 0) = i << 3;
    PAL(i + 96, 1) = 255;
    PAL(i + 96, 0) = 255;
    PAL(i + 96, 2) = (i << 1);
    PAL(i + 128, 1) = 255;
    PAL(i + 128, 0) = 255;
    PAL(i + 128, 2) = 64 + (i << 1);
    PAL(i + 160, 1) = 255;
    PAL(i + 160, 0) = 255;
    PAL(i + 160, 2) = 128 + (i << 1);
    PAL(i + 192, 1) = 255;
    PAL(i + 192, 0) = 255;
    PAL(i + 192, 2) = 192 + i;
    PAL(i + 224, 1) = 255;
    PAL(i + 224, 0) = 255;
    PAL(i + 224, 2) = 224 + i;
  }

  if (fire == nullptr) {
    fire = (uint8_t*)malloc(24 * 26);
  }
  memset(fire, 0, 24 * 26);

  memset(pixels, 0, 24 * 24 * 3);
}

void fire_destroy()
{
  free(palette);
  palette = nullptr;
  free(fire);
  fire = nullptr;
}

void fire_update()
{
  if (limiter.skip()) {
    return;
  }
  for (int x = 0; x < 24; ++x) {
    fire[25 * 24 + x] = rand() < (RAND_MAX / 3) ? 255 : 0;
  }

  uint8_t* row = &fire[25 * 24];
  for (int i = 0; i < 25; ++i) {
    for (int x = 0; x < 24; ++x) {
      int temp = 0;
      temp += 4 * row[x]; // below
      temp += 2 * (x < 23 ? row[x + 1] : 0); // right
      temp += 2 * (x > 0 ? row[x - 1] : 0); // left
      temp += 8 * (i < 24 ? row[x - 24] : 0);
      temp /= 16;
      if (temp > 1) {
        temp -= 1;
      }
      row[x - 24] = temp;
    }
    row -= 24;
  }

  for (int y = 0; y < 24; ++y)
    for (int x = 0; x < 24; ++x) {
      memcpy(&pixels[y * 24 + x], &PAL(fire[y * 24 + x], 0), 3);
    }
}

class Fire : public Program
{
public:
  Fire()
  {
    fire_init();
  }
  ~Fire()
  {
    fire_destroy();
  }
  virtual void run()
  {
    fire_update();
  }
};

REGISTER_PROGRAM(Fire);
