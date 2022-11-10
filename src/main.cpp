#include <Arduino.h>
#include <librobus.h>
#include <Adafruit_TCS34725.h>
#include "constants.h"
#include "sensors.h"
#include "movements.h"
#include "utils.h"






void setup() {
 	Serial.begin(9600);
    BoardInit();  
    
    
    
    // Set output for leds
    pinMode(10, OUTPUT); 
    pinMode(11, OUTPUT); 
    pinMode(12, OUTPUT); 
    pinMode(13, OUTPUT); 
    
    //Signal
    pinMode(A2, INPUT);

 	
}

void loop() {
    float red=0,green=0,blue=0;
    int color=0;
    float speed_left=0.35;
    


    if(ROBUS_IsBumper(3)){
    MOTOR_SetSpeed(0,0.35);
    double lastime=0;
    double errsum=0;
    float signal = 0;
    ReadColor(&red,&green,&blue);
    color=PrintColor(red,green,blue);
    TurnOnLight(red,green,blue);
    signal = analogRead(A2);
    float voltage = signal * (5.0 / 1023.0);
    
    voltage =3; //Temporaire
    while (1)
    if (voltage>1.7) {

        RotateForward(color,speed_left);
     
      //MOTOR_SetSpeed(1, 0.35+Compute1(0.003,0.001,&lastime,&errsum,1));

        //int distance1 = 0, distance2=0;
        
        //Serial.println(ROBUS_ReadIR(1));
        //Serial.println(ROBUS_ReadIR(2));
        

        

        //Détection de la couleur
       
       
        
    }
    }
}

