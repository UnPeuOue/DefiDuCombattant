#include <constants.h>
#include <sensors.h>
#include "Adafruit_TCS34725.h"
#include <Wire.h>
#include "utils.h"

// Description : La fonction détecte une intensité de rouge, de vert et de bleu.
// Préconditions : La fonction prend en arguments trois pointeurs vers rouge, vert et bleu.
// Postconditions : Aucun retour.
void ReadColorSensor(float* pointerRed, float* pointerGreen, float* pointerBlue)
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

    if (r>(2.5*b) && r>(2.5*g))
    {
        TurnOffLights();
        digitalWrite(13, HIGH);
        Serial.println("Rouge\n");
        return 1;
    }
  
    if (r>(2.5*b) && r<(2.5*g))
    {
        TurnOffLights();
        digitalWrite(12, HIGH);
        Serial.println("Jaune\n");
        return 2;
    }
  
    if (g>r && g>b)
    {
        TurnOffLights();
        digitalWrite(10, HIGH);
        Serial.println("Vert\n");
        return 3;
    }
    if (b>r && b>g)
    {
        TurnOffLights();
        digitalWrite(11, HIGH);
        Serial.println("Bleu\n");
        return 4;
    }
    return 0;
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

int GetDistance (int pin) {
 	
	float Vout = float(pin) * 0.0048828125; // Conversion analog to voltage
	int phys = 13 * pow(Vout, -1); // Conversion volt to distance

 	Serial.println(int(InchToCm(phys)));
	return int(InchToCm(phys));

}