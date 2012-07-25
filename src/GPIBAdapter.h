#ifndef GPIBADAPTER_H
#define GPIBADAPTER_H

#include <avr/interrupt.h>
#include <stdio.h>
#include "lib/GPIB.h"
#include "lib/USART.h"
#include "Defines.h"
#ifdef USB
#include "conf/AppConfig.h"
#include "Descriptors.h"
#include "lib/LUFA/Drivers/USB/USB.h"
#endif

#ifdef USB
// Event functions for USB
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

// Interrupt handling function when DAV goes high (listener is trying to send data)
ISR(INT0_vect);

// Interrupt handling functions for the USART
ISR(USART1_TX_vect);
ISR(USART1_RX_vect);
#endif
