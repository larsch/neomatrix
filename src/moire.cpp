#include <cmath>
#include "display.hpp"
#include "counter.hpp"
#include "program.hpp"
#include "hsv2rgb.hpp"

struct pt {
  int x, y;
};

uint8_t sine[256];

#define TAU 6.2831853071

void moire_init()
{
  for (int i = 0; i < 256; ++i) {
    sine[i] = (uint8_t)(128.0 + 127.99 * sin((i * TAU) / 256.0));
  }
}

Counter<64, 65565> c;

static unsigned isq(unsigned x)
{
  unsigned l = x >> 12;
  unsigned d = (4096 + l) >> 1;
  l = x / d;
  d = (d + l) >> 1;
  l = x / d;
  d = (d + l) >> 1;
  return d;
}

inline int iabs(int i)
{
  return i < 0 ? -i : i;
}

Counter<32, 360> hueCounter;

template<int T>
int sawtooth(int v)
{
  return T - iabs(v % (2 * T) - T);
}

void moire_run()
{
  int t = c();

  pt pts[2] = {
    {
      6 * 256 + sine[((t * 9 + 2391) / 8) % 256] * 12,
      6 * 256 + sine[((t * 3 + 7232) / 8) % 256] * 12
    },
    {
      6 * 256 + sine[((t * 5 + 1243) / 8) % 256] * 12,
      6 * 256 + sine[((t * 7 + 6314) / 8) % 256] * 12
    }
  };

  for (int y = 0; y < 24; ++y) {
    int y256 = y * 256;
    for (int x = 0; x < 24; ++x) {
      int level = 0;
      for (int i = 0; i < 2; ++i) {
        int dx = (x * 256 - pts[i].x);
        int dy = (y256 - pts[i].y);
        int d = (isq(dx * dx + dy * dy) >> 4);
        int e = sawtooth<64>(d);
        level += e;
        // pixels[y * 24 + x][i] = e;
      }
      pixel& p = pixels[y * 24 + x];
      p = hsv2rgb((hueCounter() + level) % 360, 255, 255);
      // p.r = p.g = p.b = level;
    }
  }
}

class Moire : public Program
{
public:
  Moire()
  {
    moire_init();
  }
  virtual ~Moire() {}
  virtual void run()
  {
    moire_run();
  }
};

REGISTER_PROGRAM(Moire);
