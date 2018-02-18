#ifndef _usb_requests_h_
#define _usb_requests_h_

#include <stdint.h>

#define USB_REQUEST_DEVICE_GET_STATUS        0x00
#define USB_REQUEST_DEVICE_CLEAR_FEATURE     0x01
#define USB_REQUEST_DEVICE_SET_FEATURE       0x03
#define USB_REQUEST_DEVICE_SET_ADDRESS       0x05
#define USB_REQUEST_DEVICE_GET_DESCRIPTOR    0x06
#define USB_REQUEST_DEVICE_SET_DESCRIPTOR    0x07
#define USB_REQUEST_DEVICE_GET_CONFIGURATION 0x08
#define USB_REQUEST_DEVICE_SET_CONFIGURATION 0x09

#define USB_REQUEST_INTERFACE_GET_STATUS     0x00
#define USB_REQUEST_INTERFACE_CLEAR_FEATURE  0x01
#define USB_REQUEST_INTERFACE_SET_FEATURE    0x03
#define USB_REQUEST_INTERFACE_GET_INTERFACE  0x0A
#define USB_REQUEST_INTERFACE_SET_INTERFACE  0x11

#define USB_REQUEST_ENDPOINT_GET_STATUS      0x00
#define USB_REQUEST_ENDPOINT_CLEAR_FEATURE   0x01
#define USB_REQUEST_ENDPOINT_SET_FEATURE     0x03
#define USB_REQUEST_ENDPOINT_SYNC_FRAME      0x12

typedef struct {
  uint8_t bmRequestType;
  uint8_t bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} __attribute__((packed)) usb_setup_request_t;


#endif /* _usb_requests_h_ */
