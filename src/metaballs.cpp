#include "common.hpp"
#include "metaballs.hpp"
#include "display.hpp"
#include "counter.hpp"
#include "program.hpp"
#include <cmath>
#include "display.hpp"

Metaballs::Metaballs()
{
  for (int i = 0; i < 255; ++i) {
    gm1[i] = 255.0 * pow(i / 255.0, 2.2);
    gm2[i] = 255.0 * pow(i / 255.0, 1.0 / 2.2);
  }
}

Metaballs::~Metaballs()
{
}

int32_t walk(int32_t w)
{
  int32_t x = w - 24 * 256;
  return x < 0 ? -x : x;
}

uint32_t Metaballs::interp(int lvl, int max, uint32_t c1, uint32_t c2)
{
  uint8_t f1 = (lvl * 255) / max;
  uint8_t f2 = 255 - f1;
  uint8_t r1 = c1 >> 16;
  uint8_t r2 = c2 >> 16;
  uint8_t g1 = c1 >> 8;
  uint8_t g2 = c2 >> 8;
  uint8_t b1 = c1;
  uint8_t b2 = c2;
  // uint8_t r = (r1 * f2 + r2 * f1) / 256;
  // uint8_t g = (g1 * f2 + g2 * f1) / 256;
  // uint8_t b = (b1 * f2 + b2 * f1) / 256;
  uint8_t r = gm2[(gm1[r1] * f2 + gm1[r2] * f1) / 256];
  uint8_t g = gm2[(gm1[g1] * f2 + gm1[g2] * f1) / 256];
  uint8_t b = gm2[(gm1[b1] * f2 + gm1[b2] * f1) / 256];
  return (r << 16) + (g << 8) + b;
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
      // uint8_t level = s > 4096 ? 0x40 : (s / 64); // s > 2048 ? 0x20 : 0x00;
      // uint8_t level = (s > 255 ? 255 : s) / 4;

#if 1
#define C1 0x00b000
#define C2 0x004060
#define C3 0x000000
#define L1 8192
#define L2 5120
#define L3 2048
#else
#define C1 0x606005
#define C2 0x401000
#define C3 0x000000
#define L1 8192
#define L2 2048
#define L3 1024
#endif

      uint32_t c;
      if (s >= L1) {
        c = C1;
      } else if (s >= L2) {
        c = interp(s - L2, L1 - L2, C2, C1);
      } else if (s >= L3) {
        c = interp(s - L3, L2 - L3, C3, C2);
      } else {
        c = C3;
      }
      // uint32_t c;
      // if (s > 8192)
      //   c = 0x606005;
      // else if (s > 2048)
      //   // c = 0x404000;
      //   c = interp((s - 2048), (8192-2048), 0x401000, 0x606005);
      // else if (s > 1024)
      //   // c = 0x401000;
      //   c = interp(s - 1024, 1024, 0x000000, 0x401000);
      // else
      //   c = 0x000000;
      p->g = c >> 8;
      p->r = c >> 16;
      p->b = c;
      ++p;
      // *p++ = c >> 8;               //
      // *p++ = c >> 16;
      // *p++ = c;
    }
  }

  // if (fireKeyPressed())
  //    setMode(MODE_SNAKE);
  // if (leftKeyPressed())
  //    setMode(MODE_LOGO_SCROLL);
  // if (upKeyPressed())
  //   setMode(MODE_FIRE);
}

REGISTER_PROGRAM(Metaballs);
