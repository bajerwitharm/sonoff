#include "timer1s.h"
#include <Arduino.h>
#include "logger.h"
#include "sonoff.h"
#include "relay.h"

#ifndef SKIP_MQTT
#include "mqtt.h"
extern Mqtt mqtt;
#endif

#define INVERT_BUTTON true
extern Timer1s timer;
extern Relay relay;

#define BUTTON 0
#define LED 13
#define MOVE_DETECTOR 14



void Sonoff::setup() {
    pinMode(BUTTON, INPUT);
    pinMode(MOVE_DETECTOR, INPUT);
    digitalWrite(MOVE_DETECTOR,HIGH);
    pinMode(LED, OUTPUT);
}

void Sonoff::ledOn() {
  digitalWrite(LED , 0);
  mqtt.publish_led(true);
  L_INFO("LED ON");
}

void Sonoff::ledOff() {
  digitalWrite(LED , 1);
  mqtt.publish_led(false);
  L_INFO("LED OFF");
}

void Sonoff::ledBlink() {
  digitalWrite(LED , !digitalRead(LED));
  mqtt.publish_led(digitalRead(LED)?false:true);
  L_INFO("LED blink");
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
  bool newState = (digitalRead(MOVE_DETECTOR)?false:true); 
  bool changed = (oldState!=newState);
  oldState = newState;   
  return (newState?1:0)+((changed)?2:0);
}

void Sonoff::detectMovie() {
    static char countdown =10;
    char detection = getMoveDetectorState();

    switch(detection){
      case 1:      
        if (countdown==0){

        } else {
          countdown--;
          if (countdown==0) {
            L_INFO("Move detected");
            ledOn();
          }
        }
          //ledOn();
        break;
      case 0:    
          if (countdown==10) {

          } else {
             countdown++;   
             if (countdown==10) {
                L_INFO("Move end");   
                ledOff();    
             }
          }
          //ledOff();
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
    detectMovie(); 
    oldTime = newTime;
  }

}

