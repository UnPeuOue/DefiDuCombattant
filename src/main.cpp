#include <constants.h>
#include "sensors.h"
#include "movements.h"
#include "utils.h"

int i=0;

void setup() {
    Serial.begin(9600);
    BoardInit();  
    //The following code will be executed once when your Arduino turns on.
    pinMode(10, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    

    pinMode(11, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
    
    pinMode(12, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
    
    pinMode(13, OUTPUT); //Set pin 13 as an 'output' pin as we will make it output a voltage.
    
    SERVO_Disable(1);
    //SERVO_Enable(1);

}


void loop() {

    
    delay(1000);

	//int pin = analogRead(A1);
	//GetDistance(pin);
    
}
