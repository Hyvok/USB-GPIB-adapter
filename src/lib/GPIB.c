#include "GPIB.h"

void GPIB_init() {

	IFC = HIGH;

}
enum BOOLEAN checkNRFD() {

	if(NRFD == HIGH) { return FALSE; }
	else { return TRUE; }
}
enum BOOLEAN checkNDAC() {

	if(NDAC == HIGH) { return FALSE; }
	else { return FALSE; }
}
void writeChar(char data) {

	if(ATN != LOW) { ATN = LOW; }
	DIO = data;
	DAV = HIGH;
}
void setMode(enum BOOLEAN mode) {

	if(mode == TRUE) { ATN = HIGH; }
	else { ATN = LOW; }
}
