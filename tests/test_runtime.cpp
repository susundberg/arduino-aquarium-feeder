

#include "catch.hpp"
#include <iostream>
#include <string.h>
#include "Arduino.h"

#include "runtime.h"

#include "mock_servo_we.h"
#include "mock_stime.h"
#include "mock_delay.h"
   
void run_loop(Runtime* runtime, int nsecs )
{
   for ( int loop = 0; loop < nsecs*10; loop ++ )
   {
      runtime->loop();
      millis_fake.return_val += 100;
      
   }
}


   
TEST_CASE( "Runtime loading is crc protected", "[runtime]" ) 
{
   DelayFromPin delay;
   TimeFromEeprom time;
   StatusToLed led;
   ServoWE servo;
   Runtime runtime;
   ARDUINO_TEST.hookup();
   
   RESET_FAKE(millis);
   RESET_FAKE(ServoWE__set_position);
   RESET_FAKE(TimeFromEeprom__get_time);
   RESET_FAKE(DelayFromPin__get_delay_min);
   runtime.setup( &delay, &time, &led, &servo, 1 );
   
   ARDUINO_TEST.pin_value[ 1 ] = 1;
   
   SECTION("Run with invalid eeprom")
   {
      TimeFromEeprom__get_time_fake.return_val = TimeFromEeprom::TIME_INVALID;
      run_loop( &runtime, 5 );
      REQUIRE( ServoWE__set_position_fake.call_count == 0 );
   }
   
   SECTION("Run with delay 00")
   {
      DelayFromPin__get_delay_min_fake.return_val = 00;
      run_loop( &runtime, 5 );
      REQUIRE( ServoWE__set_position_fake.call_count == 1 );
      REQUIRE( ServoWE__set_position_fake.arg2_val == true );
      REQUIRE( ServoWE__set_position_fake.arg1_val == runtime.calculate_hole_angle(-1) );
      
      run_loop( &runtime, 30 );
      REQUIRE( ServoWE__set_position_fake.arg1_val == runtime.calculate_hole_angle(0) );
      REQUIRE( ServoWE__set_position_fake.arg2_val == false );
   }
   
   SECTION("Run with delay 01")
   {
      DelayFromPin__get_delay_min_fake.return_val = 12*60;
      run_loop( &runtime, 5 );
      REQUIRE( ServoWE__set_position_fake.call_count > 0 );
      REQUIRE( ServoWE__set_position_fake.arg1_val == runtime.calculate_hole_angle(-1) );
      
      // Elapse 11h 59min
      for (int loop = 0;loop < runtime.NHOLES; loop ++ )
      {
         TimeFromEeprom__get_time_fake.return_val = loop*12*60 + 1;
         run_loop( &runtime, 3 );
         REQUIRE( ServoWE__set_position_fake.arg1_val == runtime.calculate_hole_angle(loop - 1) );
      }
      RESET_FAKE( ServoWE__set_position );
      TimeFromEeprom__get_time_fake.return_val = (runtime.NHOLES+1)*12*60 + 1;
      run_loop( &runtime, 3 );
      REQUIRE( ServoWE__set_position_fake.call_count == 0 );
      
   }
  
   
}