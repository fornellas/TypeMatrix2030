extern "C" {
#include "LUFA/LUFA.h"
}
#include "Keyboard/Keyboard.h"

#include <stdlib.h>

void * operator new(size_t size){
  return malloc(size); 
} 

void operator delete(void * ptr){
  free(ptr); 
} 

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Peripheral/TWI.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs
 */
extern "C"{
FILE USBSerialStream;
}
Keyboard *kbd;

int main(void){
  SetupHardware();
  /* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
  CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

  kbd=new Keyboard(&USBSerialStream);

  GlobalInterruptEnable();

  for (;;){
    /* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
    CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
    CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
    // Keyboard
    kbd->clearDisplay();
    HID_Device_USBTask(&Keyboard_HID_Interface);

    USB_USBTask();
  }
}
