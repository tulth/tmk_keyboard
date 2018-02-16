#ifndef KINESIS_ADV1_TEENSY3_H
#define KINESIS_ADV1_TEENSY3_H

#include <stdint.h>
#include <stdbool.h>
#include <core_pins.h>

#ifdef __cplusplus
extern "C" {
#endif

void kinesis_init(void);
void kinesis_init_cols(void);
void kinesis_unselect_rows(void);

static inline void set_led_teensy(bool val)
{
  if (val != 0) {
    /* usb_hid_listen_write("set_led_teensy\n", 23); */
    GPIOC_PSOR = (1<<5);
  } else {
    GPIOC_PCOR = (1<<5);
  }
}

static inline void set_led_num_lock(bool val)
{
  if (val != 0) {
    /* usb_hid_listen_write("set_led_num_lock\n", 25); */
    GPIOC_PCOR = (1<<4);
  } else {
    GPIOC_PSOR = (1<<4);
  }
}

static inline void set_led_caps_lock(bool val)
{
  if (val != 0) {
    /* usb_hid_listen_write("set_led_caps_lock\n", 26); */
    GPIOC_PCOR = (1<<7);
  } else {
    GPIOC_PSOR = (1<<7);
  }
}

static inline void set_led_scroll_lock(bool val)
{
  if (val != 0) {
    /* usb_hid_listen_write("set_led_scroll_lock\n", 28); */
    GPIOB_PCOR = (1<<2);
  } else {
    GPIOB_PSOR = (1<<2);
  }
}

static inline void set_led_keypad(bool val)
{
  if (val != 0) {
    /* usb_hid_listen_write("set_led_keypad\n", 23); */
    GPIOC_PCOR = (1<<6);
  } else {
    GPIOC_PSOR = (1<<6);
  }
}

static inline bool kinesis_keypad_button_depressed(void)
{
  return (GPIOA_PDIR & (1 << 12)) == 0;
}

static inline bool kinesis_program_button_depressed(void)
{
  return (GPIOA_PDIR & (1 << 13)) == 0;
}


void kinesis_start_buzzer(unsigned long buzz_duration_ms, unsigned long buzz_halfperiod_us);
bool kinesis_buzzer_busy(void);
void kinesis_buzzer_update(void);
  
#ifdef __cplusplus
}
#endif


#endif
