#include "lib_gpib.h"

void GPIB_init() {

	IFC = HIGH;

}
BOOLEAN checkNRFD() {

	if(NRFD == HIGH) { return FALSE; }
	else { return TRUE; }
}
BOOLEAN checkNDAC() {

	if(NDAC == HIGH) { return FALSE; }
	else { return TRUE; }
}
void writeChar(char data) {

	if(ATN != LOW) { ATN = LOW; }
	DIO = data;
	DAV = HIGH;
}
void setMode(BOOLEAN mode) {

	if(mode == TRUE) { ATN = HIGH; }
	else { ATN = LOW; }
}
