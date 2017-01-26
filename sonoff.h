#pragma once

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
    void detectMovie();
};

