
/**
This is automatically generate mock file (from /home/pauli/DEV/arduino/feeder/src/runtime.h). If you wish to edit this, move this to mocks_man directory.
*/
#ifndef _AUTOMOCK_RUNTIME_H
#define _AUTOMOCK_RUNTIME_H

#include "fff.h"
#include "runtime.h"

void Runtime__Runtime(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__Runtime,  Runtime* );
void Runtime__Runtime_DTOR(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__Runtime_DTOR,  Runtime* );
void Runtime__setup(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__setup,  Runtime* );
void Runtime__load(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__load,  Runtime* );
void Runtime__save(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__save,  Runtime* );
void Runtime__stop(  Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__stop,  Runtime* );
bool Runtime__time_pass(  Runtime*, int );
DECLARE_FAKE_VALUE_FUNC( bool, Runtime__time_pass,  Runtime*, int );
bool Runtime__valid( const Runtime* );
DECLARE_FAKE_VALUE_FUNC( bool, Runtime__valid, const Runtime* );
void Runtime__print( const Runtime* );
DECLARE_FAKE_VOID_FUNC( Runtime__print, const Runtime* );
int Runtime__get_time( const Runtime* );
DECLARE_FAKE_VALUE_FUNC( int, Runtime__get_time, const Runtime* );
void Runtime__get_status( const Runtime*, int*, bool* );
DECLARE_FAKE_VOID_FUNC( Runtime__get_status, const Runtime*, int*, bool* );
uint16_t Runtime__calculate_crc( const Runtime* );
DECLARE_FAKE_VALUE_FUNC( uint16_t, Runtime__calculate_crc, const Runtime* );

#endif // _AUTOMOCK_RUNTIME_H
