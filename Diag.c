#include "Diag.h"
#include <stdint.h>
#include <stdio.h>

static unsigned long s_last_error = 0;
static unsigned long s_error_count = 0;

void Diag_Init(void)
{
    s_last_error = 0;
    s_error_count = 0;
}

void Diag_ReportError(Diag_Module_t module, Diag_Error_t code)
{
    s_error_count++;
    s_last_error = ((unsigned long)module << 16) | ((unsigned long)code << 8) | (s_error_count & 0xFF);
    // Optionally, route to UART/logging for post-mortem
    // Example (replace with your UART logging):
    // printf("DIAG: module=%u code=%u count=%u\n", module, code, s_error_count);
}

unsigned long Diag_GetLastError(void)
{
    return s_last_error;
}
