#include <constants.h>
#include "sensors.h"
#include "movements.h"
#include "utils.h"




void setup() {
 	//Init Serial USB
	BoardInit();
	
 	Serial.begin(9600);
 	 Serial.println(F("faudrait faire le PID bro"));
 	//Init ditance ir
 	pinMode(A0, INPUT);
	pinMode(13,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
	
}
void loop() {
 Serial.println(GetDistance(analogRead(A0)));

if (ROBUS_IsBumper(3)) {


if(GetDistance(analogRead(A0))>125) {
	 RotateTwoWheels(176);
} 





	
}

}