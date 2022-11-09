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

    


    if(ROBUS_IsBumper(3)){
    float signal = 0;
    signal = analogRead(A2);
    float voltage = signal * (5.0 / 1023.0);
    
    voltage =2; //Temporaire
    
    if (voltage>1.7) {


        //int distance1 = 0, distance2=0;
        
        //Serial.println(ROBUS_ReadIR(1));
        //Serial.println(ROBUS_ReadIR(2));
        

        

        //Détection de la couleur
        int success = 1;
        int color = 0;
        while (success){
        float red=0, green=0, blue=0;
        ReadColor(&red, &green, &blue);
        color = TurnOnLight(red, green, blue);
        
        
        switch (color){
            case RED:
            RotateForward(RED, 0.4);
            
            success = 0;
            break;

            case YELLOW:
            RotateForward(YELLOW, 0.4);
            success = 0;
            break;
            
            case GREEN:
            RotateForward(GREEN, 0.4);
            success = 0;
            break;
            
            case BLUE:
            RotateForward(BLUE, 0.4);
            success = 0;
            break;
            
            default:
            break;
        }
        }
        Stop();
        
        Forward(InchToCm(2*12));

        switch (color){
            case RED:
            RotateForward(RED, 0.4);
            
            success = 0;
            break;

            case YELLOW:
            RotateForward(YELLOW, 0.4);
            success = 0;
            break;
            
            case GREEN:
            RotateForward(GREEN, 0.4);
            success = 0;
            break;
            
            case BLUE:
            RotateForward(BLUE, 0.4);
            success = 0;
            break;
            
            default:
            break;
        }
        
        Stop();


        Forward(InchToCm(8*12));


        if (color == RED) Rotate(90, 0);


        LineDetector(); //Bouble infinie

        double errorSums = 0;
        while (ENCODER_Read(0) < DistanceToPulse(InchToCm(8*12)))
        {
            int32_t wheelOne = ENCODER_Read(0);
            int32_t wheelTwo = ENCODER_Read(1);
            int32_t errorRange = abs(wheelOne) - abs(wheelTwo);
            errorSums += errorRange;
            double errorcorrected = (0.01 * errorRange);
            MOTOR_SetSpeed(0,SPEED_LIMIT);
            MOTOR_SetSpeed(1,SPEED_LIMIT+errorcorrected);
        }
        Stop();

        RotateForward(BLUE, 0.4);


        switch (color)
        {
            case RED:
            Forward(DistanceToPulse(91.5));
            break;
            
            case YELLOW:
            Forward(DistanceToPulse(61));
            break;

            case GREEN:
            Forward(DistanceToPulse(30.5));
            break;
        
            default:
            break;
        }

        Forward(InchToCm(2*12));

        RotateForward(BLUE, 0.4);










        
        
        
        
        //Forward(InchToCm(8));

        



        


        //int pin = analogRead(A0);
        //int distance = GetDistance (pin);
        //Serial.println(distance);
        
        
    }
    }
}

