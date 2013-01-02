#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#include <LUFA/Drivers/USB/USB.h>

#define NUM_KEYS 90

#define KP(key) press(key)

#ifdef __cplusplus

#define QWERTY 0
#define DVORAK 1
#define LAYOUT_MAX 1

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
  void processKeyEvent(uint8_t key);
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
  // Keyboard layouts
  //

  // Common keys
  void common8(); void common9(); void common10();
  void common11(); void common15(); void common17();
  void common18(); void common19(); void common20();
  void common21(); void common22(); void common23();
  void common24(); void common25(); void common26();
  void common27(); void common28(); void common29();
  void common30(); void common31(); void common32();
  void common33(); void common34(); void common37();
  void common47(); void common48(); void common49();
  void common50(); void common51(); void common52();
  void common53(); void common55(); void common57();
  void common58(); void common59(); void common60();
  void common61(); void common62(); void common63();
  void common66(); void common68(); void common69();
  void common70(); void common71(); void common78();
  void common79(); void common80(); void common83();
  void common85(); void common86(); void common87();
  void common88(); void common89();
  // Dvorak
  void (Keyboard::*dvorak[NUM_KEYS])();
  void dvorak0(); void dvorak1(); void dvorak2();
  void dvorak3(); void dvorak4(); void dvorak5();
  void dvorak6(); void dvorak7(); void dvorak12();
  void dvorak13(); void dvorak14(); void dvorak16();
  void dvorak35(); void dvorak36(); void dvorak38();
  void dvorak39(); void dvorak40(); void dvorak41();
  void dvorak42(); void dvorak43(); void dvorak44();
  void dvorak45(); void dvorak46(); void dvorak54();
  void dvorak56(); void dvorak64(); void dvorak65();
  void dvorak67(); void dvorak72(); void dvorak73();
  void dvorak74(); void dvorak75(); void dvorak76();
  void dvorak77(); void dvorak81(); void dvorak82();
  void dvorak84();
  // QWERTY
  void (Keyboard::*qwerty[NUM_KEYS])();
  void qwerty0(); void qwerty1(); void qwerty2();
  void qwerty3(); void qwerty4(); void qwerty5();
  void qwerty6(); void qwerty7(); void qwerty12();
  void qwerty13(); void qwerty14(); void qwerty16();
  void qwerty35(); void qwerty36(); void qwerty38();
  void qwerty39(); void qwerty40(); void qwerty41();
  void qwerty42(); void qwerty43(); void qwerty44();
  void qwerty45(); void qwerty46(); void qwerty54();
  void qwerty56(); void qwerty64(); void qwerty65();
  void qwerty67(); void qwerty72(); void qwerty73();
  void qwerty74(); void qwerty75(); void qwerty76();
  void qwerty77(); void qwerty81(); void qwerty82();
  void qwerty84();
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
void keyboardClearDisplay();
void keyboardSetLEDs(uint8_t report);

#ifdef __cplusplus
}
#endif

#endif
