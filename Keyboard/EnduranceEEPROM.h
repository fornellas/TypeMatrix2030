#include <inttypes.h>

class EnduranceEEPROM {
  private:
    uint8_t locations;
    const uint8_t *baseAddr;
    uint8_t pointer;
    uint8_t getNextPointer();
  public:
    // locations max = 255
    EnduranceEEPROM(uint8_t locations, const uint8_t *baseAddr);
    uint8_t read();
    void write(uint8_t value);
};
