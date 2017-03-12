#include "framelimiter.hpp"
#include "common.hpp"

FrameLimiter::FrameLimiter(int fps)
{
  cyclesPerFrame = HZ / fps;
  nextFrame = getCycleCount();
}

bool FrameLimiter::skip()
{
  uint32_t now = getCycleCount();
  uint32_t untilNextFrame = nextFrame - now;
  if (untilNextFrame < cyclesPerFrame) {
    return true;
  }
  nextFrame += cyclesPerFrame;
  untilNextFrame = nextFrame - now;
  if (untilNextFrame >= cyclesPerFrame) {
    nextFrame = now + cyclesPerFrame;
  }
  return false;
}
