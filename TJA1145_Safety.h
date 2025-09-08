// File: TJA1145_Safety.h
// Description: Header for TJA1145 SPI and safety control

#ifndef TJA1145_SAFETY_H
#define TJA1145_SAFETY_H

#include <stdint.h>

// === SPI-level access ===
void TJA1145_WriteRegister(unsigned char address, unsigned char value);
unsigned char TJA1145_ReadRegister(unsigned char address);

// === TJA1145 initialization and safety control ===
void TJA1145_Init(void);
void TJA1145_MonitorSafety(void);

#endif // TJA1145_SAFETY_H