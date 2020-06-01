#include <PID_v1.h>
#include "IMU.h"

//PID VARS

double MotorPWM = 0; 
double TargetTheta = 0;
double kp = 0.5;
double ki = 0.5;
double kd = 0.5;

// Instantiate an instance of the IMU class

iMU imu;

// Instantiate an instance of the PID class

PID myPID(&imu.THETA_Y,&MotorPWM, &TargetTheta, kp, ki, kd, DIRECT);

void setup() {
 myPID.SetMode(AUTOMATIC);
 
  // put your setup code here, to run once:
 imu.Begin();

 imu.ConfigureGyro();
 imu.ConfigureAccelerometer();
 imu.Calibrate();
}

void loop() {
  imu.ReadAccelerometer();
  imu.ReadGyro();
  imu.CalculateTilt();
  myPID.Compute();
  imu.PrintResult();
}
