#include <string.h>  // for memcpy
#include <stdio.h>  // for debug printf
#include <usb_dev.h>
#include "host_driver_teensy3.h"

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
  memcpy(tx_packet->buf, report, 8);
  tx_packet->len = 8;
  usb_tx(KEYBOARD_ENDPOINT, tx_packet);
}

static void send_mouse(report_mouse_t *report)
{
#ifdef MOUSE_ENABLE
  printf("report->x: %02X\n", report->x);
  printf("report->y: %02X\n", report->y);
  printf("report->v: %02X\n", report->v);
  printf("report->h: %02X\n", report->h);
  printf("report->buttons: %02X\n", report->buttons);
#endif
}

static void send_system(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
#endif
}

static void send_consumer(uint16_t data)
{
#ifdef EXTRAKEY_ENABLE
#endif
}
