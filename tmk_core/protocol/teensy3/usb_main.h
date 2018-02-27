/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */


#ifndef _USB_MAIN_H_
#define _USB_MAIN_H_

#include <usb_desc.h>

/* main keyboard (6kro) */
#define KBD_INTERFACE   KEYBOARD_INTERFACE  
#define KBD_ENDPOINT    KEYBOARD_ENDPOINT   
#define KBD_EPSIZE      KEYBOARD_SIZE	    
#define KBD_REPORT_KEYS KEYBOARD_REPORT_KEYS

/* secondary keyboard */
#ifdef NKRO_ENABLE
#define NKRO_INTERFACE   4               
#define NKRO_ENDPOINT    5               
#define NKRO_EPSIZE      16              
#define NKRO_REPORT_KEYS (KBD2_SIZE - 1)
#endif                   

extern void usb_remote_wakeup(void);
extern bool usb_is_sleeped(void);

#endif /* _USB_MAIN_H_ */
