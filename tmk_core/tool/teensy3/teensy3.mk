##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
OPT_DEFS += -DPROTOCOL_TEENSY3
# ifeq ($(USE_OPT),)
#   USE_OPT = -mcpu=cortex-m4 -ffunction-sections -fdata-sections -Os
# endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# include specific config.h?
ifdef CONFIG_H
    USE_COPT += -include $(CONFIG_H)
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT = -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs
endif

# Enable this if you want link time optimizations (LTO)
ifeq ($(USE_LTO),)
  USE_LTO = no
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x200
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Imported source files and paths
# None

# Define linker script file here
LDSCRIPT = $(TMK_DIR)/common/teensy3/cores/teensy3/$(MCU_LDSCRIPT).ld

EXTRALDFLAGS += -T$(LDSCRIPT)
EXTRALDFLAGS += -specs=nano.specs
EXTRALDFLAGS += -specs=nosys.specs


SRC += $(TMK_DIR)/protocol/teensy3/host_driver.c
SRC += $(TMK_DIR)/protocol/teensy3/usb_main.c
SRC += $(TMK_DIR)/protocol/teensy3/main.c
SRC += $(TMK_DIR)/protocol/teensy3/usb_dev.c
SRC += $(TMK_DIR)/protocol/teensy3/usb_keyboard.c
SRC += $(TMK_DIR)/protocol/teensy3/usb_hid_listen.c
SRC += $(TMK_DIR)/protocol/teensy3/usb_desc.c

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC =

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC =
ASMXSRC = $(STARTUPASM) $(PORTASM) $(OSALASM)

# VPATH = $(TMK_DIR) $(COMMON_DIR)/teensy $(TMK_DIR)/protocol/teensy \
#         $(TMK_DIR)/protocol $(TARGET_DIR)
VPATH = $(TMK_DIR) $(TMK_DIR)/protocol/teensy3 $(COMMON_DIR) $(COMMON_DIR)/teensy3 $(COMMON_DIR)/teensy3/cores/teensy3


#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size -A
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
# CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes -Wno-missing-field-initializers
CWARN = -Wpedantic -Wextra -Werror -Wno-old-style-declaration

# Define C++ warning options here
# CPPWARN = -Wall -Wextra -Wundef
CPPWARN = -Wpedantic -Wextra -Werror

EXTRAINCDIRS=$
#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
## Select which interfaces to include here!
UDEFS += $(OPT_DEFS)

# # Define ASM defines here
# UADEFS += $(OPT_DEFS)
# # bootloader definitions may be used in the startup .s file
# ifneq ("$(wildcard $(TARGET_DIR)/bootloader_defs.h)","")
#     UADEFS += -include $(TARGET_DIR)/bootloader_defs.h
#     UDEFS += -include $(TARGET_DIR)/bootloader_defs.h
# else ifneq ("$(wildcard $(TARGET_DIR)/boards/$(BOARD)/bootloader_defs.h)","")
#     UADEFS += -include $(TARGET_DIR)/boards/$(BOARD)/bootloader_defs.h
#     UDEFS += -include $(TARGET_DIR)/boards/$(BOARD)/bootloader_defs.h
# endif

# List all user directories here
#UINCDIR =

# List the user directory to look for the libraries here
#ULIBDIR =

# List all user libraries here
#ULIBS =

#
# End of user defines
##############################################################################

