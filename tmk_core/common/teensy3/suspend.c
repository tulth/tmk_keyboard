#include <stdint.h>
#include <stdbool.h>
#include <core_pins.h>  // for delay
#include "suspend.h"
#include "action.h"
#include "matrix.h"

// unused
void suspend_idle(uint8_t timeout) {}

void suspend_power_down(void)
{
  delay(15);
}

bool suspend_wakeup_condition(void)
{
    matrix_power_up();
    for (uint8_t r = 0; r <  2 * MATRIX_ROWS; r++) {
      matrix_scan();
    }
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

void suspend_wakeup_init(void)
{
    matrix_clear();
    clear_keyboard();
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
}
