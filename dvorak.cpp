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
    KP('F');
  else
    KP('f');
};
void TypeMatrix::dvorakR4(){
  KR('F');
  KR('f');
};
// I
void TypeMatrix::dvorakP5(){
  if(shift)
    KP('G');
  else
    KP('g');
};
void TypeMatrix::dvorakR5(){
  KR('G');
  KR('g');
};
// O/Tab
void TypeMatrix::dvorakP6(){
  if(fn||numLock)
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
  if(fn||numLock)
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
  
};
// Tab
void TypeMatrix::dvorakP9(){
  KP(KEY_TAB);
};
void TypeMatrix::dvorakR9(){
  KR(KEY_TAB);
};
// CL/AC
void TypeMatrix::dvorakP10(){
  if(fn){
    // FIXME calc
  }else{
    KP(KEY_CAPS_LOCK);
  }
};
void TypeMatrix::dvorakR10(){
  KR(KEY_CAPS_LOCK);
};
// F3
void TypeMatrix::dvorakP11(){
  
};
void TypeMatrix::dvorakR11(){
  
};
// G
void TypeMatrix::dvorakP12(){
  
};
void TypeMatrix::dvorakR12(){
  
};
// H/Home
void TypeMatrix::dvorakP13(){
  
};
void TypeMatrix::dvorakR13(){
  
};
// ]}-
void TypeMatrix::dvorakP14(){
  
};
void TypeMatrix::dvorakR14(){
  
};
// F7/Pwr
void TypeMatrix::dvorakP15(){
  
};
void TypeMatrix::dvorakR15(){
  
};
// [{*
void TypeMatrix::dvorakP16(){
  
};
void TypeMatrix::dvorakR16(){
  
};
// Bs/V+
void TypeMatrix::dvorakP17(){

};
void TypeMatrix::dvorakR17(){

};
// Calc
void TypeMatrix::dvorakP18(){
  
};
void TypeMatrix::dvorakR18(){
  
};
// LSft
void TypeMatrix::dvorakP19(){
  KP(KEY_LEFT_SHIFT);
  shift=1;
};
void TypeMatrix::dvorakR19(){
  KR(KEY_LEFT_SHIFT);
  shift=0;
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
  
};
void TypeMatrix::dvorakR22(){
  
};
// 2@
void TypeMatrix::dvorakP23(){
  
};
void TypeMatrix::dvorakR23(){
  
};
// 3#
void TypeMatrix::dvorakP24(){
  
};
void TypeMatrix::dvorakR24(){
  
};
// 4$
void TypeMatrix::dvorakP25(){
  
};
void TypeMatrix::dvorakR25(){
  
};
// 7&
void TypeMatrix::dvorakP26(){
  
};
void TypeMatrix::dvorakR26(){
  
};
// 8*
void TypeMatrix::dvorakP27(){
  
};
void TypeMatrix::dvorakR27(){
  
};
// 9(
void TypeMatrix::dvorakP28(){
  
};
void TypeMatrix::dvorakR28(){
  
};
// 0)
void TypeMatrix::dvorakP29(){
  
};
void TypeMatrix::dvorakR29(){
  
};
// F10/PSc
void TypeMatrix::dvorakP30(){
  
};
void TypeMatrix::dvorakR30(){
  
};
// End/3
void TypeMatrix::dvorakP31(){
  
};
void TypeMatrix::dvorakR31(){
  
};
// PDwn/Nx
void TypeMatrix::dvorakP32(){
  
};
void TypeMatrix::dvorakR32(){
  
};
// F5
void TypeMatrix::dvorakP33(){
  
};
void TypeMatrix::dvorakR33(){
  
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
  
};
void TypeMatrix::dvorakR35(){
  
};
// `~
void TypeMatrix::dvorakP36(){
  
};
void TypeMatrix::dvorakR36(){
  
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
  
};
void TypeMatrix::dvorakR38(){
  
};
// S
void TypeMatrix::dvorakP39(){
  
};
void TypeMatrix::dvorakR39(){
  
};
// D
void TypeMatrix::dvorakP40(){
  
};
void TypeMatrix::dvorakR40(){
  
};
// F
void TypeMatrix::dvorakP41(){
  
};
void TypeMatrix::dvorakR41(){
  
};
// J/Up
void TypeMatrix::dvorakP42(){
  
};
void TypeMatrix::dvorakR42(){
  
};
// K/End
void TypeMatrix::dvorakP43(){
  
};
void TypeMatrix::dvorakR43(){
  
};
// L/7
void TypeMatrix::dvorakP44(){
  
};
void TypeMatrix::dvorakR44(){
  
};
// ;:8
void TypeMatrix::dvorakP45(){
  
};
void TypeMatrix::dvorakR45(){
  
};
// \|6
void TypeMatrix::dvorakP46(){
  
};
void TypeMatrix::dvorakR46(){
  
};
// www/Bs
void TypeMatrix::dvorakP47(){
  
};
void TypeMatrix::dvorakR47(){
  
};
// RSft/+
void TypeMatrix::dvorakP48(){
  if(shift||fn)
    KP(KEY_KP_PLUS);
  else {
    KP(KEY_RIGHT_SHIFT);
    shift=1;
  }
};
void TypeMatrix::dvorakR48(){
  KR(KEY_RIGHT_SHIFT);
  KR(KEY_KP_PLUS);
  shift=0;
};
// Dsk/Pv
void TypeMatrix::dvorakP49(){
  
};
void TypeMatrix::dvorakR49(){
  
};
// F1/Dvk
void TypeMatrix::dvorakP50(){
  
};
void TypeMatrix::dvorakR50(){
  
};
// F2
void TypeMatrix::dvorakP51(){
  
};
void TypeMatrix::dvorakR51(){
  
};
// 5%
void TypeMatrix::dvorakP52(){
  
};
void TypeMatrix::dvorakR52(){
  
};
// 6^
void TypeMatrix::dvorakP53(){
  
};
void TypeMatrix::dvorakR53(){
  
};
// =+
void TypeMatrix::dvorakP54(){
  
};
void TypeMatrix::dvorakR54(){
  
};
// F8/Slp
void TypeMatrix::dvorakP55(){
  
};
void TypeMatrix::dvorakR55(){
  
};
// -_
void TypeMatrix::dvorakP56(){
  
};
void TypeMatrix::dvorakR56(){
  
};
// F9/Wke
void TypeMatrix::dvorakP57(){
  
};
void TypeMatrix::dvorakR57(){
  
};
// Home/1
void TypeMatrix::dvorakP58(){
  
};
void TypeMatrix::dvorakR58(){
  
};
// PUp/Bck
void TypeMatrix::dvorakP59(){
  
};
void TypeMatrix::dvorakR59(){
  
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
  
};
void TypeMatrix::dvorakR61(){
  
};
// Del/Ins
void TypeMatrix::dvorakP62(){
  
};
void TypeMatrix::dvorakR62(){
  
};
// F4
void TypeMatrix::dvorakP63(){
  
};
void TypeMatrix::dvorakR63(){
  
};
// G
void TypeMatrix::dvorakP64(){
  
};
void TypeMatrix::dvorakR64(){
  
};
// H/Home
void TypeMatrix::dvorakP65(){
  
};
void TypeMatrix::dvorakR65(){
  
};
// F6/Ejct
void TypeMatrix::dvorakP66(){
  
};
void TypeMatrix::dvorakR66(){
  
};
// '"9
void TypeMatrix::dvorakP67(){
  
};
void TypeMatrix::dvorakR67(){
  
};
// F11/SLk
void TypeMatrix::dvorakP68(){
  
};
void TypeMatrix::dvorakR68(){
  
};
// Up/2
void TypeMatrix::dvorakP69(){
  
};
void TypeMatrix::dvorakR69(){
  
};
// LAlt
void TypeMatrix::dvorakP70(){
  KP(KEY_LEFT_ALT);
};
void TypeMatrix::dvorakR70(){
  KR(KEY_LEFT_ALT);
};
// Spc/Mte
void TypeMatrix::dvorakP71(){
  
};
void TypeMatrix::dvorakR71(){
  
};
// X
void TypeMatrix::dvorakP72(){
  
};
void TypeMatrix::dvorakR72(){
  
};
// C
void TypeMatrix::dvorakP73(){
  
};
void TypeMatrix::dvorakR73(){
  
};
// V
void TypeMatrix::dvorakP74(){
  
};
void TypeMatrix::dvorakR74(){
  
};
// M/Dwn
void TypeMatrix::dvorakP75(){
  
};
void TypeMatrix::dvorakR75(){
  
};
// ,</Rgt
void TypeMatrix::dvorakP76(){
  
};
void TypeMatrix::dvorakR76(){
  
};
// .>4
void TypeMatrix::dvorakP77(){
  
};
void TypeMatrix::dvorakR77(){
  
};
// Ret/V-
void TypeMatrix::dvorakP78(){
  Keyboard.press(KEY_RETURN);
};
void TypeMatrix::dvorakR78(){
  Keyboard.release(KEY_RETURN);  
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
  
};
void TypeMatrix::dvorakR80(){
  
};
// B
void TypeMatrix::dvorakP81(){
  
};
void TypeMatrix::dvorakR81(){
  
};
// N/Left
void TypeMatrix::dvorakP82(){
  
};
void TypeMatrix::dvorakR82(){
  
};
// Menu/CC
void TypeMatrix::dvorakP83(){

};
void TypeMatrix::dvorakR83(){

};
// /?5
void TypeMatrix::dvorakP84(){
  
};
void TypeMatrix::dvorakR84(){
  
};
// F12/Pse
void TypeMatrix::dvorakP85(){
  
};
void TypeMatrix::dvorakR85(){
  
};
// Left/0
void TypeMatrix::dvorakP86(){
  
};
void TypeMatrix::dvorakR86(){
  
};
// Rght/.
void TypeMatrix::dvorakP87(){
  
};
void TypeMatrix::dvorakR87(){
  
};
// RAlt/Nx
void TypeMatrix::dvorakP88(){
  KP(KEY_RIGHT_ALT);
};
void TypeMatrix::dvorakR88(){
  KR(KEY_RIGHT_ALT);
};
// Dwn/00
void TypeMatrix::dvorakP89(){
  
};
void TypeMatrix::dvorakR89(){
  
};
