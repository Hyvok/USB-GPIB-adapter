#include "GPIBAdapter.h"

int main(void) {

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

	// Configure interrupt on falling edge of INT0 (DAV)
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);

	// Start and configure USART
	USART_Init();

#ifdef USB
	// Start USB
	USB_Init();
#endif

	// Interrupts enabled after configuration
	sei();
	while(1) {
#ifdef USB
		// Poll USB, TODO something about the data if received
		HID_Device_USBTask(&Generic_HID_Interface);
		USB_USBTask();
#endif
		// Poll SRQ
		if((PORTD & (1<<SRQ)) == HIGH) { serviceRequest(); }

		// Poll UART
		if(receiveFlag == true) { /* TODO: Do something about the data */ }
	}
}
ISR(USART1_TX_vect){ transmitInterrupt(); }
ISR(USART1_RX_vect){ receiveInterrupt(); }
ISR(INT0_vect) {

// TODO: something when DAV goes HIGH

}
