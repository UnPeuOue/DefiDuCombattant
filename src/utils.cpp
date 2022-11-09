#include <constants.h>
#include <utils.h>
#include <movements.h>

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


float InchToCm (float distance)
{
    return distance * 2.54;
}
