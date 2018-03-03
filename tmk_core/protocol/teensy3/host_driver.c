#include <string.h>  // for memcpy
#include <stdio.h>  // for debug printf
#include <usb_dev.h>
#include "host.h"
#include "host_driver_teensy3.h"

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
volatile uint8_t keyboard_protocol=1;

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
volatile uint8_t keyboard_idle_config=125;

// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
volatile uint8_t driver_keyboard_leds=0;

// count until idle timeout
uint8_t keyboard_idle_count=0;



/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

static host_driver_t driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};

host_driver_t *teensy3_driver(void)
{
  return &driver;
}

uint8_t keyboard_leds(void) {
  return driver_keyboard_leds;
}

#define TX_PACKET_LIMIT 4
// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 50

#if F_CPU == 240000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1600)
#elif F_CPU == 216000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1440)
#elif F_CPU == 192000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1280)
#elif F_CPU == 180000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1200)
#elif F_CPU == 168000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1100)
#elif F_CPU == 144000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 932)
#elif F_CPU == 120000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 764)
#elif F_CPU == 96000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 72000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 512)
#elif F_CPU == 48000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 262)
#endif
static uint8_t transmit_previous_timeout=0;
static void send_keyboard(report_keyboard_t *report)
{
  uint32_t wait_count=0;
  usb_packet_t *tx_packet;
  while (1) {
    if (!usb_configuration) {
      return;
    }
    if (usb_tx_packet_count(KEYBOARD_ENDPOINT) < TX_PACKET_LIMIT) {
      tx_packet = usb_malloc();
      if (tx_packet) break;
    }
    if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
      transmit_previous_timeout = 1;
      return;
    }
  }
  
#ifdef NKRO_ENABLE
  if (keyboard_nkro) {
      memcpy(tx_packet->buf, report, NKRO_SIZE);
      tx_packet->len = NKRO_SIZE;
      usb_tx(NKRO_ENDPOINT, tx_packet);
  } else 
#endif
    {
      memcpy(tx_packet->buf, report, KEYBOARD_SIZE);
      tx_packet->len = KEYBOARD_SIZE;
      usb_tx(KEYBOARD_ENDPOINT, tx_packet);
    }
}

static void send_mouse(report_mouse_t *report)
{
#ifdef MOUSE_ENABLE
  /* printf("report->x: %02X\n", report->x); */
  /* printf("report->y: %02X\n", report->y); */
  /* printf("report->v: %02X\n", report->v); */
  /* printf("report->h: %02X\n", report->h); */
  /* printf("report->buttons: %02X\n", report->buttons); */
  uint32_t wait_count=0;
  usb_packet_t *tx_packet;
  while (1) {
    if (!usb_configuration) {
      return;
    }
    if (usb_tx_packet_count(MOUSE_ENDPOINT) < TX_PACKET_LIMIT) {
      tx_packet = usb_malloc();
      if (tx_packet) break;
    }
    if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
      transmit_previous_timeout = 1;
      return;
    }
  }
  memcpy(tx_packet->buf, report, sizeof(report_mouse_t));
  tx_packet->len = sizeof(report_mouse_t);
  usb_tx(MOUSE_ENDPOINT, tx_packet);
#endif
}

void send_extra(uint8_t report_id, uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
  /* printf("extra report_id: %d\n", report_id); */
  /* printf("extra report data: %04X\n", data); */
  uint32_t wait_count=0;
  usb_packet_t *tx_packet;
  while (1) {
    if (!usb_configuration) {
      return;
    }
    if (usb_tx_packet_count(EXTRA_ENDPOINT) < TX_PACKET_LIMIT) {
      tx_packet = usb_malloc();
      if (tx_packet) break;
    }
    if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
      transmit_previous_timeout = 1;
      return;
    }
  }
  *(tx_packet->buf + 0) = report_id;
  *(tx_packet->buf + 1) = data & 0xFF;
  *(tx_packet->buf + 2) = (data>>8) & 0xFF;
  tx_packet->len = 3;
  usb_tx(EXTRA_ENDPOINT, tx_packet);
#endif
}


static void send_system(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
  return send_extra(REPORT_ID_SYSTEM, data);
#endif
}

static void send_consumer(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
  return send_extra(REPORT_ID_CONSUMER, data);
#endif
}

