#ifndef CSIG_SPI_MASTER_HS_H
#define CSIG_SPI_MASTER_HS_H

#include <stdint.h>

void CSIG_MasterHS_Init(void);
void CSIG_MasterHS_Transmit(unsigned long data);
unsigned char CSIG_MasterHS_Receive(void);

#endif // CSIG_SPI_MASTER_HS_H