#include "GPIB.h"

void GPIB_Init() {

	PORTC &= ~(1<<IFC);
	// Delay to give devices time to respond, standard specifies 100µs
	_delay_us(100);
	setBusMode(true);

}
bool readNRFD() {

	if((PORTD & (1<<NRFD)) == HIGH) { return false; }
	else { return true; }
}
bool readNDAC() {

	if((PORTD & (1<<NDAC)) == HIGH) { return false; }
	else { return false; }
}
void writeChar(char data) {

	DIO = data;
	// Enable output buffer in output mode
	PORTE &= ~(1<<TE);
	PORTD &= ~(1<<DAV);
}
uint8_t readChar(void) {

	return DIO;

}
void setBusMode(bool mode) {

	if(mode == true) {
		PORTE &= ~(1<<TE);
		PORTF &= ~(1<<DC);
		PORTD &= ~(1<<ATN); 
	}
	else {
		PORTE |= (1<<TE);
		PORTF |= (1<<DC);
		PORTD |= (1<<ATN); 
	}
}
void serviceRequest(void) {

	// Do something about a service request
	return;
}
