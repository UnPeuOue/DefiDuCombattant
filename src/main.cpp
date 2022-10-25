#include <Arduino.h>
#include <librobus.h>

#define PI 3.14159
#define WHEELS_DISTANCE 18.75
#define WHEEL_DIAMETER 7.62
#define WHEEL_CIRCUMFERENCE (PI*WHEEL_DIAMETER)
#define SPEED_LIMIT_ROTATE 0.3
#define SPEED_LIMIT 0.6
#define ACCEL_DECEL_distance 37.4

//Description: La fonction calcul l'arc tracé lorsqu'une seule roue tourne
//Précondition: L'angle (réel) doit être compris entre 0 et 180 degs
//Postcondition: La fonction retourne un arc de cercle (réel) en cm
float CalculArc(float angle)
{
    return (2*WHEELS_DISTANCE*PI)*(angle/360);
}



//Description: La fonction convertie une distance en pulse
//Précondition: La distance (réel) doit être exprimée en cm
//Postcondition: La fonction retourne le nombre de pulses (réel)
float DistanceToPulse(float distance)
{
    return (3200/WHEEL_CIRCUMFERENCE)*distance;
}

//Desciption: La fonction convertie un nombre de pulses en distance
//Précondition: Fournir le nombre de pulses (réel)
//Postcondition: La fonction retourne la distance (réel) en cm
float PulseToDistance (float pulse)
{
    return (WHEEL_CIRCUMFERENCE/3200)*pulse;
}


//Description: La fonction mets en arrêt le robot
//Aucune entrée/sortie
void Stop()
{
    MOTOR_SetSpeed(0, 0.0);
    MOTOR_SetSpeed(1, 0.0);
}
//Description: La fonction effectue un virage
//Précondition: L'arc (réel) en pulse est plus grand que 0 et direction est soit 0:VirageDroite ou 1:VirageGauche
//Précondition: Aucune sortie
void Rotate(float angle, int direction)
{
    ENCODER_ReadReset(0);
    ENCODER_ReadReset(1);
    float arc = DistanceToPulse(CalculArc(angle)); 

    switch(direction)
    {
        case 0: //Roue gauche
            MOTOR_SetSpeed(direction, SPEED_LIMIT_ROTATE);
            while(ENCODER_Read(0)<arc){}
            Stop();
            break;
        case 1: //Roue droite
            MOTOR_SetSpeed(direction, SPEED_LIMIT_ROTATE);
            while(ENCODER_Read(1)<arc){}
            Stop();
            break;
    }
}

//Description: La fonction effectue un virage de retour
//Précondition: Aucune entrée
//Précondition: Aucune sortie
void RotateTwoWheels(float angle)
{
    ENCODER_ReadReset(0);
    ENCODER_ReadReset(1);
    float arc = DistanceToPulse(CalculArc(angle/2)); 
    MOTOR_SetSpeed(0, SPEED_LIMIT_ROTATE/2);
    MOTOR_SetSpeed(1, -SPEED_LIMIT_ROTATE/2);
    while (ENCODER_Read(0)<(arc))
    {
        int32_t wheelOne = ENCODER_Read(0);
        int32_t wheelTwo = ENCODER_Read(1);
        int32_t errorRange = abs(wheelOne) - abs(wheelTwo);
        if(errorRange > 0){ 
            float output = 0.01 * errorRange;
            MOTOR_SetSpeed(1, -(SPEED_LIMIT_ROTATE/2 + output));
        }
    }
    Stop();   
}

//Description: La fonction corrige la trajectoire avancer
//Précondition: Les constantes kp et ki (réels) et lastTime
//Précondition: 
double Compute(double kp, double ki)
{  
    int32_t wheelOne = ENCODER_Read(0);
    int32_t wheelTwo = ENCODER_Read(1);
    int32_t errorRange = abs(wheelOne) - abs(wheelTwo);
    double output = 0;
    output = (kp * errorRange) + ki;
    return output;
}

//Description: La fonction fait avancer le robot
//Précondition: La distance (réel) est en pulse
//Précondition: Aucune sortie
void Forward(float distance)
{
    distance = DistanceToPulse(distance);
    ENCODER_ReadReset(0);
    ENCODER_ReadReset(1);
    //unsigned long lastTime = 0;
    //unsigned long * pointLastTime = &lastTime;
    Acce(SPEED_LIMIT);
    double errorSums = 0;
    while (ENCODER_Read(0)<= distance)
    {
        int32_t wheelOne = ENCODER_Read(0);
        int32_t wheelTwo = ENCODER_Read(1);
        int32_t errorRange = abs(wheelOne) - abs(wheelTwo);
        errorSums += errorRange;
        double errorcorrected = (0.01 * errorRange);
        MOTOR_SetSpeed(0,SPEED_LIMIT);
        MOTOR_SetSpeed(1,SPEED_LIMIT+errorcorrected);
    }
    Dece(SPEED_LIMIT);

}

void Dece(float currentSpeed)
{
    int endocerMeasure = 0;
    ////unsigned long lastTime = 0;
    //unsigned long * pointLastTime = &lastTime;
    
    endocerMeasure = ENCODER_Read(0);
        for (float i = currentSpeed; i >= 0.1; i -= 0.01)
        {
            while (ENCODER_Read(0) < endocerMeasure + 50)
            {
                double errorcorrected=Compute(0.01,0.005);
                MOTOR_SetSpeed(0,i);
                MOTOR_SetSpeed(1,i+errorcorrected);
            }
            endocerMeasure = ENCODER_Read(0);
        }
        Stop();

}

void Acce(float desiredSpeed)
{
    int endocerMeasure = 0;
    //unsigned long lastTime = 0;
    //unsigned long * pointLastTime = &lastTime;
    
    endocerMeasure = ENCODER_Read(0);
        for (float i = 0.1; i < desiredSpeed; i += 0.01)
        {
            while (ENCODER_Read(0) < endocerMeasure + 50)
            {
                double errorcorrected=Compute(0.01,0.005);
                MOTOR_SetSpeed(0,i);
                MOTOR_SetSpeed(1,i+errorcorrected);
            }
            endocerMeasure = ENCODER_Read(0);
        }

}




void setup() {
  Serial.begin(9600);
  delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}