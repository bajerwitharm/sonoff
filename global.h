#pragma once
#ifndef GLOBAL_H_
#define GLOBAL_H_

//#define WIFI_SSID "Salwatorska6admin"
//#define WIFI_SSID "Salwatorska6admi"
#define WIFI_SSID "TP-LINK_ANIA"
//#define WIFI_PASSWORD "Administrator@main6"
#define WIFI_PASSWORD "KochamAnie1"
#define MQTT_SERVER_HOST "mqtt.salwatorska.pl"
#define MQTT_SERVER_PORT 1883

#define MQTT_USER "Administracja"
#define MQTT_PASSWORD "Administrator@main6"
#define HOST_NAME "sonoff"
#define MQTT_SUBSCRIBE_TOPIC "salwatorska6/" HOST_NAME "/control/#"
#define MQTT_RGB_TOPIC "salwatorska6/" HOST_NAME "/control/rgb"

#define MQTT_LED_TOPIC "salwatorska6/" HOST_NAME "/state/led"
#define MQTT_LED_ON_TOPIC "salwatorska6/" HOST_NAME "/control/ledOn"
#define MQTT_LED_OFF_TOPIC "salwatorska6/" HOST_NAME "/control/ledOff"
#define MQTT_LED_BLINK_TOPIC "salwatorska6/" HOST_NAME "/control/ledBlink"

#define MQTT_RELAY_TOPIC "salwatorska6/" HOST_NAME "/state/relay"
#define MQTT_RELAY_ON_TOPIC "salwatorska6/" HOST_NAME "/control/relayOn"
#define MQTT_RELAY_OFF_TOPIC "salwatorska6/" HOST_NAME "/control/relayOff"
#define MQTT_RELAY_BLINK_TOPIC "salwatorska6/" HOST_NAME "/control/relayBlink"
#define MQTT_REBOOT_TOPIC "salwatorska6/" HOST_NAME "/control/reboot"

#define MQTT_STATUS_TOPIC "salwatorska6/" HOST_NAME "/status"
#define MQTT_DEBUG_TOPIC "salwatorska6/" HOST_NAME "/debug"


#define MAX_LOG_ENTRY_SIZE 256
#define L_LEVEL LOG_INFO ///< Minimal level of event severity to log base on syslog level
//#define SKIP_MQTT

#define SYSLOG_IP "logger.salwatorska.pl"
#define SYSLOG_PORT 5140
//#define USE_OWN_SYSLOG
#define APPLICATON_NAME HOST_NAME


/**
 * Logger related settings
 */
//#define USE_SYSLOG ///< Logs will be saved to system systlog
//#define USE_CONSOLE ///< Logs will be printed to console
#define USE_MQTT ///< Logs will be printed to mqtt
#define CONSOLE_SPEED 9600

/**
 * OTA settings
 */
#define OTA_HOSTNAME HOST_NAME

#endif


