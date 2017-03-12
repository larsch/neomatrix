#ifndef _shadebob_hpp
#define _shadebob_hpp

#include "program.hpp"

class Shadebob : public Program
{
public:
  Shadebob();
  ~Shadebob();
  virtual void run();
private:
  pixel palette[256];
  int x;
  int y;
};
