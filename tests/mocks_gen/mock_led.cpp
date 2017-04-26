
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_led.h"
DEFINE_FAKE_VOID_FUNC( StatusToLed__setup,  StatusToLed*, int );
void StatusToLed::setup(int pin)  { StatusToLed__setup(  this, pin ); }
DEFINE_FAKE_VOID_FUNC( StatusToLed__loop,  StatusToLed* );
void StatusToLed::loop()  { StatusToLed__loop(  this ); }
DEFINE_FAKE_VOID_FUNC( StatusToLed__set_status,  StatusToLed*, int );
void StatusToLed::set_status(int blinks)  { StatusToLed__set_status(  this, blinks ); }
