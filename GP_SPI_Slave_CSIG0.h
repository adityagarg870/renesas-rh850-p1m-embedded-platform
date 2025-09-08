#ifndef GP_SPI_SLAVE_CSIG0_H
#define GP_SPI_SLAVE_CSIG0_H

#include "SPI_USER_CONFIG.h"
#include <stdint.h>

void CSIG0_Slave_Init(void);
void CSIG0_Slave_Send(unsigned short data);
unsigned short CSIG0_Slave_Receive(void);
unsigned char CSIG0_Slave_IsBusy(void);
void CSIG0_Slave_ClearErrors(void);

#endif