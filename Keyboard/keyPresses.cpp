#include "Keyboard.h"

#include <avr/eeprom.h>

#define getByte(b, v) ((v>>(b*8))&0xFF)

void Keyboard::keyPressesInit(){
  keyPresses0=new EnduranceEEPROM(EEPROM_KEYPRESSES_0_LOCATIONS, (const uint8_t *)EEPROM_KEYPRESSES_0);
  keyPresses1=new EnduranceEEPROM(EEPROM_KEYPRESSES_1_LOCATIONS, (const uint8_t *)EEPROM_KEYPRESSES_1);
  ramKeyPresses=(((uint32_t)eeprom_read_byte((const uint8_t *)EEPROM_KEYPRESSES_3)<<24)|((uint32_t)eeprom_read_byte((const uint8_t *)EEPROM_KEYPRESSES_2)<<16)|(keyPresses1->read()<<8)|keyPresses0->read());
}

uint32_t Keyboard::readKeyPresses(){

  return ramKeyPresses;
}

void Keyboard::keyPress(){
  ramKeyPresses++;
  saveKeyPresses();
}

void Keyboard::saveKeyPresses(){
  uint8_t b;
  eeprom_update_byte((uint8_t *)EEPROM_KEYPRESSES_3, getByte(3, ramKeyPresses));
  eeprom_update_byte((uint8_t *)EEPROM_KEYPRESSES_2, getByte(2, ramKeyPresses));
  b=getByte(1, ramKeyPresses);
  if(b!=keyPresses1->read())
    keyPresses1->write(b);
  b=getByte(0, ramKeyPresses);
  if(b-keyPresses0->read()>=EEPROM_KEYPRESSES_0_WRITE_INTERVAL)
    keyPresses0->write(b);
}
