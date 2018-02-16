#include "timer.h"
#include "core_pins.h"

void timer_init(void) {}

void timer_clear(void) {}

uint16_t timer_read(void)
{
  return (uint16_t)(millis() & 0xFFFF);
}

uint32_t timer_read32(void)
{
  return millis();
}

uint16_t timer_elapsed(uint16_t last)
{
  return (uint16_t)(timer_elapsed32(last) & 0xFFFF);
}

uint32_t timer_elapsed32(uint32_t last)
{
  return millis() - last;
}
