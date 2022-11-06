#include <constants.h>
#include "sensors.h"
#include "movements.h"

void testGP2Y0A21();
int distRawToPhys(int raw);


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
 float red=0;
 float green=0;
 float blue=0;

  ReadColorSensor(&red,&green,&blue);
  PrintColor(red,green,blue);
  

}
