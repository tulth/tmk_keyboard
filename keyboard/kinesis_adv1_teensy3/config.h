
#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFF44
#define PRODUCT_ID      0xFF54
#define MANUFACTURER    Demetulth
#define PRODUCT         Kinesis Advantage1 Upgrade
#define DEVICE_VER      0x0001


/* key matrix size */
#define MATRIX_ROWS 16 // 2 74LS138 1-of-8 demultiplexers
#define MATRIX_COLS 10 // 8 demultiplexer selected matrix columns, and two direct button inputs (pins 5 and 6)

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)



/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

/* teensy3 compat */
#define LAYOUT_US_ENGLISH  
#define USB_KINESIS_ADVANTAGE1_UPDGRADE
#define KEYMAP_DVORAK

#endif
