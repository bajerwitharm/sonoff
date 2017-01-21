#include "timer1s.h"
#include <Arduino.h>
#include "logger.h"
#include "sonoff.h"

#ifndef SKIP_MQTT
#include "mqtt.h"
extern Mqtt mqtt;
#endif

#define INVERT_BUTTON true
extern Timer1s timer;

const int BUTTON = 0;
const int LED = 13;
const int RELAY = 12;
const int MOVE_DETECTOR = 14;



void Sonoff::setup() {
    pinMode(BUTTON, INPUT);
    pinMode(MOVE_DETECTOR, INPUT);
    digitalWrite(MOVE_DETECTOR,LOW);
    pinMode(LED, OUTPUT);
    pinMode(RELAY, OUTPUT);
}

void Sonoff::relayOn() {
  digitalWrite(RELAY , 0);
  mqtt.publish_relay(true);
  L_INFO("Relay ON");
}

void Sonoff::relayOff() {
  digitalWrite(RELAY , 1);
  mqtt.publish_relay(false);
  L_INFO("Relay OFF");
}

void Sonoff::relayBlink() {
  digitalWrite(RELAY, !digitalRead(RELAY));
  mqtt.publish_relay(digitalRead(RELAY)?false:true);
  L_INFO("Relay blink");
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
  bool newState = (digitalRead(MOVE_DETECTOR)?true:false); 
  bool changed = (oldState!=newState);
  if (changed) {
    if (newState!=((digitalRead(MOVE_DETECTOR)?true:false))) {
      changed = false;
    }
  }
  oldState = newState;   
  return (newState?1:0)+((changed)?2:0);
}

bool Sonoff::detectMovie() {
    static char countdown =10;
    char detection = getMoveDetectorState();
    switch(detection){

      case 3:      
          L_INFO("Move detected");
          ledOn();

        countdown =10;
        break;
    }
    if (countdown--==0) {
      L_INFO("Move end");
      ledOff();
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
        relayBlink();
        break;
    }
      detectMovie();
  }

  oldTime = newTime;
}
