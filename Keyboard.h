#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#include <LUFA/Drivers/USB/USB.h>

#define NUM_KEYS 90

#ifdef __cplusplus

extern USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

class Keyboard {
private:
  // Serial
  FILE *Stream;
  // reset MCP
   void MCPreset(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit);
  // writes two 8/16bit vales starting at baseReg address
   void MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v);
   void MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2);
  // reads 16bit values starting at baseReg
   uint16_t MCPread16(uint8_t i2cAddr, uint8_t baseReg);
  // set lowPin to low and scan other asked pins for low signal. Last arg must be -1.
   void scanPairs(uint8_t lowPin, ...);
  // Process key event
   void processRawEvent(uint8_t a, uint8_t b, uint8_t state);
   void processKeyEvent(uint8_t key);
  // key pressses
  void press(uint8_t key);
  // States
  uint8_t keyState[NUM_KEYS];
  uint8_t keypad;
  uint8_t fn;
  uint8_t dvorakQWERTY;
  // aidd a key sequence to be outputted by scanAll()
  // seq will be freed with free() in the end
  // [number of keys] [key1] [key2] ...
  // [number of keys] [key1] [key2] ...
  // 0x00
  void addKeySequence(uint8_t *seq);
  uint8_t *sequence;
  void playKeySequence();
  // Dvorak
  void (Keyboard::*dvorakPressed[NUM_KEYS])();
  void dvorak0(); void dvorak1(); void dvorak2();
  void dvorak3(); void dvorak4(); void dvorak5();
  void dvorak6(); void dvorak7(); void dvorak8();
  void dvorak9(); void dvorak10(); void dvorak11();
  void dvorak12(); void dvorak13(); void dvorak14();
  void dvorak15(); void dvorak16(); void dvorak17();
  void dvorak18(); void dvorak19(); void dvorak20();
  void dvorak21(); void dvorak22(); void dvorak23();
  void dvorak24(); void dvorak25(); void dvorak26();
  void dvorak27(); void dvorak28(); void dvorak29();
  void dvorak30(); void dvorak31(); void dvorak32();
  void dvorak33(); void dvorak34(); void dvorak35();
  void dvorak36(); void dvorak37(); void dvorak38();
  void dvorak39(); void dvorak40(); void dvorak41();
  void dvorak42(); void dvorak43(); void dvorak44();
  void dvorak45(); void dvorak46(); void dvorak47();
  void dvorak48(); void dvorak49(); void dvorak50();
  void dvorak51(); void dvorak52(); void dvorak53();
  void dvorak54(); void dvorak55(); void dvorak56();
  void dvorak57(); void dvorak58(); void dvorak59();
  void dvorak60(); void dvorak61(); void dvorak62();
  void dvorak63(); void dvorak64(); void dvorak65();
  void dvorak66(); void dvorak67(); void dvorak68();
  void dvorak69(); void dvorak70(); void dvorak71();
  void dvorak72(); void dvorak73(); void dvorak74();
  void dvorak75(); void dvorak76(); void dvorak77();
  void dvorak78(); void dvorak79(); void dvorak80();
  void dvorak81(); void dvorak82(); void dvorak83();
  void dvorak84(); void dvorak85(); void dvorak86();
  void dvorak87(); void dvorak88(); void dvorak89();
public:
  Keyboard(FILE *S);
  void scanAll();
  USB_KeyboardReport_Data_t *KeyboardReport;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void keyboardScanAll(USB_KeyboardReport_Data_t *KR);

#ifdef __cplusplus
}
#endif

#endif
