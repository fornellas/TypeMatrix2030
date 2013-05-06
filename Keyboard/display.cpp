#include "Keyboard.h"

#include <LUFA/Drivers/Peripheral/SPI.h>
#include <stdlib.h>

#include "binary.h"

#define U8G_CS PN(5,5)		// PF5
#define U8G_A0 PN(5,7)		// PF7
#define U8G_RESET PN(5,6)	// PF6
#define U8G_SCK PN(1,1)
#define U8G_MOSI PN(1,2)

#define TOGGLE_BORDER 2
#define TOGGLE_SPACING 2

#define ICON_WIDTH 2 // bytes
#define ICON_HEIGHT 13 // pixels

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
  if(displayUpdating)
    displayUpdateAgain=true;
  else
    displayUpdating=1;
}

void Keyboard::displayUpdate(){
  uint8_t offset, y;
  u8g_pgm_uint8_t *str;
  char strBuff[11];
  if(displayUpdating==0)
    return;
  // first iteration, save vars for processing
  if(displayUpdating++==1){
    u8g_FirstPage(&u8g);
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
      u8g_SetFont(&u8g, u8g_font_fur17);
      // LEDs
      if(display_var_LEDReport!=NO_LED_REPORT){
        offset=0;
        offset+=TOGGLE_SPACING+displayDrawToggle(LEDReport & HID_KEYBOARD_LED_NUMLOCK, 0, 0, U8G_PSTR("1"));
        offset+=TOGGLE_SPACING+displayDrawToggle(LEDReport & HID_KEYBOARD_LED_CAPSLOCK, offset, 0, U8G_PSTR("A"));
        displayDrawToggle(LEDReport & HID_KEYBOARD_LED_SCROLLLOCK, offset, 0, U8G_PSTR("S"));
      }
      if(NULL!=display_var_KeyboardReport) {
        // Keypad
        str=U8G_PSTR("K");
        offset=u8g_GetWidth(&u8g)-displayGetToggleWidth(str);
        displayDrawToggle(keypad, offset, 0, str);
        // Fn
        str=U8G_PSTR("Fn");
        offset-=TOGGLE_SPACING+displayGetToggleWidth(str);
        displayDrawToggle(fn, offset, 0, str);
        // Layout
        y=displayGetToggleHeight()+3;
        u8g_SetFont(&u8g, u8g_font_6x10);
        switch(layout){
          case US_US:
            displayDrawKeyboardLayout(y, true, false, true, false, false);
            break;
          case US_DVORAK:
            displayDrawKeyboardLayout(y, false, true, true, false, false);
            break;
          case ABNT2_US:
            displayDrawKeyboardLayout(y, true, false, false, false, true);
            break;
          case ABNT2_DVORAK:
            displayDrawKeyboardLayout(y, false, true, false, false, true);
            break;
          case DVORAK_DVORAK:
            displayDrawKeyboardLayout(y, false, true, false, true, false);
            break;
        }
      }
      // Key counter
      // FIXME
      u8g_SetFontPosTop(&u8g);
      ultoa(keyPresses, strBuff, 10);
      u8g_DrawStr(&u8g, u8g_GetWidth(&u8g)/2-u8g_GetStrWidth(&u8g, strBuff)/2, 56, strBuff);
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
      if(display_var_USB_Device_RemoteWakeupEnabled)
        displayDrawStrCenter(0, 0, U8G_PSTR("Suspended:"), U8G_PSTR("Press Any Key"), U8G_PSTR("To Wake Up"), NULL);
      else
        displayDrawStrCenter(0, 0, U8G_PSTR("Suspended"), NULL);
      break;
  }
  // last iteration
  if(!u8g_NextPage(&u8g)){
    // force new display update if required
    if(displayUpdateAgain)
      displayUpdating=1;
    else
      displayUpdating=0;
    displayUpdateAgain=false;
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

uint8_t Keyboard::displayGetToggleWidth(u8g_pgm_uint8_t *str){
  return u8g_GetStrWidthP(&u8g, str)+2+TOGGLE_BORDER*2;
}

uint8_t Keyboard::displayGetToggleHeight(){
  return u8g_GetFontAscent(&u8g)+2+TOGGLE_BORDER*2;
}

uint8_t Keyboard::displayDrawToggle(bool state, uint8_t x, uint8_t y, u8g_pgm_uint8_t *str){
  uint8_t width=displayGetToggleWidth(str);
  u8g_SetFontRefHeightText(&u8g);
  uint8_t height=displayGetToggleHeight();
  u8g_SetColorIndex(&u8g, 1);
  if(state){
    u8g_DrawBox(&u8g, x, y, width, height);
    u8g_SetColorIndex(&u8g, 0);
  }else{
    u8g_DrawFrame(&u8g, x, y, width, height);
  }
  u8g_SetFontPosTop(&u8g);
  u8g_DrawStrP(&u8g, x+1+TOGGLE_BORDER, y+TOGGLE_BORDER, str);
  u8g_SetColorIndex(&u8g, 1);
  return width;
}

void Keyboard::displayDrawKeyboardLayout(uint8_t y, bool kb_us, bool kb_dvorak, bool host_us, bool host_dvorak, bool host_abnt2){
  uint8_t offset;
  u8g_pgm_uint8_t *us=U8G_PSTR("US");
  u8g_pgm_uint8_t *dvorak=U8G_PSTR("Dvorak");
  u8g_pgm_uint8_t *abnt2=U8G_PSTR("ABNT2");
  // keyoard layout
  offset=(u8g_GetWidth(&u8g)-(ICON_WIDTH*8+2+displayGetToggleWidth(us)+displayGetToggleWidth(dvorak)-1))/2; // center
  u8g_DrawBitmapP(&u8g, offset, y, ICON_WIDTH, ICON_HEIGHT, icon_keyboard);
  offset+=ICON_WIDTH*8+2;
  offset+=-1+displayDrawToggle(kb_us, offset, y, us);
  displayDrawToggle(kb_dvorak, offset, y, dvorak);
  // host layout
  offset=(u8g_GetWidth(&u8g)-(ICON_WIDTH*8+2+displayGetToggleWidth(us)+displayGetToggleWidth(dvorak)+displayGetToggleWidth(abnt2)-1))/2; // center
  y+=ICON_HEIGHT+2;
  u8g_DrawBitmapP(&u8g, offset, y, ICON_WIDTH, ICON_HEIGHT, icon_computer);
  offset+=ICON_WIDTH*8+2;
  offset+=-1+displayDrawToggle(host_us, offset, y, us);
  offset+=-1+displayDrawToggle(host_dvorak, offset, y, dvorak);
  offset+=-1+displayDrawToggle(host_abnt2, offset, y, abnt2);
}

void Keyboard::setLEDs(uint8_t report){
  LEDReport=report;
  displayForceUpdate();
}
