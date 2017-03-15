
#ifndef SUPA_RUNTIME_H
#define SUPA_RUNTIME_H

#include <stdint.h>
#include <stdbool.h>

#define EEPROM_WRITE_THRESHOLD_MIN 16
#define CRC_DEFAULT_SEED (0xFFFFL)
#define EEPROM_ADDR_RUNTIME ((void*)0x10)


typedef struct
{
   int ndays;
   int nholes;
   int time_loop;
   uint16_t crc; 
} RuntimeEeprom;


void runtime_load( RuntimeEeprom* runtime );
void runtime_save( RuntimeEeprom* runtime );
int  runtime_get_hole( RuntimeEeprom* runtime );
void runtime_time_pass( RuntimeEeprom* runtime, int done_secs );
bool runtime_valid( RuntimeEeprom* runtime );
void runtime_setup(RuntimeEeprom* runtime);
void runtime_stop(RuntimeEeprom* runtime);
void runtime_print(const RuntimeEeprom* runtime);


#endif
