#include <constants.h>
#include "sensors.h"
#include "movements.h"
#include "utils.h"




void setup() {
 	//Init Serial USB
	BoardInit();
 	Serial.begin(9600);
 	Serial.println(F("Initialize System"));
 	//Init ditance ir
 	pinMode(A1, INPUT);
	
}
void loop() {
	float red=0;
	float green=0;
	float blue=0;

ReadColorSensor(&red,&green,&blue);
PrintColor(red,green,blue);
if(GetDistance(analogRead(A1))>125)  RotateTwoWheels(176);




delay(1000);
	
}
