/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */


#include <Arduino.h>
#include <Servo.h>

#include "serial.h"
#include "runtime.h"
#include "main.h"

#define PIN_SERVO_ENABLE 8
#define N_SECONDS_IN_MINUTE (60)

static RuntimeEeprom RUNTIME;
static Servo SERVO;  



static void servo_set_hole( int index );

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode( PIN_SERVO_ENABLE, OUTPUT );
  digitalWrite( PIN_SERVO_ENABLE, LOW);
  
  serial_setup( "Feeder terminal" );
  serial_print(" * type 'setup' to configure and start\n");
  serial_print(" * type 'stop' to cancel\n" );
  
  SERVO.attach( 9 );
  
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
   
   
   digitalWrite( PIN_SERVO_ENABLE, HIGH );
   delay(10);
   
   // On the first round we just set the value on what it supposed to be
   if ( old_value == 0xFF )
   {
      SERVO.write( target_value / 10 );
      old_value = target_value ;
   }
   else
   {
      // otherwise make 'smooth' transition
      int value_inc = ( target_value - old_value )/(n_steps-1);
      for ( int loop_steps = 0; loop_steps < n_steps; loop_steps ++ )
      {
         int value = old_value + value_inc*loop_steps;
         SERVO.write( (value + 5) / 10 );
         delay( 10 );
      }
   }
   delay( 200 );
   digitalWrite( PIN_SERVO_ENABLE, LOW );
   old_value = target_value;
}


static void toggle_led()
{
  static bool state = 0;
  digitalWrite(LED_BUILTIN, state);
  state = !state;
}

bool handle_receive( RuntimeEeprom* runtime,  int sleep_time_ms )
{
   for ( int loop = 0; loop < sleep_time_ms; loop += 100 )
   {
        int input_n = 0;
        char* input = serial_receive( &input_n );
        
        toggle_led();
        
        delay( 100 );
        
        if (input == NULL )
           continue;
        
        if (strcmp( input, "setup") == 0 )
        {
           runtime_setup( runtime );
           return true;
        }
        else if (strcmp( input, "print") == 0 )
        {
           runtime_print( runtime );
        }
        else if (strcmp( input, "stop") == 0 )
        {
           runtime_stop( runtime );
           serial_print("Runtime cleared.\n");
           return true;
        }
        else if (strcmp( input, "set") == 0 )
        {
           serial_print("Input hole\n");
           int hole = serial_receive_number( 0, 10 );
           servo_set_hole( hole );
           delay(1000);
        }
        else
        {
           serial_print("Invalid command '%s'\n>", input );
        }
   }
   return false;
}


void loop()
{
  toggle_led();
  
  if ( runtime_valid( &RUNTIME ) == false )
  {
     handle_receive( &RUNTIME, 500 );
     return;
  }
  
  // Ok we have valid structure
  int curr_hole = runtime_get_hole( &RUNTIME );
  serial_print("Current time %d hole: %d\n", RUNTIME.time_loop, curr_hole );
  
  servo_set_hole( curr_hole );
  
  if ( curr_hole == (RUNTIME.nholes-1) )
  {
     serial_print("End position reached, clearing the configuration.");
     runtime_stop( &RUNTIME );
  }
  
  // wait for one minute
  bool wait_cancelled = false;
  for ( int sec_loop= 0; sec_loop < N_SECONDS_IN_MINUTE; sec_loop ++ )
  {
     wait_cancelled = handle_receive( &RUNTIME, 1000 );
     
     if ( wait_cancelled == true )
     {
        break;
     }
  }   
  
  if ( wait_cancelled == false )
  {
     runtime_time_pass( &RUNTIME, 60 );
  }
}  
