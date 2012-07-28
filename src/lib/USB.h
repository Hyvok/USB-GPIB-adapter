#ifndef USB_H
#define USB_H
#include "Defines.h"
#include "conf/AppConfig.h"
#include "Descriptors.h"
#include "lib/LUFA/Drivers/USB/USB.h"

#ifdef USB
// Event functions for USB
USB_ClassInfo_HID_Device_t Generic_HID_Interface;
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(
											USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, 
											uint8_t* const ReportID, 
											const uint8_t ReportType, 
											void* ReportData, 
											uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(
											USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, 
											const uint8_t ReportID, 
											const uint8_t ReportType, 
											const void* ReportData, 
											const uint16_t ReportSize);
#endif
#endif
