#include "LUFA.h"
#include "Keyboard.h"

extern FILE USBSerialStream;

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface = {
  .Config = {
    .InterfaceNumber              = 2,
    .ReportINEndpoint             = {
      .Address              = KEYBOARD_EPADDR,
      .Size                 = KEYBOARD_EPSIZE,
      .Banks                = 1,
      },
    .PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
    .PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
    },
  };

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface = {
   .Config = {
       .ControlInterfaceNumber   = 0,
       .DataINEndpoint           = {
           .Address          = CDC_TX_EPADDR,
           .Size             = CDC_TXRX_EPSIZE,
           .Banks            = 1,
         },
       .DataOUTEndpoint = {
           .Address          = CDC_RX_EPADDR,
           .Size             = CDC_TXRX_EPSIZE,
           .Banks            = 1,
         },
       .NotificationEndpoint = {
           .Address          = CDC_NOTIFICATION_EPADDR,
           .Size             = CDC_NOTIFICATION_EPSIZE,
           .Banks            = 1,
         },
     },
  };

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void){
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  /* Disable clock division */
  clock_prescale_set(clock_div_1);

  /* Hardware Initialization */
  LEDs_Init();
  USB_Init();
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void){
  CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
  HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
  USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void){
  CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
  HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void){
  HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize){
  USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

  keyboardScanAll(KeyboardReport);
/*
if(KeyboardReport->KeyCode[0]||
KeyboardReport->KeyCode[1]||
KeyboardReport->KeyCode[2]||
KeyboardReport->KeyCode[3]||
KeyboardReport->KeyCode[4]||
KeyboardReport->KeyCode[5]||
KeyboardReport->Modifier)
fprintf_P(&USBSerialStream, PSTR("%d / %d %d %d %d %d %d\r\n"),
KeyboardReport->Modifier,
(uint8_t)KeyboardReport->KeyCode[0],
(uint8_t)KeyboardReport->KeyCode[1],
(uint8_t)KeyboardReport->KeyCode[2],
(uint8_t)KeyboardReport->KeyCode[3],
(uint8_t)KeyboardReport->KeyCode[4],
(uint8_t)KeyboardReport->KeyCode[5]
);
*/
  *ReportSize = sizeof(USB_KeyboardReport_Data_t);
  return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize){
  uint8_t  LEDMask   = LEDS_NO_LEDS;
  uint8_t* LEDReport = (uint8_t*)ReportData;
//fprintf_P(&USBSerialStream, PSTR("LEDS=%d\r\n"), *LEDReport);
  if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
    LEDMask |= LEDS_LED1;

  if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
    LEDMask |= LEDS_LED3;

  if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
    LEDMask |= LEDS_LED4;

  LEDs_SetAllLEDs(LEDMask);
}
