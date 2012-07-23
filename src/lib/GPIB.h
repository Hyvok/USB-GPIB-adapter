#ifndef GPIB_H
#define GPIB_H

#define HIGH 0
#define LOW 1

enum BOOLEAN { TRUE = 1, FALSE  = 0 };

/* Initialize GPIB bus, become controller-in-charge */
void GPIB_init(void);

/* Function checks if the listener is ready for data */
enum BOOLEAN checkNRFD(void);

/* Functions checks if the listener is ready to accept data */
enum BOOLEAN checkNDAC(void);

/* Write a char to the bus, listener is ready for data when NRFD = LOW,
listener has accepted data when NDAC == HIGH */
void writeChar(char data);

/* Set bus mode, true for command mode false for data mode */
void setMode(enum BOOLEAN mode);
#endif
