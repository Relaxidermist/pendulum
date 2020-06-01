#ifndef IMU
#define IMU

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class iMU {
  public:
  //Constructor
    iMU();
  //Methods
  void Begin();
  void ConfigureGyro();
  float ReadGyro();
  void CalculateTilt();
  void PrintResult();
  void Calibrate();
  void ConfigureAccelerometer();
  float ReadAccelerometer();
  double THETA_X;
  double THETA_Y;
  
  

  private:
    int GYRO_X_H;
    int GYRO_X_L;
    int GYRO_Y_H;
    int GYRO_Y_L;
    int ACC_X_H;
    int ACC_X_L;
    int ACC_Y_H;
    int ACC_Y_L;
    int ACC_Z_H;
    int ACC_Z_L;
    int PrintCount;

    double GYRO_DTHETA_X;
    double GYRO_DTHETA_Y;
    double GYRO_X;
    double GYRO_Y;
    double ACC_X;
    double ACC_Y;
    double ACC_Z;
    double ACC_THETA_X;
    double ACC_THETA_Y;
    double delta_x;
    double GYRO_CAL_X;
    double GYRO_CAL_Y;
    double ACC_CAL_X;
    double ACC_CAL_Y;
    double ACC_CAL_Z;
  
};
#endif
