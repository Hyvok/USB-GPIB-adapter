#ifndef GPIB_H
#define GPIB_H

#include "Defines.h"

/* Initialize GPIB bus, become controller-in-charge */
void GPIB_Init(void);

/* Function reads if the listener is ready for data */
bool readNRFD(void);

/* Functions reads if the listener is ready to accept data */
bool readNDAC(void);

/* Write a char to the bus, listener is ready for data when NRFD = LOW,
listener has accepted data when NDAC == HIGH */
void writeChar(char data);

/* Read a char from the bus */
uint8_t readChar(void);

/* Set bus mode, true for command mode false for data mode */
void setBusMode(bool mode);

/* Dummy function for handling a service request, to be implemented */
void serviceRequest(void);
#endif
