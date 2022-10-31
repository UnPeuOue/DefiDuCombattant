#include <constants.h>
#include <Arduino.h>
#include <LibRobus.h>


void testGP2Y0A21();
int distRawToPhys(int raw);
double Compute(double kp, double ki,double sp , double pv,double *lastime, double *errsum);


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
        Serial.println(lastime);
         Serial.println(errsum);
        
        MOTOR_SetSpeed(0,0.3);
        MOTOR_SetSpeed(1,0.3+Compute(0.001,0.0005,ENCODER_Read(0),ENCODER_Read(1),&lastime,&errsum));
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
    *lastime= now;
    
    return output;
    }
 return 0;
}