#include "TypeMatrix.h"

#include <Arduino.h>
#include <Wire.h>
#include "MCP23017_registers.h"

#define MCP23017_PIN0 4
#define MCP23017_PIN1 5
#define MCP23017_ADDR0 0x20
#define MCP23017_ADDR1 0x21

#define PRESSED 1
#define RELEASED 0

void TypeMatrix::MCPreset(uint8_t pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(50);
  digitalWrite(pin, HIGH);
}

void TypeMatrix::MCPwrite8(uint8_t i2cAddr, uint8_t baseReg, uint8_t v){
  Wire.beginTransmission(i2cAddr);
  Wire.write(baseReg);
  Wire.write(v);
  Wire.endTransmission();
}

void TypeMatrix::MCPwrite16(uint8_t i2cAddr, uint8_t baseReg, uint8_t v1, uint8_t v2){
  Wire.beginTransmission(i2cAddr);
  Wire.write(baseReg);
  Wire.write(v1);
  Wire.write(v2);
  Wire.endTransmission();
}

uint16_t TypeMatrix::MCPread16(uint8_t i2cAddr, uint8_t baseReg){
  uint16_t v=0;
  Wire.beginTransmission(i2cAddr);
  Wire.write(baseReg);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)i2cAddr, (uint8_t)2);
  v=Wire.read();
  v|=((uint32_t)Wire.read()<<8);
  return v;
}

TypeMatrix::TypeMatrix(){
  // Wire
  Wire.begin();
  // clear states
  for(int i=0;i<NUM_KEYS;i++)
    keyState[0];
  // reset MCPs
  MCPreset(MCP23017_PIN0);
  MCPreset(MCP23017_PIN1);
  // set all pull ups
  MCPwrite16(MCP23017_ADDR0, MCP23017_GPPUA, 0xFF, 0xFF);
  MCPwrite16(MCP23017_ADDR1, MCP23017_GPPUA, 0xFF, 0xFF);
  // States
  numLock=0;
  shift=0;
  keypad=0;
  capsLock=0;
  fn=0;
  dvorakQWERTY=0; // FIXME load from EEPROM
  // Dvorak callbacks (should go to PROGMEM...)
  dvorakPressed={
    &TypeMatrix::dvorakP0,  &TypeMatrix::dvorakP1,  &TypeMatrix::dvorakP2,  &TypeMatrix::dvorakP3,  &TypeMatrix::dvorakP4,
    &TypeMatrix::dvorakP5,  &TypeMatrix::dvorakP6,  &TypeMatrix::dvorakP7,  &TypeMatrix::dvorakP8,  &TypeMatrix::dvorakP9,
    &TypeMatrix::dvorakP10, &TypeMatrix::dvorakP11, &TypeMatrix::dvorakP12, &TypeMatrix::dvorakP13, &TypeMatrix::dvorakP14,
    &TypeMatrix::dvorakP15, &TypeMatrix::dvorakP16, &TypeMatrix::dvorakP17, &TypeMatrix::dvorakP18, &TypeMatrix::dvorakP19,
    &TypeMatrix::dvorakP20, &TypeMatrix::dvorakP21, &TypeMatrix::dvorakP22, &TypeMatrix::dvorakP23, &TypeMatrix::dvorakP24,
    &TypeMatrix::dvorakP25, &TypeMatrix::dvorakP26, &TypeMatrix::dvorakP27, &TypeMatrix::dvorakP28, &TypeMatrix::dvorakP29,
    &TypeMatrix::dvorakP30, &TypeMatrix::dvorakP31, &TypeMatrix::dvorakP32, &TypeMatrix::dvorakP33, &TypeMatrix::dvorakP34,
    &TypeMatrix::dvorakP35, &TypeMatrix::dvorakP36, &TypeMatrix::dvorakP37, &TypeMatrix::dvorakP38, &TypeMatrix::dvorakP39,
    &TypeMatrix::dvorakP40, &TypeMatrix::dvorakP41, &TypeMatrix::dvorakP42, &TypeMatrix::dvorakP43, &TypeMatrix::dvorakP44,
    &TypeMatrix::dvorakP45, &TypeMatrix::dvorakP46, &TypeMatrix::dvorakP47, &TypeMatrix::dvorakP48, &TypeMatrix::dvorakP49,
    &TypeMatrix::dvorakP50, &TypeMatrix::dvorakP51, &TypeMatrix::dvorakP52, &TypeMatrix::dvorakP53, &TypeMatrix::dvorakP54,
    &TypeMatrix::dvorakP55, &TypeMatrix::dvorakP56, &TypeMatrix::dvorakP57, &TypeMatrix::dvorakP58, &TypeMatrix::dvorakP59,
    &TypeMatrix::dvorakP60, &TypeMatrix::dvorakP61, &TypeMatrix::dvorakP62, &TypeMatrix::dvorakP63, &TypeMatrix::dvorakP64,
    &TypeMatrix::dvorakP65, &TypeMatrix::dvorakP66, &TypeMatrix::dvorakP67, &TypeMatrix::dvorakP68, &TypeMatrix::dvorakP69,
    &TypeMatrix::dvorakP70, &TypeMatrix::dvorakP71, &TypeMatrix::dvorakP72, &TypeMatrix::dvorakP73, &TypeMatrix::dvorakP74,
    &TypeMatrix::dvorakP75, &TypeMatrix::dvorakP76, &TypeMatrix::dvorakP77, &TypeMatrix::dvorakP78, &TypeMatrix::dvorakP79,
    &TypeMatrix::dvorakP80, &TypeMatrix::dvorakP81, &TypeMatrix::dvorakP82, &TypeMatrix::dvorakP83, &TypeMatrix::dvorakP84,
    &TypeMatrix::dvorakP85, &TypeMatrix::dvorakP86, &TypeMatrix::dvorakP87, &TypeMatrix::dvorakP88, &TypeMatrix::dvorakP89,
    };
  dvorakReleased={
    &TypeMatrix::dvorakR0,  &TypeMatrix::dvorakR1,  &TypeMatrix::dvorakR2,  &TypeMatrix::dvorakR3,  &TypeMatrix::dvorakR4,
    &TypeMatrix::dvorakR5,  &TypeMatrix::dvorakR6,  &TypeMatrix::dvorakR7,  &TypeMatrix::dvorakR8,  &TypeMatrix::dvorakR9,
    &TypeMatrix::dvorakR10, &TypeMatrix::dvorakR11, &TypeMatrix::dvorakR12, &TypeMatrix::dvorakR13, &TypeMatrix::dvorakR14,
    &TypeMatrix::dvorakR15, &TypeMatrix::dvorakR16, &TypeMatrix::dvorakR17, &TypeMatrix::dvorakR18, &TypeMatrix::dvorakR19,
    &TypeMatrix::dvorakR20, &TypeMatrix::dvorakR21, &TypeMatrix::dvorakR22, &TypeMatrix::dvorakR23, &TypeMatrix::dvorakR24,
    &TypeMatrix::dvorakR25, &TypeMatrix::dvorakR26, &TypeMatrix::dvorakR27, &TypeMatrix::dvorakR28, &TypeMatrix::dvorakR29,
    &TypeMatrix::dvorakR30, &TypeMatrix::dvorakR31, &TypeMatrix::dvorakR32, &TypeMatrix::dvorakR33, &TypeMatrix::dvorakR34,
    &TypeMatrix::dvorakR35, &TypeMatrix::dvorakR36, &TypeMatrix::dvorakR37, &TypeMatrix::dvorakR38, &TypeMatrix::dvorakR39,
    &TypeMatrix::dvorakR40, &TypeMatrix::dvorakR41, &TypeMatrix::dvorakR42, &TypeMatrix::dvorakR43, &TypeMatrix::dvorakR44,
    &TypeMatrix::dvorakR45, &TypeMatrix::dvorakR46, &TypeMatrix::dvorakR47, &TypeMatrix::dvorakR48, &TypeMatrix::dvorakR49,
    &TypeMatrix::dvorakR50, &TypeMatrix::dvorakR51, &TypeMatrix::dvorakR52, &TypeMatrix::dvorakR53, &TypeMatrix::dvorakR54,
    &TypeMatrix::dvorakR55, &TypeMatrix::dvorakR56, &TypeMatrix::dvorakR57, &TypeMatrix::dvorakR58, &TypeMatrix::dvorakR59,
    &TypeMatrix::dvorakR60, &TypeMatrix::dvorakR61, &TypeMatrix::dvorakR62, &TypeMatrix::dvorakR63, &TypeMatrix::dvorakR64,
    &TypeMatrix::dvorakR65, &TypeMatrix::dvorakR66, &TypeMatrix::dvorakR67, &TypeMatrix::dvorakR68, &TypeMatrix::dvorakR69,
    &TypeMatrix::dvorakR70, &TypeMatrix::dvorakR71, &TypeMatrix::dvorakR72, &TypeMatrix::dvorakR73, &TypeMatrix::dvorakR74,
    &TypeMatrix::dvorakR75, &TypeMatrix::dvorakR76, &TypeMatrix::dvorakR77, &TypeMatrix::dvorakR78, &TypeMatrix::dvorakR79,
    &TypeMatrix::dvorakR80, &TypeMatrix::dvorakR81, &TypeMatrix::dvorakR82, &TypeMatrix::dvorakR83, &TypeMatrix::dvorakR84,
    &TypeMatrix::dvorakR85, &TypeMatrix::dvorakR86, &TypeMatrix::dvorakR87, &TypeMatrix::dvorakR88, &TypeMatrix::dvorakR89,
    };
  // Keyboard
  Keyboard.begin();
}

void TypeMatrix::scanPairs(uint8_t lowPin, ...){
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

void TypeMatrix::scanAll(){
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

void TypeMatrix::processKeyEvent(uint8_t key, uint8_t state){
  if(keyState[key]!=state){
    keyState[key]=state;
Serial.print(key);
    if(state){
Serial.println(" Pressed");
      if(dvorakQWERTY){

      }else{
        (this->*dvorakPressed[key])();
      }
    }else{
Serial.println(" Released");
      if(dvorakQWERTY){
      
      }else{
        (this->*dvorakReleased[key])();
      }
    }
  }
}

void TypeMatrix::processRawEvent(uint8_t a, uint8_t b, uint8_t state){
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
