#include <Wire.h>
#include "IMU.h"

//MPU9250 CONSTANTS

#define MPU9250_ADDRESS 0x68
#define GYRO_CONFIG_REG 0x1B

#define GYRO_X_REG 0x43
#define GYRO_Y_REG 0x45
#define GYRO_Z_REG 0x47

#define ACC_X_REG 0x3B
#define ACC_Y_REG 0x3D
#define ACC_Z_REG 0x3F

iMU::iMU(bool displayMsg) {
  
}

void iMU::Begin(){
  Serial.begin(115200);
  Wire.begin();
}

void iMU::ConfigureGyro(){
  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(GYRO_CONFIG_REG);
  Wire.write(0b00010000);
  Wire.endTransmission();
}

float iMU::ReadGyro(){
  
  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(GYRO_X_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_ADDRESS, 2);
  while(Wire.available() < 2);

  GYRO_X_H = Wire.read();
  GYRO_X_L = Wire.read();

  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(GYRO_Y_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_ADDRESS, 2);
  while(Wire.available() < 2);

  GYRO_Y_H = Wire.read();
  GYRO_Y_L = Wire.read();

  GYRO_X_H = GYRO_X_H << 8;
  GYRO_X = (GYRO_X_H + GYRO_X_L)/32.8;
  
  GYRO_Y_H = GYRO_Y_H << 8;
  GYRO_Y = (GYRO_Y_H + GYRO_Y_L)/32.8;

  return GYRO_X;

}

void iMU::CalculateTilt(){
  
  static bool init_flag;
  static unsigned long t_start;
  static unsigned long t_fin;
  unsigned long delta_t;

  ACC_THETA_X = (-180/3.141)*atan((ACC_Y)/(ACC_Z));
  ACC_THETA_Y = (180/3.141)*atan((ACC_X)/(ACC_Z));

  if(init_flag != true){
    t_start = millis();
    init_flag = true;

    THETA_X = ACC_THETA_X;
    THETA_Y = ACC_THETA_Y;
  }
  t_fin = millis();
  // Using Accelerometer

  delta_t = (t_fin - t_start);

  GYRO_DTHETA_X = 0.001*((GYRO_X-GYRO_CAL_X)*delta_t);
  GYRO_DTHETA_Y = 0.001*((GYRO_Y-GYRO_CAL_Y)*delta_t);

  THETA_X += 1*GYRO_DTHETA_X + 0.000*(ACC_THETA_X - ACC_CAL_X);
  THETA_Y += 1*GYRO_DTHETA_Y + 0.000*(ACC_THETA_Y - ACC_CAL_Y);

  t_start = millis();
}

void iMU::PrintResult(){
  Serial.print(THETA_X);
  Serial.print(" ");
  Serial.print(THETA_Y);
  Serial.print(" ");
  Serial.print(ACC_THETA_X);
  Serial.print(" ");
  Serial.println(ACC_THETA_Y);
  
}

void iMU::Calibrate(){
  for(int i = 0; i<5000; i++){
   ReadGyro();
   ReadAccelerometer();
   
   GYRO_CAL_X = GYRO_CAL_X + GYRO_X;
   GYRO_CAL_Y = GYRO_CAL_Y + GYRO_Y;

   ACC_THETA_X = (-180/3.141)*atan((ACC_Y)/(ACC_Z));
   ACC_THETA_Y = (180/3.141)*atan((ACC_X)/(ACC_Z));
   
   ACC_CAL_X = ACC_CAL_X + ACC_THETA_X;
   ACC_CAL_Y = ACC_CAL_Y + ACC_THETA_Y;
   
   Serial.print(GYRO_CAL_X);
   Serial.print(" ");
   Serial.print(GYRO_CAL_Y);
   Serial.print(" ");
   Serial.println(ACC_CAL_X);
    
  }
  
  GYRO_CAL_X = GYRO_CAL_X/5000.0;
  GYRO_CAL_Y = GYRO_CAL_Y/5000.0;
  
  ACC_CAL_X = ACC_CAL_X/5000;
  ACC_CAL_Y = ACC_CAL_Y/5000;
  ACC_CAL_Z = ACC_CAL_Z/5000;

  Serial.print(GYRO_CAL_X);
  Serial.print(" ");
  Serial.print(GYRO_CAL_Y);
  Serial.print(" ");
  Serial.println(ACC_CAL_X);
  delay(2000);
}

void iMU::ConfigureAccelerometer(){
  
}

float iMU::ReadAccelerometer(){
  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(ACC_X_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_ADDRESS, 2);
  while(Wire.available() < 2);

  ACC_X_H = Wire.read();
  ACC_X_L = Wire.read();

  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(ACC_Y_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_ADDRESS, 2);
  while(Wire.available() < 2);

  ACC_Y_H = Wire.read();
  ACC_Y_L = Wire.read();
  
  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(ACC_Z_REG);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_ADDRESS, 2);
  while(Wire.available() < 2);

  ACC_Z_H = Wire.read();
  ACC_Z_L = Wire.read();
  
  ACC_X_H = ACC_X_H << 8;
  ACC_X = (float(ACC_X_H) + float(ACC_X_L))/16384;

  ACC_Y_H = ACC_Y_H << 8;
  ACC_Y = (float(ACC_Y_H) + float(ACC_Y_L))/16384;

  ACC_Z_H = ACC_Z_H << 8;
  ACC_Z = -1*(float(ACC_Z_H) + float(ACC_Z_L))/16384;

  return ACC_X;
  
}
