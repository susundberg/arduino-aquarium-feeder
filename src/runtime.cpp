
#include <avr/eeprom.h>
#include <util/crc16.h>
#include <string.h>

#include "runtime.h"
#include "serial.h"

void runtime_print(const RuntimeEeprom* runtime  )
{
   if ( runtime->ndays == 0)
   {
      serial_print("RuntimeEeprom: not valid.\n");
      return;
   }
   serial_print("RuntimeEeprom: valid.\n");
   
   serial_print( "   ndays: %d\n" , runtime->ndays );   
   serial_print( "   nholes: %d\n", runtime->nholes);
   serial_print( "   tloop: %d\n" , runtime->time_loop );
   
}


bool runtime_valid( RuntimeEeprom* runtime  )
{
   return ( runtime->ndays > 0 && runtime->ndays < 60 );
}

void runtime_time_pass(RuntimeEeprom* runtime, int done_secs)
{
   static int done_mins_acc = 0;
   
   done_mins_acc += (done_secs)/60;
   
   if (done_mins_acc >= EEPROM_WRITE_THRESHOLD_MIN )
   {
      runtime->time_loop += done_mins_acc;
      runtime_save( runtime );
      done_mins_acc = 0;
   }
   
}

uint16_t runtime_crc16( const RuntimeEeprom* runtime  ) 
{
   uint16_t crc_ret = CRC_DEFAULT_SEED;
   const char* runtime_array = (const char*)runtime;
   
   int calc_size = sizeof(RuntimeEeprom) - sizeof(uint16_t);
   for ( int cloop = 0; cloop < calc_size; cloop ++ )
   {
      crc_ret = _crc16_update( crc_ret , runtime_array[cloop] );
   }
   return crc_ret;
}

void runtime_save( RuntimeEeprom* runtime  )
{
   runtime->crc = runtime_crc16( runtime );
   eeprom_update_block( (const char*)runtime, EEPROM_ADDR_RUNTIME, sizeof(RuntimeEeprom) );
}


void runtime_stop(  RuntimeEeprom* runtime  )
{
   memset( runtime, 0x00, sizeof(RuntimeEeprom));
   runtime_save(runtime);
}

void runtime_load( RuntimeEeprom* runtime )
{
   eeprom_read_block( runtime, EEPROM_ADDR_RUNTIME,  sizeof(RuntimeEeprom) );
   uint16_t crc_calc  = runtime_crc16( runtime );
   if (crc_calc != runtime->crc )
   {
      serial_print("Invalid eeprom content -> clearing.");
      runtime_stop( runtime );
   }
   runtime_print(runtime);
}

void runtime_setup(RuntimeEeprom* runtime)
{
   serial_print("Input number of days to stay\n");
   int ndays = serial_receive_number( 1, 255);

   serial_print("Input number holes filled\n");
   int nholes = serial_receive_number( 1, 9 );
   

   float holes_per_day = (float)nholes / (float)ndays ;
   float sleep_hours = (24.0f ) / holes_per_day ;
   
   serial_print("-> %f holes per day -> sleep of %f hours between holes\n", holes_per_day, sleep_hours );
   runtime->time_loop = 0;
   runtime->ndays     = ndays;
   runtime->nholes    = nholes;
   runtime_save(runtime);
}


int runtime_get_hole( RuntimeEeprom* runtime )
{
   // we proceed all the holes in given time 
   
   uint32_t time = runtime->time_loop;
   
   uint32_t time_per_hole = (runtime->ndays*24L*60L) / runtime->nholes;
   
   int index = (time/time_per_hole) - 1;
   
   return index;
}
