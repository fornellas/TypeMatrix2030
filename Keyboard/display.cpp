#include "Keyboard.h"

#include <LUFA/Drivers/Peripheral/SPI.h>

#include "binary.h"

#define U8G_CS PN(5,5)		// PF5
#define U8G_A0 PN(5,7)		// PF7
#define U8G_RESET PN(5,6)	// PF6
#define U8G_SCK PN(1,1)
#define U8G_MOSI PN(1,2)

#define BORDER 2

const uint8_t icon_computer[] U8G_PROGMEM = {
  B1111111, B11111111,
  B1000000, B00000001,
  B1011111, B11111001,
  B1000000, B00000001,
  B1011111, B11000001,
  B1000000, B00000001,
  B1011111, B11111101,
  B1000000, B00000001,
  B1111111, B11111111,
  B0000001, B10000000,
  B0000001, B10000000,
  B0000011, B11000000,
  B0001111, B11110000
};

const uint8_t icon_keyboard[] U8G_PROGMEM = {
  B0000000, B00001000,
  B0000000, B00001000,
  B0000000, B00001000,
  B0000000, B11110000,
  B0000001, B00000000,
  B0000001, B00000000,
  B1111111, B11111111,
  B1000000, B00000001,
  B1010101, B01010101,
  B1000000, B00000001,
  B1010101, B01010101,
  B1000000, B00000001,
  B1111111, B11111111
};

void Keyboard::displayInit(){
//  SPI_Init(SPI_SPEED_FCPU_DIV_2|SPI_SCK_LEAD_RISING|SPI_SAMPLE_LEADING|SPI_ORDER_MSB_FIRST|SPI_MODE_MASTER);
  u8g_InitSPI(&u8g, &u8g_dev_ssd1306_128x64_sw_spi, U8G_SCK, U8G_MOSI, U8G_CS, U8G_A0, U8G_RESET);
//  u8g_InitHWSPI(&u8g, &u8g_dev_ssd1306_128x64_hw_spi, U8G_CS, U8G_A0, U8G_RESET);
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
    // Internally implemented by the library. This state indicates that the device is not currently connected to a host.
    case DEVICE_STATE_Unattached:
      u8g_SetFont(&u8g, u8g_font_helvB12);
      displayDrawStrCenter(0, 0, U8G_PSTR("Disconnected"), U8G_PSTR("From"), U8G_PSTR("USB Host"), NULL);
      break;
    // Internally implemented by the library. This state indicates that the device is connected to a host, but enumeration has not yet begun.
    case DEVICE_STATE_Powered:
      u8g_SetFont(&u8g, u8g_font_helvB12);
      displayDrawStrCenter(0, 0, U8G_PSTR("Connected"), U8G_PSTR("To USB Host:"), U8G_PSTR("Not Enumerated"), NULL);
      break;
    // Internally implemented by the library. This state indicates that the device's USB bus has been reset by the host and it is now waiting for the host to begin the enumeration process.
    case DEVICE_STATE_Default:
      u8g_SetFont(&u8g, u8g_font_helvB12);
      displayDrawStrCenter(0, 0, U8G_PSTR("Resetted By"), U8G_PSTR("USB Host:"), U8G_PSTR("Not Enumerated"), NULL);
      break;
    // Internally implemented by the library. This state indicates that the device has been addressed by the USB Host, but is not yet configured.
    case DEVICE_STATE_Addressed:
      u8g_SetFont(&u8g, u8g_font_helvB12);
      displayDrawStrCenter(0, 0, U8G_PSTR("Addressed By"), U8G_PSTR("USB Host:"), U8G_PSTR("Not Configured"), NULL);
      break;
    // May be implemented by the user project. This state indicates that the device has been enumerated by the host and is ready for USB communications to begin.
    case DEVICE_STATE_Configured:
      uint8_t offset;
      // LEDs
      u8g_SetFont(&u8g, u8g_font_fur17);
      offset=0;
      if(display_var_LEDReport!=NO_LED_REPORT){
        if(LEDReport & HID_KEYBOARD_LED_NUMLOCK)
          offset+=displayDrawToggle(true, 0, 0, U8G_PSTR("1"));
        else
          offset+=displayDrawToggle(false, 0, 0, U8G_PSTR("1"));
        if(LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
          offset+=displayDrawToggle(true, offset+=BORDER, 0, U8G_PSTR("A"));
        else
          offset+=displayDrawToggle(false, offset+=BORDER, 0, U8G_PSTR("A"));
        if(LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
          offset+=displayDrawToggle(true, offset+=BORDER, 0, U8G_PSTR("S"));
        else
          offset+=displayDrawToggle(false, offset+=BORDER, 0, U8G_PSTR("S"));
      }
      // Keypad
      if(NULL!=display_var_KeyboardReport) {
        if(keypad)
          displayDrawToggle(true, 107, 0, U8G_PSTR("K"));
        else
          displayDrawToggle(false, 107, 0, U8G_PSTR("K"));
        // Layout
        int y;
        y=u8g_GetFontAscent(&u8g)+2+BORDER*2;
        offset=13+BORDER;
        u8g_SetFont(&u8g, u8g_font_6x10);
        switch(layout){
          case US_US:
            break;
          case US_DVORAK:
            ++y;
            offset=16+BORDER*2;
            u8g_DrawBitmapP(&u8g, 0, y+BORDER, 2, 13, icon_keyboard);
            offset+=displayDrawToggle(false, offset, y+BORDER, U8G_PSTR("US"));
            displayDrawToggle(true, --offset, y+BORDER, U8G_PSTR("Dvorak"));
            y+=u8g_GetFontAscent(&u8g)+2+BORDER*2+4;
            u8g_DrawBitmapP(&u8g, 0, y, 2, 13, icon_computer);
            offset=16+BORDER*2;
            offset+=displayDrawToggle(true, offset, y, U8G_PSTR("US"));
            offset+=displayDrawToggle(false, --offset, y, U8G_PSTR("Dvorak"));
            offset+=displayDrawToggle(false, --offset, y, U8G_PSTR("ABNT2"));
            break;
          case ABNT2_US:
            break;
          case ABNT2_DVORAK:
            break;
          case DVORAK_DVORAK:
            break;
        }
      }
      // Key counter
      // FIXME
      u8g_SetFontPosTop(&u8g);
      u8g_DrawStrP(&u8g, 60, 56, U8G_PSTR("1341"));
/*
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
*/
      break;
    // May be implemented by the user project. This state indicates that the USB bus has been suspended by the host, and the device should power down to a minimal power level until the bus is resumed.
    case DEVICE_STATE_Suspended:
      u8g_SetFont(&u8g, u8g_font_helvB12);
      displayDrawStrCenter(0, 0, U8G_PSTR("Suspended"), U8G_PSTR("By"), U8G_PSTR("USB Host"), NULL);
/*
      u8g_SetFont(&u8g, u8g_font_helvB12);
      if(display_var_USB_Device_RemoteWakeupEnabled){
        displayDrawStrCenter(U8G_PSTR("Press any key"), 0, u8g_GetFontLineSpacing(&u8g)/2*-1-1);
        displayDrawStrCenter(U8G_PSTR("to wake up"), 0, u8g_GetFontLineSpacing(&u8g)/2+1);
      }else{
        displayDrawStrCenter(U8G_PSTR("Suspended"), 0, 0);
      }
*/
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

void Keyboard::displayDrawStrCenter(int8_t x_offset, int8_t y_offset, ...){
  va_list ap, apl;
  uint8_t lines;
  u8g_pgm_uint8_t *str;
  va_start(ap, y_offset);
  // count lines
  va_copy(apl, ap);
  lines=0;
  while(va_arg(apl, u8g_pgm_uint8_t *)!=NULL)
    lines++;
  va_end(apl);
  // print lines
  int l=0;
  while((str=va_arg(ap, u8g_pgm_uint8_t *))!=NULL){
    int8_t x=u8g_GetWidth(&u8g)/2-u8g_GetStrWidthP(&u8g, str)/2+x_offset;
    u8g_SetFontRefHeightText(&u8g);
    int8_t y=u8g_GetHeight(&u8g)/2+u8g_GetFontAscent(&u8g)/2+y_offset;
    u8g_SetFontRefHeightAll(&u8g);
    int8_t font_height=(u8g_GetFontLineSpacing(&u8g));
    int8_t line_y_offset=-font_height/2*(lines-1);
    u8g_DrawStrP(&u8g, x, y+line_y_offset+font_height*l+2*l, str);
    l++;
  }
  va_end(ap);
}

uint8_t Keyboard::displayDrawToggle(bool state, uint8_t x, uint8_t y, u8g_pgm_uint8_t *str, ...){
  uint8_t width=u8g_GetStrWidthP(&u8g, str)+2+BORDER*2;
  u8g_SetFontRefHeightText(&u8g);
  uint8_t height=u8g_GetFontAscent(&u8g)+2+BORDER*2;
  u8g_SetColorIndex(&u8g, 1);
  if(state){
    u8g_DrawBox(&u8g, x, y, width, height);
    u8g_SetColorIndex(&u8g, 0);
  }else{
    u8g_DrawFrame(&u8g, x, y, width, height);
  }
  u8g_SetFontPosTop(&u8g);
  u8g_DrawStrP(&u8g, x+1+BORDER, y+BORDER, str);
  u8g_SetColorIndex(&u8g, 1);
  return width;
}

void Keyboard::setLEDs(uint8_t report){
  LEDReport=report;
  displayForceUpdate();
}


/*
void Keyboard::displayDrawIndicator(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x){
  u8g_SetColorIndex(&u8g, 1);
  if(on){
    u8g_DrawBox(&u8g, x, 0, 13, 16);
    u8g_SetColorIndex(&u8g, 0);
  }else{
    u8g_DrawFrame(&u8g, x, 0, 13, 16);
  }
  u8g_DrawStrP(&u8g, x+4, 11, str);
}

void Keyboard::displayDrawIndicator2(u8g_pgm_uint8_t *str, uint8_t on, uint8_t x){
  u8g_SetColorIndex(&u8g, 1);
  if(on){
    u8g_DrawBox(&u8g, x, 0, 27, 16);
    u8g_SetColorIndex(&u8g, 0);
  }else{
    u8g_DrawFrame(&u8g, x, 0, 27, 16);
  }
  u8g_DrawStrP(&u8g, x+6, 11, str);
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

void Keyboard::displayDrawLayoutStates(){
  // Keypad
  if(keypad)
    displayDrawIndicator(U8G_PSTR("K"), 1, 43);
  else
    displayDrawIndicator(U8G_PSTR("K"), 0, 43);
  // Layout
  switch(layout){
    case US_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 58);
      displayDrawIndicator(U8G_PSTR("D"), 0, 72);
      displayDrawIndicator(U8G_PSTR("U"), 1, 87);
      displayDrawIndicator(U8G_PSTR("A"), 0, 101);
      displayDrawIndicator(U8G_PSTR("D"), 0, 115);
      break;
    case US_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 58);
      displayDrawIndicator(U8G_PSTR("D"), 1, 72);
      displayDrawIndicator(U8G_PSTR("U"), 1, 87);
      displayDrawIndicator(U8G_PSTR("A"), 0, 101);
      displayDrawIndicator(U8G_PSTR("D"), 0, 115);
      break;
    case ABNT2_US:
      displayDrawIndicator(U8G_PSTR("U"), 1, 58);
      displayDrawIndicator(U8G_PSTR("D"), 0, 72);
      displayDrawIndicator(U8G_PSTR("U"), 0, 87);
      displayDrawIndicator(U8G_PSTR("A"), 1, 101);
      displayDrawIndicator(U8G_PSTR("D"), 0, 115);
      break;
    case ABNT2_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 58);
      displayDrawIndicator(U8G_PSTR("D"), 1, 72);
      displayDrawIndicator(U8G_PSTR("U"), 0, 87);
      displayDrawIndicator(U8G_PSTR("A"), 1, 101);
      displayDrawIndicator(U8G_PSTR("D"), 0, 115);
      break;
    case DVORAK_DVORAK:
      displayDrawIndicator(U8G_PSTR("U"), 0, 58);
      displayDrawIndicator(U8G_PSTR("D"), 1, 72);
      displayDrawIndicator(U8G_PSTR("U"), 0, 87);
      displayDrawIndicator(U8G_PSTR("A"), 0, 101);
      displayDrawIndicator(U8G_PSTR("D"), 1, 115);
      break;
  }
}

*/
