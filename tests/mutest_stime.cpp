#include "catch.hpp"
#include "Arduino.h"
#include "avr/eeprom.h"

#include "stime.h"


TEST_CASE( "STimer invalid eeprom", "[time]" ) 
{
  TimeFromEeprom time;
  _test_eeprom_reset();
  
  time.setup();
  int wanted = TimeFromEeprom::TIME_INVALID;
  REQUIRE( time.get_time() == wanted ); 
  time.reset();
  REQUIRE( time.get_time() == 0); 
  time.setup();
  REQUIRE( time.get_time() == 0); 
}

TEST_CASE( "STimer functionality", "[time]" ) 
{
  TimeFromEeprom time;
  time.reset();
  time.setup();
  
  SECTION("Time elapses")
  {
    int changed = 0;
    for ( int minutes = 0; minutes < 600 + 1; minutes ++ )
    {
       millis_fake.return_val = minutes * 6 * 1000;
       changed += time.loop();
    }
    int assumed = 60 / TimeFromEeprom::EEPROM_WRITE_THRESHOLD_MINS;
    REQUIRE( changed == assumed );
    REQUIRE( time.get_time() == 60 ); 
  }
  
  memset( &time, 0x00, sizeof(time));
  time.setup(); // let it load from eeprom
  REQUIRE( time.get_time() == 60 ); 
  
  _test_eeprom_reset(); 
  
  memset( &time, 0x00, sizeof(time));
  time.setup(); // let it load from eeprom
  int wanted = TimeFromEeprom::TIME_INVALID;
  REQUIRE( time.get_time() == wanted );   
}

