#ifndef DEFINES_H
#define DEFINES_H

#define DIO PORTB

#define IFC PORTC6
#define REN PORTC7

#define TE PORTE6

#define DAV PORTD0
#define ATN PORTD1
#define EOI PORTD4
#define SRQ PORTD5
#define NRFD PORTD6
#define NDAC PORTD7

#define GPIO1 PORTF0
#define GPIO2 PORTF1
#define GPIO3 PORTF4
#define GPIO4 PORTF5
#define GPIO5 PORTF6
#define DC PORTF7

#define USB
#define USE_STATIC_OPTIONS
#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define HIGH 0
#define LOW 1

/* AVR USART buffer size */
#define FIFO_SIZE 128

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#endif
