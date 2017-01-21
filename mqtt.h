#pragma once
#include "Arduino.h"
class Mqtt
{
  public:
    void setup();
    void loop();
    int publish_debug(const char* message, size_t length);
    int publish_debug(uint8_t* message, size_t length);
    int publish_debug(uint8_t message);
    int publish_debug(const char* message);
    int publish_status(uint8_t* message, size_t length, bool retain = false);
    int publish_status(const char* message, bool retain = false);
    int publish(const char* topic, char* message, size_t length);    
    int publish_radiation(uint16_t radiation);
    int publish_led(bool state);
    int publish_relay(bool state);
  private:
    void reconnect();






};


