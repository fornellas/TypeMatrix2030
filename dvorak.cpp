#include "Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>

#include "extraKeys.h"

#define KP(key) press(key)
#define KR(key) release(key)

// Q
void Keyboard::dvorakP0(){
  KP(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
};
void Keyboard::dvorakR0(){
  KR(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
};
// W
void Keyboard::dvorakP1(){
  KP(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
};
void Keyboard::dvorakR1(){
  KR(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
};
// E
void Keyboard::dvorakP2(){
  KP(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
};
void Keyboard::dvorakR2(){
  KR(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
};
// R
void Keyboard::dvorakP3(){
  KP(HID_KEYBOARD_SC_P);
};
void Keyboard::dvorakR3(){
  KR(HID_KEYBOARD_SC_P);
};
// U
void Keyboard::dvorakP4(){
  KP(HID_KEYBOARD_SC_G);
};
void Keyboard::dvorakR4(){
  KR(HID_KEYBOARD_SC_G);
};
// I
void Keyboard::dvorakP5(){
  KP(HID_KEYBOARD_SC_C);
};
void Keyboard::dvorakR5(){
  KR(HID_KEYBOARD_SC_C);
};
// O/Tab
void Keyboard::dvorakP6(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_TAB );
  else
    KP(HID_KEYBOARD_SC_R);
};
void Keyboard::dvorakR6(){
  KR(HID_KEYBOARD_SC_TAB );
  KR(HID_KEYBOARD_SC_R);
};
// P/
void Keyboard::dvorakP7(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_SLASH);
  else
    KP(HID_KEYBOARD_SC_L);
};
void Keyboard::dvorakR7(){
  KR(HID_KEYBOARD_SC_KEYPAD_SLASH);
  KR(HID_KEYBOARD_SC_L);
};
// Ply/CX
void Keyboard::dvorakP8(){
  if(fn){
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
    KP(HID_KEYBOARD_SC_X);
    KR(HID_KEYBOARD_SC_X);
    KR(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else{
    KP(HID_KEYBOARD_SC_EXSEL);
  }
};
void Keyboard::dvorakR8(){
  KR(HID_KEYBOARD_SC_EXSEL);
};
// Tab
void Keyboard::dvorakP9(){
  KP(HID_KEYBOARD_SC_TAB);
};
void Keyboard::dvorakR9(){
  KR(HID_KEYBOARD_SC_TAB);
};
// CapsLock/Clear
void Keyboard::dvorakP10(){
  if(fn||keypad){
    KP(HID_KEYBOARD_SC_ERROR_ROLLOVER);
  }else{
    KP(HID_KEYBOARD_SC_CAPS_LOCK);
  }
};
void Keyboard::dvorakR10(){
  KR(HID_KEYBOARD_SC_ERROR_ROLLOVER);
  KR(HID_KEYBOARD_SC_CAPS_LOCK);
};
// F3
void Keyboard::dvorakP11(){
  KP(HID_KEYBOARD_SC_F3);
};
void Keyboard::dvorakR11(){
  KR(HID_KEYBOARD_SC_F3);
};
// G
void Keyboard::dvorakP12(){
  KP(HID_KEYBOARD_SC_Y);
};
void Keyboard::dvorakR12(){
  KR(HID_KEYBOARD_SC_Y);
};
// Y
void Keyboard::dvorakP13(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_F);
};
void Keyboard::dvorakR13(){
  KR(HID_KEYBOARD_SC_HOME);
  KR(HID_KEYBOARD_SC_F);
};
// ]}-
void Keyboard::dvorakP14(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_MINUS);
  else
    KP(HID_KEYBOARD_SC_EQUAL_AND_PLUS);
};
void Keyboard::dvorakR14(){
  KR(HID_KEYBOARD_SC_KEYPAD_MINUS);
  KR(HID_KEYBOARD_SC_EQUAL_AND_PLUS);
};
// F7/Pwr
void Keyboard::dvorakP15(){
  if(fn)
    KP(HID_KEYBOARD_SC_POWER);
  else
    KP(HID_KEYBOARD_SC_F7);
};
void Keyboard::dvorakR15(){
  KR(HID_KEYBOARD_SC_POWER);
  KR(HID_KEYBOARD_SC_F7);
};
// [{*
void Keyboard::dvorakP16(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_ASTERISK);
  else
    KP(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
};
void Keyboard::dvorakR16(){
  KR(HID_KEYBOARD_SC_KEYPAD_ASTERISK);
  KR(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
};
// Bs/V+
void Keyboard::dvorakP17(){
  if(fn)
    KP(HID_KEYBOARD_SC_F24);
  else
    KP(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
};
void Keyboard::dvorakR17(){
  KR(HID_KEYBOARD_SC_F24);
  KR(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
};
// Calc
void Keyboard::dvorakP18(){
  KP(HID_KEYBOARD_SC_INTERNATIONAL6);
};
void Keyboard::dvorakR18(){
  KR(HID_KEYBOARD_SC_INTERNATIONAL6);
};
// LSft
void Keyboard::dvorakP19(){
  KP(HID_KEYBOARD_SC_LEFT_SHIFT);
  shift++;
};
void Keyboard::dvorakR19(){
  KR(HID_KEYBOARD_SC_LEFT_SHIFT);
  shift--;
};
// AT/CV
void Keyboard::dvorakP20(){
  if(fn){
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
    KP(HID_KEYBOARD_SC_V);
    KR(HID_KEYBOARD_SC_V);
    KR(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else{
    KP(HID_KEYBOARD_SC_LEFT_ALT);
    KP(HID_KEYBOARD_SC_TAB);
    KR(HID_KEYBOARD_SC_TAB);
  }
};
void Keyboard::dvorakR20(){
  KR(HID_KEYBOARD_SC_LEFT_ALT);
};
// Start
void Keyboard::dvorakP21(){
  KP(HID_KEYBOARD_SC_LEFT_GUI);
};
void Keyboard::dvorakR21(){
  KR(HID_KEYBOARD_SC_LEFT_GUI);
};
// 1!
void Keyboard::dvorakP22(){
  KP(HID_KEYBOARD_SC_1_AND_EXCLAMATION);
};
void Keyboard::dvorakR22(){
  KR(HID_KEYBOARD_SC_1_AND_EXCLAMATION);
};
// 2@
void Keyboard::dvorakP23(){
  KP(HID_KEYBOARD_SC_2_AND_AT);
};
void Keyboard::dvorakR23(){
  KR(HID_KEYBOARD_SC_2_AND_AT);
};
// 3#
void Keyboard::dvorakP24(){
  KP(HID_KEYBOARD_SC_3_AND_HASHMARK);
};
void Keyboard::dvorakR24(){
  KR(HID_KEYBOARD_SC_3_AND_HASHMARK);
};
// 4$
void Keyboard::dvorakP25(){
  KP(HID_KEYBOARD_SC_4_AND_DOLLAR);
};
void Keyboard::dvorakR25(){
  KR(HID_KEYBOARD_SC_4_AND_DOLLAR);
};
// 7&
void Keyboard::dvorakP26(){
  KP(HID_KEYBOARD_SC_7_AND_AND_AMPERSAND);
};
void Keyboard::dvorakR26(){
  KR(HID_KEYBOARD_SC_7_AND_AND_AMPERSAND);
};
// 8*
void Keyboard::dvorakP27(){
  KP(HID_KEYBOARD_SC_8_AND_ASTERISK);
};
void Keyboard::dvorakR27(){
  KR(HID_KEYBOARD_SC_8_AND_ASTERISK);
};
// 9(
void Keyboard::dvorakP28(){
  KP(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS);
};
void Keyboard::dvorakR28(){
  KR(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS);
};
// 0)
void Keyboard::dvorakP29(){
  KP(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS);
};
void Keyboard::dvorakR29(){
  KR(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS);
};
// F10/PSc
void Keyboard::dvorakP30(){
  if(fn)
    if(alt)
      KP(HID_KEYBOARD_SC_SISREQ);
    else
      KP(HID_KEYBOARD_SC_PRINT_SCREEN);
  else
    KP(HID_KEYBOARD_SC_F10);
};
void Keyboard::dvorakR30(){
  KR(HID_KEYBOARD_SC_SISREQ);
  KR(HID_KEYBOARD_SC_PRINT_SCREEN);
  KR(HID_KEYBOARD_SC_F10);
};
// End/3
void Keyboard::dvorakP31(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN);
  else
    KP(HID_KEYBOARD_SC_END);
};
void Keyboard::dvorakR31(){
  KR(HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN);
  KR(HID_KEYBOARD_SC_END);
};
// PDwn/Nx
void Keyboard::dvorakP32(){
  if(fn)
    KP(HID_KEYBOARD_SC_INTERNATIONAL6);
  else
    KP(HID_KEYBOARD_SC_PAGE_DOWN);
};
void Keyboard::dvorakR32(){
  KR(HID_KEYBOARD_SC_INTERNATIONAL6);
  KR(HID_KEYBOARD_SC_PAGE_DOWN);
};
// F5
void Keyboard::dvorakP33(){
  KP(HID_KEYBOARD_SC_F5);
};
void Keyboard::dvorakR33(){
  KR(HID_KEYBOARD_SC_F5);
};
// Fn
void Keyboard::dvorakP34(){
  fn=1;
};
void Keyboard::dvorakR34(){
  fn=0;
};
// A
void Keyboard::dvorakP35(){
  KP(HID_KEYBOARD_SC_A);
};
void Keyboard::dvorakR35(){
  KR(HID_KEYBOARD_SC_A);
};
// `~
void Keyboard::dvorakP36(){
  KP(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
};
void Keyboard::dvorakR36(){
  KR(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
};
// Esc
void Keyboard::dvorakP37(){
  KP(HID_KEYBOARD_SC_ESCAPE);
};
void Keyboard::dvorakR37(){
  KR(HID_KEYBOARD_SC_ESCAPE);
};
// Z
void Keyboard::dvorakP38(){
  KP(HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
};
void Keyboard::dvorakR38(){
  KR(HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
};
// S
void Keyboard::dvorakP39(){
  KP(HID_KEYBOARD_SC_O);
};
void Keyboard::dvorakR39(){
  KR(HID_KEYBOARD_SC_O);
};
// D
void Keyboard::dvorakP40(){
  KP(HID_KEYBOARD_SC_E);
};
void Keyboard::dvorakR40(){
  KR(HID_KEYBOARD_SC_E);
};
// F
void Keyboard::dvorakP41(){
  KP(HID_KEYBOARD_SC_U);
};
void Keyboard::dvorakR41(){
  KR(HID_KEYBOARD_SC_U);
};
// J/Up
void Keyboard::dvorakP42(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_H);
};
void Keyboard::dvorakR42(){
  KR(HID_KEYBOARD_SC_UP_ARROW);
  KR(HID_KEYBOARD_SC_H);
};
// K/End
void Keyboard::dvorakP43(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_END);
  else
    KP(HID_KEYBOARD_SC_T);
};
void Keyboard::dvorakR43(){
  KR(HID_KEYBOARD_SC_END);
  KR(HID_KEYBOARD_SC_T);
};
// L/7
void Keyboard::dvorakP44(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_7_AND_HOME);
  else
    KP(HID_KEYBOARD_SC_N);
};
void Keyboard::dvorakR44(){
  KR(HID_KEYBOARD_SC_KEYPAD_7_AND_HOME);
  KR(HID_KEYBOARD_SC_N);
};
// ;:8
void Keyboard::dvorakP45(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_S);
};
void Keyboard::dvorakR45(){
  KR(HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW);
  KR(HID_KEYBOARD_SC_S);
};
// \|6
void Keyboard::dvorakP46(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE);
};
void Keyboard::dvorakR46(){
  KR(HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW);
  KR(HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE);
};
// www/Bs
void Keyboard::dvorakP47(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
  else
    KP(KEY_WWW);
};
void Keyboard::dvorakR47(){
  KR(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
  KR(KEY_WWW);
};
// RSft/+
void Keyboard::dvorakP48(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_PLUS);
  else {
    KP(HID_KEYBOARD_SC_RIGHT_SHIFT);
    shift++;
  }
};
void Keyboard::dvorakR48(){
  KR(HID_KEYBOARD_SC_KEYPAD_PLUS);
  KR(HID_KEYBOARD_SC_RIGHT_SHIFT);
  shift--;
};
// Dsk/Pv
void Keyboard::dvorakP49(){
  if(fn)
    KP(KEY_MEDIA_PREV);
  else{
    KP(HID_KEYBOARD_SC_LEFT_GUI);
    KP(HID_KEYBOARD_SC_D);
    KR(HID_KEYBOARD_SC_D);
    KR(HID_KEYBOARD_SC_LEFT_GUI);
  }
};
void Keyboard::dvorakR49(){
  KR(KEY_MEDIA_PREV);
};
// F1/Dvk
void Keyboard::dvorakP50(){
  if(fn)
    dvorakQWERTY=!dvorakQWERTY;
  else
    KP(HID_KEYBOARD_SC_F1);
};
void Keyboard::dvorakR50(){
  KR(HID_KEYBOARD_SC_F1);
};
// F2
void Keyboard::dvorakP51(){
  KP(HID_KEYBOARD_SC_F2);
};
void Keyboard::dvorakR51(){
  KR(HID_KEYBOARD_SC_F2);
};
// 5%
void Keyboard::dvorakP52(){
  KP(HID_KEYBOARD_SC_5_AND_PERCENTAGE);
};
void Keyboard::dvorakR52(){
  KR(HID_KEYBOARD_SC_5_AND_PERCENTAGE);
};
// 6^
void Keyboard::dvorakP53(){
  KP(HID_KEYBOARD_SC_6_AND_CARET);
};
void Keyboard::dvorakR53(){
  KR(HID_KEYBOARD_SC_6_AND_CARET);
};
// =+
void Keyboard::dvorakP54(){
  KP(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
};
void Keyboard::dvorakR54(){
  KR(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
};
// F8/Slp
void Keyboard::dvorakP55(){
  if(fn)
    KP(HID_KEYBOARD_SC_INTERNATIONAL8);
  else
    KP(HID_KEYBOARD_SC_F8);
};
void Keyboard::dvorakR55(){
  KR(HID_KEYBOARD_SC_INTERNATIONAL8);
  KR(HID_KEYBOARD_SC_F8);
};
// -_
void Keyboard::dvorakP56(){
  KP(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
};
void Keyboard::dvorakR56(){
  KR(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
};
// F9/Wke
void Keyboard::dvorakP57(){
  if(fn)
    KP(HID_KEYBOARD_SC_INTERNATIONAL9);
  else
    KP(HID_KEYBOARD_SC_F9);
};
void Keyboard::dvorakR57(){
  KR(HID_KEYBOARD_SC_INTERNATIONAL9);
  KR(HID_KEYBOARD_SC_F9);
};
// Home/1
void Keyboard::dvorakP58(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_1_AND_END);
  else
    KP(HID_KEYBOARD_SC_HOME);
};
void Keyboard::dvorakR58(){
  KR(HID_KEYBOARD_SC_KEYPAD_1_AND_END);
  KR(HID_KEYBOARD_SC_HOME);
};
// PUp/Bck
void Keyboard::dvorakP59(){
  if(fn)
    KP(HID_KEYBOARD_SC_RETURN);
  else
    KP(HID_KEYBOARD_SC_PAGE_UP);
};
void Keyboard::dvorakR59(){
  KR(HID_KEYBOARD_SC_RETURN);
  KR(HID_KEYBOARD_SC_PAGE_UP);
};
// LCtrl
void Keyboard::dvorakP60(){
  KP(HID_KEYBOARD_SC_LEFT_CONTROL);
};
void Keyboard::dvorakR60(){
  KR(HID_KEYBOARD_SC_LEFT_CONTROL);
};
// Mil/BTb
void Keyboard::dvorakP61(){
  if(fn){
    KP(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
    KP(HID_KEYBOARD_SC_L);
    KR(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
    KR(HID_KEYBOARD_SC_L);
  }else
    KP(HID_KEYBOARD_SC_CANCEL);
};
void Keyboard::dvorakR61(){
  KR(HID_KEYBOARD_SC_CANCEL);
};
// Del/Ins
void Keyboard::dvorakP62(){
  if(fn)
    KP(HID_KEYBOARD_SC_INSERT);
  else
    KP(HID_KEYBOARD_SC_DELETE);
};
void Keyboard::dvorakR62(){
  KR(HID_KEYBOARD_SC_INSERT);
  KR(HID_KEYBOARD_SC_DELETE);
};
// F4
void Keyboard::dvorakP63(){
  KP(HID_KEYBOARD_SC_F4);
};
void Keyboard::dvorakR63(){
  KR(HID_KEYBOARD_SC_F4);
};
// G
void Keyboard::dvorakP64(){
  KP(HID_KEYBOARD_SC_I);
};
void Keyboard::dvorakR64(){
  KR(HID_KEYBOARD_SC_I);
};
// D/Home
void Keyboard::dvorakP65(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_D);
};
void Keyboard::dvorakR65(){
  KR(HID_KEYBOARD_SC_HOME);
  KR(HID_KEYBOARD_SC_D);
};
// F6/Ejct
void Keyboard::dvorakP66(){
  if(fn)
    KP(HID_KEYBOARD_SC_OPER);
  else
    KP(HID_KEYBOARD_SC_F6);
};
void Keyboard::dvorakR66(){
  KR(HID_KEYBOARD_SC_OPER);
  KR(HID_KEYBOARD_SC_F6);
};
// '"9
void Keyboard::dvorakP67(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP);
  else
    KP(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
};
void Keyboard::dvorakR67(){
  KR(HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP);
  KR(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
};
// F11/SLk
void Keyboard::dvorakP68(){
  if(fn)
    KP(HID_KEYBOARD_SC_SCROLL_LOCK);
  else
    KP(HID_KEYBOARD_SC_F11);
};
void Keyboard::dvorakR68(){
  KR(HID_KEYBOARD_SC_SCROLL_LOCK);
  KR(HID_KEYBOARD_SC_F11);
};
// Up/2
void Keyboard::dvorakP69(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_UP_ARROW);
};
void Keyboard::dvorakR69(){
  KR(HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW);
  KR(HID_KEYBOARD_SC_UP_ARROW);
};
// LAlt
void Keyboard::dvorakP70(){
  KP(HID_KEYBOARD_SC_LEFT_ALT);
  alt++;
};
void Keyboard::dvorakR70(){
  KR(HID_KEYBOARD_SC_LEFT_ALT);
  alt--;
};
// Spc/Mte
void Keyboard::dvorakP71(){
  if(fn)
    KP(HID_KEYBOARD_SC_F22);
  else
    KP(HID_KEYBOARD_SC_SPACE);
};
void Keyboard::dvorakR71(){
  KR(HID_KEYBOARD_SC_F22);
  KR(HID_KEYBOARD_SC_SPACE);
};
// X
void Keyboard::dvorakP72(){
  KP(HID_KEYBOARD_SC_Q);
};
void Keyboard::dvorakR72(){
  KR(HID_KEYBOARD_SC_Q);
};
// C
void Keyboard::dvorakP73(){
  KP(HID_KEYBOARD_SC_J);
};
void Keyboard::dvorakR73(){
  KR(HID_KEYBOARD_SC_J);
};
// V
void Keyboard::dvorakP74(){
  KP(HID_KEYBOARD_SC_K);
};
void Keyboard::dvorakR74(){
  KR(HID_KEYBOARD_SC_K);
};
// M/Dwn
void Keyboard::dvorakP75(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_M);
};
void Keyboard::dvorakR75(){
  KR(HID_KEYBOARD_SC_DOWN_ARROW);
  KR(HID_KEYBOARD_SC_M);
};
// ,</Rgt
void Keyboard::dvorakP76(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_W);
};
void Keyboard::dvorakR76(){
  KR(HID_KEYBOARD_SC_RIGHT_ARROW);
  KR(HID_KEYBOARD_SC_W);
};
// .>4
void Keyboard::dvorakP77(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_V);
};
void Keyboard::dvorakR77(){
  KR(HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW);
  KR(HID_KEYBOARD_SC_V);
};
// Ret/V-
void Keyboard::dvorakP78(){
  if(fn)
    KP(HID_KEYBOARD_SC_F23);
  else
    KP(HID_KEYBOARD_SC_ENTER);
};
void Keyboard::dvorakR78(){
  KR(HID_KEYBOARD_SC_F23);
  KR(HID_KEYBOARD_SC_ENTER);
};
// RCtl/Ret
void Keyboard::dvorakP79(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_ENTER);
  else
    KP(HID_KEYBOARD_SC_RIGHT_CONTROL);
};
void Keyboard::dvorakR79(){
  KR(HID_KEYBOARD_SC_KEYPAD_ENTER);
  KR(HID_KEYBOARD_SC_RIGHT_CONTROL);
};
// NLock
void Keyboard::dvorakP80(){
  if(fn)
    KP(HID_KEYBOARD_SC_NUM_LOCK);
  else
    keypad=!keypad;
};
void Keyboard::dvorakR80(){
  KR(HID_KEYBOARD_SC_NUM_LOCK);
};
// B
void Keyboard::dvorakP81(){
  KP(HID_KEYBOARD_SC_X);
};
void Keyboard::dvorakR81(){
  KR(HID_KEYBOARD_SC_X);
};
// N/Left
void Keyboard::dvorakP82(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_B);
};
void Keyboard::dvorakR82(){
  KR(HID_KEYBOARD_SC_LEFT_ARROW);
  KR(HID_KEYBOARD_SC_B);
};
// Menu/CC
void Keyboard::dvorakP83(){
  if(fn){
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
    KP(HID_KEYBOARD_SC_C);
    KR(HID_KEYBOARD_SC_C);
    KR(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_MUTE);
};
void Keyboard::dvorakR83(){
  KR(HID_KEYBOARD_SC_MUTE);
};
// /?5
void Keyboard::dvorakP84(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_5);
  else
    KP(HID_KEYBOARD_SC_Z);
};
void Keyboard::dvorakR84(){
  KR(HID_KEYBOARD_SC_KEYPAD_5);
  KR(HID_KEYBOARD_SC_Z);
};
// F12/Pse
void Keyboard::dvorakP85(){
  if(fn)
    KP(HID_KEYBOARD_SC_SELECT);
  else
    KP(HID_KEYBOARD_SC_F12);
};
void Keyboard::dvorakR85(){
  KR(HID_KEYBOARD_SC_SELECT);
  KR(HID_KEYBOARD_SC_F12);
};
// Left/0
void Keyboard::dvorakP86(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT);
  else
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
};
void Keyboard::dvorakR86(){
  KR(HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT);
  KR(HID_KEYBOARD_SC_LEFT_ARROW);
};
// Rght/.
void Keyboard::dvorakP87(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE);
  else
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
};
void Keyboard::dvorakR87(){
  KR(HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE);
  KR(HID_KEYBOARD_SC_RIGHT_ARROW);
};
// RAlt/Nx
void Keyboard::dvorakP88(){
  KP(HID_KEYBOARD_SC_RIGHT_ALT);
  alt++;
};
void Keyboard::dvorakR88(){
  KR(HID_KEYBOARD_SC_RIGHT_ALT);
  alt--;
};
// Dwn/00
void Keyboard::dvorakP89(){
  if(fn||keypad)
    KP(HID_KEYBOARD_SC_KEYPAD_00);
  else
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
};
void Keyboard::dvorakR89(){
  KR(HID_KEYBOARD_SC_KEYPAD_00);
  KR(HID_KEYBOARD_SC_DOWN_ARROW);
};
