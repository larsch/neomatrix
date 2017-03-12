#include "common.hpp"
#include "metaballs.hpp"
#include "display.hpp"
#include "counter.hpp"
#include "program.hpp"
#include <cmath>
#include "display.hpp"
#include "hsv2rgb.hpp"

Metaballs::Metaballs()
{
  for (int i = 0; i < 255; ++i) {
    gm1[i] = 255.0 * pow(i / 255.0, 2.2);
    gm2[i] = 255.0 * pow(i / 255.0, 1.0 / 2.2);
  }
  int hue = (uint64_t(360) * rand()) / RAND_MAX;
  c2 = hsv2rgb(hue, 255, 128);
  c1 = hsv2rgb((hue + 32) % 360, 128, 128 + 64);
}

Metaballs::~Metaballs()
{
}

int32_t walk(int32_t w)
{
  int32_t x = w - 24 * 256;
  return x < 0 ? -x : x;
}

pixel Metaballs::interp(int lvl, int max, pixel c1, pixel c2)
{
  uint8_t f1 = (lvl * 255) / max;
  uint8_t f2 = 255 - f1;
  uint8_t r1 = c1.r;
  uint8_t r2 = c2.r;
  uint8_t g1 = c1.g;
  uint8_t g2 = c2.g;
  uint8_t b1 = c1.b;
  uint8_t b2 = c2.b;
  uint8_t r = gm2[(gm1[r1] * f2 + gm1[r2] * f1) / 256];
  uint8_t g = gm2[(gm1[g1] * f2 + gm1[g2] * f1) / 256];
  uint8_t b = gm2[(gm1[b1] * f2 + gm1[b2] * f1) / 256];
  return pixel{g, r, b};
}

void Metaballs::run()
{
  static Counter<4 * 256, 48 * 256> c1x;
  static Counter<3 * 256, 48 * 256> c1y;
  static Counter<5 * 256, 48 * 256> c2x;
  static Counter<6 * 256, 48 * 256> c2y;
  static Counter<9 * 256, 48 * 256> c3x;
  static Counter<8 * 256, 48 * 256> c3y;

  pixel* p = pixels;
  for (uint16_t y = 0; y < 24 * 256; y += 256) {
    for (uint16_t x = 0; x < 24 * 256; x += 256) {
      int32_t dx1 = walk(c1x()) - x;
      int32_t dy1 = walk(c1y()) - y;
      uint32_t d1 = (dx1 * dx1 + dy1 * dy1) / 256 + 1;
      uint32_t f1 = 16777216 / d1;

      int32_t dx2 = walk(c2x()) - x;
      int32_t dy2 = walk(c2y()) - y;
      uint32_t d2 = (dx2 * dx2 + dy2 * dy2) / 256 + 1;
      uint32_t f2 = 16777216 / d2;

      int32_t dx3 = walk(c3x()) - x;
      int32_t dy3 = walk(c3y()) - y;
      uint32_t d3 = (dx3 * dx3 + dy3 * dy3) / 256 + 1;
      uint32_t f3 = 16777216 / d3;

      uint32_t s = f1 + f2 + f3;

#define C1 c1
#define C2 c2
#define C3 pixel{0,0,0}
#define L1 8192
#define L2 (2.5*1024)
#define L3 2048

      pixel c;
      if (s >= L1) {
        c = C1;
      } else if (s >= L2) {
        c = interp(s - L2, L1 - L2, C2, C1);
      } else if (s >= L3) {
        c = interp(s - L3, L2 - L3, C3, C2);
      } else {
        c = C3;
      }
      *p++ = c;
    }
  }
}

REGISTER_PROGRAM(Metaballs);
