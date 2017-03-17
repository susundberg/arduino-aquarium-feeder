
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_runtime.h"
DEFINE_FAKE_VOID_FUNC( Runtime__Runtime,  Runtime* );
 Runtime::Runtime()  { Runtime__Runtime(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__Runtime_DTOR,  Runtime* );
 Runtime::~Runtime()  { Runtime__Runtime_DTOR(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__setup,  Runtime* );
void Runtime::setup()  { Runtime__setup(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__load,  Runtime* );
void Runtime::load()  { Runtime__load(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__save,  Runtime* );
void Runtime::save()  { Runtime__save(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__stop,  Runtime* );
void Runtime::stop()  { Runtime__stop(  this ); }
DEFINE_FAKE_VALUE_FUNC( bool, Runtime__time_pass,  Runtime*, int );
bool Runtime::time_pass(int done_secs)  { return Runtime__time_pass(  this, done_secs ); }
DEFINE_FAKE_VALUE_FUNC( bool, Runtime__valid, const Runtime* );
bool Runtime::valid() const { return Runtime__valid(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__print, const Runtime* );
void Runtime::print() const { Runtime__print(  this ); }
DEFINE_FAKE_VALUE_FUNC( int, Runtime__get_time, const Runtime* );
int Runtime::get_time() const { return Runtime__get_time(  this ); }
DEFINE_FAKE_VOID_FUNC( Runtime__get_status, const Runtime*, int*, bool* );
void Runtime::get_status(int* holes, bool* done) const { Runtime__get_status(  this, holes, done ); }
DEFINE_FAKE_VALUE_FUNC( uint16_t, Runtime__calculate_crc, const Runtime* );
uint16_t Runtime::calculate_crc() const { return Runtime__calculate_crc(  this ); }
