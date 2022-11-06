#ifndef SENSORS_H
#define SENSORS_H

void ReadColorSensor(float* pointerRed, float* pointerGreen, float* pointerBlue);
int PrintColor(float r, float g, float b);
void TurnOffLights();
void LineDetector ();

#endif