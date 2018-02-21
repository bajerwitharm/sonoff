#pragma once
class Led
{
  public:
    void setup();
    void loop();
    void ledOn();
    void ledOff();  
    void ledBlink(); 
    void startBlink(int period);
  private:
    int blinkPeriod;
};
