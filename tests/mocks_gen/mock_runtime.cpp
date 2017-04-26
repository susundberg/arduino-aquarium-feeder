
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_runtime.h"
DEFINE_FAKE_VOID_FUNC( Runtime__setup,  Runtime*, DelayFromPin*, TimeFromEeprom*, StatusToLed*, ServoWE*, int );
void Runtime::setup(DelayFromPin* delay, TimeFromEeprom* time, StatusToLed* led, ServoWE* servo, int pin_button)  { Runtime__setup(  this, delay, time, led, servo, pin_button ); }
DEFINE_FAKE_VOID_FUNC( Runtime__loop,  Runtime* );
void Runtime::loop()  { Runtime__loop(  this ); }
DEFINE_FAKE_VALUE_FUNC( int, Runtime__calculate_hole_angle, const Runtime*, int );
int Runtime::calculate_hole_angle(int hole_index) const { return Runtime__calculate_hole_angle(  this, hole_index ); }
DEFINE_FAKE_VOID_FUNC( Runtime___servo_drive,  Runtime*, int, bool );
void Runtime::_servo_drive(int position, bool direct)  { Runtime___servo_drive(  this, position, direct ); }
DEFINE_FAKE_VOID_FUNC( Runtime__logic,  Runtime* );
void Runtime::logic()  { Runtime__logic(  this ); }
