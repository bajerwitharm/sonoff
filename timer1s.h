#pragma once
#include <stdint.h>
typedef int (*timerCallback)(long);

class Timer1s
{
  public:
    void setup();
    void stop();
    long getTicks();
    void setTimerCallback(timerCallback function);
};



