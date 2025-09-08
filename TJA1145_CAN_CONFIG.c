/* 
 *
 *  Created on: Jun 09, 2025
 *      Author: Aditya Garg                                   */ 

// File: TJA1145_CAN_Config.c
// Description: Full configuration of TJA1145 for CAN ID, DLC, masks, and safety-based mode switching
// Microcontroller: RH850/P1M | IDE: CS+

#include "TJA1145_Safety.h"
#include "HS_SPI_Master_CSIH0.h"
#include "SPI_CSIH_USER_CONFIG.h"
#include "iodefine.h"

// === Set CAN Standard Identifier and DLC ===
void TJA1145_SetCAN_ID(unsigned short std_id)
{
    unsigned char id_low  = std_id & 0xFF;  // Extract lower 8 bits (ID[7:0])
    unsigned char id_high = (std_id >> 8) & 0x07; // Extract upper 3 bits (ID[10:8])

    TJA1145_WriteRegister(0x27, id_low);    // ID[7:0]
    TJA1145_WriteRegister(0x28, id_high);   // ID[10:8]
    TJA1145_WriteRegister(0x2F, 0x08);      // DLC = 8, IDE = 0 (standard)
}

// === Set CAN ID Mask for Filtering ===
void TJA1145_SetCAN_Mask(unsigned long mask)
{
    TJA1145_WriteRegister(0x2B, (mask >> 0) & 0xFF);
    TJA1145_WriteRegister(0x2C, (mask >> 8) & 0xFF);
    TJA1145_WriteRegister(0x2D, (mask >> 16) & 0xFF);
    TJA1145_WriteRegister(0x2E, (mask >> 24) & 0xFF);
}

// === Enable Wake Edge Detection (WAKE Pin) ===
void TJA1145_EnableWakeEdgeDetection(void)
{
    TJA1145_WriteRegister(0x4C, 0x03); // Rising + Falling edge
}

// === Set CAN Control (CMC and PNCOK) ===
void TJA1145_SetCANControl(void)
{
    TJA1145_WriteRegister(0x20,(3<<4)| (1<<0)); // CMC = 01 (Active), PNCOK = 1
}

// === Safety-Driven Mode Switching ===
void TJA1145_HandleSafetyMode(void)
{
    unsigned char main_status = TJA1145_ReadRegister(0x03); // Main Status
    unsigned char trans_stat  = TJA1145_ReadRegister(0x22); // Transceiver Status
    unsigned char sys_status  = TJA1145_ReadRegister(0x61); // System Event

    // Overtemperature shutdown or warning
    if (main_status & (1 << 6) || sys_status & (1 << 2)) {
        // OTWS or OTW set
        TJA1145_WriteRegister(0x01, 0x04); // Standby mode
        TJA1145_WriteRegister(0x61, (1 << 2)); // Clear OTW
    }
    // Undervoltage detected
    else if (trans_stat & (1 << 1)) {
        TJA1145_WriteRegister(0x01, 0x01); // Sleep mode
    }
    // Recovery: return to Normal if safe
    else if (!(main_status & (1 << 5))) {
        TJA1145_WriteRegister(0x01, 0x07); // Normal mode
    }
}

// === Complete TJA1145 CAN Setup ===
void TJA1145_ConfigureCAN(unsigned short can_id, unsigned long mask)
{
    TJA1145_SetCAN_ID(can_id);
    TJA1145_SetCAN_Mask(mask);
    TJA1145_EnableWakeEdgeDetection();
    TJA1145_SetCANControl();
    TJA1145_WriteRegister(0x01, 0x07); // Set Normal mode
}
// === Send CAN Data Frame (8 Bytes) === To be used in TJA1145 in stand alone mode
/*void TJA1145_SendCANFrame(unsigned char *data)
{
    unsigned char i;
    for ( i = 0; i < 8; i++)
        TJA1145_WriteRegister(0x31 + i, data[i]);
}*/

unsigned char CAN_ReadFrame(unsigned char *buffer)
{
    // Check receive new data flag for mailbox 1 (bit 1 of RMND0)
    if (RSCAN0.RMND0.UINT32 & (1 << 1))
    {
        unsigned long low = RSCAN0.RMDF01.UINT32;
        unsigned long high = RSCAN0.RMDF11.UINT32;

        buffer[0] = (low      ) & 0xFF;
        buffer[1] = (low  >> 8) & 0xFF;
        buffer[2] = (low  >>16) & 0xFF;
        buffer[3] = (low  >>24) & 0xFF;
        buffer[4] = (high     ) & 0xFF;
        buffer[5] = (high >> 8) & 0xFF;
        buffer[6] = (high >>16) & 0xFF;
        buffer[7] = (high >>24) & 0xFF;

        // Clear NEW DATA FLAG for mailbox 1 (by writing 1)
        RSCAN0.RMND0.UINT32 = (1 << 1);

        return 1;
    }

    return 0;
}


// === Transmit CAN frame via RH850 ===
unsigned char CAN_SendFrame(unsigned short id, unsigned char *data)
{
    // Load ID into TMID0 (Standard ID shifted to bit 18)
    RSCAN0.TMID0.UINT32 = ((unsigned long)id << 18);

    // Load the data fields into TMDF00 and TMDF10
    RSCAN0.TMDF00.UINT32 = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    RSCAN0.TMDF10.UINT32 = (data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4];

    // Set Data Length Code = 8 bytes
    RSCAN0.TMPTR0.BIT.TMDLC = 8;

    // Request Transmission
    RSCAN0.TMC0.BIT.TMTR = 1;

    // Wait for transmission to complete (TMTR bit auto-clears to 0 when done)
    while (RSCAN0.TMC0.BIT.TMTR);

    return 1;
}


// === Check Transmit Success ===
unsigned char TJA1145_CheckTXSuccess(void)
{
    unsigned char status = TJA1145_ReadRegister(0x22); // Transceiver Status
    return !(status & (1 << 0)); // 0 = Success, 1 = TX Error
}
