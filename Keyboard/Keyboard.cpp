#include "Keyboard.h"

extern "C" {
#include "LUFA.h"
}

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Peripheral/TWI.h>

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/eeprom.h>

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

#define U8G_SCK PN(3,7)		// PD7 / 6
#define U8G_MOSI PN(4,6)	// PE6 / 7
#define U8G_CS PN(5,5)		// PF5 / 20/A2
#define U8G_A0 PN(3,6)		// PD6 / 12
#define U8G_RESET PN(2,7)	// PC7 / 13

//
// I/O Expander
//

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

//
// Key scanning
//

#define SETMOD(key, value) case key: KeyboardReport->Modifier|=value;break;
void Keyboard::press(uint8_t key){
//fprintf_P(Stream, PSTR("      press() %d +++\r\n"), key);
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
      for(uint8_t i=0;i<6;i++)
        if(KeyboardReport->KeyCode[i]==key)
          break;
      for(uint8_t i=0;i<6;i++){
        if(KeyboardReport->KeyCode[i]==0){
          KeyboardReport->KeyCode[i]=key;
          break;
        }
      }
      break;
  }
}

void Keyboard::processKeyEvent(uint8_t key){
//fprintf_P(Stream, PSTR("PRESSED %d\r\n"), key);
  switch(layout){
    case DVORAK:
      (this->*dvorak[key])();
      break;
    case QWERTY:
      (this->*qwerty[key])();
      break;
    default:
      layout=QWERTY;
      (this->*qwerty[key])();
      break;
  }
}

void Keyboard::processRawEvent(uint8_t a, uint8_t b, uint8_t state){
  uint8_t *seq;
  switch(a){
    case 0:
      switch(b){
        case 3:
          if(state)processKeyEvent(0);keyState[0]=state;break;
        case 8:
          if(state)processKeyEvent(1);keyState[1]=state;break;
        case 9:
          if(state)processKeyEvent(2);keyState[2]=state;break;
        case 10:
          if(state)processKeyEvent(3);keyState[3]=state;break;
        case 11:
          if(state)processKeyEvent(4);keyState[4]=state;break;
        case 12:
          if(state)processKeyEvent(5);keyState[5]=state;break;
        case 13:
          if(state)processKeyEvent(6);keyState[6]=state;break;
        case 14:
          if(state)processKeyEvent(7);keyState[7]=state;break;
        case 16: // Play / Ctrl+X
          if((state&&!keyState[8])&&fn)
            if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
              seq[0]=1;
              seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
              seq[2]=2;
              seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
              seq[4]=HID_KEYBOARD_SC_X;
              seq[5]=0x00;
              addKeySequence(seq);
            }
          if(state)processKeyEvent(8);keyState[8]=state;break;
      }
      break;
    case 1:
      switch(b){
        case 3:
          if(state)processKeyEvent(9);keyState[9]=state;break;
        case 8:
          if(state)processKeyEvent(10);keyState[10]=state;break;
        case 9:
          if(state)processKeyEvent(11);keyState[11]=state;break;
        case 10:
          if(state)processKeyEvent(12);keyState[12]=state;break;
        case 11:
          if(state)processKeyEvent(13);keyState[13]=state;break;
        case 12:
          if(state)processKeyEvent(14);keyState[14]=state;break;
        case 13:
          if(state)processKeyEvent(15);keyState[15]=state;break;
        case 14:
          if(state)processKeyEvent(16);keyState[16]=state;break;
        case 15:
          if(state)processKeyEvent(17);keyState[17]=state;break;
        case 16:
          if(state)processKeyEvent(18);keyState[18]=state;break;
        case 18:
          if(state)processKeyEvent(19);keyState[19]=state;break;
        case 20: // Shuffle / Ctrl+V
          if(state&&!keyState[20]){
            if(fn){
              if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
                seq[0]=1;
                seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
                seq[2]=2;
                seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
                seq[4]=HID_KEYBOARD_SC_V;
                seq[5]=0x00;
                addKeySequence(seq);
              }
            }else{
              if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
                seq[0]=1;
                seq[1]=HID_KEYBOARD_SC_LEFT_ALT;
                seq[2]=2;
                seq[3]=HID_KEYBOARD_SC_LEFT_ALT;
                seq[4]=HID_KEYBOARD_SC_TAB;
                seq[5]=0x00;
                addKeySequence(seq);
              }
            }
          }
          if(state)processKeyEvent(20);keyState[20]=state;break;
        case 23:
          if(state)processKeyEvent(21);keyState[21]=state;break;
      }
      break;
    case 2:
      switch(b){
        case 3:
          if(state)processKeyEvent(22);keyState[22]=state;break;
        case 8:
          if(state)processKeyEvent(23);keyState[23]=state;break;
        case 9:
          if(state)processKeyEvent(24);keyState[24]=state;break;
        case 10:
          if(state)processKeyEvent(25);keyState[25]=state;break;
        case 11:
          if(state)processKeyEvent(26);keyState[26]=state;break;
        case 12:
          if(state)processKeyEvent(27);keyState[27]=state;break;
        case 13:
          if(state)processKeyEvent(28);keyState[28]=state;break;
        case 14:
          if(state)processKeyEvent(29);keyState[29]=state;break;
        case 15:
          if(state)processKeyEvent(30);keyState[30]=state;break;
        case 16:
          if(state)processKeyEvent(31);keyState[31]=state;break;
        case 17:
          if(state)processKeyEvent(32);keyState[32]=state;break;
        case 19:
          if(state)processKeyEvent(33);keyState[33]=state;break;
        case 20:
          if(state)
            fn=1;
          else
            fn=0;
      }
      break;
    case 3:
      switch(b){
        case 4:
          if(state)processKeyEvent(35);keyState[35]=state;break;
        case 5:
          if(state)processKeyEvent(36);keyState[36]=state;break;
        case 6:
          if(state)processKeyEvent(37);keyState[37]=state;break;
        case 7:
          if(state)processKeyEvent(38);keyState[38]=state;break;
      }
      break;
    case 4:
      switch(b){
        case 8:
          if(state)processKeyEvent(39);keyState[39]=state;break;
        case 9:
          if(state)processKeyEvent(40);keyState[40]=state;break;
        case 10:
          if(state)processKeyEvent(41);keyState[41]=state;break;
        case 11:
          if(state)processKeyEvent(42);keyState[42]=state;break;
        case 12:
          if(state)processKeyEvent(43);keyState[43]=state;break;
        case 13:
          if(state)processKeyEvent(44);keyState[44]=state;break;
        case 14:
          if(state)processKeyEvent(45);keyState[45]=state;break;
        case 15:
          if(state)processKeyEvent(46);keyState[46]=state;break;
        case 16:
          if(state)processKeyEvent(47);keyState[47]=state;break;
        case 18:
          if(state)processKeyEvent(48);keyState[48]=state;break;
        case 20:
          if((state&&!keyState[49])&&!fn)
            if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
              seq[0]=1;
              seq[1]=HID_KEYBOARD_SC_LEFT_GUI;
              seq[2]=2;
              seq[3]=HID_KEYBOARD_SC_LEFT_GUI;
              seq[4]=HID_KEYBOARD_SC_D;
              seq[5]=0x00;
              addKeySequence(seq);
            }
          if(state)processKeyEvent(49);keyState[49]=state;break;
      }
      break;
    case 5:
      switch(b){
        case 8:
          if((state&&!keyState[50])&&fn){
            if(layout==QWERTY)
              layout=DVORAK;
            else if(layout==DVORAK)
              layout=QWERTY;
            eeprom_busy_wait();
            eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
          }
          if(state)processKeyEvent(50);keyState[50]=state;break;
        case 9:
          if(state)processKeyEvent(51);keyState[51]=state;break;
        case 10:
          if(state)processKeyEvent(52);keyState[52]=state;break;
        case 11:
          if(state)processKeyEvent(53);keyState[53]=state;break;
        case 12:
          if(state)processKeyEvent(54);keyState[54]=state;break;
        case 13:
          if(state)processKeyEvent(55);keyState[55]=state;break;
        case 14:
          if(state)processKeyEvent(56);keyState[56]=state;break;
        case 15:
          if(state)processKeyEvent(57);keyState[57]=state;break;
        case 16:
          if(state)processKeyEvent(58);keyState[58]=state;break;
        case 17:
          if(state)processKeyEvent(59);keyState[59]=state;break;
        case 19:
          if(state)processKeyEvent(60);keyState[60]=state;break;
        case 21:
          if((state&&!keyState[61])&&!fn)
            if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
              seq[0]=1;
              seq[1]=HID_KEYBOARD_SC_LEFT_SHIFT;
              seq[2]=2;
              seq[3]=HID_KEYBOARD_SC_LEFT_SHIFT;
              seq[4]=HID_KEYBOARD_SC_TAB;
              seq[5]=0x00;
              addKeySequence(seq);
            }
          if(state)processKeyEvent(61);keyState[61]=state;break;
        case 24:
          if(state)processKeyEvent(62);keyState[62]=state;break;
      }
      break;
    case 6:
      switch(b){
        case 9:
          if(state)processKeyEvent(63);keyState[63]=state;break;
        case 10:
          if(state)processKeyEvent(64);keyState[64]=state;break;
        case 11:
          if(state)processKeyEvent(65);keyState[65]=state;break;
        case 12:
          if(state)processKeyEvent(66);keyState[66]=state;break;
        case 14:
          if(state)processKeyEvent(67);keyState[67]=state;break;
        case 15:
          if(state)processKeyEvent(68);keyState[68]=state;break;
        case 16:
          if(state)processKeyEvent(69);keyState[69]=state;break;
        case 22:
          if(state)processKeyEvent(70);keyState[70]=state;break;
        case 24:
          if(state)processKeyEvent(71);keyState[71]=state;break;
      }
      break;
    case 7:
      switch(b){
        case 8:
          if(state)processKeyEvent(72);keyState[72]=state;break;
        case 9:
          if(state)processKeyEvent(73);keyState[73]=state;break;
        case 10:
          if(state)processKeyEvent(74);keyState[74]=state;break;
        case 11:
          if(state)processKeyEvent(75);keyState[75]=state;break;
        case 12:
          if(state)processKeyEvent(76);keyState[76]=state;break;
        case 13:
          if(state)processKeyEvent(77);keyState[77]=state;break;
        case 15:
          if(state)processKeyEvent(78);keyState[78]=state;break;
        case 19:
          if(state)processKeyEvent(79);keyState[79]=state;break;
        case 24: // Keypad
          if(state&&!keyState[80]&&!fn)
            keypad=!keypad;
          if(state)processKeyEvent(80);keyState[80]=state;break;
      }
      break;
    case 25:
      switch(b){
        case 10:
          if(state)processKeyEvent(81);keyState[81]=state;break;
        case 11:
          if(state)processKeyEvent(82);keyState[82]=state;break;
        case 13: // App Menu / Ctrl+C
          if((state&&!keyState[83])&&fn)
            if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
              seq[0]=1;
              seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
              seq[2]=2;
              seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
              seq[4]=HID_KEYBOARD_SC_C;
              seq[5]=0x00;
              addKeySequence(seq);
            } 
          if(state)processKeyEvent(83);keyState[83]=state;break;
        case 14:
          if(state)processKeyEvent(84);keyState[84]=state;break;
        case 15:
          if(state)processKeyEvent(85);keyState[85]=state;break;
        case 16:
          if(state)processKeyEvent(86);keyState[86]=state;break;
        case 21:
          if(state)processKeyEvent(87);keyState[87]=state;break;
        case 22:
          if(state)processKeyEvent(88);keyState[88]=state;break;
        case 24:
          if(state)processKeyEvent(89);keyState[89]=state;break;
      }
      break;
  }
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
  // Playback key sequences
  playKeySequence();
}

//
// Key sequencing
//

void Keyboard::addKeySequence(uint8_t *seq){
  if(NULL==sequence)
    sequence=seq;
}

void Keyboard::playKeySequence(){
  if(NULL==sequence)
    return;
//fprintf_P(Stream, PSTR("Playing sequence.\r\n"));
  // skip
  uint8_t p=0;
  while(sequence[p]==0x00)
    p++;
  // process round
//fprintf_P(Stream, PSTR("  Start of round p=%d\r\n"), p);
  for(uint8_t k=p+1;k<p+sequence[p]+1;k++){
//fprintf_P(Stream, PSTR("    p=%d k=%d\r\n"), p, k);
    press(sequence[k]);
    sequence[k]=0x00;
  }
  // last round
  if(!sequence[p+sequence[p]+1]){
//fprintf_P(Stream, PSTR("End of sequence.\r\n"));
    free(sequence);
    sequence=NULL;
  // more rounds
  }else{
    sequence[p]=0x00;
//fprintf_P(Stream, PSTR("  One more round, p=%d\r\n"), p);
  }
}

//
// Display
//

void Keyboard::initDisplay(){
  u8g_InitSPI(&u8g, &u8g_dev_st7565_lm6059_sw_spi, U8G_SCK, U8G_MOSI, U8G_CS, U8G_A0, U8G_RESET);
  u8g_SetRot180(&u8g);
  u8g_SetFont(&u8g, u8g_font_6x10);
  u8g_FirstPage(&u8g);
  do{
    u8g_DrawStrP(&u8g, 0, 15, U8G_PSTR("Booting..."));
  }while(u8g_NextPage(&u8g));
}

void Keyboard::updateDisplay(){
  u8g_FirstPage(&u8g);
  do{
    if (LEDReport & HID_KEYBOARD_LED_NUMLOCK){
      u8g_DrawStrP(&u8g, 0, 8, U8G_PSTR("NumLck"));
    }else{
      
    }
    if (LEDReport & HID_KEYBOARD_LED_CAPSLOCK){
      u8g_DrawStrP(&u8g, 48, 8, U8G_PSTR("CpsLck"));
    }else{

    }
    if (LEDReport & HID_KEYBOARD_LED_SCROLLLOCK){
      u8g_DrawStrP(&u8g, 92, 8, U8G_PSTR("ScrLck"));
    }else{

    }
  }while(u8g_NextPage(&u8g));
}

void Keyboard::clearDisplay(){
  u8g_FirstPage(&u8g);
  do{
  }while(u8g_NextPage(&u8g));
}

void Keyboard::setLEDs(uint8_t report){
  LEDReport=report;
  updateDisplay();
}

//
// Constructor
//

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
  for(int i=0;i<NUM_KEYS;i++)
    keyState[i]=0;
  keypad=0;
  fn=0;
  LEDReport=0;
  // Load layout
  eeprom_busy_wait();
  layout=eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT);
  if(layout>LAYOUT_MAX){
    layout=QWERTY;
    eeprom_busy_wait();
    eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
  }
  // Sequences
  sequence=NULL;
  // Display
  initDisplay();
  // Dvorak callbacks (should go to PROGMEM...)
  dvorak={
    &Keyboard::dvorak0,  &Keyboard::dvorak1,  &Keyboard::dvorak2,  &Keyboard::dvorak3,  &Keyboard::dvorak4,
    &Keyboard::dvorak5,  &Keyboard::dvorak6,  &Keyboard::dvorak7,  &Keyboard::common8,  &Keyboard::common9,
    &Keyboard::common10, &Keyboard::common11, &Keyboard::dvorak12, &Keyboard::dvorak13, &Keyboard::dvorak14,
    &Keyboard::common15, &Keyboard::dvorak16, &Keyboard::common17, &Keyboard::common18, &Keyboard::common19,
    &Keyboard::common20, &Keyboard::common21, &Keyboard::common22, &Keyboard::common23, &Keyboard::common24,
    &Keyboard::common25, &Keyboard::common26, &Keyboard::common27, &Keyboard::common28, &Keyboard::common29,
    &Keyboard::common30, &Keyboard::common31, &Keyboard::common32, &Keyboard::common33, &Keyboard::common34,
    &Keyboard::dvorak35, &Keyboard::dvorak36, &Keyboard::common37, &Keyboard::dvorak38, &Keyboard::dvorak39,
    &Keyboard::dvorak40, &Keyboard::dvorak41, &Keyboard::dvorak42, &Keyboard::dvorak43, &Keyboard::dvorak44,
    &Keyboard::dvorak45, &Keyboard::dvorak46, &Keyboard::common47, &Keyboard::common48, &Keyboard::common49,
    &Keyboard::common50, &Keyboard::common51, &Keyboard::common52, &Keyboard::common53, &Keyboard::dvorak54,
    &Keyboard::common55, &Keyboard::dvorak56, &Keyboard::common57, &Keyboard::common58, &Keyboard::common59,
    &Keyboard::common60, &Keyboard::common61, &Keyboard::common62, &Keyboard::common63, &Keyboard::dvorak64,
    &Keyboard::dvorak65, &Keyboard::common66, &Keyboard::dvorak67, &Keyboard::common68, &Keyboard::common69,
    &Keyboard::common70, &Keyboard::common71, &Keyboard::dvorak72, &Keyboard::dvorak73, &Keyboard::dvorak74,
    &Keyboard::dvorak75, &Keyboard::dvorak76, &Keyboard::dvorak77, &Keyboard::common78, &Keyboard::common79,
    &Keyboard::common80, &Keyboard::dvorak81, &Keyboard::dvorak82, &Keyboard::common83, &Keyboard::dvorak84,
    &Keyboard::common85, &Keyboard::common86, &Keyboard::common87, &Keyboard::common88, &Keyboard::common89,
    };
  qwerty={
    &Keyboard::qwerty0,  &Keyboard::qwerty1,  &Keyboard::qwerty2,  &Keyboard::qwerty3,  &Keyboard::qwerty4,
    &Keyboard::qwerty5,  &Keyboard::qwerty6,  &Keyboard::qwerty7,  &Keyboard::common8,  &Keyboard::common9,
    &Keyboard::common10, &Keyboard::common11, &Keyboard::qwerty12, &Keyboard::qwerty13, &Keyboard::qwerty14,
    &Keyboard::common15, &Keyboard::qwerty16, &Keyboard::common17, &Keyboard::common18, &Keyboard::common19,
    &Keyboard::common20, &Keyboard::common21, &Keyboard::common22, &Keyboard::common23, &Keyboard::common24,
    &Keyboard::common25, &Keyboard::common26, &Keyboard::common27, &Keyboard::common28, &Keyboard::common29,
    &Keyboard::common30, &Keyboard::common31, &Keyboard::common32, &Keyboard::common33, &Keyboard::common34,
    &Keyboard::qwerty35, &Keyboard::qwerty36, &Keyboard::common37, &Keyboard::qwerty38, &Keyboard::qwerty39,
    &Keyboard::qwerty40, &Keyboard::qwerty41, &Keyboard::qwerty42, &Keyboard::qwerty43, &Keyboard::qwerty44,
    &Keyboard::qwerty45, &Keyboard::qwerty46, &Keyboard::common47, &Keyboard::common48, &Keyboard::common49,
    &Keyboard::common50, &Keyboard::common51, &Keyboard::common52, &Keyboard::common53, &Keyboard::qwerty54,
    &Keyboard::common55, &Keyboard::qwerty56, &Keyboard::common57, &Keyboard::common58, &Keyboard::common59,
    &Keyboard::common60, &Keyboard::common61, &Keyboard::common62, &Keyboard::common63, &Keyboard::qwerty64,
    &Keyboard::qwerty65, &Keyboard::common66, &Keyboard::qwerty67, &Keyboard::common68, &Keyboard::common69,
    &Keyboard::common70, &Keyboard::common71, &Keyboard::qwerty72, &Keyboard::qwerty73, &Keyboard::qwerty74,
    &Keyboard::qwerty75, &Keyboard::qwerty76, &Keyboard::qwerty77, &Keyboard::common78, &Keyboard::common79,
    &Keyboard::common80, &Keyboard::qwerty81, &Keyboard::qwerty82, &Keyboard::common83, &Keyboard::qwerty84,
    &Keyboard::common85, &Keyboard::common86, &Keyboard::common87, &Keyboard::common88, &Keyboard::common89,
    };
}

//
// C bindings
//

extern Keyboard *kbd;

void keyboardScanAll(USB_KeyboardReport_Data_t *KR){
  kbd->KeyboardReport=KR;
  kbd->scanAll();
}

void keyboardUpdateDisplay(){
  kbd->updateDisplay();
}

void keyboardClearDisplay(){
  kbd->clearDisplay();
}

void keyboardSetLEDs(uint8_t report){
  kbd->setLEDs(report);
}
