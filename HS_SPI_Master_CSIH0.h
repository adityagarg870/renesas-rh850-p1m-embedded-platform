#ifndef HS_SPI_MASTER_CSIH0_H
#define HS_SPI_MASTER_CSIH0_H

void CSIHSPI_Master_Init(void);
void CSIHSPI_Master_Send(unsigned short data);
unsigned short CSIHSPI_Master_Receive(void);
void CSIHSPI_Master_SendDMA(unsigned short *buffer, unsigned short length);
void CSIHSPI_Master_ChipSelect(unsigned char enable);
void CSIHSPI_Master_ClearErrors(void);
unsigned char CSIHSPI_Master_Status(void);

#endif