#ifndef main_h
#define main_h

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

// Internal RC oscillator, 8MHz
#define F_CPU 8000000UL

#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

// Initialize USART, set baud rate to USART_BAUDRATE
void USART_Init(void);

// Send one byte to the USART, function waits for previous data to transmit
void USART_SendByte(uint8_t data);

// Receive one byte, function waits for data
uint8_t USART_ReceiveByte();

// Interrupt handling function when USART receives a byte
ISR(USART1_RX_vect);
#endif
