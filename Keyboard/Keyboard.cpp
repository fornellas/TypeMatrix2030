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


#include "layouts/us_us.h"
#include "layouts/us_dvorak.h"
#include "layouts/abnt2_us.h"
#include "layouts/abnt2_dvorak.h"

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
  if(key==NO_KEY)
    return;
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

void Keyboard::processKeyEvent(uint8_t key, uint8_t state){
  uint8_t *seq=NULL;
  // wake up if suspended
  if(DEVICE_STATE_Suspended==USB_DeviceState){
    if(USB_Device_RemoteWakeupEnabled)
      if(state)
        USB_Device_SendRemoteWakeup();
    goto end;
  }
  // Non suspended
  switch(key){
    case 8: // Play / Ctrl+X
      if((state&&!keyState[key])&&fn){
        if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
          seq[0]=1;
          seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
          seq[2]=2;
          seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
          seq[4]=HID_KEYBOARD_SC_X;
          seq[5]=0x00;
          addKeySequence(seq);
        }
        goto end;
      }
      break;
    case 20: // Shuffle / Ctrl+V
      if(state&&!keyState[key]){
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
            break;
          }
        }
        goto end;
      }
      break;
    case 34: // Fn
      if(state)
        fn=1;
      else
        fn=0;
      goto end;
    case 49: // Desktop
      if((state&&!keyState[key])&&!fn){
        if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
          seq[0]=1;
          seq[1]=HID_KEYBOARD_SC_LEFT_GUI;
          seq[2]=2;
          seq[3]=HID_KEYBOARD_SC_LEFT_GUI;
          seq[4]=HID_KEYBOARD_SC_D;
          seq[5]=0x00;
          addKeySequence(seq);
        }
        goto end;
      }
      break;
    case 50: // F1 / Keyboard layout
      if((state&&!keyState[key])&&fn){
        switch(layout){
          case US_US:
            layout=US_DVORAK;
            break;
          case US_DVORAK:
            layout=US_US;
            break;
          case ABNT2_US:
            layout=ABNT2_DVORAK;
            break;
          case ABNT2_DVORAK:
            layout=ABNT2_US;
            break;
        }
        displayForceUpdate=true;
        eeprom_busy_wait();
        eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
        goto end;
      }
      break;
    case 51: // F2 / Host layout
      if((state&&!keyState[key])&&fn){
        switch(layout){
          case US_US:
            layout=ABNT2_US;
            break;
          case US_DVORAK:
            layout=ABNT2_DVORAK;
            break;
          case ABNT2_US:
            layout=US_US;
            break;
          case ABNT2_DVORAK:
            layout=US_DVORAK;
            break;
        }
        displayForceUpdate=true;
        eeprom_busy_wait();
        eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
        goto end;
      }
      break;
    case 61: // BTab
      if((state&&!keyState[key])&&((!fn&&keypad)||(fn&&!keypad))){
        if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
          seq[0]=1;
          seq[1]=HID_KEYBOARD_SC_LEFT_SHIFT;
          seq[2]=2;
          seq[3]=HID_KEYBOARD_SC_LEFT_SHIFT;
          seq[4]=HID_KEYBOARD_SC_TAB;
          seq[5]=0x00;
          addKeySequence(seq);
        }
        goto end;
      }
      break;
    case 80: // Keypad
      if(state&&!keyState[key]&&!fn){
        keypad=!keypad;
        displayForceUpdate=true;
        goto end;
      }
      break;
    case 83: // App Menu / Ctrl+C
      if((state&&!keyState[83])&&fn){
        if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
          seq[0]=1;
          seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
          seq[2]=2;
          seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
          seq[4]=HID_KEYBOARD_SC_C;
          seq[5]=0x00;
          addKeySequence(seq);
        }
        goto end;
      }
      break;
    // CTRL+key for left hand letters and Dvorak
    case 0:
    case 1:
    case 2:
    case 3:
    case 12:
    case 35:
    case 39:
    case 40:
    case 41:
    case 64:
    case 38:
    case 72:
    case 73:
    case 74:
    case 81:
      if(fn&&state)
        switch(layout){
          case US_DVORAK:
          case ABNT2_DVORAK:
            KP(HID_KEYBOARD_SC_LEFT_CONTROL);
            KP(pgm_read_byte_near(us_us+key));
            goto end;
        }
      break;
  }
  if(state){
    switch(layout){
      case US_US:
        if(fn&&!keypad)
          KP(pgm_read_byte_near(us_us_fn+key));
        else if(!fn&&keypad)
          KP(pgm_read_byte_near(us_us_keypad+key));
        else
          KP(pgm_read_byte_near(us_us+key));
        break;
      case US_DVORAK:
        if(fn&&!keypad)
          KP(pgm_read_byte_near(us_dvorak_fn+key));
        else if(!fn&&keypad)
          KP(pgm_read_byte_near(us_dvorak_keypad+key));
        else
          KP(pgm_read_byte_near(us_dvorak+key));
        break;
      case ABNT2_US:
        if(fn&&!keypad)
          KP(pgm_read_byte_near(abnt2_us_fn+key));
        else if(!fn&&keypad)
          KP(pgm_read_byte_near(abnt2_us_keypad+key));
        else
          KP(pgm_read_byte_near(abnt2_us+key));
        break;
      case ABNT2_DVORAK:
        if(fn&&!keypad)
          KP(pgm_read_byte_near(abnt2_dvorak_fn+key));
        else if(!fn&&keypad)
          KP(pgm_read_byte_near(abnt2_dvorak_keypad+key));
        else
          KP(pgm_read_byte_near(abnt2_dvorak+key));
        break;
    }
  }
  end:
  keyState[key]=state;
}

void Keyboard::processRawEvent(uint8_t a, uint8_t b, uint8_t state){
  switch(a){
    case 0:
      switch(b){
        case 3:
          processKeyEvent(0, state);break;
        case 8:
          processKeyEvent(1, state);break;
        case 9:
          processKeyEvent(2, state);break;
        case 10:
          processKeyEvent(3, state);break;
        case 11:
          processKeyEvent(4, state);break;
        case 12:
          processKeyEvent(5, state);break;
        case 13:
          processKeyEvent(6, state);break;
        case 14:
          processKeyEvent(7, state);break;
        case 16:
          processKeyEvent(8, state);break;
      }
      break;
    case 1:
      switch(b){
        case 3:
          processKeyEvent(9, state);break;
        case 8:
          processKeyEvent(10, state);break;
        case 9:
          processKeyEvent(11, state);break;
        case 10:
          processKeyEvent(12, state);break;
        case 11:
          processKeyEvent(13, state);break;
        case 12:
          processKeyEvent(14, state);break;
        case 13:
          processKeyEvent(15, state);break;
        case 14:
          processKeyEvent(16, state);break;
        case 15:
          processKeyEvent(17, state);break;
        case 16:
          processKeyEvent(18, state);break;
        case 18:
          processKeyEvent(19, state);break;
        case 20:
          processKeyEvent(20, state);break;
        case 23:
          processKeyEvent(21, state);break;
      }
      break;
    case 2:
      switch(b){
        case 3:
          processKeyEvent(22, state);break;
        case 8:
          processKeyEvent(23, state);break;
        case 9:
          processKeyEvent(24, state);break;
        case 10:
          processKeyEvent(25, state);break;
        case 11:
          processKeyEvent(26, state);break;
        case 12:
          processKeyEvent(27, state);break;
        case 13:
          processKeyEvent(28, state);break;
        case 14:
          processKeyEvent(29, state);break;
        case 15:
          processKeyEvent(30, state);break;
        case 16:
          processKeyEvent(31, state);break;
        case 17:
          processKeyEvent(32, state);break;
        case 19:
          processKeyEvent(33, state);break;
        case 20:
          processKeyEvent(34, state);break;
      }
      break;
    case 3:
      switch(b){
        case 4:
          processKeyEvent(35, state);break;
        case 5:
          processKeyEvent(36, state);break;
        case 6:
          processKeyEvent(37, state);break;
        case 7:
          processKeyEvent(38, state);break;
      }
      break;
    case 4:
      switch(b){
        case 8:
          processKeyEvent(39, state);break;
        case 9:
          processKeyEvent(40, state);break;
        case 10:
          processKeyEvent(41, state);break;
        case 11:
          processKeyEvent(42, state);break;
        case 12:
          processKeyEvent(43, state);break;
        case 13:
          processKeyEvent(44, state);break;
        case 14:
          processKeyEvent(45, state);break;
        case 15:
          processKeyEvent(46, state);break;
        case 16:
          processKeyEvent(47, state);break;
        case 18:
          processKeyEvent(48, state);break;
        case 20:
          processKeyEvent(49, state);break;
      }
      break;
    case 5:
      switch(b){
        case 8:
          processKeyEvent(50, state);break;
        case 9:
          processKeyEvent(51, state);break;
        case 10:
          processKeyEvent(52, state);break;
        case 11:
          processKeyEvent(53, state);break;
        case 12:
          processKeyEvent(54, state);break;
        case 13:
          processKeyEvent(55, state);break;
        case 14:
          processKeyEvent(56, state);break;
        case 15:
          processKeyEvent(57, state);break;
        case 16:
          processKeyEvent(58, state);break;
        case 17:
          processKeyEvent(59, state);break;
        case 19:
          processKeyEvent(60, state);break;
        case 21:
          processKeyEvent(61, state);break;
        case 24:
          processKeyEvent(62, state);break;
      }
      break;
    case 6:
      switch(b){
        case 9:
          processKeyEvent(63, state);break;
        case 10:
          processKeyEvent(64, state);break;
        case 11:
          processKeyEvent(65, state);break;
        case 12:
          processKeyEvent(66, state);break;
        case 14:
          processKeyEvent(67, state);break;
        case 15:
          processKeyEvent(68, state);break;
        case 16:
          processKeyEvent(69, state);break;
        case 22:
          processKeyEvent(70, state);break;
        case 24:
          processKeyEvent(71, state);break;
      }
      break;
    case 7:
      switch(b){
        case 8:
          processKeyEvent(72, state);break;
        case 9:
          processKeyEvent(73, state);break;
        case 10:
          processKeyEvent(74, state);break;
        case 11:
          processKeyEvent(75, state);break;
        case 12:
          processKeyEvent(76, state);break;
        case 13:
          processKeyEvent(77, state);break;
        case 15:
          processKeyEvent(78, state);break;
        case 19:
          processKeyEvent(79, state);break;
        case 24:
          processKeyEvent(80, state);break;
      }
      break;
    case 25:
      switch(b){
        case 10:
          processKeyEvent(81, state);break;
        case 11:
          processKeyEvent(82, state);break;
        case 13:
          processKeyEvent(83, state);break;
        case 14:
          processKeyEvent(84, state);break;
        case 15:
          processKeyEvent(85, state);break;
        case 16:
          processKeyEvent(86, state);break;
        case 21:
          processKeyEvent(87, state);break;
        case 22:
          processKeyEvent(88, state);break;
        case 24:
          processKeyEvent(89, state);break;
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

void Keyboard::displayInit(){
  u8g_InitSPI(&u8g, &u8g_dev_st7565_lm6059_sw_spi, U8G_SCK, U8G_MOSI, U8G_CS, U8G_A0, U8G_RESET);
  u8g_SetRot180(&u8g);
  u8g_SetFont(&u8g, u8g_font_6x10);
}

void Keyboard::displayDrawIndicator(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x){
  if(on){
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawBox(&u8g, x, 0, 13, 16);
    u8g_SetColorIndex(&u8g, 0);
    u8g_DrawStrP(&u8g, x+4, 11, str);
  }else{
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawFrame(&u8g, x, 0, 13, 16);
    u8g_DrawStrP(&u8g, x+4, 11, str);
  }
}

void Keyboard::displayDrawStrCenter(u8g_pgm_uint8_t *str, uint8_t y){
  uint8_t x;
  x=u8g_GetWidth(&u8g)/2-u8g_GetStrWidthP(&u8g, str)/2;
  u8g_DrawStrP(&u8g, x, y, str);
}

void Keyboard::displayUpdate(){
  if(USB_DeviceState!=last_USB_DeviceState||displayForceUpdate){
    if(displayForceUpdate)
      displayForceUpdate=false;
    if(USB_DeviceState!=DEVICE_STATE_Configured)
      LEDReport=NO_LED_REPORT;
    u8g_FirstPage(&u8g);
    do{
      switch(USB_DeviceState){
        case DEVICE_STATE_Unattached:
          displayDrawStrCenter(U8G_PSTR("Unattached"), 11);
          break;
        case DEVICE_STATE_Powered:
          displayDrawStrCenter(U8G_PSTR("Powered"), 11);
          break;
        case DEVICE_STATE_Default:
          displayDrawStrCenter(U8G_PSTR("Default"), 11);
          break;
        case DEVICE_STATE_Addressed:
          displayDrawStrCenter(U8G_PSTR("Addressed"), 11);
          break;
        case DEVICE_STATE_Configured:
          if(LEDReport!=NO_LED_REPORT)
            displayDrawLEDs();
          displayDrawLayoutStates();
          break;
        case DEVICE_STATE_Suspended:
          displayDrawStrCenter(U8G_PSTR("Suspended"), 11);
          if(USB_Device_RemoteWakeupEnabled)
            displayDrawStrCenter(U8G_PSTR("Press any key"), 32);
            displayDrawStrCenter(U8G_PSTR("to wake up"), 32+11);
          break;
      }
    }while(u8g_NextPage(&u8g));
    last_USB_DeviceState=USB_DeviceState;
  }
}

void Keyboard::displayDrawLEDs(){
  // Keyboard LEDs
  if(LEDReport & HID_KEYBOARD_LED_NUMLOCK)
    displayDrawIndicator(U8G_PSTR("1"), 1, 0);
  else
    displayDrawIndicator(U8G_PSTR("1"), 0, 0);
  if(LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
    displayDrawIndicator(U8G_PSTR("A"), 1, 14);
  else
    displayDrawIndicator(U8G_PSTR("A"), 0, 14);
  if(LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
    displayDrawIndicator(U8G_PSTR("S"), 1, 28);
  else
    displayDrawIndicator(U8G_PSTR("S"), 0, 28);
}

void Keyboard::setLEDs(uint8_t report){
  LEDReport=report;
  displayForceUpdate=true;
}

void Keyboard::displayDrawLayoutStates(){
  // Keypad
  if(keypad)
    displayDrawIndicator(U8G_PSTR("K"), 1, 48);
  else
    displayDrawIndicator(U8G_PSTR("K"), 0, 48);
  // Layout
  switch(layout){
    case US_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 68);
      displayDrawIndicator(U8G_PSTR("D"), 0, 82);
      displayDrawIndicator(U8G_PSTR("U"), 1, 101);
      displayDrawIndicator(U8G_PSTR("2"), 0, 115);
      break;
    case US_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 68);
      displayDrawIndicator(U8G_PSTR("D"), 1, 82);
      displayDrawIndicator(U8G_PSTR("U"), 1, 101);
      displayDrawIndicator(U8G_PSTR("2"), 0, 115);
      break;
    case ABNT2_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 68);
      displayDrawIndicator(U8G_PSTR("D"), 0, 82);
      displayDrawIndicator(U8G_PSTR("U"), 0, 101);
      displayDrawIndicator(U8G_PSTR("2"), 1, 115);
      break;
    case ABNT2_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 68);
      displayDrawIndicator(U8G_PSTR("D"), 1, 82);
      displayDrawIndicator(U8G_PSTR("U"), 0, 101);
      displayDrawIndicator(U8G_PSTR("2"), 1, 115);
      break;
  }
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
  LEDReport=NO_LED_REPORT;
  last_USB_DeviceState=NO_USB_DEVICE_STATE;
  // Load layout
  eeprom_busy_wait();
  layout=eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT);
  if(layout>LAYOUT_MAX){
    layout=US_US;
    eeprom_busy_wait();
    eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
  }
  // Sequences
  sequence=NULL;
  // Display
  displayInit();
  displayForceUpdate=0;
}

//
// C bindings
//

extern Keyboard *kbd;

void keyboardScanAll(USB_KeyboardReport_Data_t *KR){
  kbd->KeyboardReport=KR;
  kbd->scanAll();
}

void keyboardSetLEDs(uint8_t report){
  kbd->setLEDs(report);
}
