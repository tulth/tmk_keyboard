#ifndef _usb_descriptors_h_
#define _usb_descriptors_h_

#include <stdint.h>

#define USB_DESCRIPTOR_TYPE_DEVICE    0x01
#define USB_DESCRIPTOR_TYPE_CONFIG    0x02
#define USB_DESCRIPTOR_TYPE_INTERFACE 0x04
#define USB_DESCRIPTOR_TYPE_ENDPOINT  0x05
#define USB_DESCRIPTOR_TYPE_STRING    0x03

#define USB_DESCRIPTOR_CLASS_HID      0x21
#define USB_DESCRIPTOR_CLASS_REPORT   0x22

#define USB_ENDPOINT_TRANSMIT_ONLY    0x15

typedef struct {
  uint8_t bLength;
  uint8_t bDescriptorType;
} __attribute__((packed)) usb_descriptor_header_t;

typedef struct {
  usb_descriptor_header_t header;
  uint16_t bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubClass;
  uint8_t bDeviceProtocol;
  uint8_t bMaxPacketSize;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t iManufacturer;
  uint8_t iProduct;
  uint8_t iSerialNumber;
  uint8_t bNumConfigurations;
} __attribute__((packed)) usb_descriptor_device_t;

typedef struct {
  usb_descriptor_header_t header;
  uint16_t wTotalLength;
  uint8_t bNumInterfaces;
  uint8_t bConfigurationValue;
  uint8_t iConfiguration;
  uint8_t bmAttributes;
  uint8_t bMaxPower;
} __attribute__((packed)) usb_descriptor_configuration_t;

typedef struct {
  usb_descriptor_header_t header;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceClass;
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
} __attribute__((packed)) usb_descriptor_interface_t;

typedef struct {
  usb_descriptor_header_t header;
  uint8_t bEndpointAddress;
  uint8_t bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t bInterval;
} __attribute__((packed)) usb_descriptor_endpoint_t;

typedef struct {
  usb_descriptor_header_t header;
  uint16_t bString[];
} __attribute__((packed)) usb_descriptor_string_t;

typedef struct {
  usb_descriptor_header_t header;
  uint16_t bcdHID;
  uint8_t bCountryCode;
  uint8_t bNumDescriptors;
  uint8_t bDescriptorType;
  uint16_t wDescriptorLength;
} __attribute__((packed)) usb_descriptor_class_hid_t;

#define USB_INTERFACE_CLASS_HID 0x03

#define USB_INTERFACE_CLASS_HID_SUBCLASS_NONE 0x00
#define USB_INTERFACE_CLASS_HID_SUBCLASS_BOOT 0x01

#define USB_INTERFACE_CLASS_HID_PROTOCOL_NONE     0x00
#define USB_INTERFACE_CLASS_HID_PROTOCOL_KEYBOARD 0x01
#define USB_INTERFACE_CLASS_HID_PROTOCOL_MOUSE    0x02

#define USB_ENDPOINT_DIRECTION_IN  0x80
#define USB_ENDPOINT_DIRECTION_OUT 0x00

#define USB_ATTRIBUTE_CONTROL     0x00
#define USB_ATTRIBUTE_ISOCHRONOUS 0x01
#define USB_ATTRIBUTE_BULK        0x02
#define USB_ATTRIBUTE_INTERRUPT   0x03

#endif /* _usb_descriptors_h_ */
