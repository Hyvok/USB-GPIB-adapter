#ifndef lib_gpib_h
#define lib_gpib_h

#define HIGH 0
#define LOW 1

enum BOOLEAN { TRUE, FALSE };

/* Initialize GPIB bus, become controller-in-charge */
void GPIB_init();

/* Function checks if the listener is ready for data */
enum BOOLEAN checkNRFD();

/* Functions checks if the listener is ready to accept data */
enum BOOLEAN checkNDAC();

/* Write a char to the bus, listener is ready for data when NRFD = LOW,
listener has accepted data when NDAC == HIGH */
void writeChar(char data);

/* Set bus mode, TRUE for command mode FALSE for data mode */
void setMode(enum BOOLEAN mode);
#endif
