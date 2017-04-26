
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_stime.h"
DEFINE_FAKE_VOID_FUNC( TimeFromEeprom__setup,  TimeFromEeprom* );
void TimeFromEeprom::setup()  { TimeFromEeprom__setup(  this ); }
DEFINE_FAKE_VALUE_FUNC( bool, TimeFromEeprom__loop,  TimeFromEeprom* );
bool TimeFromEeprom::loop()  { return TimeFromEeprom__loop(  this ); }
DEFINE_FAKE_VOID_FUNC( TimeFromEeprom__reset,  TimeFromEeprom* );
void TimeFromEeprom::reset()  { TimeFromEeprom__reset(  this ); }
DEFINE_FAKE_VALUE_FUNC( uint16_t, TimeFromEeprom__get_time,  TimeFromEeprom* );
uint16_t TimeFromEeprom::get_time()  { return TimeFromEeprom__get_time(  this ); }
DEFINE_FAKE_VOID_FUNC( TimeFromEeprom__eeprom_save,  TimeFromEeprom* );
void TimeFromEeprom::eeprom_save()  { TimeFromEeprom__eeprom_save(  this ); }
DEFINE_FAKE_VALUE_FUNC( uint16_t, TimeFromEeprom__calculate_crc, const TimeFromEeprom* );
uint16_t TimeFromEeprom::calculate_crc() const { return TimeFromEeprom__calculate_crc(  this ); }
