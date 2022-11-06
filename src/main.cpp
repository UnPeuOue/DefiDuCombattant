#include <constants.h>
#include <Arduino.h>
#include <LibRobus.h>


void testGP2Y0A21();
int distRawToPhys(int raw);
double Compute(double kp, double ki,double *lastime, double *errsum);


void setup() {
    Serial.begin(9600);
    BoardInit();  
   
}


void loop() {
 if (ROBUS_IsBumper(3)) {
    double lastime=0;
    double errsum=0;

    while(1) 
    {
        Serial.print("encoder 0=");
        Serial.println(ENCODER_Read(0));
        Serial.print("encoder 1=");
        Serial.println(ENCODER_Read(1));
        MOTOR_SetSpeed(0,0.3+Compute(0.003,0.001,&lastime,&errsum));
        MOTOR_SetSpeed(1,0.3);
    }
 }
 
    

}






double Compute(double kp, double ki,double *lastime, double *errsum)
{  
    int sampletime = 200; 
    unsigned long now = millis();
    int timechange = now-*lastime;
    if (timechange>= sampletime) 
    {
    double error = ENCODER_Read(1)-ENCODER_Read(0);
    Serial.print("error=");
    Serial.println(error);

   
    *errsum+= error;
    double output = 0;
    output = (kp * error) + (ki* *errsum);
    *lastime= now;
    
    
    return output;
    }
 return 0;
}