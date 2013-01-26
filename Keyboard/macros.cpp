#include "Keyboard.h"

//
// Macros
//

void Keyboard::playMacro(uint8_t key){
  
}

void Keyboard::changeMacroMode(uint8_t mode){
  macroState=mode;
  displayForceUpdate();
}
