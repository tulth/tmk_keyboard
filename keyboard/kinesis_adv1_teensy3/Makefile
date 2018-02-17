# Target file name (without extension).
TARGET = kinesis_adv1_teensy3

# Directory common source files exist
TMK_DIR = ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR = .

# project specific files
# SRC =	matrix.c \
# 	led.c
SRC =
SRC += led.c
SRC += matrix.c
SRC += keymap.c
SRC += notes.c
SRC += kinesis_adv1_teensy3.c

CONFIG_H = config.h

## chip/board settings
MCU_FAMILY = KINETIS
MCU_SERIES = K20x

# Linker script to use
#   - MKL26Z64 for Teensy LC
#   - MK20DX128 for Teensy 3.0
#   - MK20DX256 for Teensy 3.1 and 3.2
MCU_LDSCRIPT = mk20dx256

F_CPU = 48000000

# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m4

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
# I.e. 6 for Teensy LC; 7 for Teensy 3.x
ARMV = 7

# Build Options
#   comment out to disable the options.
#
# BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
# NKRO_ENABLE = yes	    # USB Nkey Rollover

# include $(TMK_DIR)/protocol.mk
# include $(TMK_DIR)/protocol/teensy3.mk
include $(TMK_DIR)/tool/teensy3/common.mk
include $(TMK_DIR)/tool/teensy3/teensy3.mk
include $(TMK_DIR)/tool/teensy3/rules.mk
