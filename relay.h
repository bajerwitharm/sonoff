#pragma once
#include "global.h"

class Relay
{
  public:
    void setup();
    void setOn();
    void setOff();
    void blink(const char* payload="");
    void loop();
    int parseOffIn(const char* payload);
    void setOffIn(int seconds);
  private:

    volatile int defaultOffIn = ON_AFTER_BUTTON;
    volatile int offIn = 0;

};


