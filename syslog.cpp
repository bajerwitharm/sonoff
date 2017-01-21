#include "global.h"
#ifdef USE_OWN_SYSLOG
#include <cstring>
#include <cstdlib>
#include <WiFiUdp.h>

WiFiUDP Udp;

int syslog(int level, const char * format, ...) {
  // send a reply, to the IP address and port that sent us the packet we received
  char buffer[MAX_LOG_ENTRY_SIZE];
  char* p_buffer = buffer;
  va_list args;
  va_start(args, format);
  p_buffer += sprintf(buffer, "<%d> %s ", level, HOST_NAME);
  vsnprintf(p_buffer, MAX_LOG_ENTRY_SIZE-3, format, args);
  va_end(args);

  Udp.beginPacket(SYSLOG_IP, SYSLOG_PORT);
  Udp.write(buffer);
  Udp.endPacket();
  
  return 0;
}
#else
void syslog(...) {

}
#endif


