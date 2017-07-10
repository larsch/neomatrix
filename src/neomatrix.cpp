/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Main display code
 */

#include "common.hpp"
#include "pixel.hpp"
#include "ws2812_i2s.hpp"
#include "program.hpp"

static pixel* frame;
pixel* pixels;

Program* current = nullptr;
uint32_t startTime = 0;
ProgramFactory* currentFactory = nullptr;

// #define TEST_PROGRAM "Hal9kWipe"

void neomatrix_init()
{
  ws2812_init();
  frame = new pixel[WS_PIXELS];
  pixels = frame + 2;
  // fire_init();
  // balls_init();

#ifdef TEST_PROGRAM
  currentFactory = ProgramFactory::get(TEST_PROGRAM);
#else
  currentFactory = ProgramFactory::first;
#endif
  current = currentFactory->launch();
  startTime = millis();
}

#define RUNTIME 16000
#define FADETIME 1000
#define FADEIN FADETIME
#define FADEOUT (RUNTIME-FADETIME)
#define MAX_BRIGHT 128

void program_loop()
{
  uint32_t now = millis();
  uint32_t prgTime = now - startTime;
  if (prgTime < FADEIN) {
    ws2812_brightness((prgTime * MAX_BRIGHT) / FADEIN);
  } else if (prgTime < FADEOUT) {
    ws2812_brightness(MAX_BRIGHT);
  } else if (prgTime < RUNTIME) {
    ws2812_brightness(((RUNTIME - prgTime) * MAX_BRIGHT) / FADETIME);
  } else {
    ws2812_brightness(0);
    delete current;
    currentFactory = currentFactory->next;
    if (currentFactory == nullptr) {
      currentFactory = ProgramFactory::first;
    }
    current = currentFactory->launch();
    printf("running %s\n", currentFactory->name);
    startTime = now;
  }
}

void neomatrix_run()
{
  uint32_t m = getCycleCount();
#ifndef TEST_PROGRAM
  program_loop();
#endif
  current->run();
  uint32_t a = getCycleCount();
  uint32_t time = a - m;
  if (time * 50 > HZ) {
    Serial.printf("Slow render %u\n", time);
  }
  ws2812_show(frame);
}
