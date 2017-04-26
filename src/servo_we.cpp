
#include "servo_we.h"


void ServoWE::setup(int pwm_pin, int enable_pin, int steps, int min_angle, int max_angle )
{
  this->current_position = -1;
  this->pin_enable = enable_pin;
  this->max_angle = max_angle;
  this->min_angle = min_angle;
  this->n_steps = steps;
  
  this->servo.attach( pwm_pin );
  pinMode( this->pin_enable, OUTPUT );
  digitalWrite(  this->pin_enable, LOW );
}
  
void ServoWE::set_position(int angle, bool direct)
{

   if ( angle < this->min_angle )
      angle = this->min_angle ;
   if (angle > this->max_angle)
      angle = this->max_angle;

   // If value has not changed, do nothing
   if ( this->current_position == angle )
      return;
   
   digitalWrite( this->pin_enable, HIGH );
   delay(10);
   
  
   if ( direct == true )
   {
      this->servo.write( angle / 10 );
   }
   else
   {
      // otherwise make 'smooth' transition
      int value_inc = ( angle - this->current_position  )/(n_steps-1);
      for ( int loop_steps = 0; loop_steps < n_steps; loop_steps ++ )
      {
         int value = this->current_position  + value_inc*loop_steps;
         this->servo.write( (value + 5) / 10 );
         delay( 10 );
      }
   }
   delay( 200 + direct*5000 );
   digitalWrite(  this->pin_enable, LOW );
   this->current_position = angle;
}