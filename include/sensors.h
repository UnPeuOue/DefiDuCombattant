#ifndef SENSORS_H
#define SENSORS_H
#include <SharpIR.h>
void ReadColor(float* pointerRed, float* pointerGreen, float* pointerBlue);
int TurnOnLight(float r, float g, float b);
void TurnOffLights();
void LineDetector ();
int PrintColor(float r, float g, float b);
void ReadIR () ;
void RotateStart();
#endif