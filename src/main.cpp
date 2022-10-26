#include <constants.h>
#include <sensors.h>
#include <sensors.cpp>



void setup() {
    Serial.begin(9600);
    MOTOR_SetSpeed(0,0.0);
    MOTOR_SetSpeed(1,0.0);

    

}


void loop() {

  MOTOR_SetSpeed(0,0.0);
  MOTOR_SetSpeed(1,0.0);
  
  float r=0, g=0, b=0;
    
  ReadColorSensor(&r, &g, &b);

  if (r>(2.5*b) && r>(2.5*g))
  {
    Serial.println("Rouge\n");
    delay(500);
  }
  
  if (r>(2.5*b) && r<(2.5*g))
  {
    Serial.println("Jaune\n");
    delay(500);
  }
  
  if (g>r && g>b)
  {
    Serial.println("Vert\n");
    delay(500);
  }
  if (b>r && b>g)
  {
    Serial.println("Bleu\n");
    delay(500);
  }
  
}



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