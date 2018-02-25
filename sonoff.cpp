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

#define BUTTON 0
#define MOVE_DETECTOR 14



void Sonoff::setup() {
    pinMode(BUTTON, INPUT);
    pinMode(MOVE_DETECTOR, INPUT_PULLUP);
  //  digitalWrite(MOVE_DETECTOR,HIGH);
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


/**
 * 0 - no pressed
 * 1 - pressed
 * 2 - falling edge
 * 3 - rising edge
 */
char Sonoff::getMoveDetectorState() {
  static bool oldState;
  bool newState = (digitalRead(MOVE_DETECTOR)?true:false); 
  bool changed = (oldState!=newState);
  oldState = newState;   
  return (newState?1:0)+((changed)?2:0);
}

void Sonoff::detectMovie() {
    char detection = getMoveDetectorState();

    switch(detection){
      case 1+2:      
        relay.setOn();
        led.ledOn();
        break;
      case 0+2:    
         led.ledOff();
         relay.setOffIn(ON_AFTER_MOTION);
        break;
    }
}

void Sonoff::loop() {
  static int oldTime;
  int newTime = timer.getTicks();
  if (newTime != oldTime) {
    switch(getButtonState()){
      case 2:
        L_INFO("Button released");
        break;
      case 3:      
        L_INFO("Button pressed");
        relay.blink();
        break;
    }
    oldTime = newTime;
  }
  detectMovie(); 
}

