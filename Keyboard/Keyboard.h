#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include <u8g.h>

//#define SERIAL_DEBUG 1

#ifdef __cplusplus

#include "EnduranceEEPROM.h"

//
// General
//

#define NUM_KEYS 90

#define KP(key) press(key)

#define NO_KEY			0x00
#define NO_LED_REPORT		0xFF
#define NO_USB_DEVICE_STATE	0xFF

//
// Layout
//

#define     US_US 		0
#define     US_DVORAK 	1
#define  ABNT2_US	2
#define  ABNT2_DVORAK	3
#define DVORAK_DVORAK	4
#define LAYOUT_MAX 	4

//
// EEPROM
//

#define EEPROM_LAYOUT 0 // uint8_t
// Values to ensure endurance of 15000/day for 15 years == 109500000 key presses
// Assuminh 100000 erase/write EEPROM cycles
#define EEPROM_KEYPRESSES_0 (uint16_t)(EEPROM_LAYOUT+sizeof(uint8_t))
#define EEPROM_KEYPRESSES_0_LOCATIONS 255
#define EEPROM_KEYPRESSES_0_WRITE_INTERVAL 5
#define EEPROM_KEYPRESSES_1 (uint16_t)(EEPROM_KEYPRESSES_0+(uint16_t)EEPROM_KEYPRESSES_0_LOCATIONS*(uint16_t)2) 
#define EEPROM_KEYPRESSES_1_LOCATIONS 4
#define EEPROM_KEYPRESSES_2 (uint16_t)(EEPROM_KEYPRESSES_1+(uint16_t)EEPROM_KEYPRESSES_1_LOCATIONS*(uint16_t)2)
#define EEPROM_KEYPRESSES_3 (uint16_t)(EEPROM_KEYPRESSES_2+(uint16_t)sizeof(uint8_t))

//
// Macros
//

#define MACRO_STATE_NONE 0
#define MACRO_STATE_INIT 1
// Recording
#define MACRO_STATE_REC_INIT 2
#define MACRO_STATE_REC_LOCK 3
#define MACRO_STATE_REC_TYPE 4
// Delete
#define MACRO_STATE_DEL 5
// Unlock
#define MACRO_STATE_UNLOCK 6
#define MACRO_STATE_CLEAR 7
#define MACRO_STATE_PASSWD 8

extern USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

class Keyboard {
private:
  //
  // Facilities
  //

#ifdef SERIAL_DEBUG
  // Serial
  FILE *Stream;
#endif

  //
  // Key scannig
  //

  // Init ports
  void portInit();
  // translate keyboard track to pin mapping
  volatile uint8_t *getPinDDR(uint8_t pin);
  volatile uint8_t *getPinPORT(uint8_t pin);
  volatile uint8_t *getPinPIN(uint8_t pin);
  uint8_t getPinBit(uint8_t pin);
  // I/O
  void setPinInLow(uint8_t pin);
  void setPinOut(uint8_t pin, uint8_t value);
  uint8_t readPin(uint8_t pin);
  // Send key press to USB driver
  void press(const uint8_t key);
  // Module specic key processing
  bool processSuspendKeys(const bool state);
  bool processMacroKeys(const uint8_t key, const bool state);
  bool processCommonKeys(const uint8_t key, const bool state);
  bool processDvorakQwertyKeys(const uint8_t key, const bool state);
  // Generic key processor (calls above methods)
  void processKeyEvent(const uint8_t key, const bool state);
  // process keys with raw FFC addressing
  void processRawEvent(uint8_t a, uint8_t b, const bool state);
  // set lowPin to low and scan other asked pins for low signal. Last arg must be -1.
  void scanPairs(uint8_t lowPin, ...);

  //
  // States
  //

  bool keyState[NUM_KEYS];
  bool keypad;
  bool fn;
  bool fn_used;
  uint8_t layout;
  volatile uint8_t LEDReport;
  uint8_t last_USB_DeviceState;
  uint8_t last_USB_Device_RemoteWakeupEnabled;

  //
  // Macros
  //

  uint8_t macroState;
  bool macroLocked;
  void playMacro(uint8_t key);
  void changeMacroMode(uint8_t mode);

  //
  // Key sequencing
  //

  // add a key sequence to be outputted by scanAll()
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
  void displayInit();
  uint8_t displayUpdating;
  bool displayUpdateAgain;
  uint8_t display_var_USB_DeviceState;
  uint8_t display_var_LEDReport;
  volatile USB_KeyboardReport_Data_t *display_var_KeyboardReport;
  uint8_t display_var_macroState;
  uint8_t display_var_USB_Device_RemoteWakeupEnabled;
  void displayForceUpdate();
  void displayDrawStrCenter(int8_t x_offset, int8_t y_offset, ...);
  uint8_t displayGetToggleWidth(u8g_pgm_uint8_t *str);
  uint8_t displayGetToggleHeight();
  uint8_t displayDrawToggle(bool state, uint8_t x, uint8_t y, u8g_pgm_uint8_t *str);
  void displayDrawKeyboardLayout(uint8_t y, bool kb_us, bool kb_dvorak, bool host_us, bool host_dvorak, bool host_abnt2);
  //
  // Key press counter
  //
  void keyPressesInit();
  uint32_t readKeyPresses();
  void keyPress();
  EnduranceEEPROM *keyPresses0;
  EnduranceEEPROM *keyPresses1;
  uint32_t ramKeyPresses;
  uint32_t readEEPROMKeyPresses();
public:
  // Facilities
  volatile USB_KeyboardReport_Data_t *KeyboardReport;
  // Key scanning
  void scanAll();
  // Display
  void displayUpdate();
  void setLEDs(uint8_t report);
  // Main loop
  void loopTask();
  // Constructor
#ifdef SERIAL_DEBUG
  Keyboard(FILE *S);
#else
  Keyboard();
#endif
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void keyboardScanAll(USB_KeyboardReport_Data_t *KR);
void keyboardSetLEDs(uint8_t report);

#ifdef __cplusplus
}
#endif

#endif
