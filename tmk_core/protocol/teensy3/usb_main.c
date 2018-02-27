/*
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#include <stdint.h>
#include <stdbool.h>
#include <kinetis.h>
#include <core_pins.h> // for delay
#include "usb_dev.h"
#include <usb_hid_listen.h>
#include "usb_main.h"

uint8_t keyboard_idle=125;

int8_t sendchar(uint8_t c)
{
  return usb_hid_listen_putchar(c);
}

void usb_remote_wakeup(void) {
  uint8_t prev_ctl = USB0_CTL;
  USB0_CTL |= USB_CTL_RESUME;
  delay(12);
  USB0_CTL = prev_ctl;
}

bool usb_is_sleeped(void)
{
  return usb_sleeped;
}
