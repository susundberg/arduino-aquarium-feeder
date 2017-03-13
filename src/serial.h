#ifndef SUPA_SERIAL_H
#define SUPA_SERIAL_H


bool serial_process_number( const char* buffer, int buffer_n, int* convert );
char* serial_receive( int* buffer_len );
void serial_setup();
int serial_receive_number( int min_value, int max_value );
void serial_print_int( const char* explain, int v );
#endif
