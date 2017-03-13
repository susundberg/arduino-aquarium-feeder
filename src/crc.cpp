

#include "crc.h"

unsigned long crc_calculate(unsigned long crc, const char* buffer, int buffer_n) 
{

  const unsigned long crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
  };

  for (int index = 0 ; index < buffer_n; index++) 
  {
    crc = crc_table[(crc ^ buffer[index]) & 0x0f] ^ (crc >> 4);
    crc = crc_table[(crc ^ (buffer[index] >> 4)) & 0x0f] ^ (crc >> 4);
    crc = ~crc;
  }
  return crc;
}
