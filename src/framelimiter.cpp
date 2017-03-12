#include "framelimiter.hpp"
#include "common.hpp"

FrameLimiter::FrameLimiter(int fps) {
  cyclesPerFrame = HZ / fps;
  nextFrame = getCycleCount();
}

bool FrameLimiter::skip() {
  uint32_t now = getCycleCount();
  int32_t untilNextFrame = nextFrame - now;
  if (untilNextFrame <= 0) {
    nextFrame += cyclesPerFrame;
    if (int32_t(nextFrame - now) < 0)
      nextFrame = now;
    return false;
  } else {
    return true;
  }
}
