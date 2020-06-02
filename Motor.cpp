#include "Motor.h"



motor::motor(int Enable, int Phase){
  _Enable = Enable;
  _Phase = Phase;
  pinMode(_Enable, OUTPUT);
  pinMode(_Phase, OUTPUT);  
}

void motor::Direction(bool Clockwise){
  digitalWrite(_Phase, Clockwise);
}

void motor::Speed(int Level){
  analogWrite(_Enable, Level);
}
