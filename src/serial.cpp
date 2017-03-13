


#include <Arduino.h>
#include "serial.h"

void serial_setup()
{
  Serial.begin(9600); 
  Serial.write("***********************************\n");  
  Serial.write("Welcome to my project!\n");
  Serial.write("***********************************\n");
  Serial.write( ">" );   
}

bool serial_process_number( const char* buffer, int buffer_n, int* convert )
{
    char* end_ptr;
    int value = strtol( (const char*)buffer, &end_ptr, 10  );
    if ( end_ptr != buffer + buffer_n )
    {
        Serial.write(" Invalid: '" );
        Serial.write( (const char*)buffer);
        Serial.write("'\n"); 
        return false;
    }
    
    *convert = value;
    return true;
}



char* serial_receive( int* buffer_len)
{
  static char buffer[64];
  static int loop = 0;
  
  // if there's any serial available, read it:
  while (Serial.available() > 0) 
  {
    // do it again:
    buffer[ loop ] = Serial.read();

    if (buffer[loop] == '\n')
    {
      buffer[loop] = 0x00;
      *buffer_len = loop;
      loop = 0;
      return buffer;
    }

    loop += 1;
    if ( loop >= 64 )
    {
      Serial.write("E: Too long line\n");
      loop = 0;
    }
    
  }
  return NULL;
}

 
void serial_print_int( const char* desc, int v )
{
   Serial.write( desc );
   Serial.println( v );
}

int serial_receive_number(int min_value, int max_value)
{
   int buffer_n = 0;
   int number;
   bool print_prompt = true;
   
   while ( true ) 
   {
      if ( print_prompt )
      {
        Serial.write(">");
        print_prompt = false;
      }
      char* buffer = serial_receive( &buffer_n );
      if ( buffer == NULL )
        continue;
      Serial.write(buffer);
      Serial.write("\n");
     
      print_prompt = true;
      
      if ( serial_process_number( buffer, buffer_n , &number ) == false )
        continue;
      
      if ( number < min_value )
      {
         serial_print_int("Too small number. Min ", min_value );
      }   
      else if ( number > max_value)
      {
         serial_print_int("Too large number. Max ", max_value );
      }
      else
      {
         return number;
      }
   }
}
