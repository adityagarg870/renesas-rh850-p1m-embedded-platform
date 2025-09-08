#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stdlib.h>

/* CRC-6 (x^6 + x + 1) - polynomial 0x43 (binary 1000011)
   Returns 6-bit CRC in lower bits of uint8_t.
*/
unsigned char Crc6_Calc(const unsigned char *data, size_t len);

#endif // CRC_H
