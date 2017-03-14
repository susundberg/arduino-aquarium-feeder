#ifndef mock_main_H
#define mock_main_H

/*
    Auto-generated mock file for FFF.
*/

#include <string.h>
#include "fff.h"

DEFINE_FFF_GLOBALS;


FAKE_VOID_FUNC(loop);
FAKE_VOID_FUNC(setup);

#define RESET_MOCK_MAIN() \
    RESET_FAKE(loop); \
    RESET_FAKE(setup);

#endif // mock_main_H
