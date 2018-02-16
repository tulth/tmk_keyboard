/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if F_CPU >= 20000000

#define USB_DESC_LIST_DEFINE
#include "usb_desc.h"
#ifdef NUM_ENDPOINTS
#include "usb_names.h"
#include "kinetis.h"
#include <nonstd.h>

// USB Descriptors are binary data which the USB host reads to
// automatically detect a USB device's capabilities.  The format
// and meaning of every field is documented in numerous USB
// standards.  When working with USB descriptors, despite the
// complexity of the standards and poor writing quality in many
// of those documents, remember descriptors are nothing more
// than constant binary data that tells the USB host what the
// device can do.  Computers will load drivers based on this data.
// Those drivers then communicate on the endpoints specified by
// the descriptors.

// To configure a new combination of interfaces or make minor
// changes to existing configuration (eg, change the name or ID
// numbers), usually you would edit "usb_desc.h".  This file
// is meant to be configured by the header, so generally it is
// only edited to add completely new USB interfaces or features.



// **************************************************************
//   USB Device
// **************************************************************

#define LSB(n) ((n) & 255)
#define MSB(n) (((n) >> 8) & 255)

// USB Device Descriptor.  The USB host reads this first, to learn
// what type of device is connected.
static uint8_t device_descriptor[] = {
        18,                                     // bLength
        1,                                      // bDescriptorType
        0x10, 0x01,                             // bcdUSB
#ifdef DEVICE_CLASS
        DEVICE_CLASS,                           // bDeviceClass
#else
	0,
#endif
#ifdef DEVICE_SUBCLASS
        DEVICE_SUBCLASS,                        // bDeviceSubClass
#else
	0,
#endif
#ifdef DEVICE_PROTOCOL
        DEVICE_PROTOCOL,                        // bDeviceProtocol
#else
	0,
#endif
        EP0_SIZE,                               // bMaxPacketSize0
        LSB(VENDOR_ID), MSB(VENDOR_ID),         // idVendor
        LSB(PRODUCT_ID), MSB(PRODUCT_ID),       // idProduct
#ifdef BCD_DEVICE
	LSB(BCD_DEVICE), MSB(BCD_DEVICE),       // bcdDevice
#else
        0x00, 0x02,
#endif
        1,                                      // iManufacturer
        2,                                      // iProduct
        3,                                      // iSerialNumber
        1                                       // bNumConfigurations
};

// These descriptors must NOT be "const", because the USB DMA
// has trouble accessing flash memory with enough bandwidth
// while the processor is executing from flash.



// **************************************************************
//   HID Report Descriptors
// **************************************************************

// Each HID interface needs a special report descriptor that tells
// the meaning and format of the data.

// Keyboard Protocol 1, HID 1.11 spec, Appendix B, page 59-60
static uint8_t keyboard_report_desc[] = {
        0x05, 0x01,          // Usage Page (Generic Desktop),
        0x09, 0x06,          // Usage (Keyboard),
        0xA1, 0x01,          // Collection (Application),
        0x75, 0x01,          //   Report Size (1),
        0x95, 0x08,          //   Report Count (8),
        0x05, 0x07,          //   Usage Page (Key Codes),
        0x19, 0xE0,          //   Usage Minimum (224),
        0x29, 0xE7,          //   Usage Maximum (231),
        0x15, 0x00,          //   Logical Minimum (0),
        0x25, 0x01,          //   Logical Maximum (1),
        0x81, 0x02,          //   Input (Data, Variable, Absolute), ;Modifier byte
        0x95, 0x01,          //   Report Count (1),
        0x75, 0x08,          //   Report Size (8),
        0x81, 0x03,          //   Input (Constant),                 ;Reserved byte
        0x95, 0x05,          //   Report Count (5),
        0x75, 0x01,          //   Report Size (1),
        0x05, 0x08,          //   Usage Page (LEDs),
        0x19, 0x01,          //   Usage Minimum (1),
        0x29, 0x05,          //   Usage Maximum (5),
        0x91, 0x02,          //   Output (Data, Variable, Absolute), ;LED report
        0x95, 0x01,          //   Report Count (1),
        0x75, 0x03,          //   Report Size (3),
        0x91, 0x03,          //   Output (Constant),                 ;LED report padding
        0x95, 0x06,    //   Report Count (6),
        0x75, 0x08,          //   Report Size (8),
        0x15, 0x00,          //   Logical Minimum (0),
        0x25, 0xFF,    //   Logical Maximum(255),
        0x05, 0x07,          //   Usage Page (Key Codes),
        0x19, 0x00,          //   Usage Minimum (0),
        0x29, 0xFF,          //   Usage Maximum (255),
        0x81, 0x00,          //   Input (Data, Array),
        0xC0                 // End Collection
};

// Mouse Protocol 1, HID 1.11 spec, Appendix B, page 59-60, with wheel extension
static uint8_t mouse_report_desc[] = {
    /* mouse */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    //0x85, REPORT_ID_MOUSE,         //   REPORT_ID (1)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
                                   // ----------------------------  Buttons
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x05,                    //     USAGE_MAXIMUM (Button 5)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x05,                    //     REPORT_COUNT (5)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x03,                    //     REPORT_SIZE (3)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
                                   // ----------------------------  X,Y position
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
                                   // ----------------------------  Vertical wheel
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)        - reset physical
    0x45, 0x00,                    //     PHYSICAL_MAXIMUM (0)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
                                   // ----------------------------  Horizontal wheel
    0x05, 0x0c,                    //     USAGE_PAGE (Consumer Devices)
    0x0a, 0x38, 0x02,              //     USAGE (AC Pan)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
};

static uint8_t hid_listen_report_desc[] = {
	0x06, 0x31, 0xFF,			// Usage Page 0xFF31 (vendor defined)
	0x09, 0x74,				// Usage 0x74
	0xA1, 0x53,				// Collection 0x53
	0x75, 0x08,				// report size = 8 bits
	0x15, 0x00,				// logical minimum = 0
	0x26, 0xFF, 0x00,			// logical maximum = 255
	0x95, HID_LISTEN_TX_SIZE,			// report count
	0x09, 0x75,				// usage
	0x81, 0x02,				// Input (array)
	0xC0					// end collection
};

// audio controls & system controls
#define REPORT_ID_SYSTEM 2
#define REPORT_ID_CONSUMER 3
static uint8_t keymedia_report_desc[] = {
    /* system control */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x80,                    // USAGE (System Control)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, REPORT_ID_SYSTEM,        //   REPORT_ID (2)
    0x15, 0x01,                    //   LOGICAL_MINIMUM (0x1)
    0x26, 0xb7, 0x00,              //   LOGICAL_MAXIMUM (0xb7)
    0x19, 0x01,                    //   USAGE_MINIMUM (0x1)
    0x29, 0xb7,                    //   USAGE_MAXIMUM (0xb7)
    0x75, 0x10,                    //   REPORT_SIZE (16)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x81, 0x00,                    //   INPUT (Data,Array,Abs)
    0xc0,                          // END_COLLECTION
    /* consumer */
    0x05, 0x0c,                    // USAGE_PAGE (Consumer Devices)
    0x09, 0x01,                    // USAGE (Consumer Control)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, REPORT_ID_CONSUMER,      //   REPORT_ID (3)
    0x15, 0x01,                    //   LOGICAL_MINIMUM (0x1)
    0x26, 0x9c, 0x02,              //   LOGICAL_MAXIMUM (0x29c)
    0x19, 0x01,                    //   USAGE_MINIMUM (0x1)
    0x2a, 0x9c, 0x02,              //   USAGE_MAXIMUM (0x29c)
    0x75, 0x10,                    //   REPORT_SIZE (16)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x81, 0x00,                    //   INPUT (Data,Array,Abs)
    0xc0,                          // END_COLLECTION
};

#ifdef NKRO_ENABLE
// for NKRO
static uint8_t keyboard2_report_desc[] = {
        0x05, 0x01,                     // Usage Page (Generic Desktop),
        0x09, 0x06,                     // Usage (Keyboard),
        0xA1, 0x01,                     // Collection (Application),
        // bitmap of modifiers
        0x75, 0x01,                     //   Report Size (1),
        0x95, 0x08,                     //   Report Count (8),
        0x05, 0x07,                     //   Usage Page (Key Codes),
        0x19, 0xE0,                     //   Usage Minimum (224),
        0x29, 0xE7,                     //   Usage Maximum (231),
        0x15, 0x00,                     //   Logical Minimum (0),
        0x25, 0x01,                     //   Logical Maximum (1),
        0x81, 0x02,                     //   Input (Data, Variable, Absolute), ;Modifier byte
        // LED output report
        0x95, 0x05,                     //   Report Count (5),
        0x75, 0x01,                     //   Report Size (1),
        0x05, 0x08,                     //   Usage Page (LEDs),
        0x19, 0x01,                     //   Usage Minimum (1),
        0x29, 0x05,                     //   Usage Maximum (5),
        0x91, 0x02,                     //   Output (Data, Variable, Absolute),
        0x95, 0x01,                     //   Report Count (1),
        0x75, 0x03,                     //   Report Size (3),
        0x91, 0x03,                     //   Output (Constant),
        // bitmap of keys
#ifdef NKRO_ENABLE
        0x95, KBD2_REPORT_KEYS*8,       //   Report Count (),
        0x75, 0x01,                     //   Report Size (1),
        0x15, 0x00,                     //   Logical Minimum (0),
        0x25, 0x01,                     //   Logical Maximum(1),
        0x05, 0x07,                     //   Usage Page (Key Codes),
        0x19, 0x00,                     //   Usage Minimum (0),
        0x29, KBD2_REPORT_KEYS*8-1,     //   Usage Maximum (),
        0x81, 0x02,                     //   Input (Data, Variable, Absolute),
        0xc0                            // End Collection
#endif
};
#endif

// **************************************************************
//   USB Descriptor Sizes
// **************************************************************
#define KEYBOARD_HID_DESC_NUM                0
#define KEYBOARD_HID_DESC_OFFSET             (9+(9+9+7)*KEYBOARD_HID_DESC_NUM+9)

#define MOUSE_HID_DESC_NUM           (KEYBOARD_HID_DESC_NUM + 1)
#define MOUSE_HID_DESC_OFFSET        (9+(9+9+7)*MOUSE_HID_DESC_NUM+9)

#define HID_LISTEN_HID_DESC_NUM              (MOUSE_HID_DESC_NUM + 1)
#define HID_LISTEN_HID_DESC_OFFSET           (9+(9+9+7)*HID_LISTEN_HID_DESC_NUM+9)

#define KEYMEDIA_HID_DESC_NUM           (HID_LISTEN_HID_DESC_NUM + 1)
#define KEYMEDIA_HID_DESC_OFFSET        (9+(9+9+7)*KEYMEDIA_HID_DESC_NUM+9)

#ifdef NKRO_ENABLE
#define KBD2_HID_DESC_NUM            (KEYMEDIA_HID_DESC_NUM + 1)
#define KBD2_HID_DESC_OFFSET         (9+(9+9+7)*KEYMEDIA_HID_DESC_NUM+9)
#define NUM_INTERFACES                  (KBD2_HID_DESC_NUM + 1)
#define CONFIG_DESC_SIZE               (9+(9+9+7)*NUM_INTERFACES)
#else
#define NUM_INTERFACES                  (KEYMEDIA_HID_DESC_NUM + 1)
#define CONFIG_DESC_SIZE               (9+(9+9+7)*NUM_INTERFACES)
#endif



// **************************************************************
//   USB Configuration
// **************************************************************

// USB Configuration Descriptor.  This huge descriptor tells all
// of the devices capbilities.
static uint8_t config_descriptor[CONFIG_DESC_SIZE] = {
                                       // configuration descriptor, USB spec 9.6.3, page 264-266, Table 9-10
  9,                                   // bLength;
  2,                                   // bDescriptorType;
  LSB(CONFIG_DESC_SIZE),               // wTotalLength
  MSB(CONFIG_DESC_SIZE),
  5,                                   // bNumInterfaces
  1,                                   // bConfigurationValue
  0,                                   // iConfiguration
  0xA0,                                // bmAttributes: bus powered, remote wakeup
  40,                                  // bMaxPower.  Kinesis says 64 ma, so 64 + margin = 80, in 2 mA steps

                                       // KEYBOARD 6kro
                                       // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
  9,                                   // bLength
  4,                                   // bDescriptorType
  KEYBOARD_INTERFACE,                  // bInterfaceNumber
  0,                                   // bAlternateSetting
  1,                                   // bNumEndpoints
  0x03,                                // bInterfaceClass (0x03 = HID)
  0x01,                                // bInterfaceSubClass (0x01 = Boot)
  0x01,                                // bInterfaceProtocol (0x01 = Keyboard)
  0,                                   // iInterface
                                       // HID interface descriptor, HID 1.11 spec, section 6.2.1
  9,                                   // bLength
  0x21,                                // bDescriptorType
  0x11, 0x01,                          // bcdHID
  0,                                   // bCountryCode
  1,                                   // bNumDescriptors
  0x22,                                // bDescriptorType
  LSB(sizeof(keyboard_report_desc)),   // wDescriptorLength
  MSB(sizeof(keyboard_report_desc)),
                                       // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
  7,                                   // bLength
  5,                                   // bDescriptorType
  KEYBOARD_ENDPOINT | 0x80,            // bEndpointAddress
  0x03,                                // bmAttributes (0x03=intr)
  KEYBOARD_SIZE, 0,                    // wMaxPacketSize
  10,                                  // bInterval

                                       // MOUSE
                                       // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
  9,                                   // bLength
  4,                                   // bDescriptorType
  MOUSE_INTERFACE,                     // bInterfaceNumber
  0,                                   // bAlternateSetting
  1,                                   // bNumEndpoints
  0x03,                                // bInterfaceClass (0x03 = HID)
  0x01,                                // bInterfaceSubClass (0x01 = Boot)
  0x02,                                // bInterfaceProtocol (0x02 = Mouse)
  0,                                   // iInterface
                                       // HID interface descriptor, HID 1.11 spec, section 6.2.1
  9,                                   // bLength
  0x21,                                // bDescriptorType
  0x11, 0x01,                          // bcdHID
  0,                                   // bCountryCode
  1,                                   // bNumDescriptors
  0x22,                                // bDescriptorType
  LSB(sizeof(mouse_report_desc)),      // wDescriptorLength
  MSB(sizeof(mouse_report_desc)),
                                       // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
  7,                                   // bLength
  5,                                   // bDescriptorType
  MOUSE_ENDPOINT | 0x80,               // bEndpointAddress
  0x03,                                // bmAttributes (0x03=intr)
  MOUSE_SIZE, 0,                       // wMaxPacketSize
  10,                                  // bInterval

                                       // HID LISTEN (debug interface)
                                       // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
  9,				       // bLength
  4,				       // bDescriptorType
  HID_LISTEN_INTERFACE,		       // bInterfaceNumber
  0,				       // bAlternateSetting
  2,				       // bNumEndpoints
  0x03,				       // bInterfaceClass (0x03 = HID)
  0x00,				       // bInterfaceSubClass
  0x00,				       // bInterfaceProtocol
  0,				       // iInterface
                                       // HID descriptor, HID 1.11 spec, section 6.2.1
  9,				       // bLength
  0x21,				       // bDescriptorType
  0x11, 0x01,			       // bcdHID
  0,				       // bCountryCode
  1,				       // bNumDescriptors
  0x22,				       // bDescriptorType
  LSB(sizeof(hid_listen_report_desc)), // wDescriptorLength
  MSB(sizeof(hid_listen_report_desc)),
                                       // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
  7,				       // bLength
  5,				       // bDescriptorType
  HID_LISTEN_TX_ENDPOINT | 0x80,       // bEndpointAddress
  0x03,				       // bmAttributes (0x03=intr)
  HID_LISTEN_TX_SIZE, 0,	       // wMaxPacketSize
  1,				       // bInterval

                                       // MEDIA KEYS (media and system control keys)
                                       // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
  9,                                   // bLength
  4,                                   // bDescriptorType
  KEYMEDIA_INTERFACE,                  // bInterfaceNumber
  0,                                   // bAlternateSetting
  1,                                   // bNumEndpoints
  0x03,                                // bInterfaceClass (0x03 = HID)
  0x00,                                // bInterfaceSubClass
  0x00,                                // bInterfaceProtocol
  0,                                   // iInterface
                                       // HID interface descriptor, HID 1.11 spec, section 6.2.1
  9,                                   // bLength
  0x21,                                // bDescriptorType
  0x11, 0x01,                          // bcdHID
  0,                                   // bCountryCode
  1,                                   // bNumDescriptors
  0x22,                                // bDescriptorType
  LSB(sizeof(keymedia_report_desc)),   // wDescriptorLength
  MSB(sizeof(keymedia_report_desc)),
                                       // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
  7,                                   // bLength
  5,                                   // bDescriptorType
  KEYMEDIA_ENDPOINT | 0x80,            // bEndpointAddress
  0x03,                                // bmAttributes (0x03=intr)
  KEYMEDIA_SIZE, 0,                    // wMaxPacketSize
  10,                                  // bInterval
#ifdef NKRO_ENABLE
                                       // NKRO (n-key rollover) keyboard interface
  9,				       // bLength
  4,				       // bDescriptorType
  KBD2_INTERFACE,		       // bInterfaceNumber
  0,				       // bAlternateSetting
  1,				       // bNumEndpoints
  0x03,				       // bInterfaceClass (0x03 = HID)
  0x00,				       // bInterfaceSubClass (0x01 = Boot)
  0x00,				       // bInterfaceProtocol (0x01 = Keyboard)
  0,				       // iInterface
                                       // HID descriptor, HID 1.11 spec, section 6.2.1
  9,				       // bLength
  0x21,				       // bDescriptorType
  0x11, 0x01,			       // bcdHID
  0,				       // bCountryCode
  1,				       // bNumDescriptors
  0x22,				       // bDescriptorType
  LSB(sizeof(keyboard2_report_desc)),  // wDescriptorLength
  MSB(sizeof(keyboard2_report_desc)),
                                       // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
  7,				       // bLength
  5,				       // bDescriptorType
  KBD2_ENDPOINT | 0x80,		       // bEndpointAddress
  0x03,				       // bmAttributes (0x03=intr)
  KBD2_SIZE, 0,			       // wMaxPacketSize
  1,				       // bInterval
#endif        
};


// **************************************************************
//   String Descriptors
// **************************************************************

// The descriptors above can provide human readable strings,
// referenced by index numbers.  These descriptors are the
// actual string data

/* defined in usb_names.h
struct usb_string_descriptor_struct {
        uint8_t bLength;
        uint8_t bDescriptorType;
        uint16_t wString[];
};
*/

extern struct usb_string_descriptor_struct usb_string_manufacturer_name
        __attribute__ ((weak, alias("usb_string_manufacturer_name_default")));
extern struct usb_string_descriptor_struct usb_string_product_name
        __attribute__ ((weak, alias("usb_string_product_name_default")));
extern struct usb_string_descriptor_struct usb_string_serial_number
        __attribute__ ((weak, alias("usb_string_serial_number_default")));

struct usb_string_descriptor_struct string0 = {
        4,
        3,
        {0x0409}
};

struct usb_string_descriptor_struct usb_string_manufacturer_name_default = {
        2 + MANUFACTURER_NAME_LEN * 2,
        3,
        MANUFACTURER_NAME
};
struct usb_string_descriptor_struct usb_string_product_name_default = {
	2 + PRODUCT_NAME_LEN * 2,
        3,
        PRODUCT_NAME
};
struct usb_string_descriptor_struct usb_string_serial_number_default = {
        12,
        3,
        {0,0,0,0,0,0,0,0,0,0}
};

void usb_init_serialnumber(void)
{
	char buf[11];
	uint32_t i, num;

	__disable_irq();
#if defined(HAS_KINETIS_FLASH_FTFA) || defined(HAS_KINETIS_FLASH_FTFL)
	FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
	FTFL_FCCOB0 = 0x41;
	FTFL_FCCOB1 = 15;
	FTFL_FSTAT = FTFL_FSTAT_CCIF;
	while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
	num = *(uint32_t *)&FTFL_FCCOB7;
#elif defined(HAS_KINETIS_FLASH_FTFE)
	kinetis_hsrun_disable();
	FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
	*(uint32_t *)&FTFL_FCCOB3 = 0x41070000;
	FTFL_FSTAT = FTFL_FSTAT_CCIF;
	while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
	num = *(uint32_t *)&FTFL_FCCOBB;
	kinetis_hsrun_enable();
#endif
	__enable_irq();
	// add extra zero to work around OS-X CDC-ACM driver bug
	if (num < 10000000) num = num * 10;
	ultoa(num, buf, 10);
	for (i=0; i<10; i++) {
		char c = buf[i];
		if (!c) break;
		usb_string_serial_number_default.wString[i] = c;
	}
	usb_string_serial_number_default.bLength = i * 2 + 2;
}


// **************************************************************
//   Descriptors List
// **************************************************************

// This table provides access to all the descriptor data above.

const usb_descriptor_list_t usb_descriptor_list[] = {
	//wValue, wIndex, address,          length
        // DEVICE descriptor
	{0x0100, 0x0000, device_descriptor, sizeof(device_descriptor)},
        // CONFIGURATION descriptor
	{0x0200, 0x0000, config_descriptor, sizeof(config_descriptor)},
        // HID/REPORT descriptors
        {0x2200, KEYBOARD_INTERFACE, keyboard_report_desc, sizeof(keyboard_report_desc)},
	{0x2100, KEYBOARD_INTERFACE, config_descriptor+KEYBOARD_HID_DESC_OFFSET, 9},
	{0x2200, MOUSE_INTERFACE, mouse_report_desc, sizeof(mouse_report_desc)},
	{0x2100, MOUSE_INTERFACE, config_descriptor+MOUSE_HID_DESC_OFFSET, 9},
	{0x2200, HID_LISTEN_INTERFACE, hid_listen_report_desc, sizeof(hid_listen_report_desc)},
	{0x2100, HID_LISTEN_INTERFACE, config_descriptor+HID_LISTEN_HID_DESC_OFFSET, 9},
	{0x2200, KEYMEDIA_INTERFACE, keymedia_report_desc, sizeof(keymedia_report_desc)},
	{0x2100, KEYMEDIA_INTERFACE, config_descriptor+KEYMEDIA_HID_DESC_OFFSET, 9},
#ifdef NKRO_ENABLE
	{0x2200, KBD2_INTERFACE, keyboard2_report_desc, sizeof(keyboard2_report_desc)},
	{0x2100, KBD2_INTERFACE, config_descriptor+KBD2_HID_DESC_OFFSET, 9},
#endif
        {0x0300, 0x0000, (const uint8_t *)&string0, 0},
        {0x0301, 0x0409, (const uint8_t *)&usb_string_manufacturer_name, 0},
        {0x0302, 0x0409, (const uint8_t *)&usb_string_product_name, 0},
        {0x0303, 0x0409, (const uint8_t *)&usb_string_serial_number, 0},
	{0, 0, NULL, 0}
};


// **************************************************************
//   Endpoint Configuration
// **************************************************************
const uint8_t usb_endpoint_config_table[NUM_ENDPOINTS] =
{
  ENDPOINT_TRANSIMIT_ONLY, // kbd, 6kro
  ENDPOINT_TRANSIMIT_ONLY, // mouse
  ENDPOINT_TRANSIMIT_ONLY, // hid listen (debug)
  ENDPOINT_TRANSIMIT_ONLY, // media keys 
  ENDPOINT_TRANSIMIT_ONLY, // kbd, nkro
};


#endif // NUM_ENDPOINTS
#endif // F_CPU >= 20 MHz
