#include "../Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>

#include <stdlib.h>

#include "extraKeys.h"

// Q
void Keyboard::dvorak0(){
  if(fn){
    KP(HID_KEYBOARD_SC_Q);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
};
// W
void Keyboard::dvorak1(){
  if(fn){
    KP(HID_KEYBOARD_SC_W);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
};
// E
void Keyboard::dvorak2(){
  if(fn){
    KP(HID_KEYBOARD_SC_E);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
};
// R
void Keyboard::dvorak3(){
  if(fn){
    KP(HID_KEYBOARD_SC_R);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
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
// T
void Keyboard::dvorak12(){
  if(fn){
    KP(HID_KEYBOARD_SC_T);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
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
// [{*
void Keyboard::dvorak16(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_ASTERISK);
  else
    KP(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
};
// A
void Keyboard::dvorak35(){
  if(fn)
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  KP(HID_KEYBOARD_SC_A);
};
// `~
void Keyboard::dvorak36(){
  KP(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
};
// Z
void Keyboard::dvorak38(){
  if(fn){
    KP(HID_KEYBOARD_SC_Z);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
};
// S
void Keyboard::dvorak39(){
  if(fn){
    KP(HID_KEYBOARD_SC_S);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_O);
};
// D
void Keyboard::dvorak40(){
  if(fn){
    KP(HID_KEYBOARD_SC_D);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_E);
};
// F
void Keyboard::dvorak41(){
  if(fn){
    KP(HID_KEYBOARD_SC_F);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
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
    KP(HID_KEYBOARD_SC_BACKSLASH_AND_PIPE);
};
// =+
void Keyboard::dvorak54(){
  KP(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
};
// -_
void Keyboard::dvorak56(){
  KP(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
};
// G
void Keyboard::dvorak64(){
  if(fn){
    KP(HID_KEYBOARD_SC_G);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_I);
};
// H/Home
void Keyboard::dvorak65(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_D);
};
// '"9
void Keyboard::dvorak67(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP);
  else
    KP(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
};
// X
void Keyboard::dvorak72(){
  if(fn){
    KP(HID_KEYBOARD_SC_X);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_Q);
};
// C
void Keyboard::dvorak73(){
  if(fn){
    KP(HID_KEYBOARD_SC_C);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_J);
};
// V
void Keyboard::dvorak74(){
  if(fn){
    KP(HID_KEYBOARD_SC_V);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
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
// B
void Keyboard::dvorak81(){
  if(fn){
    KP(HID_KEYBOARD_SC_B);
    KP(HID_KEYBOARD_SC_LEFT_CONTROL);
  }else
    KP(HID_KEYBOARD_SC_X);
};
// N/Left
void Keyboard::dvorak82(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_B);
};
// /?5
void Keyboard::dvorak84(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_5);
  else
    KP(HID_KEYBOARD_SC_Z);
};
