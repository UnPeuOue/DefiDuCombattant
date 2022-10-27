#include <constants.h>
#include "sensors.h"
#include "movements.h"

double Compute(double kp, double ki,double sp , double pv,double *lastime, double *errsum);

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
  if (ROBUS_IsBumper(1)) {
  
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(ledPin, val);  // sets the LED to the button's value
  Serial.println(val);
  }
  

  if (ROBUS_IsBumper(3)) {
  double kp = 0.005;
  double ki = 0.005;
  
  double lastime = 0;
  double errsum = 0;
  while (1)
  {
    
    double sp = ENCODER_Read(0);
  double pv = ENCODER_Read(1);
  MOTOR_SetSpeed(0, 0.5);
  
  MOTOR_SetSpeed(1, 0.5+Compute(kp, ki, sp, pv, &lastime ,&errsum));
  Serial.println("lastime : ");
  Serial.println(lastime);
  Serial.println("errsum : ");
  Serial.println(errsum);
  if (errsum>1000)
  {
    errsum=0;
  }
  
  }
  }

}

double Compute(double kp, double ki,double sp , double pv,double *lastime, double *errsum)
{  
    int sampletime = 100; 
    unsigned long now = millis();
    int timechange = now-*lastime;
    if (timechange>= sampletime) 
    {
    double error = sp-pv;
    *errsum+= error;
    double output = 0;
    output = (kp * error) + (ki* *errsum);
    *lastime = now;
    Serial.println("output : ");
    Serial.println(output);
    return output;
    }
    return 0;
}
