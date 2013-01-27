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
#define NO_LED_REPORT	0xFF
#define NO_USB_DEVICE_STATE	0xFF

#define US_US 		0
#define US_DVORAK 	1
#define ABNT2_US	2
#define ABNT2_DVORAK	3
#define LAYOUT_MAX 	3

#define EEPROM_LAYOUT 0

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

  // Serial
  FILE *Stream;

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

  uint8_t keyState[NUM_KEYS];
  uint8_t keypad;
  uint8_t fn;
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
  bool displayDoUpdate;
  bool displayUpdateAgain;
  bool displayFirstLoopRun;
  uint8_t display_var_USB_DeviceState;
  uint8_t display_var_LEDReport;
  volatile USB_KeyboardReport_Data_t *display_var_KeyboardReport;
  uint8_t display_var_macroState;
  uint8_t display_var_USB_Device_RemoteWakeupEnabled;
  void displayForceUpdate();
  void displayDrawIndicator(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x);
  void displayDrawLEDs();
  void displayDrawLayoutStates();
  void displayDrawStrCenter(u8g_pgm_uint8_t *str, uint8_t y);
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
  Keyboard(FILE *S);
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
