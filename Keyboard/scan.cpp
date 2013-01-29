#include "Keyboard.h"

extern "C" {
#include "LUFA.h"
}

#include <LUFA/Drivers/USB/USB.h>

#include "layouts/us_us.h"
#include "layouts/us_dvorak.h"
#include "layouts/abnt2_us.h"
#include "layouts/abnt2_dvorak.h"

#include <stdlib.h>

#define PRESSED 1
#define RELEASED 0

/*

*Pull down resistor ; INT / PCINT

Track	Port
0	B0*
1	B4*
2	B5*
3	B6*
4	B7*
5	E4*
6	E5*
7	E6*
8	A0
9	A1
10	A2
11	A3
12	A4
13	A5
14	A6
15	A7
16	C0
17	C1
18	C2
19	C3
20	C4
21	C5
22	C6
23	C7
24	D4
25	E7*
	
*/

void Keyboard::portInit(){
  // set all input without pull ups (tri-state hi-z)
  DDRA=0x00;		PORTA=0x00;
  DDRB&=~0b11110001;	PORTB&=~0b11110001;
  DDRC=0x00;		PORTC=0x00;
  DDRD&=~0b00010011;	PORTD&=~0b00010011;
  DDRD&=~0b11110000;	PORTE&=~0b11110000;
}

volatile uint8_t *Keyboard::getPinDDR(uint8_t pin){
  if(pin<5)
    return &DDRB;
  if(pin<8||pin==25)
    return &DDRE;
  if(pin<16)
    return &DDRA;
  if(pin<24)
    return &DDRC;
  return &DDRD; // 24
}

volatile uint8_t *Keyboard::getPinPORT(uint8_t pin){
  if(pin<5)
    return &PORTB;
  if(pin<8||pin==25)
    return &PORTE;
  if(pin<16)
    return &PORTA;
  if(pin<24)
    return &PORTC;
  return &PORTD; // 24
}

volatile uint8_t *Keyboard::getPinPIN(uint8_t pin){
  if(pin<5)
    return &PINB;
  if(pin<8||pin==25)
    return &PINE;
  if(pin<16)
    return &PINA;
  if(pin<24)
    return &PINC;
  return &PIND; // 24
}

uint8_t Keyboard::getPinBit(uint8_t pin){
  if(pin==0)
    return 0;
  if(pin<5)
    return pin+3;
  if(pin<8)
    return pin-1;
  if(pin<16)
    return pin-8;
  if(pin<24)
    return pin-16;
  if(pin==24)
    return 4;
  return 7; // 25
}

void Keyboard::setPinInLow(uint8_t pin){
  volatile uint8_t *ddr=getPinDDR(pin);
  volatile uint8_t *port=getPinPORT(pin);
  uint8_t bit=getPinBit(pin);
  (*ddr)&=~(1<<bit);
  (*port)&=~(1<<bit);
}

void Keyboard::setPinOut(uint8_t pin, uint8_t value){
  volatile uint8_t *ddr=getPinDDR(pin);
  volatile uint8_t *port=getPinPORT(pin);
  uint8_t bit=getPinBit(pin);
  (*ddr)|=(1<<bit);
  if(value)
    (*port)|=(1<<bit);
  else
    (*port)&=~(1<<bit);
}

uint8_t Keyboard::readPin(uint8_t inPin){
  volatile uint8_t *pin=getPinPIN(inPin);
  uint8_t bit=getPinBit(inPin);
  return (*pin&(1<<bit));
}

#define SETMOD(key, value) case key: KeyboardReport->Modifier|=value;break;
void Keyboard::press(const uint8_t key){
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

bool Keyboard::processSuspendKeys(const bool state){
  // wake up if suspended
  if(DEVICE_STATE_Suspended==USB_DeviceState){
    if(USB_Device_RemoteWakeupEnabled)
      if(state)
        USB_Device_SendRemoteWakeup();
    return true;
  }else
    return false;
}

bool Keyboard::processMacroKeys(const uint8_t key, const bool state){
  if(DEVICE_STATE_Configured!=USB_DeviceState){
    changeMacroMode(MACRO_STATE_NONE);
    return true;
  }
  if(macroState!=MACRO_STATE_NONE&&key==37&&state){ // exit macro mode with Esc
    changeMacroMode(MACRO_STATE_NONE);
    return true;
  }
  switch(macroState){
    case MACRO_STATE_NONE:
      if(key==70&&state&&keyState[34]) // Fn+LAlt
        changeMacroMode(MACRO_STATE_INIT);
      else
        return false;
      break;
    case MACRO_STATE_INIT:
      if(!keyState[34]||!keyState[70]) // Fn+LAlt not pressed
        changeMacroMode(MACRO_STATE_NONE);
      else
        switch(key){
          case 71: // Space (Record Macro)
            if(state&&!keyState[71])
              changeMacroMode(MACRO_STATE_REC_INIT);
            break;
          case 62: // Del (Delete Macro)
            if(state&&!keyState[62])
              changeMacroMode(MACRO_STATE_DEL);
            break;
          case 78: // Enter (Unlock Macros)
            if(state&&!keyState[78])
              changeMacroMode(MACRO_STATE_UNLOCK);
            break;
          case 17: // Backspace (Lock Macros)
            if(state&&!keyState[17])
              macroLocked=true;
            break;
          // 0-9 (Play Macros)
/*          case 0:
          case 22:
          case 23:
          case 24:
          case 25:
          case 52:
          case 53:
          case 26:
          case 27:*/
          case 28:
            if(state&&!keyState[28])
              playMacro(key);
            break;
        }
      break;
    case MACRO_STATE_REC_INIT:
      break;
    case MACRO_STATE_DEL:
      break;
    case MACRO_STATE_UNLOCK:
      break;
  }
  return true;
}


bool Keyboard::processCommonKeys(const uint8_t key, const bool state){
  uint8_t *seq=NULL;
  switch(key){
    case 8: // Play / Ctrl+X
      if(state&&!keyState[key]){
        if(fn){
          if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
            seq[0]=1;
            seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
            seq[2]=2;
            seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
            seq[4]=HID_KEYBOARD_SC_X;
            seq[5]=0x00;
            addKeySequence(seq);
          }
        }else
          KP(KEY_PLAY);
      }
      return true;
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
      }
      return true;
      break;
    case 34: // Fn
      if(state)
        fn=1;
      else
        fn=0;
      return true;
    case 49: // Desktop / previous
      if(state&&!keyState[key]){
        if(!fn){
          if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
            seq[0]=1;
            seq[1]=HID_KEYBOARD_SC_LEFT_GUI;
            seq[2]=2;
            seq[3]=HID_KEYBOARD_SC_LEFT_GUI;
            seq[4]=HID_KEYBOARD_SC_D;
            seq[5]=0x00;
            addKeySequence(seq);
          }
        }else
          KP(KEY_MEDIA_PREVIOUS);
      }
      return true;
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
        displayForceUpdate();
        eeprom_busy_wait();
        eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
        return true;
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
        displayForceUpdate();
        eeprom_busy_wait();
        eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
        return true;
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
        return true;
      }
      break;
    case 80: // Keypad
      if(state&&!keyState[key]&&!fn){
        keypad=!keypad;
        displayForceUpdate();
      }else if(state&&!keyState[key]&&fn){
        KP(HID_KEYBOARD_SC_NUM_LOCK);
      }
      return true;
      break;
    case 83: // App Menu / Ctrl+C
      if(state&&!keyState[key]){
        if(fn){
          if(NULL!=(seq=(uint8_t *)malloc(sizeof(uint8_t)*6))){
            seq[0]=1;
            seq[1]=HID_KEYBOARD_SC_LEFT_CONTROL;
            seq[2]=2;
            seq[3]=HID_KEYBOARD_SC_LEFT_CONTROL;
            seq[4]=HID_KEYBOARD_SC_C;
            seq[5]=0x00;
            addKeySequence(seq);
          }
        }else
          KP(HID_KEYBOARD_SC_APPLICATION);
      }
      return true;
      break;
  }
  return false;
}

bool Keyboard::processDvorakQwertyKeys(const uint8_t key, const bool state){
  switch(key){
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
            return true;
        }
      break;
  }
  return false;
}

void Keyboard::processKeyEvent(const uint8_t key, const bool state){
  // special keys
  if(processSuspendKeys(state))
    goto end;
  if(processMacroKeys(key, state))
    goto end;
  if(processCommonKeys(key, state))
    goto end;
  if(processDvorakQwertyKeys(key, state))
    goto end;
  // all other keys
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

void Keyboard::processRawEvent(uint8_t a, uint8_t b, const bool state){
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
  // set current pin to input with pull down resistor
  setPinInLow(lowPin);

  // pin list
  va_list ap;
  int8_t scanPin;
  va_start(ap, lowPin);

  // test each supplied pin
  while((scanPin=va_arg(ap, int))!=-1){
    setPinOut(scanPin, 1);
    if(readPin(lowPin))
      processRawEvent(lowPin, scanPin, PRESSED);
    else
      processRawEvent(lowPin, scanPin, RELEASED);
    setPinInLow(scanPin);
  }
  va_end(ap);
  // reset current pin to input
  setPinInLow(lowPin);
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
