#include <stdint.h>
#include <stdbool.h>
#include <core_pins.h>
#include "kinesis_adv1_teensy3.h"

void kinesis_led_config(void)
{
  /* teensy led */
  PORTC_PCR5 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOC_PDDR |= (1<<5); 
  /* num lock led */
  PORTC_PCR4 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOC_PDDR |= (1<<4); 
  /* caps lock led */
  PORTC_PCR7 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOC_PDDR |= (1<<7); 
  /* scroll led */
  PORTB_PCR2 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOB_PDDR |= (1<<2); 
  /* keypad led */
  PORTC_PCR6 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOC_PDDR |= (1<<6); 
}

static unsigned long buzzer_duration_ms = 0;
static unsigned long buzzer_halfperiod_us;
static unsigned long buzzer_duration_elapsed_ms;
static unsigned long buzzer_halfperiod_elapsed_us;

bool kinesis_buzzer_busy(void)
{
  /* printf("buzzer_duration_ms %d\n", buzzer_duration_ms); */
  return buzzer_duration_ms > 0;
}

void kinesis_buzzer_config(void)
{
  /* buzzer pin */
  PORTB_PCR0 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOB_PDDR |= (1<<0);
  buzzer_duration_ms = 0;
  buzzer_halfperiod_us = 0;
}

void kinesis_start_buzzer(unsigned long buzz_duration_ms, unsigned long buzz_halfperiod_us)
{
  buzzer_duration_ms = buzz_duration_ms;
  buzzer_halfperiod_us = buzz_halfperiod_us;
  buzzer_duration_elapsed_ms = millis();  
  buzzer_halfperiod_elapsed_us = micros();  
}

static inline void kinesis_set_buzzer_pin(bool val)
{
  if (val) {
    GPIOB_PSOR = (1<<0);
  } else {
    GPIOB_PCOR = (1<<0);
  }
}

void kinesis_buzzer_update(void)
{
  if (buzzer_duration_ms <= 0) {
    return;
  }
  /* printf("buzzer_elapsed %d\n", millis()-buzzer_duration_elapsed_ms); */
  if ((millis()-buzzer_duration_elapsed_ms) <= buzzer_duration_ms) {
    if ((micros() - buzzer_halfperiod_elapsed_us) >= buzzer_halfperiod_us) {
      buzzer_halfperiod_elapsed_us = micros();  
      kinesis_toggle_buzzer_pin();
    }
  } else {
    buzzer_duration_ms = 0;
    kinesis_set_buzzer_pin(0);
  }
}


void kinesis_init_cols(void)
{
  /* init matrix inputs */
  PORTD_PCR0 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR1 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR2 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR3 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR4 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR5 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR6 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  PORTD_PCR7 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  GPIOD_PDDR &= ~(0xFF); 
  /* keypad button */
  PORTA_PCR12 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  GPIOA_PDDR &= ~(1<<12);
  /* program button */
  PORTA_PCR13 |= PORT_PCR_MUX(1) | PORT_PCR_PE | PORT_PCR_PS; 
  GPIOA_PDDR &= ~(1<<13);
}


void kinesis_init_rows(void)
{
  /* 74ls138 select */
  /* 74ls138 c */
  /* 74ls138 b */
  /* 74ls138 a */
  PORTC_PCR0 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  PORTC_PCR1 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  PORTC_PCR2 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  PORTC_PCR3 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); 
  GPIOC_PDDR |= (0x0F); 
  GPIOC_PCOR = (0x0F);  /* start low */
  /* 74ls138 output enable active low */
  PORTB_PCR1 |= PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
  GPIOB_PDDR |= (1 << 1); 
}

void kinesis_unselect_rows(void)
{
  GPIOB_PSOR = (1 << 1);  /* disable 74ls138 output, active low */
}

void kinesis_init(void)
{
  kinesis_led_config();
  kinesis_buzzer_config();
  kinesis_init_cols();
  kinesis_init_rows();
  kinesis_unselect_rows();
}

