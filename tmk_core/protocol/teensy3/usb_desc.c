#include <usb_desc.h>
#include <usb/usb_reports.h>

// convert to U string
#define USTR(s) XUSTR(s)
#define XUSTR(s) u ## #s

static uint8_t usb_report_descriptor_hid_listen[] = {
  0x06, 0x31, 0xFF,	    // Usage Page 0xFF31 (vendor defined)
  0x09, 0x74,		    // Usage 0x74
  0xA1, 0x53,		    // Collection 0x53
  0x75, 0x08,		    // report size = 8 bits
  0x15, 0x00,		    // logical minimum = 0
  0x26, 0xFF, 0x00,	    // logical maximum = 255
  0x95, HID_LISTEN_SIZE,    // report count
  0x09, 0x75,		    // usage
  0x81, 0x02,		    // Input (array)
  0xC0			    // end collection
};

usb_descriptor_device_t device_descriptor = {
    .header = {.bLength         = sizeof(usb_descriptor_device_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_DEVICE },
    .bcdUSB                     = 0x0200,
    .bDeviceClass               = 0,
    .bDeviceSubClass            = 0,
    .bDeviceProtocol            = 0,
    .bMaxPacketSize             = EP0_SIZE,
    .idVendor                   = VENDOR_ID,
    .idProduct                  = PRODUCT_ID,
    .bcdDevice                  = DEVICE_VER,
    .iManufacturer              = 1,
    .iProduct                   = 2,
    .iSerialNumber              = 3,
    .bNumConfigurations         = 1,
};

usb_config_t config_descriptor = {
  {
    .header = {.bLength         = sizeof(usb_descriptor_configuration_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_CONFIG },
    .wTotalLength               = sizeof(usb_config_t),
    .bNumInterfaces             = NUM_INTERFACES,
    .bConfigurationValue        = 1,
    .iConfiguration             = 0,
    .bmAttributes               = 0xA0,
    .bMaxPower                  = 40,
  },
  // keyboard 6kro 
  {
    .header = {.bLength         = sizeof(usb_descriptor_interface_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_INTERFACE },
    .bInterfaceNumber           = KEYBOARD_INTERFACE,
    .bAlternateSetting          = 0,
    .bNumEndpoints              = 1,
    .bInterfaceClass            = USB_INTERFACE_CLASS_HID,
    .bInterfaceSubClass         = USB_INTERFACE_CLASS_HID_SUBCLASS_BOOT,
    .bInterfaceProtocol         = USB_INTERFACE_CLASS_HID_PROTOCOL_KEYBOARD,
    .iInterface                 = 0,
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_class_hid_t),
               .bDescriptorType = USB_DESCRIPTOR_CLASS_HID },
    .bcdHID                     = 0x0111,
    .bCountryCode               = 0,
    .bNumDescriptors            = 1,
    .bDescriptorType            = USB_DESCRIPTOR_CLASS_REPORT,
    .wDescriptorLength          = sizeof(usb_report_descriptor_keyboard_6kro),
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_endpoint_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_ENDPOINT },
    .bEndpointAddress           = KEYBOARD_ENDPOINT | USB_ENDPOINT_DIRECTION_IN,
    .bmAttributes               = USB_ATTRIBUTE_INTERRUPT,
    .wMaxPacketSize             = KEYBOARD_SIZE,
    .bInterval                  = 0x0A,
  },
#ifdef MOUSE_ENABLE
  // mouse
  {
    .header = {.bLength         = sizeof(usb_descriptor_interface_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_INTERFACE },
    .bInterfaceNumber           = MOUSE_INTERFACE,
    .bAlternateSetting          = 0,
    .bNumEndpoints              = 1,
    .bInterfaceClass            = USB_INTERFACE_CLASS_HID,
    .bInterfaceSubClass         = USB_INTERFACE_CLASS_HID_SUBCLASS_BOOT,
    .bInterfaceProtocol         = USB_INTERFACE_CLASS_HID_PROTOCOL_MOUSE,
    .iInterface                 = 0,
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_class_hid_t),
               .bDescriptorType = USB_DESCRIPTOR_CLASS_HID },
    .bcdHID                     = 0x0111,
    .bCountryCode               = 0,
    .bNumDescriptors            = 1,
    .bDescriptorType            = USB_DESCRIPTOR_CLASS_REPORT,
    .wDescriptorLength          = sizeof(usb_report_descriptor_mouse),
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_endpoint_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_ENDPOINT },
    .bEndpointAddress           = MOUSE_ENDPOINT | USB_ENDPOINT_DIRECTION_IN,
    .bmAttributes               = USB_ATTRIBUTE_INTERRUPT,
    .wMaxPacketSize             = MOUSE_SIZE,
    .bInterval                  = 0x0A,
  },
#endif
#ifdef CONSOLE_ENABLE  
  // hid_listen
  {
    .header = {.bLength         = sizeof(usb_descriptor_interface_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_INTERFACE },
    .bInterfaceNumber           = HID_LISTEN_INTERFACE,
    .bAlternateSetting          = 0,
    .bNumEndpoints              = 1,
    .bInterfaceClass            = USB_INTERFACE_CLASS_HID,
    .bInterfaceSubClass         = USB_INTERFACE_CLASS_HID_SUBCLASS_NONE,
    .bInterfaceProtocol         = USB_INTERFACE_CLASS_HID_PROTOCOL_NONE,
    .iInterface                 = 0,
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_class_hid_t),
               .bDescriptorType = USB_DESCRIPTOR_CLASS_HID },
    .bcdHID                     = 0x0111,
    .bCountryCode               = 0,
    .bNumDescriptors            = 1,
    .bDescriptorType            = USB_DESCRIPTOR_CLASS_REPORT,
    .wDescriptorLength          = sizeof(usb_report_descriptor_hid_listen),
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_endpoint_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_ENDPOINT },
    .bEndpointAddress           = HID_LISTEN_ENDPOINT | USB_ENDPOINT_DIRECTION_IN,
    .bmAttributes               = USB_ATTRIBUTE_INTERRUPT,
    .wMaxPacketSize             = HID_LISTEN_SIZE,
    .bInterval                  = 0x01,
  },
#endif
#ifdef EXTRAKEY_ENABLE
  // media and system keys
  {
    .header = {.bLength         = sizeof(usb_descriptor_interface_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_INTERFACE },
    .bInterfaceNumber           = EXTRA_INTERFACE,
    .bAlternateSetting          = 0,
    .bNumEndpoints              = 1,
    .bInterfaceClass            = USB_INTERFACE_CLASS_HID,
    .bInterfaceSubClass         = USB_INTERFACE_CLASS_HID_SUBCLASS_NONE,
    .bInterfaceProtocol         = USB_INTERFACE_CLASS_HID_PROTOCOL_NONE,
    .iInterface                 = 0,
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_class_hid_t),
               .bDescriptorType = USB_DESCRIPTOR_CLASS_HID },
    .bcdHID                     = 0x0111,
    .bCountryCode               = 0,
    .bNumDescriptors            = 1,
    .bDescriptorType            = USB_DESCRIPTOR_CLASS_REPORT,
    .wDescriptorLength          = sizeof(usb_report_descriptor_extra),
  },
  {
    .header = {.bLength         = sizeof(usb_descriptor_endpoint_t),
               .bDescriptorType = USB_DESCRIPTOR_TYPE_ENDPOINT },
    .bEndpointAddress           = EXTRA_ENDPOINT | USB_ENDPOINT_DIRECTION_IN,
    .bmAttributes               = USB_ATTRIBUTE_INTERRUPT,
    .wMaxPacketSize             = EXTRA_SIZE,
    .bInterval                  = 0x0A,
  },
#endif
};

usb_descriptor_string_t language_id = {
  .header = {.bLength         = sizeof(usb_descriptor_header_t)+2,
             .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING },
  .bString = {0x0409},
};

usb_descriptor_string_t manufacturer = {
  .header = {.bLength         = sizeof(usb_descriptor_header_t)+sizeof(USTR(MANUFACTURER)),
             .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING },
  .bString = USTR(MANUFACTURER),
};

usb_descriptor_string_t product = {
  .header = {.bLength         = sizeof(usb_descriptor_header_t)+sizeof(USTR(PRODUCT)),
             .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING },
  .bString = USTR(PRODUCT),
};

usb_descriptor_string_t serial_number = {
  .header = {.bLength         = sizeof(usb_descriptor_header_t)+sizeof(USTR(SERIAL_NUMBER)),
             .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING },
  .bString = USTR(SERIAL_NUMBER),
};

const usb_descriptor_list_t usb_descriptor_list[] = {
	{0x0100, 0x0000, (const uint8_t *)&device_descriptor, sizeof(usb_descriptor_device_t)},
	{0x0200, 0x0000, (const uint8_t *)&config_descriptor, sizeof(usb_config_t)},
        
	{0x2100, KEYBOARD_INTERFACE, (const uint8_t *)&(config_descriptor.keyboard_6kro_class), sizeof(usb_descriptor_class_hid_t)},
        {0x2200, KEYBOARD_INTERFACE, usb_report_descriptor_keyboard_6kro, sizeof(usb_report_descriptor_keyboard_6kro)},
        
	{0x2100, MOUSE_INTERFACE, (const uint8_t *)&(config_descriptor.mouse_class), sizeof(usb_descriptor_class_hid_t)},
	{0x2200, MOUSE_INTERFACE, usb_report_descriptor_mouse, sizeof(usb_report_descriptor_mouse)},
        
	{0x2100, HID_LISTEN_INTERFACE, (const uint8_t *)&(config_descriptor.hid_listen_class), sizeof(usb_descriptor_class_hid_t)},
	{0x2200, HID_LISTEN_INTERFACE, usb_report_descriptor_hid_listen, sizeof(usb_report_descriptor_hid_listen)},
        
	{0x2100, EXTRA_INTERFACE, (const uint8_t *)&(config_descriptor.extra_class), sizeof(usb_descriptor_class_hid_t)},
	{0x2200, EXTRA_INTERFACE, usb_report_descriptor_extra, sizeof(usb_report_descriptor_extra)},
/* #ifdef NKRO_ENABLE */
/* 	{0x2200, NKRO_INTERFACE, keyboard2_report_desc, sizeof(keyboard2_report_desc)}, */
/* 	{0x2100, NKRO_INTERFACE, (const uint8_t *)&(config_descriptor+NKRO_HID_DESC_OFFSET, sizeof(usb_descriptor_class_hid_t)}, */
/* #endif */
        {0x0300, 0x0000, (const uint8_t *)&language_id, 0},
        {0x0301, 0x0409, (const uint8_t *)&manufacturer, 0},
        {0x0302, 0x0409, (const uint8_t *)&product, 0},
        {0x0303, 0x0409, (const uint8_t *)&serial_number, 0},
	{0, 0, 0, 0}
};

const uint8_t usb_endpoint_config_table[NUM_ENDPOINTS] =
{
  USB_ENDPOINT_TRANSMIT_ONLY, // kbd, 6kro
  USB_ENDPOINT_TRANSMIT_ONLY, // mouse
  USB_ENDPOINT_TRANSMIT_ONLY, // hid listen (debug)
  USB_ENDPOINT_TRANSMIT_ONLY, // media keys 
  USB_ENDPOINT_TRANSMIT_ONLY, // kbd, nkro
};
  
// OLD, FIXME
void usb_init_serialnumber(void)
{
}
