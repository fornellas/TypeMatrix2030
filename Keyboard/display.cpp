#include "Keyboard.h"

#define U8G_CS PN(5,5)		// PF5
#define U8G_A0 PN(5,7)		// PF7
#define U8G_RESET PN(5,6)	// PF6
#define U8G_SCK PN(1,1)
#define U8G_MOSI PN(1,2)

void Keyboard::displayInit(){
  u8g_InitSPI(&u8g, &u8g_dev_ssd1306_128x64_sw_spi, U8G_SCK, U8G_MOSI, U8G_CS, U8G_A0, U8G_RESET);

  u8g_SetFont(&u8g, u8g_font_6x10);
}

void Keyboard::displayDrawIndicator(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x){
  if(on){
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawBox(&u8g, x, 0, 13, 16);
    u8g_SetColorIndex(&u8g, 0);
    u8g_DrawStrP(&u8g, x+4, 11, str);
  }else{
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawFrame(&u8g, x, 0, 13, 16);
    u8g_DrawStrP(&u8g, x+4, 11, str);
  }
}

void Keyboard::displayDrawStrCenter(u8g_pgm_uint8_t *str, uint8_t y){
  uint8_t x;
  x=u8g_GetWidth(&u8g)/2-u8g_GetStrWidthP(&u8g, str)/2;
  u8g_DrawStrP(&u8g, x, y, str);
}

void Keyboard::displayForceUpdate(){
  if(displayDoUpdate)
    displayUpdateAgain=true;
  else{
    displayDoUpdate=true;
    displayUpdateAgain=false;
  }
}

void Keyboard::displayUpdate(){
  /* Causes screen corruption
  // break current loop if new update asked
  if(displayUpdateAgain){
    displayUpdateAgain=false;
    displayFirstLoopRun=true;
  } */
  // first iteration, save vars for processing
  if(displayFirstLoopRun){
    u8g_FirstPage(&u8g);
    displayFirstLoopRun=false;
    display_var_USB_DeviceState=USB_DeviceState;
    display_var_LEDReport=LEDReport;
    display_var_KeyboardReport=KeyboardReport;
    display_var_macroState=macroState;
    display_var_USB_Device_RemoteWakeupEnabled=USB_Device_RemoteWakeupEnabled;
  }
  // draw display
  switch(display_var_USB_DeviceState){
    case DEVICE_STATE_Unattached:
      displayDrawStrCenter(U8G_PSTR("Unattached"), 11);
      break;
    case DEVICE_STATE_Powered:
      displayDrawStrCenter(U8G_PSTR("Powered"), 11);
      break;
    case DEVICE_STATE_Default:
      displayDrawStrCenter(U8G_PSTR("Default"), 11);
      break;
    case DEVICE_STATE_Addressed:
      displayDrawStrCenter(U8G_PSTR("Addressed"), 11);
      break;
    case DEVICE_STATE_Configured:
      // LEDs / layout
      if(display_var_LEDReport!=NO_LED_REPORT)
        displayDrawLEDs();
      if(NULL!=display_var_KeyboardReport)
        displayDrawLayoutStates();
      // Macros
      switch(display_var_macroState){
        case MACRO_STATE_INIT:
          displayDrawStrCenter(U8G_PSTR("Macro"), 38);
          break;
        case MACRO_STATE_REC_INIT:
          displayDrawStrCenter(U8G_PSTR("<Record macro>"), 32);
          displayDrawStrCenter(U8G_PSTR("Macro number?"), 32+11);
          break;
        case MACRO_STATE_DEL:
          displayDrawStrCenter(U8G_PSTR("<Delete macro>"), 32);
          displayDrawStrCenter(U8G_PSTR("Macro number?"), 32+11);
          break;
        case MACRO_STATE_UNLOCK:
          displayDrawStrCenter(U8G_PSTR("<Unlock macros>"), 32);
          displayDrawStrCenter(U8G_PSTR("Type password:"), 32+11);
          break;
      }
      break;
    case DEVICE_STATE_Suspended:
      displayDrawStrCenter(U8G_PSTR("Suspended"), 11);
      if(display_var_USB_Device_RemoteWakeupEnabled){
        displayDrawStrCenter(U8G_PSTR("Press any key"), 32);
        displayDrawStrCenter(U8G_PSTR("to wake up"), 32+11);
      }
      break;
  }
  // last iteration
  if(!u8g_NextPage(&u8g)){
    // force new display update if required
    if(displayUpdateAgain){
      displayUpdateAgain=false;
      displayFirstLoopRun=true;
      return;
    }else{
      displayDoUpdate=false;
      displayFirstLoopRun=true;
    }
  }
}

void Keyboard::displayDrawLEDs(){
  // Keyboard LEDs
  if(LEDReport & HID_KEYBOARD_LED_NUMLOCK)
    displayDrawIndicator(U8G_PSTR("1"), 1, 0);
  else
    displayDrawIndicator(U8G_PSTR("1"), 0, 0);
  if(LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
    displayDrawIndicator(U8G_PSTR("A"), 1, 14);
  else
    displayDrawIndicator(U8G_PSTR("A"), 0, 14);
  if(LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
    displayDrawIndicator(U8G_PSTR("S"), 1, 28);
  else
    displayDrawIndicator(U8G_PSTR("S"), 0, 28);
}

void Keyboard::setLEDs(uint8_t report){
  LEDReport=report;
  displayForceUpdate();
}

void Keyboard::displayDrawLayoutStates(){
  // Keypad
  if(keypad)
    displayDrawIndicator(U8G_PSTR("K"), 1, 48);
  else
    displayDrawIndicator(U8G_PSTR("K"), 0, 48);
  // Layout
  switch(layout){
    case US_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 68);
      displayDrawIndicator(U8G_PSTR("D"), 0, 82);
      displayDrawIndicator(U8G_PSTR("U"), 1, 101);
      displayDrawIndicator(U8G_PSTR("2"), 0, 115);
      break;
    case US_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 68);
      displayDrawIndicator(U8G_PSTR("D"), 1, 82);
      displayDrawIndicator(U8G_PSTR("U"), 1, 101);
      displayDrawIndicator(U8G_PSTR("2"), 0, 115);
      break;
    case ABNT2_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 68);
      displayDrawIndicator(U8G_PSTR("D"), 0, 82);
      displayDrawIndicator(U8G_PSTR("U"), 0, 101);
      displayDrawIndicator(U8G_PSTR("2"), 1, 115);
      break;
    case ABNT2_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 68);
      displayDrawIndicator(U8G_PSTR("D"), 1, 82);
      displayDrawIndicator(U8G_PSTR("U"), 0, 101);
      displayDrawIndicator(U8G_PSTR("2"), 1, 115);
      break;
  }
}
