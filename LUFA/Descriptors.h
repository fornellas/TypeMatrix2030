#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

//
// Macros
//

// Keyboard

// Endpoint address of the Keyboard HID reporting IN endpoint.
#define KEYBOARD_EPADDR              (ENDPOINT_DIR_IN | 1)
// Size in bytes of the Keyboard HID reporting IN endpoint.
#define KEYBOARD_EPSIZE              8

// CDC

// Endpoint address of the CDC device-to-host notification IN endpoint.
#define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 2)
// Endpoint address of the CDC device-to-host data IN endpoint.
#define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 3)
// Endpoint address of the CDC host-to-device data OUT endpoint.
#define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)
// Size in bytes of the CDC device-to-host notification IN endpoint.
#define CDC_NOTIFICATION_EPSIZE        8
// Size in bytes of the CDC data IN and OUT endpoints.
#define CDC_TXRX_EPSIZE                16

/* Type Defines: */
/** Type define for the device configuration descriptor structure. This must be defined in the
  *  application code, as the configuration descriptor contains several sub-descriptors which
  *  vary between devices, and which describe the device's usage to the host.
  */
typedef struct{
  USB_Descriptor_Configuration_Header_t    Config;

  // Keyboard HID Interface
  USB_Descriptor_Interface_t HID_Interface;
  USB_HID_Descriptor_HID_t HID_KeyboardHID;
  USB_Descriptor_Endpoint_t HID_ReportINEndpoint;

  // CDC Control Interface
  USB_Descriptor_Interface_t               CDC_CCI_Interface;
  USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
  USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
  USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
  USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

  // CDC Data Interface
  USB_Descriptor_Interface_t               CDC_DCI_Interface;
  USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
  USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
} USB_Descriptor_Configuration_t;

/* Function Prototypes: */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

