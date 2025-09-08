/* 
 *
 *  Created on: Jun 03, 2025
 *      Author: DXR1COB/ Aditya Garg                                   */ 

#include "GP_SPI_Slave_CSIG0.h"
#include "SPI_USER_CONFIG.h"
#include "iodefine.h"

void CSIG0_Slave_Init(void)
{
    CSIG0.CTL0.BIT.PWR = 1;
    CSIG0.CTL0.BIT.MBS = 0;

    /* Set to slave mode */
    
    CSIG0.CTL2.BIT.PRS = 0x07U;  // Slave mode when PRS == 111b don't change the value
    CSIG0.CTL2.BIT.BRS = 0x000;  // Baud Rate Disabled 

    CSIG0.CFG0.BIT.DIR = 0;
    CSIG0.CFG0.BIT.DLS   = SPI_CSIG0_DATA_LENGTH;
    CSIG0.CFG0.BIT.PS = SPI_CSIG0_PARITY_ODD;

    CSIG0.CTL0.BIT.MBS = 1;
}

void CSIG0_Slave_Send(unsigned short data)
{
    while (CSIG0.STR0.BIT.TSF);  // Wait for previous transfer
    CSIG0.TX0H.UINT16 = data;    //TX0W--> If data is >16 bit used for EDL
                                 //TX0H--> If data is <=16 bit
}

unsigned short CSIG0_Slave_Receive(void)
{
    while (!CSIG0.STR0.BIT.TSF);
    return CSIG0.RX0.UINT16;
}

unsigned char CSIG0_Slave_IsBusy(void)
{
    return (CSIG0.STR0.BIT.TSF != 0);
}

void CSIG0_Slave_ClearErrors(void)
{
    if (CSIG0.STR0.BIT.OVE) CSIG0.STCR0.BIT.OVEC = 1;
    if (CSIG0.STR0.BIT.PE)  CSIG0.STCR0.BIT.PEC  = 1;
    if (CSIG0.STR0.BIT.DCE) CSIG0.STCR0.BIT.DCEC = 1;
}