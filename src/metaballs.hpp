/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Metaballs
 */

#ifndef _metaballs_hpp_
#define _metaballs_hpp_

#include "program.hpp"
#include "pixel.hpp"

class Metaballs : public Program
{
public:
  Metaballs();
  ~Metaballs();
  virtual void run();
private:
  pixel interp(int lvl, int max, pixel c1, pixel c2);
  uint8_t gm1[256];
  uint8_t gm2[256];
  pixel c1;
  pixel c2;
};

#endif // _metaballs_hpp_
