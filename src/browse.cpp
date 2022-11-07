#include "constants.h"
#include "sensors.h"
#include "movements.h"

void BrowsingRed (){
    int distanceMin = 95;
    int distanceMax = 110;
    int distance1=0;
    int distance2=0;

    for (int i=0; i<20; i++){
        int pin1 = analogRead(A0);
        distance1 += GetDistance (pin1);
        int pin2 = analogRead(A1);
        distance2 += GetDistance (pin2);
        }
        distance1 /=20; distance2 /=20;
    if (distance1>distanceMin && distance1<distanceMax){
        if (distance2<distanceMin || distance2>distanceMax){
            RotateTwoWheels(180);
        Serial.println("Rouge");
        }}
    else if (distance2>distanceMin && distance2<distanceMax){
        if (distance1<distanceMin || distance1>distanceMax){
        Serial.println("Rouge");
        }}
    

}

void BrowsingYellow (){
    int distanceMin = 80;
    int distanceMax = 100;
    int distance1=0;
    int distance2=0;

    for (int i=0; i<20; i++){
        int pin1 = analogRead(A0);
        distance1 += GetDistance (pin1);
        int pin2 = analogRead(A1);
        distance2 += GetDistance (pin2);
        }
        distance1 /=20; distance2 /=20;
    if (distance1>distanceMin && distance1<distanceMax){
        if (distance2<distanceMin || distance2>distanceMax){
            RotateTwoWheels(180);
        Serial.println("Rouge");
        }}
    else if (distance2>distanceMin && distance2<distanceMax){
        if (distance1<distanceMin || distance1>distanceMax){
        Serial.println("Rouge");
        }}
}

void BrowsingGreen (){
    int distanceMin = 40;
    int distanceMax = 50;
    int distance1=0;
    int distance2=0;

    for (int i=0; i<20; i++){
        int pin1 = analogRead(A0);
        distance1 += GetDistance (pin1);
        int pin2 = analogRead(A1);
        distance2 += GetDistance (pin2);
        }
        distance1 /=20; distance2 /=20;
    if (distance1>distanceMin && distance1<distanceMax){
        if (distance2<distanceMin || distance2>distanceMax){
            RotateTwoWheels(180);
        Serial.println("Rouge");
        }}
    else if (distance2>distanceMin && distance2<distanceMax){
        if (distance1<distanceMin || distance1>distanceMax){
        Serial.println("Rouge");
        }}
}

void BrowsingBlue (){
    int distanceMin = 5;
    int distanceMax = 15;
    int distance1=0;
    int distance2=0;

    for (int i=0; i<20; i++){
        int pin1 = analogRead(A0);
        distance1 += GetDistance (pin1);
        int pin2 = analogRead(A1);
        distance2 += GetDistance (pin2);
        }
        distance1 /=20; distance2 /=20;
    if (distance1>distanceMin && distance1<distanceMax){
        if (distance2<distanceMin || distance2>distanceMax){
            RotateTwoWheels(180);
        Serial.println("Rouge");
        }}
    else if (distance2>distanceMin && distance2<distanceMax){
        if (distance1<distanceMin || distance1>distanceMax){
        Serial.println("Rouge");
        }}
}