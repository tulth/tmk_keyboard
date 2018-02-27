#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <core_pins.h>
#include <keyboard.h>
#include "suspend.h"
#include "usb_main.h"
#include "hook.h"
#include "led.h"
#include "host.h"
#include "host_driver_teensy3.h"
#include "usb_dev.h"
/* Main thread
 */

static uint8_t saved_led_state = 0;

int main(void)
{
  keyboard_setup();

  // is this needed?   while (!usb_configured()) /* wait */ ;

  host_set_driver(teensy3_driver());
  keyboard_init();
#ifdef SLEEP_LED_ENABLE
  sleep_led_init();
#endif
  led_set(host_keyboard_leds());
  while (1) {
    if (usb_is_sleeped()) {
      hook_usb_suspend_entry();
      while (usb_is_sleeped()) {
        hook_usb_suspend_loop();
      }
      hook_usb_wakeup();
    }

    keyboard_task();
  }
}

void bootloader_jump(void)
{
  _reboot_Teensyduino_();
}

void yield(void) {}

volatile uint32_t systick_millis_count;
void systick_isr(void)
{
  systick_millis_count++;
}

 __attribute__((weak))
void hook_usb_suspend_entry(void)
{
  saved_led_state = driver_keyboard_leds;
  driver_keyboard_leds = 0;
#ifdef SLEEP_LED_ENABLE
  sleep_led_enable();
#endif
  GPIOC_PCOR = (1<<5);  // deactivate teensy3 blinky led
}

__attribute__((weak))
void hook_usb_suspend_loop(void)
{
  suspend_power_down();
  if (suspend_wakeup_condition()) {
    usb_remote_wakeup();
  }
}

__attribute__((weak))
void hook_usb_wakeup(void)
{
  suspend_wakeup_init();
#ifdef SLEEP_LED_ENABLE
  sleep_led_disable();
#endif
  driver_keyboard_leds = saved_led_state;
}
