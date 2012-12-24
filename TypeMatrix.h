#ifndef TypeMatrix_h
#define TypeMatrix_h

#include <inttypes.h>
#include <stdarg.h>

#define NUM_KEYS 90

class TypeMatrix {
private:
  // pressed state for each key
  uint8_t keyState[NUM_KEYS];
  // reset MCP
  inline void MCPreset(uint8_t pin);
  // writes two 8/16bit vales starting at baseReg address
  inline void MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v);
  inline void MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2);
  // reads 16bit values starting at baseReg
  inline uint16_t MCPread16(uint8_t i2cAddr, uint8_t baseReg);
  // set lowPin to low and scan other asked pins for low signal. Last arg must be -1.
  inline void scanPairs(uint8_t lowPin, ...);
  // Process key event
  inline void processRawEvent(uint8_t a, uint8_t b, uint8_t pressed);
  inline void processKeyEvent(uint8_t key, uint8_t pressed);
public:
  TypeMatrix();
  void scanAll();
};

#endif
