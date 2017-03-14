#ifndef mock_runtime_H
#define mock_runtime_H

/*
    Auto-generated mock file for FFF.
*/

#include <string.h>
#include "fff.h"


FAKE_VOID_FUNC(runtime_load, RuntimeEeprom*);
FAKE_VOID_FUNC(runtime_save, RuntimeEeprom*);
FAKE_VALUE_FUNC(int, runtime_get_hole, RuntimeEeprom*);
FAKE_VOID_FUNC(runtime_time_pass, RuntimeEeprom*, int);
FAKE_VALUE_FUNC(bool, runtime_valid, RuntimeEeprom*);
FAKE_VOID_FUNC(runtime_setup, RuntimeEeprom*);
FAKE_VOID_FUNC(runtime_stop, RuntimeEeprom*);
FAKE_VOID_FUNC(runtime_print, RuntimeEeprom*);

#define RESET_MOCK_RUNTIME() \
    RESET_FAKE(runtime_load); \
    RESET_FAKE(runtime_save); \
    RESET_FAKE(runtime_get_hole); \
    RESET_FAKE(runtime_time_pass); \
    RESET_FAKE(runtime_valid); \
    RESET_FAKE(runtime_setup); \
    RESET_FAKE(runtime_stop); \
    RESET_FAKE(runtime_print);

#endif // mock_runtime_H
