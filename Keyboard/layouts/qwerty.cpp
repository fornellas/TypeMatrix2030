#include "../Keyboard.h"

#include <LUFA/Drivers/USB/USB.h>

#include <stdlib.h>

#include "extraKeys.h"

// Q
void Keyboard::qwerty0(){
  KP(HID_KEYBOARD_SC_Q);
};
// W
void Keyboard::qwerty1(){
  KP(HID_KEYBOARD_SC_W);
};
// E
void Keyboard::qwerty2(){
  KP(HID_KEYBOARD_SC_E);
};
// R
void Keyboard::qwerty3(){
  KP(HID_KEYBOARD_SC_R);
};
// U
void Keyboard::qwerty4(){
  KP(HID_KEYBOARD_SC_U);
};
// I
void Keyboard::qwerty5(){
  KP(HID_KEYBOARD_SC_I);
};
// O/Tab
void Keyboard::qwerty6(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_TAB );
  else
    KP(HID_KEYBOARD_SC_O);
};
// P/
void Keyboard::qwerty7(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_SLASH);
  else
    KP(HID_KEYBOARD_SC_P);
};
// T
void Keyboard::qwerty12(){
  KP(HID_KEYBOARD_SC_T);
};
// Y
void Keyboard::qwerty13(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_Y);
};
// ]}-
void Keyboard::qwerty14(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_MINUS);
  else
    KP(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE);
};
// [{*
void Keyboard::qwerty16(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_ASTERISK);
  else
    KP(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE);
};
// A
void Keyboard::qwerty35(){
  KP(HID_KEYBOARD_SC_A);
};
// `~
void Keyboard::qwerty36(){
  KP(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE);
};
// Z
void Keyboard::qwerty38(){
  KP(HID_KEYBOARD_SC_Z);
};
// S
void Keyboard::qwerty39(){
  KP(HID_KEYBOARD_SC_S);
};
// D
void Keyboard::qwerty40(){
  KP(HID_KEYBOARD_SC_D);
};
// F
void Keyboard::qwerty41(){
  KP(HID_KEYBOARD_SC_F);
};
// J/Up
void Keyboard::qwerty42(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_J);
};
// K/End
void Keyboard::qwerty43(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_END);
  else
    KP(HID_KEYBOARD_SC_K);
};
// L/7
void Keyboard::qwerty44(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_7_AND_HOME);
  else
    KP(HID_KEYBOARD_SC_L);
};
// ;:8
void Keyboard::qwerty45(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW);
  else
    KP(HID_KEYBOARD_SC_SEMICOLON_AND_COLON);
};
// \|6
void Keyboard::qwerty46(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_BACKSLASH_AND_PIPE);
};
// =+
void Keyboard::qwerty54(){
  KP(HID_KEYBOARD_SC_EQUAL_AND_PLUS);
};
// -_
void Keyboard::qwerty56(){
  KP(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE);
};
// G
void Keyboard::qwerty64(){
  KP(HID_KEYBOARD_SC_G);
};
// H/Home
void Keyboard::qwerty65(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_HOME);
  else
    KP(HID_KEYBOARD_SC_H);
};
// '"9
void Keyboard::qwerty67(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP);
  else
    KP(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE);
};
// X
void Keyboard::qwerty72(){
  KP(HID_KEYBOARD_SC_X);
};
// C
void Keyboard::qwerty73(){
  KP(HID_KEYBOARD_SC_C);
};
// V
void Keyboard::qwerty74(){
  KP(HID_KEYBOARD_SC_V);
};
// M/Dwn
void Keyboard::qwerty75(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_DOWN_ARROW);
  else
    KP(HID_KEYBOARD_SC_M);
};
// ,</Rgt
void Keyboard::qwerty76(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_RIGHT_ARROW);
  else
    KP(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN);
};
// .>4
void Keyboard::qwerty77(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN);
};
// B
void Keyboard::qwerty81(){
  KP(HID_KEYBOARD_SC_B);
};
// N/Left
void Keyboard::qwerty82(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_LEFT_ARROW);
  else
    KP(HID_KEYBOARD_SC_N);
};
// /?5
void Keyboard::qwerty84(){
  if((fn&&!keypad)||(!fn&&keypad))
    KP(HID_KEYBOARD_SC_KEYPAD_5);
  else
    KP(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK);
};
