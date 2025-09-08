/* 
 *
 *  Created on: Jun 09, 2025
 *      Author: Aditya Garg                                   */ 

#ifndef SPI_CSIH_USER_CONFIG_H
#define SPI_CSIH_USER_CONFIG_H

// Mode Selection
#define CSIHSPI_MODE_MASTER     1
#define CSIHSPI_MODE_SLAVE      0
#define CSIHSPI_USE_MODE        CSIHSPI_MODE_MASTER

// Clock & Speed
#define CSIHSPI_PCLK_DIV        1     // PRS =1 ->PCLK/2 0: no divide, 1: /2, 2: /4, etc.
#define CSIHSPI_BAUD_RATE       10    // Baud rate value for CSIH0.BRS0

/* Data Format
CAUTION

When CSIHnTX0W.CSIHnEDL = 1, the setting of this bit is invalid. (the data 
length is 16 bits), when CSIHnTX0W.CSIHnEDL = 0, the setting of this bit is 
valid. Only when the previous transmit data is 16 bits while CSIHnEDL = 1, 
writing 1 to this bit is enabled.*/

#define CSIHSPI_DATA_LENGTH     16     // 8-16 bits

#define CSIHSPI_MSB_FIRST       0     // 0: MSB first, 1: LSB first

// Handshake
#define CSIHSPI_USE_HANDSHAKE   1

// DMA (optional)
#define CSIHSPI_USE_DMA         0    // 1: enable DMA-based transfer

// Multi-device support (manual chip select pin)
#define CSIHSPI_CS_GPIO_PORT    PORT.P1
#define CSIHSPI_CS_GPIO_BIT     1

#endif /* SPI_CSIH_USER_CONFIG_H */