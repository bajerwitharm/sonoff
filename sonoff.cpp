#include "timer1s.h"
#include <Arduino.h>
#include "logger.h"
#include "sonoff.h"
#include "relay.h"
#include "led.h"

#ifndef SKIP_MQTT
#include "mqtt.h"
extern Mqtt mqtt;
#endif
extern Led led;

#define INVERT_BUTTON true
extern Timer1s timer;
extern Relay relay;



#define RELEASED 0
#define PRESSED 1
#define RELEASING 2
#define PRESSING 3




void Sonoff::setup() {
    pinMode(BUTTON, INPUT);
    pinMode(MOVE_DETECTOR_1, INPUT_PULLUP);
#ifdef MOVE_DETECTOR_2
    pinMode(MOVE_DETECTOR_2, INPUT_PULLUP);
#endif

}

/**
 * 0 - no pressed
 * 1 - pressed
 * 2 - falling edge
 * 3 - rising edge
 */
char Sonoff::getButtonState() {
  static bool oldState;
  bool newState = (digitalRead(BUTTON)?true:false)^INVERT_BUTTON; 
  bool changed = (oldState!=newState);
  oldState = newState;   
  return (newState?1:0)+((changed)?2:0);
}

void Sonoff::detectMovie() {
    char detection = getMoveDetectorState<MOVE_DETECTOR_1>();
    switch(detection){
      case PRESSING:      
        relay.setOn();
        led.ledOn();
        break;
      case RELEASING:    
         led.ledOff();
         relay.setOffIn(ON_AFTER_MOTION);
        break;
    }
#ifdef MOVE_DETECTOR_2
    detection = getMoveDetectorState<MOVE_DETECTOR_2>();
    switch(detection){
      case PRESSING:      
        relay.setOn();
        led.ledOn();
        break;
      case RELEASING:    
         led.ledOff();
         relay.setOffIn(ON_AFTER_MOTION);
        break;
    }
#endif
    
}

#define DIFF(a,b) ((a)>(b)?((a)-(b)):((b)-(a))) 

void Sonoff::loop() {
  static int oldTime;
  static int pressTime;
  int newTime = timer.getTicks();
  if (newTime != oldTime) {
    switch(getButtonState()){
      case PRESSED:
        switch(DIFF(pressTime,newTime)){
          case SECONDS_AS_TICKS(ALWAYS_ON_AFTER-2):
            relay.setOn();
            break;
          case SECONDS_AS_TICKS(ALWAYS_ON_AFTER-1):
            relay.setOff();
            break;
          case SECONDS_AS_TICKS(ALWAYS_ON_AFTER):
            relay.setOn();
            relay.setAlwaysOnFlag();
            break;
        }
        break;
      case RELEASING:
        led.ledOff();
        L_INFO("Button released");
        break;
      case PRESSING:      
        L_INFO("Button pressed");
        led.ledOn();
        relay.clearAlwaysOnFlag();
        pressTime = newTime;
        relay.blink();
        break;
    }
    oldTime = newTime;
  }
  detectMovie(); 
}

