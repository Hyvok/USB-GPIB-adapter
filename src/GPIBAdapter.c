#include "GPIBAdapter.h"

volatile uint8_t USART_ReceivedByte;

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevHIDReportBuffer[GENERIC_REPORT_SIZE];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Generic_HID_Interface = {
	.Config =
		{
			.InterfaceNumber              = 0,
			.ReportINEndpoint             = {
					.Address              = GENERIC_IN_EPADDR,
					.Size                 = GENERIC_EPSIZE,
					.Banks                = 1,
			},
			.PrevReportINBuffer           = PrevHIDReportBuffer,
			.PrevReportINBufferSize       = sizeof(PrevHIDReportBuffer),
		},
};

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void) {
	// Do something here when USB is connected
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void) {
	// Do something here when USB is disconnected
}
/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Generic_HID_Interface);

	USB_Device_EnableSOFEvents();

	// Do something here when USB configuration changed
}
/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void) {
	HID_Device_ProcessControlRequest(&Generic_HID_Interface);
}
/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void) {
	HID_Device_MillisecondElapsed(&Generic_HID_Interface);
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
                                         uint16_t* const ReportSize)
{
	uint8_t* Data = (uint8_t*)ReportData;
	/* Example code:
	uint8_t  CurrLEDMask = LEDs_GetLEDs();

	Data[0] = ((CurrLEDMask & LEDS_LED1) ? 1 : 0);
	Data[1] = ((CurrLEDMask & LEDS_LED2) ? 1 : 0);
	Data[2] = ((CurrLEDMask & LEDS_LED3) ? 1 : 0);
	Data[3] = ((CurrLEDMask & LEDS_LED4) ? 1 : 0);
	*/
	*ReportSize = GENERIC_REPORT_SIZE;
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
                                          const uint16_t ReportSize) {
	uint8_t* Data = (uint8_t*)ReportData;
	/* Example code:
	uint8_t  NewLEDMask = LEDS_NO_LEDS;

	if (Data[0])
	  NewLEDMask |= LEDS_LED1;

	if (Data[1])
	  NewLEDMask |= LEDS_LED1;

	if (Data[2])
	  NewLEDMask |= LEDS_LED1;

	if (Data[3])
	  NewLEDMask |= LEDS_LED1;

	LEDs_SetAllLEDs(NewLEDMask);
	*/
}
void USART_Init(void) {

	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
	UBRR1L = BAUD_PRESCALE; 

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR1C = (0<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10);

	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
}
void USART_SendByte(uint8_t data) {

	// Wait if a byte is being transmitted, after finished transmit new data
	while((UCSR1A&(1<<UDRIE1)) == 0);
	UDR1 = data;
}
uint8_t USART_ReceiveByte() {

	// Wait until a byte has been received
	while((UCSR1A&(1<<RXC1)) == 0);
	return UDR1;
}
int main() {

	// Interrupts disabled at boot
	cli();

	/* Set PortB as inputs, 
	 * PortC as outputs, 
	 * PortD 0, 1, 3, 4 (DAV, ATN, TXD, EOI) as outputs and 2, 5-7 (RXD, SRQ, NRFD, NDAC) as inputs, 
	 * PortE 6 (TE) as output, 
	 * PortF 0, 1, 4, 5,6 (GPIO) as inputs with pull-ups and 7 (DC) as output
	*/
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0x1B;
	DDRE = 0x40;
	DDRF = 0x80;
	PORTF = 0x73;

	// Start and configure USART
	USART_Init();

	// Start USB
	USB_Init();

	// Interrupts enabled after configuration
	sei();
	while(1) {
		// Keep checking USB
		HID_Device_USBTask(&Generic_HID_Interface);
		USB_USBTask();
	}
}
ISR(USART1_RX_vect) {
 
	// Fetch the received byte value into the global variable "USART_ReceivedByte"
	USART_ReceivedByte = UDR1;
}
