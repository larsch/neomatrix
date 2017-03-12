#include "common.hpp"

// Generic counter with compile-time choice of rate (ticks per second)
// and period (ticks before wrap-around).
template<int RATE, int PERIOD>
class Counter
{
public:
  uint32_t operator()()
  {
    uint32_t current = getCycleCount();
    const uint32_t divisor = HZ / RATE;
    residual += current - previous;
    counter = (counter + residual / divisor) % PERIOD;
    residual %= divisor;
    previous = current;
    return counter;
  }

  uint32_t counter = 0;
  uint32_t residual = 0;
  uint32_t previous = 0;
};
