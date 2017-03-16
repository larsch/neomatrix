#include "program.hpp"
#include "display.hpp"
#include "hsv2rgb.hpp"
#include "coord.hpp"
#include "counter.hpp"

static Counter<200, 360> c;

class Hal9kRainbow : public Program
{
public:
  virtual void run()
  {
    for (int i = 0; i < LETTERS; ++i) {
      for (int n = 0; n < count[i]; ++n) {
        pixels[offset[i] + n] = hsv2rgb(((i * 360) / LETTERS + c()) % 360, 255, 255);
      }
    }
  }
};

REGISTER_PROGRAM(Hal9kRainbow);
