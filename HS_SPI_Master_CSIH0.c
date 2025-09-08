/* 
 *
 *  Created on: Jun 06, 2025
 *      Author: Aditya Garg                                   */ 

#include "HS_SPI_Master_CSIH0.h"
#include "SPI_CSIH_USER_CONFIG.h"
#include "iodefine.h"

void CSIHSPI_Master_Init(void)
{
    // Power on and enable CSIH0
    CSIH0.CTL0.BIT.PWR = 0;   // Disable while configuring
    CSIH0.CTL2.BIT.PRS = 1;   // Master mode
    CSIH0.CTL0.BIT.PWR = 1;  

    CSIH0.CFG0.BIT.CKP0 = 0;  //Clock Phase 
    CSIH0.CFG0.BIT.DAP0 = 0;  //Data Phase
    CSIH0.CFG0.BIT.DIR0  = CSIHSPI_MSB_FIRST;
    CSIH0.CFG0.BIT.DLS0  = CSIHSPI_DATA_LENGTH - 1;

    CSIH0.BRS0.UINT16 = CSIHSPI_BAUD_RATE;
    // Step 3: Tell SPI to use BRS0 for CS0
    CSIH0.CFG0.BIT.BRSS0 = 0;
    


    if (CSIHSPI_USE_HANDSHAKE) {
        CSIH0.CTL1.BIT.HSE = 1;
    }

    // CS pin setup (if needed)
    CSIHSPI_Master_ChipSelect(0);  // CS High
}

void CSIHSPI_Master_Send(unsigned short data)
{
    while (CSIH0.STR0.BIT.TSF);     // Wait until idle
    CSIH0.TX0W.UINT32 = data;
}

unsigned short CSIHSPI_Master_Receive(void)
{
    while (!CSIH0.STR0.BIT.TSF);
    return CSIH0.RX0W.UINT32;
    
}

void CSIHSPI_Master_ChipSelect(unsigned char enable)
{
    if (enable)
        CSIHSPI_CS_GPIO_PORT.UINT16 &= ~(1U << CSIHSPI_CS_GPIO_BIT); // CS Low
    else
        CSIHSPI_CS_GPIO_PORT.UINT16 |= (1U << CSIHSPI_CS_GPIO_BIT); // CS High
}

void CSIHSPI_Master_ClearErrors(void)
{
    CSIH0.STCR0.BIT.OVEC  = 1;
    CSIH0.STCR0.BIT.PEC   = 1;
    CSIH0.STCR0.BIT.DCEC  = 1;
}

unsigned char CSIHSPI_Master_Status(void)
{
    return (CSIH0.STR0.UINT32 &0XFF);
}

// Optional DMA hook
void CSIHSPI_Master_SendDMA(unsigned short *buffer, unsigned short length)
{
#if (CSIHSPI_USE_DMA)
    // Set up DMAC to transfer `length` words from buffer to CSIH0TX
    // Configure DMACn, source address, dest address (CSIH0TX0W), etc.
#endif
}