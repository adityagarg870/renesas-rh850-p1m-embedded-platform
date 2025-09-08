#include "System_Init.h"
#include "iodefine.h"

#define SPI_SCK_PORT_INIT()         do { \
                                        /* For P3_8 as CSIH0SCK: Select ALT-OUT-1 */ \
					PORT.PM3.BIT.PM3_8 = 0; \
                                        PORT.PFC3.BIT.PFC3_8 = 0; \
                                        PORT.PFCE3.BIT.PFCE3_8 = 0; \
                                        PORT.PFCAE3.BIT.PFCAE3_8 = 0; \
                                        /* Enable Peripheral Mode */ \
                                        PORT.PMC3.BIT.PMC3_8 = 1; \
                                        /* Give Peripheral Control over pin */ \
                                        PORT.PIPC3.BIT.PIPC3_8 = 1; \
                                    } while(0)
#define SPI_MOSI_PORT_INIT()        do { \
					/* For P3_7 as CSIH0SO: Select ALT-OUT-1 */ \
					PORT.PM3.BIT.PM3_7 = 0; \
					PORT.PFC3.BIT.PFC3_7 = 0; \
					PORT.PFCE3.BIT.PFCE3_7 =0; \
					PORT.PFCAE3.BIT.PFCAE3_7 =0; \
					/* Enable Peripheral Mode */ \
					PORT.PMC3.BIT.PMC3_7 = 1; \
					/* Give Peripheral Control over pin */ \
					PORT.PIPC3.BIT.PIPC3_7 = 1; \
				    } while(0)
#define SPI_MISO_PORT_INIT()	    do{ \
                                       /*For P3_6 as CSIH0SI : Select ALT-IN-1 */ \
				       PORT.PM3.BIT.PM3_6 = 1; \
				       PORT.PFC3.BIT.PFC3_6 = 0; \
				       PORT.PFCE3.BIT.PFCE3_6 = 0; \
				       PORT.PFCAE3.BIT.PFCAE3_6 = 0; \
				       /*Enable Peripheral Mode */ \
				       PORT.PMC3.BIT.PMC3_6 = 1; \
				       /*Give Peripheral Control over Pin */ \
				       PORT.PIPC3.BIT.PIPC3_6 = 1; \
                                     } while(0)

#define SPI_CSS_PORT_INIT()          do{ \
                                       /*For P3_12 as CSIH0CSS0 : Select ALT-OUT-5 */ \
				       PORT.PM3.BIT.PM3_12 = 0; \
				       PORT.PFC3.BIT.PFC3_12 = 0; \
				       PORT.PFCE3.BIT.PFCE3_12 = 0; \
				       PORT.PFCAE3.BIT.PFCAE3_12 = 1; \
				       /*Enable Peripheral Mode */ \
				       PORT.PMC3.BIT.PMC3_12 = 1; \
				       /*Give Peripheral control over Pin */ \
				       PORT.PIPC3.BIT.PIPC3_12 = 1; \
                                      } while(0)
				      
// RSCAN0 (CAN)

#define CAN_RX_PORT_INIT()           do{ \
					/*For P2_0 as RSCAN0RX0 : Select ALT-OUT-1 */ \
					PORT.PM2.BIT.PM2_0 = 0; \
					PORT.PFC2.BIT.PFC2_0 = 0; \
					PORT.PFCE2.BIT.PFCE2_0 = 0; \
					PORT.PFCAE2.BIT.PFCAE2_0 = 0; \
					/*Enable Peripheral Mode */ \
					PORT.PMC2.BIT.PMC2_0 = 1; \
					/*Give Peripheral Control over 	Pin */ \
					PORT.PIPC2.BIT.PIPC2_0 = 1; \
					}while(0)
				      
#define CAN_TX_PORT_INIT()           do{ \
					/*For P2_1 as RSCAN0TX0 : Select ALT-IN-1 */ \
					PORT.PM2.BIT.PM2_1 = 1; \
					PORT.PFC2.BIT.PFC2_1 = 0; \
					PORT.PFCE2.BIT.PFCE2_1 = 0; \
					PORT.PFCAE2.BIT.PFCAE2_1 = 0; \
					/*Enable Peripheral Mode */ \
					PORT.PMC2.BIT.PMC2_1 = 1; \
					/*Give Peripheral Control over 	Pin */ \
					PORT.PIPC2.BIT.PIPC2_1 = 1; \
					}while(0)
					
#define PROTECTION_KEY (0x000000A5U) // This key is used to unlock write-protected registers.

static void Clock_Init(void){
	
/**
 * @brief Initializes the main clock system of the RH850/P1M.
 * * This function performs the following sequence:
 * 1. Starts the Main Oscillator (MOSC) using an external 16MHz crystal.
 * 2. Configures and starts the main PLL (PLL0) to generate a 160MHz CPU clock.
 * 3. Switches the main system clock source from the default internal oscillator to the PLL.
 */
	
	// As per Table 4.3 in the user manual, PROT1PHCMD is used for Clock Controller
	// register for the "LVI / Reset / Clock Controller / BIST" group.
	// --- Step 1: Start the Main Oscillator (External Crystal)
	// Reference: Section 12.3 in the RH850/P1M User's Manual.
	SYS.PROT1PHCMD.UINT32 = PROTECTION_KEY; //Unlock Protection for Clock Controller
	
}

static void Port_Init(void){
	SPI_SCK_PORT_INIT();
	SPI_MOSI_PORT_INIT();
	SPI_MISO_PORT_INIT();
	SPI_CSS_PORT_INIT();
	CAN_TX_PORT_INIT();
	CAN_RX_PORT_INIT();
}
	
void System_Init(void){
	Port_Init();
}