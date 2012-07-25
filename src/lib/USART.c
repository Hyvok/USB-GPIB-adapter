#include "USART.h"

// This char is the most current char to go into the UART
volatile unsigned char transmittedByte;
// This char is the most current char to come out of the UARTBuffer
volatile unsigned char receivedByte;

volatile bool receiveFlag;

volatile unsigned char transmitBuffer[FIFO_SIZE];
volatile unsigned char receiveBuffer[FIFO_SIZE];

// These pointers keep track where the USART and the program are in the FIFOs
volatile unsigned int transmitBufferPtrA;
volatile unsigned int transmitBufferPtrB;
volatile unsigned int receiveBufferPtrA;
volatile unsigned int receiveBufferPtrB;

volatile bool receiveBufferFull;
volatile bool transmitBufferFull;

void USART_Init() {

	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR1H = (BAUD_PRESCALE >> 8);
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
	UBRR1L = BAUD_PRESCALE; 

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR1C = (0<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10);

	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);

	receiveFlag = false;

	transmitBufferPtrA = 0;
	transmitBufferPtrB = 0;
	receiveBufferPtrA = 0;
	receiveBufferPtrB = 0;

	transmitBufferFull = false;
	receiveBufferFull = false;

}
unsigned char USART_ReceiveByte() {

	unsigned char byte;

	// Wait for receiveFlag to be set
	while (receiveFlag == false);

	// Copy the char from the buffer
	byte = receiveBuffer[receiveBufferPtrA];
	// Increase the buffer pointer		
	receiveBufferPtrA++;

	// If pointer is equal to the max size roll it over
	if(receiveBufferPtrA == FIFO_SIZE) { receiveBufferPtrA = 0; }

	//if the pointers are the same we have no new data
	if(receiveBufferPtrA == receiveBufferPtrB) { receiveFlag = false; }
    return byte;

}
void USART_ReceiveString(char* array, int length) {

	unsigned int i = 0;

	// Wait for the buffer to fill
	while((i < length)) {
		array[i] = USART_ReceiveByte();
		// If we receive a newline, stop reading
		if(array[i] == '\n') {
			//fill the rest of the string with \0 nul. Overwrites the \n with \0
			for( ; i < length ; i++) {
				array[i] = '\0';
			}
			break;
		}
		i++;
	}

    return;
}

void USART_SendByte(unsigned char c) {

	transmittedByte = c;
	transmitBuffer[transmitBufferPtrA] = transmittedByte;
	transmitBufferPtrA++;

	// Check to see if the pointer is max size. If so roll it over
	if(transmitBufferPtrA == FIFO_SIZE) { transmitBufferPtrA = 0; }
	// Check if the transmit buffer is full
	if(transmitBufferPtrB == transmitBufferPtrA) { transmitBufferFull = true; }
	else{ transmitBufferFull = false; }
	// Enable TX interrupt
	UCSR1B |= (1<<TXCIE1);
	return;
}

void USART_SendString(char *str) {

     while(*str) USART_SendByte(*str++);
     return;
}
void transmitInterrupt(){

	// Copy the current byte into the TX buffer
	UDR1 = transmitBuffer[transmitBufferPtrB];
	transmitBufferPtrB++;

	// If pointer is equal to the max size roll it over
	if(transmitBufferPtrB == FIFO_SIZE) { transmitBufferPtrB = 0; }
	// If the pointers are the same, no new data to transmit
	// Turn off the interrupt to save CPU
    if(transmitBufferPtrB == transmitBufferPtrA) { 	UCSR1B &= ~(1<<TXCIE1); }
}
void receiveInterrupt(){

	// Copy byte from RX buffer, in doing so we ACK the interrupt as well
	receivedByte = UDR1;
	// Set the receiveFlag to true
	receiveFlag = true;

	// Copy the receivedByte into the buffer
	receiveBuffer[receiveBufferPtrB] = receivedByte;
	receiveBufferPtrB++;

	// Check to see if the pointer is max size. If so roll it over
	if(receiveBufferPtrB == FIFO_SIZE) { receiveBufferPtrB = 0; }
	// Check if the buffer is full
	if(receiveBufferPtrB == receiveBufferPtrA) { receiveBufferFull = true; }
	else { receiveBufferFull = false; }
}
