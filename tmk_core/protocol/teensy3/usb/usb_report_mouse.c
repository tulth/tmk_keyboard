#include <stdint.h>
#include "usb_reports.h"

#ifdef MOUSE_ENABLE
uint8_t usb_report_descriptor_mouse[] = { USB_REPORT_DESCRIPTOR_MOUSE_VAL() };
#endif
