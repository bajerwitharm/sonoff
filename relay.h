#pragma once

class Relay
{
  public:
    void setup();
    void setOn(const char* payload="");
    void setOff();
    void blink(const char* payload="");
    void loop();
  private:
    void setOffIn(int seconds);
    int parseOffIn(const char* payload);
    volatile int defaultOffIn = 10;
    volatile int offIn = 0;

};


