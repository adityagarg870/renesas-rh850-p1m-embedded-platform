#include "HS_SPI_Master_CSIG0.h"
#include "iodefine.h"

// CSIG0 is used; change if using CSIG1, CSIG2, etc.
#define SPI_CSIG             CSIG0
#define SPI_DATA_LENGTH      7U         // 8-bit data (value = bits - 1)
#define WAIT_FOR_TX_READY() while (!(SPI_CSIG.STR0.UINT32 & (1 << 1)))
#define WAIT_FOR_RX_READY() while (!(SPI_CSIG.STR0.UINT32 & (1 << 0)))

void CSIG_MasterHS_Init(void) {
    // Disable SPI before configuration
    SPI_CSIG.CTL0.UINT8 = 0x00000000;
    
    SPI_CSIG.CTL0.UINT8 = 0x10000000;

    // Set master mode (CTL1 bit 0 = 1)
    SPI_CSIG.CTL1.UINT32 = 0x00000001;

    // Configure data length and no parity
    SPI_CSIG.CFG0.UINT32 =
        (SPI_DATA_LENGTH << 24); // 8-bit frame (DLS)

    // High-speed: minimal wait (bit 4 = 0), full-duplex enabled
    SPI_CSIG.CTL2.UINT16 = 0x00000000;

    // Enable SPI module (CTL0 bit 15 = 1)
    SPI_CSIG.CTL0.UINT8 = 0x00008000;
}

void CSIG_MasterHS_Transmit(unsigned long data) {
    WAIT_FOR_TX_READY();
    SPI_CSIG.TX0W.UINT32 = data;
}

unsigned char CSIG_MasterHS_Receive(void) {
    WAIT_FOR_RX_READY();
    return (unsigned char)(SPI_CSIG.RX0.UINT16 & 0xFF);
}