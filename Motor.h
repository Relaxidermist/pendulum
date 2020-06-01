#ifndef Motor
#define Motor

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Motor {
  public:
  //Constructor
  Motor();
  void Begin();

  private:
  
}

#endif
