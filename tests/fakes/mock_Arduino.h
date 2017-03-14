#ifndef mock_Arduino_H
#define mock_Arduino_H

/*
    Auto-generated mock file for FFF.
*/

#include <string.h>
#include "fff.h"


FAKE_VOID_FUNC(pinMode, uint8_t, uint8_t);
FAKE_VOID_FUNC(digitalWrite, uint8_t, uint8_t);
FAKE_VOID_FUNC(delay, unsigned long);

#define RESET_MOCK_ARDUINO() \
    RESET_FAKE(pinMode); \
    RESET_FAKE(digitalWrite); \
    RESET_FAKE(delay);

#endif // mock_Arduino_H
