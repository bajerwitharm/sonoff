#include "timer1s.h"
#include "led.h"
#include <Arduino.h>

extern Timer1s timer;

#define LED 13

void Led::setup() {
      pinMode(LED, OUTPUT);
}

void Led::ledOn() {
  digitalWrite(LED , 0);
  blinkPeriod = 0;
}

void Led::ledOff() {
  digitalWrite(LED , 1);
  blinkPeriod = 0;
}

void Led::ledBlink() {
  digitalWrite(LED , !digitalRead(LED));
}

void Led::startBlink(int period) {
   blinkPeriod = period;
}

void Led::loop() {
  static int timeToBlink;
  static int oldTime;
  int newTime = timer.getTicks();
  if (newTime != oldTime) {
    if (blinkPeriod!=0) {
      if (timeToBlink == 0) {
        timeToBlink = blinkPeriod;
        ledBlink();
      } else timeToBlink--;
    }
    oldTime = newTime;
  }
}

