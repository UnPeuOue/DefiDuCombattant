#ifndef SENSORS_H
#define SENSORS_H

void ReadColor(float* pointerRed, float* pointerGreen, float* pointerBlue);
int TurnOnLight(float r, float g, float b);
void TurnOffLights();
void LineDetector ();
int GetDistance (int pin);


#endif