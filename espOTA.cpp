#include "global.h"
#include "logger.h"
#include "espOTA.h"
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include "timer1s.h"
extern Timer1s timer;


void EspOTA::setup() {
  L_DEBUG("Connected to %s", WIFI_SSID);
  L_DEBUG("Init of GenwayOTA");
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.onStart([]() {
    L_INFO("START updating firmware !!");
      timer.stop();
  });
  ArduinoOTA.onEnd([]() {
    L_INFO("END updating firmware !!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    L_DEBUG("Update progress: %u", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    L_ERROR("Error %u: ", error);
    if (error == OTA_AUTH_ERROR) L_ERROR("Firmware update auth Failed")
    else if (error == OTA_BEGIN_ERROR) L_ERROR("Firmware update Begin Failed")
    else if (error == OTA_CONNECT_ERROR) L_ERROR("Firmware update Connect Failed")
    else if (error == OTA_RECEIVE_ERROR) L_ERROR("Firmware update Receive Failed")
    else if (error == OTA_END_ERROR) L_ERROR("Firmware update End Failed");
  });
  ArduinoOTA.begin();
  L_DEBUG("Ready to OTA");
}

void EspOTA::loop() {
  ArduinoOTA.handle();
}


