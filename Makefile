BOARD_TAG=leonardo
ARDUINO_PORT=/dev/serial/by-id/usb-Arduino_LLC_Arduino_Leonardo-if00
ARDUINO_LIBS=\
  Wire \
  Wire/utility
ARDUINO_DIR=/home/fornellas/local/arduino-1.0.1
ARDMK_DIR=/home/fornellas/src/Arduino-Makefile
AVR_TOOLS_DIR=/usr
include /home/fornellas/src/Arduino-Makefile/arduino-mk/Arduino.mk
MONITOR_BAUDRATE=115200
RESET_CMD=/home/fornellas/src/Arduino-Makefile/bin/reset.py $(ARDUINO_PORT)
