#include "EspWiFi.h"
#include "global.h"
#include "timer1s.h"
#include "logger.h"
#include <ESP8266WiFi.h>

extern Timer1s timer;

void EspWiFi::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOST_NAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setAutoReconnect(true);
  WiFi.setAutoConnect(true);
}


void EspWiFi::loop() {
  static int lastTry;
  if (WiFi.status() != WL_CONNECTED) {
    int newTry = timer.getTicks();
    if (lastTry + SECONDS_AS_TICKS(10) == newTry) {
      L_DEBUG("Connecting");
      lastTry = newTry;
    }
  }
}


