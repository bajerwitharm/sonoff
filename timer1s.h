#pragma once

#define TRIGGER_TIME  (41660000) //0.5s
#define SECONDS_AS_TICKS(x) ((x)*2)

class Timer1s
{
  public:
    void setup();
    void stop();
    long getTicks();
};




