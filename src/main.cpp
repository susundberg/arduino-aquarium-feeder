/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>

#include "serial.h"
#include "crc.h"

#define EEPROM_ADDR_RUNTIME 0x10



typedef struct
{
   int ndays;
   int nholes;
   int time_loop;
} RuntimeEeprom;


static RuntimeEeprom RUNTIME;
static Servo servo;  

void runtime_load( RuntimeEeprom* runtime );
void runtime_save( RuntimeEeprom* runtime );
int  runtime_get_hole( RuntimeEeprom* runtime );
void runtime_time_pass( RuntimeEeprom* runtime, int done_secs );
bool runtime_valid( RuntimeEeprom* runtime );
void servo_set_hole( int index );

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  serial_setup();
  servo.attach( 9 );
  runtime_load( &RUNTIME );
  
  if ( runtime_valid( &RUNTIME ) == true )
  {
     int curr_hole = runtime_get_hole( &RUNTIME );
     servo_set_hole( curr_hole );
  }
}



void servo_set_hole( int index )
{
   static int old_value = 0xFF;
   static const int n_steps = 20;
   
   int target_value = index * 125 + 700;

   if (target_value < 0 )
      target_value = 0;
   if (target_value > 1650)
      target_value = 1650;

   // If value has not changed, do nothing
   if ( old_value == target_value )
      return;
   
   // On the first round we just set the value on what it supposed to be
   if ( old_value == 0xFF )
   {
      servo.write( target_value / 10 );
      old_value = target_value ;
      return;
   }
   
   // otherwise make 'smooth' transition
   int value_inc = ( target_value - old_value )/(n_steps-1);
   for ( int loop_steps = 0; loop_steps < n_steps; loop_steps ++ )
   {
      int value = old_value + value_inc*loop_steps;
      servo.write( (value + 5) / 10 );
      delay( 10 );
   }
   
   old_value = target_value;
}




void eeprom_write( const unsigned int addr_start, const char* data, int size)
{
   for ( int loop = 0; loop < size; loop ++ )
   {
      EEPROM.write( addr_start + loop, data[loop] );
   }
}
void eeprom_read(  const unsigned int addr_start, char* data, int size )
{
   for ( int loop = 0; loop < size; loop ++ )
   {
      data[loop] = EEPROM.read( addr_start + loop );
   }
}



void runtime_print(RuntimeEeprom* runtime  )
{
   if ( runtime->ndays == 0)
   {
      Serial.write("RuntimeEeprom: not valid.\n");
      return;
   }
   Serial.write("RuntimeEeprom: valid.\n");
   
   serial_print_int( "   ndays: " , runtime->ndays );   
   serial_print_int( "   nholes: ", runtime->nholes);
   serial_print_int( "   tloop: " , runtime->time_loop );
   
}


bool runtime_valid( RuntimeEeprom* runtime  )
{
   return ( runtime->ndays > 0 && runtime->ndays < 60 );
}

void runtime_time_pass(RuntimeEeprom* runtime, int done_secs)
{
   static int done_secs_acc = 0;
   
   done_secs_acc += done_secs;
   
   if (done_secs_acc > EEPROM_WRITE_THRESHOLD )
   {
      int inc_min = (done_secs_acc / 60);
      runtime->time_loop += (done_secs_acc / 60);
      runtime_save( runtime );
      done_secs_acc -= inc_min * 60;
   }
   
}

void runtime_save( RuntimeEeprom* runtime  )
{
   eeprom_write( EEPROM_ADDR_RUNTIME, (const char*)runtime, sizeof(RuntimeEeprom) );
   long crc_full = crc_calculate( CRC_DEFAULT_SEED, (const char*)runtime, sizeof(RuntimeEeprom) );
   eeprom_write( EEPROM_ADDR_RUNTIME + sizeof(RuntimeEeprom), (const char*)(&crc_full), sizeof(long) );
}

void runtime_load( RuntimeEeprom* runtime )
{
   eeprom_read( EEPROM_ADDR_RUNTIME, ( char*)runtime, sizeof(RuntimeEeprom) );
   long crc_calc   = 0;
   eeprom_read( EEPROM_ADDR_RUNTIME + sizeof(RuntimeEeprom), ( char*)(&crc_calc), sizeof(long) );
   
   long crc_eeprom = crc_calculate( CRC_DEFAULT_SEED, (const char*)runtime, sizeof(RuntimeEeprom) );
   if (crc_calc != crc_eeprom)
   {
      Serial.write("Invalid eeprom content -> not starting.");
      memset( &runtime, 0x00, sizeof(runtime));
   }
   runtime_print(runtime);
}

void runtime_stop(  RuntimeEeprom* runtime  )
{
   memset( &runtime, 0x00, sizeof(runtime));
   runtime_save(runtime);
}


void runtime_setup(RuntimeEeprom* runtime)
{
   Serial.write("Input number of days to stay\n");
   int ndays = serial_receive_number( 1, 255);

   Serial.write("Input number holes filled\n");
   int nholes = serial_receive_number( 1, 9 );
   

   float holes_per_day = (float)nholes / (float)ndays ;
   float sleep_mins = (24.0f * 60.0f) / holes_per_day ;
   
   Serial.write("This means ");
   Serial.print( holes_per_day);
   Serial.write( " holes per day\n -> sleep of ");
   Serial.print( sleep_mins );
   Serial.write( " minutes between holes\n");
   
   runtime->time_loop = 0;
   runtime->ndays     = ndays;
   runtime->nholes    = nholes;
   
   runtime_save(runtime);
}


bool handle_receive( int sleep_time_ms )
{
   for ( int loop = 0; loop < sleep_time_ms; loop += 100 )
   {
        int input_n = 0;
        char* input = serial_receive( &input_n );
        
        delay( 100 );
        if (input == NULL )
           continue;
        
        if (strcmp( input, "setup") == 0 )
        {
           runtime_setup( &RUNTIME );
           return true;
        }
        if (strcmp( input, "stop") == 0 )
        {
           runtime_stop( &RUNTIME );
           return true;
        }
        else
        {
           Serial.write("Invalid command '");
           Serial.write( input );
           Serial.write("'\n");
           Serial.write(">");
        }
   }
   return false;
}

void toggle_led()
{
  static bool state = 0;
  digitalWrite(LED_BUILTIN, state);
  state = !state;
}

void loop()
{
  toggle_led();
  
  if ( runtime_valid( &RUNTIME ) == false )
  {
     handle_receive( 500 );
     return;
  }
  
  // Ok we have valid structure
  int curr_hole = runtime_get_hole( &RUNTIME );
  servo_set_hole( curr_hole );
  
  if ( curr_hole == (RUNTIME.nholes-1) )
  {
     Serial.write("End position reached, clearing the configuration.");
     runtime_stop( &RUNTIME );
  }
  
  // wait for one minute
  for ( int sec_loop= 0; sec_loop < 60; sec_loop ++ )
  {
     handle_receive( 1000 );
     toggle_led();
  }   
  runtime_time_pass( &RUNTIME, 60 );
}  
