#include "Logger.h"
#include "Arduino.h"
#include <cstdio>
#include "timer1s.h"
//#include <ctime>
#ifndef SKIP_MQTT
#include "mqtt.h"
extern Mqtt mqtt;
#endif
extern Timer1s timer;

void Logger::dummy(int level, const char* location, const char* file, const char * format, ...)
{

}

#if L_LEVEL>=LOG_CRIT
/**
 Adds new event to log

 @param level - event severity base on syslog
 @param location - function and class name where event was triggered
 @param file - name of the file and line where event was triggered
 @param format - printf based message to log
*/
void Logger::add(int level, const char* location, const char* file, const char * format, ...)
{
  va_list argptr;
  va_start(argptr, format);
  storeEvent(level, location, file, format, argptr);
  va_end(argptr);
}


void Logger::storeEvent(const int level, const char* location, const char* file, const char*& format, va_list& argptr) {
  char message[MAX_LOG_ENTRY_SIZE];
  vsnprintf(message, MAX_LOG_ENTRY_SIZE, format, argptr);
#ifdef USE_CONSOLE
  writeToConsole(message, location, file, level);
#endif
#ifdef USE_MQTT
  writeToMqtt(message, location, file, level);
#endif
#ifdef USE_SYSLOG
  writeToSyslog(message, location, file , level);
#endif
}
#endif

void Logger::prepareEntry( char* buffer, const char * format, ... )
{
  va_list args;
  va_start (args, format);
  vsnprintf(buffer, MAX_LOG_ENTRY_SIZE, format, args);
  va_end (args);
}

void Logger::writeToConsole(const char* message, const char* location, const char* file, int level) {
  char tmp[MAX_LOG_ENTRY_SIZE];
  prepareEntry(tmp, "%s %s: %s -> %s [%s]\n", getDateAndTime(), getLevel(level), location, message, file);
  Serial.println(tmp);
}

void Logger::writeToMqtt(const char* message, const char* location, const char* file, int level) {
  char tmp[MAX_LOG_ENTRY_SIZE];
  prepareEntry(tmp, "{\"level\":\"%s\",\"location\":\"%s\", \"syslog_message\":\"%s\"}", getLevel(level), location, message);  
  #ifndef SKIP_MQTT
  mqtt.publish_debug(tmp);
  #endif

}

void Logger::writeToSyslog(const char* message, const char* location, const char* file, int level) {
#ifdef USE_SYSLOG
  if (message[0] == '{') {
    syslog(level, "{\"location\":\"%s\", \"syslog_message\":%s, \"file\":\"%s\", \"syslog_program\":\"%s\"}", location, message, file, APPLICATON_NAME);
  } else {
    syslog(level, "{\"location\":\"%s\", \"syslog_message\":\"%s\", \"file\":\"%s\", \"syslog_program\":\"%s\"}", location, message, file, APPLICATON_NAME);
  } 
#endif
}

/**
 Get current Date and Time
*/
char* Logger::getDateAndTime()
{
  static char result[6];
  sprintf(result, " %d",timer.getTicks());
  return result;
}

/**
Return event level as text
*/
const char* Logger::getLevel(const int level)
{ 
  const static char* priority[] = { "EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG" };
  return priority[level];
}

const char* Logger::exeptionToString(const char* message,...) {
  return message;
}


