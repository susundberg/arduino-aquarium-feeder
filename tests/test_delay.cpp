
#include "catch.hpp"
#include "Arduino.h"

#include "delay.h"

   


   
TEST_CASE( "Basic stuff", "[delay]" ) 
{
 
    ARDUINO_TEST.hookup();
   
    DelayFromPin delay;
    delay.setup( 1, 2, 4 );
    
    ARDUINO_TEST.pin_value[ 1 ] = 1;
    ARDUINO_TEST.pin_value[ 2 ] = 1;
    ARDUINO_TEST.pin_value[ 4 ] = 1;
    
    SECTION("Reading value 0")
    {
       delay.loop();
       REQUIRE( delay.get_delay_min() == 0);
    }
    
    SECTION("Reading value 4")
    {
       ARDUINO_TEST.pin_value[ 4 ] = 0;
       delay.loop();
       int del = delay.get_delay_min() ;
       REQUIRE( delay.get_delay_min() == delay.delay_multiplier * 4 );
    }

    SECTION("Reading value 3")
    {
       ARDUINO_TEST.pin_value[ 2 ] = 0;
       ARDUINO_TEST.pin_value[ 1 ] = 0;
       delay.loop();
       
       REQUIRE( delay.get_delay_min() == delay.delay_multiplier * 3 );
    }

}