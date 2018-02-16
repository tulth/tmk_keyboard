#ifndef PROGMEM_H
#define PROGMEM_H 1

#if defined(__AVR__)
#   include <avr/pgmspace.h>
#elif defined(TEENSY3_PROTOCOL)
#   define PROGMEM
#   define pgm_read_byte(addr) (*(const uint8_t *)(addr))
#   define pgm_read_word(addr) ({               \
      typeof(addr) _addr = (addr);              \
      *(const uint16_t *)(_addr);         \
    })
#elif defined(__arm__)
#   define PROGMEM
#   define pgm_read_byte(p)     *((unsigned char*)p)
#   define pgm_read_word(p)     *((uint16_t*)p)
#endif

#endif
