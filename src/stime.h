#ifndef SUPA_STIME_H
#define SUPA_STIME_H

#include <Arduino.h>
#include "stimer.h"

class TimeFromEeprom
{
   public:
      
     constexpr static void* const  EEPROM_ADDR = (void*)0x10;
     constexpr static const uint32_t TIME_INVALID = 0xFFFF;
     constexpr static const unsigned long EEPROM_WRITE_THRESHOLD_MINS = 15; // 15min
  
     void setup(); /// Loads the time from eeprom
     bool loop();  /// @returns true if the time on eeprom has changed
     void reset(); /// Reset the elapsed time on eeprom to zero
     uint16_t get_time(); /// @returns minutes from last reset on eeprom, or 0xFFFFFFFF if invalid
  
  protected:
     
     typedef struct 
     {
       uint16_t time;
       uint16_t crc;
     } EepromData;
     
     EepromData eeprom;
     STimer timer;
     
        
     void eeprom_save();
     uint16_t calculate_crc() const ;
};

#endif