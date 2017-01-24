 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include "mqtt.h"
#include "global.h"
#include "logger.h"
#include "espOTA.h"
#include "timer1s.h"
#include "sonoff.h"


Timer1s timer;
WiFiClient wifiClient;

#ifndef SKIP_MQTT
Mqtt mqtt;
#endif

Sonoff sonoff;
EspOTA espOTA;

/**
 * WiFi setup
 */
void setup_wifi() {
  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
 //   sonoff.ledBlink();
 //   delay(1000);
//  }
//  sonoff.ledOn();
//  L_DEBUG("Connectted to WiFi %s",WIFI_SSID);
}

/**
 * Add here all initialization function of submodules
 */
void setup() {
#ifdef USE_CONSOLE
  Serial.begin(CONSOLE_SPEED);
#endif
  delay(1000);
  setup_wifi();
  timer.setup();
#ifndef SKIP_MQTT
  mqtt.setup();
#endif
  sonoff.setup();
  espOTA.setup();
  //L_INFO("Device startup ready");
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
}
