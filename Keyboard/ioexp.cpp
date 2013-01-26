#include "Keyboard.h"

extern "C" {
#include "LUFA.h"
}

#include <LUFA/Drivers/Peripheral/TWI.h>

//
// Registers
//

#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

//
// Pin mappings
//

#define MCP23017_RESET_DDR_0 DDRD
#define MCP23017_RESET_PORT_0 PORTD
#define MCP23017_RESET_BIT_0 4
#define MCP23017_RESET_DDR_1 DDRC
#define MCP23017_RESET_PORT_1 PORTC
#define MCP23017_RESET_BIT_1 6

//
// Addresses
//

#define MCP23017_ADDR_0 0b01000000
#define MCP23017_ADDR_1 0b01000010

//
// Methods
//

void Keyboard::MCPinit(){
  // reset MCPs
  MCPreset(&MCP23017_RESET_DDR_0, &MCP23017_RESET_PORT_0, MCP23017_RESET_BIT_0);
  MCPreset(&MCP23017_RESET_DDR_1, &MCP23017_RESET_PORT_1, MCP23017_RESET_BIT_1);
  // set all pull ups
  MCPwrite16(MCP23017_ADDR_0, MCP23017_GPPUA, 0xFF, 0xFF);
  MCPwrite16(MCP23017_ADDR_1, MCP23017_GPPUA, 0xFF, 0xFF);
}

void Keyboard::MCPreset(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit){
  *ddr|=(1<<bit); // output
  *port&=~(1<<bit); // low
  _delay_ms(50); // sleep
  *port|=(1<<bit); // high
}

void Keyboard::MCPsetPin(uint8_t lowPin, bool dir){
  // set current pin as output
  if(lowPin<8){
    if(dir)
      MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRA, 0xFF);
    else
      MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRA, ~(1<<lowPin));
  }else if(lowPin<16){
    if(dir)
      MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRB, 0xFF);
    else
      MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRB, ~(1<<(lowPin-8)));
  }else if(lowPin<24){
    if(dir)
      MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRA, 0xFF);
    else
      MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRA, ~(1<<(lowPin-16)));
  }else{
    if(dir)
      MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRB, 0xFF);
    else
      MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRB, ~(1<<(lowPin-24)));
  }
}

uint32_t Keyboard::MCPreadPins(){
  uint32_t gpio=0;
  gpio=MCPread16(MCP23017_ADDR_0, MCP23017_GPIOA);
  gpio|=((uint32_t)MCPread16(MCP23017_ADDR_1, MCP23017_GPIOA)<<16);
  return gpio;
}

void Keyboard::MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v){
  if(TWI_WritePacket(i2cAddr, 10, &baseReg, sizeof(baseReg), &v, sizeof(v))!=TWI_ERROR_NoError)
    while(1)
      fprintf_P(Stream, PSTR("FAIL MCPwrite8(%d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v);
}

void Keyboard::MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2){
  uint8_t v[2]={v1, v2};
  if(TWI_WritePacket(i2cAddr, 10, &baseReg, sizeof(baseReg), v, sizeof(v))!=TWI_ERROR_NoError)
    while(1)
      fprintf_P(Stream, PSTR("FAIL MCPwrite16(%d, %d, %d, %d);\r\n"), i2cAddr, baseReg, v1, v2);
}

uint16_t Keyboard::MCPread16(uint8_t i2cAddr, uint8_t baseReg){
  uint8_t v[2];
  uint16_t r=0;
  if(TWI_ReadPacket(i2cAddr, 10, &baseReg, sizeof(baseReg), v, sizeof(v))!=TWI_ERROR_NoError)
    while(1)
      fprintf_P(Stream, PSTR("FAIL MCPread16(%d, %d);\r\n"), i2cAddr, baseReg);
  r=v[0];
  r|=((uint16_t)v[1])<<8;
  return r;
}
