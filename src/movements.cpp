#include <constants.h>
#include <utils.h>
#include <movements.h>
#include <sensors.h>

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


void RotateForward (int Color, float speedLeft)
{
    switch (Color)
    {
    case RED:

        ENCODER_Reset(0); ENCODER_Reset(1);
        MOTOR_SetSpeed(0, speedLeft);

        float distance1 = RED*30.5-5.6; //Left
        float distance2 = (RED-1)*30.5+5.6; //Right
        int encoderMeasure =0;
        

        float speedRight = speedLeft*(distance2/distance1);
        MOTOR_SetSpeed(1, speedRight);

        float distance = distance1*PI*2;
        distance *= 90;
        distance /= 360;
        distance = DistanceToPulse(distance);
        while (encoderMeasure<distance){
            encoderMeasure = ENCODER_Read(0);
        }
        Stop();
        


        break;
    
    case YELLOW:
        /* code */
        break;
    
    case GREEN:
        /* code */
        break;

    case BLUE:
        /* code */
        break;

    default:
        break;
    }

    
} 


