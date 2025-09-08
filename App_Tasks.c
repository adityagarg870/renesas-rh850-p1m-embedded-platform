#include "App_Tasks.h"
#include "WdgM.h"
#include "Diag.h"
#include "TJA1145_Safety.h"
#include "HS_SPI_Master_CSIH0.h"
#include "SPI_USER_CONFIG.h"

void App_Task_1ms(void) {
    // Example: Poll SPI or check fast signals
}

void App_Task_10ms(void) {
    // Example: Refresh watchdog
    WdgM_Init(300U);

    // Example: Poll TJA1145 status
     TJA1145_MonitorSafety();
}

void App_Task_100ms(void) {
    // Example: Run diagnostics aggregation
    Diag_Init();
}
