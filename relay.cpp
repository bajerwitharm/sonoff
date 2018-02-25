#include <stdint.h>
#include "Arduino.h"
#include "relay.h"
#include "logger.h"
#include "global.h"
#include "timer1s.h"
#include "led.h"

#define RELAY_PIN 12
#define RELAY_ON 1
#define RELAY_OFF 0

extern Timer1s timer;
extern Led led;

bool relayState;

#ifndef SKIP_MQTT
#include "mqtt.h"
extern Mqtt mqtt;
#endif

void Relay::setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setOff();
}

void Relay::loop() {
  static long old_ticks = 0;
  long ticks = timer.getTicks();
  if (ticks != old_ticks) {
    if (offIn != 0) {
      offIn--;
      if (offIn == 0) {
        setOff();
      }
    }
    old_ticks = ticks;
  }
}

int Relay::parseOffIn(const char* payload) {
  if (strlen(payload)==0) return defaultOffIn;
  return atoi(payload);
}

void Relay::setOn() {
  digitalWrite(RELAY_PIN , RELAY_ON);
  offIn = 0;
  if (relayState!=true) {
    #ifndef SKIP_MQTT
    mqtt.publish_relay(true);
    #endif
    L_INFO("Relay ON");
    relayState = true;
  }
}

void Relay::setOff() {
  digitalWrite(RELAY_PIN, RELAY_OFF);
  if (relayState!=false) {
    #ifndef SKIP_MQTT
    mqtt.publish_relay(false);
    #endif
    L_INFO("Relay OFF");
    relayState = false;
  }
}

void Relay::blink(const char* payload) {
  bool state = digitalRead(RELAY_PIN);
  if (state==RELAY_ON) {
    setOff();
  } else {
    setOn();
    setOffIn(parseOffIn(payload));
  }
}

void Relay::setOffIn(int seconds) {
  if (seconds!=0) {
      offIn = SECONDS_AS_TICKS(seconds);
      //led.startBlink(4);
  } //else led.ledOn();
}




