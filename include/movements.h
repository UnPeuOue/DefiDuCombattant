#ifndef MOVEMENTS_H
#define MOVEMENTS_H


void Stop();
void Rotate(float angle, int direction);
void RotateTwoWheels(float angle);
double Compute(double kp, double ki);
void Forward(float distance);
void Dece(float currentSpeed);
void Acce(float desiredSpeed);
void RotateForward (int Color, float speedLeft);
double Compute1(double kp, double ki,double *lastime, double *errsum, float fraction);


#endif