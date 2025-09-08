#ifndef DIAG_H
#define DIAG_H

#include <stdint.h>

typedef enum {
    DIAG_MODULE_NONE = 0,
    DIAG_MODULE_SPI,
    DIAG_MODULE_CAN,
    DIAG_MODULE_TJA1145,
    DIAG_MODULE_WDG,
    DIAG_MODULE_TIMER,
    // add modules as needed
} Diag_Module_t;

typedef enum {
    DIAG_OK = 0,
    DIAG_ERROR_TIMEOUT,
    DIAG_ERROR_HW_FAULT,
    DIAG_ERROR_PARAM,
    DIAG_ERROR_WDG_NOT_IMPLEMENTED,
    // add other codes
} Diag_Error_t;

void Diag_Init(void);
void Diag_ReportError(Diag_Module_t module, Diag_Error_t code);
unsigned long Diag_GetLastError(void); // packed module<<16 | code<<8 | count low

#endif // DIAG_H
