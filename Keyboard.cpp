#include "Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Peripheral/TWI.h>

#include <avr/pgmspace.h>
#include <util/delay.h>

#include "MCP23017_registers.h"

#define MCP23017_RESET_DDR_0 DDRD
#define MCP23017_RESET_PORT_0 PORTD
#define MCP23017_RESET_BIT_0 4
#define MCP23017_RESET_DDR_1 DDRC
#define MCP23017_RESET_PORT_1 PORTC
#define MCP23017_RESET_BIT_1 6

#define MCP23017_ADDR0 0x20
#define MCP23017_ADDR1 0x21

#define PRESSED 1
#define RELEASED 0

extern FILE USBSerialStream;

void Keyboard::MCPreset(uint8_t ddr, uint8_t port, uint8_t bit){
  ddr|=(1<<bit); // output
  port&=~(1<<bit); // low
  _delay_ms(50); // sleep
  port|=(1<<bit); // high
}

void Keyboard::MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v){
  if(TWI_StartTransmission(i2cAddr|TWI_ADDRESS_WRITE, 10)==TWI_ERROR_NoError){
    if(!TWI_SendByte(baseReg)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite8(%d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v);
      while(1);
    }
    if(!TWI_SendByte(v)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite8(%d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v);
      while(1);
    }
    TWI_StopTransmission();
  }else{
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite8(%d, %d, %d); TWI_StartTransmission();\r\n"), i2cAddr, baseReg, v);
    while(1);
  }
}

void Keyboard::MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2){
  if(TWI_StartTransmission(i2cAddr|TWI_ADDRESS_WRITE, 10)==TWI_ERROR_NoError){
    if(!TWI_SendByte(baseReg)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite16(%d, %d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v1, v2);
      while(1);
    }
    if(!TWI_SendByte(v1)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite16(%d, %d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v1, v2);
      while(1);
    }
    if(!TWI_SendByte(v2)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite16(%d, %d, %d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg, v1, v2);
      while(1);
    }
    TWI_StopTransmission();
  }else{
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite16(%d, %d, %d, %d); TWI_StartTransmission();\r\n"), i2cAddr, baseReg, v1, v2);
    while(1);
  }
}

uint16_t Keyboard::MCPread16(uint8_t i2cAddr, uint8_t baseReg){
  // Write baseReg
  if(TWI_StartTransmission(i2cAddr|TWI_ADDRESS_WRITE, 10)==TWI_ERROR_NoError){
    if(!TWI_SendByte(baseReg)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPread16(%d, %d); TWI_SendByte();\r\n"), i2cAddr, baseReg);
      while(1);
    }
    TWI_StopTransmission();
    // Read 16 bits
    if(TWI_StartTransmission(i2cAddr|TWI_ADDRESS_READ, 10)==TWI_ERROR_NoError){
      uint16_t v=0;
      uint8_t b1;
      uint8_t b2;
      if(!TWI_ReceiveByte(&b1, false)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPread16(%d, %d); TWI_ReceiveByte();\r\n"), i2cAddr, baseReg);
        while(1);
      }
      if(!TWI_ReceiveByte(&b2, true)){
fprintf_P(&USBSerialStream, PSTR("FAIL MCPread16(%d, %d); TWI_ReceiveByte();\r\n"), i2cAddr, baseReg);
        while(1);
      }
      v=b1;
      v|=((uint16_t)b2)<<8;
      return v;
    }else{
fprintf_P(&USBSerialStream, PSTR("FAIL MCPread16(%d, %d); TWI_StartTransmission();\r\n"), i2cAddr, baseReg);
      while(1);
    }
  }else{
fprintf_P(&USBSerialStream, PSTR("FAIL MCPwrite16(%d, %d); TWI_StartTransmission();\r\n"), i2cAddr, baseReg);
    while(1);
  }
}

Keyboard::Keyboard(){
  // TWI
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 100000L));
  // clear states
  for(int i=0;i<NUM_KEYS;i++)
    keyState[i]=0;
  // reset MCPs
  MCPreset(MCP23017_RESET_DDR_0, MCP23017_RESET_PORT_0, MCP23017_RESET_BIT_0);
  MCPreset(MCP23017_RESET_DDR_1, MCP23017_RESET_PORT_1, MCP23017_RESET_BIT_1);
  // set all pull ups
  MCPwrite16(MCP23017_ADDR0, MCP23017_GPPUA, 0xFF, 0xFF);
  MCPwrite16(MCP23017_ADDR1, MCP23017_GPPUA, 0xFF, 0xFF);
  // States
  numLock=0;
  shift=0;
  keypad=0;
  capsLock=0;
  alt=0;
  fn=0;
  dvorakQWERTY=0; // FIXME load from EEPROM
  // Dvorak callbacks (should go to PROGMEM...)
  dvorakPressed={
    &Keyboard::dvorakP0,  &Keyboard::dvorakP1,  &Keyboard::dvorakP2,  &Keyboard::dvorakP3,  &Keyboard::dvorakP4,
    &Keyboard::dvorakP5,  &Keyboard::dvorakP6,  &Keyboard::dvorakP7,  &Keyboard::dvorakP8,  &Keyboard::dvorakP9,
    &Keyboard::dvorakP10, &Keyboard::dvorakP11, &Keyboard::dvorakP12, &Keyboard::dvorakP13, &Keyboard::dvorakP14,
    &Keyboard::dvorakP15, &Keyboard::dvorakP16, &Keyboard::dvorakP17, &Keyboard::dvorakP18, &Keyboard::dvorakP19,
    &Keyboard::dvorakP20, &Keyboard::dvorakP21, &Keyboard::dvorakP22, &Keyboard::dvorakP23, &Keyboard::dvorakP24,
    &Keyboard::dvorakP25, &Keyboard::dvorakP26, &Keyboard::dvorakP27, &Keyboard::dvorakP28, &Keyboard::dvorakP29,
    &Keyboard::dvorakP30, &Keyboard::dvorakP31, &Keyboard::dvorakP32, &Keyboard::dvorakP33, &Keyboard::dvorakP34,
    &Keyboard::dvorakP35, &Keyboard::dvorakP36, &Keyboard::dvorakP37, &Keyboard::dvorakP38, &Keyboard::dvorakP39,
    &Keyboard::dvorakP40, &Keyboard::dvorakP41, &Keyboard::dvorakP42, &Keyboard::dvorakP43, &Keyboard::dvorakP44,
    &Keyboard::dvorakP45, &Keyboard::dvorakP46, &Keyboard::dvorakP47, &Keyboard::dvorakP48, &Keyboard::dvorakP49,
    &Keyboard::dvorakP50, &Keyboard::dvorakP51, &Keyboard::dvorakP52, &Keyboard::dvorakP53, &Keyboard::dvorakP54,
    &Keyboard::dvorakP55, &Keyboard::dvorakP56, &Keyboard::dvorakP57, &Keyboard::dvorakP58, &Keyboard::dvorakP59,
    &Keyboard::dvorakP60, &Keyboard::dvorakP61, &Keyboard::dvorakP62, &Keyboard::dvorakP63, &Keyboard::dvorakP64,
    &Keyboard::dvorakP65, &Keyboard::dvorakP66, &Keyboard::dvorakP67, &Keyboard::dvorakP68, &Keyboard::dvorakP69,
    &Keyboard::dvorakP70, &Keyboard::dvorakP71, &Keyboard::dvorakP72, &Keyboard::dvorakP73, &Keyboard::dvorakP74,
    &Keyboard::dvorakP75, &Keyboard::dvorakP76, &Keyboard::dvorakP77, &Keyboard::dvorakP78, &Keyboard::dvorakP79,
    &Keyboard::dvorakP80, &Keyboard::dvorakP81, &Keyboard::dvorakP82, &Keyboard::dvorakP83, &Keyboard::dvorakP84,
    &Keyboard::dvorakP85, &Keyboard::dvorakP86, &Keyboard::dvorakP87, &Keyboard::dvorakP88, &Keyboard::dvorakP89,
    };
  dvorakReleased={
    &Keyboard::dvorakR0,  &Keyboard::dvorakR1,  &Keyboard::dvorakR2,  &Keyboard::dvorakR3,  &Keyboard::dvorakR4,
    &Keyboard::dvorakR5,  &Keyboard::dvorakR6,  &Keyboard::dvorakR7,  &Keyboard::dvorakR8,  &Keyboard::dvorakR9,
    &Keyboard::dvorakR10, &Keyboard::dvorakR11, &Keyboard::dvorakR12, &Keyboard::dvorakR13, &Keyboard::dvorakR14,
    &Keyboard::dvorakR15, &Keyboard::dvorakR16, &Keyboard::dvorakR17, &Keyboard::dvorakR18, &Keyboard::dvorakR19,
    &Keyboard::dvorakR20, &Keyboard::dvorakR21, &Keyboard::dvorakR22, &Keyboard::dvorakR23, &Keyboard::dvorakR24,
    &Keyboard::dvorakR25, &Keyboard::dvorakR26, &Keyboard::dvorakR27, &Keyboard::dvorakR28, &Keyboard::dvorakR29,
    &Keyboard::dvorakR30, &Keyboard::dvorakR31, &Keyboard::dvorakR32, &Keyboard::dvorakR33, &Keyboard::dvorakR34,
    &Keyboard::dvorakR35, &Keyboard::dvorakR36, &Keyboard::dvorakR37, &Keyboard::dvorakR38, &Keyboard::dvorakR39,
    &Keyboard::dvorakR40, &Keyboard::dvorakR41, &Keyboard::dvorakR42, &Keyboard::dvorakR43, &Keyboard::dvorakR44,
    &Keyboard::dvorakR45, &Keyboard::dvorakR46, &Keyboard::dvorakR47, &Keyboard::dvorakR48, &Keyboard::dvorakR49,
    &Keyboard::dvorakR50, &Keyboard::dvorakR51, &Keyboard::dvorakR52, &Keyboard::dvorakR53, &Keyboard::dvorakR54,
    &Keyboard::dvorakR55, &Keyboard::dvorakR56, &Keyboard::dvorakR57, &Keyboard::dvorakR58, &Keyboard::dvorakR59,
    &Keyboard::dvorakR60, &Keyboard::dvorakR61, &Keyboard::dvorakR62, &Keyboard::dvorakR63, &Keyboard::dvorakR64,
    &Keyboard::dvorakR65, &Keyboard::dvorakR66, &Keyboard::dvorakR67, &Keyboard::dvorakR68, &Keyboard::dvorakR69,
    &Keyboard::dvorakR70, &Keyboard::dvorakR71, &Keyboard::dvorakR72, &Keyboard::dvorakR73, &Keyboard::dvorakR74,
    &Keyboard::dvorakR75, &Keyboard::dvorakR76, &Keyboard::dvorakR77, &Keyboard::dvorakR78, &Keyboard::dvorakR79,
    &Keyboard::dvorakR80, &Keyboard::dvorakR81, &Keyboard::dvorakR82, &Keyboard::dvorakR83, &Keyboard::dvorakR84,
    &Keyboard::dvorakR85, &Keyboard::dvorakR86, &Keyboard::dvorakR87, &Keyboard::dvorakR88, &Keyboard::dvorakR89,
    };
}

void Keyboard::scanPairs(uint8_t lowPin, ...){
  // set current pin as output
  if(lowPin<8)
    MCPwrite8(MCP23017_ADDR0, MCP23017_IODIRA, ~(1<<lowPin));
  else if(lowPin<16)
    MCPwrite8(MCP23017_ADDR0, MCP23017_IODIRB, ~(1<<(lowPin-8)));
  else if(lowPin<24)
    MCPwrite8(MCP23017_ADDR1, MCP23017_IODIRA, ~(1<<(lowPin-16)));
  else
    MCPwrite8(MCP23017_ADDR1, MCP23017_IODIRB, ~(1<<(lowPin-24)));

  // pin list
  va_list ap;
  int8_t scanPin;
  va_start(ap, lowPin);

  // read all pins
  uint32_t gpio=0;
  gpio=MCPread16(MCP23017_ADDR0, MCP23017_GPIOA);
  gpio|=((uint32_t)MCPread16(MCP23017_ADDR1, MCP23017_GPIOA)<<16);

  // test each supplied pin
  while(true){
    scanPin=va_arg(ap, int);
    if(scanPin==-1)
      break;
    if(~gpio&(1L<<scanPin))
      processRawEvent(lowPin, scanPin, PRESSED);
    else
      processRawEvent(lowPin, scanPin, RELEASED);
  }
  va_end(ap);
  // reset current pin to input
  if(lowPin<8)
    MCPwrite8(MCP23017_ADDR0, MCP23017_IODIRA, 0xFF);
  else if(lowPin<16)
    MCPwrite8(MCP23017_ADDR0, MCP23017_IODIRB, 0xFF);
  else if(lowPin<24)
    MCPwrite8(MCP23017_ADDR1, MCP23017_IODIRA, 0xFF);
  else
    MCPwrite8(MCP23017_ADDR1, MCP23017_IODIRB, 0xFF);
}

void Keyboard::scanAll(){
  // scan all keys
  scanPairs(0, 3, 8, 9, 10, 11, 12, 13, 14, 16, -1);
  scanPairs(1, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 23, -1);
  scanPairs(2, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, -1);
  scanPairs(3, 4, 5, 6, 7, -1);
  scanPairs(4, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, -1);
  scanPairs(5, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 21, 24, -1);
  scanPairs(6, 9, 10, 11, 12, 14, 15, 16, 22, 24, -1);
  scanPairs(7, 8, 9, 10, 11, 12, 13, 15, 19, 24, -1);
  scanPairs(25, 10, 11, 13, 14, 15, 16, 21, 22, 24, -1);
}

void Keyboard::processKeyEvent(uint8_t key, uint8_t state){
  if(keyState[key]!=state){
    keyState[key]=state;
fprintf(&USBSerialStream, PSTR("%d"), key);
    if(state){
fprintf(&USBSerialStream, PSTR(" Pressed\r\n"));
      if(dvorakQWERTY){

      }else{
        (this->*dvorakPressed[key])();
      }
    }else{
fprintf_P(&USBSerialStream, PSTR(" Released\r\n"));
      if(dvorakQWERTY){
      
      }else{
        (this->*dvorakReleased[key])();
      }
    }
  }
}

void Keyboard::processRawEvent(uint8_t a, uint8_t b, uint8_t state){
  switch(a){
    case 0:
      switch(b){
        case 3:
          processKeyEvent(0, state);
          break;
        case 8:
          processKeyEvent(1, state);
          break;
        case 9:
          processKeyEvent(2, state);
          break;
        case 10:
          processKeyEvent(3, state);
          break;
        case 11:
          processKeyEvent(4, state);
          break;
        case 12:
          processKeyEvent(5, state);
          break;
        case 13:
          processKeyEvent(6, state);
          break;
        case 14:
          processKeyEvent(7, state);
          break;
        case 16:
          processKeyEvent(8, state);
          break;
      }
      break;
    case 1:
      switch(b){
        case 3:
          processKeyEvent(9, state);
          break;
        case 8:
          processKeyEvent(10, state);
          break;
        case 9:
          processKeyEvent(11, state);
          break;
        case 10:
          processKeyEvent(12, state);
          break;
        case 11:
          processKeyEvent(13, state);
          break;
        case 12:
          processKeyEvent(14, state);
          break;
        case 13:
          processKeyEvent(15, state);
          break;
        case 14:
          processKeyEvent(16, state);
          break;
        case 15:
          processKeyEvent(17, state);
          break;
        case 16:
          processKeyEvent(18, state);
          break;
        case 18:
          processKeyEvent(19, state);
          break;
        case 20:
          processKeyEvent(20, state);
          break;
        case 23:
          processKeyEvent(21, state);
          break;
      }
      break;
    case 2:
      switch(b){
        case 3:
          processKeyEvent(22, state);
          break;
        case 8:
          processKeyEvent(23, state);
          break;
        case 9:
          processKeyEvent(24, state);
          break;
        case 10:
          processKeyEvent(25, state);
          break;
        case 11:
          processKeyEvent(26, state);
          break;
        case 12:
          processKeyEvent(27, state);
          break;
        case 13:
          processKeyEvent(28, state);
          break;
        case 14:
          processKeyEvent(29, state);
          break;
        case 15:
          processKeyEvent(30, state);
          break;
        case 16:
          processKeyEvent(31, state);
          break;
        case 17:
          processKeyEvent(32, state);
          break;
        case 19:
          processKeyEvent(33, state);
          break;
        case 20:
          processKeyEvent(34, state);
          break;
      }
      break;
    case 3:
      switch(b){
        case 4:
          processKeyEvent(35, state);
          break;
        case 5:
          processKeyEvent(36, state);
          break;
        case 6:
          processKeyEvent(37, state);
          break;
        case 7:
          processKeyEvent(38, state);
          break;
      }
      break;
    case 4:
      switch(b){
        case 8:
          processKeyEvent(39, state);
          break;
        case 9:
          processKeyEvent(40, state);
          break;
        case 10:
          processKeyEvent(41, state);
          break;
        case 11:
          processKeyEvent(42, state);
          break;
        case 12:
          processKeyEvent(43, state);
          break;
        case 13:
          processKeyEvent(44, state);
          break;
        case 14:
          processKeyEvent(45, state);
          break;
        case 15:
          processKeyEvent(46, state);
          break;
        case 16:
          processKeyEvent(47, state);
          break;
        case 18:
          processKeyEvent(48, state);
          break;
        case 20:
          processKeyEvent(49, state);
          break;
      }
      break;
    case 5:
      switch(b){
        case 8:
          processKeyEvent(50, state);
          break;
        case 9:
          processKeyEvent(51, state);
          break;
        case 10:
          processKeyEvent(52, state);
          break;
        case 11:
          processKeyEvent(53, state);
          break;
        case 12:
          processKeyEvent(54, state);
          break;
        case 13:
          processKeyEvent(55, state);
          break;
        case 14:
          processKeyEvent(56, state);
          break;
        case 15:
          processKeyEvent(57, state);
          break;
        case 16:
          processKeyEvent(58, state);
          break;
        case 17:
          processKeyEvent(59, state);
          break;
        case 19:
          processKeyEvent(60, state);
          break;
        case 21:
          processKeyEvent(61, state);
          break;
        case 24:
          processKeyEvent(62, state);
          break;
      }
      break;
    case 6:
      switch(b){
        case 9:
          processKeyEvent(63, state);
          break;
        case 10:
          processKeyEvent(64, state);
          break;
        case 11:
          processKeyEvent(65, state);
          break;
        case 12:
          processKeyEvent(66, state);
          break;
        case 14:
          processKeyEvent(67, state);
          break;
        case 15:
          processKeyEvent(68, state);
          break;
        case 16:
          processKeyEvent(69, state);
          break;
        case 22:
          processKeyEvent(70, state);
          break;
        case 24:
          processKeyEvent(71, state);
          break;
      }
      break;
    case 7:
      switch(b){
        case 8:
          processKeyEvent(72, state);
          break;
        case 9:
          processKeyEvent(73, state);
          break;
        case 10:
          processKeyEvent(74, state);
          break;
        case 11:
          processKeyEvent(75, state);
          break;
        case 12:
          processKeyEvent(76, state);
          break;
        case 13:
          processKeyEvent(77, state);
          break;
        case 15:
          processKeyEvent(78, state);
          break;
        case 19:
          processKeyEvent(79, state);
          break;
        case 24:
          processKeyEvent(80, state);
          break;
      }
      break;
    case 25:
      switch(b){
        case 10:
          processKeyEvent(81, state);
          break;
        case 11:
          processKeyEvent(82, state);
          break;
        case 13:
          processKeyEvent(83, state);
          break;
        case 14:
          processKeyEvent(84, state);
          break;
        case 15:
          processKeyEvent(85, state);
          break;
        case 16:
          processKeyEvent(86, state);
          break;
        case 21:
          processKeyEvent(87, state);
          break;
        case 22:
          processKeyEvent(88, state);
          break;
        case 24:
          processKeyEvent(89, state);
          break;
      }
      break;
  }
}
