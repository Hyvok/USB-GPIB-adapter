#ifndef GPIBADAPTER_H
#define GPIBADAPTER_H

#define DIO PORTB

#define IFC PORTC6
#define REN PORTC7

#define DAV PORTD0
#define ATN PORTD1
#define EOI PORTD4
#define SRQ PORTD5
#define NRFD PORTD6
#define NDAC PORTD7

#define TE PORTE6

#define GPIO1 PORTF0
#define GPIO2 PORTF1
#define GPIO3 PORTF4
#define GPIO4 PORTF5
#define GPIO5 PORTF6
#define DC PORTF7

#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "./lib/GPIB.h"
#include "Config/AppConfig.h"
#include "Descriptors.h"
#include "./lib/LUFA/Drivers/USB/USB.h"

// Event functions for USB
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize);

// Initialize USART, set baud rate to USART_BAUDRATE
void USART_Init(void);

// Send one byte to the USART, function waits for previous data to transmit
void USART_SendByte(uint8_t data);

// Receive one byte, function waits for data
uint8_t USART_ReceiveByte();

// Interrupt handling function when USART receives a byte
ISR(USART1_RX_vect);
#endif
