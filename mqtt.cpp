#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#include "Arduino.h"
#include "mqtt.h"
#include "global.h"
#include "logger.h"
#include "sonoff.h"
#include "timer1s.h"
#include "relay.h"

extern WiFiClient wifiClient;
extern Sonoff sonoff;
extern Timer1s timer;
extern Relay relay;


PubSubClient client;

void mqtt_callback(char* topic, unsigned char* payload, unsigned int length) {
  payload[length] = 0;
  String data = (const char*)payload;
  L_DEBUG("MQTT payload:%s topic:%s",payload,topic);
  if (strncmp(topic, MQTT_LED_ON_TOPIC, strlen(MQTT_LED_ON_TOPIC)) == 0) {
    sonoff.ledOn();
  }
  else if (strncmp(topic, MQTT_LED_OFF_TOPIC, strlen(MQTT_LED_OFF_TOPIC)) == 0) {
    sonoff.ledOff();
  }
  else if (strncmp(topic, MQTT_LED_BLINK_TOPIC, strlen(MQTT_LED_BLINK_TOPIC)) == 0) {
    sonoff.ledBlink();
  }
  else if (strncmp(topic, MQTT_RELAY_BLINK_TOPIC, strlen(MQTT_RELAY_BLINK_TOPIC)) == 0) {
    relay.blink(data.c_str());
  }  
  else if (strncmp(topic, MQTT_RELAY_ON_TOPIC, strlen(MQTT_RELAY_ON_TOPIC)) == 0) {
    relay.setOn(data.c_str());
  }
  else if (strncmp(topic, MQTT_RELAY_OFF_TOPIC, strlen(MQTT_RELAY_OFF_TOPIC)) == 0) {
    relay.setOff();
  } else if (strncmp(topic, MQTT_REBOOT_TOPIC, strlen(MQTT_REBOOT_TOPIC)) == 0) {
    L_INFO("System reboot");
    ESP.restart();
  }
}



void Mqtt::setup() {
  client.setClient(wifiClient);
  client.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
  client.setCallback(mqtt_callback);
}


void Mqtt::reconnect() {
  static int lastTry;
  if ((WiFi.status() != WL_CONNECTED)&&(!client.connected())) {
    int newTry = timer.getTicks();
    if (lastTry != newTry) {
      L_NOTICE("{\"syslog_message\":\"Connecting to %s with user %s\", \"mqtt_host\":\"%s\", \"mqtt_user\":\"%s\"}", MQTT_SERVER_HOST, MQTT_USER, MQTT_SERVER_HOST, MQTT_USER);
      if (client.connect(HOST_NAME, MQTT_USER, MQTT_PASSWORD)) {
        client.subscribe(MQTT_SUBSCRIBE_TOPIC);
        L_NOTICE("{\"syslog_message\":\"Subscribed to %s topic\", \"mqtt_subscribed_topic\":\"%s\"}", MQTT_RGB_TOPIC, MQTT_RGB_TOPIC);
      } else {
        L_ERROR("Unable to connect to %s with user %s. Reconnectiong in 1s..", HOST_NAME, MQTT_USER);
      }
      lastTry = newTry;
    }
  }
}

void Mqtt::loop() {
  reconnect();
  client.loop();
}

int Mqtt::publish_status(uint8_t* message, size_t length, bool retain) {
  return client.publish(MQTT_STATUS_TOPIC, message, length, retain);
}

int Mqtt::publish_status(const char* message, bool retain) {
  return publish_status((uint8_t*)message, strlen(message), retain);
}

int Mqtt::publish_debug(const char* message, size_t length) {
  return client.publish(MQTT_DEBUG_TOPIC, (uint8_t*)message, length);
}

int Mqtt::publish_debug(uint8_t* message, size_t length) {
  return client.publish(MQTT_DEBUG_TOPIC, message, length);
}

int Mqtt::publish_debug(const char* message) {
  return publish_debug(message, strlen(message));
};

int Mqtt::publish_debug(uint8_t data) {
  char tmp[6];
  sprintf(tmp, "%d", data);
  return client.publish(MQTT_DEBUG_TOPIC, tmp, strlen(tmp));
}

int Mqtt::publish_led(bool state){
  char tmp[20];
  sprintf(tmp, "{\"led\":%s}", state?"true":"false");
  return client.publish(MQTT_LED_TOPIC, tmp,strlen(tmp));
}

int Mqtt::publish_relay(bool state){
  char tmp[20];
  sprintf(tmp, "{\"relay\":%s}", state?"true":"false");
  return client.publish(MQTT_RELAY_TOPIC, tmp,strlen(tmp));
}


int Mqtt::publish(const char* topic, char* message, size_t length) {
  return client.publish(topic, message, length);
}


