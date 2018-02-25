 
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

void setup() {
  led.setup();
  led.ledOff();
  timer.setup();
  espWiFi.setup();
  espOTA.setup();
  relay.setup();
  sonoff.setup();
  #ifdef USE_CONSOLE
  Serial.begin(CONSOLE_SPEED);
  #endif
  led.ledOn();
  L_INFO("Device startup ready");
}
 
void loop() {
  led.loop();
  espWiFi.loop();
  espOTA.loop();
  sonoff.loop();
  relay.loop();
}
