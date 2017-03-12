#ifndef _metaballs_hpp_
#define _metaballs_hpp_

#include "program.hpp"

class Metaballs : public Program
{
public:
  Metaballs();
  ~Metaballs();
  virtual void run();
private:
  uint32_t interp(int lvl, int max, uint32_t c1, uint32_t c2);
  uint8_t gm1[256];
  uint8_t gm2[256];
};

#endif // _metaballs_hpp_
