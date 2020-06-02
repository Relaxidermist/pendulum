#include <PID_v1.h>
#include "IMU.h"
#include "Motor.h"

//PID VARS

double MotorPWM = 0; 
double TargetTheta = 0;
double kp = 0.5;
double ki = 0.5;
double kd = 0.5;

//DEFINE PINS

#define PHASELEFT 2
#define ENABLELEFT 9

// Instantiate an instance of the IMU class
iMU imu;

// Instantiate an instance of the PID class
PID myPID(&imu.THETA_Y,&MotorPWM, &TargetTheta, kp, ki, kd, DIRECT);

// Instantiate motor objects
motor leftmotor(ENABLELEFT, PHASELEFT);

void setup() {

 leftmotor.Speed(0);
 leftmotor.Direction(true);
 
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
