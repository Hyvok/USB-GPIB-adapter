#ifndef USART_H
#define USART_H

#include "Defines.h"

/* This flag is true if new data has been received. */
extern volatile bool receiveFlag;

/* This flag is true if the RX buffer is full. */
extern volatile bool receiveBufferFull;

/* This flag is true if the TX buffer is full. */
extern volatile bool transmitBufferFull;

/* Initialize USART, set baud rate to USART_BAUDRATE */
void USART_Init(void);

/* Receive one byte, function waits for data */
unsigned char USART_ReceiveByte(void);

/* Receive a string from the USART to 'array' of size 'length', 
 functions waits for data */
void USART_ReceiveString(char* array, int length);

/* Send one byte to the USART, function waits for previous data to transmit */
void USART_SendByte(unsigned char c);

/* Send a string to the USART */
void USART_SendString(char *str);

/* These functions need to be called from the interrupt handling functions */
void transmitInterrupt(void);
void receiveInterrupt(void);
#endif
