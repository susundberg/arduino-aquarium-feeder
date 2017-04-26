#ifndef SUPA_SERVO_H
#define SUPA_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class ServoWE
{
   public:
     /// Set the servo to action. The angles are *10 and degrees.
     void setup( int pwm_pin, int enable_pin, int steps, int min_angle, int max_angle );
     /// The @param angle is *10 degree. If @param direct is set true, then the servo will directly, no ramp, drive to position.
     void set_position( int angle, bool direct );
   
   protected:
     Servo servo;
     int current_position;
     int max_angle;
     int min_angle;
     int pin_enable;
     int n_steps;
};


#endif