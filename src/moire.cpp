#include <cmath>
#include "display.hpp"
#include "counter.hpp"
#include "program.hpp"

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
      p = hsv2rgb((hueCounter() + level) % 360, 255, 64);
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
