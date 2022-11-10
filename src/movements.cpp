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
    //Acce(SPEED_LIMIT);
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
    //Dece(SPEED_LIMIT);
    Stop();

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


void RotateForwardhardcoded (int Color, float speedLeft)
{

    float distance1 = 0;
    float distance2 = 0;
    int encoderMeasure =0;
    
        
    float speedRight = 0;
    float distance = 0;

    double lastime=0;
    double errsum=0;
    float fraction=0; //POUR LE PID

    switch (Color)
    {
    case RED:

        ENCODER_Reset(0); ENCODER_Reset(1);
        MOTOR_SetSpeed(0, speedLeft);

         distance1 = RED*30.5-5.6; //Left
         distance2 = (RED-1)*30.5+5.6; //Right
         encoderMeasure =0;
        

         speedRight = speedLeft*(distance2/distance1);
         fraction = distance2/distance1;
        MOTOR_SetSpeed(1, speedRight+Compute1(0.003,0.001,&lastime,&errsum, fraction)); //PID

         distance = distance1*PI*2;
        distance *= 90;
        distance /= 360;
        distance = DistanceToPulse(distance);
        while (encoderMeasure<distance){
            MOTOR_SetSpeed(1, speedRight+Compute1(0.003,0.001,&lastime,&errsum, fraction));
            encoderMeasure = ENCODER_Read(0);
        }
        Stop();
        


        break;
    
    case YELLOW:
        
        ENCODER_Reset(0); ENCODER_Reset(1);
        MOTOR_SetSpeed(0, speedLeft);

         distance1 = YELLOW*30.5-5.6; //Left
         distance2 = (YELLOW-1)*30.5+5.6; //Right
         encoderMeasure =0;
        

         speedRight = speedLeft*(distance2/distance1);
        MOTOR_SetSpeed(1, speedRight); //PID

         distance = distance1*PI*2;
        distance *= 90;
        distance /= 360;
        distance = DistanceToPulse(distance);
        while (encoderMeasure<distance){
            encoderMeasure = ENCODER_Read(0);
        }
        Stop();

        break;
    
    case GREEN:
        
        ENCODER_Reset(0); ENCODER_Reset(1);
        MOTOR_SetSpeed(0, speedLeft);

         distance1 = GREEN*30.5-5.6; //Left
         distance2 = (GREEN-1)*30.5+5.6; //Right
         encoderMeasure =0;
        

         speedRight = speedLeft*(distance2/distance1);
        MOTOR_SetSpeed(1, speedRight); //PID

         distance = distance1*PI*2;
        distance *= 90;
        distance /= 360;
        distance = DistanceToPulse(distance);
        while (encoderMeasure<distance){
            encoderMeasure = ENCODER_Read(0);
        }
        Stop();
        
        
        break;

    case BLUE:
        
        
        ENCODER_Reset(0); ENCODER_Reset(1);
        MOTOR_SetSpeed(0, speedLeft);

         distance1 = BLUE*30.5-5.6; //Left
         distance2 = (BLUE-1)*30.5+5.6; //Right
         encoderMeasure =0;
        

         speedRight = speedLeft*(distance2/distance1);
        MOTOR_SetSpeed(1, speedRight); //PID

         distance = distance1*PI*2;
        distance *= 90;
        distance /= 360;
        distance = DistanceToPulse(distance);
        while (encoderMeasure<distance){
            encoderMeasure = ENCODER_Read(0);
        }
        Stop();
        
        
        
        break;

    default:
        break;
    }

    
} 


double Compute1(double kp, double ki,double *lastime, double *errsum, float fraction)
{  
    int sampletime = 200; 
    unsigned long now = millis();
    int timechange = now-*lastime;
    if (timechange>= sampletime) 
    {
    double error = ENCODER_Read(1)-(fraction*ENCODER_Read(0));
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

void RotateForward(int Color, float speedLeft)
{

float speedRight=speedLeft;
int currentcolor= 100;
float red=0;
float green=0;
float blue=0;
double errsum=0;
double lastime=0;
MOTOR_SetSpeed(1,speedLeft);
while(currentcolor!=0) 
{
    

 switch (Color) 
    {
       
        case YELLOW : 
         Serial.println(currentcolor);
        ReadColor(&red,&green,&blue);

        currentcolor=PrintColor(red,green,blue);
        

        if (currentcolor==RED) 
        {
            MOTOR_SetSpeed(0,speedLeft+speedIteration);

            
        }

        if(currentcolor==GREEN) 
        {
            MOTOR_SetSpeed(0,speedLeft-speedIteration);
        }

        else
        {
            MOTOR_SetSpeed(0,speedRight);
            MOTOR_SetSpeed(1,speedLeft+0.02);
        
        }
        break;

        //default: 
        //MOTOR_SetSpeed(0,0);
      
        //MOTOR_SetSpeed(1,0);
        //break;
     }



    }
}






