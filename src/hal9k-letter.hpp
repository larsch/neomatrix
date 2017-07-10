/**
 * Copyright (C) 2017 Lars Christensen
 */

#ifndef _letterwipe_hpp_
#define _letterwipe_hpp_

#include "program.hpp"
#include "pixel.hpp"

class LetterWipe : public Program
{
public:
  LetterWipe();
  ~LetterWipe();
  virtual void run();
private:
  uint32_t start;
};

#endif /* _letterwipe_hpp_ */
