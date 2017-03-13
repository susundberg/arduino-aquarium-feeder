
#ifndef SUPA_CRC_H
#define SUPA_CRC_H


#define CRC_DEFAULT_SEED (0xFFFFL)

unsigned long crc_calculate(unsigned long crc, const char* buffer, int buffer_n) ;


#endif