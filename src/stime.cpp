#include <avr/eeprom.h>
#include <util/crc16.h>

#include "stime.h"
#include "serial.h"


void TimeFromEeprom::setup()
{
   eeprom_read_block( &this->eeprom, EEPROM_ADDR,  sizeof(EepromData) );
   uint16_t crc_calc  = this->calculate_crc();
   if (crc_calc != this->eeprom.crc )
   {
      serial_print("Invalid eeprom content. Marking as time invalid.\n");
      this->eeprom.time = TIME_INVALID;
      this->eeprom_save();
   }
   this->timer.reset();

}

uint16_t TimeFromEeprom::get_time()
{
   return this->eeprom.time;
}


bool TimeFromEeprom::loop()
{
   if (this->eeprom.time == TIME_INVALID )
      return false;
   
   if ( this->timer.check( EEPROM_WRITE_THRESHOLD_MINS*60*1000 ) == false )
      return false;
   
   this->timer.reset_with_carry( EEPROM_WRITE_THRESHOLD_MINS*60*1000 );
   this->eeprom.time += EEPROM_WRITE_THRESHOLD_MINS;
   this->eeprom_save();
   return true;
}


void TimeFromEeprom::reset()
{
   this->eeprom.time = 0;
   this->eeprom_save();
}

void TimeFromEeprom::eeprom_save()
{
   this->eeprom.crc = this->calculate_crc();
   eeprom_update_block( (const char*)(&this->eeprom), EEPROM_ADDR, sizeof(EepromData) );

}


uint16_t TimeFromEeprom::calculate_crc( ) const
{
   uint16_t crc_ret = 0xFFEE;
   const char* eeprom_array = (const char*)(&this->eeprom);
   int calc_size = sizeof(EepromData) - sizeof(uint16_t);
   for ( int cloop = 0; cloop < calc_size; cloop ++ )
   {
      crc_ret = _crc16_update( crc_ret , eeprom_array[cloop] );
   }
   return crc_ret;
}

