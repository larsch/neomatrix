/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * The Matrix
 */

#ifndef _matrix_hpp_
#define _matrix_hpp_

#include "framelimiter.hpp"
#include "program.hpp"
#include "pixel.hpp"

class TheMatrix : public Program
{
public:
  TheMatrix();
  ~TheMatrix();
  virtual void run();
private:
  pixel palette[256];
  uint8_t frame[24 * 24];
  uint16_t pos[24];
  int speed[24];
  FrameLimiter limiter;
};

#endif // _matrix_hpp_
