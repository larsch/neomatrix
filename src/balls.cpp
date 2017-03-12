#include "common.hpp"
#include "pixel.hpp"
#include "counter.hpp"
#include <stdint.h>
#include <string.h>
#include <math.h>

// int abs(int x) {
//   return x < 0 ? -x : x;
// }

extern pixel* pixels;

// static uint8_t circle[] =
// {
//   0, 32, 175, 223, 223, 175, 32, 0,
//   32, 239, 255, 255, 255, 255, 239, 32,
//   176, 255, 255, 255, 255, 255, 255, 176,
//   240, 255, 255, 255, 255, 255, 255, 223,
//   240, 255, 255, 255, 255, 255, 255, 224,
//   176, 255, 255, 255, 255, 255, 255, 176,
//   32, 240, 255, 255, 255, 255, 240, 32,
//   0, 32, 176, 224, 224, 176, 32, 0
// };

struct ball {
  int x;
  int y;
  int vx;
  int vy;
};

static ball balls[3];
static uint32_t lastTick;

void balls_init()
{
  balls[0] = { 0, 0, 19, 0 };
  balls[1] = { 4 * 256, 4 * 256, 17, 0 };
  balls[2] = { 8 * 256, 8 * 256, 13, 0 };
  lastTick = getCycleCount();
}

#define LIMIT (17 * 256)

// static void simulate(int32_t delta)
// {
//   for (int i = 0; i < 3; ++i) {
//     balls[i].vy += (delta * 100) / HZ;
//     balls[i].y += (balls[i].vy * delta) / (HZ / 256);

//     balls[i].x += (balls[i].vx * delta) / (HZ / 256);

//     if (balls[i].y > LIMIT) {
//       balls[i].y = 2 * LIMIT - balls[i].y;
//       balls[i].vy *= -1;
//     }
//     if (balls[i].x > LIMIT) {
//       balls[i].x = 2 * LIMIT - balls[i].x;
//       balls[i].vx *= -1;
//     }
//     if (balls[i].x < -128) {
//       balls[i].x *= -1;
//       balls[i].vx *= -1;
//     }
//   }
// }

static Counter<256, 7 * 11 * 13 * 32 * 256> c;

void balls_update()
{
  // uint32_t now = getCycleCount();
  // int32_t delta = now - lastTick;
  // // while (delta > 1024) {
  // //   simulate(delta);
  // //   delta -= 1024;
  // // }
  // simulate(delta);

  int32_t t = c();

  const int mul[3] = { 7, 11, 13 };
  for (int i = 0; i < 3; ++i) {
    int x = t * mul[i];

    int l = abs((x + i * 1365) % (32 * 256) - 16 * 256);
    balls[i].x = 16 * 256 - l;
    int32_t t = 16 * 256 - abs((x + i * 3365 + 1365) % (32 * 256) - 16 * 256);
    balls[i].y = (t * t) / (16 * 256);
  }

  // lastTick = now;

  memset(pixels, 0, 576 * 3);
  for (int y = 0; y < 24; ++y) {
    for (int i = 0; i < 3; ++i) {
      int dy = y * 256 - 896 - balls[i].y;
      int dy2 = dy * dy;
      for (int x = 0; x < 24; ++x) {
        int dx = x * 256 - 896 - balls[i].x;
        int d2 = dx * dx + dy2;
#define CUTOFF 1224
        if (d2 < CUTOFF * CUTOFF) {
          pixels[y * 24 + x][i] = 64;
        } else if (d2 < (CUTOFF + 256) * (CUTOFF + 256)) {
          int d = sqrt(d2);
          if (d < (CUTOFF + 256)) {
            pixels[y * 24 + x][i] = 63 - (d - CUTOFF) / 4;
          }
        }
      }
    }
  }
}
