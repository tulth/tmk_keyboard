#include <stdint.h>
#include "usb_reports.h"

#ifdef EXTRAKEY_ENABLE
uint8_t usb_report_descriptor_extra[] = { USB_REPORT_DESCRIPTOR_EXTRA_VAL() };

#endif
