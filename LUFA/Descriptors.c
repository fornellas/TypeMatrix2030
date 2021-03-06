#include "Descriptors.h"

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] = {
  /* Use the HID class driver's standard Keyboard report.
   *   Max simultaneous keys: 6
   */
  HID_DESCRIPTOR_KEYBOARD (6)
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = {
  .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
  .USBSpecification       = VERSION_BCD(1,1,0),
  .Class                  = USB_CSCP_NoDeviceClass,
  .SubClass               = USB_CSCP_NoDeviceSubclass,
  .Protocol               = USB_CSCP_NoDeviceProtocol,
  .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
  .VendorID               = 0x03EB, // Atmel
  .ProductID              = 0x2042, // Keyboard Demo Application
  .ReleaseNumber          = VERSION_BCD(0,0,1),
  .ManufacturerStrIndex   = 0x01,
  .ProductStrIndex        = 0x02,
  .SerialNumStrIndex      = USE_INTERNAL_SERIAL,
  .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = {
  .Config = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},
    .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
#ifdef SERIAL_DEBUG
    .TotalInterfaces        = 3,
#else
    .TotalInterfaces        = 1,
#endif
    .ConfigurationNumber    = 1,
    .ConfigurationStrIndex  = NO_DESCRIPTOR,
    .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_REMOTEWAKEUP),
    .MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
    },
#ifdef SERIAL_DEBUG
  // CDC
  .CDC_CCI_Interface = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
    .InterfaceNumber        = 0,
    .AlternateSetting       = 0,
    .TotalEndpoints         = 1,
    .Class                  = CDC_CSCP_CDCClass,
    .SubClass               = CDC_CSCP_ACMSubclass,
    .Protocol               = CDC_CSCP_ATCommandProtocol,
    .InterfaceStrIndex      = NO_DESCRIPTOR
    },
  .CDC_Functional_Header = {
    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = DTYPE_CSInterface},
    .Subtype                = CDC_DSUBTYPE_CSInterface_Header,
    .CDCSpecification       = VERSION_BCD(1,1,0),
    },
  .CDC_Functional_ACM = {
    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = DTYPE_CSInterface},
    .Subtype                = CDC_DSUBTYPE_CSInterface_ACM,
    .Capabilities           = 0x06,
    },
  .CDC_Functional_Union = {
    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = DTYPE_CSInterface},
    .Subtype                = CDC_DSUBTYPE_CSInterface_Union,
    .MasterInterfaceNumber  = 0,
    .SlaveInterfaceNumber   = 1,
    },
  .CDC_NotificationEndpoint = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
    .EndpointAddress        = CDC_NOTIFICATION_EPADDR,
    .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
    .EndpointSize           = CDC_NOTIFICATION_EPSIZE,
    .PollingIntervalMS      = 0xFF
    },
  .CDC_DCI_Interface = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
    .InterfaceNumber        = 1,
    .AlternateSetting       = 0,
    .TotalEndpoints         = 2,
    .Class                  = CDC_CSCP_CDCDataClass,
    .SubClass               = CDC_CSCP_NoDataSubclass,
    .Protocol               = CDC_CSCP_NoDataProtocol,
    .InterfaceStrIndex      = NO_DESCRIPTOR
    },
  .CDC_DataOutEndpoint = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
    .EndpointAddress        = CDC_RX_EPADDR,
    .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
    .EndpointSize           = CDC_TXRX_EPSIZE,
    .PollingIntervalMS      = 0x05
    },
  .CDC_DataInEndpoint = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
    .EndpointAddress        = CDC_TX_EPADDR,
    .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
    .EndpointSize           = CDC_TXRX_EPSIZE,
    .PollingIntervalMS      = 0x05
    },
#endif
  // Keyboard
  .HID_Interface = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
#ifdef SERIAL_DEBUG
    .InterfaceNumber        = 2,
#else
    .InterfaceNumber        = 0,
#endif
    .AlternateSetting       = 0x00,
    .TotalEndpoints         = 1,
    .Class                  = HID_CSCP_HIDClass,
    .SubClass               = HID_CSCP_BootSubclass,
    .Protocol               = HID_CSCP_KeyboardBootProtocol,
    .InterfaceStrIndex      = NO_DESCRIPTOR
    },
  .HID_KeyboardHID = {
    .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
    .HIDSpec                = VERSION_BCD(1,1,1),
    .CountryCode            = 0x00,
    .TotalReportDescriptors = 1,
    .HIDReportType          = HID_DTYPE_Report,
    .HIDReportLength        = sizeof(KeyboardReport)
    },
  .HID_ReportINEndpoint = {
    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
    .EndpointAddress        = KEYBOARD_EPADDR,
    .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
    .EndpointSize           = KEYBOARD_EPSIZE,
    .PollingIntervalMS      = 0x05
    },
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString = {
  .Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
  .UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString = {
  .Header                 = {.Size = USB_STRING_LEN(20), .Type = DTYPE_String},
  .UnicodeString          = L"TypeMatrix (Hacked!)"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString = {
  .Header                 = {.Size = USB_STRING_LEN(27), .Type = DTYPE_String},
  .UnicodeString          = L"2030 USB Keyboard (Hacked!)"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress) {
  const uint8_t  DescriptorType   = (wValue >> 8);
  const uint8_t  DescriptorNumber = (wValue & 0xFF);

  const void* Address = NULL;
  uint16_t    Size    = NO_DESCRIPTOR;

  switch (DescriptorType) {
    case DTYPE_Device:
      Address = &DeviceDescriptor;
      Size    = sizeof(USB_Descriptor_Device_t);
      break;
    case DTYPE_Configuration:
      Address = &ConfigurationDescriptor;
      Size    = sizeof(USB_Descriptor_Configuration_t);
      break;
    case DTYPE_String:
      switch (DescriptorNumber) {
        case 0x00:
          Address = &LanguageString;
          Size    = pgm_read_byte(&LanguageString.Header.Size);
          break;
        case 0x01:
          Address = &ManufacturerString;
          Size    = pgm_read_byte(&ManufacturerString.Header.Size);
          break;
        case 0x02:
          Address = &ProductString;
          Size    = pgm_read_byte(&ProductString.Header.Size);
          break;
      }
      break;
    case HID_DTYPE_HID:
      Address = &ConfigurationDescriptor.HID_KeyboardHID;
      Size    = sizeof(USB_HID_Descriptor_HID_t);
      break;
    case HID_DTYPE_Report:
      Address = &KeyboardReport;
      Size    = sizeof(KeyboardReport);
      break;
  }

  *DescriptorAddress = Address;
  return Size;
}

