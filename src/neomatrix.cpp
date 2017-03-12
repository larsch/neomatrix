#include "common.hpp"
#include "pixel.hpp"
#include "ws2812_i2s.hpp"
#include "program.hpp"

#include "fire.hpp"
#include "balls.hpp"
#include "framelimiter.hpp"
#include "moire.hpp"

FrameLimiter limit(50);

static pixel* frame;
pixel* pixels;

Program* current = nullptr;
uint32_t runTime = 0;
ProgramFactory* currentFactory = nullptr;

void neomatrix_init()
{
  ws2812_init();
  frame = new pixel[WS_PIXELS];
  pixels = frame + 2;
  // fire_init();
  // balls_init();

  currentFactory = ProgramFactory::first;
  current = currentFactory->launch();
  runTime = getCycleCount();
}

#define RUNTIME HZ * 3

void neomatrix_run()
{
  // if (limit.skip())
  //   return;

  uint32_t m = getCycleCount();

  if (m - runTime > RUNTIME) {
    delete current;
    currentFactory = currentFactory->next;
    if (currentFactory == nullptr) {
      currentFactory = ProgramFactory::first;
    }
    current = currentFactory->launch();
    printf("running %s\n", currentFactory->name);
    runTime = m;
  }

  // fire_update();
  // balls_update();
  current->run();

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
