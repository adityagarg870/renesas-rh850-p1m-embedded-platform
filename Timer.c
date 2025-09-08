#include "timer.h"
#include "iodefine.h"

/*********************************************************
 * Constants
 *********************************************************/

#define TIMER_PRESCALER       0U           // CK0 = fCLK/1
#define TIMER_CK_FREQ         10000000UL   // Adjust to your fCLK (10 MHz assumed)
#define TIMER_COMPARE_VALUE   (TIMER_CK_FREQ / 1000) // 1 ms interval

/*********************************************************
 * Function: Timer_Init
 * --------------------
 * Configures TAUJ0 Channel 1 as interval timer (1ms)
 *********************************************************/
 volatile unsigned long g_ms_tick = 0;
void Timer_Init(void)
{
    TAUJ0.TT.BIT.TT01 = 1;  // Stop channel 1
    TAUJ0.TPS.UINT16 = TIMER_PRESCALER;

    TAUJ0.CMOR1.BIT.CKS = 0;  // CK0
    TAUJ0.CMOR1.BIT.MD    = 0;  // Interval timer mode
    TAUJ0.CMOR1.BIT.MAS   = 0;  // Not master
    TAUJ0.CMOR1.BIT.STS   = 0;  // Rising edge

    TAUJ0.CMUR1.UINT8 = 0x00;

    TAUJ0.CDR1 = TIMER_COMPARE_VALUE; // Count for 1 ms delay
     g_ms_tick = 0;
    
}

/*********************************************************
 * Function: Timer_DelayMs
 * -----------------------
 * Simple blocking delay using polling
 *********************************************************/
void Timer_DelayMs(unsigned short ms)
{
    unsigned short i;

    for (i = 0; i < ms; i++)
    {
        TAUJ0.TS.BIT.TS01 = 1;  // Start Channel 1

        // Wait until counter match occurs
        while (TAUJ0.CSR1.BIT.OVF == 0);

        TAUJ0.CSR1.BIT.OVF = 0; // Clear interrupt flag
        TAUJ0.TT.BIT.TT01 = 1;   // Stop the timer
    }
}

/* Example ISR – increment tick every 1 ms */
void Timer1_ISR(void)
{
    g_ms_tick++;

    /* Clear interrupt flag */
    TAUJ0.CSR1.BIT.OVF = 0;
}