#include "TypeMatrix.h"

#include <Arduino.h>
#include <Wire.h>
#include "MCP23017_registers.h"

#define MCP23017_PIN0 4
#define MCP23017_PIN1 5
#define MCP23017_ADDR0 0x20
#define MCP23017_ADDR1 0x21

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
  // clear pressed keys
  for(int i=0;i<NUM_KEYS;i++)
    keyState[0];
  // reset MCPs
  MCPreset(MCP23017_PIN0);
  MCPreset(MCP23017_PIN1);
  // set all pull ups
  MCPwrite16(MCP23017_ADDR0, MCP23017_GPPUA, 0xFF, 0xFF);
  MCPwrite16(MCP23017_ADDR1, MCP23017_GPPUA, 0xFF, 0xFF);
  // Keyboard
  Keyboard.begin();
}

//int counter=0;
void TypeMatrix::scanPairs(uint8_t lowPin, ...){
//Serial.println("scanPairs start...");Serial.flush();
//uint8_t values[26];
//for(int i=0;i<26;i++)
//  values[i]=0;
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
//  while(-1!=(scanPin=va_arg(va, int8_t))){
  while(true){
    scanPin=va_arg(ap, int);
//Serial.print("scanPin=");Serial.flush();
//Serial.println(scanPin);Serial.flush();
    if(scanPin==-1)
      break;
    if(~gpio&(1L<<scanPin)){
//values[lowPin]=1;
//values[scanPin]=1;
      processRawEvent(lowPin, scanPin, 1);
    } else
      processRawEvent(lowPin, scanPin, 0);
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

// Print results
//Serial.print(counter++);
//Serial.print(": ");
//for(int i=0;i<26;i++){
//  if(values[i]){
//    if(i<10)
//      Serial.print(' ');
//    Serial.print(i);
//  } else
//    Serial.print(" .");
//  Serial.print(' ');
//}
//Serial.println("");Serial.flush();
//Serial.println("scanPairs exit.");Serial.flush();
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

void TypeMatrix::processKeyEvent(uint8_t key, uint8_t pressed){
  if(keyState[key]!=pressed){
    keyState[key]=pressed;
    Serial.print(key);
    if(pressed){
      Serial.println(" Pressed");
    }else{
      Serial.println(" Released");
    }
  }
}

void TypeMatrix::processRawEvent(uint8_t a, uint8_t b, uint8_t pressed){
  switch(a){
    case 0:
      switch(b){
        case 3:
          processKeyEvent(0, pressed);
          break;
        case 8:
          processKeyEvent(1, pressed);
          break;
        case 9:
          processKeyEvent(2, pressed);
          break;
        case 10:
          processKeyEvent(3, pressed);
          break;
        case 11:
          processKeyEvent(4, pressed);
          break;
        case 12:
          processKeyEvent(5, pressed);
          break;
        case 13:
          processKeyEvent(6, pressed);
          break;
        case 14:
          processKeyEvent(7, pressed);
          break;
        case 16:
          processKeyEvent(8, pressed);
          break;
      }
      break;
    case 1:
      switch(b){
        case 3:
          processKeyEvent(9, pressed);
          break;
        case 8:
          processKeyEvent(10, pressed);
          break;
        case 9:
          processKeyEvent(11, pressed);
          break;
        case 10:
          processKeyEvent(12, pressed);
          break;
        case 11:
          processKeyEvent(13, pressed);
          break;
        case 12:
          processKeyEvent(14, pressed);
          break;
        case 13:
          processKeyEvent(15, pressed);
          break;
        case 14:
          processKeyEvent(16, pressed);
          break;
        case 15:
          processKeyEvent(17, pressed);
          break;
        case 16:
          processKeyEvent(18, pressed);
          break;
        case 18:
          processKeyEvent(19, pressed);
          break;
        case 20:
          processKeyEvent(20, pressed);
          break;
        case 23:
          processKeyEvent(21, pressed);
          break;
      }
      break;
    case 2:
      switch(b){
        case 3:
          processKeyEvent(22, pressed);
          break;
        case 8:
          processKeyEvent(23, pressed);
          break;
        case 9:
          processKeyEvent(24, pressed);
          break;
        case 10:
          processKeyEvent(25, pressed);
          break;
        case 11:
          processKeyEvent(26, pressed);
          break;
        case 12:
          processKeyEvent(27, pressed);
          break;
        case 13:
          processKeyEvent(28, pressed);
          break;
        case 14:
          processKeyEvent(29, pressed);
          break;
        case 15:
          processKeyEvent(30, pressed);
          break;
        case 16:
          processKeyEvent(31, pressed);
          break;
        case 17:
          processKeyEvent(32, pressed);
          break;
        case 19:
          processKeyEvent(33, pressed);
          break;
        case 20:
          processKeyEvent(34, pressed);
          break;
      }
      break;
    case 3:
      switch(b){
        case 4:
          processKeyEvent(35, pressed);
          break;
        case 5:
          processKeyEvent(36, pressed);
          break;
        case 6:
          processKeyEvent(37, pressed);
          break;
        case 7:
          processKeyEvent(38, pressed);
          break;
      }
      break;
    case 4:
      switch(b){
        case 8:
          processKeyEvent(39, pressed);
          break;
        case 9:
          processKeyEvent(40, pressed);
          break;
        case 10:
          processKeyEvent(41, pressed);
          break;
        case 11:
          processKeyEvent(42, pressed);
          break;
        case 12:
          processKeyEvent(43, pressed);
          break;
        case 13:
          processKeyEvent(44, pressed);
          break;
        case 14:
          processKeyEvent(45, pressed);
          break;
        case 15:
          processKeyEvent(46, pressed);
          break;
        case 16:
          processKeyEvent(47, pressed);
          break;
        case 18:
          processKeyEvent(48, pressed);
          break;
        case 20:
          processKeyEvent(49, pressed);
          break;
      }
      break;
    case 5:
      switch(b){
        case 8:
          processKeyEvent(50, pressed);
          break;
        case 9:
          processKeyEvent(51, pressed);
          break;
        case 10:
          processKeyEvent(52, pressed);
          break;
        case 11:
          processKeyEvent(53, pressed);
          break;
        case 12:
          processKeyEvent(54, pressed);
          break;
        case 13:
          processKeyEvent(55, pressed);
          break;
        case 14:
          processKeyEvent(56, pressed);
          break;
        case 15:
          processKeyEvent(57, pressed);
          break;
        case 16:
          processKeyEvent(58, pressed);
          break;
        case 17:
          processKeyEvent(59, pressed);
          break;
        case 19:
          processKeyEvent(60, pressed);
          break;
        case 21:
          processKeyEvent(61, pressed);
          break;
        case 24:
          processKeyEvent(62, pressed);
          break;
      }
      break;
    case 6:
      switch(b){
        case 9:
          processKeyEvent(63, pressed);
          break;
        case 10:
          processKeyEvent(64, pressed);
          break;
        case 11:
          processKeyEvent(65, pressed);
          break;
        case 12:
          processKeyEvent(66, pressed);
          break;
        case 14:
          processKeyEvent(67, pressed);
          break;
        case 15:
          processKeyEvent(68, pressed);
          break;
        case 16:
          processKeyEvent(69, pressed);
          break;
        case 22:
          processKeyEvent(70, pressed);
          break;
        case 24:
          processKeyEvent(71, pressed);
          break;
      }
      break;
    case 7:
      switch(b){
        case 8:
          processKeyEvent(72, pressed);
          break;
        case 9:
          processKeyEvent(73, pressed);
          break;
        case 10:
          processKeyEvent(74, pressed);
          break;
        case 11:
          processKeyEvent(75, pressed);
          break;
        case 12:
          processKeyEvent(76, pressed);
          break;
        case 13:
          processKeyEvent(77, pressed);
          break;
        case 15:
          processKeyEvent(78, pressed);
          break;
        case 19:
          processKeyEvent(79, pressed);
          break;
        case 24:
          processKeyEvent(80, pressed);
          break;
      }
      break;
    case 25:
      switch(b){
        case 10:
          processKeyEvent(81, pressed);
          break;
        case 11:
          processKeyEvent(82, pressed);
          break;
        case 13:
          processKeyEvent(83, pressed);
          break;
        case 14:
          processKeyEvent(84, pressed);
          break;
        case 15:
          processKeyEvent(85, pressed);
          break;
        case 16:
          processKeyEvent(86, pressed);
          break;
        case 21:
          processKeyEvent(87, pressed);
          break;
        case 22:
          processKeyEvent(88, pressed);
          break;
        case 24:
          processKeyEvent(89, pressed);
          break;
      }
      break;
  }
}
