
#ifndef SUPA_RUNTIME_H
#define SUPA_RUNTIME_H

#include <Servo.h>

#include "delay.h"
#include "stime.h"
#include "led.h"
#include "servo_we.h"

class Runtime
{
   public:
      constexpr static const int NHOLES = 9;
      constexpr static const int SERVO_PER_HOLE = 125;
      constexpr static const int SERVO_START_OFFSET = 700;
   
   
      void setup( DelayFromPin* delay, TimeFromEeprom* time, StatusToLed* led, ServoWE* servo, int pin_button );
      void loop();
      int calculate_hole_angle( int hole_index ) const ;
   protected:
      void _servo_drive(int position, bool direct );
      void logic();
      
      STimer timer_print;
      DelayFromPin* delay;
      TimeFromEeprom* time;
      StatusToLed* led;      
      ServoWE* servo;
      int pin_button; 
      int current_hole;
};


#endif
