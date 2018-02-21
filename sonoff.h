#pragma once

class Sonoff
{
  public:
    void setup();
    void loop();
    char getButtonState();
    char getMoveDetectorState();
    void detectMovie();
};

