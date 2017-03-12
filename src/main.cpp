/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Servo.h>

#include "serial.h"


static Servo servo;  //
void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  serial_setup();
  servo.attach( 9 );
  
}

void servo_set_hole( int index );

void servo_init()
{
  servo_set_hole(-1); 
}


void servo_set_hole( int index )
{
   static int old_value = 650;
   static const int n_steps = 20;
   
   int target_value = index * 125 + 700;
   
   if (target_value < 0 )
      target_value = 0;
   if (target_value > 1650)
      target_value = 1650;
   
   int value_inc = ( target_value - old_value )/(n_steps-1);
   for ( int loop_steps = 0; loop_steps < n_steps; loop_steps ++ )
   {
      int value = old_value + value_inc*loop_steps;
      servo.write( (value + 5) / 10 );
      delay( 10 );
   }
   
   old_value = target_value;
}

void handle_setup()
{
   Serial.write("Input number of days to stay\n");
   long ndays = serial_receive_number( );

   Serial.write("Input number holes filled\n");
   long nholes = serial_receive_number( );
   

   float holes_per_day = (float)nholes / (float)ndays ;
   float sleep_mins = (24.0f * 60.0f) / holes_per_day ;
   
   Serial.write("This means ");
   Serial.print( holes_per_day);
   Serial.write( " holes per day\n -> sleep of ");
   Serial.print( sleep_mins );
   Serial.write( " minutes between holes\n");
 
   
}


void handle_receive( int sleep_time )
{
   
   for ( int loop = 0; loop < sleep_time; loop += 100 )
   {
        int input_n = 0;
        char* input = serial_receive( &input_n );
        
        delay( 100 );
        if (input == NULL )
           continue;
        
        if (strcmp( input, "setup") == 0 )
        {
           handle_setup();
        }
        else
        {
           Serial.write("Invalid command '");
           Serial.write( input );
           Serial.write("'\n");
           Serial.write(">");
        }
   }
   
}

void loop()
{
  static bool state = 0;
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  
  
  
  static int hole_loop = -1;
  servo_set_hole( hole_loop );
  hole_loop += 1;
  if (hole_loop > 8)
     hole_loop = 8;


  handle_receive( 2000 );

}  


