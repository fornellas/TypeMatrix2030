#ifndef Keyboard_h
#define Keyboard_h

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#define NUM_KEYS 90

class Keyboard {
private:
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
   void processKeyEvent(uint8_t key, uint8_t state);
  // key pressses
  void press(uint8_t key);
  void release(uint8_t key);
  // States
  uint8_t numLock;
  uint8_t shift;
  uint8_t keypad;
  uint8_t fn;
  uint8_t capsLock;
  uint8_t alt;
  uint8_t dvorakQWERTY;
  uint8_t keyState[NUM_KEYS];
  // Dvorak
  void (Keyboard::*dvorakPressed[NUM_KEYS])();
  void (Keyboard::*dvorakReleased[NUM_KEYS])();
  void dvorakP0(); void dvorakR0();
  void dvorakP1(); void dvorakR1();
  void dvorakP2(); void dvorakR2();
  void dvorakP3(); void dvorakR3();
  void dvorakP4(); void dvorakR4();
  void dvorakP5(); void dvorakR5();
  void dvorakP6(); void dvorakR6();
  void dvorakP7(); void dvorakR7();
  void dvorakP8(); void dvorakR8();
  void dvorakP9(); void dvorakR9();
  void dvorakP10(); void dvorakR10();
  void dvorakP11(); void dvorakR11();
  void dvorakP12(); void dvorakR12();
  void dvorakP13(); void dvorakR13();
  void dvorakP14(); void dvorakR14();
  void dvorakP15(); void dvorakR15();
  void dvorakP16(); void dvorakR16();
  void dvorakP17(); void dvorakR17();
  void dvorakP18(); void dvorakR18();
  void dvorakP19(); void dvorakR19();
  void dvorakP20(); void dvorakR20();
  void dvorakP21(); void dvorakR21();
  void dvorakP22(); void dvorakR22();
  void dvorakP23(); void dvorakR23();
  void dvorakP24(); void dvorakR24();
  void dvorakP25(); void dvorakR25();
  void dvorakP26(); void dvorakR26();
  void dvorakP27(); void dvorakR27();
  void dvorakP28(); void dvorakR28();
  void dvorakP29(); void dvorakR29();
  void dvorakP30(); void dvorakR30();
  void dvorakP31(); void dvorakR31();
  void dvorakP32(); void dvorakR32();
  void dvorakP33(); void dvorakR33();
  void dvorakP34(); void dvorakR34();
  void dvorakP35(); void dvorakR35();
  void dvorakP36(); void dvorakR36();
  void dvorakP37(); void dvorakR37();
  void dvorakP38(); void dvorakR38();
  void dvorakP39(); void dvorakR39();
  void dvorakP40(); void dvorakR40();
  void dvorakP41(); void dvorakR41();
  void dvorakP42(); void dvorakR42();
  void dvorakP43(); void dvorakR43();
  void dvorakP44(); void dvorakR44();
  void dvorakP45(); void dvorakR45();
  void dvorakP46(); void dvorakR46();
  void dvorakP47(); void dvorakR47();
  void dvorakP48(); void dvorakR48();
  void dvorakP49(); void dvorakR49();
  void dvorakP50(); void dvorakR50();
  void dvorakP51(); void dvorakR51();
  void dvorakP52(); void dvorakR52();
  void dvorakP53(); void dvorakR53();
  void dvorakP54(); void dvorakR54();
  void dvorakP55(); void dvorakR55();
  void dvorakP56(); void dvorakR56();
  void dvorakP57(); void dvorakR57();
  void dvorakP58(); void dvorakR58();
  void dvorakP59(); void dvorakR59();
  void dvorakP60(); void dvorakR60();
  void dvorakP61(); void dvorakR61();
  void dvorakP62(); void dvorakR62();
  void dvorakP63(); void dvorakR63();
  void dvorakP64(); void dvorakR64();
  void dvorakP65(); void dvorakR65();
  void dvorakP66(); void dvorakR66();
  void dvorakP67(); void dvorakR67();
  void dvorakP68(); void dvorakR68();
  void dvorakP69(); void dvorakR69();
  void dvorakP70(); void dvorakR70();
  void dvorakP71(); void dvorakR71();
  void dvorakP72(); void dvorakR72();
  void dvorakP73(); void dvorakR73();
  void dvorakP74(); void dvorakR74();
  void dvorakP75(); void dvorakR75();
  void dvorakP76(); void dvorakR76();
  void dvorakP77(); void dvorakR77();
  void dvorakP78(); void dvorakR78();
  void dvorakP79(); void dvorakR79();
  void dvorakP80(); void dvorakR80();
  void dvorakP81(); void dvorakR81();
  void dvorakP82(); void dvorakR82();
  void dvorakP83(); void dvorakR83();
  void dvorakP84(); void dvorakR84();
  void dvorakP85(); void dvorakR85();
  void dvorakP86(); void dvorakR86();
  void dvorakP87(); void dvorakR87();
  void dvorakP88(); void dvorakR88();
  void dvorakP89(); void dvorakR89();
public:
  Keyboard(FILE *S);
  void scanAll();
};

#endif
