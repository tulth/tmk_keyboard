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

#ifndef _usb_hid_listen_h_
#define _usb_hid_listen_h_

#include "usb_desc.h"

#if defined(HID_LISTEN_INTERFACE)

#include <inttypes.h>

#if F_CPU >= 20000000 && !defined(USB_DISABLED)

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_hid_listen_putchar(uint8_t c);
int usb_hid_listen_write(const void *buffer, uint32_t size);
int usb_hid_listen_write_buffer_free(void);
void usb_hid_listen_flush_output(void);
extern volatile uint8_t usb_hid_listen_transmit_flush_timer;
extern volatile uint8_t usb_configuration;
#ifdef __cplusplus
}
#endif

#define USB_HID_LISTEN_DTR  0x01
#define USB_HID_LISTEN_RTS  0x02

// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_hid_listen_class : public Print
{
public:
	constexpr usb_hid_listen_class() {}
        void begin() { }
        void end() { /* TODO: flush output and shut down USB port */ };
        virtual void flush() { usb_hid_listen_flush_output(); }  // TODO: actually wait for data to leave USB...
        virtual size_t write(uint8_t c) { return usb_hid_listen_putchar(c); }
        virtual size_t write(const uint8_t *buffer, size_t size) { return usb_hid_listen_write(buffer, size); }
	size_t write(unsigned long n) { return write((uint8_t)n); }
	size_t write(long n) { return write((uint8_t)n); }
	size_t write(unsigned int n) { return write((uint8_t)n); }
	size_t write(int n) { return write((uint8_t)n); }
	virtual int availableForWrite() { return usb_hid_listen_write_buffer_free(); }
	using Print::write;
        void send_now(void) { usb_hid_listen_flush_output(); }

};
extern usb_hid_listen_class Hid_Listen;
extern void hid_listenEvent(void);
#endif // __cplusplus


#else  // F_CPU < 20000000


#endif // F_CPU

#endif // HID_LISTEN_INTERFACE

#endif // _usb_hid_listen_h_
