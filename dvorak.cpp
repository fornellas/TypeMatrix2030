#include "TypeMatrix.h"

#include <Arduino.h>
#include "extraKeys.h"

#define KP(key) Keyboard.press(key)
#define KR(key) Keyboard.release(key)

// Q
void TypeMatrix::dvorakP0(){
  if(shift)
    KP('"');
  else
    KP('\'');
};
void TypeMatrix::dvorakR0(){
  KR('"');
  KR('\'');
};
// W
void TypeMatrix::dvorakP1(){
  if(shift)
    KP('<');
  else
    KP(',');
};
void TypeMatrix::dvorakR1(){
  KR('<');
  KR(',');
};
// E
void TypeMatrix::dvorakP2(){
  if(shift)
   KP('>');
  else
   KP('.');
};
void TypeMatrix::dvorakR2(){
  KR('>');
  KR('.');
};
// R
void TypeMatrix::dvorakP3(){
  if(shift)
    KP('P');
  else
    KP('p');
};
void TypeMatrix::dvorakR3(){
  KR('P');
  KR('p');
};
// U
void TypeMatrix::dvorakP4(){
  if(shift)
    KP('G');
  else
    KP('g');
};
void TypeMatrix::dvorakR4(){
  KR('G');
  KR('g');
};
// I
void TypeMatrix::dvorakP5(){
  if(shift)
    KP('C');
  else
    KP('c');
};
void TypeMatrix::dvorakR5(){
  KR('C');
  KR('c');
};
// O/Tab
void TypeMatrix::dvorakP6(){
  if(fn||keypad)
    KP(KEY_TAB);
  else
    if(shift)
      KP('R');
    else
      KP('r');
};
void TypeMatrix::dvorakR6(){
  KR(KEY_TAB);
  KR('R');
  KR('r');
};
// P/
void TypeMatrix::dvorakP7(){
  if(fn||keypad)
    KP(KEY_KP_SLASH);
  else
    if(shift)
      KP('L');
    else
      KP('l');
};
void TypeMatrix::dvorakR7(){
  KR(KEY_KP_SLASH);
  KR('L');
  KR('l');
};
// Ply/CX
void TypeMatrix::dvorakP8(){
  if(fn){
    KP(KEY_LEFT_CTRL);
    KP('x');
    KR('x');
    KR(KEY_LEFT_CTRL);
  }else{
    // FIXME Play
  }
};
void TypeMatrix::dvorakR8(){
  // FIXME Play
};
// Tab
void TypeMatrix::dvorakP9(){
  KP(KEY_TAB);
};
void TypeMatrix::dvorakR9(){
  KR(KEY_TAB);
};
// CapsLock/Clear
void TypeMatrix::dvorakP10(){
  if(fn||keypad){
    ; // FIXME clear
  }else{
    KP(KEY_CAPS_LOCK);
  }
};
void TypeMatrix::dvorakR10(){
  // FIXME clear
  KR(KEY_CAPS_LOCK);
};
// F3
void TypeMatrix::dvorakP11(){
  KP(KEY_F3);
};
void TypeMatrix::dvorakR11(){
  KR(KEY_F3);
};
// G
void TypeMatrix::dvorakP12(){
  if(shift)
    KP('Y');
  else
    KP('y');
};
void TypeMatrix::dvorakR12(){
  KR('Y');
  KR('y');
};
// Y
void TypeMatrix::dvorakP13(){
  if(fn||keypad)
    KP(KEY_HOME);
  else
    if(shift)
      KP('F');
    else
      KP('f');
};
void TypeMatrix::dvorakR13(){
  KR(KEY_HOME);
  KR('F');
  KR('F');
};
// ]}-
void TypeMatrix::dvorakP14(){
  if(fn||keypad)
    KP(KEY_KP_MINUS);
  else
    if(shift)
      KP('+');
    else
      KP('=');
};
void TypeMatrix::dvorakR14(){
  KR(KEY_KP_MINUS);
  KR('+');
  KR('=');
};
// F7/Pwr
void TypeMatrix::dvorakP15(){
  if(fn)
    KP(KEY_POWER); // FIXME not working
  else
    KP(KEY_F7);
};
void TypeMatrix::dvorakR15(){
  KR(KEY_POWER);
  KR(KEY_F7);
};
// [{*
void TypeMatrix::dvorakP16(){
  if(fn||keypad)
    KP(KEY_KP_ASTERISK);
  else
    if(shift)
      KP('?');
    else
      KP('/');
};
void TypeMatrix::dvorakR16(){
  KR(KEY_KP_ASTERISK);
  KR('?');
  KR('/');
};
// Bs/V+
void TypeMatrix::dvorakP17(){
  if(fn)
    KP(KEY_VOLUME_UP); // FIXME not working
  else
    KP(KEY_BACKSPACE);
};
void TypeMatrix::dvorakR17(){
  KR(KEY_VOLUME_UP);
  KR(KEY_BACKSPACE);
};
// Calc
void TypeMatrix::dvorakP18(){
  // FIXME calc
};
void TypeMatrix::dvorakR18(){
  // FIXME calc
};
// LSft
void TypeMatrix::dvorakP19(){
  KP(KEY_LEFT_SHIFT);
  shift++;
};
void TypeMatrix::dvorakR19(){
  KR(KEY_LEFT_SHIFT);
  shift--;
};
// AT/CV
void TypeMatrix::dvorakP20(){
  if(fn){
    KP(KEY_LEFT_CTRL);
    KP('v');
    KR('v');
    KR(KEY_LEFT_CTRL);
  }else{
    KP(KEY_LEFT_ALT);
    KP(KEY_TAB);
    KR(KEY_TAB);
  }
};
void TypeMatrix::dvorakR20(){
  KR(KEY_LEFT_ALT);
};
// Start
void TypeMatrix::dvorakP21(){
  KP(KEY_LEFT_GUI);
};
void TypeMatrix::dvorakR21(){
  KR(KEY_LEFT_GUI);
};
// 1!
void TypeMatrix::dvorakP22(){
  if(shift)
    KP('!');
  else
    KP('1');
};
void TypeMatrix::dvorakR22(){
  KR('!');
  KR('1');
};
// 2@
void TypeMatrix::dvorakP23(){
  if(shift)
    KP('@');
  else
    KP('2');
};
void TypeMatrix::dvorakR23(){
  KR('@');
  KR('2');
};
// 3#
void TypeMatrix::dvorakP24(){
  if(shift)
    KP('#');
  else
    KP('3');
};
void TypeMatrix::dvorakR24(){
  KR('#');
  KR('3');
};
// 4$
void TypeMatrix::dvorakP25(){
  if(shift)
    KP('$');
  else
    KP('4');
};
void TypeMatrix::dvorakR25(){
  KR('$');
  KR('4');
};
// 7&
void TypeMatrix::dvorakP26(){
  if(shift)
    KP('&');
  else
    KP('7');
};
void TypeMatrix::dvorakR26(){
  KR('&');
  KR('7');
};
// 8*
void TypeMatrix::dvorakP27(){
  if(shift)
    KP('*');
  else
    KP('8');
};
void TypeMatrix::dvorakR27(){
  KR('*');
  KR('8');
};
// 9(
void TypeMatrix::dvorakP28(){
  if(shift)
    KP('(');
  else
    KP('9');
};
void TypeMatrix::dvorakR28(){
  KR('(');
  KR('9');
};
// 0)
void TypeMatrix::dvorakP29(){
  if(shift)
    KP(')');
  else
    KP('0');
};
void TypeMatrix::dvorakR29(){
  KR(')');
  KR('0');
};
// F10/PSc
void TypeMatrix::dvorakP30(){
  if(fn)
    if(alt)
      KP(KEY_SYSRQ);
    else
      KP(KEY_PRINT_SCREEN);
  else
    KP(KEY_F10);
};
void TypeMatrix::dvorakR30(){
  KR(KEY_SYSRQ);
  KR(KEY_PRINT_SCREEN);
  KR(KEY_F10);
};
// End/3
void TypeMatrix::dvorakP31(){
  if(fn||keypad)
    KP(KEY_KP_3_PAGE_DOWN);
  else
    KP(KEY_END);
};
void TypeMatrix::dvorakR31(){
  KR(KEY_KP_3_PAGE_DOWN);
  KR(KEY_END);
};
// PDwn/Nx
void TypeMatrix::dvorakP32(){
  if(fn)
    ;// FIXME Next
  else
    KP(KEY_PAGE_DOWN);
};
void TypeMatrix::dvorakR32(){
//  KR // FIXME Next
  KR(KEY_PAGE_DOWN);
};
// F5
void TypeMatrix::dvorakP33(){
  KP(KEY_F5);
};
void TypeMatrix::dvorakR33(){
  KR(KEY_F5);
};
// Fn
void TypeMatrix::dvorakP34(){
  fn=1;
};
void TypeMatrix::dvorakR34(){
  fn=0;
};
// A
void TypeMatrix::dvorakP35(){
  if(shift)
    KP('A');
  else
    KP('a');
};
void TypeMatrix::dvorakR35(){
  KR('A');
  KR('a');
};
// `~
void TypeMatrix::dvorakP36(){
  if(shift)
    KP('~');
  else
    KP('`');
};
void TypeMatrix::dvorakR36(){
  KR('~');
  KR('`');
};
// Esc
void TypeMatrix::dvorakP37(){
  KP(KEY_ESC);
};
void TypeMatrix::dvorakR37(){
  KR(KEY_ESC);
};
// Z
void TypeMatrix::dvorakP38(){
  if(shift)
    KP(':');
  else
    KP(';');
};
void TypeMatrix::dvorakR38(){
  KR(':');
  KR(';');
};
// S
void TypeMatrix::dvorakP39(){
  if(shift)
    KP('O');
  else
    KP('o');
};
void TypeMatrix::dvorakR39(){
  KR('O');
  KR('o');
};
// D
void TypeMatrix::dvorakP40(){
  if(shift)
    KP('E');
  else
    KP('e');
};
void TypeMatrix::dvorakR40(){
  KR('E');
  KR('e');
};
// F
void TypeMatrix::dvorakP41(){
  if(shift)
    KP('U');
  else
    KP('u');
};
void TypeMatrix::dvorakR41(){
  KR('U');
  KR('u');
};
// J/Up
void TypeMatrix::dvorakP42(){
  if(fn||keypad)
    KP(KEY_UP_ARROW);
  else
    if(shift)
      KP('H');
    else
      KP('h');
};
void TypeMatrix::dvorakR42(){
  KR(KEY_UP_ARROW);
  KR('H');
  KR('h');
};
// K/End
void TypeMatrix::dvorakP43(){
  if(fn||keypad)
    KP(KEY_END);
  else
    if(shift)
      KP('T');
    else
      KP('t');
};
void TypeMatrix::dvorakR43(){
  KR(KEY_END);
  KR('T');
  KR('t');
};
// L/7
void TypeMatrix::dvorakP44(){
  if(fn||keypad)
    KP(KEY_KP_7_HOME);
  else
    if(shift)
      KP('N');
    else
      KP('n');
};
void TypeMatrix::dvorakR44(){
  KR(KEY_KP_7_HOME);
  KR('N');
  KR('n');
};
// ;:8
void TypeMatrix::dvorakP45(){
  if(fn||keypad)
    KP(KEY_KP_8_UP);
  else
    if(shift)
      KP('S');
    else
      KP('s');
};
void TypeMatrix::dvorakR45(){
  KR(KEY_KP_8_UP);
  KR('S');
  KR('s');
};
// \|6
void TypeMatrix::dvorakP46(){
  if(fn||keypad)
    KP(KEY_KP_6_RIGHT);
  else
    if(shift)
      KP('|');
    else
      KP('\\');
};
void TypeMatrix::dvorakR46(){
  KR(KEY_KP_6_RIGHT);
  KR('|');
  KR('\\');
};
// www/Bs
void TypeMatrix::dvorakP47(){
  if(fn||keypad)
    KP(KEY_BACKSPACE);
  else
    ; // FIXME www
};
void TypeMatrix::dvorakR47(){
  KR(KEY_BACKSPACE);
  // FIXME www
};
// RSft/+
void TypeMatrix::dvorakP48(){
  if(fn||keypad)
    KP(KEY_KP_PLUS);
  else {
    KP(KEY_RIGHT_SHIFT);
    shift++;
  }
};
void TypeMatrix::dvorakR48(){
  KR(KEY_RIGHT_SHIFT);
  KR(KEY_KP_PLUS);
  shift--;
};
// Dsk/Pv
void TypeMatrix::dvorakP49(){
  // FIXME Deskpot
  // FIXME Prev
};
void TypeMatrix::dvorakR49(){
  // FIXME Desktop
  // FIXME Prev
};
// F1/Dvk
void TypeMatrix::dvorakP50(){
  if(fn)
    dvorakQWERTY=!dvorakQWERTY;
  else
    KP(KEY_F1);
};
void TypeMatrix::dvorakR50(){
  KR(KEY_F1);
};
// F2
void TypeMatrix::dvorakP51(){
  KP(KEY_F2);
};
void TypeMatrix::dvorakR51(){
  KR(KEY_F2);
};
// 5%
void TypeMatrix::dvorakP52(){
  if(shift)
    KP('%');
  else
    KP('5');
};
void TypeMatrix::dvorakR52(){
  KR('%');
  KR('5');
};
// 6^
void TypeMatrix::dvorakP53(){
  if(shift)
    KP('^');
  else
    KP('6');
};
void TypeMatrix::dvorakR53(){
  KR('^');
  KR('6');
};
// =+
void TypeMatrix::dvorakP54(){
  if(shift)
    KP('}');
  else
    KP(']');
};
void TypeMatrix::dvorakR54(){
  KR('}');
  KR(']');
};
// F8/Slp
void TypeMatrix::dvorakP55(){
  if(fn)
    ; // FIXME sleep
  else
    KP(KEY_F8);
};
void TypeMatrix::dvorakR55(){
  // FIXME sleep
  KR(KEY_F8);
};
// -_
void TypeMatrix::dvorakP56(){
  if(shift)
    KP('{');
  else
    KP('[');
};
void TypeMatrix::dvorakR56(){
  KR('{');
  KR('[');
};
// F9/Wke
void TypeMatrix::dvorakP57(){
  if(fn)
    ; // FIXME wake
  else
    KP(KEY_F9);
};
void TypeMatrix::dvorakR57(){
  // FIXME wake
  KR(KEY_F9);
};
// Home/1
void TypeMatrix::dvorakP58(){
  if(fn||keypad)
    KP(KEY_KP_1_END);
  else
    KP(KEY_HOME);
};
void TypeMatrix::dvorakR58(){
  KR(KEY_KP_1_END);
  KR(KEY_HOME);
};
// PUp/Bck
void TypeMatrix::dvorakP59(){
  if(fn)
    ; // FIXME back
  else
    KP(KEY_PAGE_UP);
};
void TypeMatrix::dvorakR59(){
  // FIXME back
  KR(KEY_PAGE_UP);
};
// LCtrl
void TypeMatrix::dvorakP60(){
  KP(KEY_LEFT_CTRL);
};
void TypeMatrix::dvorakR60(){
  KR(KEY_LEFT_CTRL);
};
// Mil/BTb
void TypeMatrix::dvorakP61(){
  // FIXME Mail
  // FIXME BackTab
};
void TypeMatrix::dvorakR61(){
  // FIXME Mail
  // FIXME BackTab
};
// Del/Ins
void TypeMatrix::dvorakP62(){
  if(fn)
    KP(KEY_INSERT);
  else
    KP(KEY_DELETE);
};
void TypeMatrix::dvorakR62(){
  KR(KEY_INSERT);
  KR(KEY_DELETE);
};
// F4
void TypeMatrix::dvorakP63(){
  KP(KEY_F4);
};
void TypeMatrix::dvorakR63(){
  KR(KEY_F4);
};
// G
void TypeMatrix::dvorakP64(){
  if(shift)
    KP('I');
  else
    KP('i');
};
void TypeMatrix::dvorakR64(){
  KR('I');
  KR('i');
};
// D/Home
void TypeMatrix::dvorakP65(){
  if(fn||keypad)
    KP(KEY_HOME);
  else
    if(shift)
      KP('D');
    else
      KP('d');
};
void TypeMatrix::dvorakR65(){
  KR(KEY_HOME);
  KR('D');
  KR('d');
};
// F6/Ejct
void TypeMatrix::dvorakP66(){
  if(fn)
    ; // FIXME Eject
  else
    KP(KEY_F6);
};
void TypeMatrix::dvorakR66(){
  // FIXME Eject
  KR(KEY_F6);
};
// '"9
void TypeMatrix::dvorakP67(){
  if(fn||keypad)
    KP(KEY_KP_9_PAGE_UP);
  else
    if(shift)
      KP('_');
    else
      KP('-');
};
void TypeMatrix::dvorakR67(){
  KR(KEY_KP_9_PAGE_UP);
  KR('_');
  KR('-');
};
// F11/SLk
void TypeMatrix::dvorakP68(){
  if(fn)
    KP(KEY_SCROLL_LOCK);
  else
    KP(KEY_F11);
};
void TypeMatrix::dvorakR68(){
  KR(KEY_SCROLL_LOCK);
  KR(KEY_F11);
};
// Up/2
void TypeMatrix::dvorakP69(){
  if(fn||keypad)
    KP(KEY_KP_2_DOWN);
  else
    KP(KEY_UP_ARROW);
};
void TypeMatrix::dvorakR69(){
  KR(KEY_KP_2_DOWN);
  KR(KEY_UP_ARROW);
};
// LAlt
void TypeMatrix::dvorakP70(){
  KP(KEY_LEFT_ALT);
  alt++;
};
void TypeMatrix::dvorakR70(){
  KR(KEY_LEFT_ALT);
  alt--;
};
// Spc/Mte
void TypeMatrix::dvorakP71(){
  if(fn)
    KP(KEY_MUTE);
  else
    KP(' ');
};
void TypeMatrix::dvorakR71(){
  KR(KEY_MUTE);
  KR(' ');
};
// X
void TypeMatrix::dvorakP72(){
  if(shift)
    KP('Q');
  else
    KP('q');
};
void TypeMatrix::dvorakR72(){
  KR('Q');
  KR('q');
};
// C
void TypeMatrix::dvorakP73(){
  if(shift)
    KP('J');
  else
    KP('j');
};
void TypeMatrix::dvorakR73(){
  KR('J');
  KR('j');
};
// V
void TypeMatrix::dvorakP74(){
  if(shift)
    KP('K');
  else
    KP('k');
};
void TypeMatrix::dvorakR74(){
  KR('K');
  KR('k');
};
// M/Dwn
void TypeMatrix::dvorakP75(){
  if(fn||keypad)
    KP(KEY_DOWN_ARROW);
  else
    if(shift)
      KP('M');
    else
      KP('m');
};
void TypeMatrix::dvorakR75(){
  KR(KEY_DOWN_ARROW);
  KR('M');
  KR('m');
};
// ,</Rgt
void TypeMatrix::dvorakP76(){
  if(fn||keypad)
    KP(KEY_RIGHT_ARROW);
  else
    if(shift)
      KP('W');
    else
      KP('w');
};
void TypeMatrix::dvorakR76(){
  KR(KEY_RIGHT_ARROW);
  KR('W');
  KR('w');
};
// .>4
void TypeMatrix::dvorakP77(){
  if(fn||keypad)
    KP(KEY_KP_4_LEFT);
  else
    if(shift)
      KP('V');
    else
      KP('v');
};
void TypeMatrix::dvorakR77(){
  KR(KEY_KP_4_LEFT);
  KR('V');
  KR('v');
};
// Ret/V-
void TypeMatrix::dvorakP78(){
  if(fn)
    KP(KEY_VOLUME_DOWN);
  else
    KP(KEY_RETURN);
};
void TypeMatrix::dvorakR78(){
  KR(KEY_VOLUME_DOWN);
  KR(KEY_RETURN);  
};
// RCtl/Ret
void TypeMatrix::dvorakP79(){
  if(fn||keypad)
    KP(KEY_KP_RETURN);
  else
    KP(KEY_RIGHT_CTRL);
};
void TypeMatrix::dvorakR79(){
  KR(KEY_KP_RETURN);
  KR(KEY_RIGHT_CTRL);
};
// NLock
void TypeMatrix::dvorakP80(){
  if(fn)
    KP(KEY_NUM_LOCK);
  else
    keypad=!keypad;
};
void TypeMatrix::dvorakR80(){
  KR(KEY_NUM_LOCK);
};
// B
void TypeMatrix::dvorakP81(){
  if(shift)
    KP('X');
  else
    KP('x');
};
void TypeMatrix::dvorakR81(){
  KR('X');
  KR('x');
};
// N/Left
void TypeMatrix::dvorakP82(){
  if(fn||keypad)
    KP(KEY_LEFT_ARROW);
  else
    if(shift)
      KP('B');
    else
      KP('b');
};
void TypeMatrix::dvorakR82(){
  KR(KEY_LEFT_ARROW);
  KR('B');
  KR('b');
};
// Menu/CC
void TypeMatrix::dvorakP83(){
  if(fn){
    KP(KEY_RIGHT_CTRL);
    KP('c');
    KR('c');
    KR(KEY_RIGHT_CTRL);
  }else
    KP(KEY_MENU);
};
void TypeMatrix::dvorakR83(){
  KR(KEY_MENU);
};
// /?5
void TypeMatrix::dvorakP84(){
  if(fn||keypad)
    KP(KEY_KP_5);
  else
    if(shift)
      KP('Z');
    else
      KP('z');
};
void TypeMatrix::dvorakR84(){
  KR(KEY_KP_5);
  KR('Z');
  KR('z');
};
// F12/Pse
void TypeMatrix::dvorakP85(){
  if(fn)
    ; // FIXME pause
  else
    KP(KEY_F12);
};
void TypeMatrix::dvorakR85(){
  // FIXME pause
  KR(KEY_F12);
};
// Left/0
void TypeMatrix::dvorakP86(){
  if(fn||keypad)
    KP(KEY_KP_0_INSERT);
  else
    KP(KEY_LEFT_ARROW);
};
void TypeMatrix::dvorakR86(){
  KR(KEY_KP_0_INSERT);
  KR(KEY_LEFT_ARROW);
};
// Rght/.
void TypeMatrix::dvorakP87(){
  if(fn||keypad)
    KP(KEY_KP_DOT_DELETE);
  else
    KP(KEY_RIGHT_ARROW);
};
void TypeMatrix::dvorakR87(){
  KR(KEY_KP_DOT_DELETE);
  KR(KEY_RIGHT_ARROW);
};
// RAlt/Nx
void TypeMatrix::dvorakP88(){
  KP(KEY_RIGHT_ALT);
  alt++;
};
void TypeMatrix::dvorakR88(){
  KR(KEY_RIGHT_ALT);
  alt--;
};
// Dwn/00
void TypeMatrix::dvorakP89(){
  if(fn||keypad)
    Keyboard.print("00");
  else
    KP(KEY_DOWN_ARROW);
};
void TypeMatrix::dvorakR89(){
  KR(KEY_DOWN_ARROW);
};
