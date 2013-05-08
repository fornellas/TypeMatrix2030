#include "Keyboard.h"

#include <avr/eeprom.h>

#define getByte(b, v) ((v>>(b*8))&0xFF)

void Keyboard::keyPressesInit(){
  keyPresses0=new EnduranceEEPROM(EEPROM_KEYPRESSES_0_LOCATIONS, (uint8_t *)EEPROM_KEYPRESSES_0);
  keyPresses1=new EnduranceEEPROM(EEPROM_KEYPRESSES_1_LOCATIONS, (uint8_t *)EEPROM_KEYPRESSES_1);
  ramKeyPresses=readEEPROMKeyPresses();
}

uint32_t Keyboard::readKeyPresses(){
  return ramKeyPresses;
}

void Keyboard::keyPress(){
  uint8_t b,r;
  ramKeyPresses++;

  b=getByte(0, ramKeyPresses);
  r=keyPresses0->read();
  if((b>r)) {
    if(b-r>=EEPROM_KEYPRESSES_0_WRITE_INTERVAL)
      keyPresses0->write(b);
  }else{
    if(b<r)
      if(255-r+b+1>=EEPROM_KEYPRESSES_0_WRITE_INTERVAL)
        keyPresses0->write(b);
  }

  b=getByte(1, ramKeyPresses);
  if(b!=keyPresses1->read())
    keyPresses1->write(b);

  eeprom_update_byte((uint8_t *)EEPROM_KEYPRESSES_2, getByte(2, ramKeyPresses));

  eeprom_update_byte((uint8_t *)EEPROM_KEYPRESSES_3, getByte(3, ramKeyPresses));
}

uint32_t Keyboard::readEEPROMKeyPresses(){
  return (
    (((uint32_t)eeprom_read_byte((const uint8_t *)EEPROM_KEYPRESSES_3))<<24)
    |
    (((uint32_t)eeprom_read_byte((const uint8_t *)EEPROM_KEYPRESSES_2))<<16)
    |
    (((uint32_t)keyPresses1->read())<<8)
    |
    ((uint32_t)keyPresses0->read())
    );
}


