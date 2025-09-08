#include "Crc.h"
#include "stdint.h"
#include "stddef.h"

/* Polynomial: x^6 + x + 1 -> 0b1000011 -> 0x43
   Implementation: MSB-first bitwise (no reflection). Initial remainder = 0.
   Produces 6-bit remainder (0..0x3F).
*/
unsigned char Crc6_Calc(const unsigned char *data, size_t len)
{
    const unsigned char POLY = 0x43; // 0b1000011
    unsigned char rem = 0;
    unsigned char b;
    int bit;
    unsigned char bit_in;
    unsigned char msb;
    size_t i;
    for (i = 0; i < len; ++i) {
        b = data[i];
        for (bit = 7; bit >= 0; --bit) {
            bit_in = (b >> bit) & 0x01;
            // shift rem left by 1, insert bit_in at LSB of extended remainder
           msb = (rem >> 5) & 0x01; // rem is 6-bit, msb is bit5 before shift
            rem = (unsigned char)((rem << 1) & 0x3F); // keep 6 bits
            rem |= bit_in;
            if (msb) {
                rem ^= POLY & 0x3F; // polynomial applied to 6 bits
            }
        }
    }
    return rem & 0x3F;
}
