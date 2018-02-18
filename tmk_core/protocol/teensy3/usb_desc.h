#ifndef _usb_desc_h_
#define _usb_desc_h_

#include <usb/usb_descriptors.h>


#ifndef MANUFACTURER
#define MANUFACTURER    t.m.k.
#endif

#ifndef PRODUCT
#define PRODUCT         USB-HID keyboard (Teensy3-baremetal)
#endif

#ifndef VENDOR_ID
#define VENDOR_ID       0xFEED
#endif

#ifndef PRODUCT_ID
#define PRODUCT_ID      0xBEEF
#endif

#ifndef SERIAL_NUMBER
#define SERIAL_NUMBER   000001
#endif

#define EP0_SIZE           8

#define KEYBOARD_INTERFACE     0
#define KEYBOARD_ENDPOINT      1
#define KEYBOARD_SIZE          8
#define MOUSE_INTERFACE        1
#define MOUSE_ENDPOINT         2
#define MOUSE_SIZE             8
#define HID_LISTEN_INTERFACE   2
#define HID_LISTEN_ENDPOINT    3
#define HID_LISTEN_SIZE        32
#define EXTRA_INTERFACE        3
#define EXTRA_ENDPOINT         4
#define EXTRA_SIZE             8

/* #define NKRO_INTERFACE         0 */
/* #define NKRO_ENDPOINT          1 */
/* #define NKRO_SIZE              8 */

#define NUM_ENDPOINTS          5  // is this right???
#define NUM_INTERFACES         4  // is this right???
#define NUM_USB_BUFFERS        24


typedef struct {
  usb_descriptor_configuration_t config;
  usb_descriptor_interface_t keyboard_6kro_if;
  usb_descriptor_class_hid_t keyboard_6kro_class;
  usb_descriptor_endpoint_t keyboard_6kro_endpoint;
#ifdef MOUSE_ENABLE
  usb_descriptor_interface_t mouse_if;
  usb_descriptor_class_hid_t mouse_class;
  usb_descriptor_endpoint_t mouse_endpoint;
#endif
#ifdef CONSOLE_ENABLE
  usb_descriptor_interface_t hid_listen_if;
  usb_descriptor_class_hid_t hid_listen_class;
  usb_descriptor_endpoint_t hid_listen_endpoint;
#endif
#ifdef EXTRAKEY_ENABLE
  usb_descriptor_interface_t extra_if;
  usb_descriptor_class_hid_t extra_class;
  usb_descriptor_endpoint_t extra_endpoint;
#endif
} __attribute__((packed)) usb_config_t;

typedef struct {
	uint16_t	wValue;
	uint16_t	wIndex;
	const uint8_t	*addr;
	uint16_t	length;
} usb_descriptor_list_t;

extern const uint8_t usb_endpoint_config_table[NUM_ENDPOINTS];
extern const usb_descriptor_list_t usb_descriptor_list[];
extern usb_config_t config_descriptor;

#endif
