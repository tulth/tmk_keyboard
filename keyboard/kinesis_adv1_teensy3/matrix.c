#include <stdint.h>
#include <stdbool.h>
#include <matrix.h>
#include <string.h>  // for memset
#include <host.h>  // for keyboard_nkro
#include <printf.h>
#include <util.h>  // for bitpop16
#include <usb_hid_listen.h>
#include "kinesis_adv1_teensy3.h"
#include "notes.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

matrix_row_t read_cols();
void init_cols(void);
void unselect_rows();
void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_clear(void)
{
  memset(matrix, 0, sizeof(matrix_row_t) * MATRIX_ROWS);
  memset(matrix_debouncing, 0, sizeof(matrix_row_t) * MATRIX_ROWS);
}

void matrix_init(void)
{
  kinesis_init();
  set_led_keypad(0);
#ifdef NKRO_ENABLE
  keyboard_nkro = false;  // don't boot in nkro mode
#endif
  notes_start();
  while (notes_busy()) {
    notes_update();
    kinesis_buzzer_update();
  }
}

unsigned long blink_ms_elapsed = 0;

bool _debounce_complete = false;
uint32_t debounce_timestamp = 0;

static inline void start_debounce_timer(void)
{
  debounce_timestamp = millis();
  _debounce_complete = false;
}

static inline uint32_t get_debounce_elapsed(void)
{
  return millis() - debounce_timestamp;
}

static inline bool is_debounce_done(void)
{
  if (_debounce_complete) {
    return true;
  }
  if (get_debounce_elapsed() > DEBOUNCE) {
    _debounce_complete = true;
    return true;
  }
  return false;
}

static inline void blink_update()
{
  if ((millis() - blink_ms_elapsed) > 200) {
    GPIOC_PTOR = (1<<5);
    blink_ms_elapsed = millis();
  }
}

#define ROW_STROBE_DELAY_US 30
uint8_t scan_row = 0;
bool row_strobe_not_read = true;
uint32_t row_strobe_delay_timestamp_us;
static inline void row_strobe_update()
{
  // strobe the row, then wait ROW_STROBE_DELAY_US (before reading the column values)
  // should give time for the matrix to settle between strobes
  select_row(scan_row);
  if ((micros() - row_strobe_delay_timestamp_us) > ROW_STROBE_DELAY_US) {
    row_strobe_not_read = false;
  }
}
static inline void col_read_update()
{
  matrix_row_t cols = read_cols();
  for (uint8_t scan_col=0; scan_col<MATRIX_COLS; scan_col++) {
    if (matrix_debouncing[scan_row] != cols) {
      matrix_debouncing[scan_row] = cols;
      start_debounce_timer();
    }
  }
    
  scan_row++;
  if(scan_row>=MATRIX_ROWS) {
    scan_row=0;
    if (is_debounce_done()) {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }
  row_strobe_not_read = true;
  row_strobe_delay_timestamp_us = micros();
}

uint8_t matrix_scan(void)
{
  blink_update();
  if (row_strobe_not_read) {
    row_strobe_update();
  } else {
    col_read_update();
  }
  return 1;
}

bool matrix_is_modified(void)
{
  return is_debounce_done();
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  matrix_row_t row_val;
  printf("\nr/c |9|8|7|6|5|4|3|2|1|0|\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    row_val = matrix_get_row(row);
    //    printf("      ---------------------\n");
    printf("%01X:  |%x|%x|%x|%x|%x|%x|%x|%x|%x|%x|\n",
           row,
           (row_val & (1 << 9)) != 0,
           (row_val & (1 << 8)) != 0,
           (row_val & (1 << 7)) != 0,
           (row_val & (1 << 6)) != 0,
           (row_val & (1 << 5)) != 0,
           (row_val & (1 << 4)) != 0,
           (row_val & (1 << 3)) != 0,
           (row_val & (1 << 2)) != 0,
           (row_val & (1 << 1)) != 0,
           (row_val & (1 << 0)) != 0
           );
  }
  // printf("      ---------------------\n");
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

matrix_row_t read_cols(void)
{
  return
    (0xFF & ~(GPIOD_PDIR << 0)) |
    (kinesis_keypad_button_depressed() ? (1 << 8): 0) |
    (kinesis_program_button_depressed() ? (1 << 9) : 0);
}

void init_cols(void)
{
  kinesis_init_cols();
}

void unselect_rows(void)
{
  kinesis_unselect_rows();
}

/* 16 rows supported, row in range 0-15 inclusive */
void select_row(uint8_t row)
{
  GPIOB_PCOR = (1 << 1);  /* enable 74ls138 output, active low */
  GPIOC_PCOR = (0x0F);  /* start all low */
  GPIOC_PSOR = (row & 0x0F);
}

void matrix_power_up(void) {}

void matrix_power_down(void) {}
