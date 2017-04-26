
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_delay.h"
DEFINE_FAKE_VOID_FUNC( DelayFromPin__setup,  DelayFromPin*, int, int, int );
void DelayFromPin::setup(int pin_1, int pin_2, int pin_4)  { DelayFromPin__setup(  this, pin_1, pin_2, pin_4 ); }
DEFINE_FAKE_VOID_FUNC( DelayFromPin__loop,  DelayFromPin* );
void DelayFromPin::loop()  { DelayFromPin__loop(  this ); }
DEFINE_FAKE_VALUE_FUNC( int, DelayFromPin__get_delay_min,  DelayFromPin* );
int DelayFromPin::get_delay_min()  { return DelayFromPin__get_delay_min(  this ); }
