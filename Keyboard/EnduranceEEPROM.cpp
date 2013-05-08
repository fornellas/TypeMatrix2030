#include "EnduranceEEPROM.h"

#include <avr/eeprom.h>

#define addrPointer(p) (baseAddr+(uint16_t)p)
#define addrValue(p) (baseAddr+(uint16_t)locations+(uint16_t)p)
#define readPointer(p) eeprom_read_byte((const uint8_t *)addrPointer(p))

EnduranceEEPROM::EnduranceEEPROM(uint8_t locations, uint8_t *baseAddr){
  this->locations=locations;
  this->baseAddr=baseAddr;
  if(locations==256)
    locations=255;
  loadPointer();
}

uint8_t EnduranceEEPROM::getNextPointer(){
  uint8_t nextPointer=pointer+1;
  if(nextPointer==locations)
    return 0;
  else
    return nextPointer;
}

void EnduranceEEPROM::loadPointer(){
  for(pointer=0;pointer<locations;pointer++){
    uint8_t nextPointerValue=readPointer(getNextPointer());
    uint8_t currPointerValue=readPointer(pointer);
    if(nextPointerValue>currPointerValue){
      if(nextPointerValue-currPointerValue!=1)
        break;
    }else{
      if(nextPointerValue==currPointerValue)
        break;
      else
        if(((255-currPointerValue)+(nextPointerValue)+1)!=1)
          break;
    }
  }
  if(pointer==locations)
    --pointer;
}

uint8_t EnduranceEEPROM::read(){
  return eeprom_read_byte((const uint8_t *)addrValue(pointer));
}

void EnduranceEEPROM::write(uint8_t value){
  uint8_t nextPointer=getNextPointer();
  eeprom_write_byte((uint8_t *)addrValue(nextPointer), value);
  eeprom_write_byte((uint8_t *)addrPointer(nextPointer), readPointer(pointer)+1);
  pointer=nextPointer;
}
