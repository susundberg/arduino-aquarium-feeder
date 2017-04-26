
/**
This is automatically generate mock file (from /home/pauli/DEV/arduino/feeder/src/runtime.h). If you wish to edit this, move this to mocks_man directory.
*/
#ifndef _AUTOMOCK_RUNTIME_H
#define _AUTOMOCK_RUNTIME_H

#include "fff.h"
#include "runtime.h"

void Runtime__setup(  Runtime*, DelayFromPin*, TimeFromEeprom*, StatusToLed*, ServoWE*, int );
DECLARE_FAKE_VOID_FUNC( Runtime__setup,  Runtime*, DelayFromPin*, TimeFromEeprom*, StatusToLed*, ServoWE*, int );
void Runtime__loop(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__loop,  Runtime* );
int Runtime__calculate_hole_angle( const Runtime*, int );
DECLARE_FAKE_VALUE_FUNC( int, Runtime__calculate_hole_angle, const Runtime*, int );
void Runtime___servo_drive(  Runtime*, int, bool );
DECLARE_FAKE_VOID_FUNC( Runtime___servo_drive,  Runtime*, int, bool );
void Runtime__logic(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__logic,  Runtime* );

#endif // _AUTOMOCK_RUNTIME_H
