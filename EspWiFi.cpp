#include "EspWiFi.h"
#include "global.h"
#include "timer1s.h"
#include "logger.h"
#include <ESP8266WiFi.h>

extern Timer1s timer;

void EspWiFi::setup() {
  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setAutoReconnect(true);
  WiFi.setAutoConnect(true);
}


void EspWiFi::loop() {
  static int lastTry;
  if (WiFi.status() != WL_CONNECTED) {
    int newTry = timer.getTicks();
    if (lastTry != newTry) {
      L_DEBUG("Connecting");
    //  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      lastTry = newTry;
    }
  }
}


