#include "timer1s.h"
#include "Arduino.h"
static volatile long ticks = 0;

void inline handler (void) {
  ticks++;
  timer0_write(ESP.getCycleCount() + TRIGGER_TIME);
}

void Timer1s::setup() {
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(handler);
  timer0_write(ESP.getCycleCount() + TRIGGER_TIME);
  interrupts(); // See more at: http://www.esp8266.com/viewtopic.php?f=8&t=4865#sthash.eogrRK4G.dpuf
}


void Timer1s::stop() {
  timer0_detachInterrupt();
}

long Timer1s::getTicks() {
  return ticks;
}


