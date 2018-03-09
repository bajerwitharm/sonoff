#pragma once

class Sonoff
{
  public:
    void setup();
    void loop();
    char getButtonState();
    /**
    * 0 - no pressed
    * 1 - pressed
    * 2 - falling edge
    * 3 - rising edge
    */
    template<int PIN>
    char getMoveDetectorState() {
      static bool oldState;
      bool newState = (digitalRead(PIN)?true:false); 
      bool changed = (oldState!=newState);
      oldState = newState;   
      return (newState?1:0)+((changed)?2:0);
    }
    void detectMovie();
};

