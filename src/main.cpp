#include <Arduino.h>
#include <librobus.h>
#include <Adafruit_TCS34725.h>
#include "constants.h"
#include "sensors.h"
#include "movements.h"
#include "utils.h"
#include "browse.h"





void setup() {
 	Serial.begin(9600);
    BoardInit();  
    
    // Set output for leds
    pinMode(10, OUTPUT); 
    pinMode(11, OUTPUT); 
    pinMode(12, OUTPUT); 
    pinMode(13, OUTPUT); 

 	pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void loop() {
//ROBUS_IsBumper(3)
    if (1) { // DEVRA ÊTRE REMPLACÉ PAR LE SIFFLET
        int distance1 = 0, distance2=0;
        while(1)
        {
            int pin1 = analogRead(A0);
            distance1 = GetDistance (pin1);
            int pin2 = analogRead(A1);
            distance2 = GetDistance (pin2);
            Serial.print("Pin1 = ");
            Serial.print(pin1);
            Serial.print("\n");
            Serial.print("Pin2 = ");
            Serial.print(pin2);
            Serial.print("\n\n");
            delay(500);
        }

        float red=0, green=0, blue=0;

        //Détection de la couleur
        ReadColor(&red, &green, &blue);
        int color = TurnOnLight(red, green, blue);
        
        switch (color){
            case RED:
            BrowsingRed();
            break;

            case YELLOW:
            BrowsingYellow();
            break;
            
            case GREEN:
            BrowsingGreen();
            break;
            
            case BLUE:
            BrowsingBlue();
            break;
            
            default:
            break;

        }
        

        


        //int pin = analogRead(A0);
        //int distance = GetDistance (pin);
        //Serial.println(distance);
        
        
    }

}

