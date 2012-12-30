#include "Keyboard.h"

extern "C" {
#include "LUFA.h"
}

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

#define MCP23017_ADDR_0 0b01000000
#define MCP23017_ADDR_1 0b01000010

#define PRESSED 1
#define RELEASED 0

void Keyboard::MCPreset(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t bit){
  *ddr|=(1<<bit); // output
  *port&=~(1<<bit); // low
  _delay_ms(50); // sleep
  *port|=(1<<bit); // high
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

Keyboard::Keyboard(FILE *S){
  // Serial
  Stream=S;
  // reset MCPs
  MCPreset(&MCP23017_RESET_DDR_0, &MCP23017_RESET_PORT_0, MCP23017_RESET_BIT_0);
  MCPreset(&MCP23017_RESET_DDR_1, &MCP23017_RESET_PORT_1, MCP23017_RESET_BIT_1);
  // TWI
  PORTD|=(1<<1); // SDA pull up
  PORTD|=(1<<0); // SCL pull up
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 100000L));
  // set all pull ups
  MCPwrite16(MCP23017_ADDR_0, MCP23017_GPPUA, 0xFF, 0xFF);
  MCPwrite16(MCP23017_ADDR_1, MCP23017_GPPUA, 0xFF, 0xFF);
  // States
  numLock=0;
  keypad=0;
  capsLock=0;
  fn=0;
  dvorakQWERTY=0; // FIXME load from EEPROM
  // Dvorak callbacks (should go to PROGMEM...)
  dvorakPressed={
    &Keyboard::dvorak0,  &Keyboard::dvorak1,  &Keyboard::dvorak2,  &Keyboard::dvorak3,  &Keyboard::dvorak4,
    &Keyboard::dvorak5,  &Keyboard::dvorak6,  &Keyboard::dvorak7,  &Keyboard::dvorak8,  &Keyboard::dvorak9,
    &Keyboard::dvorak10, &Keyboard::dvorak11, &Keyboard::dvorak12, &Keyboard::dvorak13, &Keyboard::dvorak14,
    &Keyboard::dvorak15, &Keyboard::dvorak16, &Keyboard::dvorak17, &Keyboard::dvorak18, &Keyboard::dvorak19,
    &Keyboard::dvorak20, &Keyboard::dvorak21, &Keyboard::dvorak22, &Keyboard::dvorak23, &Keyboard::dvorak24,
    &Keyboard::dvorak25, &Keyboard::dvorak26, &Keyboard::dvorak27, &Keyboard::dvorak28, &Keyboard::dvorak29,
    &Keyboard::dvorak30, &Keyboard::dvorak31, &Keyboard::dvorak32, &Keyboard::dvorak33, &Keyboard::dvorak34,
    &Keyboard::dvorak35, &Keyboard::dvorak36, &Keyboard::dvorak37, &Keyboard::dvorak38, &Keyboard::dvorak39,
    &Keyboard::dvorak40, &Keyboard::dvorak41, &Keyboard::dvorak42, &Keyboard::dvorak43, &Keyboard::dvorak44,
    &Keyboard::dvorak45, &Keyboard::dvorak46, &Keyboard::dvorak47, &Keyboard::dvorak48, &Keyboard::dvorak49,
    &Keyboard::dvorak50, &Keyboard::dvorak51, &Keyboard::dvorak52, &Keyboard::dvorak53, &Keyboard::dvorak54,
    &Keyboard::dvorak55, &Keyboard::dvorak56, &Keyboard::dvorak57, &Keyboard::dvorak58, &Keyboard::dvorak59,
    &Keyboard::dvorak60, &Keyboard::dvorak61, &Keyboard::dvorak62, &Keyboard::dvorak63, &Keyboard::dvorak64,
    &Keyboard::dvorak65, &Keyboard::dvorak66, &Keyboard::dvorak67, &Keyboard::dvorak68, &Keyboard::dvorak69,
    &Keyboard::dvorak70, &Keyboard::dvorak71, &Keyboard::dvorak72, &Keyboard::dvorak73, &Keyboard::dvorak74,
    &Keyboard::dvorak75, &Keyboard::dvorak76, &Keyboard::dvorak77, &Keyboard::dvorak78, &Keyboard::dvorak79,
    &Keyboard::dvorak80, &Keyboard::dvorak81, &Keyboard::dvorak82, &Keyboard::dvorak83, &Keyboard::dvorak84,
    &Keyboard::dvorak85, &Keyboard::dvorak86, &Keyboard::dvorak87, &Keyboard::dvorak88, &Keyboard::dvorak89,
    };
}

void Keyboard::scanPairs(uint8_t lowPin, ...){
  // set current pin as output
  if(lowPin<8)
    MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRA, ~(1<<lowPin));
  else if(lowPin<16)
    MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRB, ~(1<<(lowPin-8)));
  else if(lowPin<24)
    MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRA, ~(1<<(lowPin-16)));
  else
    MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRB, ~(1<<(lowPin-24)));

  // pin list
  va_list ap;
  int8_t scanPin;
  va_start(ap, lowPin);

  // read all pins
  uint32_t gpio=0;
  gpio=MCPread16(MCP23017_ADDR_0, MCP23017_GPIOA);
  gpio|=((uint32_t)MCPread16(MCP23017_ADDR_1, MCP23017_GPIOA)<<16);

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
    MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRA, 0xFF);
  else if(lowPin<16)
    MCPwrite8(MCP23017_ADDR_0, MCP23017_IODIRB, 0xFF);
  else if(lowPin<24)
    MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRA, 0xFF);
  else
    MCPwrite8(MCP23017_ADDR_1, MCP23017_IODIRB, 0xFF);
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

void Keyboard::processKeyEvent(uint8_t key){
  if(dvorakQWERTY){

  }else{
    (this->*dvorakPressed[key])();
  }
}

#define SETMOD(key, value) case key: KeyboardReport->Modifier|=value;break;
void Keyboard::press(uint8_t key){
fprintf_P(Stream, PSTR("  press() %d +++\r\n"), key);
  switch(key){
    SETMOD(HID_KEYBOARD_SC_LEFT_CONTROL, HID_KEYBOARD_MODIFIER_LEFTCTRL);
    SETMOD(HID_KEYBOARD_SC_LEFT_SHIFT, HID_KEYBOARD_MODIFIER_LEFTSHIFT);
    SETMOD(HID_KEYBOARD_SC_LEFT_ALT, HID_KEYBOARD_MODIFIER_LEFTALT);
    SETMOD(HID_KEYBOARD_SC_LEFT_GUI, HID_KEYBOARD_MODIFIER_LEFTGUI);
    SETMOD(HID_KEYBOARD_SC_RIGHT_CONTROL, HID_KEYBOARD_MODIFIER_RIGHTCTRL);
    SETMOD(HID_KEYBOARD_SC_RIGHT_SHIFT, HID_KEYBOARD_MODIFIER_RIGHTSHIFT);
    SETMOD(HID_KEYBOARD_SC_RIGHT_ALT, HID_KEYBOARD_MODIFIER_RIGHTALT);
    SETMOD(HID_KEYBOARD_SC_RIGHT_GUI, HID_KEYBOARD_MODIFIER_RIGHTGUI);
    default:
      for(uint8_t i=0;i<6;i++){
        if(KeyboardReport->KeyCode[i]==0){
          KeyboardReport->KeyCode[i]=key;
          break;
        }
      }
      break;
  }
}

#define UNSETMOD(key, value) case key: KeyboardReport->Modifier&=~value;break;
void Keyboard::release(uint8_t key){
fprintf_P(Stream, PSTR("  release() %d ---\r\n"), key);
  switch(key){
    UNSETMOD(HID_KEYBOARD_SC_LEFT_CONTROL, HID_KEYBOARD_MODIFIER_LEFTCTRL);
    UNSETMOD(HID_KEYBOARD_SC_LEFT_SHIFT, HID_KEYBOARD_MODIFIER_LEFTSHIFT);
    UNSETMOD(HID_KEYBOARD_SC_LEFT_ALT, HID_KEYBOARD_MODIFIER_LEFTALT);
    UNSETMOD(HID_KEYBOARD_SC_LEFT_GUI, HID_KEYBOARD_MODIFIER_LEFTGUI);
    UNSETMOD(HID_KEYBOARD_SC_RIGHT_CONTROL, HID_KEYBOARD_MODIFIER_RIGHTCTRL);
    UNSETMOD(HID_KEYBOARD_SC_RIGHT_SHIFT, HID_KEYBOARD_MODIFIER_RIGHTSHIFT);
    UNSETMOD(HID_KEYBOARD_SC_RIGHT_ALT, HID_KEYBOARD_MODIFIER_RIGHTALT);
    UNSETMOD(HID_KEYBOARD_SC_RIGHT_GUI, HID_KEYBOARD_MODIFIER_RIGHTGUI);
    default:
      for(uint8_t i=0;i<6;i++){
        if(KeyboardReport->KeyCode[i]==key){
          KeyboardReport->KeyCode[i]=0;
          break;
        }
      }
      break;
  }
}

void Keyboard::processRawEvent(uint8_t a, uint8_t b, uint8_t pressed){
  switch(a){
    case 0:
      switch(b){
        case 3:
          if(pressed)processKeyEvent(0);
          break;
        case 8:
          if(pressed)processKeyEvent(1);
          break;
        case 9:
          if(pressed)processKeyEvent(2);
          break;
        case 10:
          if(pressed)processKeyEvent(3);
          break;
        case 11:
          if(pressed)processKeyEvent(4);
          break;
        case 12:
          if(pressed)processKeyEvent(5);
          break;
        case 13:
          if(pressed)processKeyEvent(6);
          break;
        case 14:
          if(pressed)processKeyEvent(7);
          break;
        case 16:
          if(pressed)processKeyEvent(8);
          break;
      }
      break;
    case 1:
      switch(b){
        case 3:
          if(pressed)processKeyEvent(9);
          break;
        case 8:
          if(pressed)processKeyEvent(10);
          break;
        case 9:
          if(pressed)processKeyEvent(11);
          break;
        case 10:
          if(pressed)processKeyEvent(12);
          break;
        case 11:
          if(pressed)processKeyEvent(13);
          break;
        case 12:
          if(pressed)processKeyEvent(14);
          break;
        case 13:
          if(pressed)processKeyEvent(15);
          break;
        case 14:
          if(pressed)processKeyEvent(16);
          break;
        case 15:
          if(pressed)processKeyEvent(17);
          break;
        case 16:
          if(pressed)processKeyEvent(18);
          break;
        case 18:
          if(pressed)processKeyEvent(19);
          break;
        case 20:
          if(pressed)processKeyEvent(20);
          break;
        case 23:
          if(pressed)processKeyEvent(21);
          break;
      }
      break;
    case 2:
      switch(b){
        case 3:
          if(pressed)processKeyEvent(22);
          break;
        case 8:
          if(pressed)processKeyEvent(23);
          break;
        case 9:
          if(pressed)processKeyEvent(24);
          break;
        case 10:
          if(pressed)processKeyEvent(25);
          break;
        case 11:
          if(pressed)processKeyEvent(26);
          break;
        case 12:
          if(pressed)processKeyEvent(27);
          break;
        case 13:
          if(pressed)processKeyEvent(28);
          break;
        case 14:
          if(pressed)processKeyEvent(29);
          break;
        case 15:
          if(pressed)processKeyEvent(30);
          break;
        case 16:
          if(pressed)processKeyEvent(31);
          break;
        case 17:
          if(pressed)processKeyEvent(32);
          break;
        case 19:
          if(pressed)processKeyEvent(33);
          break;
        case 20:
          if(pressed)
            fn=1;
          else
            fn=0;
          break;
      }
      break;
    case 3:
      switch(b){
        case 4:
          if(pressed)processKeyEvent(35);
          break;
        case 5:
          if(pressed)processKeyEvent(36);
          break;
        case 6:
          if(pressed)processKeyEvent(37);
          break;
        case 7:
          if(pressed)processKeyEvent(38);
          break;
      }
      break;
    case 4:
      switch(b){
        case 8:
          if(pressed)processKeyEvent(39);
          break;
        case 9:
          if(pressed)processKeyEvent(40);
          break;
        case 10:
          if(pressed)processKeyEvent(41);
          break;
        case 11:
          if(pressed)processKeyEvent(42);
          break;
        case 12:
          if(pressed)processKeyEvent(43);
          break;
        case 13:
          if(pressed)processKeyEvent(44);
          break;
        case 14:
          if(pressed)processKeyEvent(45);
          break;
        case 15:
          if(pressed)processKeyEvent(46);
          break;
        case 16:
          if(pressed)processKeyEvent(47);
          break;
        case 18:
          if(pressed)processKeyEvent(48);
          break;
        case 20:
          if(pressed)processKeyEvent(49);
          break;
      }
      break;
    case 5:
      switch(b){
        case 8:
          if(pressed)processKeyEvent(50);
          break;
        case 9:
          if(pressed)processKeyEvent(51);
          break;
        case 10:
          if(pressed)processKeyEvent(52);
          break;
        case 11:
          if(pressed)processKeyEvent(53);
          break;
        case 12:
          if(pressed)processKeyEvent(54);
          break;
        case 13:
          if(pressed)processKeyEvent(55);
          break;
        case 14:
          if(pressed)processKeyEvent(56);
          break;
        case 15:
          if(pressed)processKeyEvent(57);
          break;
        case 16:
          if(pressed)processKeyEvent(58);
          break;
        case 17:
          if(pressed)processKeyEvent(59);
          break;
        case 19:
          if(pressed)processKeyEvent(60);
          break;
        case 21:
          if(pressed)processKeyEvent(61);
          break;
        case 24:
          if(pressed)processKeyEvent(62);
          break;
      }
      break;
    case 6:
      switch(b){
        case 9:
          if(pressed)processKeyEvent(63);
          break;
        case 10:
          if(pressed)processKeyEvent(64);
          break;
        case 11:
          if(pressed)processKeyEvent(65);
          break;
        case 12:
          if(pressed)processKeyEvent(66);
          break;
        case 14:
          if(pressed)processKeyEvent(67);
          break;
        case 15:
          if(pressed)processKeyEvent(68);
          break;
        case 16:
          if(pressed)processKeyEvent(69);
          break;
        case 22:
          if(pressed)processKeyEvent(70);
          break;
        case 24:
          if(pressed)processKeyEvent(71);
          break;
      }
      break;
    case 7:
      switch(b){
        case 8:
          if(pressed)processKeyEvent(72);
          break;
        case 9:
          if(pressed)processKeyEvent(73);
          break;
        case 10:
          if(pressed)processKeyEvent(74);
          break;
        case 11:
          if(pressed)processKeyEvent(75);
          break;
        case 12:
          if(pressed)processKeyEvent(76);
          break;
        case 13:
          if(pressed)processKeyEvent(77);
          break;
        case 15:
          if(pressed)processKeyEvent(78);
          break;
        case 19:
          if(pressed)processKeyEvent(79);
          break;
        case 24:
          if(pressed&&!fn)
            keypad=!keypad;
          if(pressed)processKeyEvent(80);
          break;
      }
      break;
    case 25:
      switch(b){
        case 10:
          if(pressed)processKeyEvent(81);
          break;
        case 11:
          if(pressed)processKeyEvent(82);
          break;
        case 13:
          if(pressed)processKeyEvent(83);
          break;
        case 14:
          if(pressed)processKeyEvent(84);
          break;
        case 15:
          if(pressed)processKeyEvent(85);
          break;
        case 16:
          if(pressed)processKeyEvent(86);
          break;
        case 21:
          if(pressed)processKeyEvent(87);
          break;
        case 22:
          if(pressed)processKeyEvent(88);
          break;
        case 24:
          if(pressed)processKeyEvent(89);
          break;
      }
      break;
  }
}

extern Keyboard *kbd;

void keyboardScanAll(USB_KeyboardReport_Data_t *KR){
  kbd->KeyboardReport=KR;
  kbd->scanAll();
}
