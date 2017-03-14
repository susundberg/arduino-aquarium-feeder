#ifndef mock_serial_H
#define mock_serial_H

/*
    Auto-generated mock file for FFF.
*/

#include <string.h>
#include "fff.h"

FAKE_VOID_FUNC(serial_setup, const char*);
FAKE_VALUE_FUNC(char*, serial_receive, int*);
FAKE_VALUE_FUNC(int, serial_receive_number, int, int);
FAKE_VOID_FUNC(serial_print_int, char*, int);
FAKE_VOID_FUNC(serial_print, char*);

#define RESET_MOCK_SERIAL() \
    RESET_FAKE(serial_setup); \
    RESET_FAKE(serial_receive); \
    RESET_FAKE(serial_receive_number); \
    RESET_FAKE(serial_print_int); \
    RESET_FAKE(serial_print);

#endif // mock_serial_H
