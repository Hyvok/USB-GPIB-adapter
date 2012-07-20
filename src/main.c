#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "main.h"
#include <util/delay.h>
#include "./lib/lib_gpib.h"

volatile uint8_t USART_ReceivedByte;

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

	/* Start and configure USART
	*/
	USART_Init();

	// Interrupts enabled after configuration
	sei();
	while(1) {


	}
}
ISR(USART1_RX_vect) {
 
	// Fetch the received byte value into the variable "USART_ReceivedByte"
	USART_ReceivedByte = UDR1;
}
