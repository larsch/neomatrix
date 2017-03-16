#include "program.hpp"
#include "display.hpp"
#include "hsv2rgb.hpp"
#include "coord.hpp"
#include "counter.hpp"
#include "framelimiter.hpp"
#include "string.h"

class Hal9kGlitter : public Program
{
public:
  uint8_t frame[198];
  FrameLimiter limit;
  Hal9kGlitter()
    : limit(50)
  {
    memset(frame, 0, 198);
  }

  virtual void run()
  {
    if (limit.skip()) return;
    for (int i = 0; i < 198; ++i)
      frame[i] = (frame[i] > 2) ? (frame[i] - 2) : 0;
    frame[rand() % 198] = 255;
    for (int i = 0; i < 198; ++i)
      pixels[i] = hsv2rgb(60, 64, frame[i]);
  }
};

REGISTER_PROGRAM(Hal9kGlitter);
