#ifndef GPIBADAPTER_H
#define GPIBADAPTER_H

#include <avr/interrupt.h>
#include <stdio.h>
#include "lib/GPIB.h"
#include "lib/USART.h"
#include "Defines.h"
#ifdef USB
#include "lib/USB.h"
#endif

// Interrupt handling function when DAV goes high (listener is trying to send data)
ISR(INT0_vect);

// Interrupt handling functions for the USART
ISR(USART1_TX_vect);
ISR(USART1_RX_vect);
#endif
