#ifndef SPI_USER_CONFIG_H
#define SPI_USER_CONFIG_H

/* Select Mode */
#define SPI_CSIG_MODE_MASTER   (1U)
#define SPI_CSIG_MODE_SLAVE    (0U)

/* User Configuration */
#define SPI_CSIG0_MODE          SPI_CSIG_MODE_MASTER

/* Clock and Baud Rate */

/* WARNING --> Master mode is enabled by setting bits CSIGnCTL2.CSIGnPRS[2:0] to anything but 111B. In master 
mode, the BRG frequency setting is enabled by setting bits CSIGnCTL2. CSIGnPRS[2:0] and bits 
CSIGnCTL2.CSIGnBRS[11:0] */

#define SPI_CSIG0_BRG_DIV       (0x02U)     // BRG clock divider setting
#define SPI_CSIG0_BAUD_RATE     (0x003CU)   // CSIGnCTL2.CSIGnBRS[11:0]

/* Data Format */
#define SPI_CSIG0_DATA_LENGTH   (0x07U)     // 8-bit data (0x07 means 8 bits)

#define SPI_CSIG0_PARITY_ODD    (2U)        // 1 0 Add odd parity Odd parity bit is expected.
                                            // 1 1 Add even parity Even parity bit is expected

#endif /* SPI_USER_CONFIG_H */