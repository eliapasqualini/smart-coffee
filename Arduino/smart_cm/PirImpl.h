#ifndef __PIR__
#define __PIR__

#include "Pir.h"

class PirImpl: public Pir {
 
public: 
  PirImpl(int pin);
  bool isDetected();

private:
  int pin;

};

#endif
