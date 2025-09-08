#ifndef GP_SPI_MASTER_CSIG0_H
#define GP_SPI_MASTER_CSIG0_H

#include "SPI_USER_CONFIG.h"
#include <stdint.h>

void CSIG0_Master_Init(void);
void CSIG0_Master_Send(unsigned short data);
unsigned short CSIG0_Master_Receive(void);
unsigned char CSIG0_Master_IsBusy(void);
void CSIG0_Master_ClearErrors(void);

#endif