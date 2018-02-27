COMMON_DIR = $(TMK_DIR)/common
SRC +=	$(COMMON_DIR)/host.c
SRC +=	$(COMMON_DIR)/keyboard.c
SRC +=	$(COMMON_DIR)/matrix.c
SRC +=	$(COMMON_DIR)/action.c
SRC +=	$(COMMON_DIR)/action_tapping.c
SRC +=	$(COMMON_DIR)/action_macro.c
SRC +=	$(COMMON_DIR)/action_layer.c
SRC +=	$(COMMON_DIR)/action_util.c
#SRC +=	$(COMMON_DIR)/actionmap.c
SRC +=	$(COMMON_DIR)/keymap.c
SRC +=	$(COMMON_DIR)/print.c
SRC +=	$(COMMON_DIR)/debug.c
SRC +=	$(COMMON_DIR)/util.c
SRC +=	$(COMMON_DIR)/hook.c
SRC +=	$(COMMON_DIR)/teensy3/printf.c
SRC +=	$(COMMON_DIR)/teensy3/timer.c
SRC +=	$(COMMON_DIR)/teensy3/suspend.c
SRC +=	$(COMMON_DIR)/teensy3/cores/teensy3/mk20dx128.c
SRC +=	$(COMMON_DIR)/teensy3/cores/teensy3/nonstd.c
SRC +=	$(COMMON_DIR)/teensy3/cores/teensy3/pins_teensy.c
SRC +=	$(COMMON_DIR)/teensy3/cores/teensy3/usb_mem.c # KEEP!!!

# Option modules
ifdef BOOTMAGIC_ENABLE
    SRC += $(COMMON_DIR)/bootmagic.c
    OPT_DEFS += -DBOOTMAGIC_ENABLE
endif

ifdef MOUSEKEY_ENABLE
    SRC += $(COMMON_DIR)/mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef CONSOLE_ENABLE
    OPT_DEFS += -DCONSOLE_ENABLE
else
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifdef COMMAND_ENABLE
    SRC += $(COMMON_DIR)/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifdef NKRO_ENABLE
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef USB_6KRO_ENABLE
    OPT_DEFS += -DUSB_6KRO_ENABLE
endif

ifdef SLEEP_LED_ENABLE
    $(error SLEEP_LED_ENABLE not supported on teensy3)
endif

ifdef BACKLIGHT_ENABLE
    SRC += $(COMMON_DIR)/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifdef KEYMAP_SECTION_ENABLE
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE

    ifeq ($(strip $(MCU)),atmega32u2)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr35.x
    else ifeq ($(strip $(MCU)),atmega32u4)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr5.x
    else
	EXTRALDFLAGS = $(error no ldscript for keymap section)
    endif
endif

# Version string
OPT_DEFS += -DVERSION=$(shell (git describe --always --dirty || echo 'unknown') 2> /dev/null)

OPT_DEFS += -D__MK20DX256__

# Bootloader address
ifdef STM32_BOOTLOADER_ADDRESS
    OPT_DEFS += -DSTM32_BOOTLOADER_ADDRESS=$(STM32_BOOTLOADER_ADDRESS)
endif
