 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include "mqtt.h"
#include "global.h"
#include "logger.h"
#include "espOTA.h"
#include "espWiFi.h"
#include "timer1s.h"
#include "sonoff.h"
#include "relay.h"
#include "led.h"

Timer1s timer;
WiFiClient wifiClient;

#ifndef SKIP_MQTT
Mqtt mqtt;
#endif

Sonoff sonoff;
EspOTA espOTA;
EspWiFi espWiFi;
Relay relay;
Led led;

/**
 * Add here all initialization function of submodules
 */
void setup() {
//   wdt_disable();
   sonoff.setup();
   led.setup();
   led.ledOff();
#ifdef USE_CONSOLE
  Serial.begin(CONSOLE_SPEED);
#endif
  espWiFi.setup();
  timer.setup();
#ifndef SKIP_MQTT
  mqtt.setup();
#endif
  espOTA.setup();
  relay.setup();
  led.ledOn();
  L_INFO("Device startup ready");
}

/**
 * Add here all loop functions from submodules
 */
void loop() {
#ifndef SKIP_MQTT
  mqtt.loop();
#endif
  sonoff.loop();
  espOTA.loop();
  espWiFi.loop();
  relay.loop();
  led.loop();
}

