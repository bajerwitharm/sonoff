#pragma once
#ifndef GLOBAL_H_
#define GLOBAL_H_

#define ON_AFTER_BUTTON 30 ///< How long light on after button pressed
#define ON_AFTER_MOTION 30 ///< How long light on after motion detected
#define ALWAYS_ON_AFTER 10 ///< How long need to press button until light will be always on

#define BUTTON 0            ///< GPIO of button
#define MOVE_DETECTOR_1 14  ///< GPIO of motion detector
#define MOVE_DETECTOR_2 1   ///< GPIO of motion detector 2 (if available)

#define WIFI_SSID "TP-LINK_ANIA"
//#define WIFI_SSID "Salwatorska6admin"
#define WIFI_PASSWORD "KochamAnie1"
//#define WIFI_PASSWORD "Administrator@main6"
#define MQTT_SERVER_HOST "mqtt.salwatorska.pl"
#define MQTT_SERVER_PORT 1883

#define MQTT_USER "Administracja"
#define MQTT_PASSWORD "Administrator@main6"
#define HOST_NAME "rowerownia"
#define MQTT_SUBSCRIBE_TOPIC "salwatorska6/" HOST_NAME "/control/#"  

#define MQTT_RELAY_TOPIC "salwatorska6/" HOST_NAME "/state/relay"               ///< Where relay state will be write
#define MQTT_RELAY_ON_TOPIC "salwatorska6/" HOST_NAME "/control/relayOn"        ///< Need to write number of seconds how long light should be on (0 for infinite)
#define MQTT_RELAY_OFF_TOPIC "salwatorska6/" HOST_NAME "/control/relayOff"      ///< Any write will off the light
#define MQTT_RELAY_BLINK_TOPIC "salwatorska6/" HOST_NAME "/control/relayBlink"  ///< Any write will blink the light
#define MQTT_REBOOT_TOPIC "salwatorska6/" HOST_NAME "/control/reboot"           ///< Any write will force reboot

#define MQTT_STATUS_TOPIC "salwatorska6/" HOST_NAME "/status"
#define MQTT_DEBUG_TOPIC "salwatorska6/" HOST_NAME "/debug"


#define MAX_LOG_ENTRY_SIZE 256
#define L_LEVEL LOG_DEBUG ///< Minimal level of event severity to log base on syslog level
//#define SKIP_MQTT

#define SYSLOG_IP "logger.salwatorska.pl"
#define SYSLOG_PORT 5140
//#define USE_OWN_SYSLOG
#define APPLICATON_NAME HOST_NAME


/**
 * Logger related settings
 */
//#define USE_SYSLOG ///< Logs will be saved to system systlog
#define USE_CONSOLE ///< Logs will be printed to console
#ifndef SKIP_MQTT
#define USE_MQTT ///< Logs will be printed to mqtt
#endif
#define CONSOLE_SPEED 9600

/**
 * OTA settings
 */
#define OTA_HOSTNAME HOST_NAME

#endif


