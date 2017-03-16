#include "program.hpp"
#include "display.hpp"
#include "hsv2rgb.hpp"
#include "coord.hpp"
#include "counter.hpp"
#include "framelimiter.hpp"
#include "string.h"
#include <cmath>

static Counter<1400, 3600> c;
static Counter<128, 256> c2;

#define TAU 6.2831

class Hal9kWipe : public Program
{
public:
  Hal9kWipe()
  {
  }

  virtual void run()
  {
    int sx = 256 * sin(c2() * TAU / 256);
    int sy = 256 * cos(c2() * TAU / 256);
    for (int i = 0; i < 198; ++i) {
      int x = coord[i][0];
      int y = coord[i][1];
      int tx = c() + (x * sx) / 128 + (y * sy) / 128;
      pixels[i] = hsv2rgb((tx / 10 + 360) % 360, 255, 255);
    }
  }
};

REGISTER_PROGRAM(Hal9kWipe);
