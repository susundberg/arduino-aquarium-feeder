

#include "catch.hpp"
#include "runtime.h"
#include "avr/eeprom.h"
#include <iostream>
#include <string.h>

class RuntimeTester: public Runtime
{
  public:
   
    void set_values( RuntimeEeprom* from )
    {
       this->eeprom = (*from);
    }
    
    void populate_values( bool valid_crc )
    {
      RuntimeEeprom values;
      
      memset( &values, 0x00, sizeof(values));
      values.ndays  = 4;
      values.nholes = 8;
      this->set_values( &values );
      if ( valid_crc )
         values.crc = this->calculate_crc();
      this->set_values( &values );
   }
}; 



TEST_CASE( "Runtime loading is crc protected", "[main]" ) 
{
   
   RuntimeTester runtime;
   fake_eeprom_reset();
   
   SECTION( "invalid crc" ) {
      runtime.populate_values( false );
      runtime.load();
      REQUIRE( runtime.valid() == false );
      
   };

   SECTION( "valid crc" ) {
      runtime.populate_values( true );
      runtime.save();
      runtime.populate_values( false );
      runtime.load();
      REQUIRE( runtime.valid() == true );
      
   };   
   
}