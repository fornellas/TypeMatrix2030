#ifndef EnduranceEEPROM_h
#define EnduranceEEPROM_h

#include <inttypes.h>

class EnduranceEEPROM {
  private:
    uint8_t locations;
    const uint8_t *baseAddr;
    uint8_t pointer;
    uint8_t getNextPointer();
    void loadPointer();
  public:
    // locations max = 255
    EnduranceEEPROM(uint8_t locations, uint8_t *baseAddr);
    uint8_t read();
    void write(uint8_t value);
};

#endif
