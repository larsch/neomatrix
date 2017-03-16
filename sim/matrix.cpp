/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Simulator
 */

#include <SDL.h>
#include <iostream>
#include <../src/pixel.hpp>
#include <../src/neomatrix.hpp>
#include "../src/coord.hpp"

#define W 24
#define H 24
#define SZ (W*H)
#define BUFSZ (SZ*3)
#define PXW 16
#define PXM 2
#define SCRW 1000
#define SCRH 400

static const uint8_t* pixels;
static int brightness = 256;
void ws2812_brightness(int b)
{
  brightness = b;
}

inline uint8_t dim(uint8_t v)
{
  return (v * brightness) >> 8;
}

void ws2812_init()
{
}

void ws2812_show(const pixel pix[])
{
  pixels = reinterpret_cast<const uint8_t*>(&pix[0]) + 6;
}

void render(SDL_Surface* surface)
{
  if (pixels == nullptr) {
    return;
  }
  SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
  const uint8_t* p = pixels;
  for (int i = 0; i < COUNT; ++i) {
    float x = coord[i][0];
    float y = coord[i][1];
    float scale = 0.5;
    SDL_Rect rect = {
      int(PXM + x * scale),
      int(PXM + y * scale),
      PXW,
      PXW
    };
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format,
                                            dim(p[1]),
                                            dim(p[0]),
                                            dim(p[2])));
    p += 3;
  }
}

static bool quit = false;
uint8_t keyState;

void handleKeyDownEvent(SDL_KeyboardEvent& e)
{
  switch (e.keysym.sym) {
  case SDLK_UP:
    keyState |= 4;
    break;
  case SDLK_DOWN:
    keyState |= 8;
    break;
  case SDLK_LEFT:
    keyState |= 1;
    break;
  case SDLK_RIGHT:
    keyState |= 2;
    break;
  case SDLK_SPACE:
    keyState |= 16;
    break;
  case 'q':
  case SDLK_ESCAPE:
    quit = true;
    break;
  }
}

void handleKeyUpEvent(SDL_KeyboardEvent& e)
{
  switch (e.keysym.sym) {
  case SDLK_UP:
    keyState &= ~4;
    break;
  case SDLK_DOWN:
    keyState &= ~8;
    break;
  case SDLK_LEFT:
    keyState &= ~1;
    break;
  case SDLK_RIGHT:
    keyState &= ~2;
    break;
  case SDLK_SPACE:
    keyState &= ~16;
    break;
  }
}

void handleEvent(SDL_Event& e)
{
  switch (e.type) {
  case SDL_QUIT:
    quit = true;
    break;
  case SDL_KEYDOWN:
    handleKeyDownEvent(e.key);
    break;
  case SDL_KEYUP:
    handleKeyUpEvent(e.key);
    break;
  }
}

int main()
{
  srand(time(NULL));
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCRW, SCRH, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  neomatrix_init();

  const uint32_t updateInterval = 15;
  unsigned int nextUpdate = SDL_GetTicks();

  SDL_Surface* screenSurface = SDL_GetWindowSurface(win);
  while (!quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      handleEvent(e);
    }
    render(screenSurface);

    neomatrix_run();

    SDL_UpdateWindowSurface(win);

    nextUpdate += updateInterval;
  }

  SDL_FreeSurface(screenSurface);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
