#include "publishedVar.h"

struct ButtonLED
{
  uint8_t pwm_;
  uint8_t sw_;
  publishedVar<int> value_;

  ButtonLED(uint8_t pwm, uint8_t sw,char * pubName):
  value_(publishedVar<int>(0,pubName,true)),
  pwm_(pwm),
  sw_(sw)
  {}

};


