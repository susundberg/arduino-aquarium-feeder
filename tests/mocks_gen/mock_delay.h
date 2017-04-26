
/**
This is automatically generate mock file (from /home/pauli/DEV/arduino/feeder/src/delay.h). If you wish to edit this, move this to mocks_man directory.
*/
#ifndef _AUTOMOCK_DELAY_H
#define _AUTOMOCK_DELAY_H

#include "fff.h"
#include "delay.h"

void DelayFromPin__setup(  DelayFromPin*, int, int, int );
DECLARE_FAKE_VOID_FUNC( DelayFromPin__setup,  DelayFromPin*, int, int, int );
void DelayFromPin__loop(  DelayFromPin* );
DECLARE_FAKE_VOID_FUNC( DelayFromPin__loop,  DelayFromPin* );
int DelayFromPin__get_delay_min(  DelayFromPin* );
DECLARE_FAKE_VALUE_FUNC( int, DelayFromPin__get_delay_min,  DelayFromPin* );

#endif // _AUTOMOCK_DELAY_H
