#ifndef _usb_reports_h_
#define _usb_reports_h_

#include <stdint.h>

#define USB_USAGE_PAGE_HID_UNDEF 0x00
#define USB_USAGE_PAGE_HID_GENERIC_DESKTOP_CONTROLS 0x01

#define USB_REPORT_ITEM_MAIN_COLLECTION_APPLICATION 0xA1

// generated using
// cat keyboard_6kro_usage_report_descriptor.xml  | hidrd-convert -i xml -o code
#define USB_REPORT_DESCRIPTOR_KEYBOARD_6KRO_VAL()        \
  0x05, 0x01, /*  Usage Page (Desktop),               */ \
  0x09, 0x06, /*  Usage (Keyboard),                   */ \
  0xA1, 0x01, /*  Collection (Application),           */ \
  0x05, 0x07, /*      Usage Page (Keyboard),          */ \
  0x19, 0xE0, /*      Usage Minimum (KB Leftcontrol), */ \
  0x29, 0xE7, /*      Usage Maximum (KB Right GUI),   */ \
  0x14,       /*      Logical Minimum (0),            */ \
  0x25, 0x01, /*      Logical Maximum (1),            */ \
  0x75, 0x01, /*      Report Size (1),                */ \
  0x95, 0x08, /*      Report Count (8),               */ \
  0x81, 0x02, /*      Input (Variable),               */ \
  0x95, 0x01, /*      Report Count (1),               */ \
  0x75, 0x08, /*      Report Size (8),                */ \
  0x81, 0x01, /*      Input (Constant),               */ \
  0x95, 0x05, /*      Report Count (5),               */ \
  0x75, 0x01, /*      Report Size (1),                */ \
  0x05, 0x08, /*      Usage Page (LED),               */ \
  0x19, 0x01, /*      Usage Minimum (01h),            */ \
  0x29, 0x05, /*      Usage Maximum (05h),            */ \
  0x91, 0x02, /*      Output (Variable),              */ \
  0x95, 0x01, /*      Report Count (1),               */ \
  0x75, 0x03, /*      Report Size (3),                */ \
  0x91, 0x01, /*      Output (Constant),              */ \
  0x95, 0x06, /*      Report Count (6),               */ \
  0x75, 0x08, /*      Report Size (8),                */ \
  0x14,       /*      Logical Minimum (0),            */ \
  0x25, 0x65, /*      Logical Maximum (101),          */ \
  0x05, 0x07, /*      Usage Page (Keyboard),          */ \
  0x18,       /*      Usage Minimum (None),           */ \
  0x29, 0x65, /*      Usage Maximum (KB Application), */ \
  0x80,       /*      Input,                          */ \
  0xC0        /*  End Collection                      */


#define USB_REPORT_DESCRIPTOR_KEYBOARD_6KRO_SIZE  sizeof ((uint8_t[]) { USB_REPORT_DESCRIPTOR_KEYBOARD_6KRO_VAL() })

// see discussion here http://www.microchip.com/forums/tm.aspx?m=391435
// cat mouse_usage_report_descriptor.xml  | hidrd-convert -i xml -o code
#define USB_REPORT_DESCRIPTOR_MOUSE_VAL()        \
  0x05, 0x01,         /*  Usage Page (Desktop),                           */ \
  0x09, 0x02,         /*  Usage (Mouse),                                  */ \
  0xA1, 0x01,         /*  Collection (Application),                       */ \
  0x09, 0x02,         /*      Usage (Mouse),                              */ \
  0xA1, 0x02,         /*      Collection (Logical),                       */ \
  0x09, 0x01,         /*          Usage (Pointer),                        */ \
  0xA0,               /*          Collection (Physical),                  */ \
  0x05, 0x09,         /*              Usage Page (Button),                */ \
  0x19, 0x01,         /*              Usage Minimum (01h),                */ \
  0x29, 0x05,         /*              Usage Maximum (05h),                */ \
  0x14,               /*              Logical Minimum (0),                */ \
  0x25, 0x01,         /*              Logical Maximum (1),                */ \
  0x75, 0x01,         /*              Report Size (1),                    */ \
  0x95, 0x05,         /*              Report Count (5),                   */ \
  0x81, 0x02,         /*              Input (Variable),                   */ \
  0x75, 0x03,         /*              Report Size (3),                    */ \
  0x95, 0x01,         /*              Report Count (1),                   */ \
  0x81, 0x03,         /*              Input (Constant, Variable),         */ \
  0x05, 0x01,         /*              Usage Page (Desktop),               */ \
  0x09, 0x30,         /*              Usage (X),                          */ \
  0x09, 0x31,         /*              Usage (Y),                          */ \
  0x15, 0x81,         /*              Logical Minimum (-127),             */ \
  0x25, 0x7F,         /*              Logical Maximum (127),              */ \
  0x75, 0x08,         /*              Report Size (8),                    */ \
  0x95, 0x02,         /*              Report Count (2),                   */ \
  0x81, 0x06,         /*              Input (Variable, Relative),         */ \
  0xA1, 0x02,         /*              Collection (Logical),               */ \
  0x09, 0x48,         /*                  Usage (Resolution Multiplier),  */ \
  0x14,               /*                  Logical Minimum (0),            */ \
  0x25, 0x01,         /*                  Logical Maximum (1),            */ \
  0x35, 0x01,         /*                  Physical Minimum (1),           */ \
  0x45, 0x04,         /*                  Physical Maximum (4),           */ \
  0x75, 0x02,         /*                  Report Size (2),                */ \
  0x95, 0x01,         /*                  Report Count (1),               */ \
  0xA4,               /*                  Push,                           */ \
  0xB1, 0x02,         /*                  Feature (Variable),             */ \
  0x09, 0x38,         /*                  Usage (Wheel),                  */ \
  0x15, 0x81,         /*                  Logical Minimum (-127),         */ \
  0x25, 0x7F,         /*                  Logical Maximum (127),          */ \
  0x34,               /*                  Physical Minimum (0),           */ \
  0x44,               /*                  Physical Maximum (0),           */ \
  0x75, 0x08,         /*                  Report Size (8),                */ \
  0x81, 0x06,         /*                  Input (Variable, Relative),     */ \
  0xC0,               /*              End Collection,                     */ \
  0xA1, 0x02,         /*              Collection (Logical),               */ \
  0x09, 0x48,         /*                  Usage (Resolution Multiplier),  */ \
  0xB4,               /*                  Pop,                            */ \
  0xB1, 0x02,         /*                  Feature (Variable),             */ \
  0x34,               /*                  Physical Minimum (0),           */ \
  0x44,               /*                  Physical Maximum (0),           */ \
  0x75, 0x04,         /*                  Report Size (4),                */ \
  0xB1, 0x03,         /*                  Feature (Constant, Variable),   */ \
  0x05, 0x0C,         /*                  Usage Page (Consumer),          */ \
  0x0A, 0x38, 0x02,   /*                  Usage (AC Pan),                 */ \
  0x15, 0x81,         /*                  Logical Minimum (-127),         */ \
  0x25, 0x7F,         /*                  Logical Maximum (127),          */ \
  0x75, 0x08,         /*                  Report Size (8),                */ \
  0x81, 0x06,         /*                  Input (Variable, Relative),     */ \
  0xC0,               /*              End Collection,                     */ \
  0xC0,               /*          End Collection,                         */ \
  0xC0,               /*      End Collection,                             */ \
  0xC0                /*  End Collection                                  */
#define USB_REPORT_DESCRIPTOR_MOUSE_SIZE  sizeof ((uint8_t[]) { USB_REPORT_DESCRIPTOR_MOUSE_VAL() })

// audio controls & system controls
// http://www.microsoft.com/whdc/archive/w2kbd.mspx
// https://web.archive.org/web/20080413193426/http://www.microsoft.com/whdc/archive/w2kbd.mspx
// cat extra_usage_report_descriptor.xml  | hidrd-convert -i xml -o code
#define USB_REPORT_DESCRIPTOR_EXTRA_VAL()        \
  0x05, 0x01,         /*  Usage Page (Desktop),                       */ \
  0x09, 0x80,         /*  Usage (Sys Control),                        */ \
  0xA1, 0x01,         /*  Collection (Application),                   */ \
  0x85, 0x02,         /*      Report ID (2),                          */ \
  0x15, 0x01,         /*      Logical Minimum (1),                    */ \
  0x26, 0xB7, 0x00,   /*      Logical Maximum (183),                  */ \
  0x19, 0x01,         /*      Usage Minimum (Pointer),                */ \
  0x29, 0xB7,         /*      Usage Maximum (Sys Dspl LCD Autoscale), */ \
  0x75, 0x10,         /*      Report Size (16),                       */ \
  0x95, 0x01,         /*      Report Count (1),                       */ \
  0x80,               /*      Input,                                  */ \
  0xC0,               /*  End Collection,                             */ \
  0x05, 0x0C,         /*  Usage Page (Consumer),                      */ \
  0x09, 0x01,         /*  Usage (Consumer Control),                   */ \
  0xA1, 0x01,         /*  Collection (Application),                   */ \
  0x85, 0x03,         /*      Report ID (3),                          */ \
  0x15, 0x01,         /*      Logical Minimum (1),                    */ \
  0x26, 0x9C, 0x02,   /*      Logical Maximum (668),                  */ \
  0x19, 0x01,         /*      Usage Minimum (Consumer Control),       */ \
  0x2A, 0x9C, 0x02,   /*      Usage Maximum (AC Distribute Vert),     */ \
  0x75, 0x10,         /*      Report Size (16),                       */ \
  0x95, 0x01,         /*      Report Count (1),                       */ \
  0x80,               /*      Input,                                  */ \
  0xC0                /*  End Collection                              */
#define USB_REPORT_DESCRIPTOR_EXTRA_SIZE  sizeof ((uint8_t[]) { USB_REPORT_DESCRIPTOR_EXTRA_VAL() })

extern uint8_t usb_report_descriptor_keyboard_6kro[USB_REPORT_DESCRIPTOR_KEYBOARD_6KRO_SIZE];
extern uint8_t usb_report_descriptor_mouse[USB_REPORT_DESCRIPTOR_MOUSE_SIZE];
extern uint8_t usb_report_descriptor_extra[USB_REPORT_DESCRIPTOR_EXTRA_SIZE];

#endif /* _usb_reports_h_ */
