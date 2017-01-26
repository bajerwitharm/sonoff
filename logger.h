#pragma once
#include <cstdarg>
//#include <exception>
#include "syslog.h"
#include "global.h"

typedef int (*console_writter_ptr) (const char*);

#define FUNCTION_NAME __FUNCTION__

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__  " " STR((__LINE__)), '\\') + 1 : __FILE__  STR( (__LINE__)))
#define __FILE_AND_LINE__ __FILENAME__ 

#if L_LEVEL>LOG_CRIT
#define L_THROW(exception) {Logger::add(LOG_CRIT, FUNCTION_NAME, __FILE_AND_LINE__, Logger::exeptionToString(exception)); throw exception;}
#else
//#define L_THROW(exception) throw exception;
#endif


#if L_LEVEL>=LOG_ERR
#define L_ERROR(...) {Logger::add(LOG_ERR, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);} 
#else
#define L_ERROR(...) Logger::dummy(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#endif


#if L_LEVEL>=LOG_WARNING
#define L_WARNING(...) Logger::add(LOG_WARNING, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#else
#define L_WARNING(...) Logger::dummy(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#endif

#if L_LEVEL>=LOG_NOTICE
#define L_NOTICE(...) Logger::add(LOG_NOTICE, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#else
#define L_NOTICE(...) Logger::dummy(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#endif

#if L_LEVEL>=LOG_INFO
#define L_INFO(...) Logger::add(LOG_INFO, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#else
#define L_INFO(...) Logger::dummy(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#endif

#if L_LEVEL>=LOG_DEBUG
#define L_DEBUG(...) Logger::add(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#else
#define L_DEBUG(...) Logger::dummy(LOG_DEBUG, FUNCTION_NAME, __FILE_AND_LINE__, __VA_ARGS__);
#endif

class Logger
{
public:

  static void dummy(int level, const char* location, const char* file, const char * format, ...);
//  static const char* exeptionToString(std::exception except);
  static const char* exeptionToString(const char* message,...);
  static void prepareEntry( char* buffer, const char * format, ... );
  static console_writter_ptr console_writter;
#if L_LEVEL>=LOG_CRIT
  static void add(int level, const char* location, const char* file, const char * format, ...);
#endif
private:
  static char * getDateAndTime();
  static const char * getLevel(const int level);
  static void writeToConsole(const char * message, const char* location = "", const char* file = "", const int level = LOG_INFO);
  static void writeToMqtt(const char * message, const char* location = "", const char* file = "", const int level = LOG_INFO);
  static void writeToSyslog(const char * message, const char * location = "", const char* file = "", int level = LOG_INFO);
#if L_LEVEL>=LOG_CRIT
  static void storeEvent(const int level, const char* location, const char* file, const char *& format, va_list& argptr);
#endif

};



