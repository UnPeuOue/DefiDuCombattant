#include <Arduino.h>
#include <librobus.h>
#include <Adafruit_TCS34725.h>
#include "constants.h"
#include "sensors.h"
#include "movements.h"
#include "utils.h"
#include "SharpIR.h"


SharpIR mySensor = SharpIR(A0, 1080);



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
    pinMode(A7,INPUT);
    pinMode(A1,INPUT);

 	
}

void loop() {
    
    /*while(1)
    {
        value1 = ROBUS_ReadIR(1);
        value2 = ROBUS_ReadIR(2);
        Serial.print("1 : ");
        Serial.println(value1);
        Serial.print("2 : ");
        Serial.println(value2);
        delay(1000);
    }
    */

    /*while(1)
{
    ReadColor(&red, &green, &blue);
    Serial.print("Red : ");
    Serial.println(red);
    Serial.print("Green : ");
    Serial.println(green);
    Serial.print("Blue : ");
    Serial.println(blue);
    delay(1000);
}*/




   
    
    






    if(ROBUS_IsBumper(3)){
    
    
   float speedLeft=0.4;
    float red=0,green=0,blue=0;
    float signal = 0;
    ReadColor(&red,&green,&blue);
    int color=PrintColor(red,green,blue);
    TurnOnLight(red,green,blue);
 
    
    
    while (1) {
    signal = analogRead(A2);
    float voltage = signal * (5.0 / 1023.0);
    Serial.println(voltage);
    if (voltage>2.5) {

        RotateStart();
        RotateForward(color,speedLeft);
        LineDetector();

     
      //MOTOR_SetSpeed(1, 0.35+Compute1(0.003,0.001,&lastime,&errsum,1));

        //int distance1 = 0, distance2=0;
        
        //Serial.println(ROBUS_ReadIR(1));
        //Serial.println(ROBUS_ReadIR(2));
        

    }

}
}
}