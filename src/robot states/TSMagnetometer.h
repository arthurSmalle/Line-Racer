#ifdef ARDUINO_NANO
#ifndef TS_MAGNETOMETER
#define TS_MAGNETOMETER 
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

class TSMagnetometer: public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    TSMagnetometer(){}

  protected:
    float x,y,z;

    void enter() override{
    }

    // keep looping
    void update() override{
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
     if (IMU.magneticFieldAvailable()){ 
      if (IMU.readMagneticField(x, y, z)){
	Serial.println("$$P-auto,"+String(x)+","+String(y)+","+String(z));
      } else {
	Serial.println("Failed to read magmeter");
      }
     } else {
	Serial.println("No new mag data");
	Serial.println("Mag sample rate:" + String(IMU.magneticFieldSampleRate()));
     }
     IMU.readMagneticField(x, y, z);
     Serial.println("$$P-auto,"+String(x)+","+String(y)+","+String(z));
      motor_cl_l.update();
      motor_cl_r.update();
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    StatesEnum go_next_state() override{}
};

#endif
#endif
