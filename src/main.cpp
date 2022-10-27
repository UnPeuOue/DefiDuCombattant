#include <constants.h>
#include "sensors.h"
#include "movements.h"


int ledPin = 13;  // LED connected to digital pin 13
int inPin = 7;    // pushbutton connected to digital pin 7
int val = 0;      // variable to store the read value

void setup() {
    Serial.begin(9600);
    BoardInit();  
    pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
    pinMode(inPin, INPUT);    // sets the digital pin 7 as input
}


void loop() {
  
  double value = 0;
  if (ROBUS_IsBumper(3)) {
  
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(ledPin, val);  // sets the LED to the button's value
  Serial.println(val);

  
  
  }

}
