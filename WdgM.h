#ifndef WDGM_H
#define WDGM_H
#endif // WDGM_H
#ifndef BOOL_TYPEDEF
#define BOOL_TYPEDEF
typedef unsigned char bool;
#define true  1
#define false 0
#endif


#include <stdint.h>
#include <stdbool.h>

void WdgM_Init(unsigned long service_period_ms); // init manager; service_period_ms is expected feed interval
void WdgM_Service(void); // call periodically from scheduler
bool WdgM_ShouldFeed(void); // optional check

// Hardware-specific: implement this function in BSP to actually "kick" the watchdog.
void WDT_Feed_HW(void);

