#include "WdgM.h"
#include "Timer.h" // extern volatile uint32_t g_ms_tick
#include "Diag.h"
#include "stdbool.h"

static unsigned long s_service_period = 100; // default 100 ms
static unsigned long s_last_service = 0;
static bool s_initialized = false;

void WdgM_Init(unsigned long service_period_ms)
{
    s_service_period = (service_period_ms == 0) ? 100 : service_period_ms;
    s_last_service = g_ms_tick;
    s_initialized = true;
}

/* WdgM_Service: should be registered in SchM at a high frequency (>= service_period_ms) */
void WdgM_Service(void)
{
	 unsigned long  now;
    if (!s_initialized) return;

    now = g_ms_tick;
    if ((unsigned long )(now - s_last_service) >= s_service_period) {
        // call HW-specific feed (weak function implemented in BSP)
        WDT_Feed_HW();
        s_last_service = now;
    }
}

bool WdgM_ShouldFeed(void)
{
    return ((unsigned long )(g_ms_tick - s_last_service) >= (s_service_period - 1));
}

/* Default weak stub: implement in BSP to perform exact register writes.
   Example:
   void WDT_Feed_HW(void) { WDT.KEY = WDT_SERVICE_KEY; }
*/
/* Default (stub) implementation of WDT feed */
void WDT_Feed_HW(void)
{
    /* If nobody overrides this, it reports an error */
    Diag_ReportError(DIAG_MODULE_WDG, DIAG_ERROR_WDG_NOT_IMPLEMENTED);
}
