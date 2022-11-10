#include <constants.h>
#include <sensors.h>
#include <sensors.h>
#include "Adafruit_TCS34725.h"
#include <Wire.h>
#include <utils.h>

// Description : La fonction détecte une intensité de rouge, de vert et de bleu.
// Préconditions : La fonction prend en arguments trois pointeurs vers rouge, vert et bleu.
// Postconditions : Aucun retour.
void ReadColor(float* pointerRed, float* pointerGreen, float* pointerBlue)
{    
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
    
    if (tcs.begin()) {
        uint16_t clear, red, green, blue;

        delay(60);

        tcs.getRawData(&red, &green, &blue, &clear);
        
        uint32_t sum = clear;
        float r, g, b;
        r = red; r /= sum;
        g = green; g /= sum;
        b = blue; b /= sum;
        r *= 256; g *= 256; b *= 256;

        *pointerRed = r;
        *pointerGreen = g;
        *pointerBlue = b;
    } else {
        Serial.println("Erreur");
    }

}

int PrintColor(float r, float g, float b)
{
    if (r>(2.5*b) && r>(2.5*g)) return RED;
    if (r>(2.5*b) && r<(2.5*g)) return YELLOW;
    if (g>r && g>b) return GREEN;
    if (b>r && b>g) return BLUE;
    return 5 ;
}




// Description : La fonction allume une del et suit indique la couleur en question
// Préconditions : La fonction prend en arguments trois valeur de rouge, vert et bleu.
// Postconditions : La fonction retour 1: rouge, 2: jaune, 3: vert ou 4: bleu.
int TurnOnLight(float r, float g, float b)
{

    if (r>(2.5*b) && r>(2.5*g))
    {
        TurnOffLights();
        digitalWrite(13, HIGH);
        return RED;
    }
  
    if (r>(2.5*b) && r<(2.5*g))
    {
        TurnOffLights();
        digitalWrite(12, HIGH);
        return YELLOW;
    }
  
    if (g>r && g>b)
    {
        TurnOffLights();
        digitalWrite(10, HIGH);
        return GREEN;
    }
    if (b>r && b>g)
    {
        TurnOffLights();
        digitalWrite(11, HIGH);
        return BLUE;
    }
}

void LineDetector ()
{
    float i = 0.2;
  MOTOR_SetSpeed(0, i);
  MOTOR_SetSpeed(1, i);
  int j=-1, k=-1;

  int CONDITION=1;
  
  
  while(CONDITION)
  {
    int sensorValue = analogRead(A7);
    float voltage = sensorValue * (5.0 / 1023.0);
    Serial.println(voltage);
    

    if ((1.9 < voltage) && (voltage < 2.1))
    {
        // TURN RIGHT
        if (k!=1)
        {
            j=0;
            MOTOR_SetSpeed(j, 0.0);
        }
        else
        { 
            MOTOR_SetSpeed(0, i);
            MOTOR_SetSpeed(1, i);
        }
        ENCODER_Reset(0); ENCODER_Reset(1);
    }
    else if ((0.5 < voltage) && (voltage < 0.8))
    {
        // TURN RIGHT
        if (k!=1)
        {
            j=0;
            MOTOR_SetSpeed(j, 0.0);
        }
        else
        { 
            MOTOR_SetSpeed(0, i);
            MOTOR_SetSpeed(1, i);
        }
        ENCODER_Reset(0); ENCODER_Reset(1);
    }
    else if ((3.9 < voltage) && (voltage < 4.1))
    {
        // TURN LEFT
        if (j!=0)
        {
            k=1;
            MOTOR_SetSpeed(k, 0.0);
        }
        else
        { 
            MOTOR_SetSpeed(0, i);
            MOTOR_SetSpeed(1, i);
        }
        ENCODER_Reset(0); ENCODER_Reset(1);
    }
    else if ((2.5 < voltage) && (voltage < 2.8))
    {
        // TURN LEFT
        if (j!=0)
        {
            k=1;
            MOTOR_SetSpeed(k, 0.0);
        }
        else
        { 
            MOTOR_SetSpeed(0, i);
            MOTOR_SetSpeed(1, i);
        }
        ENCODER_Reset(0); ENCODER_Reset(1);
    }
    else
    {
        MOTOR_SetSpeed(0, i);
        MOTOR_SetSpeed(1, i);
    }
    k=-1;
    j=-1;
  }
}

void TurnOffLights()
{
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}




void DetectDistance ()
{
    


}