
#include <Arduino.h>
#include <avr/eeprom.h>
#include <util/crc16.h>
#include <string.h>

#include "runtime.h"
#include "serial.h"



void Runtime::setup( DelayFromPin* delay, TimeFromEeprom* time, StatusToLed* led, ServoWE* servo, int pin_button )
{
   this->delay = delay;
   this->time = time;
   this->led = led;
   this->servo = servo;
   
   pinMode( pin_button, INPUT_PULLUP );
   this->pin_button = pin_button;
   this->current_hole = (NHOLES);
}


void Runtime::loop()
{
   this->delay->loop();
   this->time->loop();
   logic();
   this->led->loop();
}
   
void Runtime::logic()
{
   int button_pressed = digitalRead( pin_button );
   
   if ( button_pressed == 0 )
   {
      serial_print("RESET BUTTON PRESSED. RESETING TIME.\n");
      this->time->reset();
      this->_servo_drive( -1 , true );
      return;
   }
   
   int time_bw_holes = delay->get_delay_min();
   int time_now      = (int)time->get_time();
   
   if ( time_now == time->TIME_INVALID )
   {
      serial_print("Time invalid, waiting for reset.\n");
      this->led->set_status( 6 );
      return;
   }
      
   int target_hole = -1;
   if ( time_bw_holes == 0 )
   {  // this is actually test mode where we change the target
      int secs_elapsed = (millis() / 1000);
      target_hole = (secs_elapsed/30) - 1;
   }
   else
   {
      target_hole = (time_now / time_bw_holes) - 1; // convert down
   };
   
   if ( target_hole >= (NHOLES - 1) )
   {
      serial_print("Time: %d- run done.\n", time_now );
      this->led->set_status( 5 );
      return;
   }
      
   this->led->set_status( 2 );
   
   if ( this->timer_print.check( 5000  ))
   {
      serial_print("Time: %d - target hole %d.\n", time_now, target_hole );
      this->timer_print.reset();
   }
   
   if ( target_hole != this->current_hole )
   {
      serial_print("Driving, servo to hole %d\n", target_hole );
      bool direct = ( this->current_hole == (NHOLES) );
      
      _servo_drive( target_hole, direct );
   }
   
}

int Runtime::calculate_hole_angle(int hole_index) const
{
   return SERVO_PER_HOLE*hole_index + SERVO_START_OFFSET;  
}

void Runtime::_servo_drive(int position, bool direct)
{
   this->servo->set_position(  calculate_hole_angle(position), direct );
   this->current_hole = position;
}
