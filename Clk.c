#include "iodefine.h"
#include "clk.h"

void Clk_Init(void)
{
    // ==== 1. Enable CSIH0 Clock Logic ====
    CSIH0.CTL0.BIT.PWR = 1;

    // ==== 2. Enable RS-CAN0 Global Operation ====
    RSCAN0.GCTR.UINT32 = 0x00000000;  // Set GMDC = 00b: Global Operation Mode

    // Wait for RS-CAN to fully enter operating mode (GMSTS = 00b)
    while ((RSCAN0.GSTS.UINT32 & 0x03) != 0);
}
	