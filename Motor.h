#ifndef Motor
#define Motor

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class motor {
  public:
  
    //Constructor
    motor(int Enable, int Phase);
    void Direction(bool Clockwise);
    void Speed(int Speed);

  private:

    int _Enable;
    int _Phase;
  
};

#endif
