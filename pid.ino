#include <PID_v1.h>
#include "IMU.h"

iMU imu(false);

//PID VARS

double MotorPWM, TargetTheta;
double kp = 0.5;
double ki = 0.5;
double kd = 0.5;



PID myPID(&imu.THETA_Y,&MotorPWM, &TargetTheta, 0.5, 0.5, 0.5, DIRECT);

void setup() {
 myPID.SetMode(AUTOMATIC);

 TargetTheta = 0;
 
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
