#include <Arduino.h>

#include "delay.h"
#include "serial.h"

void DelayFromPin::setup( int pin_1, int pin_2, int pin_4 )
{
   const int source[] = { pin_1, pin_2, pin_4 };
   for ( int loop = 0; loop < 3; loop ++ )
   {
      this->pins[loop] = source[loop];
      pinMode( this->pins[loop] ,  INPUT_PULLUP );
   }
}

void DelayFromPin::loop()
{
   int sum = 0;
   for ( int loop = 0; loop < 3; loop ++ )
   {
      int raw = ( digitalRead( this->pins[loop] ) == 0 );
      sum = sum + ( raw << (loop) );
   }
   int new_delay = sum * this->delay_multiplier;
   if ( new_delay != delay )
   {
      serial_print("Delay set to %d\n", new_delay );
   }
      
   this->delay = new_delay;
}
    

int DelayFromPin::get_delay_min()
{
   return this->delay;
}