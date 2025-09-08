/* 
 *
 *  Created on: Jun 02, 2025
 *      Author: DXR1COB/ Aditya Garg                                   */ 

#include "GP_SPI_Master_CSIG0.h"
#include "SPI_USER_CONFIG.h"
#include "iodefine.h"


void CSIG0_Master_Init(void)
{
    /* Power on */
    CSIG0.CTL0.BIT.PWR = 1;
    /* Disable before config */
    CSIG0.CTL0.BIT.MBS = 0;

    /* Set as master */
    CSIG0.CTL2.BIT.PRS = SPI_CSIG0_BRG_DIV;    // PRS[2:0]
    CSIG0.CTL2.BIT.BRS = SPI_CSIG0_BAUD_RATE;  // BRS[11:0]

    /* Data format */
    CSIG0.CFG0.BIT.DIR = 0;                    // MSB first
    CSIG0.CFG0.BIT.DLS = SPI_CSIG0_DATA_LENGTH;  // Bit length

    CSIG0.CFG0.BIT.PS = SPI_CSIG0_PARITY_ODD;
    

    /* Enable SPI */
    CSIG0.CTL0.BIT.MBS = 1;
    CSIG0.CTL0.BIT.TXE = 1;  // Enable transmit
    CSIG0.CTL0.BIT.RXE = 1;  // Enable receive
}

void CSIG0_Master_Send(unsigned short data)
{
    while (CSIG0.STR0.BIT.TSF);  // Wait if transfer in progress
    CSIG0.TX0H.UINT16 = data; //TX0W--> If data is >16 bit used for EDL
                       //TX0H--> If data is <=16 bit
}

unsigned short CSIG0_Master_Receive(void)
{
    while (!CSIG0.STR0.BIT.TSF);   // Wait for transfer complete
    return CSIG0.RX0.UINT16;      //If your RX0 also has a .BIT.RX field and you only want 8 bits:
                                  // Use--> return CSIG0.RX0.BIT.RX;
}

unsigned char CSIG0_Master_IsBusy(void)
{
    return (CSIG0.STR0.BIT.TSF != 0);
}

void CSIG0_Master_ClearErrors(void)
{
    if (CSIG0.STR0.BIT.OVE) CSIG0.STCR0.BIT.OVEC = 1;
    if (CSIG0.STR0.BIT.PE)  CSIG0.STCR0.BIT.PEC  = 1;
    if (CSIG0.STR0.BIT.DCE) CSIG0.STCR0.BIT.DCEC = 1;
}