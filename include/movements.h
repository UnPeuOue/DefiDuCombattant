#ifndef MOVEMENTS_H
#define MOVEMENTS_H


void Stop();
void Rotate(float angle, int direction);
void RotateTwoWheels(float angle);
double Compute(double kp, double ki);
void Forward(float distance);
void Dece(float currentSpeed);
void Acce(float desiredSpeed);



#endif