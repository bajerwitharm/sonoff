#pragma once
#include <stdint.h>

class Sonoff
{
  public:
    void setup();
    void loop();
    char getButtonState();
    char getMoveDetectorState();
    void ledOn();
    void ledOff();
    void ledBlink();
    void relayOn();
    void relayOff();
    void relayBlink();
    bool detectMovie();
};
