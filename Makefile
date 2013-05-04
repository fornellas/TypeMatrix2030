##
## Common
##

MCU=at90usb1286
TARGET=target
LUFA_PATH=$(HOME)/src/lufa/LUFA
ARCH=AVR8
U8G_PATH=$(HOME)/src/u8glib/src

##
## SOURCES
##

# Mandatory
#LUFA_PATH=
#ARCH=

##
## BUILD
##

# Mandatory
#TARGET=
#ARCH=
#MCU=
SRC=\
  $(wildcard *.cpp) \
  $(wildcard LUFA/*.c) \
  $(wildcard Keyboard/*.cpp) $(wildcard Keyboard/layouts/*.cpp) \
  $(wildcard $(U8G_PATH)/*.c) \
  $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
F_USB=$(F_CPU)
#LUFA_PATH=
# Optional
#BOARD=
OPTIMIZATION=2
#C_STANDARD=
CPP_STANDARD=c++0x
#DEBUG_FORMAT=
#DEBUG_LEVEL=
F_CPU=16000000
#C_FLAGS=
#CPP_FLAGS=
#ASM_FLAGS=
CC_FLAGS=-DUSE_LUFA_CONFIG_HEADER -ILUFA/ -I$(U8G_PATH)/
LD_FLAGS=
#LINKER_RELAXATIONS=
OBJDIR=build
#OBJECT_FILES=

##
## Custom
##

MONITOR_PORT=/dev/serial/by-id/usb-TypeMatrix__Hacked___2030_USB_Keyboard__Hacked___A4036313439351D0B0C0-if00

TEENSY_LOADER=$(HOME)/local/teensy_loader_cli/teensy_loader_cli

all:

teensy: $(TARGET).hex
	$(TEENSY_LOADER) -mmcu=$(MCU) -w -v $(TARGET).hex

monitor: 
	while ! [ -e $(MONITOR_PORT) ] ; do true ; done
	screen $(MONITOR_PORT)

include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
