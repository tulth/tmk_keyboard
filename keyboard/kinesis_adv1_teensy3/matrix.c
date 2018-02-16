#include <stdint.h>
#include <stdbool.h>
#include <matrix.h>
#include <host.h>  // for keyboard_nkro
#include <printf.h>
#include <util.h>  // for bitpop16
#include <usb_hid_listen.h>
#include "kinesis_adv1_teensy3.h"
#include "notes.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

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

#include <keymap.h>  // FIXME DELETEME FOR TEST
uint8_t matrix_scan(void)
{
  if ((millis() - blink_ms_elapsed) > 200) {
    GPIOC_PTOR = (1<<5);
    blink_ms_elapsed = millis();
  }

  keypos_t keypos;
  for (keypos.row=0; keypos.row<MATRIX_ROWS; keypos.row++) {
    select_row(keypos.row);
    matrix_row_t cols = read_cols();
    for (keypos.col=0; keypos.col<MATRIX_COLS; keypos.col++) {
      if (matrix_debouncing[keypos.row] != cols) {
        matrix_debouncing[keypos.row] = cols;
        debouncing = DEBOUNCE;
      }
    }
    
    if (debouncing) {
      if (--debouncing) {
        delay(1);
      } else {
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
          matrix[i] = matrix_debouncing[i];
        }
      }
    }
    
  }
  
  return 1;
}

bool matrix_is_modified(void)
{
  return debouncing == 0;
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
  delayMicroseconds(30);
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
