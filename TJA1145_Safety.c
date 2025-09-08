/* 
 *
 *  Created on: Jun 09, 2025
 *      Author: Aditya Garg                                   */ 

// File: TJA1145_Safety.c
// Description: TJA1145 SPI communication and safety/status control for RH850/P1M

#include "TJA1145_Safety.h"
#include "HS_SPI_Master_CSIH0.h"
#include "SPI_CSIH_USER_CONFIG.h"
#include "iodefine.h"

// === SPI Write to TJA1145 Register ===
void TJA1145_WriteRegister(unsigned char address, unsigned char value)
{
    unsigned short frame = ((address << 1) & 0xFE) << 8 | value;
    CSIHSPI_Master_ChipSelect(1);
    CSIHSPI_Master_Send(frame);
    CSIHSPI_Master_ChipSelect(0);
}

// === SPI Read from TJA1145 Register ===
unsigned char TJA1145_ReadRegister(unsigned char address)
{
    unsigned short command = ((address << 1) | 0x01) << 8;
    unsigned short response = CSIHSPI_Master_Receive();
    CSIHSPI_Master_ChipSelect(1);
    CSIHSPI_Master_Send(command);
    
    CSIHSPI_Master_ChipSelect(0);
    return (unsigned char)(response & 0xFF);
}

// === Basic Init: Safety Interrupts, Wake Support, Normal Mode ===
void TJA1145_Init(void)
{
    // Enable Overtemperature Warning and SPI Error Detection
    TJA1145_WriteRegister(0x04, 0x06);

    // Enable CAN wake-up, CAN failure detection
    TJA1145_WriteRegister(0x23, 0x05);

    // Wake pin configuration (edge detection)
    TJA1145_WriteRegister(0x4C, 0x03);

    // Activate CAN transceiver and confirm frame filters
    TJA1145_WriteRegister(0x20, 0x05);

    // Set transceiver to Normal mode
    TJA1145_WriteRegister(0x01, 0x07);
}

// === Periodic Safety Monitoring ===
void TJA1145_MonitorSafety(void)
{
    unsigned char main_status = TJA1145_ReadRegister(0x03);
    unsigned char sys_status  = TJA1145_ReadRegister(0x61);
    unsigned char trans_stat  = TJA1145_ReadRegister(0x22);

    if (!(main_status & (1 << 5))) {
        // NMS = 0 (not in normal)
        TJA1145_WriteRegister(0x01, 0x07);
    }

    if (main_status & (1 << 7)) {
        // FSMS: Forced sleep mode
        // Log or handle as needed
    }

    if (main_status & (1 << 6)) {
        // OTWS: Overtemperature warning
        // Switch to standby or notify system
    }

    if (trans_stat & (1 << 1)) {
        // VCS: VCC undervoltage
        // Optionally switch to standby
    }

    if (sys_status & (1 << 2)) {
        // OTW: Overtemperature warning (latched)
        TJA1145_WriteRegister(0x61, (1 << 2)); // Clear OTW
    }
}