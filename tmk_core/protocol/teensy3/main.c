#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <core_pins.h>
#include <keyboard.h>
#include "suspend.h"
#include "usb_main.h"
#include "led.h"
#include "host.h"
#include "host_driver_teensy3.h"
/* Main thread
 */

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
    /* while (suspend) { */
    /*     suspend_power_down(); */
    /*     if (remote_wakeup && suspend_wakeup_condition()) { */
    /*         usb_remote_wakeup(); */
    /*     } */
    /* } */

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


