
/**
This is automatically generate mock file (from /home/pauli/DEV/arduino/feeder/src/stime.h). If you wish to edit this, move this to mocks_man directory.
*/
#ifndef _AUTOMOCK_STIME_H
#define _AUTOMOCK_STIME_H

#include "fff.h"
#include "stime.h"

void TimeFromEeprom__setup(  TimeFromEeprom* );
DECLARE_FAKE_VOID_FUNC( TimeFromEeprom__setup,  TimeFromEeprom* );
bool TimeFromEeprom__loop(  TimeFromEeprom* );
DECLARE_FAKE_VALUE_FUNC( bool, TimeFromEeprom__loop,  TimeFromEeprom* );
void TimeFromEeprom__reset(  TimeFromEeprom* );
DECLARE_FAKE_VOID_FUNC( TimeFromEeprom__reset,  TimeFromEeprom* );
uint16_t TimeFromEeprom__get_time(  TimeFromEeprom* );
DECLARE_FAKE_VALUE_FUNC( uint16_t, TimeFromEeprom__get_time,  TimeFromEeprom* );
void TimeFromEeprom__eeprom_save(  TimeFromEeprom* );
DECLARE_FAKE_VOID_FUNC( TimeFromEeprom__eeprom_save,  TimeFromEeprom* );
uint16_t TimeFromEeprom__calculate_crc( const TimeFromEeprom* );
DECLARE_FAKE_VALUE_FUNC( uint16_t, TimeFromEeprom__calculate_crc, const TimeFromEeprom* );

#endif // _AUTOMOCK_STIME_H
