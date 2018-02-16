#include <stdint.h>
#include <stdbool.h>
#include <led.h>
#include <core_pins.h>
#include "kinesis_adv1_teensy3.h"

void led_set(uint8_t usb_led)
{
  set_led_num_lock(usb_led & (1 << USB_LED_NUM_LOCK));
  set_led_caps_lock(usb_led & (1 << USB_LED_CAPS_LOCK));
  set_led_scroll_lock(usb_led & (1 << USB_LED_SCROLL_LOCK));
}
