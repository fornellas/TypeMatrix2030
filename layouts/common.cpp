#include "Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>

#include <stdlib.h>

#include "extraKeys.h"

// Ply/CX
void Keyboard::common8(){
  if(!fn)
    KP(KEY_PLAY);
};
// Tab
void Keyboard::common9(){
  KP(HID_KEYBOARD_SC_TAB);
};
// CapsLock/Clear
void Keyboard::common10(){
  if((fn&&!keypad)||(!fn&&keypad)){
    KP(HID_KEYBOARD_SC_ERROR_ROLLOVER);
  }else{
    KP(HID_KEYBOARD_SC_CAPS_LOCK);
  }
};
// F3
void Keyboard::common11(){
  KP(HID_KEYBOARD_SC_F3);
};
// F7/Pwr
void Keyboard::common15(){
  if(fn)
    KP(HID_KEYBOARD_SC_POWER);
  else
    KP(HID_KEYBOARD_SC_F7);
};
// Bs/V+
void Keyboard::common17(){
  if(fn)
    KP(HID_KEYBOARD_SC_VOLUME_UP);
  else
    KP(HID_KEYBOARD_SC_BACKSPACE);
};
// Calc
void Keyboard::common18(){
  KP(KEY_CALC);
};
// LSft
void Keyboard::common19(){
  KP(HID_KEYBOARD_SC_LEFT_SHIFT);
};
// AT/CV
void Keyboard::common20(){
  if(!fn)
    KP(HID_KEYBOARD_SC_LEFT_ALT);
};
// Start
void Keyboard::common21(){
  KP(HID_KEYBOARD_SC_LEFT_GUI);
};
// 1!
void Keyboard::common22(){
  KP(HID_KEYBOARD_SC_1_AND_EXCLAMATION);
};
// 2@
void Keyboard::common23(){
  KP(HID_KEYBOARD_SC_2_AND_AT);
};
// 3#
void Keyboard::common24(){
  KP(HID_KEYBOARD_SC_3_AND_HASHMARK);
};
// 4$
void Keyboard::common25(){
  KP(HID_KEYBOARD_SC_4_AND_DOLLAR);
};
// 7&
void Keyboard::common26(){
  KP(HID_KEYBOARD_SC_7_AND_AND_AMPERSAND);
};
// 8*
void Keyboard::common27(){
  KP(HID_KEYBOARD_SC_8_AND_ASTERISK);
};
// 9(
void Keyboard::common28(){
  KP(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS);
};
// 0)
void Keyboard::common29(){
  KP(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS);
};
// F10/PSc
void Keyboard::common30(){
  if(fn)
    KP(HID_KEYBOARD_SC_PRINT_SCREEN);
  else
    KP(HID_KEYBOARD_SC_F10);
};
// End/3
void Keyboard::common31(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN);
  else
    KP(HID_KEYBOARD_SC_END);
};
// PDwn/Nx
void Keyboard::common32(){
  if(fn)
    KP(KEY_BROWSER_FORWARD);
  else
    KP(HID_KEYBOARD_SC_PAGE_DOWN);
};
// F5
void Keyboard::common33(){
  KP(HID_KEYBOARD_SC_F5);
};
// Fn
void Keyboard::common34(){

};
// Esc
void Keyboard::common37(){
  KP(HID_KEYBOARD_SC_ESCAPE);
};
// www/Bs
void Keyboard::common47(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
//  else
//    KP(KEY_WWW); // FIXME
};
// RSft/+
void Keyboard::common48(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_PLUS);
  else {
    KP(HID_KEYBOARD_SC_RIGHT_SHIFT);
  }
};
// Dsk/Pv
void Keyboard::common49(){
  if(fn)
    KP(KEY_MEDIA_PREVIOUS);
};
// F1/Dvk
void Keyboard::common50(){
  if(!fn)
    KP(HID_KEYBOARD_SC_F1);
};
// F2
void Keyboard::common51(){
  KP(HID_KEYBOARD_SC_F2);
};
// 5%
void Keyboard::common52(){
  KP(HID_KEYBOARD_SC_5_AND_PERCENTAGE);
};
// 6^
void Keyboard::common53(){
  KP(HID_KEYBOARD_SC_6_AND_CARET);
};
// F8/Slp
void Keyboard::common55(){
  if(fn)
    KP(KEY_SLEEP);
  else
    KP(HID_KEYBOARD_SC_F8);
};
// F9/Wke
void Keyboard::common57(){
  if(fn)
    KP(HID_KEYBOARD_SC_INTERNATIONAL9);
  else
    KP(HID_KEYBOARD_SC_F9);
};
// Home/1
void Keyboard::common58(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_1_AND_END);
  else
    KP(HID_KEYBOARD_SC_HOME);
};
// PUp/Bck
void Keyboard::common59(){
  if(fn)
    KP(KEY_BROWSER_BACK);
  else
    KP(HID_KEYBOARD_SC_PAGE_UP);
};
// LCtrl
void Keyboard::common60(){
  KP(HID_KEYBOARD_SC_LEFT_CONTROL);
};
// Mail/BackTab
void Keyboard::common61(){
  // FIXME Mail
};
// Del/Ins
void Keyboard::common62(){
  if(fn)
    KP(HID_KEYBOARD_SC_INSERT);
  else
    KP(HID_KEYBOARD_SC_DELETE);
};
// F4
void Keyboard::common63(){
  KP(HID_KEYBOARD_SC_F4);
};
// F6/Ejct
void Keyboard::common66(){
  if(fn)
    KP(KEY_EJECT);
  else
    KP(HID_KEYBOARD_SC_F6);
};
// F11/SLk
void Keyboard::common68(){
  if(fn)
    KP(HID_KEYBOARD_SC_SCROLL_LOCK);
  else
    KP(HID_KEYBOARD_SC_F11);
};
// Up/2
void Keyboard::common69(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_UP_ARROW);
};
// LAlt
void Keyboard::common70(){
  KP(HID_KEYBOARD_SC_LEFT_ALT);
};
// Spc/Mte
void Keyboard::common71(){
  if(fn)
    KP(HID_KEYBOARD_SC_MUTE);
  else
    KP(HID_KEYBOARD_SC_SPACE);
};
// Ret/V-
void Keyboard::common78(){
  if(fn)
    KP(HID_KEYBOARD_SC_VOLUME_DOWN);
  else
    KP(HID_KEYBOARD_SC_ENTER);
};
// RCtl/Ret
void Keyboard::common79(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_ENTER);
  else
    KP(HID_KEYBOARD_SC_RIGHT_CONTROL);
};
// NLock
void Keyboard::common80(){
  if(fn)
    KP(HID_KEYBOARD_SC_NUM_LOCK);
};
// Menu/CC
void Keyboard::common83(){
  if(!fn)
    KP(HID_KEYBOARD_SC_APPLICATION);
};
// F12/Pse
void Keyboard::common85(){
  if(fn)
    KP(HID_KEYBOARD_SC_PAUSE);
  else
    KP(HID_KEYBOARD_SC_F12);
};
// Left/0
void Keyboard::common86(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT);
  else
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
};
// Rght/.
void Keyboard::common87(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE);
  else
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
};
// RAlt/Nx
void Keyboard::common88(){
  if(fn)
    KP(KEY_MEDIA_NEXT);
  else
    KP(HID_KEYBOARD_SC_RIGHT_ALT);
};
// Dwn/00
void Keyboard::common89(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_00);
  else
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
};
