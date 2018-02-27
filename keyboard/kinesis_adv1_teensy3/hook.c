#include "hook.h"
#include "kinesis_adv1_teensy3.h"

void hook_layer_change(uint32_t layer_state)
{
  if (layer_state == 0x000000) {
    set_led_keypad(false);
  } else {
    set_led_keypad(true);
  }
}

void hook_matrix_change(keyevent_t event)
{
  if (event.pressed) {
    if ((event.key.row == 0) ||
        (event.key.row == 4) ||
        (event.key.row == 8)) {
      kinesis_start_buzzer(5, 2000);
    }
  }
}

void hook_keyboard_loop(void)
{
  kinesis_buzzer_update();
}
