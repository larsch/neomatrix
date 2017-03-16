#include "program.hpp"
#include "display.hpp"
#include "hsv2rgb.hpp"
#include "coord.hpp"
#include "counter.hpp"

class Hal9k : public Program
{
public:
  virtual void run()
  {
    for (int i = 0; i < 68; ++i)
      pixels[i] = pixel{255,255,255};
    for (int i = 68; i < 114; ++i)
      pixels[i] = pixel{0,255,0};
    for (int i = 114; i < 198; ++i)
      pixels[i] = pixel{255,255,255};
  }
};

REGISTER_PROGRAM(Hal9k);
