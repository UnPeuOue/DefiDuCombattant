#include <constants.h>
#include "sensors.h"
#include "movements.h"

void testGP2Y0A21();
int distRawToPhys(int raw);

/*
void setup() {
    Serial.begin(9600);
    BoardInit();  
    //The following code will be executed once when your Arduino turns on.
    pinMode(10, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    

    pinMode(11, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
    
    pinMode(12, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
    
    pinMode(13, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
}


void loop() {
  
  float red = 0, green = 0, blue = 0;
  ReadColorSensor(&red, &green, &blue);
  PrintColor(red, green, blue);
    

}

*/


//Parameters
const int gp2y0a21Pin 	= A0;
//Variables
int gp2y0a21Val 	= 0;
void setup() {
 	//Init Serial USB
 	Serial.begin(9600);
 	Serial.println(F("Initialize System"));
 	//Init ditance ir
 	pinMode(A0, INPUT);
}
void loop() {
 	testGP2Y0A21();
  delay(10);
}
void testGP2Y0A21() {  //function testGP2Y0A21 
 	////Read distance sensor
 	gp2y0a21Val = analogRead(A0);
 	Serial.println(distRawToPhys(gp2y0a21Val));
 	if (gp2y0a21Val < 200) {
 			//Serial.println(F("Obstacle detected"));
 	} else {
 			//Serial.println(F("No obstacle"));
 	}
}
int distRawToPhys(int raw) {  //function distRawToPhys 
 	////IR Distance sensor conversion rule
 	float Vout = float(raw) * 0.0048828125; // Conversion analog to voltage
 	int phys = 13 * pow(Vout, -1); // Conversion volt to distance
 	return phys;
}