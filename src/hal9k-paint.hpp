/**
 * Copyright (C) 2017 Lars Christensen
 */

#ifndef _letterwipe_hpp_
#define _letterwipe_hpp_

#include "program.hpp"
#include "pixel.hpp"

class Hal9kPaint : public Program
{
public:
  Hal9kPaint();
  ~Hal9kPaint();
  virtual void run();
private:
  uint32_t start;
  pixel last;
  pixel current;
  int lv;
  int cp;
};

#endif /* _letterwipe_hpp_ */
