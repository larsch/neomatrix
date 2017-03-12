#include "common.hpp"
#include "pixel.hpp"
#include "ws2812_i2s.hpp"

#include "fire.hpp"
#include "balls.hpp"
#include "framelimiter.hpp"

FrameLimiter limit(50);

static pixel* frame;
pixel* pixels;

void neomatrix_init()
{
  ws2812_init();
  frame = new pixel[WS_PIXELS];
  pixels = frame + 2;
  // fire_init();
  balls_init();
}

void neomatrix_run()
{
  if (limit.skip())
    return;
  // fire_update();

  uint32_t m = getCycleCount();
  balls_update();
  uint32_t a = getCycleCount();
  Serial.println(a - m);

  // uint32_t m = (millis() * WS_PIXELS) / 500;
  // for (int i = 0; i < WS_PIXELS; ++i) {
  //   frame[i].r = ((i + m) % WS_PIXELS) < WS_PIXELS/3 ? 64 : 0;
  //   frame[i].g = ((i + m + WS_PIXELS / 3) % WS_PIXELS) < WS_PIXELS/3 ? 64 : 0;
  //   frame[i].b = ((i + m + 2 * WS_PIXELS / 3) % WS_PIXELS) < WS_PIXELS/3 ? 64 : 0;
  // }
  ws2812_show(frame);
}
