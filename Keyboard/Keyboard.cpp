#include "Keyboard.h"

extern "C" {
#include "LUFA.h"
}

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Peripheral/TWI.h>

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/eeprom.h>

//
// Main loop
//

void Keyboard::loopTask(){
  // states
  if(DEVICE_STATE_Configured!=USB_DeviceState){
    KeyboardReport=NULL;
    LEDReport=NO_LED_REPORT;
  }

  // display
  if(USB_DeviceState!=last_USB_DeviceState){
    last_USB_DeviceState=USB_DeviceState;
    displayForceUpdate();
  }
  if(USB_DeviceState==DEVICE_STATE_Suspended){
    if(USB_Device_RemoteWakeupEnabled!=last_USB_Device_RemoteWakeupEnabled)
      displayForceUpdate();
    last_USB_Device_RemoteWakeupEnabled=USB_Device_RemoteWakeupEnabled;
  }
  if(displayDoUpdate)
    displayUpdate();

  // scan keys during suspend
  if(DEVICE_STATE_Suspended==USB_DeviceState)
    if(USB_Device_RemoteWakeupEnabled)
      scanAll();
}

//
// Constructor
//

Keyboard::Keyboard(FILE *S){
  // Serial
  Stream=S;
  // TWI
  PORTD|=(1<<1); // SDA pull up
  PORTD|=(1<<0); // SCL pull up
  TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 100000L));
  // Init ports
#ifndef TEENSY
  MCPinit();
#else
  portInit();
#endif
  // States
  for(int i=0;i<NUM_KEYS;i++)
    keyState[i]=0;
  keypad=0;
  fn=0;
  LEDReport=NO_LED_REPORT;
  last_USB_DeviceState=NO_USB_DEVICE_STATE;
  last_USB_Device_RemoteWakeupEnabled=USB_Device_RemoteWakeupEnabled;
  KeyboardReport=NULL;
  macroState=MACRO_STATE_NONE;
  macroLocked=true;
  // Load layout
  eeprom_busy_wait();
  layout=eeprom_read_byte((const uint8_t *)EEPROM_LAYOUT);
  if(layout>LAYOUT_MAX){
    layout=US_US;
    eeprom_busy_wait();
    eeprom_write_byte((uint8_t *)EEPROM_LAYOUT, layout);
  }
  // Sequences
  sequence=NULL;
  // Display
  displayInit();
  displayDoUpdate=false;
  displayUpdateAgain=false;
  displayFirstLoopRun=true;
}

//
// C bindings
//

extern Keyboard *kbd;

void keyboardScanAll(USB_KeyboardReport_Data_t *KR){
  kbd->KeyboardReport=KR;
  kbd->scanAll();
}

void keyboardSetLEDs(uint8_t report){
  kbd->setLEDs(report);
}
