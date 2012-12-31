#include "Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>

#include <stdlib.h>

#include "extraKeys.h"

#define KP(key) press(key)

// Q
void Keyboard::dvorak0(){
  KP(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
};
// W
void Keyboard::dvorak1(){
  KP(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
};
// E
void Keyboard::dvorak2(){
  KP(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
};
// R
void Keyboard::dvorak3(){
  KP(HID_KEYBOARD_SC_P);
};
// U
void Keyboard::dvorak4(){
  KP(HID_KEYBOARD_SC_G);
};
// I
void Keyboard::dvorak5(){
  KP(HID_KEYBOARD_SC_C);
};
// O/Tab
void Keyboard::dvorak6(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_TAB );
  else
    KP(HID_KEYBOARD_SC_R);
};
// P/
void Keyboard::dvorak7(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_SLASH);
  else
    KP(HID_KEYBOARD_SC_L);
};
// Ply/CX
void Keyboard::dvorak8(){
  if(!fn)
    KP(KEY_PLAY);
};
// Tab
void Keyboard::dvorak9(){
  KP(HID_KEYBOARD_SC_TAB);
};
// CapsLock/Clear
void Keyboard::dvorak10(){
  if((fn&&!keypad)||(!fn&&keypad)){
    KP(HID_KEYBOARD_SC_ERROR_ROLLOVER);
  }else{
    KP(HID_KEYBOARD_SC_CAPS_LOCK);
  }
};
// F3
void Keyboard::dvorak11(){
  KP(HID_KEYBOARD_SC_F3);
};
// G
void Keyboard::dvorak12(){
  KP(HID_KEYBOARD_SC_Y);
};
// Y
void Keyboard::dvorak13(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_F);
};
// ]}-
void Keyboard::dvorak14(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_MINUS);
  else
    KP(HID_KEYBOARD_SC_EQUAL_AND_PLUS);
};
// F7/Pwr
void Keyboard::dvorak15(){
  if(fn)
    KP(HID_KEYBOARD_SC_POWER);
  else
    KP(HID_KEYBOARD_SC_F7);
};
// [{*
void Keyboard::dvorak16(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_ASTERISK);
  else
    KP(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
};
// Bs/V+
void Keyboard::dvorak17(){
  if(fn)
    KP(HID_KEYBOARD_SC_VOLUME_UP);
  else
    KP(HID_KEYBOARD_SC_BACKSPACE);
};
// Calc
void Keyboard::dvorak18(){
  KP(KEY_CALC);
};
// LSft
void Keyboard::dvorak19(){
  KP(HID_KEYBOARD_SC_LEFT_SHIFT);
};
// AT/CV
void Keyboard::dvorak20(){
  if(!fn)
    KP(HID_KEYBOARD_SC_LEFT_ALT);
};
// Start
void Keyboard::dvorak21(){
  KP(HID_KEYBOARD_SC_LEFT_GUI);
};
// 1!
void Keyboard::dvorak22(){
  KP(HID_KEYBOARD_SC_1_AND_EXCLAMATION);
};
// 2@
void Keyboard::dvorak23(){
  KP(HID_KEYBOARD_SC_2_AND_AT);
};
// 3#
void Keyboard::dvorak24(){
  KP(HID_KEYBOARD_SC_3_AND_HASHMARK);
};
// 4$
void Keyboard::dvorak25(){
  KP(HID_KEYBOARD_SC_4_AND_DOLLAR);
};
// 7&
void Keyboard::dvorak26(){
  KP(HID_KEYBOARD_SC_7_AND_AND_AMPERSAND);
};
// 8*
void Keyboard::dvorak27(){
  KP(HID_KEYBOARD_SC_8_AND_ASTERISK);
};
// 9(
void Keyboard::dvorak28(){
  KP(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS);
};
// 0)
void Keyboard::dvorak29(){
  KP(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS);
};
// F10/PSc
void Keyboard::dvorak30(){
  if(fn)
    KP(HID_KEYBOARD_SC_PRINT_SCREEN);
  else
    KP(HID_KEYBOARD_SC_F10);
};
// End/3
void Keyboard::dvorak31(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN);
  else
    KP(HID_KEYBOARD_SC_END);
};
// PDwn/Nx
void Keyboard::dvorak32(){
  if(fn)
    KP(KEY_BROWSER_FORWARD);
  else
    KP(HID_KEYBOARD_SC_PAGE_DOWN);
};
// F5
void Keyboard::dvorak33(){
  KP(HID_KEYBOARD_SC_F5);
};
// Fn
void Keyboard::dvorak34(){

};
// A
void Keyboard::dvorak35(){
  KP(HID_KEYBOARD_SC_A);
};
// `~
void Keyboard::dvorak36(){
  KP(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
};
// Esc
void Keyboard::dvorak37(){
  KP(HID_KEYBOARD_SC_ESCAPE);
};
// Z
void Keyboard::dvorak38(){
  KP(HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
};
// S
void Keyboard::dvorak39(){
  KP(HID_KEYBOARD_SC_O);
};
// D
void Keyboard::dvorak40(){
  KP(HID_KEYBOARD_SC_E);
};
// F
void Keyboard::dvorak41(){
  KP(HID_KEYBOARD_SC_U);
};
// J/Up
void Keyboard::dvorak42(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_H);
};
// K/End
void Keyboard::dvorak43(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_END);
  else
    KP(HID_KEYBOARD_SC_T);
};
// L/7
void Keyboard::dvorak44(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_7_AND_HOME);
  else
    KP(HID_KEYBOARD_SC_N);
};
// ;:8
void Keyboard::dvorak45(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_S);
};
// \|6
void Keyboard::dvorak46(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE);
};
// www/Bs
void Keyboard::dvorak47(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_BACKSPACE);
//  else
//    KP(KEY_WWW); // FIXME
};
// RSft/+
void Keyboard::dvorak48(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_PLUS);
  else {
    KP(HID_KEYBOARD_SC_RIGHT_SHIFT);
  }
};
// Dsk/Pv
void Keyboard::dvorak49(){
  if(fn)
    KP(KEY_MEDIA_PREVIOUS);
};
// F1/Dvk
void Keyboard::dvorak50(){
  if(fn)
    dvorakQWERTY=!dvorakQWERTY;
  else
    KP(HID_KEYBOARD_SC_F1);
};
// F2
void Keyboard::dvorak51(){
  KP(HID_KEYBOARD_SC_F2);
};
// 5%
void Keyboard::dvorak52(){
  KP(HID_KEYBOARD_SC_5_AND_PERCENTAGE);
};
// 6^
void Keyboard::dvorak53(){
  KP(HID_KEYBOARD_SC_6_AND_CARET);
};
// =+
void Keyboard::dvorak54(){
  KP(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
};
// F8/Slp
void Keyboard::dvorak55(){
  if(fn)
    KP(KEY_SLEEP);
  else
    KP(HID_KEYBOARD_SC_F8);
};
// -_
void Keyboard::dvorak56(){
  KP(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
};
// F9/Wke
void Keyboard::dvorak57(){
  if(fn)
    KP(HID_KEYBOARD_SC_INTERNATIONAL9);
  else
    KP(HID_KEYBOARD_SC_F9);
};
// Home/1
void Keyboard::dvorak58(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_1_AND_END);
  else
    KP(HID_KEYBOARD_SC_HOME);
};
// PUp/Bck
void Keyboard::dvorak59(){
  if(fn)
    KP(KEY_BROWSER_BACK);
  else
    KP(HID_KEYBOARD_SC_PAGE_UP);
};
// LCtrl
void Keyboard::dvorak60(){
  KP(HID_KEYBOARD_SC_LEFT_CONTROL);
};
// Mail/BackTab
void Keyboard::dvorak61(){
  // FIXME Mail
};
// Del/Ins
void Keyboard::dvorak62(){
  if(fn)
    KP(HID_KEYBOARD_SC_INSERT);
  else
    KP(HID_KEYBOARD_SC_DELETE);
};
// F4
void Keyboard::dvorak63(){
  KP(HID_KEYBOARD_SC_F4);
};
// G
void Keyboard::dvorak64(){
  KP(HID_KEYBOARD_SC_I);
};
// D/Home
void Keyboard::dvorak65(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_D);
};
// F6/Ejct
void Keyboard::dvorak66(){
  if(fn)
    KP(KEY_EJECT);
  else
    KP(HID_KEYBOARD_SC_F6);
};
// '"9
void Keyboard::dvorak67(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP);
  else
    KP(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
};
// F11/SLk
void Keyboard::dvorak68(){
  if(fn)
    KP(HID_KEYBOARD_SC_SCROLL_LOCK);
  else
    KP(HID_KEYBOARD_SC_F11);
};
// Up/2
void Keyboard::dvorak69(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_UP_ARROW);
};
// LAlt
void Keyboard::dvorak70(){
  KP(HID_KEYBOARD_SC_LEFT_ALT);
};
// Spc/Mte
void Keyboard::dvorak71(){
  if(fn)
    KP(HID_KEYBOARD_SC_MUTE);
  else
    KP(HID_KEYBOARD_SC_SPACE);
};
// X
void Keyboard::dvorak72(){
  KP(HID_KEYBOARD_SC_Q);
};
// C
void Keyboard::dvorak73(){
  KP(HID_KEYBOARD_SC_J);
};
// V
void Keyboard::dvorak74(){
  KP(HID_KEYBOARD_SC_K);
};
// M/Dwn
void Keyboard::dvorak75(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_M);
};
// ,</Rgt
void Keyboard::dvorak76(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_W);
};
// .>4
void Keyboard::dvorak77(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_V);
};
// Ret/V-
void Keyboard::dvorak78(){
  if(fn)
    KP(HID_KEYBOARD_SC_VOLUME_DOWN);
  else
    KP(HID_KEYBOARD_SC_ENTER);
};
// RCtl/Ret
void Keyboard::dvorak79(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_ENTER);
  else
    KP(HID_KEYBOARD_SC_RIGHT_CONTROL);
};
// NLock
void Keyboard::dvorak80(){
  if(fn)
    KP(HID_KEYBOARD_SC_NUM_LOCK);
};
// B
void Keyboard::dvorak81(){
  KP(HID_KEYBOARD_SC_X);
};
// N/Left
void Keyboard::dvorak82(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_B);
};
// Menu/CC
void Keyboard::dvorak83(){
  if(!fn)
    KP(HID_KEYBOARD_SC_APPLICATION);
};
// /?5
void Keyboard::dvorak84(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_5);
  else
    KP(HID_KEYBOARD_SC_Z);
};
// F12/Pse
void Keyboard::dvorak85(){
  if(fn)
    KP(HID_KEYBOARD_SC_PAUSE);
  else
    KP(HID_KEYBOARD_SC_F12);
};
// Left/0
void Keyboard::dvorak86(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT);
  else
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
};
// Rght/.
void Keyboard::dvorak87(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE);
  else
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
};
// RAlt/Nx
void Keyboard::dvorak88(){
  if(fn)
    KP(KEY_MEDIA_NEXT);
  else
    KP(HID_KEYBOARD_SC_RIGHT_ALT);
};
// Dwn/00
void Keyboard::dvorak89(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_00);
  else
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
};
