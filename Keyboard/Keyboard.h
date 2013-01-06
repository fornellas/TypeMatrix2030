#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include <u8g.h>

#define NUM_KEYS 90

#define KP(key) press(key)

#ifdef __cplusplus

#define NO_KEY		0

#define US_US 		0
#define US_DVORAK 	1
#define ABNT2_US	2
#define ABNT2_DVORAK	3
#define LAYOUT_MAX 	3

#define EEPROM_LAYOUT 0

extern USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

class Keyboard {
private:
  //
  // Facilities
  //

  // Serial
  FILE *Stream;

  //
  // I/O expander
  //

  // reset MCP
  void MCPreset(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit);
  // writes two 8/16bit vales starting at baseReg address
  void MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v);
  void MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2);
  // reads 16bit values starting at baseReg
  uint16_t MCPread16(uint8_t i2cAddr, uint8_t baseReg);

  //
  // Key scannig
  //

  // Send key press to USB driver
  void press(uint8_t key);
  // Send addressed key event do layout callback method
  void processKeyEvent(uint8_t key, uint8_t state);
  // process keys with raw FFC addressing
  void processRawEvent(uint8_t a, uint8_t b, uint8_t state);
  // set lowPin to low and scan other asked pins for low signal. Last arg must be -1.
  void scanPairs(uint8_t lowPin, ...);


  //
  // States
  //

  uint8_t keyState[NUM_KEYS];
  uint8_t keypad;
  uint8_t fn;
  uint8_t layout;
  uint8_t LEDReport;
  uint8_t USBConfigured;

  //
  // Key sequencing
  //

  // aidd a key sequence to be outputted by scanAll()
  // seq will be freed with free() in the end
  // [number of keys] [key1] [key2] ...
  // [number of keys] [key1] [key2] ...
  // 0x00
  void addKeySequence(uint8_t *seq);
  uint8_t *sequence;
  void playKeySequence();

  //
  // Display
  //

  u8g_t u8g;
  void initDisplay();
  void drawIndicator(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x);
public:
  // Facilities
  USB_KeyboardReport_Data_t *KeyboardReport;
  // Key scanning
  void scanAll();
  // Display
  void updateDisplay();
  void clearDisplay();
  void setLEDs(uint8_t report);
  // Constructor
  Keyboard(FILE *S);
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void keyboardScanAll(USB_KeyboardReport_Data_t *KR);
void keyboardUpdateDisplay();
void keyboardSetLEDs(uint8_t report);

#ifdef __cplusplus
}
#endif

#endif
